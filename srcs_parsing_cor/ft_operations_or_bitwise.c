#include "../INC/corewar.h"

/*
** Modifier le carry uniquement sur *r3 = 0 ?
*/

void 		ft_add(int r1, int r2, int *r3, int *carry)
{
	*r3 = r1 + r2;
	*carry = (*r3) ? 0 : 1;
}

void 		ft_sub(int r1, int r2, int *r3, int *carry)
{
	*r3 = r1 - r2;
	*carry = (*r3) ? 0 : 1;
}

void 		ft_and(int r1, int r2, int *r3, int *carry)
{
	*r3 = r1 & r2;
	*carry = (*r3) ? 0 : 1;
}

void 		ft_or(int r1, int r2, int *r3, int *carry)
{
	*r3 = r1 | r2;
	*carry = (*r3) ? 0 : 1;
}

void 		ft_xor(int r1, int r2, int *r3, int *carry)
{
	*r3 = r1 ^ r2;
	*carry = (*r3) ? 0 : 1;
}
