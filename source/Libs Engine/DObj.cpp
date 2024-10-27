namespace DObj {

class DObj {
public:
    int GetCurrentTabVar(int param_1);
};

int DObj::GetCurrentTabVar(int param_1) {
return *(int *)(param_1 + 8);
}


} // namespace DObj
