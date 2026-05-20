#include "mmc_closedloop_nlm.hpp"

// OwnTech / PlatformIO entry point placeholder.
// This file is intentionally minimal. The validated MATLAB/Simulink controller
// should be migrated here after timing and signal mapping are confirmed.

int main() {
    constexpr float vc_nom = 12.0f;
    constexpr float v_arm_ref = 24.0f;
    constexpr int n_available = mmc::N_SM;

    int n_insert = mmc::nearest_level_count(v_arm_ref, vc_nom, n_available);
    (void)n_insert;

    while (true) {
        // Future real-time loop:
        // 1. acquire ADC measurements;
        // 2. update closed-loop references;
        // 3. update NLM insertion count;
        // 4. update local rank / consensus state;
        // 5. write PWM/gate outputs.
    }

    return 0;
}
