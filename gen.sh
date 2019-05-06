#!/bin/bash

set -e

EXE=$1
gcc --ansi -lm -o $EXE $EXE.c
chmod +x $EXE
shift
./$EXE "$@"
