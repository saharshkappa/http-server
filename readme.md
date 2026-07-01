# Custom HTTP Web Server from Scratch (C++)

A lightweight, low-level HTTP web server built entirely from scratch in C++ using Linux system calls and POSIX sockets. 

I built this project to understand how network protocols operate under the hood, moving away from high-level abstractions like Node.js or Express to interact directly with the operating system layer.

---

## Key Features & Concepts Mastered
* Low-Level Networking: Utilized POSIX sockets (sys/socket.h) to establish raw TCP/IP connections.
* Socket Lifecycle Management: Handled the entire lifecycle of a network connection: socket() creation, IP/Port binding (bind()), passive state listening (listen()), and incoming connection handling (accept()).
* HTTP Protocol Implementation: Manually parsed raw string buffers for incoming HTTP requests and constructed RFC-compliant HTTP/1.1 response headers (Status 200 OK, Content-Type, Content-Length).
* Resource Management: Managed file descriptors dynamically, ensuring active connections (client_fd) are closed cleanly after processing to prevent resource leaks.

---

## Tech Stack & Tools
* Language: C++17
* Build System: CMake
* APIs: Linux Syscalls & POSIX Sockets
* Networking: TCP/IP, HTTP/1.1 Protocols
* Environment: Linux / WSL

---

## Architecture Flow
1. Initialize: Creates an AF_INET (IPv4) stream socket via TCP (SOCK_STREAM).
2. Bind & Listen: Binds the socket to port 8080 and sets a connection backlog queue of 10.
3. Event Loop: Enters an infinite loop waiting to accept() incoming browser/client connections.
4. Process: Reads the raw request byte buffer, logs the request line, and crafts a valid raw HTTP response string.
5. Transmit & Terminate: Writes the response back to the client and immediately closes the client file descriptor to maintain server availability.

---

## How to Build & Run

### Prerequisites
A Unix-based system (Ubuntu, Debian, macOS, or WSL on Windows) with g++ and cmake installed.

### 1. Build the Project
Using the dedicated build directory to keep the root repository clean:
```bash
# Navigate into the build directory
cd build

# Generate the build files using CMake
cmake ..

# Compile the executable
cmake --build .

# Execute
./server