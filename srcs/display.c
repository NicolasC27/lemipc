/*
** display.c for display.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun Apr  2 22:38:56 2017 Nicolas
** Last update Sun Apr  2 22:38:56 2017 Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include "../includes/lemipc.h"

void display_game(t_ipc *pIpc)
{
  int i;
  int y;

  i = 0;
  system("clear");
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
