#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

extern int sys_cnt[22];

uint64
sys_exit(void)
{
  int n;

  sys_cnt[1]++;

  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  sys_cnt[10]++;
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  sys_cnt[0]++;
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;

  sys_cnt[2]++;

  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  sys_cnt[11]++;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  sys_cnt[12]++;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  sys_cnt[5]++;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;
  
  sys_cnt[13]++;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
