/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:06:16 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/05 19:06:19 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || \
			c == '\r' || c == '\t' || c == '\v');
}
