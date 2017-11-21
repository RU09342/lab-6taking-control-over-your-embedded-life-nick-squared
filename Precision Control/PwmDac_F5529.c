#include <msp430.h> 
#include <config.h>


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1SEL|=BIT2;
	P1DIR|=BIT2;
	BTN1INIT;

    //TA0 config
	TA0CCTL0 = CCIE; //Interrupt
    TA0CTL = TASSEL_2 + MC_1; //SMCLK, upmode
    TA0CCR0 =  200;           //Sets to 5 kHz
    TA0CCTL1 = OUTMOD_7;
    TA0CCR1 =100;


	_BIS_SR(GIE+LPM0_bits);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer (void)
{
    /*if(TA0CCR1<=200)
    {
        TA0CCR1++;
    }
    else
    {
        TA0CCR1=0;
    }*/
}

//Testing DC
#pragma vector=PORT2_VECTOR
__interrupt void button (void)
{
    if(TA0CCR1<=200)
    {
        TA0CCR1++;
    }
    else
    {
        TA0CCR1=0;
    }
    BTN1CLR;
}


