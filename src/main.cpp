#include "mmc_openloop_localrank.hpp"

// OwnTech / PlatformIO placeholder for the MMC open-loop local-rank controller.
//
// Scope of this repository version:
// - open-loop modulation only;
// - local-rank balancing only;
// - no closed-loop current controller;
// - no circulating-current controller;
// - no consensus algorithm.

int main() {

    mmc_openloop::ArmOpenLoopCommand arm{};

    // Example normalized open-loop modulation command.
    arm.m_arm = 0.5f;

    // Only used to determine charging/discharging direction
    // for local-rank balancing.
    arm.i_arm = 1.0f;

    mmc_openloop::LocalRankInput sm{};

    sm.sm_id = 0;
    sm.vc_i = 12.1f;
    sm.vc_prev = 11.9f;
    sm.vc_next = 12.0f;
    sm.available = true;

    auto out = mmc_openloop::local_rank_step(arm, sm);

    (void)out;

    while (true) {

        // Future real-time loop:
        // 1. read capacitor voltages;
        // 2. read arm-current sign;
        // 3. apply local-rank balancing;
        // 4. generate insert/bypass duty;
        // 5. write PWM or gate outputs.
    }

    return 0;
}
