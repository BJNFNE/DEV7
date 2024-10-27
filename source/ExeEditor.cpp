namespace DevEditor {

class DevEditor {
public:
    void Draw(int param_1);
};

void DevEditor::Draw(int param_1) {
{
    *(uint *)((uintptr_t)this + 0x12) = param_1; // Store param_1 at offset 0x12
    *(uint *)((uintptr_t)this + 0x16) = param_1 >> 0x18; // Store shifted param_1 at offset 0x16
    return;
}

} // namespace DevEditor
