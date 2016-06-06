/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:20:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/06 16:57:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"
#include "../incs/virtual_machine.h"

t_player					*copy_with_the_new_index(t_player *plr,
		t_player **lst, int i_grid)
{
	t_player				*new;
	t_player				*curs;

	if ((new = ft_memalloc(sizeof(t_player))) == NULL || lst == NULL ||
			*lst == NULL)
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
	return ((*lst));
}

int							ft_fork(t_vm *vm, t_player *plr)
{
	int						val;

	if (get_hexa(vm, (plr->next->next->i_grid + 1) % NB_CASE_TAB, 2, &val) == -1)
		return (-1);
	mvwprintw(vm->w_info, 61, 3, "val = %d", val);
//	if ((vm->plr = copy_with_the_new_index(vm->plr->next, &vm->plr, 45)) == NULL)
//		return (-1);
	return (0);
}
