#include<iostream>
#include<mpi.h>
using namespace std;
int main(){
	MPI_Init(NULL, NULL);
	
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	if(world_rank == 0){
		int arr[5] = {1,2,3,4,5};
		cout<<"Sender: Getting ready for sending the data..."<<endl;
		MPI_Send(arr,5,MPI_INT,1,0,MPI_COMM_WORLD);
		cout<<"Sender: The array is sent successfully!"<<endl;
	}
	else if(world_rank == 1){
		int brr[5] = {0};
		cout<<"Receiver: Waiting to receive the data..."<<endl;
		MPI_Recv(brr,5,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout<<"Receiver: The array is received successfully!"<<endl;
		cout<<"The contents of array are:"<<endl;
		for(int i=0;i<5;i++){
			cout<<brr[i]<<" ";
		}
		cout<<endl;
	}
	
	MPI_Finalize();
	return 0;
}
