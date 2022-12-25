#include "Hardware.h"

Hardware Hardware::hw = Hardware();

float Hardware::memPoolBuffer[MEMPOOL_SIZE];

void Hardware::init() {
    NativeDevice::instance.init();

    Wire.setSDA(SDA_PIN);
    Wire.setSCL(SCL_PIN);
    Wire.setClock(I2C_SPEED);
    Wire.begin();

    is32fl3738.init();
    // display.init();

    //clearOutputLeds();
    updateOutputLeds();
    
    // TODO reset Pot outputs
}

void Hardware::clearOutputLeds() {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            matrixLeds[i][j]->analogWrite(0);
        }
    }
}

void Hardware::updateOutputLeds() {
    Serial.println("updateOutputLeds");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            matrixLeds[i][j]->analogWrite(0.2);
            delay(50);
            matrixLeds[i][j]->analogWrite(0);
        }
    }

    for(int i = 0;  i < 9;  i++) {
        mcp4351[i].pins[0].analogWrite(0x00);
        mcp4351[i].pins[1].analogWrite(0x00);
        mcp4351[i].pins[2].analogWrite(0x00);
        mcp4351[i].pins[3].analogWrite(0x00);
    }

    // for(int i = 0;  i < 9;  i++) {
    //     mcp4351[i].pins[0].analogWrite(0xFF);
    //     mcp4351[i].pins[1].analogWrite(0xFF);
    //     mcp4351[i].pins[2].analogWrite(0xFF);
    //     mcp4351[i].pins[3].analogWrite(0xFF);
    // }

    
    // mcp4351[7].pins[0].analogWrite(0xFF);
    // mcp4351[7].pins[1].analogWrite(0xFF);
    // mcp4351[7].pins[2].analogWrite(0xFF);
    // mcp4351[7].pins[3].analogWrite(0xFF);

}
