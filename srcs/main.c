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
	return (0);
}
