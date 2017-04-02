/*
** move.c for move.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun Apr  2 22:39:24 2017 Nicolas
** Last update Sun Apr  2 22:40:27 2017 Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include "../includes/lemipc.h"

int movePlayer(t_ipc *pIpc, int position, int new_position, int id)
{
  if (new_position < 0 || new_position == 0 ||
      ((new_position % MAP_X) == 9 && (position % MAP_X) == 0) ||
      ((new_position % MAP_X) == 0 && (position % MAP_X) == 9) ||
      new_position >= 100)
    return (0);
  if (pIpc->map[new_position] == 0)
    {
      pIpc->map[position] = 0;
      pIpc->map[new_position] = id;
      pIpc->position = new_position;
      return (1);
    }
  return (0);
}

int moveCalculDirection(int position, t_direction direction)
{
  if (direction == UP)
    return position - 10;
  else
    if (direction == DOWN)
      return position + 10;
    else
      if (direction == LEFT)
	return position - 1;
      else
	if (direction == RIGHT)
	  return position + 1;
  return (0);
}

void moveRandom(t_ipc *pIpc)
{
  int pos;

  pos = pIpc->position;
  while (pos == pIpc->position)
    {
      pIpc->move = rand() % 4;
      movePlayer(pIpc, pIpc->position,
		 moveCalculDirection(pIpc->position, pIpc->move),
		 pIpc->id);
    }
}

void move(t_ipc *pIpc)
{
  chooseDirection(pIpc);
  if ((movePlayer(pIpc, pIpc->position,
		  moveCalculDirection(pIpc->position, pIpc->move),
		  pIpc->id)) == 0)
    moveRandom(pIpc);
}
