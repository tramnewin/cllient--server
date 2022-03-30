
// Server C code to reverse a 
// string by sent from client 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <string>
#include <iostream>
using namespace std;
#define PORT 5620 
#define MAX 80 
void func(int sockfd)       //function to read the message sent from the client and reverse it then send it back to the client
{
    char buff[MAX];
    int l;
    int i, j;
    // infinite loop for chat 
    for (;;) {
        bzero(buff, MAX);          //initialize buff in order to contain the client's message 
        char temp;
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents 
        printf("From client: %s\n", buff);
        //reverse the string from the client
        l = strlen(buff);
        for (i = 0, j = l - 1; i < j; i++, j--) {
            temp = buff[i];
            buff[i] = buff[j];
            buff[j] = temp;
        }
        printf("Modified string made by server: %s\n", buff);
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff));

        // if the reverse message is "nif", then server exit and chat ended. 
        if (strncmp("\nnif", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver code 
int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    printf("my-reverse-echo-server 5620\n");
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET,
        SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to 
    // the port 5620 
    if (bind(server_fd, (struct sockaddr*)&address,
        sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // puts the server socket in passive mode 
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd,
        (struct sockaddr*)&address,
        (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    // Function for chatting between client and server 
    func(new_socket);

    // After chatting close the socket 
    close(server_fd);

}
