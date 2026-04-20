# JSON files

Command-line combinational circuit generation requires a JSON configuration file.

The methods are described in:

1. V.V. Zunin, A.Y. Romanov, R.A. Solovyev Developing Methods for Combinational Circuit Generation, in: 2022 International Russian Automation Conference (RusAutoCon). IEEE, 2022. P. 842-846. [doi](https://doi.org/10.1109/RusAutoCon54946.2022.9896390)
2. D.A. Miachin, V.P. Pugach, S.S. Avdeiuk, V.V. Zunin, A.Y. Romanov. The Open System for Storing and Processing of a Dataset of Combinational Circuits // Proceedings of the Institute for System Programming of the RAS. 2023. Vol. 35. No. 5. P. 81-90. [doi](http://doi.org/10.15514/ISPRAS-2022-35(5)-6)

A JSON file may contain multiple generation batches:

```json
[
    {
        "generation batch 1"
    },
    {
        "generation batch 2"
    }
]
```

Each batch contains several blocks (for each parameter: type, default, whether required, and default when optional):

1. Global parameters  
   1. `multithread` (int, optional) — thread count for generation; default: 1  
2. Generation parameters — block `GenerationParameters`  
   1. `convert_to_basis` (bool, optional, default false) — whether to convert resulting graphs to a basis; if true, the basis is inferred from `gates_inputs_info`  
   2. `gates_inputs_info` (optional) — map of elements that may appear in the graph; each lists allowed input counts; currently only presence matters, not the exact count  
   3. `min_in` (int, optional, default 1) — minimum inputs  
   4. `max_in` (int, optional, default 1) — maximum inputs  
   5. `min_out` (int, optional, default 1) — minimum outputs  
   6. `max_out` (int, optional, default 1) — maximum outputs  
   7. `repeat_n` (int, optional, default 1) — repetitions per batch  
   8. `seed` (int, optional, default -1) — RNG seed; `-1` means random  
   9. **`type_of_generation`** (enum, **required**) — generator type:  
      1. `From Random Truth Table` — random truth table  
      2. `Rand Level` — random graph depth  
      3. `Rand Level Experimental` — experimental `Rand Level`  
      4. `Num Operation` — random logic operations  
      5. `Comparison` — comparator block  
      6. `Summator` — adder  
      7. `Multiplier` — multiplier  
      8. `Subtractor` — subtractor  
      9. `Multiplexer` — multiplexer  
      10. `Demultiplexer` — demultiplexer  
      11. `Encoder` — encoder  
      12. `Decoder` — decoder  
      13. `Genetic` — genetic algorithms  
      14. `Parity`  
      15. `ALU` — arithmetic logic unit  
3. Output parameters — block `OutputParameters`  
   1. `create_id_directories` (bool, optional, default false) — create per-dataset folders matching `id`  
   2. **`dataset_id`** (string, **required**) — dataset id under the dataset root  
   3. `dataset_path` (string, optional, default `"./dataset"`) — dataset directory  
   4. **`id`** (int, **required**) — subcategory id  
   5. `make_graphml_classic` (bool, optional, default false) — write classic GraphML  
   6. `make_graphml_pseudo_abc_d` (bool, optional, default false) — write pseudo-ABC GraphML  
   7. `make_graphml_open_abc_d` (bool, optional, default false) — write open-ABC GraphML  
   8. `make_dot` (bool, optional, default false) — write Graphviz DOT  
   9. `save_circuit_parameters_json` (bool, optional, default true) — when true, run circuit parameter extraction and write `<circuitName>.json` next to Verilog; when false, only emit Verilog and any other outputs enabled above (no per-circuit JSON)  
4. Type-specific blocks — required names match `type_of_generation`:  
   1. `From Random Truth Table`  
      1. `CNFF` (bool, optional, default false) — build with canonical DNF  
      2. `CNFT` (bool, optional, default false) — build with canonical CNF  
      3. `Zhegalkin` (bool, optional, default false) — build with Zhegalkin polynomial  
   2. `Rand Level`  
      1. `min_level` (int, optional, default 1) — minimum levels  
      2. `max_level` (int, optional, default 1) — maximum levels  
      3. `min_elem` (int, optional, default 1) — minimum elements  
      4. `max_elem` (int, optional, default 1) — maximum elements  
   3. `Rand Level Experimental` — same fields as `Rand Level`  
   4. `Num Operation`  
      1. `leave_empty_out` (bool, optional, default false) — allow empty outputs  
      2. `num_and` … `num_xnor` (int, optional, default 1) — counts per gate type  
   5. `Comparison`  
      1. `equal` / `less` / `more` (bool, optional, default false) — comparison ops  
   6. `Summator`  
      1. `minus` (bool, optional, default false) — negative sum  
      2. `overflowIn` / `overflowOut` (bool, optional, default false) — carry in/out ports  
   7. `Multiplier` — no extra parameters currently  
   8. `Subtractor`  
      1. `overflowIn` / `overflowOut` (bool, optional, default false)  
      2. `sub` (bool, optional, default false) — when true, subtracts the second operand  
   9. `Multiplexer` — no extra parameters currently  
   10. `Demultiplexer` — no extra parameters currently  
   11. `Encoder` — no extra parameters currently  
   12. `Decoder` — no extra parameters currently  
   13. `Genetic`  
       1. **`chromosome_type`** (string, **required**) — `TruthTableEnum`  
       2. `cycles` (int, optional, default 1) — max generation cycles  
       3. `mask_prob` (double, optional, default 1.0)  
       4. `mut_chance` (double, optional, default 0.5) — mutation probability  
       5. **`mut_type`** (string, **required**) — `Binary`, `Density`, `AccessionDel`, `InsertDel`, `Exchange`, `Delete`  
       6. `out_ratio` (double, optional, default 1.0) — termination criterion  
       7. **`playback_type`** (string, **required**) — `CrossingEachExitInTurnMany`, `CrossingUniform`, `CrossingTriadic`, `CrossingReducedReplacement`, `CrossingShuffling`  
       8. `population_size` (int, optional, default 1)  
       9. `ratio_in_table` (double, optional, default 1.0) — 0/1 distribution in the truth table  
       10. `rec_num` (int, optional, default 1) — recombination count  
       11. `ref_points` (int, optional, default 1)  
       12. **`selection_type`** (string, **required**) — `Base`  
       13. **`selection_type_parent`** (string, **required**) — `Panmixia`, `Inbringing`, `Outbrinding`, `Tournament`, `Roulette`  
       14. `surv_num` (int, optional, default 1) — survivors  
       15. `swap_type` (int, optional, default 1) — `0`, `1`, or `2`  
       16. `tour_size` (int, optional, default 1) — tournament size for `Tournament`  
   14. `Parity` — no extra parameters currently  
   15. `ALU`  
       1. `ALL` (bool, optional, default false) — enable all generator kinds (equivalent to all flags true)  
       2. `AND` (bool, optional, default false)  
       3. `NAND` (bool, optional, default false)  
       4. `OR` (bool, optional, default false)  
       5. `NOR` (bool, optional, default false)  
       6. `XOR` (bool, optional, default false)  
       7. `XNOR` (bool, optional, default false)  
       8. `SUM` (bool, optional, default false) — Summator, positive sum  
       9. `NSUM` (bool, optional, default false) — Summator, negative sum  
       10. `MULT` (bool, optional, default false) — Multiplier  
       11. `SUB` (bool, optional, default false) — Subtractor, minuend B / subtrahend A  
       12. `NSUB` (bool, optional, default false) — Subtractor, minuend A / subtrahend B  
       13. `COM` (bool, optional, default false) — Comparison  
       14. `CNF` (bool, optional, default false) — From Random Truth Table (CNFT, CNFF, Zhegalkin)  
       15. `RNL` (bool, optional, default false) — Rand Level  
       16. `NUM_OP` (bool, optional, default false) — Num Operation  
       17. `min_level` (int, optional, default 1)  
       18. `max_level` (int, optional, default 1)  
       19. `min_elem` (int, optional, default 1)  
       20. `max_elem` (int, optional, default 1)  
       21. `leave_empty_out` (bool, optional, default false)

The [sampleAll.json](../../examples/json/sampleAll.json) example lists all generation fields (except `seed`) for minimal editing.

Per-type samples in `examples/json/`:

1. [From Random Truth Table](../../examples/json/sampleTruthTable.json)  
2. [Rand Level](../../examples/json/sampleRandLevel.json)  
3. [Rand Level Experimental](../../examples/json/sampleRandLevelExperimental.json)  
4. [Num Operation](../../examples/json/sampleNumOperation.json)  
5. [Comparison](../../examples/json/sampleComparison.json)  
6. [Summator](../../examples/json/sampleGenetic.json)  
7. [Multiplier](../../examples/json/sampleMultiplier.json)  
8. [Subtractor](../../examples/json/sampleSubtractor.json)  
9. [Multiplexer](../../examples/json/sampleMultiplexer.json)  
10. [Demultiplexer](../../examples/json/sampleDemultiplexer.json)  
11. [Encoder](../../examples/json/sampleEncoder.json)  
12. [Decoder](../../examples/json/sampleDecoder.json)  
13. [Genetic](../../examples/json/sampleGenetic.json)  
14. [Parity](../../examples/json/sampleParity.json)  
15. [ALU](../../examples/json/sampleALU.json)  

**Русский:** [JSON файлы](../ru/json.md)
