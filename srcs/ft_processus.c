#include "corewar.h"

t_instruction g_instruction[] = {
	{11, ft_sti},
	{1, ft_live},
	{9, ft_zjmp},
	{-1, NULL},
};

static void 		ft_instruction_type(int tmp, int i, int *size_param, int *tab)
{
	if (tmp == 3)
		tmp--;
	else if (i == 4 && tmp == 2)
		tmp = i;
	if (tmp > 0)
	{
		tab[0] = tmp;
		*size_param += tmp;
	}
}

static int			ft_ocp_instruction(char str, int i, int *tab)
{
	char 	tmp;
	int 	size_param;

	size_param = 0;
	tmp = str >> 6;
	ft_instruction_type(tmp, i, &size_param, &tab[0]);
	tmp = (str & MASK_6_BITS) >> 4;
	ft_instruction_type(tmp, i, &size_param, &tab[1]);
	tmp = (str & MASK_4_BITS) >> 2;
	ft_instruction_type(tmp, i, &size_param, &tab[2]);
	return (size_param);
}

static int 			ft_param(t_vm *vm, t_player *plr, int octet, int index)
{
	if (index > 4095)
		index %= 4096;
	if (octet == 1)
		return (plr->reg[vm->array[index].code_hexa]);
	while (--octet >= 0)
	{

	}
	return (0);
}

void 						ft_nothing(t_vm *vm, t_player *plr)
{
	return ;
}

void 						ft_sti(t_vm *vm, t_player *plr)
{
	int 					i;
	int 					ocp;
	int 					tab[3];
	int 					count;


	count = 0;
	ft_bzero(tab, sizeof(int) * 3);
	i = plr->i_grid + 1;
	i = (i == NB_CASE_TAB) ? 0 : i;
	ocp = ft_ocp_instruction(vm->array[i].code_hexa, 2, tab);
	i = ft_param(vm, plr, tab[1], i + 1) + ft_param(vm, plr, tab[2], i + 1 + tab[1]);
	plr->i_grid += ocp + 2;
}

void 						ft_live(t_vm *vm, t_player *plr)
{

	return ;
}

void 						ft_zjmp(t_vm *vm, t_player *plr)
{

	return ;
}

void 						ft_processus_instruction(t_vm *vm, t_player *plr)
{
	int 					i;

	i = 0;
	if (vm->array[plr->i_grid].code_hexa < 1 || vm->array[plr->i_grid].code_hexa > 16)
		ft_nothing(vm, plr);
	while (g_instruction[i].p)
	{
		if (g_instruction[i].instruction == vm->array[plr->i_grid].code_hexa)
			g_instruction[i].p(vm, plr);
		i++;
	}
}

void						ft_check_processus(t_vm *vm)
{
	t_player 				*tmp;

	tmp = vm->plr;
	while (tmp)
	{
		ft_processus_instruction(vm, tmp);
		tmp = tmp->next;
	}
} 

void 						ft_processus(t_vm *vm)
{
	ft_check_processus(vm);
	if (vm->cycle_tmp == vm->cycle_to_die)
	{
		ft_check_processus_life(vm);
		vm->cycle_tmp = 0;
	}
}