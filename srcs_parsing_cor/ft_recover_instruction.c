#include "../INC/corewar.h"

void		ft_recover_instruction(int fd, t_array *array, int *size)
{
	char	instruction[10000];
	int 	y;
	int 	i;

	ft_bzero(instruction, sizeof(char) * 10000);
	i = read(fd, instruction, 10000);
	if (i == -1 || i == 0)
		exit(ERROR_READ);
	if (i != *size)
		exit(ERROR_SIZE_CHAMP);
	y = 0;
	while (y < i)
		y += ft_parse_instruction(&instruction[y], &array[y]);
	ft_printf("Champ size %d octets\n", y);
}
