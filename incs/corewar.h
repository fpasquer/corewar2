#ifndef COREWAR_H
# define COREWAR_H

#include "virtual_machine.h"
#include <fcntl.h>

/*
**	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
**	STI :
**	01,	01|10|11,	10|01,00
**	r1, r1, r1 = 84
** 	r1, r1, %1 = 88
**  r1, %1, r1 = 64
** 	r1, %1, %1 = 68
**  r1, 14, r1 = 74
** 	r1, 14, %1 = 78
**
**	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
**
**	LIVE :
**	10000000 PAS D'OCTET D'ENCODAGE
**  SOUS 4 OCTETS
**  %1 = 128
**
**  ZJMP :
**	PAS d'OCTET D'ENCODAGE
**  SOUS 2 OCTETS
*/





/*
**
** instruction :
**
** st
** ld
** ldi
** sti
** zjmp	
**
**
** 0f
** 13
** 17
** 1a
** 0f
**
*/


#define MASK_6_BITS 0x30
#define MASK_4_BITS 0xC

#define LIVE 1
#define LD 2
#define ST 3
#define ADD 4
#define SUB 5
#define AND 6
#define OR 7
#define XOR 8
#define ZJMP 9
#define LDI 10
#define STI 11
#define FORK 12
#define LLD 13
#define LLDI 14
#define LFORK 15
#define AFF 16

#define ERROR_MALLOC 10
#define ERROR_READ 11
#define ERROR_FILE 12
#define ERROR_SIZE_CHAMP 13

#define DIR_C 30
#define IND_C 31
#define REG_C 32

#define NB_LIVE_MIN 21
#define CHECKS_MAX 10

typedef struct s_ocp
{
	int 		i;
	int  		(*p)(t_vm *vm, t_player *plr, int octet, int index);
}				t_ocp;

typedef struct 	s_delais
{
	char 		instruction;
	int 		delais;
} 				t_delais;

typedef struct s_instruction
{
	char  		instruction;
	int			(*p)(t_vm *vm, t_player *plr);
}				t_instruction;

char		*ft_recover_name_champ(int fd);
char		*ft_recover_comment_champ(int fd, int *champ_size);
int			ft_open_file(char **str, int nb_champ, t_player *champ, t_array *array);
void		ft_recover_instruction(int fd, t_array *array, int *size);
int 		ft_parse_instruction(char *str, t_array *array);
int 		ft_power(int power, int nb);

/*
** UTILITAIRE
*/

int 		ft_convert_hexa_to_int(unsigned char *str);
char		*ft_llitoa_base(long long int n, int base, int *u);
char		*ft_llitoa_base2(long long int n, int base, int *u);
// short	ft_atoi_base2(const char *s, int base, short *nb);
int 		ft_check_size_max(int i, int index);
// int 		ft_param_2_octets(t_vm *vm, t_player *plr, int octet, int index);
int 		ft_param_4_octets(t_vm *vm, t_player *plr, int octet, int index);
int 		ft_param_1_octets(t_vm *vm, t_player *plr, int octet, int index);
void 		ft_print_param_to_array_4_octets(t_vm *vm, t_player *plr, int index, unsigned int nb);
/*
** DIVERS INSTRUCTION
*/

void 		ft_processus(t_vm *vm);
void 		ft_check_processus_life(t_vm *vm);
void 		ft_check_delais(t_vm *vm);

/* 
** OPERATIONS / BITWISES
*/

int 		ft_and(t_vm *vm, t_player *plr);
int 		ft_nothing(t_vm *vm, t_player *plr);
int 		ft_sti(t_vm *vm, t_player *plr);
int 		ft_zjmp(t_vm *vm, t_player *plr);
int 		ft_live(t_vm *vm, t_player *plr);

int			ft_fork(t_vm *vm, t_player *plr);
//int			ft_lfork(t_vm *vm, t_player *plr);

#endif
