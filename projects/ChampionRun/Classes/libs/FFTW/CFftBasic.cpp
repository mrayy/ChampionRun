#include "CFftBasic.h"

void CFftBasic::setup(int signalSize, fftWindowType windowType) {
	CFft::setup(signalSize, windowType);
	fftCfg = kiss_fftr_alloc(signalSize, 0, NULL, NULL);
	ifftCfg = kiss_fftr_alloc(signalSize, 1, NULL, NULL);
	windowedSignal = new float[signalSize];
	cx_out = new kiss_fft_cpx[binSize];
	cx_in = new kiss_fft_cpx[binSize];
}

CFftBasic::~CFftBasic() {
	kiss_fftr_free(fftCfg);
	kiss_fftr_free(ifftCfg);
	delete [] windowedSignal;
	delete [] cx_out;
	delete [] cx_in;
}

void CFftBasic::executeFft() {
	memcpy(windowedSignal, signal, sizeof(float) * signalSize);
	runWindow(windowedSignal);
	kiss_fftr(fftCfg, windowedSignal, cx_out);
	for(int i = 0; i < binSize; i++) {
		real[i] = cx_out[i].r;
		imag[i] = cx_out[i].i;
	}
	cartesianUpdated = true;
}

void CFftBasic::executeIfft() {
	for(int i = 0; i < binSize; i++) {
		cx_in[i].r = real[i];
		cx_in[i].i = imag[i];
	}
	kiss_fftri(ifftCfg, cx_in, signal);
	runInverseWindow(signal);
	signalUpdated = true;
}
