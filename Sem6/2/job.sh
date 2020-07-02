#!/bin/bash

#PBS -lwalltime=00:10:00,nodes=5:ppn=4
#PBS -N BIG_BOSS
#PBS -q batch

cd $PBS_O_WORKDIR
cd out
mpirun --hostfile $PBS_NODEFILE -np 20 a.out ${arg}
rm -rf a.out
