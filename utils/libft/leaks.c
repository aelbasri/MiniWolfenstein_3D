/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:07:35 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/27 19:11:35 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_return(void)
{
	static t_list	head;

	return (&head);
}

void	*ft_malloc(size_t num)
{
	void	*add;
	t_list	*head;

	head = ft_return();
	add = malloc(num);
	ft_lstadd_back(&head, ft_lstnew(add));
	return (add);
}
