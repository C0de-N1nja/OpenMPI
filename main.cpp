#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring> // For strcmp
#include <mpi.h>

// --- Function for File Transfer ---
void perform_file_transfer(int world_rank)
{
    if (world_rank == 0)
    { // Sender Logic
        int file_size = 0;
        const int MAX_FILE_SIZE = 6000;
        std::vector<char> buffer(MAX_FILE_SIZE);

        std::ifstream r_file("whatsapp.webp.gz", std::ios::binary);
        if (!r_file)
        {
            std::cerr << "Error: Could not open file on process 0!" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        r_file.seekg(0, std::ios::end);
        file_size = r_file.tellg();
        r_file.seekg(0, std::ios::beg);
        r_file.read(buffer.data(), file_size);
        r_file.close();

        MPI_Send(&file_size, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        std::cout << "Process 0 sent file size of " << file_size << " bytes to Process 1!" << std::endl;
        MPI_Send(buffer.data(), file_size, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        std::cout << "Process 0 sent file of size " << file_size << " bytes to Process 1." << std::endl;
    }
    else if (world_rank == 1)
    { // Receiver Logic
        int file_size = 0;
        const int MAX_FILE_SIZE = 6000;
        std::vector<char> buffer(MAX_FILE_SIZE);

        MPI_Recv(&file_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (file_size <= 0)
        {
            std::cerr << "Invalid file size received!" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        std::cout << "Process 1 received file size of " << file_size << " bytes from Process 0!" << std::endl;

        MPI_Recv(buffer.data(), file_size, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::ofstream w_file("whatsapp_received.webp", std::ios::binary);
        if (!w_file)
        {
            std::cerr << "Error: Could not create output file on process 1!" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        w_file.write(buffer.data(), file_size);
        w_file.close();
        std::cout << "Process 1 received file and saved it as 'whatsapp_received.webp'." << std::endl;
    }
}

// --- Function for Broadcast Demo ---
void demonstrate_broadcast(int world_rank)
{
    int data;
    if (world_rank == 0)
    {
        data = 10;
        std::cout << "Process 0 is broadcasting the value: " << data << std::endl;
    }

    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank != 0)
    {
        std::cout << "Process " << world_rank << " received broadcasted data: " << data << std::endl;
    }
}

// --- Function for Array Sending Demo ---
void demonstrate_array_send(int world_rank)
{
    if (world_rank == 0)
    {
        int arr[5] = {1, 2, 3, 4, 5};
        std::cout << "Sender: Getting ready for sending the data..." << std::endl;
        MPI_Send(arr, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
        std::cout << "Sender: The array is sent successfully!" << std::endl;
    }
    else if (world_rank == 1)
    {
        int brr[5] = {0};
        std::cout << "Receiver: Waiting to receive the data..." << std::endl;
        MPI_Recv(brr, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Receiver: The array is received successfully!" << std::endl;
        std::cout << "The contents of array are: ";
        for (int i = 0; i < 5; i++)
        {
            std::cout << brr[i] << " ";
        }
        std::cout << std::endl;
    }
}

// --- Main Application Router ---
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::string mode = "";
    for (int i = 1; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "--mode") == 0 && i + 1 < argc)
        {
            mode = argv[i + 1];
            break;
        }
    }

    if (mode == "file_transfer")
    {
        perform_file_transfer(world_rank);
    }
    else if (mode == "broadcast")
    {
        demonstrate_broadcast(world_rank);
    }
    else if (mode == "array_send")
    {
        demonstrate_array_send(world_rank);
    }
    else
    {
        if (world_rank == 0)
        {
            std::cerr << "Error: Invalid or no mode specified." << std::endl;
            std::cerr << "Usage: mpirun -np <num_procs> ./app --mode <mode_name>" << std::endl;
            std::cerr << "Available modes: file_transfer, broadcast, array_send" << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}