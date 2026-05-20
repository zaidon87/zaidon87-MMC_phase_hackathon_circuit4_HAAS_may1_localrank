#include "mmc_closedloop_nlm.hpp"
#include <algorithm>
#include <cmath>

namespace mmc {

int nearest_level_count(float v_arm_ref, float vc_nom, int n_available) {
    if (vc_nom <= 0.0f) {
        return 0;
    }

    int n = static_cast<int>(std::lround(v_arm_ref / vc_nom));
    return std::clamp(n, 0, n_available);
}

float consensus_update(float x_i, float x_prev, float x_next, float alpha) {
    return x_i + alpha * ((x_prev - x_i) + (x_next - x_i));
}

float local_rank_priority(float vc_i, float vc_ref, float i_arm) {
    const float error = vc_i - vc_ref;

    // Direction-aware priority:
    // positive arm current convention may be adapted to the final hardware sign.
    if (i_arm >= 0.0f) {
        return -error;   // lower voltage receives higher priority for charging
    }

    return error;        // higher voltage receives higher priority for discharging
}

bool local_gate_decision(float priority_i, int n_insert_ref, int sm_index, bool available) {
    if (!available) {
        return false;
    }

    // Placeholder deterministic rule for early firmware skeleton.
    // Final implementation should use neighbor voting, ring-leader selection,
    // or consensus-assisted distributed selection.
    return (sm_index < n_insert_ref) && (priority_i >= -1.0e9f);
}

} // namespace mmc
