int	ft_isprint(int c)
{
	const int	first_printable = 32;
	const int	last_printable = 127;

	return (c >= first_printable && c < last_printable);
}
