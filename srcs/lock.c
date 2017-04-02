/*
** lock.c for lock.c in /home/nicolas/rendu/PSU_2016_lemipc/srcs
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun Apr  2 22:39:55 2017 Nicolas
** Last update Sun Apr  2 23:39:11 2017 Boris ROUGAGNOU
*/

#include <sys/sem.h>

void	lock(int sem_id)
{
  struct sembuf	op;

  op.sem_flg = 0;
  op.sem_num = 0;
  op.sem_op = -1;
  semop(sem_id, &op, 1);
}

void	unlock(int sem_id)
{
  struct sembuf	op;

  op.sem_flg = 0;
  op.sem_num = 0;
  op.sem_op = 1;
  semop(sem_id, &op, 1);
}

