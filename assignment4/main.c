#include <mega32.h>
#include <delay.h>

int whichseg = 0;
int cnt=0;
char segs[6] = {2,3,5,8,0,0};
int even=0;
flash unsigned int mp[6] = {0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111};
flash unsigned inttoseg[10] = {0b00111111, 0b00000110, 0b01011011,0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};


interrupt[TIM0_OVF] void timer0_ovf_isr(void)
{
      
      TCNT0 = 0x06;
      
      PORTD=mp[whichseg];      
      if (even && whichseg%2)
      PORTC=inttoseg[segs[whichseg]]|0x80;  
      else       PORTC=inttoseg[segs[whichseg]];
      
      whichseg++;
      whichseg%=6;
     
      
}

interrupt[TIM1_COMPA] void timer1_compa_isr(void)
{
    int carry = 0;
        int tmp0=segs[0],tmp1=segs[1];

    
    
    segs[5]++;
    if (segs[5] == 10) {
        segs[5] = 0;
        carry = 1;  
    }
    even=(segs[5]+1)%2;
    
    if (carry) {
        segs[4]++;
        carry = 0;
        if (segs[4] == 6) {  
            segs[4] = 0;
            carry = 1;  
        }
    }

    
    if (carry) {
        segs[3]++;
        carry = 0;
        if (segs[3] == 10) {  
            segs[3] = 0;
            carry = 1;  
        }
    }

    
    if (carry) {
        segs[2]++;
        carry = 0;
        if (segs[2] == 6) {  
            segs[2] = 0;
            carry = 1;  
        }
    }
    
    if (carry) {
        tmp1++;
        carry = 0;

        if (tmp1 == 10) {  
            tmp1 = 0;
            carry = 1;  
        }
    }
    if (tmp0==2 && tmp1==4){
    tmp0=0;
    tmp1=0;
    }
    
    if (carry) {
        tmp0++;
        carry = 0;
        if(tmp0 == 3) {  
            tmp0 = 0;
        }
    }
    if (segs[0]==2 && segs[1]==4){
    tmp0=0;
    tmp1=0;
    }             
    segs[0]=tmp0;
    segs[1]=tmp1;
    
    
}

void main(void)
{
      
      DDRC = (1 << DDC7) | (1 << DDC6) | (1 << DDC5) | (1 << DDC4) | (1 << DDC3) | (1 << DDC2) | (1 << DDC1) | (1 << DDC0);
      
      PORTC = (0 << PORTC7) | (0 << PORTC6) | (0 << PORTC5) | (0 << PORTC4) | (0 << PORTC3) | (0 << PORTC2) | (0 << PORTC1) | (0 << PORTC0);

      
      
      DDRD = (1 << DDD7) | (1 << DDD6) | (1 << DDD5) | (1 << DDD4) | (1 << DDD3) | (1 << DDD2) | (1 << DDD1) | (1 << DDD0);
      
      PORTD = (0 << PORTD7) | (0 << PORTD6) | (0 << PORTD5) | (0 << PORTD4) | (0 << PORTD3) | (0 << PORTD2) | (0 << PORTD1) | (0 << PORTD0);

      
      TCCR0 = (0 << WGM00) | (0 << COM01) | (0 << COM00) | (0 << WGM01) | (0 << CS02) | (1 << CS01) | (1 << CS00);
      TCNT0 = 0x06;
      OCR0 = 0x00;


      
      TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (0 << WGM11) | (0 << WGM10);
      TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);
      TCNT1H = 0x85;
      TCNT1L = 0xEE;
      ICR1H = 0x00;
      ICR1L = 0x00;
      OCR1AH = 0x7A;
      OCR1AL = 0x11;
      OCR1BH = 0x00;
      OCR1BL = 0x00;

      
      
      
      
      
      TCCR2 = (0 << PWM2) | (0 << COM21) | (0 << COM20) | (0 << CTC2) | (0 << CS22) | (0 << CS21) | (0 << CS20);
      TCNT2 = 0x00;
      OCR2 = 0x00;

      
      TIMSK = (0 << OCIE2) | (0 << TOIE2) | (0 << TICIE1) | (1 << OCIE1A) | (0 << OCIE1B) | (0 << TOIE1) | (0 << OCIE0) | (1 << TOIE0);



#asm("sei")

      while (1)
      {
      }
}
