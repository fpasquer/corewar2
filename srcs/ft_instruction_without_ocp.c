#include "corewar.h"

int 						ft_live(t_vm *vm, t_player *plr)
{
	int 					i;
	
	i = ft_param_4_octets(vm, plr, 4, plr->i_grid + 1);
	if (i == plr->reg[1])
		plr->nb_live++;
	else
		vm->nb_live++;
	plr->i_grid = ft_check_size_max(5, plr->i_grid);
	// vm->array[plr->i_grid] = plr->pos;
	return (0);
}

int 						ft_zjmp(t_vm *vm, t_player *plr)
{
	short 					i;

	i = ft_param_4_octets(vm, plr, 2, plr->i_grid + 1);
	if (plr->carry)
		plr->i_grid = ft_check_size_max(i, plr->i_grid);
	else
		plr->i_grid = ft_check_size_max(5, plr->i_grid);

	return (0);
}