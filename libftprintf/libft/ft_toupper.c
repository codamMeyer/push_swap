static int	is_lower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_toupper(int c)
{
	const int	offset = 32;

	if (is_lower(c))
		return (c - offset);
	return (c);
}
