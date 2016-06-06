/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:20:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/06 20:30:10 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"
#include "../incs/virtual_machine.h"

t_player					*copy_with_the_new_index(t_player *plr,
		t_player **lst, int i_grid,t_vm *vm)
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
	new->i_grid = i_grid;
	curs = (*lst);
	while (curs->next != NULL)
		curs = curs->next;
	curs->next = new;
	new->next = NULL;
	plr->i_grid = (plr->i_grid + 3) % NB_CASE_TAB;
	vm->nb_proces++;
	return (new);
}

int							ft_fork(t_vm *vm, t_player *plr)
{
	int						adr;

<<<<<<< HEAD
	fprintf(vm->mem, "test\n");
	if (vm == NULL || plr == NULL)
		return (-1);
	if (get_hexa(vm, plr->i_grid + 1, 2, &adr) == -1)
		return (-1);
	if (copy_with_the_new_index(plr, &vm->plr, adr, vm) == NULL)
		return (-1);
=======
	if (get_hexa(vm, (plr->i_grid + 1) % NB_CASE_TAB, 2, &val) == -1)
		return (-1);
	// mvwprintw(vm->w_info, 61, 3, "val = %d", val);
	//	if ((vm->plr = copy_with_the_new_index(vm->plr->next, &vm->plr, 45)) == NULL)
	//		return (-1);
>>>>>>> 9c1746bb08f044b7c37e2375208a3adfba85ec0c
	return (0);
}
/*
int							ft_lfork(t_vm *vm, t_player *plr)
{
	int						adr;

	if (vm == NULL || plr == NULL)
		return (-1);
	if (get_hexa(vm, plr->i_grid, 2, &adr) == -1)
		return (-1);
	if (copy_with_the_new_index(plr, &vm->plr, adr, vm) == NULL)
		return (-1);
	return (0);
}*/
