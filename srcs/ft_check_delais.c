/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_delais.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 09:35:56 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/16 09:37:09 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"

t_delais g_delais[] = {
	{0, 1},
	{LIVE, 10},
	{LD, 5},
	{ST, 5},
	{ADD, 10},
	{SUB, 10},
	{AND, 6},
	{OR, 6},
	{XOR, 6},
	{ZJMP, 20},
	{LDI, 25},
	{STI, 25},
	{FORK, 800},
	{LLD, 10},
	{LLDI, 50},
	{LFORK, 1000},
	{AFF, 2},
	{25, 1},
};

int							ft_add_delais(t_vm *vm, t_player *plr)
{
	int						i;

	i = 0;
	while (g_delais[i].instruction < 25)
	{
		if (vm->array[plr->i_grid].code_hexa == g_delais[i].instruction)
		{
			plr->instruction = i;
			return (g_delais[i].delais + vm->cycle);
		}
		i++;
	}
	return (g_delais[i].delais + vm->cycle);
}

void						ft_check_delais(t_vm *vm)
{
	t_player				*tmp;

	tmp = vm->plr;
	while (tmp)
	{
		if (!tmp->delais)
			tmp->delais = ft_add_delais(vm, tmp);
		if (tmp->delais - 1 == vm->cycle)
		{
			tmp->delais = 0;
			tmp->do_instruction = 1;
		}
		tmp = tmp->next;
	}
}
