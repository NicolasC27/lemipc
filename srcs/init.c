/*
** init.c for lemipc in /home/rougag_b/rendu/PSU_2016_lemipc
** 
** Made by Boris ROUGAGNOU
** Login   <rougag_b@epitech.net>
** 
** Started on  Fri Mar 31 15:47:31 2017 Boris ROUGAGNOU
** Last update Sun Apr  2 23:38:43 2017 Boris ROUGAGNOU
*/

#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lemipc.h"

t_ipc	*init_tmp(t_ipc *tmp, char *path_key, char *nb_team)
{
  if ((tmp = malloc(sizeof(t_ipc))) == NULL)
    return (NULL);
  tmp->pos = 0;
  tmp->id = atoi(nb_team);
  tmp->path_key = strdup(path_key);
  tmp->key = ftok(getenv(path_key), 0);
  tmp->shm_id = shmget(tmp->key, (MAP_X * MAP_Y), SHM_W | SHM_R);
  return (tmp);
}

t_ipc	*init_tmp_shm(t_ipc *tmp)
{
  tmp->first = false;
  printf("Using");
  tmp->player += 1;
  tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
  tmp->sem_id = semget(tmp->key, 1, SHM_R | SHM_W);
  tmp->msg_id = msgget(tmp->key, SHM_R | SHM_W);
  printf("\nUsing msgq %d\n", tmp->msg_id);
  tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
  return (tmp);
}

t_ipc	*init_tmp_noshm(t_ipc *tmp)
{
  tmp->first = true;
  tmp->player = 1;
  tmp->shm_id = shmget(tmp->key, (MAP_X * MAP_Y), IPC_CREAT | SHM_R | SHM_W);
  tmp->sem_id = semget(tmp->key, 1, IPC_CREAT | SHM_R | SHM_W);
  semctl(tmp->sem_id, 0, SETVAL, 1);
  tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
  bzero(tmp->map, (MAP_X * MAP_Y));
  tmp->msg_id = msgget(tmp->key, IPC_CREAT | SHM_R | SHM_W);
  printf("Using create %d\n", tmp->msg_id);
  printf("Create");
  return (tmp);
}

int	players_board(t_ipc *pIpc)
{
  int	i;
  int	y;
  int	players;

  i = 0;
  players = 0;
  while (i < 100)
    {
      y = 0;
      while (y < 10)
	{
	  if (pIpc->map[y + i] != 0)
	    players += 1;
	  y += 1;
	}
      i += 10;
    }
  return (players);
}

t_ipc	*create_map(char *path_key, char *nb_team)
{
  t_ipc	*tmp;

  tmp = NULL;
  tmp = init_tmp(tmp, path_key, nb_team);
  if (tmp->shm_id == -1)
    tmp = init_tmp_noshm(tmp);
  else
    tmp = init_tmp_shm(tmp);
  if (players_board(tmp) > ((MAP_Y * MAP_X) / 2))
    return (NULL);
  tmp->position = rand() % (MAP_X * MAP_Y);
  while (tmp->map[tmp->position] != 0)
    tmp->position = (rand() % (MAP_X * MAP_Y)) - 1;
  tmp->map[tmp->position] = tmp->id;
  return (tmp);
}
