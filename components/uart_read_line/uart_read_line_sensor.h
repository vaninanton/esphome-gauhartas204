#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome::uart_read_line {

// Читает из UART строки, завершённые '\r' или '\n', и публикует каждую непустую строку.
// Строка длиннее MAX_LINE_LENGTH обрезается, остаток до конца строки отбрасывается.
// Непечатные байты (помехи на шине) заменяются на '?': строка уходит в API, а он принимает
// только валидный UTF-8 — иначе клиент (Home Assistant, esphome logs) обрывает соединение.
class UartReadLineSensor : public text_sensor::TextSensor, public Component, public uart::UARTDevice {
 public:
  static constexpr size_t MAX_LINE_LENGTH = 30;

  void loop() override;
  void dump_config() override;

 protected:
  char buffer_[MAX_LINE_LENGTH];
  size_t pos_{0};
  bool overflow_{false};
  bool corrupted_{false};
};

}  // namespace esphome::uart_read_line
