# MMC Phase Hackathon Circuit 4 — Open-Loop Local-Rank MMC Control

## Overview

This repository contains a MATLAB/Simulink implementation of a **single-phase Modular Multilevel Converter (MMC)** operating with an **open-loop modulation strategy** and a **local-rank capacitor-voltage balancing method**.

The project is organized in the same clean engineering style commonly used in OwnTech/MMC repositories while remaining focused on:

- Open-loop MMC operation;
- Local-rank balancing;
- Neighbor-voltage comparison;
- Submodule insertion and bypass logic;
- Capacitor-voltage behavior analysis.

---

# 1. Main Simulink Model

Main model:

```text
MMC_phase_hackathon_circuit4_HAAS_may1_localrank.slx
```

Updated model version:

```text
MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx
```

Expected repository location:

```text
MMC_models/
```

The model is intended for studying:

- local-rank balancing;
- capacitor-voltage evolution;
- submodule insertion behavior;
- MMC stepped waveform generation;
- neighbor-based balancing interaction.

---

# 2. MMC Model Description

The converter is composed of:

- Upper arm;
- Lower arm;
- Half-bridge submodules;
- Capacitor energy storage elements;
- Open-loop modulation generation;
- Local balancing logic.

Each submodule contains:

```text
- capacitor
- switching cell
- insertion state
- bypass state
```

The MMC synthesizes a stepped AC waveform from a DC input source through controlled insertion and bypass of the submodules.

---

# 3. Open-Loop Operating Principle

The model uses an open-loop modulation command directly distributed to the balancing layer.

Simplified control flow:

```text
Open-loop arm modulation command
                ↓
Local-rank balancing logic
                ↓
Submodule insertion/bypass decision
                ↓
MMC output voltage synthesis
```

This approach is intended to simplify:

- balancing analysis;
- waveform observation;
- debugging of insertion logic;
- capacitor-voltage behavior studies.

---

# 4. Local-Rank Balancing Strategy

The balancing method is based on local capacitor-voltage comparison.

Each submodule evaluates:

```text
Vc_i
Vc_prev
Vc_next
```

where:

- `Vc_i` = local capacitor voltage;
- `Vc_prev` = previous neighbor capacitor voltage;
- `Vc_next` = next neighbor capacitor voltage.

The balancing logic determines whether the submodule should receive a higher or lower insertion priority.

Simplified balancing concept:

```text
Lower capacitor voltage
        → higher insertion priority during charging condition

Higher capacitor voltage
        → lower insertion priority during charging condition
```

---

# 5. Local-Rank Modulation Principle

The modulation philosophy keeps the global arm modulation command dominant:

```matlab
m = min(max(double(m_arm), 0.0), 1.0);
```

Then only a small bounded local-rank correction is applied.

Conceptually:

```text
Global arm modulation
            +
Small local balancing bias
            ↓
Corrected local duty generation
```

This improves:

- waveform stability;
- balancing smoothness;
- switching transitions;
- modulation consistency.

---

# 6. Simulation Parameters

## Electrical Parameters

| Parameter | Symbol | Value |
|---|---|---|
| DC-link voltage | `VDC` | 48 V |
| Electrical frequency | `f0` | 50 Hz |
| Arm inductance | `L_arm` | 60 mH |
| Bus capacitance | `C_bus` | 4400 µF |
| Arm resistance | `R` | 15 Ω |
| Module capacitance | `C_m` | 1868.4 µF |
| Number of submodules per arm | `N` | 5 |

## Modulation Parameters

| Parameter | Value |
|---|---|
| Modulation index | `m = 1` |
| Energy balancing coefficient | `a = 1` |
| Control frequency | `f_control = 10 kHz` |

## PWM and TWIST Parameters

| Parameter | Value |
|---|---|
| Switching frequency | `200 kHz` |
| PWM resolution | `100 ns` |
| Dead time | `200 ns` |
| Data sampling frequency | `20 kHz` |

The parameters are defined in:

```text
param_phase_circuit4_20260216.m
twist_parameters.m
```

---

# 7. Repository Structure

```text
zaidon87-MMC_phase_hackathon_circuit4_HAAS_may1_localrank
├── .github/
├── .vscode/
├── MMC_documentation/
├── MMC_models/
├── docs/
├── models/
├── owntech/
├── src/
├── zephyr/
├── .gitignore
├── LICENSE
├── platformio.ini
└── README.md
```

---

# 8. MATLAB Usage

After placing the `.slx` file inside `MMC_models/`, open MATLAB and run:

```matlab
cd MMC_models
open_model
```

or directly:

```matlab
open_system('MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx')
```

Recommended simulation settings:

```matlab
set_param(bdroot,'SolverType','Fixed-step')
set_param(bdroot,'SimulationMode','normal')
```

Recommended observations:

- Output voltage waveform;
- Upper and lower arm currents;
- Capacitor-voltage balancing;
- Level transitions;
- Local-rank balancing response.

---

# 9. Repository Objective

The repository is intended as:

```text
An open-loop MMC local-rank balancing analysis and experimentation platform
```

for:

- balancing studies;
- waveform analysis;
- capacitor-voltage observation;
- MMC insertion logic evaluation.

---

# 10. Current Status

Current repository status:

```text
✔ Open-loop MMC structure
✔ Local-rank balancing implementation
✔ Improved repository consistency
```

The Simulink `.slx` file must still be uploaded manually because binary MATLAB files cannot be directly committed through text-based GitHub API updates.
