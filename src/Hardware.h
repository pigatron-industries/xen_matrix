#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <eurorack_is32fl3738.h>
#include "hardware/MCP4351Device.h"
#include "display/OLEDDisplay.h"
// #include "Colour.h"
#include "hwconfig.h"

#define MEMPOOL_SIZE 48*1024

class Hardware {
    public:
        static Hardware hw;
        void init();

        void clearOutputLeds();
        void updateOutputLeds();

        // Memory pool
        static float memPoolBuffer[MEMPOOL_SIZE];
        MemPool<float> memPool = MemPool<float>(Hardware::memPoolBuffer, MEMPOOL_SIZE);

        // Direct connections
        RotaryEncoderButton encoder = RotaryEncoderButton(ENCODER_PIN1, ENCODER_PIN2, ENCODER_BTN_PIN);

        #define AnalogInputPinT AnalogInputPin<NativeDevice>

        AnalogInput(cv1Pin, CV1_PIN)
        AnalogInput(cv2Pin, CV2_PIN)
        AnalogInputPin<> cv1Input = AnalogInputPin<>(cv1Pin);
        AnalogInputPin<> cv2Input = AnalogInputPin<>(cv2Pin);

        // Pot outputs
        MCP4351Device mcp4351[9] = { 
            MCP4351Device(POT1_CS),
            MCP4351Device(POT2_CS),
            MCP4351Device(POT3_CS),
            MCP4351Device(POT4_CS),
            MCP4351Device(POT5_CS),
            MCP4351Device(POT6_CS),
            MCP4351Device(POT7_CS),
            MCP4351Device(POT8_CS),
            MCP4351Device(POT9_CS)
        };
        AnalogOutputPin<MCP4351Device>* matrixPots[MATRIX_ROWS][MATRIX_COLS] = {
            { &mcp4351[3].pins[1], &mcp4351[6].pins[0], &mcp4351[6].pins[1], &mcp4351[0].pins[0], &mcp4351[0].pins[1], &mcp4351[3].pins[0] },
            { &mcp4351[4].pins[3], &mcp4351[7].pins[2], &mcp4351[7].pins[3], &mcp4351[1].pins[2], &mcp4351[1].pins[3], &mcp4351[4].pins[2] },
            { &mcp4351[5].pins[1], &mcp4351[8].pins[0], &mcp4351[8].pins[1], &mcp4351[2].pins[0], &mcp4351[2].pins[1], &mcp4351[5].pins[0] },
            { &mcp4351[5].pins[3], &mcp4351[8].pins[2], &mcp4351[8].pins[3], &mcp4351[2].pins[2], &mcp4351[2].pins[3], &mcp4351[5].pins[2] },
            { &mcp4351[4].pins[1], &mcp4351[7].pins[0], &mcp4351[7].pins[1], &mcp4351[1].pins[0], &mcp4351[1].pins[1], &mcp4351[4].pins[0] },
            { &mcp4351[3].pins[3], &mcp4351[6].pins[2], &mcp4351[6].pins[3], &mcp4351[0].pins[2], &mcp4351[0].pins[3], &mcp4351[3].pins[2] }
        };

        //  LED outputs
        IS32FL3738Device is32fl3738 = IS32FL3738Device(Wire, SDB_PIN);
        AnalogOutputPin<IS32FL3738Device>* matrixLeds[MATRIX_ROWS][MATRIX_COLS] = {
            { &is32fl3738.pins[40], &is32fl3738.pins[32], &is32fl3738.pins[24], &is32fl3738.pins[16], &is32fl3738.pins[8], &is32fl3738.pins[0]},
            { &is32fl3738.pins[41], &is32fl3738.pins[33], &is32fl3738.pins[25], &is32fl3738.pins[17], &is32fl3738.pins[9], &is32fl3738.pins[1]},
            { &is32fl3738.pins[42], &is32fl3738.pins[34], &is32fl3738.pins[26], &is32fl3738.pins[18], &is32fl3738.pins[10], &is32fl3738.pins[2]},
            { &is32fl3738.pins[43], &is32fl3738.pins[35], &is32fl3738.pins[27], &is32fl3738.pins[19], &is32fl3738.pins[11], &is32fl3738.pins[3]},
            { &is32fl3738.pins[44], &is32fl3738.pins[36], &is32fl3738.pins[28], &is32fl3738.pins[20], &is32fl3738.pins[12], &is32fl3738.pins[4]},
            { &is32fl3738.pins[45], &is32fl3738.pins[37], &is32fl3738.pins[29], &is32fl3738.pins[21], &is32fl3738.pins[13], &is32fl3738.pins[5]}
        };

        OLEDDisplay display;

};

#endif