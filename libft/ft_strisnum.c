#include "libft.h"

int ft_strisnum(const char *str)
{
	int i;

	i = 0;
	if(str == NULL)
			return(0);
	if(str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return(0);
		i++;
	}
	return (1);
}
