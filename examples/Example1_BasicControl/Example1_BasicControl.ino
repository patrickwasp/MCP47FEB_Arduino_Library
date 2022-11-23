#include "MCP47FEB.h"
const uint8_t lat0_pin = 1;
const uint8_t lat1_pin = 2;

MCP47FEB dac(lat0_pin, lat1_pin);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("MCP47FEB Test");

  if (!dac.begin())
  {
    Serial.println("Failed to find MCP47FEB chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("Found MCP47FEB chip");

  if (dac.testConnection())
  {
    Serial.println("Connected");
  }
  else
  {
    Serial.println("Not Connected");
  }

  delay(1000);

  if (dac.setChannelValue(kChannel0, kMinDacValue))
  {
    Serial.println("Channel Set");
  }
  else
  {
    Serial.println("Error");
  }

  dac.setAllVoltageReferenceSourceToBandGap();
  dac.setAllGainsTo2x();

  dac.setChannelValue(kChannel1, kMinDacValue);
  dac.setChannelValue(kChannel2, kMinDacValue);
  dac.setChannelValue(kChannel3, kMinDacValue);
  dac.setChannelValue(kChannel4, kMinDacValue);
  dac.setChannelValue(kChannel5, kMinDacValue);
  dac.setChannelValue(kChannel6, kMinDacValue);
  dac.setChannelValue(kChannel7, kMinDacValue);

  delay(5000);

  dac.setChannelValue(kChannel0, kMaxDacValue);
  dac.setChannelValue(kChannel1, kMaxDacValue);
  dac.setChannelValue(kChannel2, kMaxDacValue);
  dac.setChannelValue(kChannel3, kMaxDacValue);
  dac.setChannelValue(kChannel4, kMaxDacValue);
  dac.setChannelValue(kChannel5, kMaxDacValue);
  dac.setChannelValue(kChannel6, kMaxDacValue);
  dac.setChannelValue(kChannel7, kMaxDacValue);

  delay(5000);

  //// better possible api to implement
  // MCP47FEB dac(lat0_pin, lat1_pin); // varients have between 4 or 8 channels and 8/10/12 bits
  // dac.setVoltageReferenceSource(VoltageReferenceSources::kVrefPin); // other options: kDeviceVdd, kInternalBandGap
  // dac.setVrefGain(VrefGains::k1); // other options: k2
  // dac.setVrefMode(VrefModes::kBuffered); // other options: kUnbuffered
  // // for buffered mode Vref can be between 00.1V -> Vdd - 0.04V
  // // for unbuffered mode Vref can between Vss -> Vdd, Vref should have low output impedance.
  // dac.setInternalBandGapGain(InternalBandGapGains::k2) // other options: k4
  // dac.setChannelValue(DacChannels::kChannel0, 4095); // other options, 0-4095
  // dac.setChannelVoltage(DacChannels::kChannel0, 4.2); // to set an actual voltage we would need to know the
  // reference voltage and gain selected
}

void loop()
{
  delay(10);
  //   for ( int i = 0; i < kMaxDacValue + 1; i++ )
  //   {
  ////    dac.setChannelValue(kChannel1, i);
  ////    dac.setChannelValue(kChannel1, i);
  ////    dac.setChannelValue(kChannel2, i);
  ////    dac.setChannelValue(kChannel3, i);
  ////    dac.setChannelValue(kChannel4, i);
  ////    dac.setChannelValue(kChannel5, i);
  //    dac.setChannelValue(kChannel6, i);
  ////    dac.setChannelValue(kChannel7, i);
  //    delay(100);
  //   }
  //
  //   for ( int i = kMaxDacValue - 1; i > 0; i-- )
  //   {
  ////    dac.setChannelValue(kChannel1, i);
  ////    dac.setChannelValue(kChannel1, i);
  ////    dac.setChannelValue(kChannel2, i);
  ////    dac.setChannelValue(kChannel3, i);
  ////    dac.setChannelValue(kChannel4, i);
  ////    dac.setChannelValue(kChannel5, i);
  //    dac.setChannelValue(kChannel6, i);
  ////    dac.setChannelValue(kChannel7, i);
  //  delay(100);
  //   }
}