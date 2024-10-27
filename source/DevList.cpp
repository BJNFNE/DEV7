namespace DevList {

class CDEVIDENT {
public:
    void SetParamValue(int param_1);
};

void CDEVIDENT::SetParamValue(int param_1) {
    *(int *)this = param_1;
    *(int *)(param_1 + 4) = param_1 + 1;
    return;
}


} // namespace DevList
