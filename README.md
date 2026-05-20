# MMC Phase Hackathon Circuit 4 — Open-Loop Local-Rank Control

This repository contains the MATLAB/Simulink **open-loop local-rank control** version of the Modular Multilevel Converter (MMC) model.

Important scope:

```text
Open-loop local-rank control only
No closed-loop controller
No consensus algorithm
No decentralized consensus layer
```

---

## 1. Main model

Current model:

```text
MMC_phase_hackathon_circuit4_HAAS_may1_localrank.slx
```

Corrected version prepared:

```text
MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx
```

Expected location:

```text
MMC_models/
```

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
│   └── localrank_correction_v1.md
├── models/
│   └── README.md
├── owntech/
│   └── README.md
├── src/
│   ├── main.cpp
│   ├── mmc_openloop_localrank.hpp
│   └── mmc_openloop_localrank.cpp
├── zephyr/
│   └── prj.conf
├── .gitignore
├── LICENSE
├── platformio.ini
└── README.md
```

---

## 3. Control objective

The model uses an open-loop modulation command and a local-rank submodule selection/balancing method.

The control flow is:

```text
open-loop arm modulation command
        ↓
local-rank voltage-balancing logic
        ↓
submodule insertion / bypass decision
        ↓
MMC output voltage generation
```

There is no feedback loop for AC current, arm current, circulating current, or power regulation in this repository version.

---

## 4. Local-rank correction

The original open-loop local-rank function allowed each submodule to strongly modify the common arm modulation command:

```matlab
m_i = m_arm + dm
```

This can distort the total arm voltage because each submodule changes the modulation command independently.

The corrected principle is:

```matlab
m = min(max(double(m_arm), 0.0), 1.0);
```

Then the neighbor-voltage information is used only as a small bounded local-rank bias, not as a separate closed-loop modulation controller.

Detailed note:

```text
docs/localrank_correction_v1.md
```

---

## 5. MATLAB usage

After placing the `.slx` file in `MMC_models/`, open MATLAB and run:

```matlab
cd MMC_models
open_model
```

or directly:

```matlab
open_system('MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank_corrected_v1.slx')
```

Check:

- output voltage level generation;
- upper/lower arm currents;
- capacitor-voltage balancing;
- local-rank switching behavior;
- absence of unwanted closed-loop or consensus blocks.

---

## 6. Status

Current repository status:

- open-loop local-rank documentation corrected;
- closed-loop wording removed from the main README;
- consensus wording removed from the main README;
- source skeleton renamed conceptually to open-loop local-rank;
- Simulink `.slx` file must be uploaded manually because it is a binary MATLAB file.
