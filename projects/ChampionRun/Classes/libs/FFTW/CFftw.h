#pragma once

#include "CFft.h"
#include "fftw3.h"

class CFftw : public CFft{
public:
	CFftw();
	void setup(int signalSize, fftWindowType windowType);
	~CFftw();
protected:
	void executeFft();
	void executeIfft();
private:
	float *fftIn, *fftOut, *ifftIn, *ifftOut;
	fftwf_plan fftPlan, ifftPlan;
};
