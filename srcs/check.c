/*
** check.c for check.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun Apr  2 22:39:31 2017 Nicolas
** Last update Sun Apr  2 22:45:38 2017 Nicolas
*/

#include <stdio.h>
#include "../includes/lemipc.h"

int get_team(t_ipc *ipc, int x, int y)
{
  int tmp;

  if (y < 0 || x < 0 || y > 9)
    return (FALSE);
  tmp = ipc->map[(y * MAP_X) + x];
  if (tmp == 0)
    return (FALSE);
  return (tmp);
}

bool check_ennemy(t_ipc *pIpc)
{
  int i;
  int y;
  int tmp;

  i = 0;
  while (i < 100)
    {
      y = 0;
      while (y < 10)
	{
	  tmp = pIpc->map[y + i];
	  if (tmp != 0 && tmp != pIpc->id)
	    {
	      pIpc->ennemy = y + i;
	      pIpc->win = 0;
	      return (true);
	    }
	  y += 1;
	}
      i += 10;
    }
  pIpc->win += 1;
  return (false);
}

int checkAround(t_ipc *pIpc, int x, int y)
{
  int enemy;
  int team_around;

  enemy = 0;
  team_around = 0;
  if ((team_around = get_team(pIpc, x, y - 1)) != FALSE &&
      team_around != pIpc->id)
    enemy += 1;
  if ((team_around = get_team(pIpc, x, y + 1)) != FALSE &&
      team_around != pIpc->id)
    enemy += 1;
  if ((team_around = get_team(pIpc, x + 1, y)) != FALSE &&
      team_around != pIpc->id)
    enemy += 1;
  if ((team_around = get_team(pIpc, x - 1, y)) != FALSE &&
      team_around != pIpc->id)
    enemy += 1;
  return (enemy);
}

