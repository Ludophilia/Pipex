/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:45 by jegerman          #+#    #+#             */
/*   Updated: 2025/02/11 15:19:08 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_core.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (size > 0 && (nmemb != (nmemb * size) / size))
		return (NULL);
	buffer = malloc(nmemb * size);
	if (buffer)
		ft_bzero(buffer, nmemb * size);
	return (buffer);
}
