#include <mega32.h>
#include <glcd.h>
#include <font5x7.h>
#include <delay.h>
unsigned char coords[][2] = {
        {40, 60},
        {80, 60},
        {80, 40},
        {90, 40},
        {60, 10},
        {50, 20},
        {50, 16},
        {52, 16},
        {52, 12},
        {42, 12},
        {42, 16},
        {44, 16},
        {44, 26},
        {30, 40},
        {40, 40},
        {40, 60}
    };
void main(void)
{   int i;
    unsigned char x = 128 / 2;
    unsigned char y = 64 / 2;
    char dx = 1;
    char dy = 1;

    GLCDINIT_t glcd_init_data;
    ACSR = (1 << ACD);

    glcd_init_data.font = font5x7;
    glcd_init_data.readxmem = NULL;
    glcd_init_data.writexmem = NULL;
    glcd_init(&glcd_init_data);

    glcd_clear();
    glcd_setlinestyle(1, GLCD_LINE_SOLID);

    

    
    for (i = 0; i < 15; i++) {
        glcd_line(coords[i][0], coords[i][1], coords[i+1][0], coords[i+1][1]);
        delay_ms(500);
    }

    while (1) {
        glcd_clear();
        glcd_fillcircle(x, y, 4);
        delay_ms(29);

        x += dx;
        y += dy;

        if (x <= 4 || x >= 128 - 4)
            dx = -dx;
        if (y <= 4 || y >= 64 - 4)
            dy = -dy;
    }
}
