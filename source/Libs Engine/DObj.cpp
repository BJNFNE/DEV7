namespace DObj {

class DObj {
public:
    int GetCurrentTabVar(int param_1);
    int GetFuncByIndex(int param_1);
};

int DObj::GetCurrentTabVar(int param_1) {
return *(int *)(param_1 + 8);
}

int DObj::GetFuncByIndex(int param_1) {
return *(int *)(param_1 + 0xc);
}

} // namespace DObj
