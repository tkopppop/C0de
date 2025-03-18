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

int main()
{
int query_stat;
char query[255];

	printf("SYSWATCH-Log Table Creating\n");
	mysql_init(&conn);
        connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if(connection == NULL){ 
		fprintf(stderr, "Mysql Connection Error : %s\n", mysql_error(&conn));
                return -2;
	}

sprintf(query, "CREATE TABLE syswatch_log ( id int(10) not null auto_increment primary key, time char(26), type int(1) not null, username char(25), uid int(5), gid int(5), euid int(5), egid int(5), pid int(5), action int(5))");

	query_stat = mysql_query(connection, query);

	if(query_stat != 0){
		fprintf(stderr, "SYSWATCH-Log Table Creating Error : %s", mysql_error(&conn));
		return -7;
	}

	printf("SYSWATCH-Log Table Created.\n");
	return 0;
}
