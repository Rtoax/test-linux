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

	PGresult *res = PQexec(conn, "select * from Cars");
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr, "No data retrieved.\n");
		PQclear(res);
		do_exit(conn);
	}

	int ncols = PQnfields(res);

	printf("There are %d columns,\n", ncols);
	printf("The columns names are:\n");

	int i;
	for (i = 0; i < ncols; i++) {
		char *name = PQfname(res, i);
		printf("%s\n", name);
	}

	PQclear(res);
	PQfinish(conn);

	return 0;
}
