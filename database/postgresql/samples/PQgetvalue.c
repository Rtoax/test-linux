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

	PGresult *res = PQexec(conn, "select version()");
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		printf("No data retrieved.\n");
		PQclear(res);
		exit(1);
	}

	printf("%s\n", PQgetvalue(res, 0, 0));

	PQclear(res);
	PQfinish(conn);

	return 0;
}
