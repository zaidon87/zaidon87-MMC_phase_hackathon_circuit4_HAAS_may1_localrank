# Model Notes

Main Simulink model:

```text
MMC_models/MMC_phase_hackathon_circuit4_HAAS_may1_localrank.slx
```

## Purpose

This model is the current local-rank MMC simulation baseline. It should be used as the starting point for closed-loop NLM/NLC improvement and decentralized-control migration.

## Recommended simulation checks

1. Open model in MATLAB.
2. Verify solver settings.
3. Run baseline simulation.
4. Export:
   - output voltage;
   - upper/lower arm currents;
   - capacitor voltages;
   - insertion commands;
   - gate signals.
5. Compare with the expected 5-level or intended MMC output level pattern.

## Suggested next modifications

- Separate outer controller from arm controller.
- Add closed-loop circulating-current correction.
- Add local SM controller masks.
- Replace global rank with neighbor-rank logic.
- Add consensus state as a new local variable per SM.

## File integrity

SHA256 of uploaded model at packaging time:

```text
e1e6f55c12f46838b313b6d75a7079a1b6d8472a116c7ce58edd67db2e833332
```
