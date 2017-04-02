/*
** choose.c for choose.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun Apr  2 22:39:35 2017 Nicolas
** Last update Sun Apr  2 22:39:40 2017 Nicolas
*/

#include <stdlib.h>
#include <stdio.h>
#include "../includes/lemipc.h"

void chooseDirection(t_ipc *pIpc)
{
  int x;
  int y;
  int nb;

  x = (pIpc->ennemy % MAP_X) - (pIpc->position % MAP_X);
  y = (pIpc->ennemy / MAP_X) - (pIpc->position / MAP_Y);
  nb = rand() % 2;
  if (nb == 1)
    {
      if (y != 0 && y < 0)
	pIpc->move = UP;
      else
	if (y != 0 && y > 0)
	  pIpc->move = DOWN;
    }
  if (nb == 0)
    {
      if (x != 0 && x < 0)
	pIpc->move = LEFT;
      else
	if (x != 0 && x > 0)
	  pIpc->move = RIGHT;
    }
}

