#pragma once

// Uses KISS FFT.
// http://www.openframeworks.cc/forum/viewtopic.php?f=14&t=220&p=804

#include "CFft.h"
#include "kiss_fftr.h"

class CFftBasic : public CFft {
public:
	void setup(int signalSize, fftWindowType windowType);
	~CFftBasic();
protected:
	void executeFft();
	void executeIfft();
private:
	kiss_fftr_cfg fftCfg, ifftCfg;
	float* windowedSignal;
	kiss_fft_cpx* cx_out;
	kiss_fft_cpx* cx_in;
};
