# Consensus Algorithm vs Local-Rank Balancing

## 1. Purpose of this document

This document explains the difference between the current **local-rank** method and a future **consensus-based decentralized** method for MMC submodule capacitor-voltage balancing.

---

## 2. Local-rank balancing

Local-rank balancing gives each submodule a priority according to capacitor voltage and arm-current direction.

A simplified priority variable is:

```text
ξ_i = Vc_i - Vc_ref
```

The controller then selects submodules according to the charging/discharging condition.

### Case A — inserted SM is charging

If the arm current direction means that an inserted SM capacitor will be charged, then the controller should insert the lower-voltage SMs first.

```text
select SMs with smallest Vc_i
```

### Case B — inserted SM is discharging

If the arm current direction means that an inserted SM capacitor will be discharged, then the controller should insert the higher-voltage SMs first.

```text
select SMs with largest Vc_i
```

### Strength

- simple;
- fast;
- easy in Simulink;
- good for early validation;
- easy to debug.

### Weakness

If implemented with full sorting, all capacitor voltages must be known in one controller. This is not fully decentralized. It is a distributed-looking method only if each SM uses local or neighbor-only information.

---

## 3. Consensus-based balancing

Consensus balancing makes each submodule update a local state by communicating with neighbors.

General update:

```text
x_i(k+1) = x_i(k) + α Σ a_ij [x_j(k) - x_i(k)]
```

where:

- `x_i` is the local state of SM `i`;
- `x_j` is the state received from neighbor `j`;
- `α` is the consensus gain;
- `a_ij` is the connection weight.

For voltage balancing, `x_i` can represent:

- local capacitor-voltage estimate;
- local average-voltage estimate;
- balancing correction term;
- insertion priority variable.

---

## 4. Main difference

| Item | Local rank | Consensus |
|---|---|---|
| Decision basis | Voltage order/rank | Iterative convergence |
| Information needed | local or global voltage list depending implementation | neighbor states |
| Communication | optional or simple neighbor exchange | required neighbor exchange |
| Main output | priority / sorted insertion decision | converged local correction |
| Best use | small simulation, simple balancing | fully decentralized control |
| Failure behavior | needs explicit fault skip | graph can reconfigure if connected |
| Computational load | sorting can grow with N | local update per neighbor |

---

## 5. How to move from local rank to consensus

### Step 1 — keep NLM insertion count

Keep:

```text
n_arm = round(v_arm,ref / Vc_nom)
```

This can still come from the arm-level controller.

### Step 2 — replace global sorting

Instead of global sorting:

```text
sort(Vc_1, Vc_2, ..., Vc_N)
```

each SM computes:

```text
x_i(k+1) = x_i(k) + α[(x_prev - x_i) + (x_next - x_i)]
```

for a ring network.

### Step 3 — generate local priority

Each SM computes:

```text
priority_i = Vc_i - x_i
```

where `x_i` is the local estimate of the arm average voltage.

### Step 4 — decide insertion locally

The local controller combines:

```text
n_arm, priority_i, i_arm_sign, availability_i
```

to decide whether the SM should be inserted, bypassed, or placed as a PWM boundary cell.

---

## 6. Recommended PhD implementation path

For this repository, the most realistic path is hybrid:

```text
closed-loop arm controller
        ↓
NLM insertion count
        ↓
neighbor-based local rank
        ↓
ring-leader or consensus correction
        ↓
local gate generation
```

This avoids jumping directly from a working local-rank simulation to a complex masterless consensus system. It also gives a clear scientific comparison:

1. centralized sorting;
2. local-rank neighbor balancing;
3. consensus-assisted balancing;
4. fully decentralized leaderless or rotating-leader balancing.
