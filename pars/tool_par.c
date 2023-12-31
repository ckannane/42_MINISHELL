/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_par.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:27 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/23 11:39:36 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_slp_p	*init_slp_p(void)
{
	t_slp_p	*val;

	val = (t_slp_p *)malloc(sizeof(t_slp_p));
	val->initial_capacity = 10;
	val->word_count = 0;
	val->inside_quotes = 0;
	val->word_start = 0;
	val->i = 0;
	return (val);
}

void	fill_it(t_slp_p *val, char *word, char *input, char **words)
{
	char	**new_words;

	if (val->i > val->word_start)
	{
		word = (char *)malloc(val->i - val->word_start + 1);
		ft_strncpy(word, input + val->word_start, val->i - val->word_start);
		word[val->i - val->word_start] = '\0';
		words[val->word_count++] = word;
		if (val->word_count == val->initial_capacity)
		{
			val->initial_capacity *= 2;
			new_words = (char **)malloc(val->initial_capacity * sizeof(char *));
			ft_memcpy(new_words, words, val->word_count * sizeof(char *));
			free(words);
			words = new_words;
		}
	}
	val->word_start = val->i + 1;
}

char	**splitstring(char *input)
{
	t_slp_p	*val;
	char	*word;
	char	**words;

	word = NULL;
	val = init_slp_p();
	words = (char **)malloc(val->initial_capacity * sizeof(char *));
	while (input[val->i] != '\0')
	{
		if (input[val->i] == '"')
			val->inside_quotes = !val->inside_quotes;
		else if (input[val->i] == '|' && !val->inside_quotes)
			fill_it(val, word, input, words);
		val->i++;
	}
	if (val->i > val->word_start)
	{
		word = (char *)malloc(val->i - val->word_start + 1);
		ft_strncpy(word, input + val->word_start, val->i - val->word_start);
		word[val->i - val->word_start] = '\0';
		words[val->word_count++] = word;
	}
	words[val->word_count] = NULL;
	free(val);
	return (words);
}

void	re_shap_slp(char **slp)
{
	int	i;

	i = 0;
	while (slp[i])
	{
		slp[i] = return_without_quote(slp[i]);
		i++;
	}
}

void	read_com(t_com *com, t_zid __unused *zone, char __unused *line)
{
	int	num_args;
	int	n;

	com->word = redirection_split(com->word);
	com->slp = ft_splito(com->word);
	re_shap_slp(com->slp);
	if (com->slp[0] == NULL)
		return ;
	n = find_com(com->slp);
	com->commad = ft_strdup(com->slp[n]);
	if (com->commad == NULL)
		return ;
	num_args = set_arg_size(com, n);
	if (num_args == 0)
		return ;
	install_arg(com, num_args, n);
}
