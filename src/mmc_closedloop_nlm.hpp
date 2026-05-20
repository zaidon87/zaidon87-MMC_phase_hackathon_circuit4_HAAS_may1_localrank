#pragma once

#include <cstdint>
#include <array>

namespace mmc {

constexpr int N_SM = 4;

struct ArmMeasurements {
    std::array<float, N_SM> vc{};
    float i_arm = 0.0f;
    float v_arm_ref = 0.0f;
    int n_insert_ref = 0;
};

struct LocalSmState {
    float vc = 0.0f;
    float vc_prev = 0.0f;
    float vc_next = 0.0f;
    float consensus_x = 0.0f;
    bool available = true;
    bool gate = false;
    float duty = 0.0f;
};

int nearest_level_count(float v_arm_ref, float vc_nom, int n_available);
float consensus_update(float x_i, float x_prev, float x_next, float alpha);
float local_rank_priority(float vc_i, float vc_ref, float i_arm);
bool local_gate_decision(float priority_i, int n_insert_ref, int sm_index, bool available);

} // namespace mmc
