#pragma once

#include <allegro5/allegro5.h>

#define PIXEL_ARRAY_MASK 0x0FFF

class Display {

private:
    ALLEGRO_DISPLAY*    display;
    ALLEGRO_BITMAP*     display_buffer;

    int         height;
    int         width;
    uint16_t    pixel_array = 0x0000;
    
public:
    Display(int _width, int _height);
    ~Display();

    void    FlipDisplay();
    void    ChangeDisplay(ALLEGRO_BITMAP* _bitmap);
    void    ClearPixelArray();
};
