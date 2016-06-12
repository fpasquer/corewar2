#include "../incs/corewar.h"

int 						ft_live(t_vm *vm, t_player *plr)
{
	int 					i;
	int 					count;

	count = 0;
	i = ft_param_4_octets(vm, plr, 4,   plr->i_grid + 1); //attention il faut % 4096
	plr->nb_live++;
	while (count < vm->count_pos)
	{
		if (i == vm->array_pos[count])
		{
			vm->cycle_last_live[count] = vm->cycle;
			vm->nb_live_each_plr[count]++;
			break ;
		}
		count++;
	}
	plr->i_grid = (5 + plr->i_grid) % NB_CASE_TAB;
	return (0);
}

// int 						ft_live(t_vm *vm, t_player *plr)
// {
// 	int 					i;
	
// 	i = ft_param_4_octets(vm, plr, 4,   plr->i_grid + 1); //attention il faut % 4096
// 	if (i == plr->reg[1])
// 	{
// 		vm->cycle_last_live[plr->pos - 1] = vm->cycle;
// 		plr->nb_live++;
// 		vm->nb_live_each_plr[plr->pos - 1]++;
// 	}
// 	else
// 		vm->nb_live++;
// 	plr->i_grid = ft_check_size_max(5, plr->i_grid);
// 	return (0);
// }

int 						ft_zjmp(t_vm *vm, t_player *plr)
{
	short 					i;

	i = ft_param_4_octets(vm, plr, 2, plr->i_grid + 1);
	if (plr->carry)
		plr->i_grid = get_new_index_with_mod(i, plr->i_grid, vm);
	else
		plr->i_grid = get_new_index_with_mod(3, plr->i_grid, vm);
	return (0);
}
