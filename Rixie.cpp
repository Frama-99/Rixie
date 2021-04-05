#include "Rixie.h"
#include <Thread.h>
#include <ThreadController.h>

Rixie::Rixie(int numPixels, int dataPin, std::vector<std::vector<int>> numToPix)
{
    _pixels = new Adafruit_NeoPixel(numPixels, dataPin, NEO_GRB + NEO_KHZ800);
    _numToPix = numToPix;
}

void Rixie::begin()
{
    _pixels->begin();
}

void Rixie::displayDigit(uint8_t digit, uint8_t r, uint8_t g, uint8_t b)
{
    _pixels->clear();
    _pixels->setPixelColor(_numToPix[digit][0], _pixels->Color(r, g, b));
    _pixels->show();
}

void Rixie::fadeInDigit(uint8_t digit, uint8_t r, uint8_t g, uint8_t b, uint16_t duration)
{
    _pixels->clear();
    for (int i = 0; i < duration; i++)
    {
        uint8_t r_frac = (uint32_t)r * i / duration;
        uint8_t g_frac = (uint32_t)g * i / duration;
        uint8_t b_frac = (uint32_t)b * i / duration;
        _pixels->setPixelColor(_numToPix[digit][0], _pixels->Color(r_frac, g_frac, b_frac));
        _pixels->show();
        delay(1);
    }
}

void Rixie::fadeOutDigit(uint8_t digit, uint16_t duration)
{
    uint32_t packed_color = _pixels->getPixelColor(_numToPix[digit][0]);
    uint8_t r = getRGBFromPacked(packed_color, 'r');
    uint8_t g = getRGBFromPacked(packed_color, 'g');
    uint8_t b = getRGBFromPacked(packed_color, 'b');

    for (int i = duration; i > 0; i--)
    {
        uint8_t r_frac = (uint32_t)r * i / duration;
        uint8_t g_frac = (uint32_t)g * i / duration;
        uint8_t b_frac = (uint32_t)b * i / duration;
        _pixels->setPixelColor(_numToPix[digit][0], _pixels->Color(r_frac, g_frac, b_frac));
        _pixels->show();
        delay(1);
    }
    _pixels->clear();
}

/* this function does not work yet
void Rixie::crossFadeDigits(uint8_t digit1, uint8_t digit2,
                            uint8_t r2, uint8_t g2, uint8_t b2, uint16_t duration)
{
    ThreadController control = ThreadController();
    Thread outThread = Thread();
    Thread inThread = Thread();

    auto fade_out_digit_callback = [&]() {
        fade_out_digit(pixels, digit1, duration);
    };
    auto fade_in_digit_callback = [&]() {
        fade_in_digit(pixels, digit2, r2, g2, b2, duration);
    };

    outThread.onRun(fade_out_digit_callback);
    outThread.setInterval(100);
    inThread.onRun(fade_in_digit_callback);
    inThread.setInterval(100);

    control.add(&outThread);
    control.add(&inThread);

    control.run();
} */

uint8_t Rixie::getRGBFromPacked(uint32_t packed_color, char color_code)
{
    switch (color_code)
    {
    case 'r':
        return packed_color >> 16;
    case 'g':
        return packed_color >> 8;
    case 'b':
        return packed_color;
    default:
        return 0;
    }
}