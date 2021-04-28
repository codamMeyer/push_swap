#ifndef BUBBLE_SORT_H
# define BUBBLE_SORT_H

typedef void(*t_write_instruction)(const char *, int);
int	bubble_sort(int elements_size, \
				int *elements, \
				t_write_instruction write_instruction);

#endif