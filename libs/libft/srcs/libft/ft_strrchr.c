/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:45:52 by jegerman          #+#    #+#             */
/*   Updated: 2025/02/11 15:17:45 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_core.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len + 1)
	{
		if (s[len - i] == (char)c)
			return ((char *)s + len - i);
		++i;
	}
	return (NULL);
}
