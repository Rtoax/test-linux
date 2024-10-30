#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int main(int argc,char *argv[])
{
	int myid, numprocs;
	int err = 0;
	double starttime, endtime, tick;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	starttime = MPI_Wtime();
	sleep(1);
	endtime = MPI_Wtime();

	fprintf(stderr,"That took %f seconds\n", endtime-starttime);

	tick = MPI_Wtick();
	if (tick > 1.0 || tick < 0.0) {
		err++;
		fprintf(stderr, "MPI_Wtick gave a strange result: (%f)\n", tick);
	}

	MPI_Finalize();
}
