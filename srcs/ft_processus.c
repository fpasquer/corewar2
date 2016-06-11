#include "../incs/corewar.h"

t_instruction g_instruction[] = {
	{0, NULL, 0, {0}, 0},
	{1, ft_live, 4, {T_DIR}, 1},
	{2, ft_ld, 4, {T_DIR | T_IND, T_REG}, 2},
	{3, ft_st, 2, {T_REG, T_IND | T_REG}, 2},
	{4, ft_add, 0, {T_REG, T_REG, T_REG}, 3},
	{5, ft_sub, 0, {T_REG, T_REG, T_REG}, 3},
	{6, ft_and, 4, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 3},
	{7, ft_or, 4,  {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3},
	{8, ft_xor, 4, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3},
	{9, ft_zjmp, 2, {T_DIR}, 1},
	{10, ft_ldi, 2, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3},
	{11, ft_sti, 2, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 3},
	{12, ft_fork, 2, {T_DIR}, 1},
	{13, ft_lld, 4,  {T_DIR | T_IND, T_REG}, 2},
	{15, ft_lfork, 2, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3},
	{-1, NULL},
};

t_ocp g_ocp[] = {
	{0, ft_param_0_octet},
	{1, ft_param_1_octets},
	{2, ft_param_4_octets},
	{3, ft_param_4_octets},
	{4, ft_param_4_octets},
};

static void 		ft_instruction_type(int tmp, int i, int *size, int *size_param)
{
	if (tmp == 3)
		tmp--;
	else if (i == 4 && tmp == 2)
		tmp = i;
	if (tmp > 0)
	{
		*size_param = tmp;
		*size += tmp;
	}
}

static int			ft_ocp_instruction(unsigned char str, int i, t_info *info)
{
	unsigned char 	tmp;
	int 	size;

	size = 0;
	tmp = str >> 6;
	info->t_f_param = tmp;
	ft_instruction_type(tmp, i, &size, &info->s_f_param);
	tmp = (str & MASK_6_BITS) >> 4;
	info->t_s_param = tmp;
	ft_instruction_type(tmp, i, &size, &info->s_s_param);
	tmp = (str & MASK_4_BITS) >> 2;
	info->t_t_param = tmp;
	ft_instruction_type(tmp, i, &size, &info->s_t_param);
	return (size);
}

void 						ft_check_arguments_ocp(t_info *info, int nb_arg, int i)
{
	int 					count;

	count = 0;
	while (nb_arg > 0)
	{
		if (count == 0 && g_instruction[i].ocp_array[count] & info->t_f_param)
			;
		else if (count == 1 && g_instruction[i].ocp_array[count] & info->t_s_param)
			;
		else if (count == 2 && g_instruction[i].ocp_array[count] & info->t_t_param)
			;
		else
		{
			// printf("err, %d, %d\n", info->instruction, info->ocp                      );
			info->error = ERROR_REG;
			break ;
		}
		count++;
		nb_arg--;
	}
}

void 						ft_parse_info(t_vm *vm, t_player *plr)
{
	t_info					*tmp;

	tmp = &plr->info;
	tmp->index_ocp = (plr->i_grid + 1) % NB_CASE_TAB;
	tmp->ocp = vm->array[tmp->index_ocp].code_hexa;
	tmp->size_ocp_param = ft_ocp_instruction(tmp->ocp, tmp->epd, tmp);
	tmp->index_f_param = (tmp->index_ocp + 1) % NB_CASE_TAB;
	tmp->index_s_param = (tmp->index_ocp + tmp->s_f_param + 1) % NB_CASE_TAB;
	tmp->index_t_param = (tmp->index_ocp + + tmp->s_f_param + tmp->s_s_param + 1) % NB_CASE_TAB;
	tmp->nb_f_param = g_ocp[tmp->t_f_param].p(vm, plr, tmp->s_f_param, tmp->index_f_param);
	tmp->nb_s_param = g_ocp[tmp->t_s_param].p(vm, plr, tmp->s_s_param, tmp->index_s_param);
	tmp->nb_t_param = g_ocp[tmp->t_t_param].p(vm, plr, tmp->s_t_param, tmp->index_t_param);
	ft_check_arguments_ocp(tmp, tmp->nb_arg, tmp->instruction);
}


int 						ft_add(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);

	if (plr->info.error == ERROR_REG)
		plr->i_grid = (plr->i_grid + 2 + plr->pc);
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param + plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->pc) % NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int 						ft_sub(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);

	if (plr->info.error == ERROR_REG)
		plr->i_grid = (plr->i_grid + 2 + plr->pc);
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param - plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->pc) % NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int 						ft_and(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	
	if (plr->info.error == ERROR_REG)
		plr->i_grid = (plr->i_grid + 2 + plr->pc);
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param & plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->pc) % NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int 						ft_or(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	
	if (plr->info.error == ERROR_REG)
		plr->i_grid = (plr->i_grid + 2 + plr->pc);
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param | plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->pc) % NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int 						ft_xor(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	
	if (plr->info.error == ERROR_REG)
		plr->i_grid = (plr->i_grid + 2 + plr->pc);
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param ^ plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->pc) % NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int 						ft_check_size_max(int i, int index)
{
	int 					tmp;

	if (i > 511)
		i = i % 512;
	else if (i < 0)
		i = i % 512;
	tmp = index + i;
	if (tmp < 0)
		return (NB_CASE_TAB + i);
	else if (tmp > 4095)
		return (tmp - NB_CASE_TAB);
	return (index + i);
}

int 						ft_nothing(t_vm *vm, t_player *plr)
{
	plr->i_grid = (plr->i_grid + 1) % NB_CASE_TAB;
	return (0);
}

int 						ft_sti(t_vm *vm, t_player *plr)
{
	int 					i;
	ft_parse_info(vm, plr);

	i = plr->info.nb_s_param + plr->info.nb_t_param;
	i = get_new_index_with_mod(i, plr->i_grid, vm);
	ft_print_param_to_array_4_octets(vm, plr, i, plr->reg[plr->info.reg_f]);
	plr->i_grid = (plr->i_grid + 2 + plr->pc) % NB_CASE_TAB;
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}



int							ft_processus_instruction(t_vm *vm, t_player *plr)
{
	int 					i;

	i = 1;
	// if (vm->array[plr->i_grid].code_hexa < 1 || vm->array[plr->i_grid].code_hexa > 16)
	// {
	// 	ft_nothing(vm, plr);
	// 	return (0);
	// }
	 if (plr->wait < 1 || plr->wait > 16)
	{
		ft_nothing(vm, plr);
		return (0);
	}
	while (g_instruction[i].instruction > 0)
	{
		if (g_instruction[i].instruction == plr->wait)
		{
			plr->info.epd = g_instruction[i].epd;
			plr->info.nb_arg = g_instruction[i].nb_arg;
			plr->info.instruction = i;
			g_instruction[i].p(vm, plr);
			plr->wait = 0;
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
