/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:10:27 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/07 18:10:30 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	size_t	i;

	i = ft_strlen(src);
	if (!c)
		return ((char *)src + i);
	while (i)
	{
		if (((char *)src)[--i] == (char)c)
			return ((char *)src + i);
	}
	return (NULL);
}
