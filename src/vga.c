#include "kernel.h"


uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga = (uint16_t* const) vga_ptr;
const uint16_t defaultColor = (COLOR_BLUE << 8) | (COLOR_LIGHT_GREY << 12);
uint16_t currentColor = defaultColor;

void Reset(){
    line = 0;
    column = 0;
    currentColor = defaultColor;

    for(uint16_t y = 0; y < height; y++){
        for(uint16_t x = 0; x < width; x++){
            vga[y * width + x] = ' ' | defaultColor;
        } 
    }
    set_cursor_pos(0, 0);  // Réinitialise le curseur à la position (0,0)
}

void newline(){
    if(line < height - 2){
        line++;
        column = 0;
    }else{
        scrollup();
        column = 0;
    }
    set_cursor_pos(column, line);  // Met à jour le curseur après newline
}

void scrollup(){

    for(uint16_t y = 1; y < height; y++){
        for(uint16_t x = 0; x < width; x++){
            vga[(y - 1) * width + x] = vga[y * width + x];
        }
    }
    for (uint16_t x = 0; x < width; x++){
        vga[(height - 1) * width + x] = (uint16_t)(' ') | currentColor;
    }
}

void print(const char *s){
    while(*s){
        switch(*s){
            case '\n':
                newline();
                break;
            case '\r':
                column = 0;
                set_cursor_pos(column, line);  // Met à jour le curseur après retour chariot
                break;
            case '\t':
                if(column == width){
                    newline();
                }
                uint16_t tablen = 4 - (column % 4);
                while (tablen != 0){
                    vga[line * width + (column++)] = ' ' | currentColor;
                    tablen--;
                }
                set_cursor_pos(column, line);  // Met à jour le curseur après tab
                break;
            default:
                if (column == width){
                    newline();
                }
                vga[line * width + (column++)] = *s | currentColor;
                set_cursor_pos(column, line);
                break;
        }
        s++;
    }
}