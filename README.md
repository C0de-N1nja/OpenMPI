# 🚀 Multi-Functional MPI Toolkit in C++

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus">
  <img alt="Platform" src="https://img.shields.io/badge/Platform-Linux-FCC624?style=for-the-badge&logo=linux">
  <img alt="Tech" src="https://img.shields.io/badge/Technology-OpenMPI-F78701?style=for-the-badge">
</p>

A command-line utility built in C++ that demonstrates several core concepts of the **OpenMPI** library for parallel and distributed computing. This single application can operate in different modes to showcase various message-passing techniques.

---

## ✨ Features / Modes

This application can be run in one of the following modes:

- `file_transfer`: A two-process application to send a file from one host to another over the network.
- `broadcast`: A one-to-many communication demo where a root process sends data to all other processes.
- `array_send`: A point-to-point demo for sending a simple C++ array from one process to another.

---

## 🌐 Network Architecture

This toolkit demonstrates **true distributed computing** across multiple physical machines:
- **Process 0**: Runs on Machine 1 (e.g., 192.168.100.101)
- **Process 1**: Runs on Machine 2 (e.g., 192.168.100.102)
- **Communication**: Real network communication using MPI over TCP/IP

---

## 🚀 How to Compile and Run

### 1. Prerequisites
- A Linux environment.
- `build-essential` (for the g++ compiler).
- The `OpenMPI` library (`sudo apt-get install libopenmpi-dev`).

### 2. Compile the Application
Use the MPI C++ compiler wrapper (`mpic++`) to create a single executable from the unified source file:

```bash
mpic++ main.cpp -o mpi_app
```

### 3. Multi-Machine Network Setup (Optional)
For distributed execution across multiple physical machines:

#### Prerequisites for Multi-Machine Execution:
- **Network Connectivity**: All machines must be on the same network and able to communicate
- **SSH Access**: Passwordless SSH must be configured between all machines
- **Synchronized Files**: The compiled executable must be present on all machines in the same path
- **MPI Installation**: OpenMPI must be installed on all participating machines

#### Setting up Passwordless SSH:
```bash
# Generate SSH key (if not already done)
ssh-keygen -t rsa -b 2048

# Copy public key to remote machine
ssh-copy-id username@192.168.100.102

# Test passwordless connection
ssh username@192.168.100.102
```

#### Create Hostfile:
Create a `hostfile.txt` with the IP addresses of your machines:
```
192.168.100.101 slots=1
192.168.100.102 slots=1
```
- Each line represents one machine
- `slots=1` indicates one process slot per machine
- Use actual IP addresses of your machines

---

### 4. Execute a Mode
Run the compiled application using mpirun, specifying the number of processes (-np) and the desired --mode.

#### ➤ File Transfer Mode (Requires 2 processes)
*Demonstrates actual file transfer between separate machines over the network.*
*Ensure a file named whatsapp.webp.gz exists on the sender machine.*

```bash
# For local execution (single machine, 2 processes)
mpirun -np 2 ./mpi_app --mode file_transfer

# For multi-machine execution (2 separate machines)
mpirun -np 2 --hostfile hostfile.txt ./mpi_app --mode file_transfer
```

**What happens**: Process 0 (machine 1) reads a file and sends it over the network to Process 1 (machine 2), which saves it as `whatsapp_received.webp`.

#### ➤ Broadcast Mode (Requires 2+ processes)
*Demonstrates one-to-many communication across multiple machines.*

```bash
# Local execution
mpirun -np 4 ./mpi_app --mode broadcast

# Multi-machine execution (requires 4+ machines or modify slots in hostfile)
mpirun -np 4 --hostfile hostfile.txt ./mpi_app --mode broadcast
```

**What happens**: Process 0 broadcasts a value to all other processes across the network.

#### ➤ Array Send Mode (Requires 2 processes)
*Demonstrates point-to-point array transmission between machines.*

```bash
# Local execution
mpirun -np 2 ./mpi_app --mode array_send

# Multi-machine execution
mpirun -np 2 --hostfile hostfile.txt ./mpi_app --mode array_send
```

**What happens**: Process 0 sends an integer array over the network to Process 1, which receives and displays it.

---

## 🔧 Troubleshooting

### Common Issues:
- **"Permission denied"**: Check SSH passwordless setup
- **"Host unreachable"**: Verify network connectivity and IP addresses in hostfile
- **"File not found"**: Ensure the input file exists on the sender machine
- **"Connection refused"**: Check if MPI is installed on all machines
- **Wrong process count**: Each mode requires specific number of processes (see above)

### Testing Network Setup:
```bash
# Test SSH connectivity
ssh username@192.168.100.102

# Test MPI installation on remote machine
ssh username@192.168.100.102 "mpirun --version"

# Ping test between machines
ping 192.168.100.102
```