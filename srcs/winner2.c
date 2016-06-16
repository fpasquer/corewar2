/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 10:49:12 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/16 10:51:12 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"
#include "../incs/virtual_machine.h"

t_player					*get_winner2(t_vm *vm)
{
	t_player				*ret;
	t_player				*curs;

	ret = NULL;
	curs = vm->plr;
	while (curs != NULL)
	{
		ret = ret == NULL ? curs : ret;
		if (ret->last_live < curs->last_live)
			ret = curs;
		curs = curs->next;
	}
	return (ret);
}
