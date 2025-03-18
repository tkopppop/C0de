// MySQL DATABASE INFO ( Edit me ) 
#define DB_HOST "127.0.0.1"		// Host Name
#define DB_USER "root"			// Username
#define DB_PASS "superdb"			// Password
#define DB_NAME "syswatch"		// SYSWATCH DATABASE NAME

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<linux/ioctl.h>
#include<string.h>
#include<mysql.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<fcntl.h>


#define DRIVER_DEC_COUNT		0
#define DRIVER_INC_COUNT		1
#define DRIVER_FUNC_CONT		2
#define DRIVER_SET_NSG			3
#define DRIVER_GET_FUNC			4
#define DRIVER_GET_OPT			5
#define DRIVER_GET_LOG_HIT	    	6

#define	SYMLINK_DISABLE 	 210
#define	SYMLINK_ENABLE		 211
#define	PTRACE_DISABLE		 220
#define	PTRACE_ENABLE		 221
#define	EXECVE_DISABLE		 230
#define	EXECVE_ENABLE		 231
#define	CHROOT_DISABLE		 240
#define	CHROOT_ENABLE		 241
#define	SOCKETCALL_DISABLE	 250
#define	SOCKETCALL_ENABLE	 251

#define	NO_ACT		0
#define	KILL		9
#define	SEGV		11
#define	DENY_LISTEN	13

#define	MOD_SYMLINK	0
#define	MOD_PTRACE	1
#define	MOD_EXECVE	2
#define	MOD_CHROOT	3
#define	MOD_SOCKETCALL	4


#include<stdio.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<fcntl.h>
#include<linux/types.h>

struct log_format{
       __u8    log_symlink:1,
 	       log_ptrace:1,
               log_execve:1,
	       log_chroot:1,
	       log_socketcall:1,
	       res1:1,
	       res2:1,
	       res3:1;

unsigned long uid, gid, euid, egid, pid, action;
char MAGIC[4];
};

struct log_format *clog;


#define MAXFUNC 5
#define MAXOPT 2
unsigned long option[MAXOPT]={0,3333};
unsigned long func[MAXFUNC]={0,0,0,0,0};
unsigned long flag[2]={0,0};

#define MAX_THREAD	1	
void *my_thread(void *tid);

MYSQL   *connection=NULL, conn;

// Log Table Create Schema 
//
// CREATE TABLE syswatch_log(
// id int(10) not null auto_increment primary key,
// time char(26),
// type int(1) not null,
// username char(25),
// uid int(5),
// gid int(5),
// euid int(5),
// egid int(5),
// pid int(5),
// action int(5),
// );

int db_printf(int type, unsigned long uid, unsigned long gid, unsigned long euid, unsigned long egid, unsigned long pid, unsigned long action){
MYSQL_RES	*sql_result;
MYSQL_ROW	sql_row;

struct passwd *pw;
struct tm *t;
time_t timeval;
int query_stat;
char query[255];
char *stime;

	pw = getpwuid(uid);

	time(&timeval);
	t = localtime(&timeval);
	stime = asctime(t);
	stime[24] = '\0';
	
	sprintf(query, "insert into syswatch_log (time, type, username, uid, gid, euid, egid, pid, action) values "
		       "('%s','%d', '%s', '%d', '%d', '%d', '%d', '%d', '%d')", 
	       	       stime, type, pw->pw_name, uid, gid, euid, egid, pid, action);
	
	query_stat = mysql_query(connection, query);


	if(query_stat != 0){
			fprintf(stderr, "MYSQL Äõ¸® ½ÇÆÐ : %s", mysql_error(&conn));
				return -7;
	}

}

int setup(unsigned int cmd, unsigned long arg){
int fd;

fd = open("/dev/logwatch", O_RDWR);
ioctl(fd, cmd, arg);
close(fd);

}

info(){
int i;
char mark[5][25]={"Mod.RaceConditon",
                  "Mod.Ptrace",
                  "Mod.Rootshell",
                  "Mod.Chrootbreak",
                  "Mod.SocketListen"
};
char mark1[2][25]={"Module Use Count",
                   "Non-SERVER-GROUP"
};

printf("\n-------------------------------------\n");
printf("|    SYS-WATCH SECURITY MODULE     ||\n");
printf("-------------------------------------\n");
for(i=0;i<MAXFUNC;i++){
printf(" %5s = %ld\n", mark[i], func[i]);
}
printf("-------------------------------------\n");
for(i=0;i<MAXOPT;i++){
printf(" %5s = %ld\n", mark1[i], option[i]);
}
printf("-------------------------------------\n");
}


int main(int argc, char *argv[]){
FILE *fd;
pthread_t thread[MAX_THREAD];
pthread_attr_t attr;
int ret, i, stat;

mysql_init(&conn);
connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

if(connection == NULL){ 
	fprintf(stderr, "Mysql Connection Error : %s\n", mysql_error(&conn));
    return -2;
}

if(argc<3){
	fprintf(stderr, "Useage : ./u <symlink/ptrace/execve/chroot/listen> <NSG GID>\n");
	return(-1);
}

		if(strstr(argv[1], "symlink")!=0) setup(DRIVER_FUNC_CONT, SYMLINK_ENABLE);
		else setup(DRIVER_FUNC_CONT, SYMLINK_DISABLE);
		if(strstr(argv[1], "ptrace")!=0) setup(DRIVER_FUNC_CONT, PTRACE_ENABLE);
		else setup(DRIVER_FUNC_CONT, PTRACE_DISABLE);
		if(strstr(argv[1], "execve")!=0) setup(DRIVER_FUNC_CONT, EXECVE_ENABLE);
		else setup(DRIVER_FUNC_CONT, EXECVE_DISABLE);
		if(strstr(argv[1], "chroot")!=0) setup(DRIVER_FUNC_CONT, CHROOT_ENABLE);
		else setup(DRIVER_FUNC_CONT, CHROOT_DISABLE);
		if(strstr(argv[1], "listen")!=0) setup(DRIVER_FUNC_CONT, SOCKETCALL_ENABLE);
		else setup(DRIVER_FUNC_CONT, SOCKETCALL_DISABLE);
		setup(DRIVER_SET_NSG, atoi(argv[2]));

setup(DRIVER_GET_OPT, option);
setup(DRIVER_GET_FUNC, func);

info();	

pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

for(i=0;i<MAX_THREAD;i++){
	printf("Log Daemon ( %d ) Started.\n", i+1);
	ret = pthread_create(&thread[i], &attr, my_thread, NULL);
}

pthread_attr_destroy(&attr);

for(i=0;i<MAX_THREAD;i++){
	pthread_join(thread[i], (void **)&stat);
	if(!stat) printf("Log Daemon ( %d ) Halted.\n", i);
}

pthread_exit(NULL);
mysql_close(&conn);

}

void *my_thread(void *tid){
int i, fd, type;

	clog = malloc(sizeof(struct log_format));

	fd = open("/dev/logwatch", O_RDWR);
	
	if(fd < 0){
		printf("Device open error .\n");
		return -1;
	}

while(1){
	
	ioctl(fd, DRIVER_GET_LOG_HIT, flag);

	if(flag[0] == 1){
	 read(fd, clog, sizeof(struct log_format));
	 
	 if(clog->log_symlink!=0) type=MOD_SYMLINK;
	 else if(clog->log_ptrace!=0) type=MOD_PTRACE;
     else if(clog->log_execve!=0) type=MOD_EXECVE;
     else if(clog->log_chroot!=0) type=MOD_CHROOT;
     else if(clog->log_socketcall!=0) type=MOD_SOCKETCALL;

	 db_printf(type, clog->uid, clog->gid, clog->euid, clog->egid, clog->pid, clog->action);
	}
}
	close(fd);	
	
	pthread_exit((void *)tid);
}
