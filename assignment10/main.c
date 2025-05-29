#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>

signed char a = 0;

interrupt[EXT_INT0] void ext_int0_isr(void) {
    if (PORTC.3 == 0) a++;
    else a += 10;
}

interrupt[EXT_INT1] void ext_int1_isr(void) {
    if (PORTC.3 == 0) a--;
    else a -= 10;
}

interrupt[EXT_INT2] void ext_int2_isr(void) {
    PORTC ^= (1 << 3);
}

void main(void) {
    char str[6];
    DDRC |= (1 << 3);

    GICR |= (1 << INT1) | (1 << INT0) | (1 << INT2);
    MCUCR = (1 << ISC11) | (1 << ISC01);
    MCUCSR = 0;
    GIFR = (1 << INTF1) | (1 << INTF0) | (1 << INTF2);

    ACSR = (1 << ACD);
    lcd_init(16);

    #asm("sei")

    while (1) {
        lcd_gotoxy(0, 0);
        itoa(a, str);
        lcd_puts(str);
        lcd_putchar(' ');
        lcd_putchar(' ');
        delay_ms(50);
    }
}
