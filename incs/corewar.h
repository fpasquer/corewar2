#ifndef COREWAR_H
# define COREWAR_H

#include "../printf/INC/ft_printf.h"
#include <fcntl.h>

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

#define SIZE_ARRAY 4096
#define MAX_PLAYER 4

#define NB_LINE_COLUMN 64

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

typedef struct 		s_array
{
	unsigned char 	code_hexa;
	unsigned char 	player;
	struct s_array 	*next;
	struct s_array 	*prev;
}					t_array;

typedef struct  	s_champ
{
	char			*name;
	char			*comment;
	int 			size;
	int 			reg_array[16];
	int 			carry;
	t_array			*pos;
	t_array			*next_pos;
	struct s_champ 	*next;
	struct s_champ 	*prev;
}					t_champ;

typedef struct 		s_corewar
{
	t_champ			champ[MAX_PLAYER];
	t_array 		grid[SIZE_ARRAY];
	unsigned int 	nb_live;
	unsigned int	cycle_delta;
	unsigned int 	nb_proc;
	int 			cycle_to_die;
	int 			cycle;
}					t_corewar;

void 		ft_debug_add_color(t_array *array, t_champ *champ, int nb_champ, int i);
void 		ft_debug_print_array(t_array *array);
void 		ft_free_champ(t_champ *champ, t_array *array, int nb_champ);
char		*ft_recover_name_champ(int fd);
char		*ft_recover_comment_champ(int fd, int *champ_size);
int			ft_open_file(char **str, int nb_champ, t_champ *champ, t_array *array);
void		ft_recover_instruction(int fd, t_array *array, int *size);
int 		ft_parse_instruction(char *str, t_array *array);

void 		ft_start_vm(t_corewar corewar);

/*
** UTILITAIRE
*/

int 		ft_convert_hexa_to_int(unsigned char *str);

/*
** DIVERS INSTRUCTION
*/


/* 
** OPERATIONS / BITWISES
*/

void 		ft_add(int r1, int r2, int *r3, int *carry);
void 		ft_or(int r1, int r2, int *r3, int *carry);
void 		ft_xor(int r1, int r2, int *r3, int *carry);
void 		ft_sub(int r1, int r2, int *r3, int *carry);
void 		ft_and(int r1, int r2, int *r3, int *carry);

#endif
