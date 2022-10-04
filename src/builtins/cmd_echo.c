#include "minishell.h"

static int nb_args (char **args)
{

	int size;

	size = 0;
	while(args[size])
		size++;
	return(size);
}


int ft_echo(char **args)
{
	int i;
	int n_option;

	i = 1;
	n_option = 0;
      	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i],"-n") == 0)
		{
			n_option = 1 ;
			i++;
		}
		while (args[1])
		{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[1][0] != '\0')
			write(1," ",1);
		i++;
		}
	}	
	if(n_option == 0)
		write(1,"\n",1);
	return(0);

}

int ft_echo2(char *src)
{
	int i;

	i = 4;
	i = no_space(src, i);
	while (src[i])
	{
		write(1, &src[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
