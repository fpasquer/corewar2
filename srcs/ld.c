/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 15:04:59 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/07 16:04:31 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"
#include "../incs/virtual_machine.h"

int							ft_ld(t_vm *vm, t_player *plr)
{
	int						val;
	int						reg;
	int						type;
	int						decalage;

	if (get_hexa(vm, (plr->i_grid + 1) % NB_CASE_TAB, 1, &type) == -1)
		return (0);
	type = type >> 4;
	if (!(type == 9 || type == 13))
		return (1);
	decalage = type == 9 ? 4 : 2;
	if (get_hexa(vm, (plr->i_grid + 2) % NB_CASE_TAB, decalage, &val) == -1)
		return (0);
	if (get_hexa(vm, (plr->i_grid + 2 + decalage) % NB_CASE_TAB, 1, &reg) == -1)
		return (0);
	if (reg < 1 || reg > 16)
		return (1);
	plr->reg[reg] = val;
	plr->i_grid = (plr->i_grid + 3 + decalage) % NB_CASE_TAB;
	plr->carry = val == 0 ? 1 : 0;
	return (1);
}

int							ft_lld(t_vm *vm, t_player *plr)
{
	int						val;
	int						reg;
	int						type;
	int						decalage;

	if (get_hexa(vm, (plr->i_grid + 1) % NB_CASE_TAB, 1, &type) == -1)
		return (0);
	type = type >> 4;
	if (!(type == 9 || type == 13))
		return (1);
	decalage = type == 9 ? 4 : 2;
	if (get_hexa(vm, (plr->i_grid + 2) % NB_CASE_TAB, decalage, &val) == -1)
		return (0);
	if (get_hexa(vm, (plr->i_grid + 2 + decalage) % NB_CASE_TAB, 1, &reg) == -1)
		return (0);
	if (reg < 1 || reg > 16)
		return (1);
	plr->reg[reg] = val;
	plr->i_grid = (plr->i_grid + 3 + decalage) % NB_CASE_TAB;
	plr->carry = val == 0 ? 1 : 0;
	return (1);
}
