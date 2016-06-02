#include "../INC/corewar.h"

int			ft_open_file(char **str, int nb_champ, t_champ *champ, t_array *array)
{
	int		fd;
	int 	i;
	int 	y;
	int 	spacing;

	y = SIZE_ARRAY / nb_champ;
	i = 0;
	spacing = 0;
	while (i < nb_champ)
	{
		fd = open(str[i], O_RDONLY);
		if (fd < 0 && ft_printf("ERROR : %s doesn't exist\n", str[i]))
			exit (ERROR_FILE);
		champ[i].name = ft_recover_name_champ(fd);
		champ[i].comment = ft_recover_comment_champ(fd, &champ[i].size);
		ft_printf("name champ : %s\n", champ[i].name);
		ft_printf("comment champ : %s\n", champ[i].comment);
		ft_recover_instruction(fd, &array[spacing], &champ[i].size);
		ft_putendl("");
		close(fd);
		spacing += y;
		i++;
	}
	return (1);
}
