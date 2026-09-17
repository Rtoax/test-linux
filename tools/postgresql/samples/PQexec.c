#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

#define CHECK_RESULT(conn, res) \
	if (PQresultStatus(res) != PGRES_COMMAND_OK) { \
		do_exit(conn, res); \
	}

void do_exit(PGconn *conn, PGresult *res)
{
	fprintf(stderr, "exit: %s\n", PQerrorMessage(conn));
	PQclear(res);
	PQfinish(conn);
	exit(1);
}

int main(void)
{
	PGconn *conn = PQconnectdb("user=rongtao dbname=testdb");

	if (PQstatus(conn) == CONNECTION_BAD) {
		fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}

	/**
	 * drop table
	 */
	PGresult *res = PQexec(conn, "drop table if exists Cars");
	CHECK_RESULT(conn, res);
	PQclear(res);

	/**
	 * create table
	 */
	res = PQexec(conn, "create table Cars("\
						"Id integer primary key,"\
						"Name varchar(20),"\
						"Price integer);");
	CHECK_RESULT(conn, res);
	PQclear(res);

	/**
	 * insert into table
	 */
	res = PQexec(conn, "insert into Cars "\
				"values"\
				"(1, 'Audi', 52642),"\
				"(2, 'Mercedes', 57127),"\
				"(3, 'Skoda', 9000),"\
				"(4, 'Volvo', 29000),"\
				"(5, 'Bentley', 350000),"\
				"(6, 'Citroen', 21000),"\
				"(7, 'Hummer', 41400),"\
				"(8, 'Volkswagen', 21600)");
	CHECK_RESULT(conn, res);
	PQclear(res);

	PQfinish(conn);

	return 0;
}
