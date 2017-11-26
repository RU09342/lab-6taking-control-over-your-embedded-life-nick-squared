# Lab 6: Precision Control
Nick Squared

## PWM

### Overview

A 5kHz 50% duty cycle PWM signal is fed into an invertng op amp with a low pass filter with approzimately 1kHz cut off. 

### Diagrams

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/PWM_Schematic2.png" width="300"/>
PWM Schematic
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/PWM_Circuit.jpg" width="300"/>
PWM circuit

### Results 
The PWM with 50% duty cycle caused an output of a DC signal with an offset of 1.66V
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/PWM%20DC%2050%25.png" width="300"/>
PWM Output Wave Form

when an AC PWM wave is sent through the circuit the output appears to be a triangle wave with slopped tops. The FFT results of the wave show the slowly decreasing harmonic frequencies that slos make up the triangle wave.
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/PWM%20AC.png" width="300"/>
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/PWM%20FFT.png" width="300"/>
PWM Output FFT



### Loading Effects

By adding various sizes of loads to the PWM circuit the overall output of the circuit is affected. When a 100ohm load is placed at the output of the Op Amp a DC voltage of -1.83V is measured. The voltage is negative due to the inverting Op Amp set up and the filter forces only the DC signal of the input signal to be passed through. Since the load is so small compared to the rest of the circuit, it causes the output voltage to be increaded by 0.18V. Then when a 1kohm load is connected to the output of the circuitm, the output signal acts like an integrated sine wave. The steep portions of the input signal are cut off and replaced with gradulaly increasing and decreasing slopes. This shows that the greater the load put on the circuit the less the output wave form will look like the input signal.

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/PWM%20100%20ohm.png" width="300"/>
100 ohm load on the output of the op amp.

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/PWM%201k%20ohm.png" width="300"/>
1kohm load on the output of the op amp.

### Bill of Materials

|Part     |Manufacturer Part #|Brand|Value|Package      |Unit Price ($)|Quantity|Website|
|------------|-------------------|-----|-------------------|-------------------|-------------|--------------|----|
| Dual Operational Amplifier | TL072 | Texas Instruments | N/A | PDIP | 0.78 | 1 | [Link](http://www.ti.com/product/TL072/samplebuy)|
|330kohm Resistor | CF14JT330K | Stackpole Electronics Inc | 330kohm | Through hole | 0.00475 | 2 | [Link](https://www.digikey.com/product-detail/en/stackpole-electronics-inc/CF14JT330K/CF14JT330KTR-ND/1741401)
|470pF Capacitor | D471K20Y5PH63L6R | Vishay | 470pF | Ceramic | 0.20 | 1 | [Link](https://www.mouser.com/ProductDetail/Vishay/D471K20Y5PH63L6R/?qs=wEmTtUuRSe77jhSuFgvudw%3D%3D&gclid=Cj0KCQiA6enQBRDUARIsAGs1YQgNIkd8Bdq7dIL9qU-A3CiCrlsrvvJfKe8bxjE8Wf_IcY-deiaxBgAaAowJEALw_wcB)|

## R2R DAC

### Overview
An R2R DAC consists of a series resistors that takes in a certian number of Digital bits and converts them to an Analog voltage. A total of 8 bits are used to increment from 0 to 255, then decrement from 255 to 0.

### Diagrams

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/R2R_Schematic.PNG" width="400"/>
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/R2R%20DAC.jpg" width="300"/>

### Results

As seen below a 10kHz signal is used to create a triangle wave. Every 0.01ms the timer interrupts causing the digital number to increment by one, thus causing the signal to slightly increase in voltage. When the signal is zoomed in each individual increment can be seen. So the signal is basically a unit step, however since it steps so fast it appears as a triangle wave form. The voltage of the wave form is 1.64V which is approximately equivalent to a PWM signal with 50% duty cycle.

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/R2R.png" width="300">
R2R Triangle Wave
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/R2R-zoom.png" width="300">
R2R Triangle Wave Zoomed In

The signal not only looks like a triangle wave form, but it also has similair FFT Harmonics as a true triangle wave.
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/R2R%20FFT.png" width="300">
R2R Triangle Wave with FFT

### Loading Effects

Much like when the PWM signal has a load applied to the output of the circuit, it causes changes to the signal. For example, when a 100ohm resister is placed on the output of the circuit, the signal had an applitude of 157mV and an increase in output noise. As for when 1kohm is added as a load the amplitude increases to 548mv with much less noise.

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/R2R%20100%20ohm.png" width="300"/>
100 ohm load on the output of the R2R ladder.
<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/R2R%201k%20ohm.png" width="300"/>
1kohm load on the output of the R2R ladder.

### Bill of Materials

|Part     |Manufacturer Part #|Brand|Value|Package      |Unit Price ($)|Quantity|Website|
|------------|-------------------|-----|-------------------|-------------------|-------------|--------------|----|
| 1kohm Resistor | CF14JT1K00 | Stackpole Electronics Inc | 1kohm | Through hole | 0.00475 | 7 | [Link](https://www.digikey.com/product-detail/en/stackpole-electronics-inc/CF14JT1K00/CF14JT1K00TR-ND/1741314)|
| 2kohm Resistor | CF14JT2K00 | Stackpole Electronics Inc | 2kohm | Through hole | 0.00475 | 9 | [Link](https://www.digikey.com/product-detail/en/stackpole-electronics-inc/CF14JT2K00/CF14JT2K00TR-ND/1741368)|


