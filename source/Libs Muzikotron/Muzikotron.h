#ifndef ZIKMUZIKOTRON_H
#define ZIKMUZIKOTRON_H

// Forward declaration
class ztrkSoundBuffer;

class zikMuzikotron {
public:
    zikMuzikotron(unsigned long arg);
    ~zikMuzikotron();

    void SetQueueTrack(unsigned long arg1, unsigned long arg2);
    void SetQueueHasNoFixedTrack(unsigned long arg1);
    unsigned long AddSoundEvent(unsigned long arg1, const ztrkSoundBuffer* arg2, unsigned long arg3);
    void RemoveSoundEvent(unsigned long arg1, unsigned long arg2);
    void SetQueueVolume(unsigned long arg1, unsigned long arg2);
    void SetCompositionLength(unsigned long arg);
    unsigned long GetMsPosition() const;
    void Play(unsigned long arg);
    void PlayII(unsigned long arg1, unsigned long arg2);
    unsigned long Stop();
    unsigned long Update();

private:
    // Private members if any
};

#endif // ZIKMUZIKOTRON_H
