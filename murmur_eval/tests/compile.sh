#!/bin/bash
make -C ../ re && cc main.c example-murmur_eval.c -I ../incs/ ../build/libmurmureval.a -D TEST=1 && ./a.out