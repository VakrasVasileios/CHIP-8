#include "display.hpp"
#include <iostream>

Display::Display(int _width = 640, int _height = 480) : width(_width), height(_height) {
    if(!al_init()) {
        std::cout << "Failed to initialize allegro!!!\n";
    }

    display = al_create_display(width, height);
    display_buffer = al_create_bitmap(width, height);
}

Display::~Display() {

}

void
Display::FlipDisplay() {
    al_flip_display();
}

void
Display::ChangeDisplay(ALLEGRO_BITMAP* _bitmap) {
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgba(1,1,1,1));
    al_draw_bitmap(_bitmap, 0, 0, 0);    
}

bool*
Display::ClearPixelArray() {
    pixel_array = 0x0000;
}