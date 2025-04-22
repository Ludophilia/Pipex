/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:10:18 by jegerman          #+#    #+#             */
/*   Updated: 2025/02/11 15:17:56 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_core.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	sublen;
	size_t	i;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	sublen = 0;
	while (start + sublen < slen && sublen < len)
		++sublen;
	sub = ft_calloc(sublen + 1, sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < sublen)
	{
		sub[i] = s[start + i];
		++i;
	}
	return (sub);
}
