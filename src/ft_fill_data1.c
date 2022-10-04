/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:19:16 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/04 09:39:33 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_infile(t_list *cmd, size_t infile_len)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	cmd->infile = malloc(infile_len + 1);
	while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '<')
		i+= ft_cntchar(cmd->cmd_tmp, '<', i);
	if (cmd->cmd_tmp[i++] == '<')
	{
		if (cmd->cmd_tmp[i] == '<')
		{
			i++;
			cmd->infileflag = 2;
		}
		else
			cmd->infileflag = 1;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] == ' ')
			i++;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != ' ')
		{
			// printf("c: %c\n",cmd->cmd_tmp[i]);
			cpy_between_cotes(cmd->cmd_tmp, cmd->infile, &i, &j);
			// printf("i %d, j %d c=%c cmdinfile %s-\n", i ,j, cmd->cmd_tmp[i], cmd->infile);
			cmd->infile[j++] = cmd->cmd_tmp[i++];
		}
	}
	cmd->infile[j] = 0;
	// printf("fill infile : %s\n", cmd->infile);
}

void	ft_fill_outfile(t_list *cmd, size_t outfile_len)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	cmd->outfile = malloc(outfile_len + 1);
	while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '>')
		i+= ft_cntchar(cmd->cmd_tmp, '>', i);
	if (cmd->cmd_tmp[i++] == '>')
	{
		if (cmd->cmd_tmp[i] == '>')
		{
			i++;
			cmd->outfileflag = 2;
		}
		else
			cmd->outfileflag = 1;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] == ' ')
			i++;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != ' ')
		{
			cpy_between_cotes(cmd->cmd_tmp, cmd->outfile, &i, &j);
			cmd->outfile[j++] = cmd->cmd_tmp[i++];
		}
	}
	cmd->outfile[j] = 0;
}

int	no_space(char *src, int i)
{
	while (src[i] == ' ')
		i++;
	return (i);
}

static int	pass_infile(char *src, int i)
{
	if (src[i] != '<')
		printf("error pass_infile\n");
	i++;
	if (src[i] == '<')
		i++;
	while(src[i] == ' ')
		i++;
	if (src[i] == '\''  )
		i += quotesize(src, i, '\'');
	else if (src[i] == '\"')
		i += quotesize(src, i, '\"');
	while(src[i] != ' ' && src[i] != 0)
		i++;
	while(src[i] == ' '&& src[i] != 0)
		i++;
	return (i);
}

static int	pass_outfile(char *src, int i)
{
	if (src[i] != '>')
		printf("error pass_infile\n");
	i++;
	if (src[i] == '>')
		i++;
	while(src[i] == ' ')
		i++;
	if (src[i] == '\''  )
		i += quotesize(src, i, '\'');
	else if (src[i] == '\"')
		i += quotesize(src, i, '\"');
	while(src[i] != ' ' && src[i] != 0)
		i++;
	while(src[i] == ' '&& src[i] != 0)
		i++;
	return (i);
}

void	cpy_between_cotes(char *src, char *dst, int *i, int *j)
{
	// printf("cpy_between_cotes1\n");
	if (src[*i] == '\'')
	{
		dst[*j] = src[*i];
		(*i)++;
		(*j)++;
		while (src[*i] && src[*i] != '\'')
		{
			// printf("i: %d, j:%i src[i] %c, dst[j] %c\n", *i, *j, src[*i], dst[*j]);
			dst[*j] = src[*i];
			(*i)++;
			(*j)++;
		}
		dst[*j] = src[*i];
		(*i)++;
		(*j)++;
	}
	else if (src[*i] == '\"')
	{
		dst[*j] = src[*i];
		(*i)++;
		(*j)++;
		while (src[*i] && src[*i] != '\"')
		{
			// printf("A i: %d, j:%i src[i] %c, dst[j] %c\n", *i, *j, src[*i], dst[*j]);
			dst[*j] = src[*i];
			(*i)++;
			(*j)++;
			printf("B i: %d, j:%i src[i] %c, dst[j] %c\n", *i, *j, src[*i], dst[*j]);
		}
		dst[*j] = src[*i];
		(*i)++;
		(*j)++;
	}
	printf("cpy_between_cotes2\n");
}

void	ft_clean_cmdline(t_list *cmd)
{
	char	*cmdtemp2;
	int		i;
	int		j;
	int		k;
	char	first_c;

	i = 0;
	j = 0;
	cmdtemp2 = ft_strdup(cmd->cmd_tmp);
	i = no_space(cmd->cmd_tmp, i);
	while(cmd->cmd_tmp[i] && cmd->cmd_tmp[i])
	{
		if (cmd->cmd_tmp[i] == '\'' || cmd->cmd_tmp[i] == '\"')
			cpy_between_cotes(cmdtemp2, cmd->cmd_tmp, &i, &j);
		if (cmd->cmd_tmp[i] == '<')
			i = pass_infile(cmd->cmd_tmp,i);
		else if (cmd->cmd_tmp[i] == '>')
			i = pass_outfile(cmd->cmd_tmp,i);
		else if (cmd->cmd_tmp[i])
		{
			cmdtemp2[j]= cmd->cmd_tmp[i];
			i++;
			j++;
			// printf("i %d, j %d c=%c-\n", i ,j, cmd->cmd_tmp[i]);
		}
		// printf("i %d, j %d c=%c- cmdtemp2:%s-\n", i ,j, cmd->cmd_tmp[i], cmdtemp2);
	}
	while(cmdtemp2[j])
	{
		cmdtemp2[j] = 0;
		j++;
	}
	free (cmd->cmd_tmp);
	cmd->cmd_tmp = ft_strdup(cmdtemp2);
	free (cmdtemp2);
	printf("********\nclean cmd :%s-\n", cmd->cmd_tmp);
}
