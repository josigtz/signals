/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Low Pass
Filter model: Butterworth
Filter order: 2
Sampling Frequency: 44 KHz
Cut Frequency: 2.000000 KHz
Coefficents Quantization: 16-bit

Z domain Zeros
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000

Z domain Poles
z = 0.800546 + j -0.165816
z = 0.800546 + j 0.165816
***************************************************************/
#define Ntap 100

#define DCgain 131072

__int16 fir(__int16 NewSample) {
    __int16 FIRCoef[Ntap] = { 
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            1,
            2,
            3,
            4,
            6,
            7,
            9,
           11,
           12,
           13,
           13,
           10,
            6,
           -2,
          -14,
          -32,
          -57,
          -88,
         -128,
         -175,
         -229,
         -288,
         -346,
         -397,
         -429,
         -429,
         -375,
         -240,
           10,
          419,
         1040,
         1934,
         3172,
         4835,
         7006,
         9773,
        13218,
        17410,
        19701,
        17410,
        13218,
         9773,
         7006,
         4835,
         3172,
         1934,
         1040,
          419,
           10,
         -240,
         -375,
         -429,
         -429,
         -397,
         -346,
         -288,
         -229,
         -175,
         -128,
          -88,
          -57,
          -32,
          -14,
           -2,
            6,
           10,
           13,
           13,
           12,
           11,
            9,
            7,
            6,
            4,
            3,
            2,
            1,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
    };

    static __int16 x[Ntap]; //input samples
    __int32 y=0;            //output sample
    int n;

    //shift the old samples
    for(n=Ntap-1; n>0; n--)
       x[n] = x[n-1];

    //Calculate the new output
    x[0] = NewSample;
    for(n=0; n<Ntap; n++)
        y += FIRCoef[n] * x[n];
    
    return y / DCgain;
}
