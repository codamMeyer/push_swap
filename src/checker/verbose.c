#include "verbose.h"
#include <stdio.h>

void	print_final_result(const t_stack *stack_a)
{
    int i;

    i = stack_a->top;
    printf("\n\n************************* FINAL RESULT ************************\n\n");

    while (i >= 0)
    {
        printf("  |%3d|\n", stack_a->elements[i]);
        --i;
    }
    printf("\nstack A\n");
    printf("\n***************************************************************\n\n");

}

void	print_initial_state(const t_stack *stack_a)
{
    int i;

    i = stack_a->top;
    printf("\n\n************************ INITIAL STATE ***********************\n\n");

    while (i >= 0)
    {
        printf("  |%3d|\n", stack_a->elements[i]);
        --i;
    }
    printf("\nstack A\n");
}
