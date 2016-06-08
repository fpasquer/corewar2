#include "../incs/corewar.h"

/*static int 						ft_count_all_processus_live(t_player *plr) //Nouveau tableau avec le nombre de live de chacun des joueurs
{
	int 					i;

	i = 0;
	while (plr)
	{
		i += plr->nb_live;
		plr = plr->next;
	}
	return (i);
}*/

static int 						ft_count_all_processus_live(t_vm *vm) //Nouveau tableau avec le nombre de live de chacun des joueurs
{
	int 					i;

	i = vm->nb_live_each_plr[0];
	i += vm->nb_live_each_plr[1];
	i += vm->nb_live_each_plr[2];
	i += vm->nb_live_each_plr[3];
	return (i);
}


static void 				ft_reset_live(t_player *plr, t_vm *vm) // peut boucler que sur le nombre de joueur
{
	while (plr)
	{
		plr->last_live = plr->nb_live;
		plr->nb_live = 0;
		vm->nb_live_each_plr[plr->pos - 1] = 0;
		plr = plr->next;
	}
}

void 						ft_check_processus_life(t_vm *vm)
{
	int 					count_live;

	count_live = ft_count_all_processus_live(vm) + vm->nb_live;
	if (count_live > 21 && !(vm->check_max = 0))
	{
		vm->cycle_to_die -= 50;
	}
	else
	{
		vm->check_max++;
		if (vm->check_max == 10)
		{
			vm->cycle_to_die -= 50;
			vm->check_max = 0;
		}
	}
	ft_reset_live(vm->plr, vm);
	vm->nb_live = 0;
}
