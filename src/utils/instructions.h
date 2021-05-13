#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H
# define STR_SA "sa"
# define STR_SB "sb"
# define STR_SS "ss"
# define STR_PA "pa"
# define STR_PB "pb"
# define STR_RA "ra"
# define STR_RB "rb"
# define STR_RR "rr"
# define STR_RRA "rra"
# define STR_RRB "rrb"
# define STR_RRR "rrr"

typedef enum e_instructions
{
	END_OF_INSTRUCTIONS = -1,
	INVALID_INSTRUCTION = 0,
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
}	t_instructions;
#endif