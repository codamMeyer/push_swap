#include "parse_flags.h"
#include <ft_printf.h>
#include <libft.h>
#include <stdio.h>

static t_flags	create_empty_flag(void)
{
	const t_flags	flags = {
		.verbose = FALSE,
		.file_output = FALSE,
		.total = FALSE,
		.is_valid = TRUE
	};

	return (flags);
}

static void	display_help_menu(void)
{
	ft_printf("\nusage:  ./checker <flags> [numeric arguments]\n");
	ft_printf("\n-v Print stacks on screen after each movement\n");
	ft_printf("   and display manipulated numbers in different color\n");
	ft_printf("\n-t Display the total of movements\n");
	ft_printf("\n-f Write the final stack to a file called result\n");
}

static void	set_flags(const char *str, t_flags *flags)
{
	char	cur;

	++str;
	cur = *str;
	while (cur != '\0' && flags->is_valid)
	{
		if (cur == HELP)
		{
			display_help_menu();
			flags->is_valid = FALSE;
		}
		else if (cur == VERBOSE)
			flags->verbose = TRUE;
		else if (cur == FILE_OUTPUT)
			flags->file_output = TRUE;
		else if (cur == TOTAL)
			flags->total = TRUE;
		else
			flags->is_valid = FALSE;
		++str;
		cur = *str;
	}
}

static t_bool	is_flag(const char *str)
{
	const int	len = ft_strlen(str);

	return (str[0] == '-' && \
			!ft_isdigit(str[1]) && \
			len >= 2 && len <= 4);
}

t_flags	parse_flags(const char *str[], int *argc, int *i)
{
	t_flags		flags;

	flags = create_empty_flag();
	while (*argc >= 1 && is_flag(str[*i]) && flags.is_valid)
	{
		set_flags(str[*i], &flags);
		--(*argc);
		++(*i);
	}
	return (flags);
}
