#include "ChannelsPC.h"

int trkWinMasterChannel::GetLastReadBlockPosition(int param_1) {
    return *(int *)(param_1 + 0x6c);
}

int trkChannel::GetSoundBuffer(int param_1) {
    return *(int *)(param_1 + 0x30);
}

int trkChannel::GetDataToWrite(int param_1) {
    return *(int *)(param_1 + 0x2c);
}

int trkChannel::isStereo(int param_1) {
    return *(int *)(param_1 + 0x24);
}

int trkChannel::Stop(int param_1) {
    {
        *(int *)(param_1 + 0x14) = 0;
        return 1;
    }
      
};
