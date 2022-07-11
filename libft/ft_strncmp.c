/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:50:30 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/11 17:51:26 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t  i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
			if (s1[i] != s2[i])
					return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
	}
	return (0);
}
