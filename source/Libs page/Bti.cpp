namespace CBti {

class CBti {
public:
    int GetHorizontalSizeMax(int param_1);
    int GetVerticalSizeMax(int param_1);
    int GetWFrame(int param_1);
    uint GetHFrame(int param_1);
    uint LoadSignedLong(int param_1);
};

int CBti::GetHorizontalSizeMax(int param_1) {
    return *(int *)(param_1 + 0x19c);
}

int CBti::GetVerticalSizeMax(int param_1) {
    return *(int *)(param_1 + 0x1a0);
}

int CBti::GetWFrame(int param_1) {
    return **(int **)(param_1 + 0x1a4);
}

uint CBti::GetHFrame(int param_1) {
    return -(uint)(*(uint *)(param_1 + 0x10c) != 0xffff8300) & *(uint *)(param_1 + 0x10c);
}

uint CBti::LoadSignedLong(int param_1) {
    return -(uint)(*(uint *)(param_1 + 0x110) != 0xffff8300) & *(uint *)(param_1 + 0x110);
}

} // namespace CBti
