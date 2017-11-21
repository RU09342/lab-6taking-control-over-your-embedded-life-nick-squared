#include <msp430.h> 
#include <config.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	P2SEL |= BIT0;//TA1.0 initialize
	P2DIR |= BIT0;

    //TA0 config
    TA1CCTL0 = OUTMOD_4;             // toggle
    TA1CTL = TASSEL_2 + ID_3 + MC_1; //SMCLK/8, upmode
    TA1CCR0 =  62500;                //Sets to 2 Hz


	_BIS_SR(LPM0_bits+GIE);
}
