#include "SoundBuffer.h"

namespace SoundBuffer {

    int trkSoundBuffer::GetSizeInBytes(int param_1) {
        return *(int *)(param_1 + 0x10);
    }

    int trkSoundBuffer::GetFrequency(int param_1) {
        return *(int *)(param_1 + 4);
    }

    int trkSoundBuffer::GetData(int param_1) {
        return *(int *)(param_1 + 0x18);
    }

} // namespace SoundBuffer