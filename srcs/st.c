/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 15:58:03 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/07 17:17:13 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"
#include "../incs/virtual_machine.h"

int							ft_st(t_vm *vm, t_player *plr)
{
	int						reg;
	int						adr;
	int						type;
	int						decalage;

	if (get_hexa(vm, (plr->i_grid + 1) % NB_CASE_TAB, 1, &type) == -1)
		return (0);
	type = type >> 4;
	if (!(type == 5 || type == 7))
		return (1);
	if (get_hexa(vm, (plr->i_grid + 2) % NB_CASE_TAB, 1, &reg) == -1)
		return (0);
	decalage = type == 5 ? 1 : 2;
	if (get_hexa(vm, (plr->i_grid + 3) % NB_CASE_TAB, decalage, &adr)
			== -1)
		return (0);
	if (type == 5)
		plr->reg[adr] = plr->reg[reg];
	else
		ft_print_param_to_array_4_octets(vm, plr, adr, plr->reg[reg]);
	plr->i_grid = (plr->i_grid + decalage + 3) % NB_CASE_TAB;
	return (0);
}
