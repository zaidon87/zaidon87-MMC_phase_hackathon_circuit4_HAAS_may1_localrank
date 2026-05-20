# Requirements — MMC_closedloop_NLM

## 1. Software requirements

| Tool | Recommended use |
|---|---|
| MATLAB / Simulink | Main MMC simulation |
| Simscape Electrical or Specialized Power Systems | Power-stage modeling, if used by the model |
| Embedded Coder / MATLAB Coder | Future code-generation path |
| VS Code | OwnTech/TWIST firmware editing |
| PlatformIO | Embedded project structure |
| Git | Version control |
| GitHub | Collaboration, issues, branches, and releases |

## 2. MATLAB model requirement

Main model:

```text
MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank.slx
```

The model should be treated as the simulation reference. Any controller modification should be committed with a clear note describing:

- control layer modified;
- changed gains;
- expected output voltage target;
- capacitor-voltage balancing effect;
- simulation time and solver configuration.

## 3. MMC control requirements

The closed-loop MMC controller should include:

1. **Reference generation**
   - output voltage reference;
   - arm voltage references;
   - insertion-number reference for upper and lower arms.

2. **Closed-loop correction**
   - AC-side voltage or current feedback;
   - arm-current correction;
   - circulating-current correction where needed.

3. **NLM / NLC stage**
   - nearest-level insertion count;
   - saturation to valid number of available submodules;
   - correct transition between inserted/bypassed states.

4. **Voltage balancing**
   - local-rank balancing in the current version;
   - future consensus-based balancing for decentralized control.

5. **Submodule gate generation**
   - insert/bypass command;
   - optional PWM boundary command;
   - fault skip and availability handling.

## 4. Decentralization requirements

For full decentralized control, each submodule should have:

- local capacitor-voltage measurement;
- local insertion state;
- neighbor voltage/state input;
- local decision logic;
- communication timeout handling;
- fault flag;
- optional leader-token or consensus-state update.

## 5. Simulation-quality requirements

The model should be validated for:

- output-voltage amplitude;
- waveform level count;
- capacitor-voltage ripple;
- upper/lower arm current shape;
- circulating-current magnitude;
- balancing convergence;
- transient behavior during reference changes.

## 6. Repository requirements

Each future update should include:

- modified `.slx` model or MATLAB scripts;
- short documentation of the control modification;
- simulation screenshots or exported data;
- issue/commit message explaining the result.
