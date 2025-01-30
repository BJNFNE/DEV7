namespace trkWinMixer {

namespace trkChannel {

class trkChannel {
public: 
    int IsStereo(int param_1);
};

} // namespace trkChannel


class trkWinMixer {
public:
    int GetStereo(int param_1);
    int GetNbSamplesPerBlock(uint param_1);
};

int trkWinMixer::GetStereo(int param_1) {
    return *(int *)(param_1 + 0x14);
}

int trkWinMixer::GetNbSamplesPerBlock(uint param_1) {
    if (*this <= param_1) {
        return 0;
    }
    return 1;
}

} // namespace trkWinMixer
