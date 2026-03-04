from . import text_sensor as uart_read_line_text_sensor

CODEOWNERS = ["@user"]
DEPENDENCIES = ["uart"]

CONFIG_SCHEMA = uart_read_line_text_sensor.CONFIG_SCHEMA
to_code = uart_read_line_text_sensor.to_code
