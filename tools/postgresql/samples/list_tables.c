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

	/**
	 * select table_name from information_schema.tables where table_schema='public';
	 */
	char *query = "select table_name from information_schema.tables";
	PGresult *res = PQexec(conn, query);
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		printf("No data retrieved.\n");
		PQclear(res);
		exit(1);
	}

	/**
	 * PQntuples: returns the number of rows in the query result
	 */
	int i, rows = PQntuples(res);

	for (i = 0; i < rows; i++) {
		printf("%8s\n", PQgetvalue(res, i, 0));
	}

	PQclear(res);
	PQfinish(conn);

	return 0;
}
