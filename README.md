# MMC Local-Rank Open-Loop Control — Corrected v1

Repository for the MATLAB/Simulink **Modular Multilevel Converter (MMC)** open-loop local-rank controller, organized in the same general style as the referenced OwnTech/MMC repository.

---

## 1. Current corrected model

Corrected model version:

```text
MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx
```

Expected repository location:

```text
MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx
```

The corrected model modifies the open-loop local-rank controller while preserving the general MMC model organization.

---

## 2. Repository structure

```text
zaidon87-MMC_phase_hackathon_circuit4_HAAS_may1_localrank
├── .github/
│   └── ISSUE_TEMPLATE/
├── .vscode/
├── MMC_documentation/
│   └── model_notes.md
├── MMC_models/
│   ├── open_model.m
│   └── README_MODEL_FILE.md
├── docs/
│   ├── requirements.md
│   ├── control_architecture.md
│   ├── consensus_vs_local_rank.md
│   ├── decentralized_roadmap.md
│   └── localrank_correction_v1.md
├── models/
│   └── README.md
├── owntech/
│   └── README.md
├── src/
│   ├── main.cpp
│   ├── mmc_closedloop_nlm.hpp
│   └── mmc_closedloop_nlm.cpp
├── zephyr/
│   └── prj.conf
├── .gitignore
├── LICENSE
├── platformio.ini
└── README.md
```

---

## 3. Correction summary

The original open-loop local-rank controller used the neighbor-balancing term directly in the local submodule duty calculation:

```matlab
m_i = max(0.0, min(double(m_arm) + dm, 1.0));
```

This can create a problem because each submodule independently perturbs the common arm modulation command. The result can be:

- distorted output voltage;
- capacitor-voltage ripple;
- uneven upper/lower arm behavior;
- switching chatter around current zero-crossing;
- poor compatibility with later decentralized control.

The corrected version preserves the dominant arm modulation command:

```matlab
m = min(max(double(m_arm), 0.0), 1.0);
```

Then neighbor information is used only as a small bounded rank/balancing bias, not as a large independent modulation perturbation.

Full explanation:

```text
docs/localrank_correction_v1.md
```

---

## 4. Control architecture

The intended control flow is:

```text
arm modulation command m_arm
        ↓
saturation and validity check
        ↓
local neighbor voltage feedback
        ↓
small bounded local-rank bias
        ↓
submodule gate/duty command
```

This is still an open-loop local-rank controller. It is not yet a full closed-loop MMC controller. The next step should be a closed-loop arm-current and/or circulating-current correction layer.

---

## 5. Local-rank versus consensus

This repository also documents the difference between the current **local-rank** method and a future **consensus-based** decentralized method.

Local rank:

```text
select submodules using voltage priority / rank
```

Consensus:

```text
x_i(k+1) = x_i(k) + α Σ a_ij [x_j(k) - x_i(k)]
```

Detailed comparison:

```text
docs/consensus_vs_local_rank.md
```

---

## 6. MATLAB usage

After uploading the corrected `.slx` file into `MMC_models/`, open MATLAB and run:

```matlab
cd MMC_models
open_model
```

or directly:

```matlab
open_system('MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx')
```

Recommended checks:

```matlab
set_param(bdroot, 'SolverType', 'Fixed-step')
set_param(bdroot, 'SimulationMode', 'normal')
```

Observe:

- output voltage;
- upper/lower arm current;
- capacitor voltages;
- insertion/duty signals;
- level transitions.

---

## 7. Next development step

Recommended next step:

```text
corrected open-loop local rank
        ↓
closed-loop arm-current controller
        ↓
NLM/NLC insertion number correction
        ↓
local-rank or consensus balancing
        ↓
OwnTech/TWIST embedded migration
```

---

## 8. Documentation map

| File | Purpose |
|---|---|
| `docs/localrank_correction_v1.md` | Main correction explanation |
| `docs/control_architecture.md` | MMC control structure |
| `docs/requirements.md` | Requirements and validation checklist |
| `docs/consensus_vs_local_rank.md` | Difference between local rank and consensus |
| `docs/decentralized_roadmap.md` | Roadmap to decentralized MMC control |
| `MMC_documentation/model_notes.md` | Model-specific notes |

---

## 9. Status

Current status:

- repository initialized;
- correction documentation added;
- source-code skeleton added;
- GitHub structure updated;
- corrected `.slx` model prepared externally as `MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx`.

Because `.slx` is a binary Simulink file, upload it manually into `MMC_models/` if it does not appear in GitHub after automated update.
