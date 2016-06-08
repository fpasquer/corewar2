/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 11:57:41 by fpasquer          #+#    #+#             */
/*   Updated: 2016/06/08 11:09:11 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H

# define VIRTUAL_MACHINE_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <ncurses.h>

# define WIDTH_WINNER 44
# define HEIGHT_WINNER 12

# define NB_CASE_TAB 4096
# define NB_MOD 512
# define NB_LINE_COLUMN 64

# define MAX_REG 17

# define MAX_PLAYER 4

# define WIDTH_INFO 60

# define PAUSE 0
# define RUN 1

# define ESCAPE 27
# define SPACE 32

# define CYCLE_SEG 50

# define REFRESH 10

# define INIT_CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECK 10

# define COLOR_0 "\033[0;31m"
# define COLOR_1 "\033[0;32m"
# define COLOR_2 "\033[0;33m"
# define COLOR_3 "\033[0;34m"

# define MY_MAX_LEN_NAME 20
/*
**	Flags:
**		_ Dump la memoire tout les x cycles
**			[-d 12] : dump la memoire tout les 12 cycles
**		_ Number Permet de preciser pour chaque joueur leur nombre atribue
**			[-n 20 joueur_name] attribue le nombre 20 a joueur_name
**			Si 1 -n est utilise, lensemble des joueurs doivent avoir un nombre
**		_ Visu active le mode d'affichage avec les Ncurses
**			[-v]
**		_ Dump et met en pause le programme tout les x cycles
**			[-s 35]
*/

# define NONE 0
# define DUMP 1
# define NUMBER 2
# define VISU 4
# define SUSPEND 8
# define DUMP_M 16

# define NAME_FILE_DUMP_MEM "dump_memory.txt"

typedef struct s_info
{
	int 		epd;
	int 		ocp;					//ocp
	int 		size_ocp_param;			//size des X parametres.
	int 		t_f_param; 				//t = type, f = first
	int 		t_s_param;				//t = type, s = second
	int 		t_t_param;				//t = type, t = third
	int 		s_f_param;				//s = size
	int 		s_s_param;				//s = size
	int 		s_t_param;				//s = size
	int 		nb_f_param;				//valeur du parametre 1
	int 		nb_s_param;				//valeur du parametre 2
	int 		nb_t_param;				//valeur du parametre 3
	int 		index_ocp;				//index de l'ocp dans la grille.
	int 		index_f_param;			//index de du premier parametre dans la grille.
	int 		index_s_param;			//index de du second parametre dans la grille.
	int 		index_t_param;			//index de du third parametre dans la grille.
	int 		reg_f;					//numero du registre.
	int 		reg_s;
	int 		reg_t;
	int 		error;
}				t_info;


typedef struct				s_player
{
	/*
	** RAJOUT PAR JC
	*/

	int 					do_instruction;
	unsigned int 			delais;

	/*
	**
	*/
	int 					pos; 			//numero du joueur par rapport a la liste chaine au start.
	char					*name;			//nom du joueur
	char					*comment;		//commentaire du joueur
	unsigned int			reg[MAX_REG];	//les 16 registres du joueur
	unsigned int			i_grid;			//index dans la grille
	unsigned int			nb_live;		//nb de live dans le cicle
	unsigned int			last_live;		//cicle du last live
	unsigned int			i_player;		//index du joueur pour comter live
	int						size;			//taille du champion
	int 					carry;
	t_info					info;
	struct s_player			*next;			//pour les forks
}							t_player;

typedef struct				s_array
{
	unsigned char			code_hexa;			//code exa de la case
	unsigned char			player;				//nb du joueur a qui est la case
	int 					x;
	int 					y;
}							t_array;

typedef struct				s_vm
{
	/*
	** RAJOUT PAR JC
	*/

	unsigned int 			cycle_tmp;			// compteur s'incremente jusqu'a cycle_to_die puis reset a 0;
	unsigned int 			check_max;

	/*
	**
	*/
	FILE *mem;									//a supprimer

	int						status;				//run ou pause
	int						*grid;				//grille 1d pour JC
	int						**grid2d;			//dito grid en 2d
	int						nb_dump;			//dump memoire / les nb_dump cycle
	int						nb_susp;			//suspend memoire / les nb_susp cycle
	int						flags;				//flags
	int						fd;					//ou sera dump la memoire
	unsigned int			nb_player;			//nombre de joueur de la partie
	unsigned int			cycle;				//nb de cycle
	unsigned int			cycle_to_die;		//nb de cycle_to_die
	unsigned int			nb_live;			//pour compter le nombre de live
	unsigned int			nb_live_each_plr[MAX_PLAYER];// Pour afficher le nombre de live fork compris
	unsigned int			cycle_last_live[MAX_PLAYER];// pour afficher le cycle du dernier live
	unsigned long long int	nb_proces;			//nb Processes
	unsigned long long int	pause;				//pour gerer SUSPEND
	unsigned long long int	dump;				//pour gerer DUMP
	t_array					array[NB_CASE_TAB];	//tableau memoire instruction
	t_player				*plr;				//tableau de joueur
	WINDOW					*w_grid;			//affichage de la grille ncurses
	WINDOW					*w_info;			//affichage des infos courante
	WINDOW					*w_winner;			//affiche le winner
}							t_vm;

void						error(char *s);
t_vm						*init_vm(int argc, char **argv);
t_vm						*del_vm(t_vm **vm);
void						refrech_win(t_vm *vm);
void						loop_virtual_machin(t_vm *vm);
int							check_key(int key, t_vm *vm);
int							**make_tab_2d(int *tab, int height, int width);
void						print_grid(t_vm *vm);
void						print_info(t_vm *vm);
void						print_dump(t_vm *vm);
t_player					*save_player(int argc, char **argv, t_vm *vm);
t_player					*del_player(t_player **lst);
int							get_hexa(t_vm *vm, unsigned int i_grid,
		unsigned int nb_octet, int *nb);
int							change_index(int i, char *argv, int argc);
int							change_index2(t_vm *vm, int i, char **argv,
		int argc);
void						pop_winner(t_vm *vm);
int							ft_ld(t_vm *vm, t_player *plr);
int							ft_lld(t_vm *vm, t_player *plr);
int							ft_lfork(t_vm *vm, t_player *plr);
int							ft_st(t_vm *vm, t_player *plr);
unsigned int				get_new_index(int decalage, unsigned int i_grid);
unsigned int				get_new_index_with_mod(int decalage,
		unsigned int i_grid);


#endif
