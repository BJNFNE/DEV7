namespace DIdent {

class DIdent {
public:
    void IsStillReferenced(int param_1);
};

void DIdent::IsStillReferenced(int param_1) {
return *(int *)(param_1 + 4);


} // namespace DevList
