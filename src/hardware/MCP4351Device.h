#ifndef MCP4351Device_h
#define MCP4351Device_h

#include <eurorack.h>

#define MCP4351_PINCOUNT 4
#define MCP4351_BITS 8

class MCP4351Device: public Device, public AnalogOutputDevice {
    public:
        MCP4351Device(uint8_t selectPin);
        void init();
        void analogWrite(uint8_t pin, uint16_t value);
        void send();

        AnalogOutputPin<MCP4351Device> pins[MCP4351_PINCOUNT] = { 
            AnalogOutputPin<MCP4351Device>(*this, 0, MCP4351_BITS, 0, 1),
            AnalogOutputPin<MCP4351Device>(*this, 1, MCP4351_BITS, 0, 1),
            AnalogOutputPin<MCP4351Device>(*this, 2, MCP4351_BITS, 0, 1),
            AnalogOutputPin<MCP4351Device>(*this, 3, MCP4351_BITS, 0, 1)
        };

    private:
        SPISettings spiSettings = SPISettings(20000000L, MSBFIRST, SPI_MODE0);

        uint8_t selectPin;
        SPISettings spiMode;
};

#endif
