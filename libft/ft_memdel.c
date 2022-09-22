#include "libft.h"

void *ft_memdel(void *ptr)
{
	if(ptr)
	{
		free(ptr);
		ptr = NULL;
	}
return (NULL);
}
