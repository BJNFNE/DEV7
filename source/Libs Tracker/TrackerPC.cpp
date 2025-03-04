#include "TrackerPC.h"

int trkTrack_Impl::GetCallbacks(int param_1) {
    return *(int **)(param_1 + 0x30);
}

