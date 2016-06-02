/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 10:20:21 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/02 17:52:24 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"

void 						ft_free(t_vm *vm)
{
	t_player				*tmp;

	while (vm->plr)
	{
		tmp = vm->plr->next;
		free(vm->plr->name);
		free(vm->plr->comment);
		free(vm->plr);
		vm->plr = tmp;
	}
}

int							main(int argc, char **argv)
{
	t_vm					vm;

	ft_bzero(&vm, sizeof(t_vm));
	if (argc < 2)
		error("Champions ar missing");
	if (init_vm(&vm, argc, argv) == -1)
		error("Initiation error");
	loop_virtual_machin(&vm);
	del_vm(&vm);
	ft_free(&vm);
	return (0);
}
