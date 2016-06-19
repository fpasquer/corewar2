/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 11:49:11 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/19 11:52:23 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"
#include "../incs/corewar.h"

void						print_dump(t_vm *vm)
{
	if (vm->dump != vm->cycle)
		return ;
	dump_memory(vm);
	if ((vm->flags & DUMP) != 0 && (vm->flags & VISU) == 0)
	{
		del_vm(&vm);
		exit(0);
	}
	if ((vm->flags & DUMP_M) != 0)
	{
		ft_putchar_fd('\n', vm->fd);
		vm->dump += vm->nb_dump;
	}
}

void						print_players(t_vm *vm)
{
	unsigned int			i;

	if ((vm->flags & VISU) == 0)
		return ;
	i = 0;
	while (i < vm->nb_player)
	{
		mvwprintw(vm->w_info, 11 + i * 4, 3, "Name %d : ", vm->nb_rep_plr[i]);
		init_pair(i + 1, i + 1, COLOR_BLACK);
		attron(COLOR_PAIR(i + 1));
		mvwprintw(stdscr, 11 + i * 4, 210, "%s", vm->name_j[i]);
		attroff(COLOR_PAIR(i + 1));
		mvwprintw(vm->w_info, 12 + i * 4, 5, "Last live : %-10u",
				vm->cycle_last_live[i]);
		mvwprintw(vm->w_info, 13 + i * 4, 5, "Nb live : %-10u",
				vm->nb_live_each_plr[i]);
		i++;
	}
}

void						print_info(t_vm *vm)
{
	if ((vm->flags & VISU) == 0)
		return ;
	mvwprintw(vm->w_info, 2, 3, "** %s **  ", vm->status == PAUSE ?
			"PAUSED" : "RUNNNING");
	mvwprintw(vm->w_info, 4, 3, "Cyles/second limit : %d", CYCLE_SEG);
	mvwprintw(vm->w_info, 7, 3, "Cycle %u", vm->cycle);
	mvwprintw(vm->w_info, 9, 3, "Processes : %u         ", vm->nb_proces);
	print_players(vm);
	mvwprintw(vm->w_info, 13 + vm->nb_player * 3 + 1, 3,
			"Cycle to die : %u    ", vm->cycle_to_die);
	mvwprintw(vm->w_info, 15 + vm->nb_player * 3 + 1, 3, "Cycle delta : %d",
			CYCLE_DELTA);
	mvwprintw(vm->w_info, 17 + vm->nb_player * 3 + 1, 3, "NBR_LIVE : %d",
			NBR_LIVE);
	mvwprintw(vm->w_info, 19 + vm->nb_player * 3 + 1, 3, "MAX_CHECK : %d",
			MAX_CHECK);
	print_flags(vm);
	wrefresh(vm->w_info);
}

void						print_hightlight(t_vm *vm, t_player *plr)
{
	char					*tmp;
	int						size;

	while (plr)
	{
		attron(A_STANDOUT);
		attron(COLOR_PAIR(plr->pos));
		tmp = ft_llitoa_base(vm->array[plr->i_grid].code_hexa, 16, &size);
		mvwprintw(stdscr, vm->array[plr->i_grid].y, vm->array[plr->i_grid].x,
				"%s", tmp);
		attroff(A_STANDOUT);
		attroff(COLOR_PAIR(plr->pos));
		plr = plr->next;
		ft_strdel(&tmp);
	}
}
