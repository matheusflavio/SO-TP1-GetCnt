#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

extern int sys_cnt[22];

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "usage: getcnt pid...\n");
    exit(1);
  }

  int sys_ID = atoi(argv[1]);
  int id_cnt = getcnt(sys_ID);

  fprintf(2, "syscall %s has been called %d times\n", argv[1], id_cnt);

  exit(0);
}
