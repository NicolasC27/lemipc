/*
** usage.c for lemipc in 
** 
** Made by Boris ROUGAGNOU
** Login   <rougag_b@epitech.net>
** 
** Started on  Fri Mar 31 15:50:24 2017 Boris ROUGAGNOU
** Last update Sun Apr  2 23:40:23 2017 Boris ROUGAGNOU
*/

#include <stdio.h>

int	usage()
{
  fprintf(stderr, "Usage: ./lemipc path_to_key team_number\n\n");
  fprintf(stderr, "path_to_key is a valid path that will be used by ftok\n");
  fprintf(stderr,
	  "team_number is the team number assigned to the current player\n");
  return (0);
}
