#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    std::cout<<"START \n";

    int server_fd=socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        std::cout << "Failed to create socket.\n";
        return 1;
    }
    std::cout << "Socket created successfully! File Descriptor ID: " << server_fd << "\n";

    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(8080);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0){
        std::cout << "Failed to bind socket to port 8080.\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Socket successfully bound to Port 8080!\n";

    if(listen(server_fd,10)<0){
        std::cout << "Failed to put socket into listening mode.\n";
        close(server_fd);
        return 1;
    }
    std::cout << "Server is now listening on port 8080. Awaiting connections...\n";


    while(1){
        int client_fd=accept(server_fd,NULL,NULL);
        if (client_fd < 0) {
            std::cout << "Failed to accept incoming connection.\n";
            close(server_fd);
            return 1;
        }
        std::cout << "Client connected successfully! Dedicated Client FD ID: " << client_fd << "\n";

        char buffer[1024];
        int bytes_read=read(client_fd, buffer, sizeof(buffer)-1);
        if(bytes_read<0){
            std::cout << "Failed to read data from client.\n";
        }
        else{
            std::cout << "\n=== Received HTTP Request (" << bytes_read << " bytes) ===\n";
            std::string first_line(buffer);
            size_t newline_pos=first_line.find("\r\n");
            if(newline_pos != std::string::npos){
                first_line = first_line.substr(0, newline_pos);
            }
            std::cout <<first_line<<"\n";
            std::cout << "================================================\n\n";
        }

        std::string html_content = "<html><body><h1>Hello from your custom C++ Server!</h1></body></html>";
        std::string http_response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: " + std::to_string(html_content.length()) + "\r\n"
                "Connection: close\r\n"
                "\r\n" 
                + html_content;

                write(client_fd, http_response.c_str(), http_response.length());
                std::cout << "HTTP Response successfully transmitted to client.\n";

        close(client_fd);
    }   
    close(server_fd);
    std::cout<<"CLOSED \n";
    return 0;
}