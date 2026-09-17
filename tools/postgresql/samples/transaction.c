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

	if (PQstatus(conn) == CONNECTION_BAD){
		fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
		do_exit(conn);
	}

#define check_result(res, conn, lines)\
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {\
		fprintf(stderr, "%s.\n", lines);\
		PQclear(res);\
		do_exit(conn);\
	}

	PGresult *res = PQexec(conn, "BEGIN");
	check_result(res, conn, "BEGIN failed.");
	PQclear(res);

	res = PQexec(conn, "update cars set Price=23700 where Id=8");
	check_result(res, conn, "update failed.");

	res = PQexec(conn, "insert into cars values(9, 'Mazda', 27770)");
	check_result(res, conn, "insert failed.");

	res = PQexec(conn, "commit");
	check_result(res, conn, "commit failed.");

	PQclear(res);
	PQfinish(conn);

	return 0;
}
