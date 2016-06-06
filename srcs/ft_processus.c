#include "corewar.h"

t_instruction g_instruction[] = {
	{11, ft_sti},
	{6, ft_and},
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
		*tab = tmp;
		*size_param += tmp;
	}
}

static int			ft_ocp_instruction(unsigned char str, int i, int *tab)
{
	unsigned char 	tmp;
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

static int 			ft_param_2_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int 					power;
	short 					nb;

	nb = 0;
	power = 0;
	if (index > 4095)
		index %= 4096;
	if (octet == 1)
		return (plr->reg[vm->array[index].code_hexa]);
	while (octet-- > 0)
	{
		if (vm->array[index].code_hexa)
			nb = nb + ((ft_power(octet, 16)) * vm->array[index].code_hexa);
		power++;
		index++;
		if (index > 4095)
			index %= 4096;
	}
	return (nb);
}

static unsigned int 			ft_param_4_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int 					power;
	unsigned int  					nb;

	nb = 0;
	power = 0;
	if (index > 4095)
		index %= 4096;
	if (octet == 1)
		return (plr->reg[vm->array[index].code_hexa]);
	while (octet-- > 0)
	{
		if (vm->array[index].code_hexa)
			nb = nb + ((ft_power(octet, 16)) * vm->array[index].code_hexa);
		power++;
		index++;
		if (index > 4095)
			index %= 4096;
	}
	return (nb);
}

void  						ft_str_base_16(char *str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			*str = *str - 48;
		else if (*str >= 'a' && *str <= 'f')
			*str = *str - 87;
		str++;
	}
}

void 						ft_print_param_to_array_4_octets(t_vm *vm, t_player *plr, int index, unsigned int nb)
{
	int 					size;
	char 					*tmp;
	int 					i;

	i = 0;
	tmp = ft_llitoa_base2(nb, 16, &size);
	ft_str_base_16(tmp);
	if (index > 511)
			index %= 512;
	else if (index < 0)
		index = NB_CASE_TAB - ft_abs(index) % 512;
	while (i < 8)
	{
		vm->array[plr->i_grid + index].code_hexa = 16 * tmp[i] + tmp[i + 1];
		vm->array[plr->i_grid + index].player = plr->pos; // REMODIFIER CETTE PARTIE OKLM
		i += 2;
		index++;
	}
	ft_strdel(&tmp);
}

void 						ft_and(t_vm *vm, t_player *plr)
{
	int 					i;
	int 					tmp_i;
	int 					ocp;
	int 					tab[3];

	ft_bzero(tab, sizeof(int) * 3);
	i = plr->i_grid + 1;
	i = (i == NB_CASE_TAB) ? 0 : i;

	ocp = ft_ocp_instruction(vm->array[i].code_hexa, 4, tab);
	i++;
	tmp_i = i + tab[0] + tab[1];
	plr->reg[vm->array[tmp_i].code_hexa] = ft_param_4_octets(vm, plr, tab[0], i) & ft_param_4_octets(vm, plr, tab[1], i + tab[0]);
	// i = ft_param_4_octets(vm, plr, tab[0], i) & ft_param_4_octets(vm, plr, tab[1], i + tab[0]);




	plr->i_grid += ocp + 2;
	plr->do_instruction = 0;
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

	ft_bzero(tab, sizeof(int) * 3);
	i = plr->i_grid + 1;
	i = (i == NB_CASE_TAB) ? 0 : i;

	/*
	** 2, car les directs dans cette instruction sont code sous 2 octets
	*/

	ocp = ft_ocp_instruction(vm->array[i].code_hexa, 2, tab);

	/*
	** j'incremete de 2, pour que l'index passe au second parametre de l'instruction.
	** le premier etant forcement un registre.
	*/

	i = ft_param_2_octets(vm, plr, tab[1], i + 2) + 
		ft_param_2_octets(vm, plr, tab[2], i + 2 + tab[1]);

	/*
	** PHASE TEST
	*/

	// plr->reg[1] = -1;
	ft_print_param_to_array_4_octets(vm, plr, i, plr->reg[1]);

	/*
	** ocp = taile de l'instruction
	** 2 = le nom de l'instruction + le code ocp
	*/

	plr->do_instruction = 0;
	plr->i_grid += ocp + 2;
	// printf("\n\n%d\n\n", plr->i_grid);
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
	while (g_instruction[i].instruction > 0)
	{
		if (g_instruction[i].instruction == vm->array[plr->i_grid].code_hexa)
		{
			g_instruction[i].p(vm, plr);
			break ;
		}
		i++;
	}
}

void						ft_check_processus(t_vm *vm)
{
	t_player 				*tmp;

	tmp = vm->plr;
	while (tmp)
	{
		if (tmp->delais == 0 && tmp->do_instruction == 1)
			ft_processus_instruction(vm, tmp);
		tmp = tmp->next;
	}
} 

void 						ft_processus(t_vm *vm)
{
	ft_check_delais(vm);
	ft_check_processus(vm);
	if (vm->cycle_tmp == vm->cycle_to_die)
	{
		ft_check_processus_life(vm);
		vm->cycle_tmp = 0;
	}
}