#!/bin/bash

printf "\n\nRUNNING TEST\n\n"

# ARG="4 67 3 87 23"
ARG="2 1"
./push_swap $ARG | ./checker $ARG

ARG="5 4 3 2 1"
./push_swap $ARG | ./checker $ARG


ARG="20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 -18 -19 -20"
./push_swap $ARG | ./checker $ARG