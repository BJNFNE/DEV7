namespace DObj {

class DObj {
public:
    int AddHandler(int param_1);
    int GetCurrentTabVar(int param_1);
    int GetFuncByIndex(int param_1);
    int GetStackRef(int param_1);
};

int AddHandler(int param_1) {
*(short *)(param_1 + 0x3c) = *(short *)(param_1 + 0x3c) + -1;
return;
}

int DObj::GetCurrentTabVar(int param_1) {
return *(int *)(param_1 + 8);
}

int DObj::GetFuncByIndex(int param_1) {
return *(int *)(param_1 + 0xc);
}

int DObj::GetStackRef(int param_1) {

*(short *)(param_1 + 0x3c) = *(short *)(param_1 + 0x3c) + 1;
return;
}

} // namespace DObj
