/*
    process_lister.C [c -> C]
    Author: programmer KJ
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/sysinfo.h>

#include "types.h"
#include "debug.h"

#define STAT_PATH        "/proc/%d/stat"
#define STATUS_PATH      "/proc/%d/status"
#define MAX_PROCS        512
#define PATH_SIZE        256


struct ProcInfo {
  s32 pid;
  s32 active;
  s32 memory;
  char name[64];
  char state;
  double cpu_usage;
  time_t start_time;
};


struct ProcInfo pi[MAX_PROCS];
s32 cntproc = 0;


/*
  clear_screen(): ansi clear screen in this term.
  calc_cpu_usage(): pid recv and check real proc usage on cpu.
  load_procs(): capture proc list from /proc/....
  print_procs(): listing
  kill_proc(): proc id killed.
  get_system_info(): total_ram, used_ram, cpu_core's counts

*/

void clear_screen()
{

  printf("\033[2J\033[1;1H");

}

double calc_cpu_usage(int pid)
{

  char path[PATH_SIZE];
  FILE* fp;
  u32 utime;
  u32 stime;
  u32 total_time;
  u32 pid_time;

  struct sysinfo si;
  sysinfo(&si);

  sprintf(path, STAT_PATH, pid);
  fp = fopen(path, "r");
  if (!fp) return 0.0;

  fscanf(fp, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu",
         &utime, &stime);
  fclose(fp);

  total_time = si.uptime;
  pid_time = utime + stime;

  return total_time ? (100.0 * pid_time / total_time) : 0.0;

}

void get_system_info(long* total_ram, long* used_ram, long* cpu_cores)
{

  struct sysinfo si;

  if (sysinfo(&si) == 0) {

    *total_ram = si.totalram / 1024;
    *used_ram = (si.totalram - si.freeram) / 1024;
    *cpu_cores = sysconf(_SC_NPROCESSORS_ONLN);

  } else {

    *total_ram = *used_ram = *cpu_cores = 0;

  }

}

void load_procs()
{

  DIR* dir;
  struct ProcInfo* proc;
  struct dirent* entry;
  char path[PATH_SIZE];
  FILE* fp;
  s32 pid;
  
  cntproc = 0;

  dir = opendir("/proc");
  if (!dir) {
    perror("Cannot open /proc");
    return;
  }

  while ((entry = readdir(dir)) != NULL && cntproc < MAX_PROCS) {

    if (entry->d_type != DT_DIR || !atoi(entry->d_name))
      continue;

      pid = atoi(entry->d_name);
      sprintf(path, STAT_PATH, pid);
        
      fp = fopen(path, "r");
      if(!fp) continue;

      proc = &pi[cntproc];
      proc->pid = pid;
        
      fscanf(fp, "%*d %63s %c", proc->name, &proc->state);
      fclose(fp);

      memmove(proc->name, proc->name + 1, strlen(proc->name));
      proc->name[strlen(proc->name) - 1] = 0;

      sprintf(path, STATUS_PATH, pid);
      fp = fopen(path, "r");

      if (fp) {
          char line[128];
          while (fgets(line, sizeof(line), fp)) {
              if (strncmp(line, "VmRSS:", 6) == 0) {
                  sscanf(line, "VmRSS: %ld kB", &proc->memory);
                  break;
              }
          }
          fclose(fp);
      }

      proc->cpu_usage = calc_cpu_usage(pid);
      proc->start_time = time(NULL);
      proc->active = 1;
      cntproc++;

  }

  closedir(dir);

}

void print_procs()
{
  time_t uptime;
  s32 i;
  
  printf("\npid\tname\t\tstate\tmemory(kb)\tcpu%%\tuptime\n");
  printf("+-----------------------------------------------+\n");
    
  for (i = 0; i < cntproc; i++) {

    if (!pi[i].active) continue;

    uptime = time(NULL) - pi[i].start_time;
    printf("%d\t%-15.15s\t%c\t%ld\t\t%.2f\t%ld\n",
            pi[i].pid, pi[i].name, pi[i].state,
            pi[i].memory, pi[i].cpu_usage, uptime);

  }

  printf("\n");

}

void kill_proc(int pid)
{

  if (kill(pid, SIGTERM) == 0) {

    printf("Process %d terminated successfully\n", pid);

    for (int i = 0; i < cntproc; i++) {
        if (pi[i].pid == pid) {
            pi[i].active = 0;
            break;
        }
    }

  } else {

    PFATAL("_Failed to kill process");

  }

}

/* Entry Point of ProcessesMonitor */

int main(int argc, char** argv)
{
  char command[32];
  s32 pid;
  s32 cpu_cores;
  s64 total_ram;
  s64 used_ram;

  while (1) {

    clear_screen();

    printf("\n=== Process List Loader ===\n");
    printf("commands: scan, list, kill <pid>, exit\n\n");

    get_system_info(&total_ram, &used_ram, &cpu_cores);

    printf("System Info:\n");
    printf("Total RAM: %ld MB\n", total_ram / 1024);
    printf("Used RAM: %ld MB\n", used_ram / 1024);
    printf("CPU Cores: %d\n\n", cpu_cores);

    printf("Enter command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;

    if (strcmp(command, "scan") == 0) {

      load_procs();
      printf("Scan complete. Use 'list' to view processes.\n");

    } else if (strcmp(command, "list") == 0) {

      print_procs();

    } else if (strcmp(command, "kill") == 0) {

      pid = atoi(command + 5);
      kill_proc(pid);

    } else if (strcmp(command, "exit") == 0) {

      printf("_Exiting...\n");
      break;

    } else {

      printf("_invalid command!\n");

    }

    sleep(1);

  }

  return 1;

}

