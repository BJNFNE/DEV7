#ifndef ZIK_SOUNDS_QUEUE_H
#define ZIK_SOUNDS_QUEUE_H

// #include "zikSoundEvent.h" // Include the actual header for zikSoundEvent if needed

class zikSoundsQueue {
public:
    // Constructor
    zikSoundsQueue(unsigned long arg1, unsigned long arg2, unsigned long arg3, bool arg4, unsigned long arg5);

    // Destructor
    ~zikSoundsQueue();

    // Getter functions
    unsigned long GetNoTrack() const;
    unsigned long GetPosition() const;
    unsigned long HasFixedTrack() const;
    unsigned long GetFixedTrack() const;

    // Setter functions
    void SetHasFixedTrack(unsigned long arg);
    void SetHasNoFixedTrack();
    void SetLength(unsigned long arg);

    // Sound event functions
    unsigned long AddSoundEvent(zikSoundEvent* arg);
    void RemoveSoundEvent(unsigned long arg);

    // Playback functions
    void Start(unsigned long arg);
    void StartII(unsigned long arg1, unsigned long arg2);
    unsigned long Stop();

    // Buffer management functions
    void FeedBuffer(bool arg);
    void UnflagPrecalc();

    // Update function
    unsigned long Update();

private:
    // Private members and methods as needed
};

#endif // ZIK_SOUNDS_QUEUE_H
