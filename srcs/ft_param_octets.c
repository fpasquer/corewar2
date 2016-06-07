#include "corewar.h"

int 			ft_param_1_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	return (plr->reg[vm->array[index].code_hexa]);
}

/*
int 			ft_param_2_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int 		 		 			nb;
	char 							*str;
	char 							tab[9];
	// short      						i;
	int 							i;

	ft_bzero(tab, sizeof(char) * 9);
	nb = 0;
	if (index > 4095)
		index %= 4096;
	if (octet == 1)
		return (plr->reg[vm->array[index].code_hexa]);
	while (octet-- > 0)
	{
		str = ft_itoa_base(vm->array[index].code_hexa, 16);
		ft_strcat(tab, str);
		if (vm->array[index].code_hexa)
			nb = nb + ((ft_power(octet, 16)) * vm->array[index].code_hexa);
		index++;
		if (index > 4095)
			index %= 4096;
		ft_strdel(&str);
	}
	ft_atoi_base(tab, 16, &i);
	i = (short)i;
	return (i);
}
*/

int 			ft_param_4_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int 		 		 			nb;
	char 							*str;
	char 							tab[9];
	int      						i;
	int 							octet_save;

	octet_save = octet;
	ft_bzero(tab, sizeof(char) * 9);
	nb = 0;
	if (index > 4095)
		index %= 4096;
	while (octet-- > 0)
	{
		str = ft_itoa_base(vm->array[index].code_hexa, 16);
		ft_strcat(tab, str);
		if (vm->array[index].code_hexa)
			nb = nb + ((ft_power(octet, 16)) * vm->array[index].code_hexa);
		index++;
		if (index > 4095)
			index %= 4096;
		ft_strdel(&str);
	}
	ft_atoi_base(tab, 16, &i);
	if (octet_save == 2)
		return ((short)i);
	return (i);
}
