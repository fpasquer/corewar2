/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:05:25 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/02 19:23:05 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/virtual_machine.h"

static t_player				*new_player(char *name, int nb)
{
	char					*end;
	t_player				*new;

	if (name == NULL || ((end = ft_strstr(name, ".cor")) == NULL) ||
		(new = ft_memalloc(sizeof(t_player))) == NULL)
		return (NULL);
	*end = '\0';
	if ((new->name = ft_strndup(name, MY_MAX_LEN_NAME)) == NULL)
	{
		ft_memdel((void**)&new);
		return (NULL);
	}
	if ((new->color = ft_strdup(COLOR_0)) == NULL)
	{
		ft_memdel((void**)&new->name);
		ft_memdel((void**)&new);
		return (NULL);
	}
	new->nb_player = nb;
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
	t_player				*new;
	t_player				*lst;

	i = 0;
	while (i < argc && argv[i][0] == '-')
		i = (ft_strcmp(argv[i], "-d") == 0 || ft_strcmp(argv[i], "-n") == 0 ||
				ft_strcmp(argv[i], "-s") == 0) ? i + 2 : i + 1;
	j = -1;
	lst = NULL;
	while (i < argc)
	{
		if ((new = new_player(argv[i], (vm->flags & NUMBER)
				!= 0 ? ft_atoi(argv[i - 1]) : j--)) == NULL)
			return (del_player(&lst));
		add_new_player(&lst, &new);
		i = (vm->flags & NUMBER) ? i + 2 : i + 1;
		vm->nb_player++;
	}
	return (lst);
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
		ft_memdel((void**)&(*lst)->color);
		ft_memdel((void**)lst);
		(*lst) = tmp;
	}
	ft_memdel((void**)lst);
	return (NULL);
}
