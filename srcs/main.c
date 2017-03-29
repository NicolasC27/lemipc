/*
** main.c for main.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Mon Mar 27 16:16:58 2017 Nicolas
** Last update Mon Mar 27 17:13:02 2017 Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <zconf.h>
#include <slcurses.h>
#include <unistring/stdbool.h>
#include "../includes/lemipc.h"


void lock(int sem_id)
{
  struct sembuf op;

  op.sem_flg = 0;
  op.sem_num = 0;
  op.sem_op  = -1;
  semop(sem_id, &op, 1);
}

void unlock(int sem_id)
{
  struct sembuf op;

  op.sem_flg = 0;
  op.sem_num = 0;
  op.sem_op  = 1;
  semop(sem_id, &op, 1);
}

t_ipc *create_map(char *path_key, char *nb_team)
{
  t_ipc *tmp;

  if ((tmp = malloc(sizeof(t_ipc))) == NULL)
    return NULL;
  tmp->pos = 0;
  tmp->id = atoi(nb_team);
  tmp->path_key = strdup(path_key);
  tmp->key = ftok(getenv("PWD"), 0);
  tmp->shm_id = shmget(tmp->key, SIZE_SHM, SHM_W | SHM_R);
  if (tmp->shm_id == -1)
    {
      tmp->shm_id = shmget(tmp->key, SIZE_SHM, IPC_CREAT | SHM_R | SHM_W);
      tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
      printf("Create");
    }
  else
    {
      printf("Using");
      tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
//      shmctl(tmp->shm_id, IPC_RMID, NULL);
    }
  tmp->position = rand() % SIZE_SHM;
  while (tmp->map[tmp->position] != 0)
    tmp->position = rand() % SIZE_SHM;
  lock(tmp->sem_id);
  bzero(tmp->map, SIZE_SHM);
  tmp->map[tmp->position] = tmp->id;
  unlock(tmp->sem_id);
  usleep(1000);

  return (tmp);
}	

int 	usage()
{
  fprintf(stderr, "Usage: ./lemipc path_to_key team_number\n\n");
  fprintf(stderr, "path_to_key is a valid path that will be used by ftok\n");
  fprintf(stderr, "team_number is the team number assigned to the current player\n");
  return (0);
}


bool game_end(t_ipc *pIpc)
{
  return false;
}

void start_game(t_ipc *pIpc)
{
//  printf("\npIpc->position = %d \n", pIpc->position);
//  exit(0);
  printf("\npIpc->map[pIpc->position] = %d\n", pIpc->map[pIpc->position]);

  exit (0);
  while (!game_end(pIpc))
    {
      lock(pIpc->sem_id);
      pIpc->map[pIpc->position] = 0;
      unlock(pIpc->sem_id);
    }
}

int	main(int argc, char **argv)
{
  t_ipc *game;

  if (argc != 3)
    return (usage());
  srand(time(NULL));

  if ((game = create_map(argv[1], argv[2])) == NULL)
    return (RETURN_ERROR);
  start_game(game);
}
