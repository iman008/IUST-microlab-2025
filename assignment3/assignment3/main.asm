; Iman Ghader 401442355

.include "m32def.inc"

.ORG 0
    rjmp BEGIN

.ORG OC1AADDR
    rjmp ROUTINE

.ORG OC0ADDR
    rjmp CHANGESEG

BEGIN:
    LDI     R16,HIGH(RAMEND)
    OUT     SPH,R16
    LDI     R16,LOW(RAMEND)
    OUT     SPL,R16
    
    LDI     R16,0xFF
    OUT     DDRB,R16
    OUT     DDRC,R16
    OUT     DDRD,R16
    OUT     PORTA,R16
    
    ; Initialize TIMER1
    LDI     R16,HIGH(31250-1)
    OUT     OCR1AH,R16
    LDI     R16,LOW(31250-1)
    OUT     OCR1AL,R16
    LDI     R16,0x00
    OUT     TCCR1A,R16
    LDI     R16,0x0C
    OUT     TCCR1B,R16
    
    ; Init TIMER0
    LDI     R16,0x0C
    OUT     TCCR0,R16
    LDI     R16,0x00
    OUT     TCNT0,R16
    LDI     R16,0x63
    OUT     OCR0,R16

    LDI     R16,0x12
    OUT     TIMSK,R16
    SEI

    LDI     R20,0
    LDI     R26,0b11111110
    LDI     R16,0x01
	LDI		R27,0x00
	
L1:

    RJMP    L1

ROUTINE:
	MOV R18,R16
	COM R18
    OUT PORTB, R18
    IN R17, PINA
    CPI R17, 1
    BRNE INCREMENT
    RJMP DECREMENT
LL2:

    CPI R27, 0
    BREQ MOVE_FORWARD
    RJMP MOVE_BACKWARD

MOVE_FORWARD:
    LSL R16         
    CPI R16, 0b10000000
    BRNE ROUTINE_DONE
    LDI R16, 0b10000000  
    LDI R27, 1          
    RJMP ROUTINE_DONE

MOVE_BACKWARD:
    LSR R16         
    CPI R16, 0b00000001
    BRNE ROUTINE_DONE
    LDI R16, 0b00000001  
    LDI R27, 0        

ROUTINE_DONE:
    RETI






INCREMENT:
    INC R21
    CPI R21, 10
    BRNE INCREMENT_DONE
    LDI R21, 0
    INC R22
    CPI R22, 10
    BRNE INCREMENT_DONE
    LDI R22, 0
    INC R23
    CPI R23, 10
    BRNE INCREMENT_DONE
    LDI R23, 0
    INC R24
    CPI R24, 10
    BRNE INCREMENT_DONE
    LDI R24, 0

INCREMENT_DONE:
    RJMP LL2

DECREMENT:
    DEC R21
    CPI R21, 255
    BRNE DONE
    LDI R21, 9
    DEC R22
    CPI R22, 255
    BRNE DONE
    LDI R22, 9
    DEC R23
    CPI R23, 255
    BRNE DONE
    LDI R23, 9
    DEC R24
    CPI R24, 255
    BRNE DONE
    LDI R24, 9

DONE:
    RJMP LL2



CHANGESEG: 
    CPI     R26,0b11111110
    BREQ    LOAD_R21

    CPI     R26,0b11111101
    BREQ    LOAD_R22

    CPI     R26,0b11111011
    BREQ    LOAD_R23

    CPI     R26,0b11110111
    BREQ    LOAD_R24

    RJMP    SHOW 

LOAD_R21:
    MOV     R25,R24
    RJMP    SHOW

LOAD_R22:
    MOV     R25,R23
    RJMP    SHOW

LOAD_R23:
    MOV     R25,R22
    RJMP    SHOW

LOAD_R24:
    MOV     R25,R21
    RJMP    SHOW

SHOW:
    OUT     PORTD,R26
    LSL     R26
	INC		R26
    CPI     R26,0b11101111
    BRNE    D0
    LDI     R26,0b11111110 

D0:    
    CPI     R25,0
    BRNE    D1
    LDI     R19,0b00111111        
    OUT     PORTC,R19
    RETI

D1:    
    CPI     R25,1
    BRNE    D2
    LDI     R19,0b00000110        
    OUT     PORTC,R19
    RETI

D2:    
    CPI     R25,2
    BRNE    D3
    LDI     R19,0b01011011        
    OUT     PORTC,R19
    RETI

D3:    
    CPI     R25,3
    BRNE    D4
    LDI     R19,0b01001111        
    OUT     PORTC,R19
    RETI

D4:    
    CPI     R25,4    
    BRNE    D5
    LDI     R19,0b01100110        
    OUT     PORTC,R19
    RETI

D5:    
    CPI     R25,5
    BRNE    D6
    LDI     R19,0b01101101        
    OUT     PORTC,R19
    RETI

D6:    
    CPI     R25,6
    BRNE    D7    
    LDI     R19,0b01111101        
    OUT     PORTC,R19
    RETI

D7:    
    CPI     R25,7
    BRNE    D8
    LDI     R19,0b00000111        
    OUT     PORTC,R19
    RETI

D8:    
    CPI     R25,8
    BRNE    D9
    LDI     R19,0b01111111        
    OUT     PORTC,R19
    RETI

D9:    
    LDI     R19,0b01101111        
    OUT     PORTC,R19
    RETI
