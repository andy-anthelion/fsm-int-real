#!/bin/bash

OUT_FILE=sample.out

printf "\n\nINPUT: a1a2a3a4pd0p\nOUTPUT: " > $$OUT_FILE
./fsm.out a1a2a3a4pd0p >> $OUT_FILE

printf "\n\nINPUT: a1a2a3xxa4pd-12.3pa7\nOUTPUT: " >> $OUT_FILE
./fsm.out a1a2a3xxa4pd-12.3pa7 >> $OUT_FILE

printf "\n\nINPUT: a-1.234e-10a2a5a1.e10d1d1p\nOUTPUT: " >> $OUT_FILE
./fsm.out a-1.234e-10a2a5a1.e10d1d1p >> $OUT_FILE

printf "\n\nINPUT: a157a2.0a3.0a0.0a.1e10a1e23p\nOUTPUT: " >> $OUT_FILE
./fsm.out a157a2.0a3.0a0.0a.1e10a1e23p >> $OUT_FILE

printf "\n\nINPUT: xxxa-1.234e-10a1.e10a1.234e10a1.234e-10p\nOUTPUT: " >> $OUT_FILE
./fsm.out xxxa-1.234e-10a1.e10a1.234e10a1.234e-10p >> $OUT_FILE

printf "\n\nINPUT: xxx+1.234e+10a+1.234g+10a+1.234e10x+10d-2p\nOUTPUT: " >> $OUT_FILE
./fsm.out xxx+1.234e+10a+1.234g+10a+1.234e10x+10d-2p >> $OUT_FILE

printf "\n\nINPUT: aaaddddp\nOUTPUT: " >> $OUT_FILE
./fsm.out aaaddddp >> $OUT_FILE

printf "\n\nINPUT: pppppppp\nOUTPUT: " >> $OUT_FILE
./fsm.out pppppppp >> $OUT_FILE

printf "\n\nINPUT: ddddPPPP\nOUTPUT: " >> $OUT_FILE
./fsm.out ddddPPPP >> $OUT_FILE

printf "\n\nINPUT: garbage\nOUTPUT: " >> $OUT_FILE
./fsm.out garbage >> $OUT_FILE

printf "\n\nINPUT: pa1.2eE23p\nOUTPUT: " >> $OUT_FILE
./fsm.out pa1.2eE23p >> $OUT_FILE

printf "\n\nINPUT: pa-1a-2d-1d-2P\nOUTPUT: " >> $OUT_FILE
./fsm.out pa-1a-2d-1d-2P >> $OUT_FILE


printf "\n"
