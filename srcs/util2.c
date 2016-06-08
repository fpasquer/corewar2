/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:12:25 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/08 11:15:32 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"
#include "../incs/corewar.h"

static char					*get_curent_octet(t_array *array,
		unsigned int i_grid)
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