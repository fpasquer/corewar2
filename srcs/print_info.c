/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 09:49:33 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/14 08:14:59 by fpasquer         ###   ########.fr       */
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
	mvwprintw(vm->w_info, 26 + vm->nb_player * 3 + 1, 5,
			"SHOW    : %s", (vm->flags & SHOW) != 0 ? "Yes" : "No");

}

void						dump_print_player(t_vm *vm, int fd)
{
	unsigned int			i;
	t_player				*curs;

	i = 0;
	curs = vm->plr;
	ft_putstr_fd("Introducing contestants...\n", fd);
	while (curs != NULL && i++ < vm->nb_player)
	{
		ft_putstr_fd("* Player ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(", weighing ", fd);
		ft_putnbr_fd(curs->size, fd);
		ft_putstr_fd(" bytes, \"", fd);
		ft_putstr_fd(curs->name, fd);
		ft_putstr_fd("\" (\"", fd);
		ft_putstr_fd(curs->comment, fd);
		ft_putstr_fd("\") !\n", fd);
		curs = curs->next;
	}
}

static int					change_line(t_vm *vm, unsigned int i, char *line)
{
	char					*nb;
	char					*tmp;
	static unsigned int		j = 0;

	if (j == 0)
	{
		if ((nb = ft_itoa_base(i, 16)) == NULL)
			return (-1);
		while (ft_strlen(nb) < 3)
		{
			if ((tmp = ft_strjoin("0", nb)) == NULL)
				return (-1);
			ft_memdel((void**)&nb);
			nb = tmp;
		}
		ft_putstr_fd("0x0", vm->fd);
		ft_putstr_fd(nb, vm->fd);
		ft_putstr_fd(" : ", vm->fd);
		ft_memdel((void**)&nb);
	}
	ft_putstr_fd(line, vm->fd);
	ft_putstr_fd(j == 63 ? " \n" : " ", vm->fd);
	j = j == 63 ? j = 0 : j + 1;
	return (0);
}

static void					dump_memory(t_vm *vm)
{
	char					*s;
	char					*tmp;
	unsigned int			i;

	i = 0;
	if ((vm->flags & DUMP_M) != 0)
	{
		ft_putstr_fd("Cycle : ", vm->fd);
		ft_putnbr_fd(vm->cycle, vm->fd);
		ft_putchar_fd('\n', vm->fd);
	}
	while (i < NB_CASE_TAB)
	{
		if ((s = ft_itoa_base(vm->array[i++].code_hexa, 16)) == NULL)
			return ;
		if (ft_strlen(s) < 2)
		{
			if ((tmp = ft_strjoin("0", s)) == NULL)
				return ;
			ft_memdel((void**)&s);
			s = tmp;
		}
		change_line(vm, i - 1, s);
		ft_memdel((void**)&s);
	}
}

void						print_dump(t_vm *vm)
{
	if (vm->dump != vm->cycle)
		return ;
	dump_memory(vm);
	del_vm(&vm); //
	exit(0); //
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
		mvwprintw(stdscr, 11 + i * 4, 210,"%s", vm->name_j[i]);
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

void 						print_hightlight(t_vm *vm, t_player *plr)
{
	char 					*tmp;
	int 					size;

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
	if ((vm->flags & VISU) == 0)
		return ;
	while (y < NB_LINE_COLUMN)
	{
		init_pair(vm->array[count2].player, vm->array[count2].player, COLOR_BLACK);
		attron(COLOR_PAIR(vm->array[count2].player));
		tmp = ft_llitoa_base(vm->array[count].code_hexa, 16, &size);
		mvwprintw(stdscr, y + 1, x + 2, "%s ", tmp);
		vm->array[count].x = x + 2;
		vm->array[count].y = y + 1;
		attroff(COLOR_PAIR(vm->array[count2].player));
		ft_strdel(&tmp);
		count2++;
		count++;
		x += 3;
		if (x > 190 && ++y)
			x = 0;
	}
	print_hightlight(vm, vm->plr);
	wrefresh(vm->w_grid);
}

// static int					return_color_grid(t_vm *vm, unsigned int position)
// {
// 	unsigned int			i;
// 	t_player				*curs;

// 	curs = vm->plr;
// 	i = 0;
// 	if (vm->array[position].player == 0)
// 		return (0);
// 	while (curs != NULL)
// 	{
// 		if (position == curs->i_grid)
// 			return (curs->pos + 5 - 1);
// 		curs = curs->next;
// 		i++;
// 	}
// 	return (vm->array[position].player);
// }

// void						print_nb_in_grid(t_vm *vm, int i,
// 		unsigned int y, unsigned int x)
// {
// 	char 					*tmp;
// 	int 					size;
// 	int						color;

// 	attron(COLOR_PAIR((color = return_color_grid(vm, i))));
// 	// attron(COLOR_PAIR(vm->array[i].player));
// 	tmp = ft_llitoa_base(vm->array[i].code_hexa, 16, &size);
// 	mvwprintw(stdscr, y + 1, x + 2, "%s", tmp);
// 	attroff(COLOR_PAIR(color));
// 	ft_strdel(&tmp);
// }


// void						print_grid(t_vm *vm)
// {
// 	unsigned int			x;
// 	unsigned int			y;
// 	int 					count2;

// 	count2 = 0;
// 	y = 0;
// 	x = 0;
// 	while (y < NB_LINE_COLUMN)
// 	{
// 		print_nb_in_grid(vm, count2++, y, x);
// 		x += 3;
// 		if (x > 190 && ++y)
// 			x = 0;
// 	}
// 	wrefresh(vm->w_grid);
// }
