/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:22:08 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/06 11:46:35 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"
#include "../incs/corewar.h"

void						print_lst(t_player *lst, int fd)
{
	t_player				*cmp;

	cmp = lst;
	while (cmp != NULL)
	{
		ft_putendl_fd(cmp->name, fd);
		cmp = cmp->next;
	}
}

static void					get_status_suspend_dump(t_vm *vm)
{
	if ((vm->flags & DUMP) != 0 || (vm->flags & DUMP_M) != 0)
		print_dump(vm);
	if ((vm->flags & SUSPEND) == 0 || vm->cycle != vm->pause)
		return ;
	vm->pause += vm->nb_susp;
	vm->status = PAUSE;
}

void						loop_virtual_machin(t_vm *vm)
{
	int						key;

	key = REFRESH;
	while (1)
	{
		if (key == REFRESH)
			refrech_win(vm);
		print_info(vm);
		print_grid(vm);
		if ((key = check_key(getch(), vm)) == ESCAPE)
			break ;
		get_status_suspend_dump(vm);

		/*
		** JC
		*/
		
		ft_processus(vm);

		/*
		** JC
		*/ 
		vm->cycle = vm->status != PAUSE ? vm->cycle + 1 : vm->cycle;
		vm->cycle_tmp = vm->status != PAUSE ? vm->cycle_tmp + 1 : vm->cycle;
		if (vm->cycle > 25)
			sleep(1);
	}

}
