#!/bin/bash

printf "\n\nRUNNING TEST\n\n"

# ARG="4 67 3 87 23"
ARG="2 1"
./push_swap $ARG | ./checker $ARG

ARG="5 4 3 2 1"
./push_swap $ARG | ./checker $ARG
