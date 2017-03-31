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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <zconf.h>
#include <slcurses.h>
#include <unistring/stdbool.h>
#include "../includes/lemipc.h"


void lock(int sem_id)
{
  struct sembuf op;

  op.sem_flg = 0;
  op.sem_num = 0;
  op.sem_op = -1;
  semop(sem_id, &op, 1);
}

void unlock(int sem_id)
{
  struct sembuf op;

  op.sem_flg = 0;
  op.sem_num = 0;
  op.sem_op = 1;
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
  tmp->key = ftok(getenv(path_key), 0);
  tmp->shm_id = shmget(tmp->key, SIZE_SHM, SHM_W | SHM_R);

  if (tmp->shm_id == -1)
    {
      tmp->first = true;
      tmp->player = 1;
      tmp->shm_id = shmget(tmp->key, SIZE_SHM, IPC_CREAT | SHM_R | SHM_W);
      tmp->sem_id = semget(tmp->key, 1, IPC_CREAT | SHM_R | SHM_W);
      semctl(tmp->sem_id, 0, SETVAL, 1);
      tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
      bzero(tmp->map, SIZE_SHM);
      tmp->msg_id = msgget(tmp->key, IPC_CREAT | SHM_R | SHM_W);
      printf("Using create %d\n", tmp->msg_id);
      printf("Create");
    } else
    {
      tmp->first = false;
      printf("Using");
      tmp->player += 1;
      tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
      tmp->sem_id = semget(tmp->key, 1, SHM_R | SHM_W);
//      semctl(tmp->sem_id, 0, IPC_RMID);
      tmp->msg_id = msgget(tmp->key, SHM_R | SHM_W);
      printf("\nUsing msgq %d\n", tmp->msg_id);
      tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);

//      tmp->sem_id = semget(tmp->key, 1, IPC_CREAT| SHM_R | SHM_W);
    }

  tmp->position = rand() % SIZE_SHM;
  while (tmp->map[tmp->position] != 0)
    tmp->position = rand() % SIZE_SHM;
  tmp->map[tmp->position] = tmp->id;

  return (tmp);
}

int usage()
{
  fprintf(stderr, "Usage: ./lemipc path_to_key team_number\n\n");
  fprintf(stderr, "path_to_key is a valid path that will be used by ftok\n");
  fprintf(stderr,
	  "team_number is the team number assigned to the current player\n");
  return (0);
}


void display_game(t_ipc *pIpc)
{
  int i;
  int y;

  i = 0;
  while (i < 100)
    {
      y = 0;
      while (y < 10)
	{
	  printf("%d", pIpc->map[y + i]);
	  y += 1;
	}
      printf("\n");
      i += 10;
    }
  printf("\n");

}

int get_msgq(t_ipc *info, int msg_id, int team_number, t_msg *msg)
{
  int val;

  val = msgrcv(info->msg_id, &msg, sizeof(msg), info->id, IPC_NOWAIT);
  return (val);
}

//void test()
//{
//  msg.mtype = pIpc->id;
//  sprintf(&(msg.str[0]), "%d:%d", pIpc->position, pIpc->position);
//
//  lock(pIpc->sem_id);
//  msgsnd(pIpc->msg_id, &msg, strlen(msg.str) + 1, 0);
//  unlock(pIpc->sem_id);
//  lock(pIpc->sem_id);
//  val = msgrcv(pIpc->msg_id, &msg, sizeof(msg), pIpc->id, IPC_NOWAIT);
//  unlock(pIpc->sem_id);
//
//  printf("%d %s", val, msg.str);
//}

int get_team(t_ipc *ipc, int x, int y)
{
  int tmp;

  tmp = ipc->map[(x * MAP_X) + y];
  return (tmp);
}

int look_around(t_ipc *pIpc, int x, int y)
{
  int enemy;
  int team_around;

  enemy = 0;
  if ((team_around = get_team(pIpc, x, y - 1) != -1) &&
      (team_around != pIpc->id))
    enemy += 1;
  else
    if ((team_around = get_team(pIpc, x, y + 1) != -1) &&
	(team_around != pIpc->id))
      enemy += 1;
    else
      if ((team_around = get_team(pIpc, x + 1, y) != -1) &&
	  (team_around != pIpc->id))
	enemy += 1;
      else
	if ((team_around = get_team(pIpc, x - 1, y) != -1) &&
	    (team_around != pIpc->id))
	  enemy += 1;
  printf("%d", team_around);
  return enemy;
}

void ia(t_ipc *pIpc)
{
  pIpc->alive = 0; /* POUR LA MOULINETTE, NE PAS TOUCHER */
  if (pIpc->alive == 1)
    {
      if ((look_around(pIpc, pIpc->position % MAP_X, pIpc->position / MAP_Y)) >=
	  2)
	{

	}
    }
}

bool game_end(t_ipc *pIpc)
{
  if (pIpc->alive == 0)
    return true;
  else
    if (pIpc->alive == 1)
      return false;
}


void start_game(t_ipc *pIpc)
{
  t_msg msg;
  int val;

  printf("\npIpc->map[pIpc->position] = %d\n", pIpc->map[pIpc->position]);
  while (!game_end(pIpc))
    {
      lock(pIpc->sem_id);
      display_game(pIpc);
      ia(pIpc);
      unlock(pIpc->sem_id);
    }
}

void delete(t_ipc *pIpc)
{
  semctl(pIpc->sem_id, 1, IPC_RMID);
  shmctl(pIpc->shm_id, IPC_RMID, (struct shmid_ds *) 0);
  msgctl(pIpc->msg_id, IPC_RMID, (struct msqid_ds *) 0);
}

int main(int argc, char **argv)
{
  t_ipc *game;

  if (argc != 3)
    return (usage());
  srand(time(NULL));
  if ((game = create_map(argv[1], argv[2])) == NULL)
    return (RETURN_ERROR);
  game->alive = 1;
  start_game(game);
  display_game(game);
  if (game->first == true)
    {
      sleep(5);
      delete(game);
    }
}
