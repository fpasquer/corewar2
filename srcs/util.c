/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 11:07:53 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/02 18:18:19 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"

void						error(char *s)
{
	ft_putendl(s);
	exit(-1);
}

int							check_key(int key, t_vm *vm)
{
	if (key == ESCAPE)
		return (ESCAPE);
	if (key == SPACE)
		vm->status = vm->status == PAUSE ? RUN : PAUSE;
	else if (key == 410)
		return (REFRESH);
	return (-1);
}

int							**make_tab_2d(int *tab, int height, int width)
{
	int						**ret;
	int						y;
	long long int			i;
	long long int			mem;
	long long int			end;

	if ((ret = ft_memalloc(sizeof(int*) * height)) == NULL)
		return (NULL);
	i = 0;
	mem = 0;
	y = 0;
	end = height * width;
	while (i < end)
	{
		if (i == mem)
		{
			ret[y++] = &tab[i];
			mem += width;
		}
		i++;
	}
	return (ret);
}
