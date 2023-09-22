/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:01:47 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/22 16:02:15 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_of_herdoc(t_com *com, char *heredoc, int i)
{
	int	sig;

	sig = 0;
	while (com->slp[++i])
	{
		if (ft_strcmp(com->slp[i], "<<") == 0)
		{
			while (1)
			{
				signal(SIGINT, sigcheck);
				signal(SIGQUIT, SIG_IGN);
				heredoc = readline("\033[0;32mheredoc\033[0m> ");
				if (heredoc == NULL)
					sig = 1;
				if (*heredoc)
					ft_putendl_fd(heredoc, com->input);
				if (sig || ft_strcmp(heredoc, com->slp[i + 1]) == 0)
				{
					free(heredoc);
					break ;
				}
				free(heredoc);
			}
		}
	}
}

void	herdoc(t_com *com)
{
	char	*heredoc;
	int		sig;
	int		i;

	i = -1;
	sig = 0;
	heredoc = NULL;
	com->input = open("/tmp/s7i7.txt", O_CREAT | O_WRONLY | O_APPEND, 0777);
	fill_of_herdoc(com, heredoc, i);
	close(com->input);
	com->herdo = open("/tmp/s7i7.txt", O_RDONLY);
	unlink("/tmp/s7i7.txt");
	dup2(com->herdo, STDIN_FILENO);
	close(com->herdo);
}
