namespace SoundBuffer {

    class trkSoundBuffer {
    public:
        int GetSizeInBytes(int param_1);
        int GetFrequency(int param_1);
    };

    int trkSoundBuffer::GetSizeInBytes(int param_1) {
        return *(int *)(param_1 + 0x10);
    }

    int trkSoundBuffer::GetFrequency(int param_1) {
        return *(int *)(param_1 + 4);
    }

}