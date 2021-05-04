int	ft_isascii(int c)
{
	int	first_ascii;
	int	last_ascii;

	first_ascii = 0;
	last_ascii = 127;
	return (c >= first_ascii && c <= last_ascii);
}
