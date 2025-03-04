#ifndef CHANNELSPC_H
#define CHANNELSPC_H
#endif // not required?
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
            int isStereo(int param_1);
            int Stop(int param_1);
    };
}