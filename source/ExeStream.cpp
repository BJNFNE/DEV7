namespace ExeStream {

class DStream {
public:
    int GetPosition(int param_1);
};

int DStream::GetPosition(int param_1) {
    return *(int*)(reinterpret_cast<int>(this) + param_1 + 8);
}

}
