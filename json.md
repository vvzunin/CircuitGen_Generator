# JSON файлы
Для генерации комбинационных схем с использованием командной строки необходимо создать JSON файл.

Набор использованных методов описан в следующих статьях:
1) V. V. Zunin, A. Y. Romanov, Solovyev R. Developing Methods for Combinational Circuit Generation, in: 2022 International Russian Automation Conference (RusAutoCon). IEEE, 2022. [doi](https://doi.org/10.1109/RusAutoCon54946.2022.9896390)

JSON файл может содержать несколько наборов генерации:
```
[
    {
        набор генерации 1
    }
    {
        набор генерации 2
    }
]
```
Для каждого набора генерации необходимо задать набор параметров:
1) Сид генерации (опциональный параметр):
   1) seed - int; сид для генератора случайных чисел, -1 или отсутствие поля для псевдослучайного сида;
2) Определение пути генерации:
   1) dataset_path - string; путь к директории для хранения датасета, опциональный параметр, по умолчанию - "./dataset"
   2) dataset_id - int; обозначение датасета схем;
   3) id - int; обозначение подкатегории датасета;
3) Общие параметры генерации:
   1) min_in - int; минимальное количество входов;
   2) max_in - int; максимальное количество входов;
   3) min_out - int; минимальное количество выходов;
   4) max_out - int; максимальное количество выходов;
   5) repeat_n - int; количества повторений для каждого набора (num_in-num_out);
4) Выбор типа генерации:
   1) Выбор происходит путем указания в "type_of_generation" типа генерации:
      1) From Random Truth Table;
      2) Rand Level;
      3) Num Operation;
      4) Genetic;
      5) ALU;
      6) 
5) В зависимости от типа генерации необходимо описать требуемые параметры:
   1) From Random Truth Table:
      1) CNFF - bool; необходимо ли создать схему с использованием СДНФ;
      2) CNFT - bool; необходимо ли создать схему с использованием СКНФ;
   2) Rand Level:
      1) max_level - int; максимальное количество уровней в схеме;
      2) max_elem - int; максимальное количество элементов на каждом уровне;
   3) Num Operation:
      1) leave_empty_out - bool; оставлять ли пустые выходы;
      2) num_<type> - int; количество элементов каждого типа из возможных: and, nand, or, nor, not, buf, xor, xnor;
   4) Genetic:
      1) chromosome_type - тип хромосомы из возможных: Truth Table;
      2) playback_type - тип рекомбинации из возможных: CrossingEachExitInTurnMany, CrossingUniform, CrossingTriadic, CrossingReducedReplacement, CrossingShuffling;
         1) selection_type_parent - тип отбора родителей: Panmixia, Inbringing, Outbrinding, Tournament, Roulette;
         2) tourSize - int; размер турнира для Tournament;
         3) ref_points - int; для CrossingEachExitInTurnMany
      3) mut_type - тип мутации хромосом из возможных: Binary, Density, AccessionDel, InsertDel, Exchange, Delete;
         1) mut_chance - float; шанс мутации;
         2) swap_type - int (0, 1 или 2);
         3) ratio_in_table - float; распределение 0 и 1 в таблице истинности;
      4) selection_type - тип отбора после мутации: Base;
      5) population_size - int; размер начальной популяции;
      6) cycles - int; максимальное количество циклов генерации;
      7) out_ratio - float; значение критерия окончания работы генетического алгоритма;
      8) mask_prob - float; RecombinationCrossingTriadic и CrossingUniform;
      9) rec_num - int; количество рекомбинаций;
      10) surv_num - int; количество выживших.
   5) Summator:
      1) overflowIn - bool; необходимо ли создать дополнительный вход (первоначальный перенос) для первого разряда генерации;
      2) overflowOut - bool; необходимо ли создать дополнительный выход (последний перенос) для последнего разряда генерации;
      3) minus - bool; выбор отрицательной суммы.
   6) Subtractor:
      1) overflowIn - bool; необходимо ли создать дополнительный вход (первоначальный заем) для первого разряда генерации;
      2) overflowOut - bool; необходимо ли создать дополнительный выход (последний заем) для последнего разряда генерации;
      3) sub - bool; выбор вычитателя и вычитаемого (при false - B-A, при true - A-B).
   7) Comparison:
      1) "=" - bool; выбор операции сравнения: равенство;
      2) "<" - bool; выбор операции сравнения: меньше;
      3) ">" - bool; выбор операции сравнения: больше.
   8) ALU:
      1) "ALL" - bool; выбор всех типов генераций из доступных (все значения ниже будут true);
      2) "SUM" - bool; выбор генерации Summator с положительной суммой; 
      3) "SUB" - bool; выбор генерации Subtractor с выбором вычитаемого B и вычитателя A;
      4) "NSUM" - bool; выбор генерации Summator с отрицательной суммой;
      5) "NSUB" - bool; выбор генерации Subtractor с выбором вычитаемого A и вычитателя B;
      6) "MULT" - bool; выбор генерации Multiplier;
      7) "COM" - bool; выбор генерации Comparison;
      8) "AND" - bool; выбор логической операции И;
      9) "NAND" - bool; выбор логической операции НЕ-И;
      10) "OR" - bool; выбор логической операции ИЛИ;
      11) "NOR" - bool; выбор логической операции НЕ-ИЛИ;
      12) "XOR" - bool; выбор логической операции Исключающее ИЛИ;
      13) "XNOR" - bool; выбор логической операции Исключающее НЕ-ИЛИ;
      14) "CNF" - bool; выбор генерации From Random Truth Table (CNFT, CNFF, Zhegalkin);
      15) "RNL" - bool; выбор генерации Rand Level;
      16) "NUM_OP" - bool; выбор генерации Num Operation.

В [примере](examples/json/sampleAll.json) JSON файла указаны все возможные параметры генерации (кроме сида), что позволяет использовать его для всех параметров генерации с минимальными изменениями.
В дополнении в той же папке имются индивидуальные JSON файлы под каждый тип генерации:
1. [From Random Truth Table](examples/json/sampleTruthTable.json)
2. [Rand Level](examples/json/sampleRandLevel.json)
3. [Rand Level Experimental](examples/json/sampleRandLevelExperimental.json)
4. [Num Operation](examples/json/sampleNumOperation.json)
5. [Genetic](examples/json/sampleGenetic.json)
6. [Summator](examples/json/sampleGenetic.json)
7. [Comparison](examples/json/sampleComparison.json)
8. [Encoder](examples/json/sampleEncoder.json)
9. [Parity](examples/json/sampleParity.json)
10. [Subtractor](examples/json/sampleSubtractor.json)
11. [Multiplexer](examples/json/sampleMultiplexer.json)
12. [Demultiplexer](examples/json/sampleDemultiplexer.json)
13. [Multiplier](examples/json/sampleMultiplier.json)
14. [Decoder](examples/json/sampleDecoder.json)
15. [ALU](examples/json/sampleALU.json)