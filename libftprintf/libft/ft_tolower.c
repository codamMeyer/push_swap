static	int	is_upper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_tolower(int c)
{
	const int	offset = 32;

	if (is_upper(c))
		return (c + offset);
	return (c);
}
