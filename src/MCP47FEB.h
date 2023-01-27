#ifndef _MCP47FEB_H
#define _MCP47FEB_H

#include "Arduino.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

const uint8_t kDefaultI2cAddress = 0x60;
const uint8_t kMinDacValue = 0;
const uint8_t kMaxDacValue = 255;

// Memory Map, each memory address is 16 bits wide
//////////////////////////////////////////////////////
// TODO: change this to an enum class
const uint8_t kVolatileDac0Register = 0x00; // kMinDacValue to kMaxDacValue
const uint8_t kVolatileDac1Register = 0x01;
const uint8_t kVolatileDac2Register = 0x02;
const uint8_t kVolatileDac3Register = 0x03;
const uint8_t kVolatileDac4Register = 0x04;
const uint8_t kVolatileDac5Register = 0x05;
const uint8_t kVolatileDac6Register = 0x06;
const uint8_t kVolatileDac7Register = 0x07;
const uint8_t kVolatileVRefRegister = 0x08;            // 2 bits per channel
const uint8_t kVolatilePowerDownRegister = 0x09;       // 2 bits per channel
const uint8_t kVolatileGainRegister = 0x0A;            // bits 15-8, 1 bit per channel
const uint8_t kVolatileStatusRegister = 0x0A;          // shared with gain, read-only
                                                       // bit 7: power-on reset status, 1 = device reset, reading sets to 0
                                                       // bit 6: EEPROM write status, 1 = currently writing, cannot write to NonVolatile registers
const uint8_t kVolatileWiperLockStatusRegister = 0x0B; // no non volatile equivalent

// non voltatile registers addressses are voltatile + 0x10 (16)
const uint8_t kNonVolatileRegisterOffset = 0x10;
// const uint8_t kNonVolatileDac0Register = 0x10;
// const uint8_t kNonVolatileDac1Register = 0x11;
// const uint8_t kNonVolatileDac2Register = 0x12;
// const uint8_t kNonVolatileDac3Register = 0x13;
// const uint8_t kNonVolatileDac4Register = 0x14;
// const uint8_t kNonVolatileDac5Register = 0x15;
// const uint8_t kNonVolatileDac6Register = 0x16;
// const uint8_t kNonVolatileDac7Register = 0x17;
// const uint8_t kNonVolatileVRefRegister = 0x18;
// const uint8_t kNonVolatilePowerDownRegister = 0x19;
// const uint8_t kNonVolatileGainRegister = 0x1A;
// const uint8_t kNonVolatileStatusRegister = 0x1A;

// kVddVoltageReferenceMode = 0b00;
// kBandGapVoltageReferenceMode = 0b01;
// kVrefUnbufferedVoltageReferenceMode = 0b10;
// kVrefBufferedVoltageReferenceMode = 0b11;

typedef enum ChannelVoltageReferenceModes
{
    kVdd = 0b00,
    kBandGap = 0b01,
    kVrefUnbuffered = 0b10,
    kVrefBuffered = 0b11
};

typedef enum ChannelVoltageGains
{
    k1x = 0b0,
    k2x = 0b1
};

typedef enum PowerDownModes
{
    kNormal = 0b00,
    k1kOhmPullDown = 0b01,
    k125kOhmPullDown = 0b10,
    kOpenCircuit = 0b11
};

typedef enum MaxDacValue
{
    k8bit = 255,
    k10bit = 1023,
    k12bit = 4095
};

// inline uint8_t registerAddress(McpRegisters reg) noexcept
//{
//   return static_cast<uint8_t>(reg);
// }

// Commands
////////////////////////////////////////////////////////
typedef enum class McpCommands : uint8_t
{
    kWriteCommand = 0b00000000,
    kReadCommand = 0b00000110
} McpCommands_type;

// TODO: change this to an enum class so that it can be namespaced
// can't do shift operations (and probalby others) directly to an enum class
typedef enum McpChannel
{
    kChannel0 = kVolatileDac0Register,
    kChannel1 = kVolatileDac1Register,
    kChannel2 = kVolatileDac2Register,
    kChannel3 = kVolatileDac3Register,
    kChannel4 = kVolatileDac4Register,
    kChannel5 = kVolatileDac5Register,
    kChannel6 = kVolatileDac6Register,
    kChannel7 = kVolatileDac7Register
} McpChannel_type;

class MCP47FEB
{
public:
    MCP47FEB(uint8_t lat0_pin, uint8_t lat1_pin);
    bool begin(uint8_t i2c_address = kDefaultI2cAddress, TwoWire *wire = &Wire);

    bool testConnection();
    bool resetI2c();
    bool setAllVoltageReferenceSourceToVdd();
    bool setAllVoltageReferenceSourceToBandGap();
    bool setAllGainsTo1x();
    bool setAllGainsTo2x();
    bool setChannelValue(McpChannel_type channel, uint16_t value);

private:
    bool _init(void);
    uint8_t i2c_address_;
    uint8_t lat0_pin_;
    uint8_t lat1_pin_;

    Adafruit_I2CDevice *i2c_dev;
};

#endif