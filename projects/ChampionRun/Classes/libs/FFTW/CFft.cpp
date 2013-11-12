#include "CFft.h"

#include "CFftBasic.h"

#ifdef ALLOW_FFTW
	#include "CFftw.h"
#endif

#define PI 3.141592653589793
#define TWO_PI 6.28318530717959

int Clamp(int x,int a,int b)
{
    return (x<a? a: (x>b? b: x));
}

float MapValue(float v, float a, float b, float x, float y)
{
    return ((v-a)/(b-a))*(y-x)+x;
}

CFft* CFft::create(int signalSize, fftWindowType windowType, fftImplementation implementation) {
	CFft* fft;
	if(implementation == OF_FFT_BASIC) {
		fft = new CFftBasic();
	} else if(implementation == OF_FFT_FFTW) {
		#ifdef ALLOW_FFTW
			fft = new CFftw();
		#else
			//ofLog(OF_LOG_FATAL_ERROR, "You need to add #define ALLOW_FFTW");
		#endif
	}
	fft->setup(signalSize, windowType);
	return fft;
}

void CFft::setup(int signalSize, fftWindowType windowType) {
	this->signalSize = signalSize;
	this->binSize = (signalSize / 2) + 1;

	signalNormalized = true;
	signal = new float[signalSize];

	cartesianUpdated = true;
	cartesianNormalized = true;
	real = new float[binSize];
	imag = new float[binSize];

	polarUpdated = true;
	polarNormalized = true;
	amplitude = new float[binSize];
	phase = new float[binSize];

	clear();

	window = new float[signalSize];
	inverseWindow = new float[signalSize];
	setWindowType(windowType);
}

int CFft::getBinSize() {
	return binSize;
}

int CFft::getSignalSize() {
	return signalSize;
}

void CFft::setWindowType(fftWindowType windowType) {
	this->windowType = windowType;
	if(windowType == OF_FFT_WINDOW_RECTANGULAR) {
		for(int i = 0; i < signalSize; i++)
			window[i] = 1; // only used for windowSum
	} else if(windowType == OF_FFT_WINDOW_BARTLETT) {
		int half = signalSize / 2;
		for (int i = 0; i < half; i++) {
			window[i] = ((float) i / half);
			window[i + half] = (1 - ((float) i / half));
		}
	} else if(windowType == OF_FFT_WINDOW_HANN) {
		for(int i = 0; i < signalSize; i++)
			window[i] = .5 * (1 - cos((TWO_PI * i) / (signalSize - 1)));
	} else if(windowType == OF_FFT_WINDOW_HAMMING) {
		for(int i = 0; i < signalSize; i++)
			window[i] = .54 - .46 * cos((TWO_PI * i) / (signalSize - 1));
	} else if(windowType == OF_FFT_WINDOW_SINE) {
		for(int i = 0; i < signalSize; i++)
			window[i] = sin((PI * i) / (signalSize - 1));
	}

	windowSum = 0;
	for(int i = 0; i < signalSize; i++)
		windowSum += window[i];

	for(int i = 0; i < signalSize; i++)
		inverseWindow[i] = 1. / window[i];
}

CFft::~CFft() {
	delete [] signal;
	delete [] real;
	delete [] imag;
	delete [] amplitude;
	delete [] phase;
	delete [] window;
	delete [] inverseWindow;
}

void CFft::clear() {
	memset(signal, 0, sizeof(float) * signalSize);
	memset(real, 0, sizeof(float) * binSize);
	memset(imag, 0, sizeof(float) * binSize);
	memset(amplitude, 0, sizeof(float) * binSize);
	memset(phase, 0, sizeof(float) * binSize);
}

void CFft::copySignal(const float* signal) {
	memcpy(this->signal, signal, sizeof(float) * signalSize);
}

void CFft::copyReal(float* real) {
	memcpy(this->real, real, sizeof(float) * binSize);
}

void CFft::copyImaginary(float* imag) {
	if(imag == NULL)
		memset(this->imag, 0, sizeof(float) * binSize);
	else
		memcpy(this->imag, imag, sizeof(float) * binSize);
}

void CFft::copyAmplitude(float* amplitude) {
	memcpy(this->amplitude, amplitude, sizeof(float) * binSize);
}

void CFft::copyPhase(float* phase) {
	if(phase == NULL)
		memset(this->phase, 0, sizeof(float) * binSize);
	else
		memcpy(this->phase, phase, sizeof(float) * binSize);
}

void CFft::prepareSignal() {
	if(!signalUpdated)
		updateSignal();
	if(!signalNormalized)
		normalizeSignal();
}

void CFft::updateSignal() {
	prepareCartesian();
	executeIfft();
	signalUpdated = true;
	signalNormalized = false;
}

void CFft::normalizeSignal() {
	float normalizer = (float) windowSum / (2 * signalSize);
	for (int i = 0; i < signalSize; i++)
		signal[i] *= normalizer;
	signalNormalized = true;
}

float* CFft::getSignal() {
	prepareSignal();
	return signal;
}

void CFft::clampSignal() {
	prepareSignal();
	for(int i = 0; i < signalSize; i++) {
		if(signal[i] > 1)
			signal[i] = 1;
		else if(signal[i] < -1)
			signal[i] = -1;
	}
}

void CFft::prepareCartesian() {
	if(!cartesianUpdated) {
		if(!polarUpdated)
			executeFft();
		else
			updateCartesian();
	}
	if(!cartesianNormalized)
		normalizeCartesian();
}

float* CFft::getReal() {
	prepareCartesian();
	return real;
}

float* CFft::getImaginary() {
	prepareCartesian();
	return imag;
}

void CFft::preparePolar() {
	if(!polarUpdated)
		updatePolar();
	if(!polarNormalized)
		normalizePolar();
}

float* CFft::getAmplitude() {
	preparePolar();
	return amplitude;
}

float* CFft::getPhase() {
	preparePolar();
	return phase;
}

float CFft::getAmplitudeAtBin(float bin) {
	float* amplitude = getAmplitude();
	int lowBin = Clamp(floorf(bin), 0, binSize - 1);
	int highBin = Clamp(ceilf(bin), 0, binSize - 1);
	return MapValue(bin, lowBin, highBin, amplitude[lowBin], amplitude[highBin]);
}

float CFft::getBinFromFrequency(float frequency, float sampleRate) {
	return frequency * binSize / (sampleRate / 2);
}

float CFft::getAmplitudeAtFrequency(float frequency, float sampleRate) {
	return getAmplitudeAtBin(getBinFromFrequency(frequency, sampleRate));
}

void CFft::updateCartesian() {
	for(int i = 0; i < binSize; i++) {
		real[i] = cosf(phase[i]) * amplitude[i];
		imag[i] = sinf(phase[i]) * amplitude[i];
	}
	cartesianUpdated = true;
	cartesianNormalized = polarNormalized;
}

void CFft::normalizeCartesian() {
	float normalizer = 2. / windowSum;
	for(int i = 0; i < binSize; i++) {
		real[i] *= normalizer;
		imag[i] *= normalizer;
	}
	cartesianNormalized = true;
}

void CFft::updatePolar() {
	prepareCartesian();
	for(int i = 0; i < binSize; i++) {
		amplitude[i] = cartesianToAmplitude(real[i], imag[i]);
		phase[i] = cartesianToPhase(real[i], imag[i]);
	}
	polarUpdated = true;
	polarNormalized = cartesianNormalized;
}

void CFft::normalizePolar() {
	float normalizer = 2. / windowSum;
	for(int i = 0; i < binSize; i++)
		amplitude[i] *= normalizer;
	polarNormalized = true;
}

void CFft::clearUpdates() {
	cartesianUpdated = false;
	polarUpdated = false;
	cartesianNormalized = false;
	polarNormalized = false;
	signalUpdated = false;
	signalNormalized = false;
}

void CFft::setSignal(const std::vector<float>& signal) {
	setSignal(&signal[0]);
}

void CFft::setSignal(const float* signal) {
	clearUpdates();
	copySignal(signal);
	signalUpdated = true;
	signalNormalized = true;
}

void CFft::setCartesian(float* real, float* imag) {
	clearUpdates();
	copyReal(real);
	copyImaginary(imag);
	cartesianUpdated = true;
	cartesianNormalized = true;
}

void CFft::setPolar(float* amplitude, float* phase) {
	clearUpdates();
	copyAmplitude(amplitude);
	copyPhase(phase);
	polarUpdated = true;
	polarNormalized = true;
}
