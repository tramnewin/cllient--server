*******************************************************
*  Name      : Tram Nguyen         
*  Student ID: 109499620                
*  Class     :  CSC 3761 Section 01           
*  Programming lab#       :  1                
*  Due Date  :  Mar. 15, 2021
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************
Build a simple reverse echo server and a client using a TCP socket. The server and client should run at different machines.


*******************************************************
*  Source files
*******************************************************

Name:  Server.cpp
   Server would run first in order to create a socket, to bind the socket to the address and port number that are specified and to listen for incoming message from client. Then, it extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. At this point, connection is established between client and server, and they are ready to transfer data (here would recieve the string from client and reverse it and then send it back to the client).


Name: client.cpp
   same as the server program, the client would create a socket then connect it with the server and exchange data (here would send a string and recieve a reversed version of it from the server)


*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on gnu g++ 6.1.x  It was 
   compiled, run, and tested on gcc csegrid server.


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       %  tar -xvf nguyen9620.tar


   Now you should see a directory named nguyen9620, run the command:
       %   cd nguyen9620
   within the directory,there are:
        server.cpp
        client.cpp
	makefile.txt
        Readme.txt
	

2. Build the program.

    Change to the directory that contains the file by:
    % cd [nguyen_9620] 

    Compile the program by:
    % make server
    % make client

3. Run the program by:
   % ./server
   % ./client

4. Delete the obj files, executables, and core dump by
   %./make clean
