/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:11:46 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/26 00:05:13 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source )
{
	char	*dest;
	size_t	len;
	size_t	i;
	len = ft_strlen(source);
	i = 0;
	dest = (char *)ft_malloc(len + 1);

	if (!dest)
		return (0);
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
