# Local-Rank Open-Loop Correction — v1

## Corrected model

Corrected Simulink model name:

```text
MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx
```

Expected location in the repository:

```text
MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx
```

## Problem in the original open-loop local-rank controller

The original local submodule controller used the neighbor-balancing correction directly on each submodule duty/modulation command:

```matlab
m_i = max(0.0, min(double(m_arm) + dm, 1.0));
```

This creates an important issue: every submodule modifies the common arm modulation independently. Therefore, the total inserted arm voltage is no longer determined only by the arm-level reference. The local balancing loop can unintentionally change the synthesized AC voltage, creating:

- output-voltage distortion;
- capacitor-voltage ripple;
- switching chatter near zero current crossing;
- asymmetry between upper and lower arm behavior;
- unstable local duty perturbation if `k_v` is too high.

## Corrected control principle

The correction keeps the arm modulation as the dominant quantity:

```matlab
m = min(max(double(m_arm), 0.0), 1.0);
```

The neighbor voltage difference is no longer allowed to create a large independent modulation command. Instead, it is used only as a bounded local balancing/ranking bias.

## Corrected local-rank idea

The corrected logic follows this hierarchy:

```text
arm reference / m_arm
        ↓
valid modulation saturation
        ↓
small neighbor-balancing bias
        ↓
local rank / priority decision
        ↓
insert, bypass, or PWM boundary duty
```

## Expected improvement

The corrected version should provide:

- cleaner open-loop voltage waveform;
- reduced capacitor-voltage ripple;
- less duty-cycle distortion;
- smoother local-rank transition;
- better compatibility with future decentralized control.

## Corrected MATLAB Function block

The corrected function applied to each local submodule controller is conceptually:

```matlab
function gate_signal = hb_sm_local_ctrl_neighbor(sm_id, m_arm, i_arm, Vc_arm, Vc_prev, Vc_next, N)
%#codegen
% Corrected open-loop local-rank neighbor controller

k_rank = double(0.02);
deadband_i = double(1e-4);

m = min(max(double(m_arm), 0.0), 1.0);

Vref_local = 0.5 * (double(Vc_prev) + double(Vc_next));
Vc_i = double(Vc_arm(sm_id));

if abs(double(i_arm)) < deadband_i
    dir = 0.0;
else
    dir = sign(double(i_arm));
end

rank_bias = k_rank * (Vref_local - Vc_i) * dir;
rank_bias = min(max(rank_bias, -0.05), 0.05);

m_bal = min(max(m + rank_bias, 0.0), 1.0);

gate_signal = m_bal;
end
```

## Important note

This is still an **open-loop local-rank** correction. It improves the local controller behavior but does not replace a true closed-loop arm-current controller or a circulating-current controller. For a high-quality MMC output, the next step should be:

```text
open-loop local rank → closed-loop arm reference → NLM/NLC → local-rank/consensus balancing
```
