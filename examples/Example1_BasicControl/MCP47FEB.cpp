#include "MCP47FEB.h"

MCP47FEB::MCP47FEB(uint8_t lat0_pin, uint8_t lat1_pin)
{
    pinMode(lat0_pin, OUTPUT);
    pinMode(lat1_pin, OUTPUT);

    digitalWrite(lat0_pin, LOW);
    digitalWrite(lat1_pin, LOW);
}

bool MCP47FEB::begin(uint8_t i2c_address, TwoWire *wire)
{
    i2c_address_ = i2c_address;
    i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

    if (!i2c_dev->begin())
    {
        return false;
    }

    return true;
}

bool MCP47FEB::testConnection()
{
    uint8_t empty_buffer[0];
    bool has_error = i2c_dev->write(empty_buffer, 0);
    return has_error;
}

inline uint8_t getMSB(uint16_t value)
{
    return (value >> (8 * 1)) & 0xff;
}

inline uint8_t getLSB(uint16_t value)
{
    return (value >> (8 * 0)) & 0xff;
}

bool MCP47FEB::setChannelValue(McpChannel_type channel, uint16_t value)
{
    uint8_t output_buffer_size = 3;
    uint8_t output_buffer[output_buffer_size];

    // write command
    // A4 A3 A2 A1 A0  0  0  0
    uint8_t register_write_command = channel << 3;

    output_buffer[0] = register_write_command;
    output_buffer[1] = getMSB(value);
    output_buffer[2] = getLSB(value);

    if (!i2c_dev->write(output_buffer, output_buffer_size))
    {
        return false;
    }
    return true;
}

bool MCP47FEB::setAllVoltageReferenceSourceToVdd()
{
    uint8_t output_buffer_size = 3;
    uint8_t output_buffer[output_buffer_size];

    uint8_t register_write_command = kVolatileVRefRegister << 3;

    output_buffer[0] = register_write_command;
    output_buffer[1] = 0b00000000;
    output_buffer[2] = 0b00000000;

    if (!i2c_dev->write(output_buffer, output_buffer_size))
    {
        return false;
    }
    return true;
}

bool MCP47FEB::setAllVoltageReferenceSourceToBandGap()
{
    uint8_t output_buffer_size = 3;
    uint8_t output_buffer[output_buffer_size];

    uint8_t register_write_command = kVolatileVRefRegister << 3;

    output_buffer[0] = register_write_command;
    output_buffer[1] = 0b01010101;
    output_buffer[2] = 0b01010101;

    if (!i2c_dev->write(output_buffer, output_buffer_size))
    {
        return false;
    }
    return true;
}

bool MCP47FEB::setAllGainsTo1x()
{
    uint8_t output_buffer_size = 3;
    uint8_t output_buffer[output_buffer_size];

    uint8_t register_write_command = kVolatileGainRegister << 3;

    output_buffer[0] = register_write_command;
    output_buffer[1] = 0b00000000;
    output_buffer[2] = 0b00000000;

    if (!i2c_dev->write(output_buffer, output_buffer_size))
    {
        return false;
    }
    return true;
}

bool MCP47FEB::setAllGainsTo2x()
{
    uint8_t output_buffer_size = 3;
    uint8_t output_buffer[output_buffer_size];

    uint8_t register_write_command = kVolatileGainRegister << 3;

    output_buffer[0] = register_write_command;
    output_buffer[1] = 0b11111111;
    output_buffer[2] = 0b00000000;

    if (!i2c_dev->write(output_buffer, output_buffer_size))
    {
        return false;
    }
    return true;
}
