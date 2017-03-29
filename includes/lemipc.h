//
// Created by nicolas on 27/03/17.
//

#ifndef PSU_2016_LEMIPC_LEMIPC_H
#define PSU_2016_LEMIPC_LEMIPC_H

#define RETURN_ERROR        84
#define SIZE_SHM	    42
typedef struct s_ipc
{
  int pos;
  int id;
  char *path_key;
  key_t key;
  int shm_id;
  int sem_id;
  char *map;
  int position;
} t_ipc;


#endif //PSU_2016_LEMIPC_LEMIPC_H
