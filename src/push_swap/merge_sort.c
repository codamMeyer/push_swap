#include "merge_sort.h"
#include <stdlib.h>

int swap_if_needed(int *stack, int i, t_write_instruction write_instruction)
{
     if (stack[i] < stack[i - 1])
     {
          swap_elements(&stack[i], &stack[i - 1]);
          write_instruction(STR_RA, 1);
          return (1);
     }
     return (0);
}

int	merge_sort(int elements_size, \
				int *stack_a, \
				t_write_instruction write_instruction)
{
     int num_moves;
     int *stack_b;
     int i_a;

     i_a = 0;
     num_moves = 0;
     if (elements_size < 2 || is_list_sorted(elements_size, stack_a))
          return (num_moves);
     stack_b = malloc(sizeof(int) * elements_size);
     if (!stack_b)
          return (0);
     while (i_a < elements_size)
     {
          if (i_a + 1 == elements_size)
               num_moves += swap_if_needed(stack_a, i_a, write_instruction);
          ++i_a;
     }
     (void)stack_a;
     (void)write_instruction;
     free(stack_b);
     return (num_moves);
}

/*
void merge_sort(int *elements, int elements_size)
{
     int element_index = 0;
     while(element_index < elements_size)
    {
        if(element_index + 1 >= element_size)
           ra
        compare elements[i] and i+1
         swap if i > i+1, then rotateA twice
         element_index += 2;
    }

     int * stack_b;
     element_index = 0;
     while(element_index < ceil((double)elements_size/2.0))
    {
         if element[i] < element[i+1] sa then pb
         compare elements of b, swap if new element is bigger
         element_index +=1
    }
}
*/

/*
initial state               -> [5, 3, 4, 1, 2, 6, 7]
element_i = 0 -> sa ra ra   -> [3, 5, 4, 1, 2, 6, 7]
element_i = 2 -> sa ra ra   -> [3, 5, 1, 4, 2, 6, 7]
element_i = 4 ->    ra ra
element_i = 6 ->       ra


actual state             -> A [3, 5, 1, 4, 2, 6, 7] | B [_, _, _, _, _, _, _]
element_i = 0 -> sa pb   -> A [_, 3, 1, 4, 2, 6, 7] | B [_, _, _, _, _, _, 5]
element_i = 1 ->    pb   -> A [_, _, 1, 4, 2, 6, 7] | B [_, _, _, _, _, 3, 5]
element_i = 2 -> sa pb sb-> A [_, _, _, 1, 2, 6, 7] | B [_, _, _, _, 3, 4, 5]
element_i = 3 ->    pb   -> A [_, _, _, _, 2, 6, 7] | B [_, _, _, 1, 3, 4, 5]

actual state              -> A [_, _, _, _, 2, 6, 7] | B [_, _, _, 1, 3, 4, 5]
element_i = 0 -> pa ra    -> A [_, _, _, 2, 6, 7, 1] | B [_, _, _, _, 3, 4, 5]
element_i = 1 -> ra       -> A [_, _, _, 6, 7, 1, 2] | B [_, _, _, _, 3, 4, 5]
element_i = 2 -> pa ra    -> A [_, _, 6, 7, 1, 2, 3] | B [_, _, _, _, _, 4, 5]
element_i = 3 -> pa ra    -> A [_, 6, 7, 1, 2, 3, 4] | B [_, _, _, _, _, _, 5]
element_i = 4 -> pa       -> A [5, 6, 7, 1, 2, 3, 4] | B [_, _, _, _, _, _, _]
element_i = 3 -> ra ra ra -> A [1, 2, 3, 4, 5, 6, 7] | B [_, _, _, _, _, _, _]


initial state         -> A [5, 1, 2, 4, 3] | B [_, _, _, _, _]
pa                    -> A [_, 1, 2, 4, 3] | B [_, _, _, _, 5]
ra ra                 -> A [_, 4, 3, 1, 2] | B [_, _, _, _, 5]
sa                    -> A [_, 3, 4, 1, 2] | B [_, _, _, _, 5]
ra ra                 -> A [_, 1, 2, 3, 4] | B [_, _, _, _, 5]
pa ra                 -> A [1, 2, 3, 4, 5] | B [_, _, _, _, _]

sa sb ss ra rb rr rra rrb rrr pa pb
*/