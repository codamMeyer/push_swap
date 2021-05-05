#include "merge_sort.h"
#include <stack/stack.h>
#include <stack/processor.h>
#include <stdlib.h>
#include <math.h>

static t_bool    is_stack_sorted(const t_stack *stack_a, int initial_size)
{
	const int	stack_size = size(stack_a);
	int			i;

	i = 1;
	if (stack_size != initial_size)
		return (FALSE);
	while (i < stack_size)
	{
		if (stack_a->elements[i] > stack_a->elements[i - 1])
			return (FALSE);
		++i;
	}
	return (TRUE);
}

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
               int *elements, \
               t_write_instruction write_instruction)
{
     int num_moves;
     t_stack_pair stacks;
     int visited;

     stacks = create_stack_pair(elements_size);
     if (!stacks.initialized)
          return (0);
     populate_stack_a(elements, elements_size, &stacks);
     visited = 0;
     num_moves = 0;
     if (elements_size < 2)
     {
          destroy_stack_pair(&stacks);
          return (num_moves);
     }
     while (TRUE)
     {
          if (visited + 1 >= elements_size)
          {
               ra(&(stacks));
               write_instruction(STR_RA, 1);
               ++num_moves;
          }
          else if (stacks.a.elements[stacks.a.top] > stacks.a.elements[stacks.a.top - 1])
          {
               sa(&stacks);
               write_instruction(STR_SA, 1);
               ++num_moves;
          }
          visited += 2;
          if (is_stack_sorted(&stacks.a, elements_size))
               return (num_moves);
          if (visited > elements_size)
               break ;
          write_instruction(STR_RA, 2);
          num_moves += 2;
     }
     visited = 0;
     while(visited < ceil((double)elements_size / 2.0))
     {
          if (stacks.a.elements[stacks.a.top] < stacks.a.elements[stacks.a.top - 1])
          {
               sa(&(stacks));
               write_instruction(STR_SA, 1);
               pb(&(stacks));
               write_instruction(STR_PB, 1);
               num_moves += 2;
          }
          if (stacks.b.elements[stacks.b.top] > stacks.b.elements[stacks.b.top - 1])
          {
               sb(&(stacks));
               write_instruction(STR_SB, 1);
               ++num_moves;
          }
          ++visited;
     }
     destroy_stack_pair(&stacks);
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