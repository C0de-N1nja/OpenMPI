#include<iostream>
#include<mpi.h>
using namespace std;
int main(){
	MPI_Init(NULL, NULL);
	
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if(world_rank == 1){
		int data;
		cout<<"Receiver: Waiting for receiving the messages....."<<endl;
		MPI_Recv(&data,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout<<"Receiver: The value "<<data<<" is received from the sender!"<<endl;
	}
	
	MPI_Finalize();
	return 0;
}
