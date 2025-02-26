#include<iostream>
#include<mpi.h>
using namespace std;
int main(){
	MPI_Init(NULL, NULL);
	
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if(world_rank == 0){
		int data = 10;
		cout<<"Sender: Sending the value "<<data<<" to the other machine..."<<endl;
		MPI_Send(&data,1,MPI_INT,1,0,MPI_COMM_WORLD);
		cout<<"Sender: Data is sent to the other machine!"<<endl;
	}
	
	MPI_Finalize();
	return 0;
}
