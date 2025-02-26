#include<iostream>
#include<mpi.h>
using namespace std;
int main(){
	MPI_Init(NULL, NULL);
	
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int data;
	if(world_rank == 0){
		data = 10;
		cout<<"Process 0 is broadcasting the message!"<<endl;
	}
	
	MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);
	
	if(world_rank != 0){	
		cout<<"Process "<<world_rank<<" is receiving "<<data<<" from Process 0!"<<endl;
	}

	MPI_Finalize();
	return 0;
}
