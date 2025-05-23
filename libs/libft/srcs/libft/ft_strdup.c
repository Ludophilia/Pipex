/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:23:16 by jegerman          #+#    #+#             */
/*   Updated: 2025/05/16 16:18:49 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dupl;

	size = ft_strlen(s);
	dupl = malloc((size + 1) * sizeof(char));
	if (dupl == NULL)
		return (NULL);
	dupl = ft_memcpy(dupl, s, size + 1);
	return (dupl);
}
