#include <msp430.h> 
#include <config.h>

float tempC;
unsigned int tempF;
unsigned int pwm;
unsigned int buf;
unsigned int adc;

void UARTinit();

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //Disables high impedence mode

    P1SEL1 |= BIT3; // Configure P1.3 for ADC and 1.2 for TA1.1
    P1SEL0 |= BIT2+BIT3;
    P1DIR  |= BIT2;

    LED1INIT;
    LED2INIT;
    LED2OFF;
    LED1OFF;

    UARTinit();

    //TA1 config
    //TA1CCTL0 = CCIE; //Interrupt
    TA1CTL = TASSEL_2 + MC_1; //SMCLK, upmode
    TA1CCR0 =  400; //Sets to 25 kHz
    TA1CCTL1 = OUTMOD_3;
    TA1CCR1 = 300;

    //TB0 config
    TB0CCTL0 = CCIE; //Interrupt
    TB0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/8, upmode
    TB0CCR0 =  62500; //Sets to 2 Hz
    TB0EX0 = TBIDEX_7;

    //ADC config
    ADC12CTL0 &= ~ADC12ENC;              // Disable ADC12
    while(REFCTL0 & REFGENBUSY);         //Wait for reference generator
    REFCTL0=REFON + REFVSEL_2;           //Use a reference voltage of 2.5V
    while(!(REFCTL0 & REFGENRDY));       //Wait for reference generator
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;   // Sampling time, S&H=16, ADC12 on
    ADC12CTL1 = ADC12SHP;                // Use sampling timer, ADC12SC conversion start, clock=OSC
    ADC12CTL2 |= ADC12RES_2;             // 12-bit conversion results
    ADC12MCTL0|= ADC12INCH_3;           // ADC input select
    ADC12IER0 |= ADC12IE0;               // Enable ADC conv complete interrupt
    ADC12CTL0 |= ADC12ENC;               //Enable conversion

    _BIS_SR(LPM0_bits+GIE);
}

//ADC12 interrupt
#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void)
{
    adc=ADC12MEM0;
    LED1SWITCH;
    //ADC12IFGR0=0; //Reset all Flags, as a precaution
}

//UART interrupt
#pragma vector=USCI_A0_VECTOR
__interrupt void uart(void)
{
    //goalTemp=UCA0RXBUF;
    //Math to turn goalTemp into pwm
    buf=UCA0RXBUF;
   /* if(buf>72)
    {
        pwm= 100;
    }
    if(buf>=72 && buf <=78)
    {
        pwm= (82-buf)*10;
    }
    if(buf>78 && buf<=80)
    {
        pwm=40;
    }
    if(buf==81)
    {
        pwm=30;
    }
    if(buf==82)
    {
        pwm=20;
    }
    if(buf==83)
    {
        pwm=15;
    }
    if(buf>=81)
    {
        pwm=10;
    }
    */
    TA1CCR1=buf*4;
    while(!(UCA0IFG&UCTXIFG));
    UCA0TXBUF=buf*4;

}
//Timer Interrupt
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer1(void)
{
    ADC12CTL0 |= ADC12SC;//Start conversion
    tempC=adc*.08;
    tempF=9*tempC/5+32;
    while(!(UCA0IFG&UCTXIFG));
    UCA0TXBUF=tempF;
}

void UARTinit()
{

    // Configure GPIO
    P2SEL0 &= ~(BIT0 | BIT1);
    P2SEL1 |= BIT0 | BIT1;                  // USCI_A0 UART operation

    // Startup clock system with max DCO setting ~8MHz
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_3 | DCORSEL;           // Set DCO to 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;   // Set all dividers
    CSCTL0_H = 0;                           // Lock CS registers

    // Configure USCI_A0 for UART mode
    UCA0CTLW0 = UCSWRST;                    // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;             // CLK = SMCLK
    UCA0BRW = 52;                           // 8000000/16/9600
    UCA0MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
    UCA0CTLW0 &= ~UCSWRST;                  // Initialize eUSCI
    UCA0IE |= UCRXIE;               // Enable USCI_A0 RX/TX interrupt
}
