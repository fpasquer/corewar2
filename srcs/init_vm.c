/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 10:46:48 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/09 16:21:22 by fpasquer         ###   ########.fr       */
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

static void					init_color_grid(t_vm *vm)
{
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_BLACK, COLOR_RED);
		init_pair(6, COLOR_BLACK, COLOR_GREEN);
		init_pair(7, COLOR_BLACK, COLOR_YELLOW);
		init_pair(8, COLOR_BLACK, COLOR_BLUE);
}

void						init_affichage(t_vm *vm)
{
	unsigned int			i;
	t_player				*curs;

	i = 0;
	curs = vm->plr;
	while (i < vm->nb_player && i < MAX_PLAYER && curs != NULL)
	{
		 ft_strncpy(vm->name_j[i], curs->name, LEN_NAME);
		vm->nb_rep_plr[i++] = curs->reg[1];
		curs = curs->next;
	}
}

t_vm						*init_vm(int argc, char **argv)
{
	t_vm					*new_;

	if ((new_ = ft_memalloc(sizeof(t_vm))) == NULL)
		return (NULL);
	if ((new_->flags = get_flag(new_, argc, argv)) == -1)
		return (NULL);
	if ((new_->plr = save_player(argc - 1, &argv[1], new_)) == NULL)
		return (NULL);
	initscr();
	noecho();
	start_color();
	init_color_grid(new_);
	if ((new_->flags & DUMP) != 0 || (new_->flags & DUMP_M) != 0)
		if ((new_->fd = ft_fopen(NAME_FILE_DUMP_MEM, "w+")) == -1)
			return (NULL);
	new_->pause = ((new_->flags & SUSPEND) != 0) ? new_->nb_susp : 0;
	new_->dump = ((new_->flags & DUMP) != 0) ? new_->nb_dump : 0;
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	new_->nb_proces = new_->nb_player;
	new_->cycle_to_die = INIT_CYCLE_TO_DIE;
	if ((new_->mem = fopen("mem.txt", "w+")) == NULL)
		return (NULL);
	init_affichage(new_);
	return (new_->nb_player <= MAX_PLAYER ? new_ : del_vm(&new_));
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

t_vm						*del_vm(t_vm **vm)
{
	endwin();
	if (vm == NULL || *vm ==NULL)
		return (NULL);
	fclose((*vm)->mem);
	del_player(&(*vm)->plr);
	if (((*vm)->flags & DUMP) != 0)
		close((*vm)->fd);
	// if ((*vm)->w_grid != NULL)
		// ft_memdel((void**)&(*vm)->w_grid);
	// if ((*vm)->w_info != NULL)
		// ft_memdel((void**)&(*vm)->w_info);
	// ft_memdel((void**)vm);
	return (NULL);
}
