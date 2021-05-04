#include <inc/int_to_hex.h>
#include <inc/int_to_hex_helpers.h>

char	*ulong_int_to_hex(unsigned long int nbr, int to_upper)
{
	return (put_long_number(nbr, to_upper));
}

char	*int_to_hex(int nbr, int to_upper)
{
	return (put_number(nbr, to_upper));
}
