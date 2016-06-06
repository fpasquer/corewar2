#include "../incs/corewar.h"

t_instruction g_instruction[] = {
	{1, ft_live},
	{6, ft_and},
	{9, ft_zjmp},
	{11, ft_sti},
	{12, ft_fork},
//	{15, ft_lfork},
	{-1, NULL},
};

t_ocp g_ocp[] = {
	{0, NULL},
	{1, ft_param_1_octets},
	{2, ft_param_2_octets},
	{3, NULL},
	{4, ft_param_4_octets},
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

char						*ft_fill_less(char *str, int size, int octet)
{
	char 					*tmp;
	int 					i;
	int 					count;

	octet = (octet == 2) ? 4 : 8;
	count = 0;
	i = 8 - size;
	if (size == octet)
		return (str);
	if (!(tmp = ft_strnew(octet)))
		exit (-1);
	while (i < octet)
	{
		tmp[i] = str[count];
		i++;
		count++;
	}
	free(str);
	return(tmp);
}

void  						ft_str_base_16(char *str)
{
	int 					i;

	i = 0;
	while (i < 8)
	{
		if (str[i] >= '0' && str[i] <= '9')
			str[i] = str[i] - 48;
		else if (str[i] >= 'a' && str[i] <= 'f')
			str[i] = str[i] - 87;
		i++;
	}
}

void 						ft_print_param_to_array_4_octets(t_vm *vm, t_player *plr, int index, unsigned int nb)
{
	int 					size;
	char 					*tmp;
	int 					i;

	i = 0;
	tmp = ft_llitoa_base2(nb, 16, &size);
	tmp = ft_fill_less(tmp, size, 4);
	ft_str_base_16(tmp);
	if (index > 511)
			index %= 512;
	else if (index < 0)
		index = NB_CASE_TAB - ft_abs(index) % 512;
	while (i < 8)
	{
		vm->array[plr->i_grid + index].code_hexa = (16 * tmp[i]) + (tmp[i + 1]);
		vm->array[plr->i_grid + index].player = plr->pos;
		i += 2;
		index++;
	}
	ft_strdel(&tmp);
}

int 						ft_and(t_vm *vm, t_player *plr)
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
	
	plr->reg[vm->array[tmp_i].code_hexa] = g_ocp[tab[0]].p(vm, plr, tab[0], i) & g_ocp[tab[1]].p(vm, plr, tab[1], i + tab[0]);
	
	// plr->reg[vm->array[tmp_i].code_hexa] = ft_param_4_octets(vm, plr, tab[0], i) & ft_param_4_octets(vm, plr, tab[1], i + tab[0]);
	// i = ft_param_4_octets(vm, plr, tab[0], i) & ft_param_4_octets(vm, plr, tab[1], i + tab[0]);

	plr->carry = (plr->reg[vm->array[tmp_i].code_hexa]) ? 0 : 1; 



	plr->i_grid += ocp + 2;
	plr->do_instruction = 0;
	return (0);
}

int 						ft_nothing(t_vm *vm, t_player *plr)
{
	return (0);
}

int 						ft_sti(t_vm *vm, t_player *plr)
{
	int 					i;
	int 					ocp;
	int 					tab[3];
	int 					nb_reg;

	ft_bzero(tab, sizeof(int) * 3);
	i = plr->i_grid + 1;
	i = (i == NB_CASE_TAB) ? 0 : i;
	nb_reg = vm->array[i + 1].code_hexa;

	/*
	** 2, car les directs dans cette instruction sont code sous 2 octets
	*/

	ocp = ft_ocp_instruction(vm->array[i].code_hexa, 2, tab);

	/*
	** j'incremete de 2, pour que l'index passe au second parametre de l'instruction.
	** le premier etant forcement un registre.
	*/

	i = g_ocp[tab[1]].p(vm, plr, tab[1], i + 2) + g_ocp[tab[2]].p(vm, plr, tab[2], i + 2 + tab[1]);

	// i = ft_param_2_octets(vm, plr, tab[1], i + 2) + 
	// 	ft_param_2_octets(vm, plr, tab[2], i + 2 + tab[1]);

	/*
	** PHASE TEST
	*/

	ft_print_param_to_array_4_octets(vm, plr, i, plr->reg[nb_reg]);

	/*
	** ocp = taile de l'instruction
	** 2 = le nom de l'instruction + le code ocp
	*/

	plr->do_instruction = 0;
	plr->i_grid += ocp + 2;
	return (0);
	// printf("\n\n%d\n\n", plr->i_grid);
	return (0);
}

int 						ft_live(t_vm *vm, t_player *plr)
{	
	
	return (0);
}

int 						ft_zjmp(t_vm *vm, t_player *plr)
{
	return (0);
}

int							ft_processus_instruction(t_vm *vm, t_player *plr)
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
	return (0);
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
