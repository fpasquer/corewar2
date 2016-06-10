#include "../incs/corewar.h"

int 						ft_live(t_vm *vm, t_player *plr)
{
	int 					i;
	int 					count;

	// bol = 0;
	count = 0;
	i = ft_param_4_octets(vm, plr, 4,   plr->i_grid + 1); //attention il faut % 4096
	// printf("%d", i);
	plr->nb_live++;
	while (count < vm->count_pos)
	{
		// printf("%d = pos\n", vm->array_pos[count]);
		if (i == vm->array_pos[count])
		{
			// printf("ok\n");
			vm->cycle_last_live[count] = vm->cycle;
			vm->nb_live_each_plr[count]++;
			break ;
		}
		count++;
	}
	// printf("end\n");


	// if (plr->reg[1] == i && (bol = 1))
	// {
	// 	vm->cycle_last_live[plr->pos - 1] = vm->cycle;
	// 	vm->nb_live_each_plr[plr->pos - 1]++;
	// }
	// else
	// {
	// 	while (tmp)
	// 	{
	// 		if (tmp->reg[1] == i && (bol = 1))
	// 		{
	// 			vm->cycle_last_live[tmp->pos - 1] = vm->cycle;
	// 			plr->nb_live++;
	// 			vm->nb_live_each_plr[tmp->pos - 1]++;
	// 			break;
	// 		}
	// 		tmp = tmp->next;
	// 	}
	// }
	// vm->nb_live = (!bol) ? vm->nb_live + 1 : vm->nb_live ;
	plr->i_grid = ft_check_size_max(5, plr->i_grid);
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
		plr->i_grid = ft_check_size_max(i, plr->i_grid);
	else
		plr->i_grid = ft_check_size_max(3, plr->i_grid);
	return (0);
}
