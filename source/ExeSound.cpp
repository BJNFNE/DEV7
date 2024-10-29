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

class Dev7EffectsBox {
public:
    void SubVmdLink(int param_1);
    void AddVmdLink(int param_1);
    void HasFixedTracks(int param_1);
    void GetNbEffects(int param_1);
    void GetNoTrack(void);
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

bool SoundManager::IsStopped(int param_1) {

return *(int *)(param_1 + 4) == 1;
}


void Dev7EffectsBox::SubVmdLink(int param_1) {

*(reinterpret_cast<unsigned int*>(param_1 + 4)) = param_1;
}

void Dev7EffectsBox::AddVmdLink(int param_1) {

*(reinterpret_cast<unsigned int*>(param_1 + 8)) = param_1;
}

void Dev7EffectsBox::HasFixedTracks(int param_1) {
return;
}

void Dev7EffectsBox::GetNbEffects(int param_1) {

*(reinterpret_cast<int*>(param_1 + 0xc));
}

void Dev7EffectsBox::GetNoTrack(void) {

return;
}

} // namespace Dev7Sound
  // namespace Dev7EffectsBox
