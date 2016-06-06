#include "corewar.h"

int 			ft_param_1_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	return (plr->reg[vm->array[index].code_hexa]);
}

int 			ft_param_2_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int 					power;
	short 					nb;

	nb = 0;
	power = 0;
	if (index > 4095)
		index %= 4096;
	if (octet == 1)
		return (plr->reg[vm->array[index].code_hexa]);
	while (octet-- > 0)
	{
		if (vm->array[index].code_hexa)
			nb = nb + ((ft_power(octet, 16)) * vm->array[index].code_hexa);
		power++;
		index++;
		if (index > 4095)
			index %= 4096;
	}
	return (nb);
}

int 			ft_param_4_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int 		 		 			nb;
	char 							*str;
	char 							tab[9];
	unsigned long long int      	i;

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
	ft_atoi_base(tab, 10, &i);
	printf("\n%s : %llu", tab, i);
	return (i);
}
