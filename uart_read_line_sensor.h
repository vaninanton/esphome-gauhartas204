#include "esphome.h"

class UartReadLineSensor : public Component, public UARTDevice, public TextSensor
{
public:
  UartReadLineSensor(UARTComponent *parent) : UARTDevice(parent) {}
  void setup() override {}

  /**
   * @brief Read a line from the uart.
   *
   * @param readch The char read from the uart.
   * @param buffer The buffer to store the line.
   * @param len The length of the buffer.
   *
   * @return The position of the end of the line in the buffer.
   *
   * readline is a helper function to read a line from the uart. It
   * stores the line in the given buffer and returns the position of
   * the end of the line. If the end of the line is not found, it will
   * store the char in the buffer and return -1.
   *
   * The static variable pos is used to keep track of the current
   * position in the buffer. When a newline or return is encountered,
   * the end of the line is stored in the buffer and pos is reset to 0.
   *
   * The function will return -1 if the end of the line is not found.
   *
   * Example:
   * const int max_line_length = 80;
   * static char buffer[max_line_length];
   * int c;
   * while ((c = uart->read()) != -1) {
   *   int rpos = readline(c, buffer, 80);
   *   if (rpos != -1) {
   *     // Do something with the line
   *   }
   * }
   */
  int readline(int readch, char *buffer, int len)
  {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
      switch (readch) {
      case '\n':
      case '\r':
        buffer[pos] = 0;
        rpos = pos;
        pos = 0;
        return rpos;
      default:
        if (pos < len - 1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        } else {
          buffer[pos] = 0;
          rpos = pos;
          pos = 0;
          return rpos;
        }
      }
    }

    return -1;
  }

  void loop() override
  {
    const int max_line_length = 30;
    static char buffer[max_line_length];
    while (available())
    {
      if (readline(read(), buffer, max_line_length) > 0)
      {
        // Publish latest buffer state to text_sensor
        publish_state(buffer);

        // RESPONSE EXAMPLES:
        // index of symbol
        //           1111111111222
        // 01234567890123456789012
        // *RA 1 0 0 0 0 0 0 0 0 $
        // *RA 2 0 0 0 0 0 0 0 0 $
        // *RK WM ON$
        // *RK WM OFF$
        if (buffer[0] == '*' && buffer[1] == 'R' && buffer[2] == 'A' && buffer[4] == '1')
        {
          // id(prt10).publish_state(buffer[6]  == '1');
          id(BathroomLight).publish_state(buffer[8] == '1');
          id(BathroomHall).publish_state(buffer[10] == '1');
          id(KitchenLight).publish_state(buffer[12] == '1');
          id(KitchenTable).publish_state(buffer[14] == '1');
          id(HallLight).publish_state(buffer[16] == '1');
          id(LivingroomSubLight).publish_state(buffer[18] == '1');
          id(BathroomSubLight).publish_state(buffer[20] == '1');
        }
        else if (buffer[0] == '*' && buffer[1] == 'R' && buffer[2] == 'A' && buffer[4] == '2')
        {
          // id(prt20).publish_state(buffer[6]  == '1');
          id(SleepingroomRight).publish_state(buffer[8] == '1');
          id(BalconyLight).publish_state(buffer[10] == '1');
          id(SleepingroomLight).publish_state(buffer[12] == '1');
          // id(prt24).publish_state(buffer[14] == '1');
          id(SleepingroomLeft).publish_state(buffer[16] == '1');
          id(LivingroomLight).publish_state(buffer[18] == '1');
          id(SleepingroomWardrobe).publish_state(buffer[20] == '1');
        }
        else if (buffer[0] == '*' && buffer[1] == 'R' && buffer[2] == 'K' && buffer[4] == 'W' && buffer[5] == 'M')
        {
          id(rkwm).publish_state(buffer[8] == 'N');
        }
      }
    }
  }
};