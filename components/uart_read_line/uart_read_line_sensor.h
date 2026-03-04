#ifndef UART_READ_LINE_SENSOR_H
#define UART_READ_LINE_SENSOR_H

#include "esphome.h"

namespace esphome {

class UartReadLineSensor : public Component, public uart::UARTDevice, public text_sensor::TextSensor
{
public:
  UartReadLineSensor(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}
  void setup() override {}

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
        publish_state(buffer);
    }
  }
};

}  // namespace esphome

#endif  // UART_READ_LINE_SENSOR_H
