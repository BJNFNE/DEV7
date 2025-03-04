#include "TrackerPC.h"

int trkTrack_Impl::GetCallbacks(int param_1) {
    return *(int **)(param_1 + 0x30);
}

int trkTrack_Impl::DecReadPosition(int param_1) {
    {
        *(int *)((int)this + 0x1c) = ((*(int *)((int)this + 0x18) + *(int *)((int)this + 0xc)) - param_1) + param_2;
        return;
      }
}

      

