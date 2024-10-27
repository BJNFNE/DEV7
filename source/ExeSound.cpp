namespace Dev7Sound {

class SoundManager {
public:
    void SoundStopNotify(int param_1);
    bool SetIsPlaying(int param_1);
    bool IsStopped(int param_1);
    void SetIsPaused(int param_1);
    int GetPlayingTrack(int param_1);
    void SetNoEffectsBox(int param_1);
};

void SoundManager::SetNoEffectsBox(int param_1) {
*(int *)(param_1 + 0x14) = param_1; 
}

int SoundManager::GetPlayingTrack(int param_1) {
return *(int *)(param_1 + 0x14);

}

void SoundManager::SoundStopNotify(int param_1) {
    *(reinterpret_cast<unsigned int*>(param_1 + 4)) = 2;
    return;
}

bool SoundManager::SetIsPlaying(int param_1) {

return *(int *)(param_1 + 4) == 0;
}

void SoundManager::SetIsPaused(int param_1) {
    *(reinterpret_cast<unsigned int*>(param_1 + 4)) = 1;
    *(reinterpret_cast<unsigned int*>(param_1 + 8)) = param_1;
    return;
}

bool IsStopped(int param_1) {

return *(int *)(param_1 + 4) == 1;
}

} // namespace Dev7Sound
