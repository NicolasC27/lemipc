//
// Created by nicolas on 27/03/17.
//

#ifndef PSU_2016_LEMIPC_LEMIPC_H
#define PSU_2016_LEMIPC_LEMIPC_H

#define RETURN_ERROR		84
#define SIZE_SHM                100
#define MAP_X			10
#define MAP_Y			10

typedef struct s_ipc
{
  int player;
  int pos;
  int id;
  bool first;
  char *path_key;
  key_t key;
  int shm_id;
  int sem_id;
  char *map;
  int position;
  int msg_id;
  int alive;
} t_ipc;

typedef struct s_msg
{
  long mtype;
  char str[10];
} t_msg;


#endif //PSU_2016_LEMIPC_LEMIPC_H
