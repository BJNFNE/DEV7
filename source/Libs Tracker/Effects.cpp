#include "Effects.h"

namespace SoundBuffer {

    int PitchShifter::Process(int param_1) {
        {
            if (*(int **)(param_1 + 0x30) != (int *)0x0) {
              (**(code **)**(int **)(param_1 + 0x30))(1);
            }
            *(int *)(param_1 + 0x30) = 0;
            return 0;
          }
          
    }

} // namespace SoundBuffer