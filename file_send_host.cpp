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
	vector<char> buffer(MAX_FILE_SIZE); // Buffer to store the data
	if(world_rank == 0){
		ifstream r_file("whatsapp.webp.gz", ios::binary);
		if(!r_file){
			cout<<"Error: Could not open file on process 0!"<<endl;
			MPI_Abort(MPI_COMM_WORLD,1);		
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
		
	MPI_Finalize();
	return 0;
}
