
#include "bsp.h"
 
void bspInit(void)
{
    /// Input/Output Ports initialization
    // Port A initialization
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
    PORTA=0x00;
    DDRA=0x00;
    /*
    // Port B initialization
    // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
    // State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
    PORTB=0x00;
    DDRB=0xFF;
    */
    // Port B initialization
    // Func7=In Func6=Out Func5=In Func4=Out Func3=In Func2=Out Func1=Out Func0=Out 
    // State7=T State6=1 State5=T State4=1 State3=T State2=1 State1=1 State0=1 
    PORTB=0x57;
    DDRB=0x57;
    // Port C initialization
    // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=In Func0=In 
    // State7=1 State6=1 State5=0 State4=0 State3=1 State2=1 State1=T State0=T 
    PORTC=0xCC;
    DDRC=0xFC;
    //
    //
    // Port D initialization
    // Func7=Out Func6=Out Func5=Out Func4=In Func3=Out Func2=In Func1=In Func0=In
    // State7=1 State6=1 State5=1 State4=T State3=0 State2=T State1=T State0=T
    PORTD=0xE0;
    DDRD=0xE8;

    // Port E initialization
    // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=In Func1=Out Func0=In 
    // State7=T State6=T State5=0 State4=0 State3=0 State2=T State1=0 State0=T 
    PORTE=0x00;
    DDRE=0x3A;

    // Port F initialization
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
    PORTF=0x00;
    DDRF=0x00;

    // Port G initialization
    // Func4=In Func3=In Func2=In Func1=In Func0=In
    // State4=T State3=T State2=T State1=T State0=T
    PORTG=0x00;
    DDRG=0x00;
    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: 250.000 kHz
    // Mode: Normal top=FFh
    // OC0 output: Disconnected
    ASSR=0x00;
    TCCR0=0x0C;
    TCNT0=0x00;
    OCR0=0xfa;
    //
    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: 250.000 kHz
    // Mode: CTC top=OCR1A
    // OC1A output: Discon.
    // OC1B output: Discon.
    // OC1C output: Discon.
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer1 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: On
    // Compare B Match Interrupt: Off
    // Compare C Match Interrupt: Off
    TCCR1A=0x00;
    TCCR1B=0x0B;
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x12;
    OCR1AL=0x34;
    OCR1BH=0x00;
    OCR1BL=0x00;
    OCR1CH=0x00;
    OCR1CL=0x00;
    //
    // Timer/Counter 2 initialization
    // Clock source: System Clock
    // Clock value: 250.000 kHz
    // Mode: CTC top=OCR2
    // OC2 output: Disconnected
    TCCR2=0x0B;
    TCNT2=0x00;
    OCR2=0xFA;

    // Timer/Counter 3 initialization
    // Clock source: System Clock
    // Clock value: 62.500 kHz
    // Mode: CTC top=OCR3A
    // OC3A output: Discon.
    // OC3B output: Discon.
    // OC3C output: Discon.
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer3 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: On
    // Compare B Match Interrupt: Off
    // Compare C Match Interrupt: Off
    TCCR3A=0x00;
    TCCR3B=0x00;
    TCNT3H=0x00;
    TCNT3L=0x00;
    ICR3H=0x00;
    ICR3L=0x00;
    OCR3AH=0x00;
    OCR3AL=0x00;
    OCR3BH=0x00;
    OCR3BL=0x00;
    OCR3CH=0x00;
    OCR3CL=0x00;

    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    // INT2: Off
    // INT3: Off
    // INT4: Off
    // INT5: Off
    // INT6: Off
    // INT7: Off
    EICRA=0x00;
    EICRB=0x00;
    EIMSK=0x00;

    // Timer(s)/Counter(s) Interrupt(s) initialization
    // TIMSK=0x80; // TIMER 2 INT
    TIMSK=0x82;
    // ETIMSK=0x10 ;  // TIMER 3 match A INT
    ETIMSK=0x00;
    //
    // USART0 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 19200
    UCSR0A=0x00;
    UCSR0B=0xD8;
    UCSR0C=0x06;
    UBRR0H=0x00;
    UBRR0L=0x33;

    // USART1 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART1 Receiver: On
    // USART1 Transmitter: On
    // USART1 Mode: Asynchronous
    // USART1 Baud Rate: 19200
    UCSR1A=0x00;
    UCSR1B=0xD8;
    UCSR1C=0x06;
    UBRR1H=0x00;
    UBRR1L=0x33;
    //
    // Analog Comparator initialization
    // Analog Comparator: Off
    // Analog Comparator Input Capture by Timer/Counter 1: Off
    ACSR=0x80;
    SFIOR=0x00;
    // SPI initialization
    // SPI Type: Master
    // SPI Clock Rate: 4000.000 kHz
    // SPI Clock Phase: Cycle Half
    // SPI Clock Polarity: Low
    // SPI Data Order: MSB First
    //SPCR=0x50;
    //SPSR=0x00;
 
 
}
 