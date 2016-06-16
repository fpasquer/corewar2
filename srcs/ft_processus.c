/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 10:02:17 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/16 14:26:31 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/corewar.h"

t_instruction g_instruction[] = {
	{0, NULL, 0},
	{1, ft_live, 4},
	{2, ft_ld, 4},
	{3, ft_st, 4},
	{4, ft_add, 4},
	{5, ft_sub, 4},
	{6, ft_and, 4},
	{7, ft_or, 4},
	{8, ft_xor, 4},
	{9, ft_zjmp, 2},
	{10, ft_ldi, 2},
	{11, ft_sti, 2},
	{12, ft_fork, 2},
	{13, ft_ld, 4},
	{14, ft_ldi, 2},
	{15, ft_lfork, 2},
	{16, ft_aff, 1},
	{-1, NULL},
};

t_ocp g_ocp[] = {
	{0, ft_param_0_octet},
	{1, ft_param_1_octets},
	{2, ft_param_4_octets},
	{3, ft_param_4_octets},
	{4, ft_param_4_octets},
};

t_ocp_param g_ocp_param[] = {
	{0, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{LIVE, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, 1},
	{LD, {0, 0, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}, 2},
	{ST, {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 0, 0, 0}, 2},
	{ADD, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, 3},
	{SUB, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, 3},
	{AND, {0, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 0}, 3},
	{OR, {0, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 0}, 3},
	{XOR, {0, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 0}, 3},
	{ZJMP, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, 1},
	{LDI, {0, 1, 1, 1}, {0, 1, 1, 0}, {0, 1, 0, 0}, 3},
	{STI, {0, 1, 0, 0}, {0, 1, 1, 1}, {0, 1, 1, 0}, 3},
	{FORK, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, 1},
	{LLD, {0, 0, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}, 2},
	{LLDI, {0, 1, 1, 1}, {0, 1, 1, 0}, {0, 1, 0, 0}, 3},
	{LFORK, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, 1},
	{AFF, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, 1},
};

static void					ft_instruction_type(int tmp, int i, int *size,
		int *size_param)
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

int							ft_aff(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm,plr);
	plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) % 4096;
	ft_bzero(&plr->info, sizeof(t_info));
	plr->do_instruction = 0;
	return (0);
}

static int					ft_ocp_instruction(unsigned char str, int i,
		t_info *info)
{
	unsigned char			tmp;
	int						size;

	size = 0;
	tmp = str >> 6;
	info->t_f_param = tmp;
	if (g_ocp_param[info->instruction].nb_param >= 1)
		ft_instruction_type(tmp, i, &size, &info->s_f_param);
	tmp = (str & MASK_6_BITS) >> 4;
	info->t_s_param = tmp;
	if (g_ocp_param[info->instruction].nb_param >= 2)
		ft_instruction_type(tmp, i, &size, &info->s_s_param);
	tmp = (str & MASK_4_BITS) >> 2;
	info->t_t_param = tmp;
	if (g_ocp_param[info->instruction].nb_param == 3)
		ft_instruction_type(tmp, i, &size, &info->s_t_param);
	return (size);
}

void						ft_check_ocp(t_info *info, t_vm *vm)
{
	int						i;
	static int				test;

	i = 0;
	if (g_ocp_param[info->instruction].f_p[info->t_f_param])
	{
		info->size_ocp_param2 += info->s_f_param;
		i++;
	}
	if (g_ocp_param[info->instruction].s_p[info->t_s_param])
	{
		info->size_ocp_param2 += info->s_s_param;
		i++;
	}
	if (g_ocp_param[info->instruction].t_p[info->t_t_param])
	{
		info->size_ocp_param2 += info->s_t_param;
		i++;
	}
	if (g_ocp_param[info->instruction].nb_param != i)
	{
		test++;
	// if ((vm->flags & VISU) == 0)
	// 	printf("%02x, %02x = ocp, %5d s_f_p, %5d, s_s_p, %5d, s_t_p, %5d, t_f_p, %5d, t_s_p, %5d, t_t_p | %3d nb error | %6d cycle \n",
	// 	info->instruction, info->ocp, info->s_f_param, info->s_s_param, info->s_t_param,
	// 	info->t_f_param, info->t_s_param, info->t_t_param, test, vm->cycle);
		info->error = ERROR_OCP;
	}
}

int							ft_check_size_max2(int i, int index)
{
	int						tmp;

	tmp = index + i;
	if (tmp < 0)
		return (NB_CASE_TAB + i);
	else if (tmp > 4095)
		return (tmp - NB_CASE_TAB);
	return (index + i);
}

int							ft_indirect_param(t_vm *vm, t_player *plr, int move)
{
	int						i;

	if (plr->instruction != LLD && plr->instruction != LLDI &&
			plr->instruction != LFORK)
		i = get_new_index_with_mod(move, plr->i_grid, vm);
	else
		i = get_new_index(move, plr->i_grid, vm);
	if (plr->instruction == STI || plr->instruction == LD ||
			plr->instruction == LDI || plr->instruction == LLDI)
		i = ft_param_4_octets(vm, plr, 4, i);
	else
		i = ft_param_4_octets(vm, plr, 2, i);
	return (i);
}

void						ft_parse_info(t_vm *vm, t_player *plr)
{
	t_info					*tmp;

	tmp = &plr->info;
	tmp->index_ocp = (plr->i_grid + 1) % NB_CASE_TAB;
	tmp->ocp = vm->array[tmp->index_ocp].code_hexa;
	tmp->size_ocp_param = ft_ocp_instruction(tmp->ocp, tmp->epd, tmp);
	tmp->index_f_param = (tmp->index_ocp + 1) % NB_CASE_TAB;
	tmp->index_s_param = (tmp->index_ocp + tmp->s_f_param + 1) % NB_CASE_TAB;
	tmp->index_t_param = (tmp->index_ocp + tmp->s_f_param +
			tmp->s_s_param + 1) % NB_CASE_TAB;
	ft_check_ocp(tmp, vm);
	if (tmp->error)
		return ;
	tmp->nb_f_param = g_ocp[tmp->t_f_param].p(vm, plr, tmp->s_f_param,
			tmp->index_f_param);
	tmp->nb_s_param = g_ocp[tmp->t_s_param].p(vm, plr, tmp->s_s_param,
			tmp->index_s_param);
	tmp->nb_t_param = g_ocp[tmp->t_t_param].p(vm, plr, tmp->s_t_param,
			tmp->index_t_param);
	if (plr->instruction != ST && plr->instruction != ZJMP)
	{
		tmp->nb_f_param = tmp->t_f_param == T_IND ?
			ft_indirect_param(vm, plr, tmp->nb_f_param) : tmp->nb_f_param;
		tmp->nb_s_param = tmp->t_s_param == T_IND ?
			ft_indirect_param(vm, plr, tmp->nb_s_param) : tmp->nb_s_param;
		tmp->nb_t_param = tmp->t_t_param == T_IND ?
			ft_indirect_param(vm, plr, tmp->nb_t_param) : tmp->nb_t_param;
	}
}

int							ft_ld(t_vm *vm, t_player *plr)
{
	int						i;

	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		plr->reg[plr->info.reg_s] = plr->info.nb_f_param;
		plr->carry = plr->reg[plr->info.reg_s] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_ldi(t_vm *vm, t_player *plr)
{
	int						i;

	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		i = plr->info.nb_f_param + plr->info.nb_s_param;
		i = ft_indirect_param(vm, plr, i);
		plr->reg[plr->info.reg_t] = i;
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->carry = (plr->instruction == LLDI &&
			plr->reg[plr->info.reg_t]) ? 0 : 1;
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_add(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param + plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_sub(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param - plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_and(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param & plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_or(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param | plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_xor(t_vm *vm, t_player *plr)
{
	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		plr->reg[plr->info.reg_t] = plr->info.nb_f_param ^ plr->info.nb_s_param;
		plr->carry = plr->reg[plr->info.reg_t] ? 0 : 1;
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_check_size_max(int i, int index)
{
	int						tmp;

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

int							ft_nothing(t_vm *vm, t_player *plr)
{
	plr->i_grid = (plr->i_grid + 1) % NB_CASE_TAB;
	return (0);
}

int							ft_sti(t_vm *vm, t_player *plr)
{
	int						i;

	ft_parse_info(vm, plr);
	if (plr->info.error == ERROR_REG)
		plr->i_grid = get_new_index_with_mod(2 + plr->info.size_ocp_param,
				plr->i_grid, vm);
	else if (plr->info.error == ERROR_OCP)
		plr->i_grid = (plr->i_grid + plr->info.size_ocp_param + 2) %
			NB_CASE_TAB;
	else
	{
		i = plr->info.nb_s_param + plr->info.nb_t_param;
		i = get_new_index_with_mod(i, plr->i_grid, vm);
		ft_print_param_to_array_4_octets(vm, plr, i, plr->reg[plr->info.reg_f]);
		plr->i_grid = (plr->i_grid + 2 + plr->info.size_ocp_param) %
			NB_CASE_TAB;
	}
	plr->do_instruction = 0;
	ft_bzero(&plr->info, sizeof(t_info));
	return (0);
}

int							ft_processus_instruction(t_vm *vm, t_player *plr)
{
	int						i;

	i = 1;
	if (plr->instruction < 1 || plr->instruction > 16)
	{
		ft_nothing(vm, plr);
		plr->instruction = 0;
		return (0);
	}
	while (g_instruction[i].instruction > 0)
	{
		if (g_instruction[i].instruction == plr->instruction)
		{
			plr->info.instruction = plr->instruction;
			plr->info.epd = g_instruction[i].epd;
			g_instruction[i].p(vm, plr);
			plr->instruction = 0;
			break ;
		}
		i++;
	}
	return (0);
}

void						ft_check_processus(t_vm *vm)
{
	t_player				*tmp;

	tmp = vm->plr;
	while (tmp)
	{
		if (tmp->delais == 0 && tmp->do_instruction == 1)
			ft_processus_instruction(vm, tmp);
		tmp = tmp->next;
	}
}

void						ft_processus(t_vm *vm)
{
	if (vm->cycle_tmp == vm->cycle_to_die)
	{
		ft_check_processus_life(vm);
		vm->cycle_tmp = 0;
	}
	ft_check_delais(vm);
	ft_check_processus(vm);
}
