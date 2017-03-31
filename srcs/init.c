/*
** init.c for lemipc in /home/rougag_b/rendu/PSU_2016_lemipc
** 
** Made by Boris ROUGAGNOU
** Login   <rougag_b@epitech.net>
** 
** Started on  Fri Mar 31 15:47:31 2017 Boris ROUGAGNOU
** Last update Fri Mar 31 18:40:50 2017 Boris ROUGAGNOU
*/

#include "lemipc.h"

/* inititialisation du tmp de create_map */
t_ipc		*init_tmp(t_ipc *tmp, char *path_key, char *nb_team)
{
  if ((tmp = malloc(sizeof(t_ipc))) == NULL)
    return (NULL);
  tmp->pos = 0;
  tmp->id = atoi(nb_team);
  tmp->path_key = strdup(path_key);
  tmp->key = ftok(getenv(path_key), 0);
  tmp->shm_id = shmget(tmp->key, SIZE_SHM, SHM_W | SHM_R);
  return (tmp);
}

/* SI tmp->shm_id PAS -1 */
t_ipc		*init_tmp_shm(t_ipc *tmp, char *path_key, char *nb_team)
{
  tmp->first = false;
  printf("Using");
  tmp->player += 1;
  tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
  tmp->sem_id = semget(tmp->key, 1, SHM_R | SHM_W);
  // semctl(tmp->sem_id, 0, IPC_RMID);
  tmp->msg_id = msgget(tmp->key, SHM_R | SHM_W);
  printf("\nUsing msgq %d\n", tmp->msg_id);
  tmp->map = shmat(tmp->shm_id, NULL, SHM_R | SHM_W);
  // tmp->sem_id = semget(tmp->key, 1, IPC_CREAT| SHM_R | SHM_W);
  return (tmp);
}

/* SI tmp->shm_id == -1 */
t_ipc		*init_tmp_noshm(t_ipc *tmp, char *path_key, char *nb_team)
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
  return (tmp);
}

t_ipc		*create_map(char *path_key, char *nb_team)
{
  t_ipc		*tmp;

  tmp = init_tmp(tmp, path_key, nb_team);
  if (tmp->shm_id == -1)
    tmp = init_tmp_noshm(tmp, path_key, nb_team);
  else
    tmp = init_tmp_shm(tmp, path_key, nb_team);
  tmp->position = rand() % SIZE_SHM;
  while (tmp->map[tmp->position] != 0)
    tmp->position = rand() % SIZE_SHM;
  tmp->map[tmp->position] = tmp->id;
  return (tmp);
}
