#ifndef Matrix_h
#define Matrix_h

#include <eurorack_graphics.h>
#include "Hardware.h"
#include "hardware/MixMatrix.h"

class MatrixDisplay {
    public:
        MatrixDisplay() {}
        void init();
        void render();

        void focusBank();
        void focusMatrixMode();

        void setBank(uint8_t bank);
        void setMatrixMode(MixMatrix::Mode matrixMode);

    private:
        FocusManager<OLEDDisplay> focusManager;

        VerticalContainer<OLEDDisplay, 3> page;
        TextComponent<OLEDDisplay> title = TextComponent<OLEDDisplay>(OLEDDisplay::WIDTH, "MATRIX", 2);
        FieldComponent<OLEDDisplay> bankField = FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH, 40, "BANK:");
        FieldComponent<OLEDDisplay> matrixModeField = FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH, 40, "MODE:");
};

#endif