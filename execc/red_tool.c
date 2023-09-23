/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:28:19 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/23 11:40:36 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	loading_verification(t_val *zone, char *name, char *value)
{
	while (zone)
	{
		if (ft_strcmp(zone->name, name) == 0 && zone->value != \
		NULL && value == NULL)
			return (0);
		if (ft_strcmp(zone->name, name) == 0)
		{
			if (value != NULL)
			{
				free(zone->value);
				zone->value = ft_strdup(value);
			}
			return (0);
		}
		zone = zone->next;
	}
	return (1);
}

int	check_val(t_val *zone, char *content)
{
	char	*name;
	char	*value;
	int		result;

	name = save_before_equal(content);
	value = save_after_equal(content);
	result = loading_verification(zone, name, value);
	free(name);
	free(value);
	return (result);
}

int	search_for_redirection(t_com *com)
{
	int	i;
	int	i_input;
	int	i_output;

	i_input = 0;
	i_output = 0;
	i = 0;
	while (com->slp[i])
	{
		if (ft_strcmp(com->slp[i], ">") == 0)
			i_output++;
		else if (ft_strcmp(com->slp[i], "<") == 0)
			i_input++;
		else if (ft_strcmp(com->slp[i], ">>") == 0)
			i_output++;
		else if (ft_strcmp(com->slp[i], "<<") == 0)
			i_input++;
		i++;
	}
	if (i_input > 0 || i_output > 0)
		return (1);
	return (0);
}

char	*detect_file(char **spl)
{
	char	*pick;
	int		i;

	i = 0;
	while (spl[i])
	{
		if (ft_strcmp(spl[i], ">") == 0 || ft_strcmp(spl[i], ">>") == 0 \
		|| ft_strcmp(spl[i], "<") == 0 || ft_strcmp(spl[i], "<<") == 0)
		{
			i++;
			if (spl[i] == NULL)
				return (NULL);
			pick = ft_strdup(spl[i]);
			return (pick);
		}
		i++;
	}
	return (NULL);
}

void	sigcheck(int sig)
{
	if (sig == SIGINT)
		exit(0);
}
