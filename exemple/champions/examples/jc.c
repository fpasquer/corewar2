/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 17:47:29 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/31 19:29:40 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include					"../../../libft/libft.h"
#include <stdio.h>

static int					check_char_base(char c, int base)
{
	if (ft_isalnum(c) == 0)
		return (0);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		c = (c >= 'a' && c <= 'z') ? c - 'a' + 10 : c - 'A' + 10;
	else
		c -= '0';
	return ((base <= c) ? 0 : 1);
}

unsigned long long int		ret_val(char c, size_t exp, int base)
{
	unsigned long long int	ret;
	unsigned long long int	power;

	if ((power = (unsigned long long int)ft_pow(base, exp)) == 0)
		power = 1;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		c = (c >= 'a' && c <= 'z') ? c - 'a' + 10 : c - 'A' + 10;
	else
		c -= '0';
	return (c * power);
}

int							ft_atoi_base(const char *s, int base,
		unsigned long long int *nb)
{
	size_t					len;
	size_t					i;
	unsigned long long int	mem;

	if (s == NULL || base < 2 || base > 16 || (len = ft_strlen(s)) <= 0)
		return (-1);
	mem = 0;
	i = len;
	while (i-- > 0)
	{
		if (check_char_base(s[i], base) == 0)
			return (-1);
		mem += ret_val(s[i], len - i - 1, base);
	}
	 (*nb) = mem;
	return (0);
}

int							main(void)
{
	char					str[] = "1111111111";
	unsigned long long int	nb;

	if (ft_atoi_base(str, 17, &nb) == -1)
		ft_putstr("erreur\n");
	else
		printf("%llu\n", nb);
	return (0);
}
