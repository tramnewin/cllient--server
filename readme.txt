*******************************************************
*  Name      : Tram Nguyen         
*  Student ID: 109499620                
*  Class     :  CSC 3761 Section 01           
*  HW#       :  4                
*  Due Date  :  Ma7. 3rd, 2021
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************
In this programming assignment, you will be implementing 
Link-State-Routing Algorithm with either C or C++.  


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  This is the driver program that implementing
the Link-state algorithm using dijkstra's algorithm. After calculation,
the program also display the routing table as well as the forwarding table
depending on the flag.
  
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
       %  tar -xvf ngu9620.tar

   Now you should see a directory named homework with the files:
        main.cpp
	makefile.txt
        Readme.txt
	

2. Build the program.

    Change to the directory that contains the file by:
    % cd [ngu9620]

    Compile the program by:
    % make

3. Run the program by:
   % ./[ngu9620]

4. Delete the obj files, executables, and core dump by
   %./make clean
