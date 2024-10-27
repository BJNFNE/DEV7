namespace Dev7Sound {

class SoundManager {
public:
    void SoundStopNotify(int param_1);
};

void SoundManager::SoundStopNotify(int param_1) {
    *(reinterpret_cast<unsigned int*>(param_1 + 4)) = 2;
    return;
}

} // namespace Dev7Sound
