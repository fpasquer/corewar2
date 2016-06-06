/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 09:49:33 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/06 15:37:58 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"
#include "../incs/corewar.h"

static void					print_flags(t_vm *vm)
{
	mvwprintw(vm->w_info, 21 + vm->nb_player * 3 + 1, 3, "FLAGS :");
	if ((vm->flags & DUMP) != 0)
		mvwprintw(vm->w_info, 22 + vm->nb_player * 3 + 1, 5,
				"DUMP    : Yes / %d", vm->nb_dump);
	else
		mvwprintw(vm->w_info, 22 + vm->nb_player * 3 + 1, 5, "DUMP    : No");
	if ((vm->flags & SUSPEND) != 0)
		mvwprintw(vm->w_info, 23 + vm->nb_player * 3 + 1, 5,
				"SUSPEND : Yes / %d", vm->nb_susp);
	else
		mvwprintw(vm->w_info, 23 + vm->nb_player * 3 + 1, 5, "SUSPEND : No");
	mvwprintw(vm->w_info, 24 + vm->nb_player * 3 + 1, 5, "NUMBER  : %s",
			(vm->flags & NUMBER) != 0 ? "Yes" : "No");
	if ((vm->flags & DUMP_M) != 0)
		mvwprintw(vm->w_info, 25 + vm->nb_player * 3 + 1, 5,
				"DUMP_M  : Yes / %d", vm->nb_dump);
	else
		mvwprintw(vm->w_info, 25 + vm->nb_player * 3 + 1, 5, "DUMP_M  : No");
}

void						print_dump(t_vm *vm)
{
	if (vm->dump != vm->cycle)
		return ;
	ft_putnbr_fd(vm->cycle, vm->fd);
	ft_putchar_fd('\n', vm->fd);
	if ((vm->flags & DUMP_M) != 0)
		vm->dump += vm->nb_dump;
}

void						print_players(t_vm *vm)
{
	int						mem;
	unsigned int			i;
	t_player				*curs;

	curs = vm->plr;
	i = 0;
	while (i < vm->nb_player)
	{
		mem = 8 + i;
		mvwprintw(vm->w_info, 11 + i * 4, 3, "Name %d : ", curs->reg[1]);
		init_pair(i + 1, i + 1, COLOR_BLACK);
		attron(COLOR_PAIR(i + 1));
		mvwprintw(stdscr, 11 + i * 4, 210,"%s", curs->name);
		attroff(COLOR_PAIR(i + 1));
		mvwprintw(vm->w_info, 12 + i * 4, 5, "Last live : %u", curs->last_live);
		mvwprintw(vm->w_info, 13 + i * 4, 5, "Nb live : %u", curs->nb_live);
		curs = curs->next;
		i++;
	}
	wrefresh(vm->w_info);
}

void						print_info(t_vm *vm)
{
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

// void						print_grid(t_vm *vm)
// {
// 	unsigned int			x;
// 	unsigned int			y;
// 	unsigned int			decalage;

// 	y = 0;
// 	while (y < NB_LINE_COLUMN)
// 	{
// 		x = 0;
// 		decalage = 0;
// 		while (x < NB_LINE_COLUMN * 2)
// 		{
// 			mvwprintw(vm->w_grid, y + 1, x + 2 + decalage, "%c",
// 					vm->grid2d[y][x] + ((vm->grid2d[y][x] > 0 &&
// 					vm->grid2d[y][x] < 9) ? '0' : 'A'));
// 			decalage = (x % 2 == 1) ? decalage + 1 : decalage;
// 			x++;
// 		}
// 		y++;
// 	}
// 	wrefresh(vm->w_grid);
// }
/*
void						print_grid(t_vm *vm)
{
	unsigned int			x;
	unsigned int			y;
	int 					size;
	char 					*tmp;
	int 					count;
	int 					count2;

	count2 = 0;
	count = 0;
	y = 0;
	x = 0;
	while (y < NB_LINE_COLUMN)
	{
	//	if (!vm->array[count2].player)
	//		vm->array[count2].player = 7;
		init_pair(vm->array[count2].player, vm->array[count2].player, COLOR_BLACK);
		attron(COLOR_PAIR(vm->array[count2].player));
		tmp = ft_llitoa_base(vm->array[count].code_hexa, 16, &size);
		mvwprintw(stdscr, y + 1, x + 2, "%s ", tmp);
		attroff(COLOR_PAIR(vm->array[count2].player));
		ft_strdel(&tmp);
		count2++;
		count++;
		x += 3;
		if (x > 190 && ++y)
			x = 0;
	}
	wrefresh(vm->w_grid);
}*/

static int					return_color_grid(t_vm *vm, unsigned int position)
{
	unsigned int			i;
	t_player				*curs;

	curs = vm->plr;
	i = 0;
	if (vm->array[position].player == 0)
		return (0);
	while (i < vm->nb_player && curs != NULL)
	{
		if (position == curs->i_grid)
			return (i + 5);
		curs = curs->next;
		i++;
	}
	return (vm->array[position].player);
}

void						print_nb_in_grid(t_vm *vm, int i,
		unsigned int y, unsigned int x)
{
	char 					*tmp;
	int 					size;
	int						color;

	attron(COLOR_PAIR((color = return_color_grid(vm, i))));
	// attron(COLOR_PAIR(vm->array[i].player));
	tmp = ft_llitoa_base(vm->array[i].code_hexa, 16, &size);
	mvwprintw(stdscr, y + 1, x + 2, "%s", tmp);
	attroff(COLOR_PAIR(color));
	ft_strdel(&tmp);
}


void						print_grid(t_vm *vm)
{
	unsigned int			x;
	unsigned int			y;
	int 					count2;

	count2 = 0;
	y = 0;
	x = 0;
	while (y < NB_LINE_COLUMN)
	{
		print_nb_in_grid(vm, count2++, y, x);
		x += 3;
		if (x > 190 && ++y)
			x = 0;
	}
	wrefresh(vm->w_grid);
}
