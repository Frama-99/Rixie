#ifndef Rixie_h
#define Rixie_h

#include "ArduinoSTL.h"
#include <vector>
#include <Adafruit_NeoPixel.h>

class Rixie
{
    public:
        Rixie(int numPixels, int dataPin, std::vector<std::vector<int>> numToPix);
        
        void begin();
        void displayDigit(uint8_t digit, uint8_t r, uint8_t g, uint8_t b);
        void fadeInDigit(uint8_t digit, uint8_t r, uint8_t g, uint8_t b, uint16_t duration);
        void fadeOutDigit(uint8_t digit, uint16_t duration);
    private:
        Adafruit_NeoPixel* _pixels;
        std::vector<std::vector<int>> _numToPix;
        uint8_t getRGBFromPacked(uint32_t packed_color, char color_code);
};

#endif