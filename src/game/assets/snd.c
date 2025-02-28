#include "./snd.h"
#include "../../lib/def.h"
#include <portaudio.h>
#include <math.h>

static int mksin(const void *in, void *out,
		unsigned long frames,
		const PaStreamCallbackTimeInfo
		*time_info, PaStreamCallbackFlags
		status_flags, void *freq){
	float *buf = (float *)out;
	static double phase = 0.0;
	size_t i = 0;
	while(i < frames){
		buf[i] = (float)sin(phase);
		phase += (M_PI * *(float *)freq)
				/ 22050;
		i++;
	}
	return paContinue;
}

void snd_beep(enum beep_id id, float sec){
	float freq = (float)id;
	PaStream *stream;
	Pa_Initialize();
	Pa_OpenDefaultStream(&stream, 0, 1,
			paFloat32, 22050, 256,
			mksin, &freq);
	Pa_StartStream(stream);
	Pa_Sleep(sec * 1000);
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
}
