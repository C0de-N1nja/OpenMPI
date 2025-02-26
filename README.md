# OpenMPI

# Command to make MPI files executable
mpic++ program_name -o program_name


# Command to execute the MPI program
mpirun -np 1 --hostfile hostfile.txt program_name : -np 1 program_name
