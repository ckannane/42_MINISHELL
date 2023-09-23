/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:49:43 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/23 11:42:16 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fill_the_quotes(char *str, char curr_char, char curr, int res)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	result = ft_calloc(res + 1, 1);
	curr = '\0';
	while (str[i] != '\0')
	{
		curr_char = str[i];
		if ((curr_char == '\'' || curr_char == '"') && curr == '\0')
			curr = curr_char;
		else if (curr_char == curr)
			curr = '\0';
		else
			result[j++] = curr_char;
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*return_without_quote(char *str)
{
	char	curr;
	int		res;
	char	curr_char;
	int		i;
	char	*result;

	i = 0;
	curr = '\0';
	res = ft_strlen(str);
	while (str[i] != '\0')
	{
		curr_char = str[i];
		if ((curr_char == '\'' || curr_char == '"') && curr == '\0')
			curr = curr_char;
		else if (curr_char == curr)
		{
			curr = '\0';
			res--;
		}
		i++;
	}
	result = fill_the_quotes(str, curr_char, curr, res);
	free(str);
	return (result);
}

char	*set_command(char **slp)
{
	int		i;
	char	*str;

	i = 0;
	if (slp == NULL)
		return (ft_strdup(""));
	if ((ft_strcmp(slp[0], ">") == 0 || ft_strcmp(slp[0], ">>") == 0 \
	|| ft_strcmp(slp[0], "<") == 0 || ft_strcmp(slp[0], "<<") == 0) && \
	slp[1] == NULL)
		return (NULL);
	if ((ft_strcmp(slp[0], ">") == 0 || ft_strcmp(slp[0], ">>") == 0 \
	|| ft_strcmp(slp[0], "<") == 0 || ft_strcmp(slp[0], "<<") == 0))
	{
		if (slp[2] == NULL)
			return (NULL);
		else
		{
			str = ft_strdup(slp[2]);
			return (ft_strdup(return_without_quote(str)));
		}
	}
	str = ft_strdup(slp[0]);
	return (ft_strdup(return_without_quote(str)));
}

void	exe_builtins(t_com *com, t_zid *zone)
{
	t_val	*current;

	current = zone->env;
	if (ft_strcmp(com->commad, "cd") == 0)
		ft_cd(com, zone);
	else if (ft_strcmp(com->commad, "pwd") == 0)
		ft_pwd(zone);
	else if (ft_strcmp(com->commad, "echo") == 0)
		ft_echo(com, zone);
	else if (ft_strcmp(com->commad, "export") == 0)
		ft_export(com, zone);
	else if (ft_strcmp(com->commad, "unset") == 0)
		ft_unset(com, zone);
	else if (ft_strcmp(com->commad, "exit") == 0)
		ft_exit(com, zone);
	else if (ft_strcmp(com->commad, "env") == 0)
	{
		while (current)
		{
			printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
	}
}
