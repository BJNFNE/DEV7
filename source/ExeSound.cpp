namespace Dev7Sound {

class SoundManager {
public:
    void SoundStopNotify(int param_1);
    bool IsStopped(int param_1);
    void SetIsPaused(int param_1);
};

void SoundManager::SoundStopNotify(int param_1) {
    *(reinterpret_cast<unsigned int*>(param_1 + 4)) = 2;
    return;
}

void SoundManager::SetIsPaused(int param_1) {
    *(reinterpret_cast<unsigned int*>(param_1 + 4)) = 1;
    *(reinterpret_cast<unsigned int*>(param_1 + 8)) = param_1;
    return;
}

bool IsStopped(int param_1) {

return *(int *)(param_1 + 4) ==1;
}

} // namespace Dev7Sound
