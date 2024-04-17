#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

void do_exit(PGconn *conn)
{
	PQfinish(conn);
	exit(1);
}

int main(void)
{
	PGconn *conn = PQconnectdb("user=rongtao dbname=testdb");

	if (PQstatus(conn) == CONNECTION_BAD) {
		fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
		do_exit(conn);
	}

	int ver = PQserverVersion(conn);
	printf("Server version: %d\n", ver);

	char *user = PQuser(conn);
	char *dbname = PQdb(conn);
	char *pswd = PQpass(conn);

	printf("User: %s\n", user);
	printf("Database name: %s\n", dbname);
	printf("Password: %s\n", pswd);

	PQfinish(conn);

	return 0;
}
