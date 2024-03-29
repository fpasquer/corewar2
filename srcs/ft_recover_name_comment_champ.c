/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_name_comment_champ.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 10:27:33 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/16 10:29:03 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"

/*
** name_champ[4], car les 4 premiers caracteres
** corresponds a : 0, -22, -125, -13. Utilite ?
** 128, car c'est la taille maximum d'un nom qu'un
** champ peut avoir
*/

char						*ft_recover_name_champ(int fd)
{
	unsigned char			name_champ[132];

	ft_bzero(name_champ, 132);
	if (read(fd, name_champ, 132) == -1)
		return (NULL);
	return (ft_strndup((char*)&name_champ[4], 128));
}

/*
** Les 8 premiers octects correspondent a : ?
*/

char						*ft_recover_comment_champ(int fd, int *champ_size)
{
	unsigned char			comment[2060];
	int						i;
	int						y;

	i = 7;
	y = 0;
	ft_bzero(comment, 2060);
	read(fd, comment, 2060);
	while (i >= 0)
	{
		if (comment[i] > 0)
			*champ_size = *champ_size + ((ft_power(y, 16)) * comment[i]);
		y++;
		i--;
	}
	return (ft_strndup((char*)&comment[8], 2060 - (8)));
}
