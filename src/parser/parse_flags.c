#include "parse_flags.h"
#include <libft.h>

t_flags	create_empty_flag(void)
{
	const t_flags	flags = {
		.color = FALSE,
		.verbose = FALSE,
		.file_output = FALSE,
		.is_valid = TRUE
	};

	return (flags);
}

void	set_flags(const char *str, t_flags *flags)
{
	char	cur;

	++str;
	cur = *str;
	while (cur != '\0' && flags->is_valid)
	{
		if (cur == COLOR)
			flags->color = TRUE;
		else if (cur == VERBOSE)
			flags->verbose = TRUE;
		else if (cur == FILE_OUTPUT)
			flags->file_output = TRUE;
		else
			flags->is_valid = FALSE;
		++str;
		cur = *str;
	}
}

t_bool is_flag(const char *str)
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
	while (*argc >= 2 && is_flag(str[*i]) && flags.is_valid)
	{
		set_flags(str[*i], &flags);
		--(*argc);
		++(*i);
	}
	return (flags);
}
