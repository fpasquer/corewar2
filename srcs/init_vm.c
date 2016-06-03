/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 10:46:48 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/03 10:29:16 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"

static int					get_number(char *nb)
{
	int						i;

	if (ft_is_number(nb) == 0)
		return (-1);
	i = 0;
	while (ft_isspace(nb[i]) == 1 || nb[i] == '+')
		i++;
	if (nb[i] == '-' || nb[i] == '\0')
		return (-1);
	return (ft_atoi(nb));
}

static int					get_flag(t_vm *vm, int argc, char **argv)
{
	int						i;
	int						flag;

	i = 0;
	flag = NONE;
	while (i++ < argc)
		if (ft_strcmp("-d", argv[i - 1]) == 0 ||
				ft_strcmp("-dm", argv[i - 1]) == 0)
		{
			flag = ft_strcmp("-d", argv[i - 1]) == 0 ? flag | DUMP : flag;
			flag = ft_strcmp("-dm", argv[i - 1]) == 0 ? flag | DUMP_M : flag;
			if ((vm->nb_dump = get_number(argv[i])) == -1)
				return (-1);
		}
		else if (ft_strcmp("-n", argv[i - 1]) == 0)
			flag = flag | NUMBER;
		else if (ft_strcmp("-v", argv[i - 1]) == 0)
			flag = flag | VISU;
		else if (ft_strcmp("-s", argv[i - 1]) == 0)
		{
			flag = flag | SUSPEND;
			if ((vm->nb_susp = get_number(argv[i])) == -1)
				return (-1);
		}
	return (flag);
}

int							init_vm(t_vm *new_, int argc, char **argv)
{
	// if ((new_->grid = ft_memalloc(sizeof(int) * (NB_LINE_COLUMN *
	// 		(NB_CASE_TAB * 2)))) == NULL)
	// 	return (-1);
	// if ((new_->grid2d = make_tab_2d(new_->grid, NB_LINE_COLUMN,
	// 		NB_LINE_COLUMN * 2)) == NULL)
	// 	return (-1);
	if ((new_->flags = get_flag(new_, argc, argv)) == -1)
		return (-1);
	if ((new_->plr = save_player(argc - 1, &argv[1], new_)) == NULL)
		return (-1);
	initscr();
	noecho();
	start_color();
	if ((new_->flags & DUMP) != 0 || (new_->flags & DUMP_M) != 0)
		if ((new_->fd = ft_fopen(NAME_FILE_DUMP_MEM, "w+")) == -1)
			return (-1);
	new_->pause = ((new_->flags & SUSPEND) != 0) ? new_->nb_susp : 0;
	new_->dump = ((new_->flags & DUMP) != 0) ? new_->nb_dump : 0;
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	new_->nb_proces = new_->nb_player;
	new_->cycle_to_die = INIT_CYCLE_TO_DIE;
	return (0);
}

void						refrech_win(t_vm *vm)
{
	clear();
	vm->w_grid = subwin(stdscr, NB_LINE_COLUMN + 2, NB_LINE_COLUMN * 2 +
			NB_LINE_COLUMN + 3, 0, 0);
	vm->w_info = subwin(stdscr, NB_LINE_COLUMN + 2, WIDTH_INFO, 0,
			NB_LINE_COLUMN * 2 + NB_LINE_COLUMN + 3);
	box(vm->w_grid, ACS_VLINE, ACS_HLINE);
	box(vm->w_info, ACS_VLINE, ACS_HLINE);
	wrefresh(vm->w_grid);
	wrefresh(vm->w_info);
	refresh();
}

t_vm						*del_vm(t_vm *vm)
{
	endwin();
	if (vm == NULL)
		return (NULL);
	if ((vm->flags & DUMP) != 0)
		close(vm->fd);
	if (vm->w_grid != NULL)
		ft_memdel((void**)&vm->w_grid);
	if (vm->w_info != NULL)
		ft_memdel((void**)&vm->w_info);
	return (NULL);
}
