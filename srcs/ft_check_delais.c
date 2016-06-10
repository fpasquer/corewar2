#include "../incs/corewar.h"

t_delais g_delais[] = {
	{0, 1}, // revoir
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

int 						ft_add_delais(t_vm *vm, t_player *plr)
{
	int 					i;

	i = 0;
	while (g_delais[i].instruction < 25)
	{
		if (vm->array[plr->i_grid].code_hexa == g_delais[i].instruction)
			return (g_delais[i].delais + vm->cycle);
		i++;
	}
	return (1 + vm->cycle);
}

void 						ft_check_delais(t_vm *vm)
{
	t_player 				*tmp;

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
