#include "uart_read_line_sensor.h"
#include "esphome/core/log.h"

namespace esphome::uart_read_line {

static const char *const TAG = "uart_read_line";

void UartReadLineSensor::loop() {
  uint8_t c;
  while (this->available() && this->read_byte(&c)) {
    if (c == '\0')
      continue;
    if (c == '\r' || c == '\n') {
      if (this->overflow_) {
        ESP_LOGW(TAG, "Line longer than %u chars, truncated", (unsigned) MAX_LINE_LENGTH);
      }
      if (this->pos_ > 0) {
        if (this->corrupted_) {
          ESP_LOGW(TAG, "Non-printable bytes on the bus, replaced with '?': %.*s", (int) this->pos_,
                   this->buffer_);
        }
        this->publish_state(this->buffer_, this->pos_);
      }
      this->pos_ = 0;
      this->overflow_ = false;
      this->corrupted_ = false;
    } else if (this->pos_ < MAX_LINE_LENGTH) {
      // В API уходит только печатный ASCII: невалидный UTF-8 обрывает соединение клиента
      const bool printable = c >= 0x20 && c <= 0x7E;
      this->corrupted_ |= !printable;
      this->buffer_[this->pos_++] = printable ? static_cast<char>(c) : '?';
    } else {
      this->overflow_ = true;
    }
  }
}

void UartReadLineSensor::dump_config() {
  LOG_TEXT_SENSOR("", "UART Read Line", this);
  ESP_LOGCONFIG(TAG, "  Max line length: %u", (unsigned) MAX_LINE_LENGTH);
}

}  // namespace esphome::uart_read_line
