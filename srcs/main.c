/*
** main.c for main.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Mon Mar 27 16:16:58 2017 Nicolas
** Last update Sun Apr  2 22:40:54 2017 Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <unistd.h>
#include "../includes/lemipc.h"

void delete(t_ipc *pIpc)
{
  static t_ipc *sig;

  if (sig)
    {
      if (sig->first == true)
	{
	  semctl(sig->sem_id, 1, IPC_RMID);
	  shmctl(sig->shm_id, IPC_RMID, 0);
	  msgctl(sig->msg_id, IPC_RMID, 0);
	} else
	{
	  sig->map[sig->position] = 0;
	}
    }
  sig = pIpc;
}

void destroy_game(int sig)
{
  (void) sig;
  delete((t_ipc *) 0);
  exit(0);
}

bool game_end(t_ipc *pIpc)
{
  if (pIpc->alive == 0 || pIpc->win >= 5)
    return (true);
  else
    if (pIpc->alive == 1)
      return (false);
  return (true);
}

void start_game(t_ipc *pIpc)
{
  while (!game_end(pIpc))
    {
      lock(pIpc->sem_id);
      display_game(pIpc);
      ia(pIpc);
      unlock(pIpc->sem_id);
      sleep(1);
    }
}

int main(int argc, char **argv)
{
  t_ipc *game;

  signal(SIGINT, destroy_game);
  if (argc != 3)
    return (usage());
  srand(time(NULL));
  if ((game = create_map(argv[1], argv[2])) == NULL)
    return (RETURN_ERROR);
  delete(game);
  game->win = 0;
  game->ennemy = false;
  game->alive = 1;
  display_game(game);
  start_game(game);
  sleep(2);
  delete(game);
}
