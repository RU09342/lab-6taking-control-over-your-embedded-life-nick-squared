#include <msp430.h> 

signed int dir=BIT0;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//Configure GPIO pins
	P3SEL|=0x00;
	P3DIR|=0xFF;
	P3OUT|=BIT1+BIT0;

    //TA0 config
    TA0CCTL0 = CCIE;             // interrupt
    TA0CTL = TASSEL_2 + MC_1; //SMCLK, upmode
    TA0CCR0 =  100;                //Sets to 10 kHz


	_BIS_SR(LPM0_bits+GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer (void)
{

    P3OUT += dir;
    if(P3OUT == 0X7D || P3OUT ==0x02)
    {
        dir=-dir;
    }
    /*
    else if(P3OUT < 0x7E && P3OUT > 0x00)
    {
    P3OUT += dir;
    }
    */

}




