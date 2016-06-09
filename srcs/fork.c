/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:20:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/09 09:06:28 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"
#include "../incs/virtual_machine.h"

// t_player					*copy_with_the_new_index(t_player *plr,
// 		t_player **lst, int i_grid, t_vm *vm)
// {
// 	t_player				*new;
// 	t_player				*curs;

// 	if (lst == NULL || *lst == NULL || plr == NULL ||
// 			(new = ft_memalloc(sizeof(t_player))) == NULL)
// 		return (NULL);
// 	ft_memcpy(new, plr, sizeof(t_player));
// 	if ((new->name = ft_strdup(plr->name)) == NULL)
// 		return (NULL);
// 	if ((new->comment = ft_strdup(plr->comment)) == NULL)
// 		return (NULL);
// 	new->i_grid = plr->i_grid + i_grid;;
// 	curs = (*lst);
// 	while (curs->next != NULL)
// 		curs = curs->next;
// 	new->do_instruction = 0;
// 	curs->next = new;
// 	new->next = NULL;
// 	vm->nb_proces++;
// 	//mvwprintw(vm->w_info, 60, 3, "i_fils = %d, i_pere = %d", new->i_grid, plr->i_grid);
// 	return (new);
// }

t_player					*copy_with_the_new_index(t_player *plr,
		t_player **lst, int i_grid, t_vm *vm)
{
	t_player				*new;
	t_player				*curs;

	if (lst == NULL || *lst == NULL || plr == NULL ||
			(new = ft_memalloc(sizeof(t_player))) == NULL)
		return (NULL);
	ft_memcpy(new, plr, sizeof(t_player));
	if ((new->name = ft_strdup(plr->name)) == NULL)
		return (NULL);
	if ((new->comment = ft_strdup(plr->comment)) == NULL)
		return (NULL);
	new->i_grid = plr->i_grid + i_grid;;
	new->next = (*lst)->next;
	(*lst)->next = new;
	// curs = (*lst);
	// while (curs->next != NULL)
	// curs = curs->next;
	// new->do_instruction = 0;
	// curs->next = new;
	// new->next = NULL;
	vm->nb_proces++;
	//mvwprintw(vm->w_info, 60, 3, "i_fils = %d, i_pere = %d", new->i_grid, plr->i_grid);
	wrefresh(vm->w_info);
	return (new);
}

int							ft_fork(t_vm *vm, t_player *plr)
{
	int						adr;

	if (vm == NULL || plr == NULL)
		return (-1);
	//if (get_hexa(vm, (plr->i_grid + 1) % NB_CASE_TAB, 2, &adr) == -1)
	//	return (-1);
	adr = ft_param_4_octets(vm, plr, 2, (plr->i_grid + 1) % NB_CASE_TAB);
	if (copy_with_the_new_index(plr, &vm->plr, adr, vm) == NULL)
		return (-1);
	plr->i_grid = (plr->i_grid + 3) % NB_CASE_TAB;
	return (0);
}

int							ft_lfork(t_vm *vm, t_player *plr)
{
	int						adr;

	if (vm == NULL || plr == NULL)
		return (-1);
	if (get_hexa(vm, (plr->i_grid + 1) % NB_CASE_TAB, 2, &adr) == -1)
		return (-1);
	if (copy_with_the_new_index(plr, &vm->plr, adr, vm) == NULL)
		return (-1);
	plr->i_grid = (plr->i_grid + 3) % NB_CASE_TAB;
	return (0);
}
