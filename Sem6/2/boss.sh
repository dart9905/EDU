#!/bin/bash

#PBS -lwalltime=00:10:00,nodes=1:ppn=2
#PBS -N BIG_BOSS
#PBS -q batch

cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 2 ./big_boss
