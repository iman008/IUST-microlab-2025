#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

#define ADC_VREF_TYPE ((0 << REFS1) | (1 << REFS0) | (0 << ADLAR))

unsigned int read_adc(unsigned char adc_input)
{
    ADMUX = adc_input | ADC_VREF_TYPE;
    delay_us(10);
    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADIF)) == 0);
    ADCSRA |= (1 << ADIF);
    return ADCW;
}

void main(void)
{
    char ans[16];
    int temp;

    ADMUX = ADC_VREF_TYPE;
    ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);

    lcd_init(16);

    lcd_clear();
    lcd_gotoxy(2, 0);
    lcd_puts("LM35 Output");
    while (1)
    {
        temp = (read_adc(0) *0.48828125+0.5);

        lcd_gotoxy(0, 1);
        sprintf(ans, "Temp: %3d C  ", temp);
        lcd_puts(ans);

        delay_ms(10);
    }
}
