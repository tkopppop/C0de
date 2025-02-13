#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "superdb"
#define DB_NAME "syswatch"

#include<stdio.h>
#include<unistd.h>
#include<mysql.h>
#include<string.h>
#include<time.h>
#include<pwd.h>

MYSQL   *connection=NULL, conn;
MYSQL_RES	*sql_result;
MYSQL_ROW	sql_row;

int main()
{
int query_stat, msgid=0, typeid=0;
char query[255];

char msg[4][8]={"NULL", "KILL", "SEGV", "NSG"};
char type[5][10]={"symlink()", "ptrace()", "execve()", "chroot()", "listen()"};
									
	printf("SYSWATCH-Log View\n\n");
	mysql_init(&conn);

    connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	
	if(connection == NULL){ 
		fprintf(stderr, "Mysql Connection Error : %s\n", mysql_error(&conn));
                return -2;
	}

sprintf(query, "SELECT*FROM syswatch_log");

	query_stat = mysql_query(connection, query);

	if(query_stat != 0){
		fprintf(stderr, "SYSWATCH-Log Viewing Error : %s", mysql_error(&conn));
		return -7;
	}
	
	sql_result = mysql_store_result(connection);
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("   ID |    Type    |      Event Timeline      |  User |  UID  |  GID  |  EUID |  EGID |  PID  |  ACT \n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	while((sql_row = mysql_fetch_row(sql_result)) != NULL){
		if(strstr(sql_row[9], "0")) msgid = 0;
		else if(strstr(sql_row[9], "9")) msgid=1;
		else if(strstr(sql_row[9], "11")) msgid=2;
		else msgid=3;
		
		if(strstr(sql_row[2], "0")) typeid=0;
		else if(strstr(sql_row[2], "1")) typeid=1;
		else if(strstr(sql_row[2], "2")) typeid=2;
		else if(strstr(sql_row[2], "3")) typeid=3;
		else typeid=4;
		
		printf("%5s | %10s | %5s | %5s | %5s | %5s | %5s | %5s | %5s | %5s\n", sql_row[0], type[typeid], sql_row[1], sql_row[3], sql_row[4], sql_row[5], sql_row[6], sql_row[7], sql_row[8], msg[msgid]);
	}
	printf("-----------------------------------------------------------------------------------------------------\n");

	mysql_free_result(sql_result);
	mysql_close(&conn);
	printf("SYSWATCH-Log Viewing Finish.\n");
	return 0;
}
