#pragma once

#include <array>
#include <cstdint>

namespace mmc_openloop {

// Open-loop local-rank MMC helper code.
// Scope: no closed-loop current control, no circulating-current controller,
// no consensus algorithm, and no distributed consensus state.

constexpr int N_SM = 4;

struct ArmOpenLoopCommand {
    float m_arm = 0.0f;      // open-loop arm modulation command, normalized [0, 1]
    float i_arm = 0.0f;      // measured or estimated arm-current sign for charge/discharge ranking
};

struct LocalRankInput {
    int sm_id = 0;           // zero-based submodule index
    float vc_i = 0.0f;       // local capacitor voltage
    float vc_prev = 0.0f;    // previous neighbor capacitor voltage
    float vc_next = 0.0f;    // next neighbor capacitor voltage
    bool available = true;   // false means bypass/fault skip
};

struct LocalRankOutput {
    float duty = 0.0f;       // continuous duty in [0, 1]
    float rank_bias = 0.0f;  // bounded local-rank bias
    bool gate = false;       // simple insert/bypass interpretation
};

float saturate01(float x);
float local_neighbor_reference(float vc_prev, float vc_next);
float local_rank_bias(float vc_i, float vc_prev, float vc_next, float i_arm);
LocalRankOutput local_rank_step(const ArmOpenLoopCommand& arm,
                                const LocalRankInput& sm);

} // namespace mmc_openloop
