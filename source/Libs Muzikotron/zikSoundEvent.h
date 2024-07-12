#ifndef ZIK_SOUNDEVENT_H
#define ZIK_SOUNDEVENT_H

#include "trkSoundBuffer.h" // Include the actual header for trkSoundBuffer if needed

class zikSoundEvent {
public:
    // Constructors
    zikSoundEvent();
    zikSoundEvent(const trkSoundBuffer* arg1, unsigned long arg2);

    // Destructor
    ~zikSoundEvent();

    // Copy constructor and assignment operator
    zikSoundEvent(const zikSoundEvent& other);
    zikSoundEvent& operator=(const zikSoundEvent& other);

    // Comparison operators
    bool operator==(const zikSoundEvent& other) const;
    bool operator!=(const zikSoundEvent& other) const;
    bool operator<(const zikSoundEvent& other) const;
    bool operator>(const zikSoundEvent& other) const;
    bool operator<=(const zikSoundEvent& other) const;
    bool operator>=(const zikSoundEvent& other) const;

    // Getter functions
    const trkSoundBuffer* GetSoundBuffer() const;
    unsigned long GetSampleStartPosition() const;
    unsigned long GetNextSampleToRead() const;

    // Setter function
    void SetNextSampleToRead(unsigned long arg);

private:
    const trkSoundBuffer* soundBuffer;
    unsigned long sampleStartPosition;
    unsigned long nextSampleToRead;
};

#endif // ZIK_SOUNDEVENT_H
