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
	const int MAX_FILE_SIZE = 1024; // Max file size in bytes
	vector<char> buffer(MAX_FILE_SIZE); // Buffer to hold file data

	if(world_rank == 0){
		ifstream r_file("input.txt", ios::binary);
		if(!r_file){
			cout<<"Error: Could not open file on process 0!"<<endl;
		}
		r_file.seekg(0,ios::end); // Moves the pointer to the end
		file_size = r_file.tellg(); // Tells the size of file
		r_file.seekg(0,ios::beg); // Reset the pointer to the starting
		r_file.read(buffer.data(), file_size); // Read the file into buffer		
		r_file.close();
		

		// Send the file size to process 1
		MPI_Send(&file_size,1,MPI_INT,1,0,MPI_COMM_WORLD);
		cout<<"Process 0 sents file size of "<<file_size<<" bytes to Process 1!"<<endl;
		// Send the file contents to process 1
		MPI_Send(buffer.data(),file_size,MPI_CHAR,1,1,MPI_COMM_WORLD);
		cout<<"Process 0 sent file of size "<<file_size<<" bytes to Process 1."<<endl;
	}
	else if(world_rank == 1){
		MPI_Recv(&file_size,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);		
		cout<<"Process 1 received file size of "<<file_size<<" bytes from Process 0!"<<endl;
		MPI_Recv(buffer.data(),file_size,MPI_CHAR,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		ofstream w_file("output.txt",ios::binary);
		if (!w_file){
		    cout<<"Error: Could not create output file on process 1!"<<endl;
		    MPI_Abort(MPI_COMM_WORLD, 1);
        	}
		w_file.write(buffer.data(), file_size); // Write the buffer to the file
		w_file.close();

        	cout<<"Process 1 received file of size "<<file_size<<" bytes and saved it as 'output.txt'."<<endl;
	}
		
	MPI_Finalize();
	return 0;
}
