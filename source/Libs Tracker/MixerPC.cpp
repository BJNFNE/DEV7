namespace trkWinMixer {

class trkWinMixer {
public:
    int GetStereo(int param_1);
    int GetNbSamplesPerBlock(void *this,uint param_1);
};

int trkWinMixer::GetStereo(int param_1) {
    return *(int *)(param_1 + 0x14);
}

int trkWinMixer::GetNbSamplesPerBlock(void *this,uint param_1) {
    // WIP implementation
      if (*this <= param_1) {
    return 0;
  }
}

} // namespace ChannelsPC
