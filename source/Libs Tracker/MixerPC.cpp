namespace trkWinMixer {

class trkWinMixer {
public:
    int GetStereo(int param_1);
};

int trkWinMixer::GetStereo(int param_1) {
    return *(int *)(param_1 + 0x14);
}

} // namespace ChannelsPC
