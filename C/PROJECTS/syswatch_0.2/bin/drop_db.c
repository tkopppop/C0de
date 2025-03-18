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

	printf("SYSWATCH-Clear Log Table..\n");
	mysql_init(&conn);
        connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if(connection == NULL){ 
		fprintf(stderr, "Mysql Connection Error: %s\n", mysql_error(&conn));
                return -2;
	}

	sprintf(query, "DROP TABLE syswatch_log");

	query_stat = mysql_query(connection, query);

	if(query_stat != 0){
		fprintf(stderr, "SYSWATCH-Clear Log Error : %s", mysql_error(&conn));
		return -7;
	}

	printf("SYSWATCH-Log Clear Finish!\n");
	mysql_close(&conn);
	sleep(5);
	printf("SYSWATCH-Log Table re-build!!\n");
	system("./make_db");
	sleep(5);
	printf("SYSWATCH-Restart Logmon!!\n");
	system("./start");

}
