/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:38:31 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/23 11:40:42 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_com(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], ">>") == 0 || ft_strcmp(str[i], "<<") == 0 || \
		ft_strcmp(str[i], ">") == 0 || ft_strcmp(str[i], "<") == 0)
			j++;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], ">>") == 0 || ft_strcmp(str[i], "<<") == 0 || \
		ft_strcmp(str[i], ">") == 0 || ft_strcmp(str[i], "<") == 0)
		{
			j--;
			if (j == 0 && (str[i + 1] != NULL && str[i + 2] != NULL))
				return (i + 2);
		}
		i++;
	}
	return (0);
}

int	looking_for_her(char **slp)
{
	int	i;

	i = 0;
	while (slp[i])
	{
		if (ft_strcmp(slp[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}
