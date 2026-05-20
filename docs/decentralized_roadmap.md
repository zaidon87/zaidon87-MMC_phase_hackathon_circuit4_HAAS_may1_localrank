# Roadmap Toward Fully Decentralized MMC Control

## Stage 1 — Repository baseline

- Store the current Simulink model in `MMC_models/`.
- Document the control architecture.
- Define requirements and simulation targets.
- Keep the model stable before adding new control layers.

## Stage 2 — Closed-loop correction

Add or verify:

- AC voltage/current feedback;
- arm-current correction;
- circulating-current control;
- soft reference ramp;
- saturation of arm references;
- anti-windup in PI loops.

Expected output:

```text
stable output voltage + balanced capacitor voltages + controlled arm currents
```

## Stage 3 — Local-rank balancing

Make the local-rank controller modular:

```text
SM_i inputs:
- Vc_i
- Vc_prev
- Vc_next
- i_arm sign
- n_arm
- availability_i

SM_i outputs:
- gate_i
- local_status_i
```

This stage reduces dependence on global sorting.

## Stage 4 — Consensus-assisted balancing

Add a consensus state:

```text
x_i(k+1) = x_i(k) + α[(x_prev - x_i) + (x_next - x_i)]
```

Then use:

```text
priority_i = Vc_i - x_i
```

This creates a distributed voltage-balancing estimate.

## Stage 5 — Fault-tolerant decentralized operation

Add:

- `availability_i`;
- local fault flag;
- neighbor timeout;
- bypass mode;
- re-normalized insertion count;
- fault skipping in ring communication.

## Stage 6 — OwnTech/TWIST migration

Move validated controller logic into `src/`:

- map ADC measurements;
- map PWM outputs;
- configure sampling period;
- add ScopeMimicry variables;
- validate timing on TWIST or Spin boards.

## Stage 7 — Scientific evaluation

Compare:

| Method | Communication | Computation | Balancing quality | Fault tolerance |
|---|---|---|---|---|
| Centralized sorting | high/global | high | strong | weak if central controller fails |
| Local rank | low/local | low | medium to strong | medium |
| Consensus | neighbor iterative | medium | strong after convergence | strong if graph connected |
| Hybrid local-rank + consensus | local/neighbor | medium | strong | strong |
