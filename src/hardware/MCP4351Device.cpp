#include "MCP4351Device.h"
#include <SPI.h>

#define WIPER0_WRITE_CMD 0x00
#define WIPER1_WRITE_CMD 0x10
#define WIPER2_WRITE_CMD 0x60
#define WIPER3_WRITE_CMD 0x70

MCP4351Device::MCP4351Device(uint8_t selectPin) : 
    selectPin(selectPin) {
		pinMode(selectPin, OUTPUT);
		digitalWrite(selectPin, HIGH);
        SPI.begin();
}

void MCP4351Device::init() {
}

void MCP4351Device::analogWrite(uint8_t pin, uint16_t value) {
    digitalWrite(selectPin, LOW);
    SPI.beginTransaction(spiSettings);
    uint8_t cmd = 0;
    switch(pin) {
        case 0:
            cmd = WIPER0_WRITE_CMD;
            break;
        case 1:
            cmd = WIPER1_WRITE_CMD;
            break;
        case 2:
            cmd = WIPER2_WRITE_CMD;
            break;
        case 3:
            cmd = WIPER3_WRITE_CMD;
            break;
    }
    SPI.transfer(cmd);
    SPI.transfer((uint8_t)(value & 0xff));
    SPI.endTransaction();
    digitalWrite(selectPin, HIGH);
}

void MCP4351Device::send() {
    // for(int i = 0; i < MAX11300_PINCOUNT; i++) {
    //     AnalogInputOutputPin<MAX11300Device>& pin = pins[i];
    //     if(pin.getPinType() == PinType::ANALOG_OUTPUT) {
    //         analogWrite(pin.getPin(), pin.getBinaryValue());
    //     } else if(pin.getPinType() == PinType::DIGITAL_OUTPUT) {
    //         digitalWrite(pin.getPin(), pin.getDigitalValue());
    //     }
    // }
}
