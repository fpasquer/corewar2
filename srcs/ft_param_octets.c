#include "corewar.h"

int 			ft_param_0_octet(t_vm *vm, t_player *plr, int octet, int index)
{
	return (0);
}

int 			ft_param_1_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	int			reg;
	static int toto = 0;
	reg = vm->array[index].code_hexa;
		// mvwprintw(vm->w_info, 55 + toto++, 3, "reg = %d", reg);
	if (reg < 1 || reg > 16)
	{
		plr->info.error = ERROR_REG;
		return (0);
	}
	plr->info.reg_f = plr->info.index_f_param == index ? reg : plr->info.reg_f;
	plr->info.reg_s = plr->info.index_s_param == index ? reg : plr->info.reg_s;
	plr->info.reg_t = plr->info.index_t_param == index ? reg : plr->info.reg_t ;
	return (plr->reg[reg]);
}

// static char		*get_str(char val)
// {

// }

int 			ft_param_4_octets(t_vm *vm, t_player *plr, int octet, int index)
{
	char 							*str;
	char 							tab[9];
	char 							zero[3];
	int      						i;
	int 							octet_save;

	octet_save = octet;
	ft_bzero(tab, sizeof(char) * 9);
	while (octet-- > 0)
	{
		str = ft_itoa_base(vm->array[index].code_hexa, 16);
		if (ft_strlen(str) < 2)
		{
			ft_memset(zero, '0', sizeof(char) * 2);
			zero[1] = str[0];
			ft_strcat(tab, zero);
		}
		else
			ft_strcat(tab, str);
		index = (index + 1) % 4096;
		ft_strdel(&str);
	}
	ft_atoi_base(tab, 16, &i);
	return (octet_save == 2 ? (short)i : i);
}
