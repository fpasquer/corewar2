/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 09:49:33 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/19 11:52:04 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"
#include "../incs/corewar.h"

#define Q count2 = 0; count = 0; t[1] = 0; t[0] = 0;
#define R ft_strdel(&tmp); count2++; count++; t[0] += 3;

void						print_flags(t_vm *vm)
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
	j = j == 63 ? 0 : j + 1;
	return (0);
}

void						dump_memory(t_vm *vm)
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

/*
**	t[0] = x
**	t[1] = y
*/

void						print_grid(t_vm *vm)
{
	unsigned int			t[2];
	int						size;
	char					*tmp;
	int						count;
	int						count2;

	Q;
	if ((vm->flags & VISU) == 0)
		return ;
	while (t[1] < NB_LINE_COLUMN)
	{
		init_pair(vm->array[count2].player, vm->array[count2].player,
				COLOR_BLACK);
		attron(COLOR_PAIR(vm->array[count2].player));
		tmp = ft_llitoa_base(vm->array[count].code_hexa, 16, &size);
		mvwprintw(stdscr, t[1] + 1, t[0] + 2, "%s ", tmp);
		vm->array[count].x = t[0] + 2;
		vm->array[count].y = t[1] + 1;
		attroff(COLOR_PAIR(vm->array[count2].player));
		R;
		if (t[0] > 190 && ++t[1])
			t[0] = 0;
	}
	print_hightlight(vm, vm->plr);
	wrefresh(vm->w_grid);
}
