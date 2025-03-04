namespace ChannelsPC {

class trkWinMasterChannel {
public:
    int GetLastReadBlockPosition(int param_1);
    int GetSoundBuffer(int param_1);
    int GetDataToWrite(int param_1);
};

class trkChannel {
    public:
        int GetSoundBuffer(int param_1);
        int GetDataToWrite(int param_1);
};

int trkWinMasterChannel::GetLastReadBlockPosition(int param_1) {
    return *(int *)(param_1 + 0x6c);
}

int trkChannel::GetSoundBuffer(int param_1) {
    return *(int *)(param_1 + 0x30);
}

int trkChannel::GetDataToWrite(int param_1) {
    return *(int *)(param_1 + 0x2c);
}

} // namespace ChannelsPC
  // namespace trkChannel
