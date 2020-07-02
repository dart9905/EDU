#!/bin/bash
mkdir out
cd out
mpic++ ../main.cpp
qsub -v arg=25 ../job.sh
