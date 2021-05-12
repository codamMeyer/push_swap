# push_swap [![codamMeyer](https://circleci.com/gh/codamMeyer/push_swap.svg?style=shield)](https://app.circleci.com/pipelines/github/codamMeyer/push_swap?branch=main)

# Instructions
- [x] **sa**

        swap a - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements).

- [x] **sb**

        swap b - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements).

- [x] **ss** 

        sa and sb at the same time.

- [x] **pa**

         push a - take the first element at the top of b and put it at the top of a. Do nothing if b is empty.

- [x] **pb** 

        push b - take the first element at the top of a and put it at the top of b. Do nothing if a is empty.

- [x] **ra** 

        rotate a - shift up all elements of stack a by 1. The first element becomes the last one.

- [x] **rb** 

        rotate b - shift up all elements of stack b by 1. The first element becomes the last one.

- [x] **rr**

        ra and rb at the same time.

- [x] **rra**

        reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one.

- [x] **rrb**

        reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one.

- [x] **rrr** 

        rra and rrb at the same time.

# Functions

- [x] swap
- [x] push
- [x] pop
- [x] rotate
- [x] reverse_rotate
- [x] size

# push_swap parser

- [x] Check if received only numbers (first element is the top of stack)
- [x] Compare with int MIN and MAX
- [x] Check if numbers are duplicated
- [x] On error, display Error followed by a ’\n’ on the standard error.

# Checker parser

- [x] Check if received only numbers (first element is the top of stack)
- [x] Compare with int MIN and MAX
- [x] Check if numbers are duplicated
- [x] If no argument is given checker stops and displays nothing.
- [x] Read instructions on the standard input
- [x] Each instruction will be followed by ’\n’
- [x] Check if instructions are valid
- [x] On error, display Error followed by a ’\n’ on the standard error.

# TODO
- [ ] implement ceil and floor functions
- [x] remove merge sort
- [x] remove bubble sort
- [ ] fix bucket size to work with odd numbers
- [ ] try many bucket sizes
  