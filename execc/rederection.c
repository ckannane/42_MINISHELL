/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:46:14 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/22 16:17:02 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_red(t_com *com, int i)
{
	com->input = open(com->slp[i + 1], O_RDONLY);
	if (dup2(com->input, STDIN_FILENO) == -1)
	{
		perror("Duplication of file descriptor failed");
		exit(1);
	}
	close(com->input);
}

void	output_red(t_com *com, int i)
{
	com->output = open(com->slp[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (dup2(com->output, STDOUT_FILENO) == -1)
	{
		perror("Duplication of file descriptor failed");
		exit(1);
	}
	close(com->output);
}

void	output_d_red(t_com *com, int i)
{
	com->output = open(com->slp[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (dup2(com->output, STDOUT_FILENO) == -1)
	{
		perror("file not found or no premission");
		exit(1);
	}
}

void	apply_fd(t_com *com)
{
	int	i;
	int	herdo_flag;

	herdo_flag = looking_for_her(com->slp);
	i = 0;
	while (com->slp[i])
	{
		if (herdo_flag == 1 && com->slp[i + 1] != NULL)
		{
			herdoc(com);
			herdo_flag = 0;
		}
		else if (ft_strcmp(com->slp[i], ">") == 0 && herdo_flag == 0)
			output_red(com, i);
		else if (ft_strcmp(com->slp[i], ">>") == 0 && herdo_flag == 0)
			output_d_red(com, i);
		else if (ft_strcmp(com->slp[i], "<") == 0 && herdo_flag == 0)
			input_red(com, i);
		i++;
	}
}
