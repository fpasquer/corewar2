#include "../INC/corewar.h"

void 		ft_stock_hexa_to_array(t_array *array, unsigned char *str, int size)
{
	int 	i;

	i = 0;
	while (i < size)
	{
		array[i].code_hexa = str[i];
		i++;
	}
}

int 		ft_name_instruction(char instruction, t_array *array)
{
	if (instruction == LD || instruction == AND || instruction == OR
			|| instruction == XOR || instruction == LLD)
	{
		array->code_hexa = instruction;
		return (4);
	}
	else if (instruction == ST || instruction == ADD || instruction == SUB
			|| instruction == LDI || instruction == STI || instruction == LLDI
				|| instruction == AFF)
	{
		array->code_hexa = instruction;
		return (2);
	}
	array->code_hexa = instruction;
	return (instruction);
}

void 		ft_instruction_type(int tmp, int i, int *size_param)
{
	if (tmp == 3)
		tmp--;
	else if (i == 4 && tmp == 2)
		tmp = i;
	if (tmp > 0)
		*size_param += tmp;
}

int			ft_ocp_instruction(unsigned char *str, int i, t_array *array)
{
	char 	tmp;
	int 	size_param;

	size_param = 0;
	tmp = *str >> 6;
	ft_instruction_type(tmp, i, &size_param);
	tmp = (*str & MASK_6_BITS) >> 4;
	ft_instruction_type(tmp, i, &size_param);
	tmp = (*str & MASK_4_BITS) >> 2;
	ft_instruction_type(tmp, i, &size_param);
	array->code_hexa = *str;
	ft_stock_hexa_to_array(&array[1], &str[1], size_param);
	return (size_param);
}

/*
**
** Preminer byte contient le nom de l'instruction
** Dexieme byte contient les types de parametres
** si l'instruction est autre que zjmp & fork
**
*/

int 		ft_parse_instruction(char *str, t_array *array)
{
	int 	i;

	i = ft_name_instruction(str[0], array);
	if (i <= 4 && i != LIVE)
	{
		i = ft_ocp_instruction((unsigned char*)&str[1], i, &array[1]);
		return (i + 2);
	}
	else if (i == ZJMP || i == FORK || i == LFORK)
	{
		ft_stock_hexa_to_array(&array[1], (unsigned char*)&str[1], 2);
		return (3);
	}
	ft_stock_hexa_to_array(&array[1], (unsigned char *)&str[1], 4);
	return (5);
}

void 		ft_init_vm(t_corewar *corewar, int nb_proc)
{
	corewar->cycle_delta = 50;
	corewar->nb_proc = nb_proc;
	corewar->cycle_to_die = 1536;
}

int			main(int argc, char *argv[])
{
	t_corewar 	corewar;

	if (argc > 1 && argc < 6)
	{
		/*
		** PARSING
		*/

		argc--;
		ft_bzero(&corewar, sizeof(t_corewar));
		ft_open_file(&argv[1], argc, corewar.champ, corewar.grid);
		ft_debug_add_color(corewar.grid, corewar.champ, argc, 0);
		ft_debug_print_array(corewar.grid);

		/*
		** ?  
		*/

		ft_init_vm(&corewar, argc);
		ft_start_vm(corewar);

		/*
		** PART - TEST
		*/
		ft_free_champ(corewar.champ, corewar.grid, argc - 1);
	}
	return (0);
}
