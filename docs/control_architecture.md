# Closed-Loop MMC Control Architecture

## 1. Global view

The control path is organized as:

```text
v_ref / P_ref / Q_ref
        ↓
outer controller
        ↓
arm-voltage reference generation
        ↓
closed-loop current and/or circulating-current correction
        ↓
NLM / NLC insertion-number command
        ↓
balancing selector
        ↓
SM gate commands
```

## 2. Outer control layer

The outer control layer defines the reference that the converter must synthesize. Depending on the model version, this can be:

- AC output-voltage reference;
- output-current reference;
- active/reactive power reference;
- DC-link or capacitor-energy reference.

For the current simulation repository, the outer loop should be used to stabilize the output voltage and prevent drift in the arm energy.

## 3. Arm-level control

The arm-level controller converts the desired AC-side voltage into upper and lower arm voltage references. In a single-phase MMC, the simplified relation is:

```text
v_u,ref = Vdc/2 - v_ac,ref + correction
v_l,ref = Vdc/2 + v_ac,ref + correction
```

The correction term may include:

- AC current PI correction;
- circulating-current control;
- total arm-energy correction;
- differential upper/lower arm-energy balancing.

## 4. NLM / NLC insertion generation

The nearest-level stage maps each arm-voltage reference to an insertion number:

```text
n_u = round(v_u,ref / Vc_nom)
n_l = round(v_l,ref / Vc_nom)
```

The values must be saturated:

```text
0 ≤ n_u ≤ N_available,u
0 ≤ n_l ≤ N_available,l
```

## 5. Local-rank balancing

The local-rank stage chooses which capacitors should be inserted. A classical rule is:

- if `i_arm > 0` and insertion charges capacitors, insert lower-voltage SMs;
- if `i_arm < 0` and insertion discharges capacitors, insert higher-voltage SMs.

This minimizes capacitor-voltage spread but can become centralized if a full arm sorting operation is used.

## 6. Future decentralized form

A decentralized version should avoid a global sorting vector. The local controller should use:

- local capacitor voltage;
- previous and next neighbor voltage;
- local availability flag;
- local rank or consensus state;
- arm-level insertion number received from the arm controller.

The final target is:

```text
local measurements + neighbor communication → local gate decision
```
