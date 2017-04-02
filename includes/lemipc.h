/*
** lemipc.h for lemipc in /home/rougag_b/rendu/PSU_2016_lemipc
** 
** Made by Boris ROUGAGNOU
** Login   <rougag_b@epitech.net>
** 
** Started on  Fri Lun 27 15:37:56 2017 Boris ROUGAGNOU
** Last update Sun Apr  2 23:47:36 2017 Boris ROUGAGNOU
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

#include <sys/ipc.h>
#include <stdbool.h>

# define RETURN_ERROR 84
# define FALSE -1
# define TRUE 1
# define MAP_X 10
# define MAP_Y 10

typedef enum	direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
}		t_direction;

typedef struct	s_ipc
{
  int		win;
  char		*path_key;
  char		*map;
  int		player;
  int		pos;
  int		id;
  int		shm_id;
  int		sem_id;
  int		position;
  int		msg_id;
  int		alive;
  int		ennemy;
  t_direction	move;
  bool		first;
  key_t		key;
}		t_ipc;

typedef struct	s_msg
{
  long		mtype;
  char		str[10];
}		t_msg;

int	movePlayer(t_ipc *, int, int, int);

int	moveCalculDirection(int, t_direction);

void	moveRandom(t_ipc *);

int	checkAround(t_ipc *pIpc, int x, int y);

void	ia(t_ipc *);

void	lock(int);

void	unlock(int);

t_ipc	*create_map(char *, char *);

void	display_game(t_ipc *pIpc);

int	usage();

void	move(t_ipc *pIpc);

void	chooseDirection(t_ipc *pIpc);

bool	check_ennemy(t_ipc *pIpc);

#endif /* !LEMIPC_H_ */
