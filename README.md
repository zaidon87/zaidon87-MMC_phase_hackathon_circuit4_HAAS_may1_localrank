# MMC_closedloop_NLM

Closed-loop **Modular Multilevel Converter (MMC)** repository for MATLAB/Simulink development and future OwnTech/TWIST embedded deployment.

This repository follows the same general style as the CARROTS / OwnTech MMC branch:

```text
MMC_closedloop_NLM
├── .github/
│   └── ISSUE_TEMPLATE/
├── .vscode/
├── MMC_documentation/
├── MMC_models/
│   └── MMC_phase_hackathon_circuit4_HAAS_may1_localrank.slx
├── docs/
│   ├── requirements.md
│   ├── control_architecture.md
│   ├── consensus_vs_local_rank.md
│   └── decentralized_roadmap.md
├── models/
│   └── README.md
├── owntech/
├── src/
│   ├── main.cpp
│   ├── mmc_closedloop_nlm.hpp
│   └── mmc_closedloop_nlm.cpp
├── zephyr/
├── .gitignore
├── LICENSE
├── platformio.ini
├── west.yml
└── README.md
```

---

## 1. Project objective

The objective is to organize a simulation-ready MMC closed-loop Nearest Level Modulation / Nearest Level Control repository and prepare a clean path toward decentralized control.

The current model is:

```text
MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank.slx
```

The model represents the current MATLAB/Simulink development stage based on a **local-rank voltage-balancing strategy**. The repository adds documentation, embedded-code placeholders, and a control-roadmap structure so that the project can later be migrated toward OwnTech/TWIST firmware.

---

## 2. Control concept

The intended control stack is:

```text
Outer voltage / power reference
        ↓
Closed-loop AC current / arm-current control
        ↓
Arm voltage reference generation
        ↓
NLM / NLC insertion-number generation
        ↓
Voltage-balancing layer
        ↓
Submodule gate commands
```

The uploaded model is kept as the primary simulation artifact. The documentation explains how the current local-rank approach can be extended to consensus-based decentralized balancing.

---

## 3. Current local-rank method

The current local-rank method uses local capacitor-voltage information to assign insertion priority. In simple form, each submodule is evaluated by a local voltage-balancing metric:

```text
rank_i = f(Vc_i, i_arm, insertion_need)
```

Typical rule:

- if the arm current charges inserted capacitors, select lower-voltage capacitors first;
- if the arm current discharges inserted capacitors, select higher-voltage capacitors first;
- if a submodule is unavailable or faulty, exclude it from the candidate list.

This is effective for simulation and is relatively simple to implement, but it can still depend on arm-level information or global/centralized ordering if not carefully redesigned.

---

## 4. Consensus algorithm difference

A consensus-based method is different from local rank because each submodule does not only compare itself against a fixed local list. Instead, the submodules iteratively exchange information with neighbors and converge toward a shared balancing variable, for example the average capacitor voltage or a distributed priority value.

Simplified consensus update:

```text
x_i(k+1) = x_i(k) + α Σ a_ij [x_j(k) - x_i(k)]
```

where:

- `x_i` is the local estimate or balancing state of submodule `i`;
- `x_j` is the neighbor state;
- `a_ij` is the neighbor connection weight;
- `α` is the consensus step size.

The key difference is:

| Aspect | Local-rank balancing | Consensus balancing |
|---|---|---|
| Main idea | Select SMs by voltage ranking | Make SM states converge through neighbor exchange |
| Communication | Minimal, may be local or centralized depending on implementation | Neighbor-to-neighbor iterative communication |
| Decision variable | rank / priority | local consensus state |
| Scalability | Good for small arms, harder if global sorting is used | Better for distributed architectures |
| Fully decentralized path | Needs leader rotation or local voting | Naturally compatible with distributed control |
| Fault tolerance | Requires explicit fault skipping | Can tolerate topology changes if graph remains connected |

---

## 5. Forward path to decentralized control

To move from the present model to a more decentralized controller:

1. Separate the control into clear layers:
   - outer reference generation;
   - arm-level closed-loop control;
   - local submodule balancing;
   - local modulation and gate generation.

2. Replace global sorting with local communication:
   - neighbor voltage exchange;
   - local rank comparison;
   - ring-based leader token or consensus update.

3. Add a local controller inside each submodule:
   - local capacitor-voltage measurement;
   - local arm-current sign or local current estimate;
   - neighbor voltage reception;
   - local insertion/bypass/PWM decision.

4. Implement fault handling:
   - availability flag per SM;
   - skip faulty SM in insertion decisions;
   - re-normalize insertion number across healthy SMs.

5. Prepare for OwnTech/TWIST:
   - move MATLAB logic into `src/`;
   - define ADC input mapping;
   - define PWM output mapping;
   - validate timing with ScopeMimicry / serial acquisition.

---

## 6. Repository usage

### MATLAB / Simulink

Open MATLAB and run:

```matlab
open_system('MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank.slx')
```

Recommended checks:

```matlab
set_param(bdroot, 'SolverType', 'Fixed-step')
set_param(bdroot, 'SimulationMode', 'normal')
```

### Embedded placeholder

The `src/` folder contains C++ placeholder files for future OwnTech/TWIST migration. They are not a full firmware implementation yet. They define the expected structure for:

- closed-loop NLM reference update;
- local-rank balancing;
- future consensus update;
- submodule duty/gate output.

---

## 7. Documentation map

| File | Purpose |
|---|---|
| `docs/requirements.md` | Software, hardware, and control requirements |
| `docs/control_architecture.md` | Closed-loop MMC control architecture |
| `docs/consensus_vs_local_rank.md` | Detailed comparison between local-rank and consensus balancing |
| `docs/decentralized_roadmap.md` | Step-by-step path to full decentralized control |
| `MMC_documentation/model_notes.md` | Notes specific to the included Simulink model |

---

## 8. Status

Current status:

- Simulink model included;
- repository structure created;
- documentation added;
- embedded-code skeleton added;
- ready for upload to GitHub.

Next technical step:

> Validate the closed-loop voltage/current response in Simulink, then isolate the submodule local controller into code-generation-compatible MATLAB Function blocks before porting to `src/`.

---

## 9. License

This project is provided under the LGPL-2.1 license style to remain compatible with the referenced OwnTech/MMC style. Confirm final licensing with project collaborators before public release.
