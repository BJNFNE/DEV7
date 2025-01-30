namespace MemorySound {

class zikMemorySound {
public:
    int IncLink(int param_1);
    int DecLink(int param_1);
    void Load(int param_1);
};

int zikMemorySound::IncLink(int param_1) {
    return *(int *)(param_1 + 0x10);
}

int zikMemorySound::DecLink(int param_1) {
    return *(int *)(param_1 + 0x14);
}

void Load(int param_1) {
    {
  if (param_1[5] != 0) {
    param_1[5] = param_1[5] + -1;
  }
  if ((param_1[5] == 0) && (param_1 != (int *)0x0)) {
    (**(int **)param_1)(1);
  }
  return;
}

}

} // namespace MemorySound
