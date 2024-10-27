namespace DIdent {

class DIdent {
public:
    void IsStillReferenced(int param_1);
};

void DIdent::IsStillReferenced(int param_1) {
*(int *)(param_1 + 4);
return;
}


} // namespace DevList
