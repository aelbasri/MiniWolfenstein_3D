/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:39:15 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/27 11:42:56 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_return_num(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (num[i] >= '1' && num[i] <= '9')
			return (&num[i]);
		i++;
	}
	return (num);
}

t_list	*ft_return(void)
{
	static t_list	head;

	return (&head);
}

void	*ft_malloc(size_t num)
{
	t_list	*head;
	void	*add;

	head = ft_return();
	add = malloc(num);
	ft_lstadd_back(&head, ft_lstnew(add));
	return (add);
}

void	ft_free(void)
{
	t_list	*head;
	t_list	*node;
	int		i;

	head = ft_return();
	i = 0;
	while (head)
	{
		node = head->next;
		free(head->content);
		if (i != 0)
			free(head);
		head = node;
		i++;
	}
}

int ft_strcmp(char *s1 , char *s2)
{
	int i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
