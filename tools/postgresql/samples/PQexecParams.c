#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

#define LEN	20

void do_exit(PGconn *conn)
{
	PQfinish(conn);
	exit(1);
}

int main(int argc, char *argv[])
{
	const char *paramValues[1];

	if (argc != 2) {
		fprintf(stderr, "usage: %s <row id>\n", argv[0]);
		exit(1);
	}

	int rowId = atoi(argv[1]);
	if (rowId <0) {
		fprintf(stderr, "rowId out of range. %d\n", rowId);
		exit(1);
	}

	char str[LEN];
	snprintf(str, LEN, "%d", rowId);

	paramValues[0] = str;

	PGconn *conn = PQconnectdb("user=rongtao dbname=testdb");

	if (PQstatus(conn) == CONNECTION_BAD) {
		fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
		do_exit(conn);
	}

	char *stm = "select * from Cars where Id=$1";

	PGresult *res = PQexecParams(conn, stm, 1, NULL, paramValues, NULL, NULL, 0);
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		printf("No data retrieved.\n");
		PQclear(res);
		do_exit(conn);
	}

	printf("%8s | %8s | %8s\n",
			PQgetvalue(res, 0, 0),
			PQgetvalue(res, 0, 1),
			PQgetvalue(res, 0, 2)
			);

	PQfinish(conn);

	return 0;
}
