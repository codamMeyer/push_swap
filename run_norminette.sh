#!/bin/sh

SUCCESS_COLOR="\033[01;32m"
ERROR_COLOR="\033[01;31m"

NORM_ERROR=$(norminette src_checker/ src_push_swap/ | grep "Error! ")

if [ $NORM_ERROR ]
then
printf "$ERROR_COLOR NORM ERROR :(\n"

else
printf "$SUCCESS_COLOR NORM IS OK :)\n"
fi

exit $NORM_ERROR