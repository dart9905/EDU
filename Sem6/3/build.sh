#!/bin/bash
mkdir out
cd out
mpic++ ../main.cpp
qsub ../job.sh
