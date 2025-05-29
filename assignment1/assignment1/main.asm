;iman ghader 401442355

.include "m32def.inc"
		LDI R16, HIGH(RAMEND)
		out SPH, R16
		ldi R16 , LOW(RAMEND)
		out SPL,R16
		LDI		R16,0xFF
		OUT		DDRB,R16
		LDI R17,0x00
		OUT DDRA,R17
START:
LDI R19,8
LDI R16,0x01
BEGIN:
	out PORTB,R16
	call DELAY
	lsl R16
	ldi R17, 0x01
	ADD R16,R17
	dec R19
	brne BEGIN
	jmp START2
START2:
BEGIN2:
	out PORTB,R16
	call DELAY
	lsl R16
	brne BEGIN2
	jmp START



DELAY:
	IN R20 ,PINA
D1:
			LDI R21,0xFF
			D2:
				LDI R22,0x0F
				D3:
						dec R22
						brne D3
				dec R21
				brne D2
		dec R20
		brne D1
ret