import os

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor, uart
from esphome.const import CONF_ID
from esphome.core import CORE

DEPENDENCIES = ["uart"]

CONF_UART_ID = "uart_id"

# Path to this component's directory
_COMPONENT_DIR = os.path.dirname(os.path.abspath(__file__))

# Declare C++ type so codegen knows it's a Component (implementation is in .h)
UartReadLineSensor = cg.esphome_ns.class_(
    "UartReadLineSensor",
    cg.Component,
    uart.UARTDevice,
    text_sensor.TextSensor,
)

CONFIG_SCHEMA = text_sensor.text_sensor_schema().extend(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(UartReadLineSensor),
            cv.GenerateID(CONF_UART_ID): cv.use_id(uart.UARTComponent),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    # Add our C++ header to the build (include path + include)
    CORE.add_build_flag("-I" + _COMPONENT_DIR)
    cg.add_global(cg.RawStatement('#include "uart_read_line_sensor.h"'))

    uart_var = await cg.get_variable(config[CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_var)
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
