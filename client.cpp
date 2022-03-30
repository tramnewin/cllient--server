#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <sys/types.h>
#define PORT 5620               
#define MAX 80 
void func(int sockfd)       //function to read in the client's string 
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));          //initialize the string to store the client's message
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')     //read in the user's message
            ;
        write(sockfd, buff, sizeof(buff));          //write the message and send it to the server
        bzero(buff, sizeof(buff));                  //zero out the string in order to store the upcoming message sent feom the server
        read(sockfd, buff, sizeof(buff));           //read the message from the server
        printf("From Server : %s\n", buff);         
        if ((strncmp(buff, "\nnif", 4)) == 0) {     //end the chat and close the connection if the client types in "fin"
            printf("Client Exit...\n");
            break;
        }
    }
}
main() {
   // struct sockaddr_in address;
    int my_socket = 0;
    struct sockaddr_in server_address;
    int l;
    char str[100];
    char addr[MAX];
    struct hostent* hp;
    struct in_addr ip_addr;
    printf("my-echo-client 5620 ");      
    memset(str, '\0', sizeof(str));
    fgets(addr, MAX, stdin);                    //read in the name of the server's host machine that is typed by the client
    l = strlen(addr);                           //read in the length of the name of the host's machine name 
    strncpy(str, addr, l - 1);                  //discard the '/n' in the string
    hp = gethostbyname(str);                    //dns look up the IP address of the host machine
    ip_addr = *(struct in_addr*)(hp->h_addr);   //save the IP address into ip_addr
    // Creating socket file descriptor
    if ((my_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nUnable to create Socket \n");
        return -1;
    }
    
    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET;                        //set up the server's socket stream, port (which is 5620), IP address
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = ip_addr.s_addr;
    // connect the socket
    if (connect(my_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        printf("\nUnable to connect to the server \n");
        return -1;
    }
    // function for chat 
    func(my_socket);

    // close the socket 
    close(my_socket);

}