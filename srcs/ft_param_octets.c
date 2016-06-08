#include "corewar.h"

int 			ft_param_0_octet(t_vm *vm, t_player *plr, int octet, int index)
{
	return (0);
}

int 			ft_param_1_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int			reg;

	reg = vm->array[index].code_hexa;
	if (reg < 1 || reg > 16)
	{
		plr->info.error = ERROR_REG;
		return (0);
	}
	plr->info.reg_f = plr->info.index_f_param == index ? reg : 0;
	plr->info.reg_s = plr->info.index_s_param == index ? reg : 0;
	plr->info.reg_t = plr->info.index_t_param == index ? reg : 0;
	return (plr->reg[reg]);
}

int 			ft_param_4_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int 		 		 			nb;
	char 							*str;
	char 							tab[9];
	int      						i;
	int 							octet_save;
	int							test;

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
	test = (short)i;

	if (octet_save == 2)
		return ((short)i);
	return (i);
}
