#!/bin/bash
mkdir out
cd out
mpic++ ../main.cpp
qsub -v arg=20 ../job.sh
