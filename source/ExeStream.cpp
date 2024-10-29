namespace ExeStream {

class DStream {
public:
    int GetPosition(int param_1);
    int SetPosition(int param_1);
};

int DStream::GetPosition(int param_1) {
    return *(int*)(reinterpret_cast<int>(this) + param_1 + 8);
}

int DStream::SetPosition(int param_1) {
return *(int *)(param_1 + 0x10);
}

}
