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

    clearOutputLeds();
    
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
    // TODO output led values from pot output values
    // for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
    //     float value = Hardware::hw.cvOutputPins[i]->getAnalogValue();
    //     if(value > 0) {
    //         Hardware::hw.outputRedLeds[i]->analogWrite(0);
    //         Hardware::hw.outputGreenLeds[i]->analogWrite(value*0.1);
    //     } else {
    //         Hardware::hw.outputGreenLeds[i]->analogWrite(0);
    //         Hardware::hw.outputRedLeds[i]->analogWrite(-value*0.1);
    //     }
    // }
}
