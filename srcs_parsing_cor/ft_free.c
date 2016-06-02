#include "../INC/corewar.h"

void 		ft_free_champ(t_champ *champ, t_array *array, int nb_champ)
{
	while (nb_champ >= 0)
	{
		(champ[nb_champ].name) ? free(champ[nb_champ].name) : 0;
		(champ[nb_champ].comment) ? free(champ[nb_champ].comment) : 0;
		nb_champ--;
	}
}
