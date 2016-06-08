#include "../incs/corewar.h"

int 						ft_live(t_vm *vm, t_player *plr)
{
	int 					i;
	
	i = ft_param_4_octets(vm, plr, 4, plr->i_grid + 1); //attention il faut % 4096
	if (i == plr->reg[1])
	{
		vm->cycle_last_live[plr->pos - 1] = vm->cycle;
		plr->nb_live++;
		vm->nb_live_each_plr[plr->pos - 1]++;
	}
	else
		vm->nb_live++;
	plr->i_grid = ft_check_size_max(5, plr->i_grid);
	return (0);
}

int 						ft_zjmp(t_vm *vm, t_player *plr)
{
	short 					i;

	i = ft_param_4_octets(vm, plr, 2, plr->i_grid + 1);
	if (plr->carry)
		plr->i_grid = ft_check_size_max(i, plr->i_grid);
	else
		plr->i_grid = ft_check_size_max(3, plr->i_grid);
	return (0);
}
