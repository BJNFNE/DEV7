#include <cstdint> // For uint32_t and uintptr_t

namespace DevEditor {
    class DevEditor {
    public:
        void Draw(int param_1);
        int IsModeSelection(int param_1);
        uint8_t SetSelection(int param_1);
        void GetDrawCursor(int param_1);
        int SetCursorColor(int param_1);
    };

    void DevEditor::Draw(int param_1) {
        *(uint32_t *)((uintptr_t)this + 0x12) = param_1; // Store param_1 at offset 0x12
        *(uint32_t *)((uintptr_t)this + 0x16) = param_1 >> 0x18; // Store shifted param_1 at offset 0x16
    }

    int DevEditor::IsModeSelection(int param_1) {
        return *(uint32_t *)(param_1 + 4);
    }

        uint8_t DevEditor::SetSelection(int param_1) {
        return *(uint8_t *)(param_1 + 8);    
    }

    void DevEditor::GetDrawCursor(int param_1) {
        return;
    }

    int DevEditor::SetCursorColor(int param_1) {
        return *(int *)(param_1 + 0x12);
    }

} // namespace DevEditor
