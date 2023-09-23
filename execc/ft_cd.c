/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:30:39 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/23 11:08:15 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apply_empty_cd(t_zid *zone)
{
	int		found;
	t_val	*current;

	current = zone->env;
	found = 0;
	while (current)
	{
		if (ft_strcmp(current->name, "HOME") == 0)
		{
			found = 1;
			break ;
		}
		current = current -> next;
	}
	if (found == 0)
	{
		perror("cd");
		zone->exito = 1;
	}
	else
		chdir(current->value);
}

void	apply_cd(t_zid *new_path, t_zid	*old_path, t_zid *zone)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		free(old_path->env->value);
		old_path->env->value = ft_strdup(new_path->env->value);
		free(new_path->env->value);
		new_path->env->value = ft_strdup(cwd);
		free(old_path->exp->value);
		old_path->exp->value = ft_strdup(new_path->exp->value);
		free(new_path->exp->value);
		new_path->exp->value = ft_strdup(cwd);
	}
	else
	{
		perror("getcwd");
		zone->exito = 1;
	}
	free (cwd);
}

int	find_pwd(t_val *env)
{
	t_val	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, "PWD") == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	find_the_node(t_zid *target)
{
	while (target->env && ft_strcmp(target->env->name, "PWD") != 0)
		target->env = target->env -> next;
	while (target->exp && ft_strcmp(target->exp->name, "PWD") != 0)
		target->exp = target->exp-> next;
}

void	ft_cd(t_com *com, t_zid *zone)
{
	t_zid	*oldpwd_path;
	t_zid	*pwd_path;

	oldpwd_path = malloc(sizeof(t_zid));
	*oldpwd_path = *zone;
	pwd_path = malloc(sizeof(t_zid));
	*pwd_path = *zone;
	find_the_node(pwd_path);
	find_the_node(oldpwd_path);
	if (com->arg[0] == NULL || (ft_strcmp(com->arg[0], "~") == 0 \
	&& com->arg[1] == NULL))
		apply_empty_cd(zone);
	else if (chdir(com->arg[0]) == -1)
	{
		perror("cd");
		zone->exito = 1;
	}
	if (find_pwd(zone->env))
		apply_cd(pwd_path, oldpwd_path, zone);
	else
		zone->exito = 1;
	free(pwd_path);
	free(oldpwd_path);
}
