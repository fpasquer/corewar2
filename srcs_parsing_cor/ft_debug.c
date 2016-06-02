#include "../INC/corewar.h"

void 		ft_debug_add_color(t_array *array, t_champ *champ, int nb_champ, int i)
{
	int 	count;
	int 	count2;

	if (i >= nb_champ)
		return ;
	count = (SIZE_ARRAY / nb_champ) * i;
	count2 = 0;
	while (champ[i].size > count2)
	{
		array[count].player = i + 1;
		count++;
		count2++;
	}
	ft_debug_add_color(array, champ, nb_champ, i + 1);
}

void 		ft_debug_print_array(t_array *array)
{
	int 	i;
	int 	y;
	int 	size;
	char 	*tmp;

	y = 64;
	i = 0;
	size = 0;
	while (i < SIZE_ARRAY)
	{
		(i == y && (y += 64)) ? ft_putendl("") : 0; 
		tmp = ft_llitoa_base(array[i].code_hexa, 16, &size);
		(array[i].player) ? ft_printf("\x1b[3%dm", array[i].player) : 0;
		(size == 1) ? ft_printf("0%s ", tmp) : ft_printf("%s ", tmp);
		ft_putstr("\x1b[0m");
		ft_strdel(&tmp);
		i++;
	}
	ft_putendl("");
}
