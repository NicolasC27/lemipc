/*
** ia.c for ia.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun Apr  2 22:39:48 2017 Nicolas
** Last update Sun Apr  2 22:39:48 2017 Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include "../includes/lemipc.h"

bool is_here(char *map, int enemy, int team)
{
  if (enemy == 0)
    return (false);
  if (enemy == false)
    return (true);
  if (map[enemy] != 0 && map[enemy] != team)
    return (true);
  return (false);
}

bool communication(t_ipc *pIpc, int val)
{
  t_msg msg;

  msg.mtype = pIpc->id;
  val = msgrcv(pIpc->msg_id, &msg, sizeof(msg), pIpc->id, IPC_NOWAIT);
  if (val != -1)
    {
      pIpc->ennemy = atoi(msg.str);
      if (is_here(pIpc->map, pIpc->ennemy, pIpc->id) == false)
	check_ennemy(pIpc);
      sprintf(&(msg.str[0]), "%d", pIpc->ennemy);
      msgsnd(pIpc->msg_id, &msg, strlen(msg.str) + 1, IPC_NOWAIT);
    }
  if (val == -1)
    if (check_ennemy(pIpc) == true)
      {
	sprintf(&(msg.str[0]), "%d", pIpc->ennemy);
	msgsnd(pIpc->msg_id, &msg, strlen(msg.str) + 1, IPC_NOWAIT);
      }
  if (pIpc->ennemy == false)
    return (false);
  return (true);
}

void ia(t_ipc *pIpc)
{
  if (pIpc->alive == 1)
    {
      if ((checkAround(pIpc, pIpc->position % MAP_X, pIpc->position / MAP_Y)) >=
	  2)
	{
	  pIpc->alive = 0;
	  pIpc->map[pIpc->position] = 0;
	} else
	if (communication(pIpc, 0) == true)
	  move(pIpc);
	else
	  moveRandom(pIpc);
    }
}

