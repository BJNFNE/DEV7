#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

namespace SoundBuffer {

    class trkSoundBuffer {
    public:
        // Returns the size of the sound buffer in bytes
        int GetSizeInBytes(int param_1);

        // Returns the frequency of the sound buffer
        int GetFrequency(int param_1);

        // Returns the data associated with the sound buffer
        int GetData(int param_1);
    };

} // namespace SoundBuffer

#endif // SOUNDBUFFER_H