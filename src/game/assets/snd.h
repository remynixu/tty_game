#ifndef SND_H
#define SND_H

enum beep_id{
	SNDBEEP_MED = 1000
};

extern void snd_beep(enum beep_id, float sec);

#endif /* SND_H */
