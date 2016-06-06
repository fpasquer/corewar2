/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 11:07:53 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/06 20:39:40 by fpasquer         ###   ########.fr       */
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

static char					*get_curent_octet(t_array *array, unsigned int i_grid)
{
	char					*curent_octet;
	char					*tmp;

	if ((curent_octet = ft_itoa_base(array[i_grid].code_hexa, 16)) == NULL)
		return (NULL);
	if (ft_strlen(curent_octet) < 2)
	{
		if ((tmp = ft_strjoin("0", curent_octet)) == NULL)
			return (NULL);
		ft_memdel((void**)&curent_octet);
		curent_octet = tmp;
	}
	return (curent_octet);
}

int							get_hexa(t_vm *vm, unsigned int i_grid,
		unsigned int nb_octet, int *nb)
{
	char					*all_octet;
	char					*curent_octet;
	char					*tmp;
	int						ret;

		fprintf(vm->mem, "i_grid = %u, nb_octet = %u\n", i_grid, nb_octet);
	curent_octet = NULL;
	all_octet = NULL;
	while (nb_octet--)
	{
		if((curent_octet = get_curent_octet(vm->array, i_grid)) == NULL ||
				(tmp = ft_strjoin(all_octet, curent_octet)) == NULL)
			return (-1);
		if (all_octet != NULL)
			ft_memdel((void**)&all_octet);
		ft_memdel((void**)&curent_octet);
		all_octet = tmp;
		i_grid  = (i_grid + 1) % NB_CASE_TAB;
	}
	ret = ft_atoi_base(all_octet, 16, nb);
	// mvwprintw(vm->w_info, line++, 3, "all_octet = %s", all_octet);
	if (all_octet != NULL)
		ft_memdel((void**)&all_octet);
	if (curent_octet != NULL)
		ft_memdel((void**)&curent_octet);
	return (ret);
}
