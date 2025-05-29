#include <mega32.h>
#include <alcd.h>
#include <stdio.h>

unsigned int lim[4]={9,59,59,23},time[5]={0,0,58,23,0};
char  ans[20];
char header[16]="   LCD  CLOCK\n"   ;
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
char i=0;
lcd_clear();
lcd_puts(header);
time[0]++;
for (i=0;i<4;i++){
    if (time[i]>lim[i]){
        time[i]=0;
        time[i+1]++;
    }
}
sprintf(ans, "   %02d:%02d:%02d:%d", time[3], time[2], time[1], time[0]);
lcd_puts(ans);
}

void main(void)
{

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
TCNT1H=0xCF;
TCNT1L=0x2C;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x30;
OCR1AL=0xD3;
OCR1BH=0x00;
OCR1BL=0x00;
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

#asm("sei")
lcd_init(16);

while (1)
      {
      }
}
