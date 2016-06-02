#include "corewar.h"

void 		ft_start_vm(t_corewar corewar)
{
	while (corewar.nb_proc > 0 && corewar.cycle_to_die > 0)
	{
		corewar.cycle++;
	}
}