namespace ChannelsPC {

class trkWinMasterChannel {
public:
    int GetLastReadBlockPosition(int param_1);
};

int trkWinMasterChannel::GetLastReadBlockPosition(int param_1) {
    return *(int *)(param_1 + 0x6);
}

} // namespace ChannelsPC
