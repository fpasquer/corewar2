/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:05:25 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/04 22:18:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"
#include "../incs/corewar.h"


// static t_player				*new_player(char *name, int nb)
// {
// 	char					*end;
// 	t_player				*new;


// 	if (name == NULL || ((end = ft_strstr(name, ".cor")) == NULL) ||
// 		(new = ft_memalloc(sizeof(t_player))) == NULL)
// 		return (NULL);
// 	*end = '\0';
// 	if ((new->name = ft_strndup(name, MY_MAX_LEN_NAME)) == NULL)
// 	{
// 		ft_memdel((void**)&new);
// 		return (NULL);
// 	}
// 	if ((new->color = ft_strdup(COLOR_0)) == NULL)
// 	{
// 		ft_memdel((void**)&new->name);
// 		ft_memdel((void**)&new);
// 		return (NULL);
// 	}
// 	new->nb_player = nb;
// 	return (new);
// }


static t_player				*save_curs_player(t_player *lst,
		unsigned int nb_champ)
{
	unsigned int			i;
	unsigned int			position;
	t_player				*curs;

	curs = lst;
	position = NB_CASE_TAB / nb_champ;
	i = 0;
	while (curs != NULL)
	{
		curs->i_grid = position * i++;
		// printf("%s = %d\n", curs->name, curs->i_grid);
		curs = curs->next;
	}
	return (lst);
}

static t_player				*new_player(char *name, int nb,
		unsigned int nb_champ, t_array *array)
{
	t_player				*new;
	int						fd;
	int 					y;
	static int 				spacing;
	static int 				i = 1;

	y = NB_CASE_TAB / nb_champ;
	if ((fd = ft_fopen(name, "r")) == -1)
		return (NULL);
	if (!(new = (t_player*)ft_memalloc(sizeof(t_player))))
		return (NULL);
	new->name = ft_recover_name_champ(fd);
	new->comment = ft_recover_comment_champ(fd, &new->size);
	new->pos = i;
	ft_recover_instruction(fd, &array[spacing], &new->size);
	close(fd);
	new->reg[1] = nb;
	spacing += y;
	i++;
	return (new);
}

static void					add_new_player(t_player **lst, t_player **new)
{
	t_player				*curs;

	if (lst == NULL || new == NULL)
		return ;
	if ((*lst) == NULL)
		(*lst) = (*new);
	else
	{
		curs = (*lst);
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = (*new);
	}
}

t_player					*save_player(int argc, char **argv, t_vm *vm)
{
	int						i;
	int						j;
	unsigned int 			nb_champ;
	t_player				*new;
	t_player				*lst;

	i = 0;
	while (i < argc && argv[i][0] == '-')
		i = (ft_strcmp(argv[i], "-d") == 0 || ft_strcmp(argv[i], "-n") == 0 ||
				ft_strcmp(argv[i], "-s") == 0) ||
				ft_strcmp(argv[i], "-dm") == 0 ? i + 2 : i + 1;
	j = -1;
	lst = NULL;
	nb_champ = ((vm->flags & NUMBER) != 0) ? (argc - i + 1) / 2 : argc - i;
	while (i < argc)
	{
		if ((new = new_player(argv[i], (vm->flags & NUMBER)
			!= 0 ? ft_atoi(argv[i - 1]) : j--, nb_champ, vm->array)) == NULL)
			return (del_player(&lst));
		add_new_player(&lst, &new);
		i = (vm->flags & NUMBER) ? i + 2 : i + 1;
		vm->nb_player++;
	}
	return (save_curs_player(lst, nb_champ));
}

t_player					*del_player(t_player **lst)
{
	t_player				*tmp;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	while ((*lst) != NULL)
	{
		tmp = (*lst)->next;
		ft_memdel((void**)&(*lst)->name);
		// ft_memdel((void**)&(*lst)->color);
		ft_memdel((void**)&(*lst)->comment);
		ft_memdel((void**)lst);
		(*lst) = tmp;
	}
	ft_memdel((void**)lst);
	return (NULL);
}
