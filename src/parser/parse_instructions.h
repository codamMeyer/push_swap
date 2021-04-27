#ifndef PARSE_INSTRUCTIONS_H
# define PARSE_INSTRUCTIONS_H
# include "../checker/processor.h"

t_instructions	get_instruction(const char *instruction_string);
t_instructions	get_next_instruction(void);

#endif