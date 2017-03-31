/*
** lemipc.h for lemipc in /home/rougag_b/rendu/PSU_2016_lemipc
** 
** Made by Boris ROUGAGNOU
** Login   <rougag_b@epitech.net>
** 
** Started on  Fri Lun 27 15:37:56 2017 Boris ROUGAGNOU
** Last update Fri Mar 31 18:43:22 2017 Boris ROUGAGNOU
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# define RETURN_ERROR	84
# define SIZE_SHM	100
# define MAP_X		10
# define MAP_Y		10

typedef struct		s_ipc
{
  int			player;
  int			pos;
  int			id;
  bool			first;
  char			*path_key;
  key_t			key;
  int			shm_id;
  int			sem_id;
  char			*map;
  int			position;
  int			msg_id;
  int			alive;
}			t_ipc;

typedef struct		s_msg
{
  long			mtype;
  char			str[10];
}			t_msg;

#endif /* !LEMIPC_H_ */
