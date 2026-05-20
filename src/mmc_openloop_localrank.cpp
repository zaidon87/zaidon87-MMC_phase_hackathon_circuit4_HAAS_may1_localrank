#include "mmc_openloop_localrank.hpp"

#include <algorithm>
#include <cmath>

namespace mmc_openloop {

float saturate01(float x) {
    return std::clamp(x, 0.0f, 1.0f);
}

float local_neighbor_reference(float vc_prev, float vc_next) {
    return 0.5f * (vc_prev + vc_next);
}

float local_rank_bias(float vc_i,
                      float vc_prev,
                      float vc_next,
                      float i_arm) {

    constexpr float k_rank = 0.02f;
    constexpr float bias_limit = 0.05f;

    const float vc_ref = local_neighbor_reference(vc_prev, vc_next);
    const float error = vc_ref - vc_i;

    float dir = 0.0f;

    if (std::fabs(i_arm) > 1.0e-5f) {
        dir = (i_arm > 0.0f) ? 1.0f : -1.0f;
    }

    float bias = k_rank * error * dir;

    return std::clamp(bias, -bias_limit, bias_limit);
}

LocalRankOutput local_rank_step(const ArmOpenLoopCommand& arm,
                                const LocalRankInput& sm) {

    LocalRankOutput out{};

    if (!sm.available) {
        out.duty = 0.0f;
        out.rank_bias = 0.0f;
        out.gate = false;
        return out;
    }

    const float m_base = saturate01(arm.m_arm);

    const float bias = local_rank_bias(sm.vc_i,
                                       sm.vc_prev,
                                       sm.vc_next,
                                       arm.i_arm);

    const float m_local = saturate01(m_base + bias);

    out.duty = m_local;
    out.rank_bias = bias;
    out.gate = (m_local > 0.5f);

    return out;
}

} // namespace mmc_openloop
