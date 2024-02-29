
#include "bsp.h"

void bspInit(void)
{

#ifdef  _USE_ATMEGA128
    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
    // State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P 
    PORTA=(1<<PORTA7) | (1<<PORTA6) | (1<<PORTA5) | (1<<PORTA4) | (1<<PORTA3) | (1<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);

    // Port B initialization
    // Function: Bit7=In Bit6=Out Bit5=In Bit4=Out Bit3=In Bit2=Out Bit1=Out Bit0=Out 
    DDRB=(0<<DDB7) | (1<<DDB6) | (0<<DDB5) | (1<<DDB4) | (0<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
    // State: Bit7=T Bit6=1 Bit5=T Bit4=1 Bit3=T Bit2=1 Bit1=1 Bit0=1 
    PORTB=(0<<PORTB7) | (1<<PORTB6) | (0<<PORTB5) | (1<<PORTB4) | (0<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

    // Port C initialization
    // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=In Bit0=In 
    DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (0<<DDC1) | (0<<DDC0);
    // State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=P Bit0=P 
    PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (1<<PORTC1) | (1<<PORTC0);

    // Port D initialization
    // Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=Out Bit2=In Bit1=Out Bit0=Out 
    DDRD=(0<<DDD7) | (0<<DDD6) | (1<<DDD5) | (0<<DDD4) | (1<<DDD3) | (0<<DDD2) | (1<<DDD1) | (1<<DDD0);
    // State: Bit7=T Bit6=T Bit5=0 Bit4=T Bit3=1 Bit2=T Bit1=1 Bit0=1 
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (1<<PORTD3) | (0<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

    // Port E initialization
    // Function: Bit7=In Bit6=In Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=Out Bit0=In 
    DDRE=(0<<DDE7) | (0<<DDE6) | (1<<DDE5) | (1<<DDE4) | (0<<DDE3) | (0<<DDE2) | (1<<DDE1) | (0<<DDE0);
    // State: Bit7=T Bit6=T Bit5=0 Bit4=0 Bit3=T Bit2=T Bit1=1 Bit0=T 
    PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (1<<PORTE1) | (0<<PORTE0);

    // Port F initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);

    // Port G initialization
    // Function: Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRG=(0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
    // State: Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTG=(0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (0<<PORTG1) | (0<<PORTG0);

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: 250.000 kHz
    // Mode: CTC top=OCR0
    // OC0 output: Disconnected
    // Timer Period: 1 ms
    ASSR=0<<AS0;
    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (0<<CS00);
    TCNT0=0x00;
    OCR0=0xF9;

    // USART0 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 9600
    UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
    UCSR0B=(1<<RXCIE0) | (1<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
    UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
    UBRR0H=0x00;
    UBRR0L=0x19;

    // USART1 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART1 Receiver: On
    // USART1 Transmitter: On
    // USART1 Mode: Asynchronous
    // USART1 Baud Rate: 9600
    UCSR1A=(0<<RXC1) | (0<<TXC1) | (0<<UDRE1) | (0<<FE1) | (0<<DOR1) | (0<<UPE1) | (0<<U2X1) | (0<<MPCM1);
    UCSR1B=(1<<RXCIE1) | (1<<TXCIE1) | (0<<UDRIE1) | (1<<RXEN1) | (1<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
    UCSR1C=(0<<UMSEL1) | (0<<UPM11) | (0<<UPM10) | (0<<USBS1) | (1<<UCSZ11) | (1<<UCSZ10) | (0<<UCPOL1);
    UBRR1H=0x00;
    UBRR1L=0x19;


  // Timer(s)/Counter(s) Interrupt(s) initialization
  // Timer(s)/Counter(s) Interrupt(s) initialization
  TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
  ETIMSK=(0<<TICIE3) | (0<<OCIE3A) | (0<<OCIE3B) | (0<<TOIE3) | (0<<OCIE3C) | (0<<OCIE1C);
  //TIMSK=0x02;
  //ETIMSK=0x00;

  // Analog Comparator initialization
  // Analog Comparator: Off
  // Analog Comparator Input Capture by Timer/Counter 1: Off
  ACSR=0x80;
  SFIOR=0x00;

// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 250.000 kHz
// SPI Clock Phase: Cycle Half
// SPI Clock Polarity: Low
// SPI Data Order: MSB First
SPCR=0x52;
SPSR=0x00;
#endif

}
 