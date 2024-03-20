## Input

```
Arrival Time | Total CPU Time | CPU Burst | IO Burst 
000          | 400            | 50        | 50
101          | 300            | 41        | 40
202          | 200            | 32        | 50
303          | 100            | 23        | 10
```

## Output 

### Output Format

```
x y z: A -> B (At timestep x, the yth process transitioned from state A to state B.

x y z: READY -> RUNNG cb = k, rem = j, prio = n (At timestep x, the yth process transitioned from READY to RUNNING. At that time, it should run k units before its next IO operation and its remaining time to be executed by the CPU is j in total. And the dynamic priority is n at that moment)

x y z: RUNNG -> BLOCK ib = k, rem = j (At timestep x, the yth process transitioned from RUNNING to BLOCK. At that time, it should run k units to finish its IO operation and its remaining total time to be executed by the CPU is j)


Process ID | Arrival Time | Total CPU Time | CPU Burst | IO Burst |  Finish Time | Turnaround Time | IO Time | CPU Wait Time
0000:      | 0            | 400            | 50        | 50       | 2               |  x           | x       | x     
0001:      | 101          | 300            | 41        | 40       | 4               |  x           | x       | x 
0002:      | 202          | 200            | 32        | 50       | 2               |  x           | x       | x 
0003:      | 303          | 100            | 23        | 10       | 4               |  x           | x       | x 


     Total Simulation Time | CPU Utilization | IO Utilization | Average Turnaround Time | Average Wait Time | Throughout
SUM: x                     | x               | x              | x                       | x                 | x  
```

### FCFS 
```
0 0 0: CREATED -> READY
0 0 0: READY -> RUNNG cb=50 rem=400 prio=1
50 0 50: RUNNG -> BLOCK  ib=27 rem=350
77 0 27: BLOCK -> READY
77 0 0: READY -> RUNNG cb=17 rem=350 prio=1
94 0 17: RUNNG -> BLOCK  ib=9 rem=333
101 1 0: CREATED -> READY
101 1 0: READY -> RUNNG cb=35 rem=300 prio=3
103 0 9: BLOCK -> READY
136 1 35: RUNNG -> BLOCK  ib=21 rem=265
136 0 33: READY -> RUNNG cb=49 rem=333 prio=1
157 1 21: BLOCK -> READY
185 0 49: RUNNG -> BLOCK  ib=19 rem=284
185 1 28: READY -> RUNNG cb=4 rem=265 prio=3
189 1 4: RUNNG -> BLOCK  ib=4 rem=261
193 1 4: BLOCK -> READY
193 1 0: READY -> RUNNG cb=14 rem=261 prio=3
202 2 0: CREATED -> READY
204 0 19: BLOCK -> READY
207 1 14: RUNNG -> BLOCK  ib=2 rem=247
207 2 5: READY -> RUNNG cb=18 rem=200 prio=1
209 1 2: BLOCK -> READY
225 2 18: RUNNG -> BLOCK  ib=34 rem=182
225 0 21: READY -> RUNNG cb=22 rem=284 prio=1
247 0 22: RUNNG -> BLOCK  ib=16 rem=262
247 1 38: READY -> RUNNG cb=6 rem=247 prio=3
253 1 6: RUNNG -> BLOCK  ib=25 rem=241
259 2 34: BLOCK -> READY
259 2 0: READY -> RUNNG cb=23 rem=182 prio=1
263 0 16: BLOCK -> READY
278 1 25: BLOCK -> READY
282 2 23: RUNNG -> BLOCK  ib=20 rem=159
282 0 19: READY -> RUNNG cb=2 rem=262 prio=1
284 0 2: RUNNG -> BLOCK  ib=47 rem=260
284 1 6: READY -> RUNNG cb=27 rem=241 prio=3
302 2 20: BLOCK -> READY
303 3 0: CREATED -> READY
311 1 27: RUNNG -> BLOCK  ib=5 rem=214
311 2 9: READY -> RUNNG cb=27 rem=159 prio=1
316 1 5: BLOCK -> READY
331 0 47: BLOCK -> READY
338 2 27: RUNNG -> BLOCK  ib=32 rem=132
338 3 35: READY -> RUNNG cb=23 rem=100 prio=3
361 3 23: RUNNG -> BLOCK  ib=9 rem=77
361 1 45: READY -> RUNNG cb=25 rem=214 prio=3
370 2 32: BLOCK -> READY
370 3 9: BLOCK -> READY
386 1 25: RUNNG -> BLOCK  ib=19 rem=189
386 0 55: READY -> RUNNG cb=10 rem=260 prio=1
396 0 10: RUNNG -> BLOCK  ib=10 rem=250
396 2 26: READY -> RUNNG cb=7 rem=132 prio=1
403 2 7: RUNNG -> BLOCK  ib=28 rem=125
403 3 33: READY -> RUNNG cb=5 rem=77 prio=3
405 1 19: BLOCK -> READY
406 0 10: BLOCK -> READY
408 3 5: RUNNG -> BLOCK  ib=4 rem=72
408 1 3: READY -> RUNNG cb=1 rem=189 prio=3
409 1 1: RUNNG -> BLOCK  ib=18 rem=188
409 0 3: READY -> RUNNG cb=14 rem=250 prio=1
412 3 4: BLOCK -> READY
423 0 14: RUNNG -> BLOCK  ib=21 rem=236
423 3 11: READY -> RUNNG cb=14 rem=72 prio=3
427 1 18: BLOCK -> READY
431 2 28: BLOCK -> READY
437 3 14: RUNNG -> BLOCK  ib=9 rem=58
437 1 10: READY -> RUNNG cb=23 rem=188 prio=3
444 0 21: BLOCK -> READY
446 3 9: BLOCK -> READY
460 1 23: RUNNG -> BLOCK  ib=7 rem=165
460 2 29: READY -> RUNNG cb=1 rem=125 prio=1
461 2 1: RUNNG -> BLOCK  ib=26 rem=124
461 0 17: READY -> RUNNG cb=22 rem=236 prio=1
467 1 7: BLOCK -> READY
483 0 22: RUNNG -> BLOCK  ib=33 rem=214
483 3 37: READY -> RUNNG cb=13 rem=58 prio=3
487 2 26: BLOCK -> READY
496 3 13: RUNNG -> BLOCK  ib=3 rem=45
496 1 29: READY -> RUNNG cb=9 rem=165 prio=3
499 3 3: BLOCK -> READY
505 1 9: RUNNG -> BLOCK  ib=2 rem=156
505 2 18: READY -> RUNNG cb=17 rem=124 prio=1
507 1 2: BLOCK -> READY
516 0 33: BLOCK -> READY
522 2 17: RUNNG -> BLOCK  ib=46 rem=107
522 3 23: READY -> RUNNG cb=12 rem=45 prio=3
534 3 12: RUNNG -> BLOCK  ib=7 rem=33
534 1 27: READY -> RUNNG cb=24 rem=156 prio=3
541 3 7: BLOCK -> READY
558 1 24: RUNNG -> BLOCK  ib=31 rem=132
558 0 42: READY -> RUNNG cb=17 rem=214 prio=1
568 2 46: BLOCK -> READY
575 0 17: RUNNG -> BLOCK  ib=40 rem=197
575 3 34: READY -> RUNNG cb=10 rem=33 prio=3
585 3 10: RUNNG -> BLOCK  ib=8 rem=23
585 2 17: READY -> RUNNG cb=27 rem=107 prio=1
589 1 31: BLOCK -> READY
593 3 8: BLOCK -> READY
612 2 27: RUNNG -> BLOCK  ib=38 rem=80
612 1 23: READY -> RUNNG cb=9 rem=132 prio=3
615 0 40: BLOCK -> READY
621 1 9: RUNNG -> BLOCK  ib=21 rem=123
621 3 28: READY -> RUNNG cb=6 rem=23 prio=3
627 3 6: RUNNG -> BLOCK  ib=8 rem=17
627 0 12: READY -> RUNNG cb=38 rem=197 prio=1
635 3 8: BLOCK -> READY
642 1 21: BLOCK -> READY
650 2 38: BLOCK -> READY
665 0 38: RUNNG -> BLOCK  ib=44 rem=159
665 3 30: READY -> RUNNG cb=17 rem=17 prio=3
682 3 17: Done
682 1 40: READY -> RUNNG cb=36 rem=123 prio=3
709 0 44: BLOCK -> READY
718 1 36: RUNNG -> BLOCK  ib=22 rem=87
718 2 68: READY -> RUNNG cb=20 rem=80 prio=1
738 2 20: RUNNG -> BLOCK  ib=20 rem=60
738 0 29: READY -> RUNNG cb=24 rem=159 prio=1
740 1 22: BLOCK -> READY
758 2 20: BLOCK -> READY
762 0 24: RUNNG -> BLOCK  ib=49 rem=135
762 1 22: READY -> RUNNG cb=32 rem=87 prio=3
794 1 32: RUNNG -> BLOCK  ib=19 rem=55
794 2 36: READY -> RUNNG cb=19 rem=60 prio=1
811 0 49: BLOCK -> READY
813 1 19: BLOCK -> READY
813 2 19: RUNNG -> BLOCK  ib=35 rem=41
813 0 2: READY -> RUNNG cb=10 rem=135 prio=1
823 0 10: RUNNG -> BLOCK  ib=12 rem=125
823 1 10: READY -> RUNNG cb=18 rem=55 prio=3
835 0 12: BLOCK -> READY
841 1 18: RUNNG -> BLOCK  ib=28 rem=37
841 0 6: READY -> RUNNG cb=1 rem=125 prio=1
842 0 1: RUNNG -> BLOCK  ib=44 rem=124
848 2 35: BLOCK -> READY
848 2 0: READY -> RUNNG cb=6 rem=41 prio=1
854 2 6: RUNNG -> BLOCK  ib=23 rem=35
869 1 28: BLOCK -> READY
869 1 0: READY -> RUNNG cb=1 rem=37 prio=3
870 1 1: RUNNG -> BLOCK  ib=25 rem=36
877 2 23: BLOCK -> READY
877 2 0: READY -> RUNNG cb=23 rem=35 prio=1
886 0 44: BLOCK -> READY
895 1 25: BLOCK -> READY
900 2 23: RUNNG -> BLOCK  ib=40 rem=12
900 0 14: READY -> RUNNG cb=26 rem=124 prio=1
926 0 26: RUNNG -> BLOCK  ib=50 rem=98
926 1 31: READY -> RUNNG cb=35 rem=36 prio=3
940 2 40: BLOCK -> READY
961 1 35: RUNNG -> BLOCK  ib=16 rem=1
961 2 21: READY -> RUNNG cb=10 rem=12 prio=1
971 2 10: RUNNG -> BLOCK  ib=44 rem=2
976 0 50: BLOCK -> READY
976 0 0: READY -> RUNNG cb=35 rem=98 prio=1
977 1 16: BLOCK -> READY
1011 0 35: RUNNG -> BLOCK  ib=25 rem=63
1011 1 34: READY -> RUNNG cb=1 rem=1 prio=3
1012 1 1: Done
1015 2 44: BLOCK -> READY
1015 2 0: READY -> RUNNG cb=2 rem=2 prio=1
1017 2 2: Done
1036 0 25: BLOCK -> READY
1036 0 0: READY -> RUNNG cb=17 rem=63 prio=1
1053 0 17: RUNNG -> BLOCK  ib=37 rem=46
1090 0 37: BLOCK -> READY
1090 0 0: READY -> RUNNG cb=17 rem=46 prio=1
1107 0 17: RUNNG -> BLOCK  ib=42 rem=29
1149 0 42: BLOCK -> READY
1149 0 0: READY -> RUNNG cb=29 rem=29 prio=1
1178 0 29: Done
FCFS
0000:    0  400   50   50 2 |  1178  1178   525   253
0001:  101  300   41   40 4 |  1012   911   265   346
0002:  202  200   32   50 2 |  1017   815   386   229
0003:  303  100   23   10 4 |   682   379    48   231
SUM: 1178 84.89 75.38 820.75 264.75 0.340
```

### Shortest Job First 

```
0 0 0: CREATED -> READY
0 0 0: READY -> RUNNG cb=50 rem=400 prio=1
50 0 50: RUNNG -> BLOCK  ib=27 rem=350
77 0 27: BLOCK -> READY
77 0 0: READY -> RUNNG cb=17 rem=350 prio=1
94 0 17: RUNNG -> BLOCK  ib=9 rem=333
101 1 0: CREATED -> READY
101 1 0: READY -> RUNNG cb=35 rem=300 prio=3
103 0 9: BLOCK -> READY
136 1 35: RUNNG -> BLOCK  ib=21 rem=265
136 0 33: READY -> RUNNG cb=49 rem=333 prio=1
157 1 21: BLOCK -> READY
185 0 49: RUNNG -> BLOCK  ib=19 rem=284
185 1 28: READY -> RUNNG cb=4 rem=265 prio=3
189 1 4: RUNNG -> BLOCK  ib=4 rem=261
193 1 4: BLOCK -> READY
193 1 0: READY -> RUNNG cb=14 rem=261 prio=3
202 2 0: CREATED -> READY
204 0 19: BLOCK -> READY
207 1 14: RUNNG -> BLOCK  ib=2 rem=247
207 2 5: READY -> RUNNG cb=18 rem=200 prio=1
209 1 2: BLOCK -> READY
225 2 18: RUNNG -> BLOCK  ib=34 rem=182
225 1 16: READY -> RUNNG cb=22 rem=247 prio=3
247 1 22: RUNNG -> BLOCK  ib=36 rem=225
247 0 43: READY -> RUNNG cb=49 rem=284 prio=1
259 2 34: BLOCK -> READY
283 1 36: BLOCK -> READY
296 0 49: RUNNG -> BLOCK  ib=5 rem=235
296 2 37: READY -> RUNNG cb=23 rem=182 prio=1
301 0 5: BLOCK -> READY
303 3 0: CREATED -> READY
319 2 23: RUNNG -> BLOCK  ib=20 rem=159
319 3 16: READY -> RUNNG cb=11 rem=100 prio=3
330 3 11: RUNNG -> BLOCK  ib=7 rem=89
330 1 47: READY -> RUNNG cb=27 rem=225 prio=3
337 3 7: BLOCK -> READY
339 2 20: BLOCK -> READY
357 1 27: RUNNG -> BLOCK  ib=5 rem=198
357 3 20: READY -> RUNNG cb=10 rem=89 prio=3
362 1 5: BLOCK -> READY
367 3 10: RUNNG -> BLOCK  ib=2 rem=79
367 2 28: READY -> RUNNG cb=10 rem=159 prio=1
369 3 2: BLOCK -> READY
377 2 10: RUNNG -> BLOCK  ib=49 rem=149
377 3 8: READY -> RUNNG cb=3 rem=79 prio=3
380 3 3: RUNNG -> BLOCK  ib=9 rem=76
380 1 18: READY -> RUNNG cb=18 rem=198 prio=3
389 3 9: BLOCK -> READY
398 1 18: RUNNG -> BLOCK  ib=40 rem=180
398 3 9: READY -> RUNNG cb=2 rem=76 prio=3
400 3 2: RUNNG -> BLOCK  ib=8 rem=74
400 0 99: READY -> RUNNG cb=20 rem=235 prio=1
408 3 8: BLOCK -> READY
420 0 20: RUNNG -> BLOCK  ib=44 rem=215
420 3 12: READY -> RUNNG cb=19 rem=74 prio=3
426 2 49: BLOCK -> READY
438 1 40: BLOCK -> READY
439 3 19: RUNNG -> BLOCK  ib=8 rem=55
439 2 13: READY -> RUNNG cb=12 rem=149 prio=1
447 3 8: BLOCK -> READY
451 2 12: RUNNG -> BLOCK  ib=21 rem=137
451 3 4: READY -> RUNNG cb=14 rem=55 prio=3
464 0 44: BLOCK -> READY
465 3 14: RUNNG -> BLOCK  ib=9 rem=41
465 1 27: READY -> RUNNG cb=23 rem=180 prio=3
472 2 21: BLOCK -> READY
474 3 9: BLOCK -> READY
488 1 23: RUNNG -> BLOCK  ib=7 rem=157
488 3 14: READY -> RUNNG cb=2 rem=41 prio=3
490 3 2: RUNNG -> BLOCK  ib=6 rem=39
490 2 18: READY -> RUNNG cb=10 rem=137 prio=1
495 1 7: BLOCK -> READY
496 3 6: BLOCK -> READY
500 2 10: RUNNG -> BLOCK  ib=33 rem=127
500 3 4: READY -> RUNNG cb=13 rem=39 prio=3
513 3 13: RUNNG -> BLOCK  ib=3 rem=26
513 1 18: READY -> RUNNG cb=9 rem=157 prio=3
516 3 3: BLOCK -> READY
522 1 9: RUNNG -> BLOCK  ib=2 rem=148
522 3 6: READY -> RUNNG cb=14 rem=26 prio=3
524 1 2: BLOCK -> READY
533 2 33: BLOCK -> READY
536 3 14: RUNNG -> BLOCK  ib=6 rem=12
536 2 3: READY -> RUNNG cb=22 rem=127 prio=1
542 3 6: BLOCK -> READY
558 2 22: RUNNG -> BLOCK  ib=17 rem=105
558 3 16: READY -> RUNNG cb=5 rem=12 prio=3
563 3 5: RUNNG -> BLOCK  ib=1 rem=7
563 1 39: READY -> RUNNG cb=6 rem=148 prio=3
564 3 1: BLOCK -> READY
569 1 6: RUNNG -> BLOCK  ib=20 rem=142
569 3 5: READY -> RUNNG cb=7 rem=7 prio=3
575 2 17: BLOCK -> READY
576 3 7: Done
576 2 1: READY -> RUNNG cb=10 rem=105 prio=1
586 2 10: RUNNG -> BLOCK  ib=49 rem=95
586 0 122: READY -> RUNNG cb=38 rem=215 prio=1
589 1 20: BLOCK -> READY
624 0 38: RUNNG -> BLOCK  ib=8 rem=177
624 1 35: READY -> RUNNG cb=33 rem=142 prio=3
632 0 8: BLOCK -> READY
635 2 49: BLOCK -> READY
657 1 33: RUNNG -> BLOCK  ib=21 rem=109
657 2 22: READY -> RUNNG cb=30 rem=95 prio=1
678 1 21: BLOCK -> READY
687 2 30: RUNNG -> BLOCK  ib=38 rem=65
687 1 9: READY -> RUNNG cb=35 rem=109 prio=3
722 1 35: RUNNG -> BLOCK  ib=40 rem=74
722 0 90: READY -> RUNNG cb=13 rem=177 prio=1
725 2 38: BLOCK -> READY
735 0 13: RUNNG -> BLOCK  ib=42 rem=164
735 2 10: READY -> RUNNG cb=20 rem=65 prio=1
755 2 20: RUNNG -> BLOCK  ib=20 rem=45
762 1 40: BLOCK -> READY
762 1 0: READY -> RUNNG cb=12 rem=74 prio=3
774 1 12: RUNNG -> BLOCK  ib=19 rem=62
775 2 20: BLOCK -> READY
775 2 0: READY -> RUNNG cb=3 rem=45 prio=1
777 0 42: BLOCK -> READY
778 2 3: RUNNG -> BLOCK  ib=9 rem=42
778 0 1: READY -> RUNNG cb=31 rem=164 prio=1
787 2 9: BLOCK -> READY
793 1 19: BLOCK -> READY
809 0 31: RUNNG -> BLOCK  ib=35 rem=133
809 2 22: READY -> RUNNG cb=28 rem=42 prio=1
837 2 28: RUNNG -> BLOCK  ib=12 rem=14
837 1 44: READY -> RUNNG cb=18 rem=62 prio=3
844 0 35: BLOCK -> READY
849 2 12: BLOCK -> READY
855 1 18: RUNNG -> BLOCK  ib=28 rem=44
855 2 6: READY -> RUNNG cb=14 rem=14 prio=1
869 2 14: Done
869 0 25: READY -> RUNNG cb=44 rem=133 prio=1
883 1 28: BLOCK -> READY
913 0 44: RUNNG -> BLOCK  ib=36 rem=89
913 1 30: READY -> RUNNG cb=40 rem=44 prio=3
949 0 36: BLOCK -> READY
953 1 40: RUNNG -> BLOCK  ib=31 rem=4
953 0 4: READY -> RUNNG cb=25 rem=89 prio=1
978 0 25: RUNNG -> BLOCK  ib=13 rem=64
984 1 31: BLOCK -> READY
984 1 0: READY -> RUNNG cb=4 rem=4 prio=3
988 1 4: Done
991 0 13: BLOCK -> READY
991 0 0: READY -> RUNNG cb=26 rem=64 prio=1
1017 0 26: RUNNG -> BLOCK  ib=50 rem=38
1067 0 50: BLOCK -> READY
1067 0 0: READY -> RUNNG cb=38 rem=38 prio=1
1105 0 38: Done
SRTF
0000:    0  400   50   50 2 |  1105  1105   288   417
0001:  101  300   41   40 4 |   988   887   276   311
0002:  202  200   32   50 2 |   869   667   302   165
0003:  303  100   23   10 4 |   576   273    59   114
SUM: 1105 90.50 64.07 733.00 251.75 0.362
```

### Round Robin (Time Quantum = 10) 

```
0 0 0: CREATED -> READY
0 0 0: READY -> RUNNG cb=50 rem=400 prio=1
10 0 10: RUNNG -> READY  cb=40 rem=390 prio=1
10 0 0: READY -> RUNNG cb=40 rem=390 prio=1
20 0 10: RUNNG -> READY  cb=30 rem=380 prio=1
20 0 0: READY -> RUNNG cb=30 rem=380 prio=1
30 0 10: RUNNG -> READY  cb=20 rem=370 prio=1
30 0 0: READY -> RUNNG cb=20 rem=370 prio=1
40 0 10: RUNNG -> READY  cb=10 rem=360 prio=1
40 0 0: READY -> RUNNG cb=10 rem=360 prio=1
50 0 10: RUNNG -> BLOCK  ib=27 rem=350
77 0 27: BLOCK -> READY
77 0 0: READY -> RUNNG cb=17 rem=350 prio=1
87 0 10: RUNNG -> READY  cb=7 rem=340 prio=1
87 0 0: READY -> RUNNG cb=7 rem=340 prio=1
94 0 7: RUNNG -> BLOCK  ib=9 rem=333
101 1 0: CREATED -> READY
101 1 0: READY -> RUNNG cb=35 rem=300 prio=3
103 0 9: BLOCK -> READY
111 1 10: RUNNG -> READY  cb=25 rem=290 prio=3
111 0 8: READY -> RUNNG cb=11 rem=333 prio=1
121 0 10: RUNNG -> READY  cb=1 rem=323 prio=1
121 1 10: READY -> RUNNG cb=25 rem=290 prio=3
131 1 10: RUNNG -> READY  cb=15 rem=280 prio=3
131 0 10: READY -> RUNNG cb=1 rem=323 prio=1
132 0 1: RUNNG -> BLOCK  ib=49 rem=322
132 1 1: READY -> RUNNG cb=15 rem=280 prio=3
142 1 10: RUNNG -> READY  cb=5 rem=270 prio=3
142 1 0: READY -> RUNNG cb=5 rem=270 prio=3
147 1 5: RUNNG -> BLOCK  ib=39 rem=265
181 0 49: BLOCK -> READY
181 0 0: READY -> RUNNG cb=31 rem=322 prio=1
186 1 39: BLOCK -> READY
191 0 10: RUNNG -> READY  cb=21 rem=312 prio=1
191 1 5: READY -> RUNNG cb=11 rem=265 prio=3
201 1 10: RUNNG -> READY  cb=1 rem=255 prio=3
201 0 10: READY -> RUNNG cb=21 rem=312 prio=1
202 2 0: CREATED -> READY
211 0 10: RUNNG -> READY  cb=11 rem=302 prio=1
211 1 10: READY -> RUNNG cb=1 rem=255 prio=3
212 1 1: RUNNG -> BLOCK  ib=36 rem=254
212 2 10: READY -> RUNNG cb=2 rem=200 prio=1
214 2 2: RUNNG -> BLOCK  ib=32 rem=198
214 0 3: READY -> RUNNG cb=11 rem=302 prio=1
224 0 10: RUNNG -> READY  cb=1 rem=292 prio=1
224 0 0: READY -> RUNNG cb=1 rem=292 prio=1
225 0 1: RUNNG -> BLOCK  ib=34 rem=291
246 2 32: BLOCK -> READY
246 2 0: READY -> RUNNG cb=28 rem=198 prio=1
248 1 36: BLOCK -> READY
256 2 10: RUNNG -> READY  cb=18 rem=188 prio=1
256 1 8: READY -> RUNNG cb=36 rem=254 prio=3
259 0 34: BLOCK -> READY
266 1 10: RUNNG -> READY  cb=26 rem=244 prio=3
266 2 10: READY -> RUNNG cb=18 rem=188 prio=1
276 2 10: RUNNG -> READY  cb=8 rem=178 prio=1
276 0 17: READY -> RUNNG cb=49 rem=291 prio=1
286 0 10: RUNNG -> READY  cb=39 rem=281 prio=1
286 1 20: READY -> RUNNG cb=26 rem=244 prio=3
296 1 10: RUNNG -> READY  cb=16 rem=234 prio=3
296 2 20: READY -> RUNNG cb=8 rem=178 prio=1
303 3 0: CREATED -> READY
304 2 8: RUNNG -> BLOCK  ib=5 rem=170
304 0 18: READY -> RUNNG cb=39 rem=281 prio=1
309 2 5: BLOCK -> READY
314 0 10: RUNNG -> READY  cb=29 rem=271 prio=1
314 1 18: READY -> RUNNG cb=16 rem=234 prio=3
324 1 10: RUNNG -> READY  cb=6 rem=224 prio=3
324 3 21: READY -> RUNNG cb=5 rem=100 prio=3
329 3 5: RUNNG -> BLOCK  ib=10 rem=95
329 2 20: READY -> RUNNG cb=26 rem=170 prio=1
339 3 10: BLOCK -> READY
339 2 10: RUNNG -> READY  cb=16 rem=160 prio=1
339 0 25: READY -> RUNNG cb=29 rem=271 prio=1
349 0 10: RUNNG -> READY  cb=19 rem=261 prio=1
349 1 25: READY -> RUNNG cb=6 rem=224 prio=3
355 1 6: RUNNG -> BLOCK  ib=17 rem=218
355 3 16: READY -> RUNNG cb=13 rem=95 prio=3
365 3 10: RUNNG -> READY  cb=3 rem=85 prio=3
365 2 26: READY -> RUNNG cb=16 rem=160 prio=1
372 1 17: BLOCK -> READY
375 2 10: RUNNG -> READY  cb=6 rem=150 prio=1
375 0 26: READY -> RUNNG cb=19 rem=261 prio=1
385 0 10: RUNNG -> READY  cb=9 rem=251 prio=1
385 3 20: READY -> RUNNG cb=3 rem=85 prio=3
388 3 3: RUNNG -> BLOCK  ib=5 rem=82
388 1 16: READY -> RUNNG cb=21 rem=218 prio=3
393 3 5: BLOCK -> READY
398 1 10: RUNNG -> READY  cb=11 rem=208 prio=3
398 2 23: READY -> RUNNG cb=6 rem=150 prio=1
404 2 6: RUNNG -> BLOCK  ib=32 rem=144
404 0 19: READY -> RUNNG cb=9 rem=251 prio=1
413 0 9: RUNNG -> BLOCK  ib=32 rem=242
413 3 20: READY -> RUNNG cb=6 rem=82 prio=3
419 3 6: RUNNG -> BLOCK  ib=1 rem=76
419 1 21: READY -> RUNNG cb=11 rem=208 prio=3
420 3 1: BLOCK -> READY
429 1 10: RUNNG -> READY  cb=1 rem=198 prio=3
429 3 9: READY -> RUNNG cb=12 rem=76 prio=3
436 2 32: BLOCK -> READY
439 3 10: RUNNG -> READY  cb=2 rem=66 prio=3
439 1 10: READY -> RUNNG cb=1 rem=198 prio=3
440 1 1: RUNNG -> BLOCK  ib=10 rem=197
440 2 4: READY -> RUNNG cb=32 rem=144 prio=1
445 0 32: BLOCK -> READY
450 1 10: BLOCK -> READY
450 2 10: RUNNG -> READY  cb=22 rem=134 prio=1
450 3 11: READY -> RUNNG cb=2 rem=66 prio=3
452 3 2: RUNNG -> BLOCK  ib=5 rem=64
452 0 7: READY -> RUNNG cb=28 rem=242 prio=1
457 3 5: BLOCK -> READY
462 0 10: RUNNG -> READY  cb=18 rem=232 prio=1
462 1 12: READY -> RUNNG cb=32 rem=197 prio=3
472 1 10: RUNNG -> READY  cb=22 rem=187 prio=3
472 2 22: READY -> RUNNG cb=22 rem=134 prio=1
482 2 10: RUNNG -> READY  cb=12 rem=124 prio=1
482 3 25: READY -> RUNNG cb=1 rem=64 prio=3
483 3 1: RUNNG -> BLOCK  ib=1 rem=63
483 0 21: READY -> RUNNG cb=18 rem=232 prio=1
484 3 1: BLOCK -> READY
493 0 10: RUNNG -> READY  cb=8 rem=222 prio=1
493 1 21: READY -> RUNNG cb=22 rem=187 prio=3
503 1 10: RUNNG -> READY  cb=12 rem=177 prio=3
503 2 21: READY -> RUNNG cb=12 rem=124 prio=1
513 2 10: RUNNG -> READY  cb=2 rem=114 prio=1
513 3 29: READY -> RUNNG cb=15 rem=63 prio=3
523 3 10: RUNNG -> READY  cb=5 rem=53 prio=3
523 0 30: READY -> RUNNG cb=8 rem=222 prio=1
531 0 8: RUNNG -> BLOCK  ib=14 rem=214
531 1 28: READY -> RUNNG cb=12 rem=177 prio=3
541 1 10: RUNNG -> READY  cb=2 rem=167 prio=3
541 2 28: READY -> RUNNG cb=2 rem=114 prio=1
543 2 2: RUNNG -> BLOCK  ib=21 rem=112
543 3 20: READY -> RUNNG cb=5 rem=53 prio=3
545 0 14: BLOCK -> READY
548 3 5: RUNNG -> BLOCK  ib=4 rem=48
548 1 7: READY -> RUNNG cb=2 rem=167 prio=3
550 1 2: RUNNG -> BLOCK  ib=39 rem=165
550 0 5: READY -> RUNNG cb=3 rem=214 prio=1
552 3 4: BLOCK -> READY
553 0 3: RUNNG -> BLOCK  ib=7 rem=211
553 3 1: READY -> RUNNG cb=2 rem=48 prio=3
555 3 2: RUNNG -> BLOCK  ib=6 rem=46
560 0 7: BLOCK -> READY
560 0 0: READY -> RUNNG cb=22 rem=211 prio=1
561 3 6: BLOCK -> READY
564 2 21: BLOCK -> READY
570 0 10: RUNNG -> READY  cb=12 rem=201 prio=1
570 3 9: READY -> RUNNG cb=5 rem=46 prio=3
575 3 5: RUNNG -> BLOCK  ib=10 rem=41
575 2 11: READY -> RUNNG cb=1 rem=112 prio=1
576 2 1: RUNNG -> BLOCK  ib=2 rem=111
576 0 6: READY -> RUNNG cb=12 rem=201 prio=1
578 2 2: BLOCK -> READY
585 3 10: BLOCK -> READY
586 0 10: RUNNG -> READY  cb=2 rem=191 prio=1
586 2 8: READY -> RUNNG cb=18 rem=111 prio=1
589 1 39: BLOCK -> READY
596 2 10: RUNNG -> READY  cb=8 rem=101 prio=1
596 3 11: READY -> RUNNG cb=14 rem=41 prio=3
606 3 10: RUNNG -> READY  cb=4 rem=31 prio=3
606 0 20: READY -> RUNNG cb=2 rem=191 prio=1
608 0 2: RUNNG -> BLOCK  ib=46 rem=189
608 1 19: READY -> RUNNG cb=5 rem=165 prio=3
613 1 5: RUNNG -> BLOCK  ib=27 rem=160
613 2 17: READY -> RUNNG cb=8 rem=101 prio=1
621 2 8: RUNNG -> BLOCK  ib=29 rem=93
621 3 15: READY -> RUNNG cb=4 rem=31 prio=3
625 3 4: RUNNG -> BLOCK  ib=1 rem=27
626 3 1: BLOCK -> READY
626 3 0: READY -> RUNNG cb=22 rem=27 prio=3
636 3 10: RUNNG -> READY  cb=12 rem=17 prio=3
636 3 0: READY -> RUNNG cb=12 rem=17 prio=3
640 1 27: BLOCK -> READY
646 3 10: RUNNG -> READY  cb=2 rem=7 prio=3
646 1 6: READY -> RUNNG cb=8 rem=160 prio=3
650 2 29: BLOCK -> READY
654 0 46: BLOCK -> READY
654 1 8: RUNNG -> BLOCK  ib=1 rem=152
654 3 8: READY -> RUNNG cb=2 rem=7 prio=3
655 1 1: BLOCK -> READY
656 3 2: RUNNG -> BLOCK  ib=8 rem=5
656 2 6: READY -> RUNNG cb=27 rem=93 prio=1
664 3 8: BLOCK -> READY
666 2 10: RUNNG -> READY  cb=17 rem=83 prio=1
666 0 12: READY -> RUNNG cb=38 rem=189 prio=1
676 0 10: RUNNG -> READY  cb=28 rem=179 prio=1
676 1 21: READY -> RUNNG cb=9 rem=152 prio=3
685 1 9: RUNNG -> BLOCK  ib=21 rem=143
685 3 21: READY -> RUNNG cb=5 rem=5 prio=3
690 3 5: Done
690 2 24: READY -> RUNNG cb=17 rem=83 prio=1
700 2 10: RUNNG -> READY  cb=7 rem=73 prio=1
700 0 24: READY -> RUNNG cb=28 rem=179 prio=1
706 1 21: BLOCK -> READY
710 0 10: RUNNG -> READY  cb=18 rem=169 prio=1
710 2 10: READY -> RUNNG cb=7 rem=73 prio=1
717 2 7: RUNNG -> BLOCK  ib=48 rem=66
717 1 11: READY -> RUNNG cb=27 rem=143 prio=3
727 1 10: RUNNG -> READY  cb=17 rem=133 prio=3
727 0 17: READY -> RUNNG cb=18 rem=169 prio=1
737 0 10: RUNNG -> READY  cb=8 rem=159 prio=1
737 1 10: READY -> RUNNG cb=17 rem=133 prio=3
747 1 10: RUNNG -> READY  cb=7 rem=123 prio=3
747 0 10: READY -> RUNNG cb=8 rem=159 prio=1
755 0 8: RUNNG -> BLOCK  ib=44 rem=151
755 1 8: READY -> RUNNG cb=7 rem=123 prio=3
762 1 7: RUNNG -> BLOCK  ib=40 rem=116
765 2 48: BLOCK -> READY
765 2 0: READY -> RUNNG cb=3 rem=66 prio=1
768 2 3: RUNNG -> BLOCK  ib=42 rem=63
799 0 44: BLOCK -> READY
799 0 0: READY -> RUNNG cb=24 rem=151 prio=1
802 1 40: BLOCK -> READY
809 0 10: RUNNG -> READY  cb=14 rem=141 prio=1
809 1 7: READY -> RUNNG cb=17 rem=116 prio=3
810 2 42: BLOCK -> READY
819 1 10: RUNNG -> READY  cb=7 rem=106 prio=3
819 0 10: READY -> RUNNG cb=14 rem=141 prio=1
829 0 10: RUNNG -> READY  cb=4 rem=131 prio=1
829 2 19: READY -> RUNNG cb=6 rem=63 prio=1
835 2 6: RUNNG -> BLOCK  ib=49 rem=57
835 1 16: READY -> RUNNG cb=7 rem=106 prio=3
842 1 7: RUNNG -> BLOCK  ib=11 rem=99
842 0 13: READY -> RUNNG cb=4 rem=131 prio=1
846 0 4: RUNNG -> BLOCK  ib=9 rem=127
853 1 11: BLOCK -> READY
853 1 0: READY -> RUNNG cb=6 rem=99 prio=3
855 0 9: BLOCK -> READY
859 1 6: RUNNG -> BLOCK  ib=35 rem=93
859 0 4: READY -> RUNNG cb=10 rem=127 prio=1
869 0 10: RUNNG -> BLOCK  ib=12 rem=117
881 0 12: BLOCK -> READY
881 0 0: READY -> RUNNG cb=26 rem=117 prio=1
884 2 49: BLOCK -> READY
891 0 10: RUNNG -> READY  cb=16 rem=107 prio=1
891 2 7: READY -> RUNNG cb=20 rem=57 prio=1
894 1 35: BLOCK -> READY
901 2 10: RUNNG -> READY  cb=10 rem=47 prio=1
901 0 10: READY -> RUNNG cb=16 rem=107 prio=1
911 0 10: RUNNG -> READY  cb=6 rem=97 prio=1
911 1 17: READY -> RUNNG cb=5 rem=93 prio=3
916 1 5: RUNNG -> BLOCK  ib=14 rem=88
916 2 15: READY -> RUNNG cb=10 rem=47 prio=1
926 2 10: RUNNG -> BLOCK  ib=36 rem=37
926 0 15: READY -> RUNNG cb=6 rem=97 prio=1
930 1 14: BLOCK -> READY
932 0 6: RUNNG -> BLOCK  ib=23 rem=91
932 1 2: READY -> RUNNG cb=1 rem=88 prio=3
933 1 1: RUNNG -> BLOCK  ib=25 rem=87
955 0 23: BLOCK -> READY
955 0 0: READY -> RUNNG cb=13 rem=91 prio=1
958 1 25: BLOCK -> READY
962 2 36: BLOCK -> READY
965 0 10: RUNNG -> READY  cb=3 rem=81 prio=1
965 1 7: READY -> RUNNG cb=27 rem=87 prio=3
975 1 10: RUNNG -> READY  cb=17 rem=77 prio=3
975 2 13: READY -> RUNNG cb=28 rem=37 prio=1
985 2 10: RUNNG -> READY  cb=18 rem=27 prio=1
985 0 20: READY -> RUNNG cb=3 rem=81 prio=1
988 0 3: RUNNG -> BLOCK  ib=50 rem=78
988 1 13: READY -> RUNNG cb=17 rem=77 prio=3
998 1 10: RUNNG -> READY  cb=7 rem=67 prio=3
998 2 13: READY -> RUNNG cb=18 rem=27 prio=1
1008 2 10: RUNNG -> READY  cb=8 rem=17 prio=1
1008 1 10: READY -> RUNNG cb=7 rem=67 prio=3
1015 1 7: RUNNG -> BLOCK  ib=37 rem=60
1015 2 7: READY -> RUNNG cb=8 rem=17 prio=1
1023 2 8: RUNNG -> BLOCK  ib=46 rem=9
1038 0 50: BLOCK -> READY
1038 0 0: READY -> RUNNG cb=32 rem=78 prio=1
1048 0 10: RUNNG -> READY  cb=22 rem=68 prio=1
1048 0 0: READY -> RUNNG cb=22 rem=68 prio=1
1052 1 37: BLOCK -> READY
1058 0 10: RUNNG -> READY  cb=12 rem=58 prio=1
1058 1 6: READY -> RUNNG cb=2 rem=60 prio=3
1060 1 2: RUNNG -> BLOCK  ib=5 rem=58
1060 0 2: READY -> RUNNG cb=12 rem=58 prio=1
1065 1 5: BLOCK -> READY
1069 2 46: BLOCK -> READY
1070 0 10: RUNNG -> READY  cb=2 rem=48 prio=1
1070 1 5: READY -> RUNNG cb=39 rem=58 prio=3
1080 1 10: RUNNG -> READY  cb=29 rem=48 prio=3
1080 2 11: READY -> RUNNG cb=9 rem=9 prio=1
1089 2 9: Done
1089 0 19: READY -> RUNNG cb=2 rem=48 prio=1
1091 0 2: RUNNG -> BLOCK  ib=48 rem=46
1091 1 11: READY -> RUNNG cb=29 rem=48 prio=3
1101 1 10: RUNNG -> READY  cb=19 rem=38 prio=3
1101 1 0: READY -> RUNNG cb=19 rem=38 prio=3
1111 1 10: RUNNG -> READY  cb=9 rem=28 prio=3
1111 1 0: READY -> RUNNG cb=9 rem=28 prio=3
1120 1 9: RUNNG -> BLOCK  ib=7 rem=19
1127 1 7: BLOCK -> READY
1127 1 0: READY -> RUNNG cb=12 rem=19 prio=3
1137 1 10: RUNNG -> READY  cb=2 rem=9 prio=3
1137 1 0: READY -> RUNNG cb=2 rem=9 prio=3
1139 0 48: BLOCK -> READY
1139 1 2: RUNNG -> BLOCK  ib=17 rem=7
1139 0 0: READY -> RUNNG cb=42 rem=46 prio=1
1149 0 10: RUNNG -> READY  cb=32 rem=36 prio=1
1149 0 0: READY -> RUNNG cb=32 rem=36 prio=1
1156 1 17: BLOCK -> READY
1159 0 10: RUNNG -> READY  cb=22 rem=26 prio=1
1159 1 3: READY -> RUNNG cb=7 rem=7 prio=3
1166 1 7: Done
1166 0 7: READY -> RUNNG cb=22 rem=26 prio=1
1176 0 10: RUNNG -> READY  cb=12 rem=16 prio=1
1176 0 0: READY -> RUNNG cb=12 rem=16 prio=1
1186 0 10: RUNNG -> READY  cb=2 rem=6 prio=1
1186 0 0: READY -> RUNNG cb=2 rem=6 prio=1
1188 0 2: RUNNG -> BLOCK  ib=9 rem=4
1197 0 9: BLOCK -> READY
1197 0 0: READY -> RUNNG cb=4 rem=4 prio=1
1201 0 4: Done
RR 10
0000:    0  400   50   50 2 |  1201  1201   413   388
0001:  101  300   41   40 4 |  1166  1065   381   384
0002:  202  200   32   50 2 |  1089   887   342   345
0003:  303  100   23   10 4 |   690   387    51   236
SUM: 1201 83.26 59.37 885.00 338.25 0.333
```

### Priority Scheduler (Time Quantum = 10, Maximum Priority = 4)

```
0 0 0: CREATED -> READY
0 0 0: READY -> RUNNG cb=50 rem=400 prio=1
10 0 10: RUNNG -> READY  cb=40 rem=390 prio=1
10 0 0: READY -> RUNNG cb=40 rem=390 prio=0
20 0 10: RUNNG -> READY  cb=30 rem=380 prio=0
20 0 0: READY -> RUNNG cb=30 rem=380 prio=1
30 0 10: RUNNG -> READY  cb=20 rem=370 prio=1
30 0 0: READY -> RUNNG cb=20 rem=370 prio=0
40 0 10: RUNNG -> READY  cb=10 rem=360 prio=0
40 0 0: READY -> RUNNG cb=10 rem=360 prio=1
50 0 10: RUNNG -> BLOCK  ib=27 rem=350
77 0 27: BLOCK -> READY
77 0 0: READY -> RUNNG cb=17 rem=350 prio=1
87 0 10: RUNNG -> READY  cb=7 rem=340 prio=1
87 0 0: READY -> RUNNG cb=7 rem=340 prio=0
94 0 7: RUNNG -> BLOCK  ib=9 rem=333
101 1 0: CREATED -> READY
101 1 0: READY -> RUNNG cb=35 rem=300 prio=3
103 0 9: BLOCK -> READY
111 1 10: RUNNG -> READY  cb=25 rem=290 prio=3
111 1 0: READY -> RUNNG cb=25 rem=290 prio=2
121 1 10: RUNNG -> READY  cb=15 rem=280 prio=2
121 0 18: READY -> RUNNG cb=11 rem=333 prio=1
131 0 10: RUNNG -> READY  cb=1 rem=323 prio=1
131 1 10: READY -> RUNNG cb=15 rem=280 prio=1
141 1 10: RUNNG -> READY  cb=5 rem=270 prio=1
141 0 10: READY -> RUNNG cb=1 rem=323 prio=0
142 0 1: RUNNG -> BLOCK  ib=49 rem=322
142 1 1: READY -> RUNNG cb=5 rem=270 prio=0
147 1 5: RUNNG -> BLOCK  ib=39 rem=265
186 1 39: BLOCK -> READY
186 1 0: READY -> RUNNG cb=4 rem=265 prio=3
190 1 4: RUNNG -> BLOCK  ib=4 rem=261
191 0 49: BLOCK -> READY
191 0 0: READY -> RUNNG cb=36 rem=322 prio=1
194 1 4: BLOCK -> READY
201 0 10: RUNNG -> READY  cb=26 rem=312 prio=1
201 1 7: READY -> RUNNG cb=19 rem=261 prio=3
202 2 0: CREATED -> READY
211 1 10: RUNNG -> READY  cb=9 rem=251 prio=3
211 1 0: READY -> RUNNG cb=9 rem=251 prio=2
220 1 9: RUNNG -> BLOCK  ib=2 rem=242
220 2 18: READY -> RUNNG cb=18 rem=200 prio=1
222 1 2: BLOCK -> READY
230 2 10: RUNNG -> READY  cb=8 rem=190 prio=1
230 1 8: READY -> RUNNG cb=22 rem=242 prio=3
240 1 10: RUNNG -> READY  cb=12 rem=232 prio=3
240 1 0: READY -> RUNNG cb=12 rem=232 prio=2
250 1 10: RUNNG -> READY  cb=2 rem=222 prio=2
250 1 0: READY -> RUNNG cb=2 rem=222 prio=1
252 1 2: RUNNG -> BLOCK  ib=36 rem=220
252 0 51: READY -> RUNNG cb=26 rem=312 prio=0
262 0 10: RUNNG -> READY  cb=16 rem=302 prio=0
262 2 32: READY -> RUNNG cb=8 rem=190 prio=0
270 2 8: RUNNG -> BLOCK  ib=49 rem=182
270 0 8: READY -> RUNNG cb=16 rem=302 prio=1
280 0 10: RUNNG -> READY  cb=6 rem=292 prio=1
280 0 0: READY -> RUNNG cb=6 rem=292 prio=0
286 0 6: RUNNG -> BLOCK  ib=5 rem=286
288 1 36: BLOCK -> READY
288 1 0: READY -> RUNNG cb=11 rem=220 prio=3
291 0 5: BLOCK -> READY
298 1 10: RUNNG -> READY  cb=1 rem=210 prio=3
298 1 0: READY -> RUNNG cb=1 rem=210 prio=2
299 1 1: RUNNG -> BLOCK  ib=30 rem=209
299 0 8: READY -> RUNNG cb=2 rem=286 prio=1
301 0 2: RUNNG -> BLOCK  ib=47 rem=284
303 3 0: CREATED -> READY
303 3 0: READY -> RUNNG cb=13 rem=100 prio=3
313 3 10: RUNNG -> READY  cb=3 rem=90 prio=3
313 3 0: READY -> RUNNG cb=3 rem=90 prio=2
316 3 3: RUNNG -> BLOCK  ib=5 rem=87
319 2 49: BLOCK -> READY
319 2 0: READY -> RUNNG cb=27 rem=182 prio=1
321 3 5: BLOCK -> READY
329 1 30: BLOCK -> READY
329 2 10: RUNNG -> READY  cb=17 rem=172 prio=1
329 3 8: READY -> RUNNG cb=16 rem=87 prio=3
339 3 10: RUNNG -> READY  cb=6 rem=77 prio=3
339 1 10: READY -> RUNNG cb=28 rem=209 prio=3
348 0 47: BLOCK -> READY
349 1 10: RUNNG -> READY  cb=18 rem=199 prio=3
349 3 10: READY -> RUNNG cb=6 rem=77 prio=2
355 3 6: RUNNG -> BLOCK  ib=9 rem=71
355 1 6: READY -> RUNNG cb=18 rem=199 prio=2
364 3 9: BLOCK -> READY
365 1 10: RUNNG -> READY  cb=8 rem=189 prio=2
365 3 1: READY -> RUNNG cb=3 rem=71 prio=3
368 3 3: RUNNG -> BLOCK  ib=9 rem=68
368 0 20: READY -> RUNNG cb=10 rem=284 prio=1
377 3 9: BLOCK -> READY
378 0 10: RUNNG -> BLOCK  ib=10 rem=274
378 3 1: READY -> RUNNG cb=2 rem=68 prio=3
380 3 2: RUNNG -> BLOCK  ib=8 rem=66
380 1 15: READY -> RUNNG cb=8 rem=189 prio=1
388 0 10: BLOCK -> READY
388 3 8: BLOCK -> READY
388 1 8: RUNNG -> BLOCK  ib=10 rem=181
388 3 0: READY -> RUNNG cb=1 rem=66 prio=3
389 3 1: RUNNG -> BLOCK  ib=1 rem=65
389 0 1: READY -> RUNNG cb=18 rem=274 prio=1
390 3 1: BLOCK -> READY
398 1 10: BLOCK -> READY
399 0 10: RUNNG -> READY  cb=8 rem=264 prio=1
399 3 9: READY -> RUNNG cb=1 rem=65 prio=3
400 3 1: RUNNG -> BLOCK  ib=1 rem=64
400 1 2: READY -> RUNNG cb=8 rem=181 prio=3
401 3 1: BLOCK -> READY
408 1 8: RUNNG -> BLOCK  ib=39 rem=173
408 3 7: READY -> RUNNG cb=18 rem=64 prio=3
418 3 10: RUNNG -> READY  cb=8 rem=54 prio=3
418 3 0: READY -> RUNNG cb=8 rem=54 prio=2
426 3 8: RUNNG -> BLOCK  ib=7 rem=46
426 2 97: READY -> RUNNG cb=17 rem=172 prio=0
433 3 7: BLOCK -> READY
436 2 10: RUNNG -> READY  cb=7 rem=162 prio=0
436 3 3: READY -> RUNNG cb=2 rem=46 prio=3
438 3 2: RUNNG -> BLOCK  ib=6 rem=44
438 0 39: READY -> RUNNG cb=8 rem=264 prio=0
444 3 6: BLOCK -> READY
446 0 8: RUNNG -> BLOCK  ib=22 rem=256
446 3 2: READY -> RUNNG cb=5 rem=44 prio=3
447 1 39: BLOCK -> READY
451 3 5: RUNNG -> BLOCK  ib=10 rem=39
451 1 4: READY -> RUNNG cb=29 rem=173 prio=3
461 3 10: BLOCK -> READY
461 1 10: RUNNG -> READY  cb=19 rem=163 prio=3
461 3 0: READY -> RUNNG cb=13 rem=39 prio=3
468 0 22: BLOCK -> READY
471 3 10: RUNNG -> READY  cb=3 rem=29 prio=3
471 1 10: READY -> RUNNG cb=19 rem=163 prio=2
481 1 10: RUNNG -> READY  cb=9 rem=153 prio=2
481 3 10: READY -> RUNNG cb=3 rem=29 prio=2
484 3 3: RUNNG -> BLOCK  ib=2 rem=26
484 0 16: READY -> RUNNG cb=41 rem=256 prio=1
486 3 2: BLOCK -> READY
494 0 10: RUNNG -> READY  cb=31 rem=246 prio=1
494 3 8: READY -> RUNNG cb=19 rem=26 prio=3
504 3 10: RUNNG -> READY  cb=9 rem=16 prio=3
504 3 0: READY -> RUNNG cb=9 rem=16 prio=2
513 3 9: RUNNG -> BLOCK  ib=8 rem=7
513 1 32: READY -> RUNNG cb=9 rem=153 prio=1
521 3 8: BLOCK -> READY
522 1 9: RUNNG -> BLOCK  ib=27 rem=144
522 3 1: READY -> RUNNG cb=5 rem=7 prio=3
527 3 5: RUNNG -> BLOCK  ib=1 rem=2
527 0 33: READY -> RUNNG cb=31 rem=246 prio=0
528 3 1: BLOCK -> READY
537 0 10: RUNNG -> READY  cb=21 rem=236 prio=0
537 3 9: READY -> RUNNG cb=2 rem=2 prio=3
539 3 2: Done
539 2 103: READY -> RUNNG cb=7 rem=162 prio=1
546 2 7: RUNNG -> BLOCK  ib=40 rem=155
546 0 9: READY -> RUNNG cb=21 rem=236 prio=1
549 1 27: BLOCK -> READY
556 0 10: RUNNG -> READY  cb=11 rem=226 prio=1
556 1 7: READY -> RUNNG cb=34 rem=144 prio=3
566 1 10: RUNNG -> READY  cb=24 rem=134 prio=3
566 1 0: READY -> RUNNG cb=24 rem=134 prio=2
576 1 10: RUNNG -> READY  cb=14 rem=124 prio=2
576 1 0: READY -> RUNNG cb=14 rem=124 prio=1
586 2 40: BLOCK -> READY
586 1 10: RUNNG -> READY  cb=4 rem=114 prio=1
586 2 0: READY -> RUNNG cb=10 rem=155 prio=1
596 2 10: RUNNG -> BLOCK  ib=49 rem=145
596 0 40: READY -> RUNNG cb=11 rem=226 prio=0
606 0 10: RUNNG -> READY  cb=1 rem=216 prio=0
606 1 20: READY -> RUNNG cb=4 rem=114 prio=0
610 1 4: RUNNG -> BLOCK  ib=8 rem=110
610 0 4: READY -> RUNNG cb=1 rem=216 prio=1
611 0 1: RUNNG -> BLOCK  ib=8 rem=215
618 1 8: BLOCK -> READY
618 1 0: READY -> RUNNG cb=33 rem=110 prio=3
619 0 8: BLOCK -> READY
628 1 10: RUNNG -> READY  cb=23 rem=100 prio=3
628 1 0: READY -> RUNNG cb=23 rem=100 prio=2
638 1 10: RUNNG -> READY  cb=13 rem=90 prio=2
638 0 19: READY -> RUNNG cb=31 rem=215 prio=1
645 2 49: BLOCK -> READY
648 0 10: RUNNG -> READY  cb=21 rem=205 prio=1
648 1 10: READY -> RUNNG cb=13 rem=90 prio=1
658 1 10: RUNNG -> READY  cb=3 rem=80 prio=1
658 2 13: READY -> RUNNG cb=30 rem=145 prio=1
668 2 10: RUNNG -> READY  cb=20 rem=135 prio=1
668 0 20: READY -> RUNNG cb=21 rem=205 prio=0
678 0 10: RUNNG -> READY  cb=11 rem=195 prio=0
678 1 20: READY -> RUNNG cb=3 rem=80 prio=0
681 1 3: RUNNG -> BLOCK  ib=38 rem=77
681 2 13: READY -> RUNNG cb=20 rem=135 prio=0
691 2 10: RUNNG -> READY  cb=10 rem=125 prio=0
691 0 13: READY -> RUNNG cb=11 rem=195 prio=1
701 0 10: RUNNG -> READY  cb=1 rem=185 prio=1
701 2 10: READY -> RUNNG cb=10 rem=125 prio=1
711 2 10: RUNNG -> BLOCK  ib=44 rem=115
711 0 10: READY -> RUNNG cb=1 rem=185 prio=0
712 0 1: RUNNG -> BLOCK  ib=20 rem=184
719 1 38: BLOCK -> READY
719 1 0: READY -> RUNNG cb=36 rem=77 prio=3
729 1 10: RUNNG -> READY  cb=26 rem=67 prio=3
729 1 0: READY -> RUNNG cb=26 rem=67 prio=2
732 0 20: BLOCK -> READY
739 1 10: RUNNG -> READY  cb=16 rem=57 prio=2
739 0 7: READY -> RUNNG cb=42 rem=184 prio=1
749 0 10: RUNNG -> READY  cb=32 rem=174 prio=1
749 1 10: READY -> RUNNG cb=16 rem=57 prio=1
755 2 44: BLOCK -> READY
759 1 10: RUNNG -> READY  cb=6 rem=47 prio=1
759 2 4: READY -> RUNNG cb=20 rem=115 prio=1
769 2 10: RUNNG -> READY  cb=10 rem=105 prio=1
769 0 20: READY -> RUNNG cb=32 rem=174 prio=0
779 0 10: RUNNG -> READY  cb=22 rem=164 prio=0
779 1 20: READY -> RUNNG cb=6 rem=47 prio=0
785 1 6: RUNNG -> BLOCK  ib=10 rem=41
785 2 16: READY -> RUNNG cb=10 rem=105 prio=0
795 1 10: BLOCK -> READY
795 2 10: RUNNG -> BLOCK  ib=24 rem=95
795 1 0: READY -> RUNNG cb=1 rem=41 prio=3
796 1 1: RUNNG -> BLOCK  ib=11 rem=40
796 0 17: READY -> RUNNG cb=22 rem=164 prio=1
806 0 10: RUNNG -> READY  cb=12 rem=154 prio=1
806 0 0: READY -> RUNNG cb=12 rem=154 prio=0
807 1 11: BLOCK -> READY
816 0 10: RUNNG -> READY  cb=2 rem=144 prio=0
816 1 9: READY -> RUNNG cb=15 rem=40 prio=3
819 2 24: BLOCK -> READY
826 1 10: RUNNG -> READY  cb=5 rem=30 prio=3
826 1 0: READY -> RUNNG cb=5 rem=30 prio=2
831 1 5: RUNNG -> BLOCK  ib=11 rem=25
831 2 12: READY -> RUNNG cb=3 rem=95 prio=1
834 2 3: RUNNG -> BLOCK  ib=10 rem=92
834 0 18: READY -> RUNNG cb=2 rem=144 prio=1
836 0 2: RUNNG -> BLOCK  ib=12 rem=142
842 1 11: BLOCK -> READY
842 1 0: READY -> RUNNG cb=18 rem=25 prio=3
844 2 10: BLOCK -> READY
848 0 12: BLOCK -> READY
852 1 10: RUNNG -> READY  cb=8 rem=15 prio=3
852 1 0: READY -> RUNNG cb=8 rem=15 prio=2
860 1 8: RUNNG -> BLOCK  ib=28 rem=7
860 2 16: READY -> RUNNG cb=25 rem=92 prio=1
870 2 10: RUNNG -> READY  cb=15 rem=82 prio=1
870 0 22: READY -> RUNNG cb=44 rem=142 prio=1
880 0 10: RUNNG -> READY  cb=34 rem=132 prio=1
880 2 10: READY -> RUNNG cb=15 rem=82 prio=0
888 1 28: BLOCK -> READY
890 2 10: RUNNG -> READY  cb=5 rem=72 prio=0
890 1 2: READY -> RUNNG cb=3 rem=7 prio=3
893 1 3: RUNNG -> BLOCK  ib=23 rem=4
893 0 13: READY -> RUNNG cb=34 rem=132 prio=0
903 0 10: RUNNG -> READY  cb=24 rem=122 prio=0
903 2 13: READY -> RUNNG cb=5 rem=72 prio=1
908 2 5: RUNNG -> BLOCK  ib=11 rem=67
908 0 5: READY -> RUNNG cb=24 rem=122 prio=1
916 1 23: BLOCK -> READY
918 0 10: RUNNG -> READY  cb=14 rem=112 prio=1
918 1 2: READY -> RUNNG cb=4 rem=4 prio=3
919 2 11: BLOCK -> READY
922 1 4: Done
922 2 3: READY -> RUNNG cb=23 rem=67 prio=1
932 2 10: RUNNG -> READY  cb=13 rem=57 prio=1
932 0 14: READY -> RUNNG cb=14 rem=112 prio=0
942 0 10: RUNNG -> READY  cb=4 rem=102 prio=0
942 2 10: READY -> RUNNG cb=13 rem=57 prio=0
952 2 10: RUNNG -> READY  cb=3 rem=47 prio=0
952 0 10: READY -> RUNNG cb=4 rem=102 prio=1
956 0 4: RUNNG -> BLOCK  ib=40 rem=98
956 2 4: READY -> RUNNG cb=3 rem=47 prio=1
959 2 3: RUNNG -> BLOCK  ib=26 rem=44
985 2 26: BLOCK -> READY
985 2 0: READY -> RUNNG cb=30 rem=44 prio=1
995 2 10: RUNNG -> READY  cb=20 rem=34 prio=1
995 2 0: READY -> RUNNG cb=20 rem=34 prio=0
996 0 40: BLOCK -> READY
1005 2 10: RUNNG -> READY  cb=10 rem=24 prio=0
1005 0 9: READY -> RUNNG cb=47 rem=98 prio=1
1015 0 10: RUNNG -> READY  cb=37 rem=88 prio=1
1015 0 0: READY -> RUNNG cb=37 rem=88 prio=0
1025 0 10: RUNNG -> READY  cb=27 rem=78 prio=0
1025 2 20: READY -> RUNNG cb=10 rem=24 prio=1
1035 2 10: RUNNG -> BLOCK  ib=46 rem=14
1035 0 10: READY -> RUNNG cb=27 rem=78 prio=1
1045 0 10: RUNNG -> READY  cb=17 rem=68 prio=1
1045 0 0: READY -> RUNNG cb=17 rem=68 prio=0
1055 0 10: RUNNG -> READY  cb=7 rem=58 prio=0
1055 0 0: READY -> RUNNG cb=7 rem=58 prio=1
1062 0 7: RUNNG -> BLOCK  ib=32 rem=51
1081 2 46: BLOCK -> READY
1081 2 0: READY -> RUNNG cb=10 rem=14 prio=1
1091 2 10: RUNNG -> BLOCK  ib=35 rem=4
1094 0 32: BLOCK -> READY
1094 0 0: READY -> RUNNG cb=25 rem=51 prio=1
1104 0 10: RUNNG -> READY  cb=15 rem=41 prio=1
1104 0 0: READY -> RUNNG cb=15 rem=41 prio=0
1114 0 10: RUNNG -> READY  cb=5 rem=31 prio=0
1114 0 0: READY -> RUNNG cb=5 rem=31 prio=1
1119 0 5: RUNNG -> BLOCK  ib=14 rem=26
1126 2 35: BLOCK -> READY
1126 2 0: READY -> RUNNG cb=4 rem=4 prio=1
1130 2 4: Done
1133 0 14: BLOCK -> READY
1133 0 0: READY -> RUNNG cb=17 rem=26 prio=1
1143 0 10: RUNNG -> READY  cb=7 rem=16 prio=1
1143 0 0: READY -> RUNNG cb=7 rem=16 prio=0
1150 0 7: RUNNG -> BLOCK  ib=37 rem=9
1187 0 37: BLOCK -> READY
1187 0 0: READY -> RUNNG cb=9 rem=9 prio=1
1196 0 9: Done
PRIO 10
0000:    0  400   50   50 2 |  1196  1196   332   464
0001:  101  300   41   40 4 |   922   821   316   205
0002:  202  200   32   50 2 |  1130   928   334   394
0003:  303  100   23   10 4 |   539   236    67    69
SUM: 1196 83.61 63.71 795.25 283.00 0.334
```

### Preemptive Priority Scheduler (Time Quantum = 10, Maximum Priority = 4)

```
0 0 0: CREATED -> READY
0 0 0: READY -> RUNNG cb=50 rem=400 prio=1
10 0 10: RUNNG -> READY  cb=40 rem=390 prio=1
10 0 0: READY -> RUNNG cb=40 rem=390 prio=0
20 0 10: RUNNG -> READY  cb=30 rem=380 prio=0
20 0 0: READY -> RUNNG cb=30 rem=380 prio=1
30 0 10: RUNNG -> READY  cb=20 rem=370 prio=1
30 0 0: READY -> RUNNG cb=20 rem=370 prio=0
40 0 10: RUNNG -> READY  cb=10 rem=360 prio=0
40 0 0: READY -> RUNNG cb=10 rem=360 prio=1
50 0 10: RUNNG -> BLOCK  ib=27 rem=350
77 0 27: BLOCK -> READY
77 0 0: READY -> RUNNG cb=17 rem=350 prio=1
87 0 10: RUNNG -> READY  cb=7 rem=340 prio=1
87 0 0: READY -> RUNNG cb=7 rem=340 prio=0
94 0 7: RUNNG -> BLOCK  ib=9 rem=333
101 1 0: CREATED -> READY
101 1 0: READY -> RUNNG cb=35 rem=300 prio=3
103 0 9: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (8) --> NO
111 1 10: RUNNG -> READY  cb=25 rem=290 prio=3
111 1 0: READY -> RUNNG cb=25 rem=290 prio=2
121 1 10: RUNNG -> READY  cb=15 rem=280 prio=2
121 0 18: READY -> RUNNG cb=11 rem=333 prio=1
131 0 10: RUNNG -> READY  cb=1 rem=323 prio=1
131 1 10: READY -> RUNNG cb=15 rem=280 prio=1
141 1 10: RUNNG -> READY  cb=5 rem=270 prio=1
141 0 10: READY -> RUNNG cb=1 rem=323 prio=0
142 0 1: RUNNG -> BLOCK  ib=49 rem=322
142 1 1: READY -> RUNNG cb=5 rem=270 prio=0
147 1 5: RUNNG -> BLOCK  ib=39 rem=265
186 1 39: BLOCK -> READY
186 1 0: READY -> RUNNG cb=4 rem=265 prio=3
190 1 4: RUNNG -> BLOCK  ib=4 rem=261
191 0 49: BLOCK -> READY
191 0 0: READY -> RUNNG cb=36 rem=322 prio=1
194 1 4: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (7) --> YES
194 0 3: RUNNG -> READY  cb=33 rem=319 prio=1
194 1 0: READY -> RUNNG cb=19 rem=261 prio=3
202 2 0: CREATED -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (2) --> NO
204 1 10: RUNNG -> READY  cb=9 rem=251 prio=3
204 1 0: READY -> RUNNG cb=9 rem=251 prio=2
213 1 9: RUNNG -> BLOCK  ib=2 rem=242
213 2 11: READY -> RUNNG cb=18 rem=200 prio=1
215 1 2: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (8) --> YES
215 2 2: RUNNG -> READY  cb=16 rem=198 prio=1
215 1 0: READY -> RUNNG cb=22 rem=242 prio=3
225 1 10: RUNNG -> READY  cb=12 rem=232 prio=3
225 1 0: READY -> RUNNG cb=12 rem=232 prio=2
235 1 10: RUNNG -> READY  cb=2 rem=222 prio=2
235 1 0: READY -> RUNNG cb=2 rem=222 prio=1
237 1 2: RUNNG -> BLOCK  ib=36 rem=220
237 0 43: READY -> RUNNG cb=33 rem=319 prio=0
247 0 10: RUNNG -> READY  cb=23 rem=309 prio=0
247 2 32: READY -> RUNNG cb=16 rem=198 prio=0
257 2 10: RUNNG -> READY  cb=6 rem=188 prio=0
257 0 10: READY -> RUNNG cb=23 rem=309 prio=1
267 0 10: RUNNG -> READY  cb=13 rem=299 prio=1
267 2 10: READY -> RUNNG cb=6 rem=188 prio=1
273 1 36: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=0 (0) --> NO
273 2 6: RUNNG -> BLOCK  ib=49 rem=182
273 1 0: READY -> RUNNG cb=40 rem=220 prio=3
283 1 10: RUNNG -> READY  cb=30 rem=210 prio=3
283 1 0: READY -> RUNNG cb=30 rem=210 prio=2
293 1 10: RUNNG -> READY  cb=20 rem=200 prio=2
293 1 0: READY -> RUNNG cb=20 rem=200 prio=1
303 3 0: CREATED -> READY
    --> PrioPreempt Cond1=1 Cond2=0 (0) --> NO
303 1 10: RUNNG -> READY  cb=10 rem=190 prio=1
303 3 0: READY -> RUNNG cb=5 rem=100 prio=3
308 3 5: RUNNG -> BLOCK  ib=10 rem=95
308 0 41: READY -> RUNNG cb=13 rem=299 prio=0
318 3 10: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=0 (0) --> NO
318 0 10: RUNNG -> READY  cb=3 rem=289 prio=0
318 3 0: READY -> RUNNG cb=11 rem=95 prio=3
322 2 49: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (6) --> NO
328 3 10: RUNNG -> READY  cb=1 rem=85 prio=3
328 3 0: READY -> RUNNG cb=1 rem=85 prio=2
329 3 1: RUNNG -> BLOCK  ib=7 rem=84
329 2 7: READY -> RUNNG cb=15 rem=182 prio=1
336 3 7: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (3) --> YES
336 2 7: RUNNG -> READY  cb=8 rem=175 prio=1
336 3 0: READY -> RUNNG cb=18 rem=84 prio=3
346 3 10: RUNNG -> READY  cb=8 rem=74 prio=3
346 3 0: READY -> RUNNG cb=8 rem=74 prio=2
354 3 8: RUNNG -> BLOCK  ib=7 rem=66
354 1 51: READY -> RUNNG cb=10 rem=190 prio=0
361 3 7: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (3) --> YES
361 1 7: RUNNG -> READY  cb=3 rem=183 prio=0
361 3 0: READY -> RUNNG cb=16 rem=66 prio=3
371 3 10: RUNNG -> READY  cb=6 rem=56 prio=3
371 3 0: READY -> RUNNG cb=6 rem=56 prio=2
377 3 6: RUNNG -> BLOCK  ib=2 rem=50
377 2 41: READY -> RUNNG cb=8 rem=175 prio=0
379 3 2: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (6) --> YES
379 2 2: RUNNG -> READY  cb=6 rem=173 prio=0
379 3 0: READY -> RUNNG cb=6 rem=50 prio=3
385 3 6: RUNNG -> BLOCK  ib=1 rem=44
385 1 24: READY -> RUNNG cb=3 rem=183 prio=3
386 3 1: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (2) --> NO
388 1 3: RUNNG -> BLOCK  ib=19 rem=180
388 3 2: READY -> RUNNG cb=17 rem=44 prio=3
398 3 10: RUNNG -> READY  cb=7 rem=34 prio=3
398 3 0: READY -> RUNNG cb=7 rem=34 prio=2
405 3 7: RUNNG -> BLOCK  ib=10 rem=27
405 0 87: READY -> RUNNG cb=3 rem=289 prio=1
407 1 19: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (1) --> YES
407 0 2: RUNNG -> READY  cb=1 rem=287 prio=1
407 1 0: READY -> RUNNG cb=37 rem=180 prio=3
415 3 10: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (2) --> NO
417 1 10: RUNNG -> READY  cb=27 rem=170 prio=3
417 3 2: READY -> RUNNG cb=2 rem=27 prio=3
419 3 2: RUNNG -> BLOCK  ib=10 rem=25
419 1 2: READY -> RUNNG cb=27 rem=170 prio=2
429 3 10: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=0 (0) --> NO
429 1 10: RUNNG -> READY  cb=17 rem=160 prio=2
429 3 0: READY -> RUNNG cb=1 rem=25 prio=3
430 3 1: RUNNG -> BLOCK  ib=1 rem=24
430 2 51: READY -> RUNNG cb=6 rem=173 prio=1
431 3 1: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (5) --> YES
431 2 1: RUNNG -> READY  cb=5 rem=172 prio=1
431 3 0: READY -> RUNNG cb=15 rem=24 prio=3
441 3 10: RUNNG -> READY  cb=5 rem=14 prio=3
441 3 0: READY -> RUNNG cb=5 rem=14 prio=2
446 3 5: RUNNG -> BLOCK  ib=4 rem=9
446 1 17: READY -> RUNNG cb=17 rem=160 prio=1
450 3 4: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (6) --> YES
450 1 4: RUNNG -> READY  cb=13 rem=156 prio=1
450 3 0: READY -> RUNNG cb=3 rem=9 prio=3
453 3 3: RUNNG -> BLOCK  ib=4 rem=6
453 0 46: READY -> RUNNG cb=1 rem=287 prio=0
454 0 1: RUNNG -> BLOCK  ib=49 rem=286
454 2 23: READY -> RUNNG cb=5 rem=172 prio=0
457 3 4: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (2) --> YES
457 2 3: RUNNG -> READY  cb=2 rem=169 prio=0
457 3 0: READY -> RUNNG cb=6 rem=6 prio=3
463 3 6: Done
463 1 13: READY -> RUNNG cb=13 rem=156 prio=0
473 1 10: RUNNG -> READY  cb=3 rem=146 prio=0
473 1 0: READY -> RUNNG cb=3 rem=146 prio=3
476 1 3: RUNNG -> BLOCK  ib=7 rem=143
476 2 19: READY -> RUNNG cb=2 rem=169 prio=1
478 2 2: RUNNG -> BLOCK  ib=33 rem=167
483 1 7: BLOCK -> READY
483 1 0: READY -> RUNNG cb=5 rem=143 prio=3
488 1 5: RUNNG -> BLOCK  ib=2 rem=138
490 1 2: BLOCK -> READY
490 1 0: READY -> RUNNG cb=1 rem=138 prio=3
491 1 1: RUNNG -> BLOCK  ib=40 rem=137
503 0 49: BLOCK -> READY
503 0 0: READY -> RUNNG cb=43 rem=286 prio=1
511 2 33: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (2) --> NO
513 0 10: RUNNG -> READY  cb=33 rem=276 prio=1
513 2 2: READY -> RUNNG cb=10 rem=167 prio=1
523 2 10: RUNNG -> BLOCK  ib=32 rem=157
523 0 10: READY -> RUNNG cb=33 rem=276 prio=0
531 1 40: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (2) --> YES
531 0 8: RUNNG -> READY  cb=25 rem=268 prio=0
531 1 0: READY -> RUNNG cb=38 rem=137 prio=3
541 1 10: RUNNG -> READY  cb=28 rem=127 prio=3
541 1 0: READY -> RUNNG cb=28 rem=127 prio=2
551 1 10: RUNNG -> READY  cb=18 rem=117 prio=2
551 1 0: READY -> RUNNG cb=18 rem=117 prio=1
555 2 32: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (6) --> NO
561 1 10: RUNNG -> READY  cb=8 rem=107 prio=1
561 2 6: READY -> RUNNG cb=24 rem=157 prio=1
571 2 10: RUNNG -> READY  cb=14 rem=147 prio=1
571 1 10: READY -> RUNNG cb=8 rem=107 prio=0
579 1 8: RUNNG -> BLOCK  ib=38 rem=99
579 2 8: READY -> RUNNG cb=14 rem=147 prio=0
589 2 10: RUNNG -> READY  cb=4 rem=137 prio=0
589 0 58: READY -> RUNNG cb=25 rem=268 prio=1
599 0 10: RUNNG -> READY  cb=15 rem=258 prio=1
599 2 10: READY -> RUNNG cb=4 rem=137 prio=1
603 2 4: RUNNG -> BLOCK  ib=17 rem=133
603 0 4: READY -> RUNNG cb=15 rem=258 prio=0
613 0 10: RUNNG -> READY  cb=5 rem=248 prio=0
613 0 0: READY -> RUNNG cb=5 rem=248 prio=1
617 1 38: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (1) --> YES
617 0 4: RUNNG -> READY  cb=1 rem=244 prio=1
617 1 0: READY -> RUNNG cb=24 rem=99 prio=3
620 2 17: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (7) --> NO
627 1 10: RUNNG -> READY  cb=14 rem=89 prio=3
627 1 0: READY -> RUNNG cb=14 rem=89 prio=2
637 1 10: RUNNG -> READY  cb=4 rem=79 prio=2
637 2 17: READY -> RUNNG cb=31 rem=133 prio=1
647 2 10: RUNNG -> READY  cb=21 rem=123 prio=1
647 1 10: READY -> RUNNG cb=4 rem=79 prio=1
651 1 4: RUNNG -> BLOCK  ib=17 rem=75
651 0 34: READY -> RUNNG cb=1 rem=244 prio=0
652 0 1: RUNNG -> BLOCK  ib=40 rem=243
652 2 5: READY -> RUNNG cb=21 rem=123 prio=0
662 2 10: RUNNG -> READY  cb=11 rem=113 prio=0
662 2 0: READY -> RUNNG cb=11 rem=113 prio=1
668 1 17: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (4) --> YES
668 2 6: RUNNG -> READY  cb=5 rem=107 prio=1
668 1 0: READY -> RUNNG cb=34 rem=75 prio=3
678 1 10: RUNNG -> READY  cb=24 rem=65 prio=3
678 1 0: READY -> RUNNG cb=24 rem=65 prio=2
688 1 10: RUNNG -> READY  cb=14 rem=55 prio=2
688 1 0: READY -> RUNNG cb=14 rem=55 prio=1
692 0 40: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (6) --> NO
698 1 10: RUNNG -> READY  cb=4 rem=45 prio=1
698 0 6: READY -> RUNNG cb=28 rem=243 prio=1
708 0 10: RUNNG -> READY  cb=18 rem=233 prio=1
708 2 40: READY -> RUNNG cb=5 rem=107 prio=0
713 2 5: RUNNG -> BLOCK  ib=49 rem=102
713 1 15: READY -> RUNNG cb=4 rem=45 prio=0
717 1 4: RUNNG -> BLOCK  ib=8 rem=41
717 0 9: READY -> RUNNG cb=18 rem=233 prio=0
725 1 8: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (2) --> YES
725 0 8: RUNNG -> READY  cb=10 rem=225 prio=0
725 1 0: READY -> RUNNG cb=9 rem=41 prio=3
734 1 9: RUNNG -> BLOCK  ib=21 rem=32
734 0 9: READY -> RUNNG cb=10 rem=225 prio=1
744 0 10: RUNNG -> BLOCK  ib=31 rem=215
755 1 21: BLOCK -> READY
755 1 0: READY -> RUNNG cb=9 rem=32 prio=3
762 2 49: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (2) --> NO
764 1 9: RUNNG -> BLOCK  ib=38 rem=23
764 2 2: READY -> RUNNG cb=24 rem=102 prio=1
774 2 10: RUNNG -> READY  cb=14 rem=92 prio=1
774 2 0: READY -> RUNNG cb=14 rem=92 prio=0
775 0 31: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (9) --> YES
775 2 1: RUNNG -> READY  cb=13 rem=91 prio=0
775 0 0: READY -> RUNNG cb=20 rem=215 prio=1
785 0 10: RUNNG -> READY  cb=10 rem=205 prio=1
785 0 0: READY -> RUNNG cb=10 rem=205 prio=0
795 0 10: RUNNG -> BLOCK  ib=13 rem=195
795 2 20: READY -> RUNNG cb=13 rem=91 prio=1
802 1 38: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (3) --> YES
802 2 7: RUNNG -> READY  cb=6 rem=84 prio=1
802 1 0: READY -> RUNNG cb=19 rem=23 prio=3
808 0 13: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (4) --> NO
812 1 10: RUNNG -> READY  cb=9 rem=13 prio=3
812 1 0: READY -> RUNNG cb=9 rem=13 prio=2
821 1 9: RUNNG -> BLOCK  ib=4 rem=4
821 0 13: READY -> RUNNG cb=20 rem=195 prio=1
825 1 4: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (6) --> YES
825 0 4: RUNNG -> READY  cb=16 rem=191 prio=1
825 1 0: READY -> RUNNG cb=4 rem=4 prio=3
829 1 4: Done
829 2 27: READY -> RUNNG cb=6 rem=84 prio=0
835 2 6: RUNNG -> BLOCK  ib=49 rem=78
835 0 10: READY -> RUNNG cb=16 rem=191 prio=0
845 0 10: RUNNG -> READY  cb=6 rem=181 prio=0
845 0 0: READY -> RUNNG cb=6 rem=181 prio=1
851 0 6: RUNNG -> BLOCK  ib=41 rem=175
884 2 49: BLOCK -> READY
884 2 0: READY -> RUNNG cb=19 rem=78 prio=1
892 0 41: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (2) --> NO
894 2 10: RUNNG -> READY  cb=9 rem=68 prio=1
894 0 2: READY -> RUNNG cb=31 rem=175 prio=1
904 0 10: RUNNG -> READY  cb=21 rem=165 prio=1
904 2 10: READY -> RUNNG cb=9 rem=68 prio=0
913 2 9: RUNNG -> BLOCK  ib=35 rem=59
913 0 9: READY -> RUNNG cb=21 rem=165 prio=0
923 0 10: RUNNG -> READY  cb=11 rem=155 prio=0
923 0 0: READY -> RUNNG cb=11 rem=155 prio=1
933 0 10: RUNNG -> READY  cb=1 rem=145 prio=1
933 0 0: READY -> RUNNG cb=1 rem=145 prio=0
934 0 1: RUNNG -> BLOCK  ib=10 rem=144
944 0 10: BLOCK -> READY
944 0 0: READY -> RUNNG cb=12 rem=144 prio=1
948 2 35: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (6) --> NO
954 0 10: RUNNG -> READY  cb=2 rem=134 prio=1
954 2 6: READY -> RUNNG cb=20 rem=59 prio=1
964 2 10: RUNNG -> READY  cb=10 rem=49 prio=1
964 0 10: READY -> RUNNG cb=2 rem=134 prio=0
966 0 2: RUNNG -> BLOCK  ib=8 rem=132
966 2 2: READY -> RUNNG cb=10 rem=49 prio=0
974 0 8: BLOCK -> READY
    --> PrioPreempt Cond1=1 Cond2=1 (2) --> YES
974 2 8: RUNNG -> READY  cb=2 rem=41 prio=0
974 0 0: READY -> RUNNG cb=1 rem=132 prio=1
975 0 1: RUNNG -> BLOCK  ib=44 rem=131
975 2 1: READY -> RUNNG cb=2 rem=41 prio=1
977 2 2: RUNNG -> BLOCK  ib=36 rem=39
1013 2 36: BLOCK -> READY
1013 2 0: READY -> RUNNG cb=23 rem=39 prio=1
1019 0 44: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (4) --> NO
1023 2 10: RUNNG -> READY  cb=13 rem=29 prio=1
1023 0 4: READY -> RUNNG cb=11 rem=131 prio=1
1033 0 10: RUNNG -> READY  cb=1 rem=121 prio=1
1033 2 10: READY -> RUNNG cb=13 rem=29 prio=0
1043 2 10: RUNNG -> READY  cb=3 rem=19 prio=0
1043 0 10: READY -> RUNNG cb=1 rem=121 prio=0
1044 0 1: RUNNG -> BLOCK  ib=25 rem=120
1044 2 1: READY -> RUNNG cb=3 rem=19 prio=1
1047 2 3: RUNNG -> BLOCK  ib=13 rem=16
1060 2 13: BLOCK -> READY
1060 2 0: READY -> RUNNG cb=8 rem=16 prio=1
1068 2 8: RUNNG -> BLOCK  ib=26 rem=8
1069 0 25: BLOCK -> READY
1069 0 0: READY -> RUNNG cb=50 rem=120 prio=1
1079 0 10: RUNNG -> READY  cb=40 rem=110 prio=1
1079 0 0: READY -> RUNNG cb=40 rem=110 prio=0
1089 0 10: RUNNG -> READY  cb=30 rem=100 prio=0
1089 0 0: READY -> RUNNG cb=30 rem=100 prio=1
1094 2 26: BLOCK -> READY
    --> PrioPreempt Cond1=0 Cond2=1 (5) --> NO
1099 0 10: RUNNG -> READY  cb=20 rem=90 prio=1
1099 2 5: READY -> RUNNG cb=8 rem=8 prio=1
1107 2 8: Done
1107 0 8: READY -> RUNNG cb=20 rem=90 prio=0
1117 0 10: RUNNG -> READY  cb=10 rem=80 prio=0
1117 0 0: READY -> RUNNG cb=10 rem=80 prio=1
1127 0 10: RUNNG -> BLOCK  ib=46 rem=70
1173 0 46: BLOCK -> READY
1173 0 0: READY -> RUNNG cb=32 rem=70 prio=1
1183 0 10: RUNNG -> READY  cb=22 rem=60 prio=1
1183 0 0: READY -> RUNNG cb=22 rem=60 prio=0
1193 0 10: RUNNG -> READY  cb=12 rem=50 prio=0
1193 0 0: READY -> RUNNG cb=12 rem=50 prio=1
1203 0 10: RUNNG -> READY  cb=2 rem=40 prio=1
1203 0 0: READY -> RUNNG cb=2 rem=40 prio=0
1205 0 2: RUNNG -> BLOCK  ib=44 rem=38
1249 0 44: BLOCK -> READY
1249 0 0: READY -> RUNNG cb=35 rem=38 prio=1
1259 0 10: RUNNG -> READY  cb=25 rem=28 prio=1
1259 0 0: READY -> RUNNG cb=25 rem=28 prio=0
1269 0 10: RUNNG -> READY  cb=15 rem=18 prio=0
1269 0 0: READY -> RUNNG cb=15 rem=18 prio=1
1279 0 10: RUNNG -> READY  cb=5 rem=8 prio=1
1279 0 0: READY -> RUNNG cb=5 rem=8 prio=0
1284 0 5: RUNNG -> BLOCK  ib=25 rem=3
1309 0 25: BLOCK -> READY
1309 0 0: READY -> RUNNG cb=3 rem=3 prio=1
1312 0 3: Done
PREPRIO 10
0000:    0  400   50   50 2 |  1312  1312   461   451
0001:  101  300   41   40 4 |   829   728   275   153
0002:  202  200   32   50 2 |  1107   905   339   366
0003:  303  100   23   10 4 |   463   160    56     4
SUM: 1312 76.22 62.96 776.25 243.50 0.305
```
