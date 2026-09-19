import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor, uart

from . import uart_read_line_ns

DEPENDENCIES = ["uart"]

UartReadLineSensor = uart_read_line_ns.class_(
    "UartReadLineSensor",
    text_sensor.TextSensor,
    cg.Component,
    uart.UARTDevice,
)

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema(UartReadLineSensor)
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
