#include<iostream>
#include<mpi.h>
#include<fstream>
#include<vector>
using namespace std;
int main(){
	MPI_Init(NULL, NULL);
	
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int file_size = 0;
	const int MAX_FILE_SIZE = 6000; // Max file size in bytes
	vector<char> buffer(MAX_FILE_SIZE); // Buffer to hold file data
	
	if(world_rank == 1){
		MPI_Recv(&file_size,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);		
		if(file_size <= 0){
			cout<<"Invalid file size!"<<endl;
			MPI_Abort(MPI_COMM_WORLD, 1);
		}

		cout<<"Process 1 received file size of "<<file_size<<" bytes from Process 0!"<<endl;
		
		//vector<char> buffer(file_size); // Buffer to hold file data		

		MPI_Recv(buffer.data(),file_size,MPI_CHAR,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		ofstream w_file("whatsapp_received.webp",ios::binary);
		if (!w_file){
		    cout<<"Error: Could not create output file on process 1!"<<endl;
		    MPI_Abort(MPI_COMM_WORLD, 1);
        	}
		w_file.write(buffer.data(), file_size); // Write the buffer to the file
		w_file.close();

        	cout<<"Process 1 received file of size "<<file_size<<" bytes and saved it as 'whatsapp_received.webp'."<<endl;
	}
		
	MPI_Finalize();
	return 0;
}
