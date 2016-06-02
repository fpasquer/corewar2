/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 20:40:02 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/27 09:02:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"

int							main(int argc, char **argv)
{
	char					*nb;
	char					*str;
	int						start;
	int						fd;

	if (argc != 2)
		return (0);
	fd = ft_fopen("test", "w+");
	start = ft_atoi(argv[1]);
	while (start < 512)
	{
		nb = ft_itoa(start);
		str = ft_strjoin("\t\tst\t\tr2, -", nb);
		ft_putendl_fd(str, fd);
		ft_memdel((void**)&str);
		ft_memdel((void**)&nb);
		start += 9;
	}
	close(fd);
	return (0);
}
