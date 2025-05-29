
#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>

#define KEYPAD_R1 PORTD.0
#define KEYPAD_R2 PORTD.1
#define KEYPAD_R3 PORTD.2
#define KEYPAD_R4 PORTD.3
#define KEYPAD_C1 PIND.4
#define KEYPAD_C2 PIND.5
#define KEYPAD_C3 PIND.6
#define KEYPAD_C4 PIND.7

#define KEYPAD_NUM0 0
#define KEYPAD_NUM1 1
#define KEYPAD_NUM2 2
#define KEYPAD_NUM3 3
#define KEYPAD_NUM4 4
#define KEYPAD_NUM5 5
#define KEYPAD_NUM6 6
#define KEYPAD_NUM7 7
#define KEYPAD_NUM8 8
#define KEYPAD_NUM9 9
#define KEYPAD_DIV 10
#define KEYPAD_MUL 11
#define KEYPAD_PLS 12
#define KEYPAD_MNS 13
#define KEYPAD_EQU 14
#define KEYPAD_ON 15

unsigned char keypad_scan();

char isop(char x)
{
    if (x >= 10 && x <= 14)
        return 1;
    return 0;
}

void main(void)
{
    unsigned char key_res;
    char c = 1;
    char op = 0;
    int num1 = 0;
    int num2 = 0;
    int ans = 0;
    float numf1;
    float numf2;
    char buf[16];
    DDRC = 0xFF;
    DDRD = 0x0F;
    PORTC = 0x00;

    lcd_init(16);
    lcd_clear();
    

    while (1)
    {
        key_res = keypad_scan();
        if (key_res != 255)
        {
            while (keypad_scan() != 255)
                ;
            delay_ms(20);

            if (key_res == KEYPAD_ON)
            {
                num1=0;
                num2=0;
                c=1;
                op=0;
                lcd_clear();
            }
            else if (key_res == KEYPAD_EQU)
            {
                if (op == KEYPAD_DIV)
                {
                    numf1 = num1;
                    numf2 = num2;
                    sprintf(buf, "=%.10f", numf1 / numf2);
                }
                if (op == KEYPAD_MNS)
                {
                    sprintf(buf, "=%d", num1 - num2);
                }
                if (op == KEYPAD_MUL)
                {
                    sprintf(buf, "=%d", num1 * num2);
                }
                if (op == KEYPAD_PLS)
                {
                    sprintf(buf, "=%d", num1 + num2);
                }
                lcd_puts(buf);
            }
            else if (c == 1)
            {
                if (isop(key_res))
                {
                    op = key_res;
                    c++;
                    if (key_res == KEYPAD_DIV)
                    {
                        lcd_putchar('/');
                    }
                    if (key_res == KEYPAD_MNS)
                    {
                        lcd_putchar('-');
                    }
                    if (key_res == KEYPAD_MUL)
                    {
                        lcd_putchar('*');
                    }
                    if (key_res == KEYPAD_PLS)
                    {
                        lcd_putchar('+');
                    }
                }
                else
                {
                    if (num1*10+key_res>99) continue;
                    num1 *= 10;
                    num1 += key_res;
                    lcd_putchar(key_res + 48);
                }
            }
            else if (c == 2)
            {
                if (num2*10+key_res>99) continue;
                num2 *= 10;
                num2+=key_res;
                lcd_putchar(key_res+48);
            }
        }
    }
}

unsigned char keypad_scan()
{
    unsigned char result = 255;
    KEYPAD_R1 = 1;
    KEYPAD_R2 = 0;
    KEYPAD_R3 = 0;
    KEYPAD_R4 = 0; 
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_NUM7;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM8;
    else if (KEYPAD_C3)
        result = KEYPAD_NUM9;
    else if (KEYPAD_C4)
        result = KEYPAD_DIV;
    KEYPAD_R1 = 0;
    KEYPAD_R2 = 1;
    KEYPAD_R3 = 0;
    KEYPAD_R4 = 0;
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_NUM4;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM5;
    else if (KEYPAD_C3)
        result = KEYPAD_NUM6;
    else if (KEYPAD_C4)
        result = KEYPAD_MUL;

    KEYPAD_R1 = 0;
    KEYPAD_R2 = 0;
    KEYPAD_R3 = 1;
    KEYPAD_R4 = 0; 
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_NUM1;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM2;
    else if (KEYPAD_C3)
        result = KEYPAD_NUM3;
    else if (KEYPAD_C4)
        result = KEYPAD_MNS;


    KEYPAD_R1 = 0;
    KEYPAD_R2 = 0;
    KEYPAD_R3 = 0;
    KEYPAD_R4 = 1; 
    delay_ms(5);
    if (KEYPAD_C1)
        result = KEYPAD_ON;
    else if (KEYPAD_C2)
        result = KEYPAD_NUM0;
    else if (KEYPAD_C3)
        result = KEYPAD_EQU;
    else if (KEYPAD_C4)
        result = KEYPAD_PLS;

    return result;
}