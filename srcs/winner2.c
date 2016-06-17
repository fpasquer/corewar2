/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 10:49:12 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/17 18:09:33 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"
#include "../incs/virtual_machine.h"

t_player					*get_winner2(t_vm *vm)
{
	t_player				*ret;
	t_player				*curs;

	ret = &vm->last_del;
	curs = vm->plr;
	while (curs != NULL)
	{
		ret = ret == &vm->last_del ? curs : ret;
		if (ret->cycle_last_live < curs->cycle_last_live)
			ret = curs;
		curs = curs->next;
	}
	return (ret);
}
