
#include <mega32.h>
#include <delay.h>
#include <stdio.h>
#include <alcd.h>
unsigned char i;
void main(void)
{
    unsigned char a;
    UCSRA = 0x00;
    UCSRB = 0x18;
    UCSRC = 0x86;
    UBRRH = 0x00;
    UBRRL = 0x33;
    lcd_init(16);
    lcd_clear();
    while (1)
    {
        puts("> ");
        a = getchar();
        putchar(a);
        puts("\n\r");
        if (a=='C') lcd_clear();
        if (a=='N') puts("\n\rIman Ghader\n\r");
        if (a=='c') for (i=0;i<24;i++) puts("\n\r");
        if (a=='M') {
            lcd_clear();
            lcd_puts("Iman Ghader");
        }
    }
}
