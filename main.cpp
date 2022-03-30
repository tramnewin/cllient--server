#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<cstring>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdio.h>
using namespace std;
using namespace std::chrono;
struct information {        //the information of a node i to node j at what cost
    size_t i;
    size_t j;
    size_t cost;
};
struct doubleVal {         //a struct to store the source and destination nodes
    size_t i;
    size_t j;
};
void printEachIteration(vector<information> theTable, vector <int> Nprime, int totalNode) {
    cout << "Step    N'\t\t\t\t";
    for (int i = 0; i < totalNode - 1; ++i) {
        cout << theTable[i].j + 1 << "\t";
    }
    cout << "\n";
    int tracking = 0;
    vector<int> anotherNtracking;
    for (int i = 0; i < totalNode; i++) {
        cout << i << "     ";
        cout << i << "     ";
        if (i == 0) {
            cout << "{" << Nprime[i] + 1 << "}" << "\t\t\t\t";
            for (int j = 0; j < totalNode - 1; j++) {
                if (theTable[j + tracking].cost != 1073741824)
                    cout << theTable[j].cost << ", " << theTable[j].i + 1 << "\t";
                else
                    cout << "INF, " << theTable[j].i + 1 << "\t";
            }
            tracking = tracking + totalNode - 1;
        }
        else if (i == totalNode - 1) {
            cout << "{";
            int count = 0;
            for (int j = 0; j < i; j++) {
                cout << Nprime[j] + 1 << ", ";
                count = j;
            }
            cout << Nprime[count + 1] + 1 << "}" << "                             ";
        }
        else {
            cout << "{";
            int counting;
            for (int j = 0; j < i; j++) {
                cout << Nprime[j] + 1 << ", ";
                anotherNtracking.push_back(Nprime[j]);
                counting = j;
            }
            cout << Nprime[i] + 1 << "}" << "                             ";
            for (int f = (totalNode-1)/4; f> counting; f--) {
                cout << " ";
            }
            anotherNtracking.push_back(Nprime[i]);
            int anothercount = 0;
            for (int j = 0; j < totalNode - 1; j++) {
                if (theTable[j + 1].j != 0) {
                    if (find(anotherNtracking.begin(), anotherNtracking.end(), theTable[j + tracking].j) != anotherNtracking.end()) {
                        cout << "\t";
                    }
                    else {
                        if (theTable[j + tracking].cost != 1073741824)
                            cout << theTable[j + tracking].cost << ", " << theTable[j + tracking].i + 1 << "\t";
                        else
                            cout << "INF, " << theTable[j + tracking].i + 1 << "\t";
                    }


                }

                anothercount = j;
            }
            if (find(anotherNtracking.begin(), anotherNtracking.end(), theTable[anothercount + tracking].j) == anotherNtracking.end()) {
                if (theTable[anothercount + tracking].cost != 1073741824)
                    cout << theTable[anothercount + tracking].cost << ", " << theTable[anothercount + tracking].i + 1 << "\t";
                else
                    cout << "INF, " << theTable[anothercount + tracking].i + 1 << "\t";
            }
            else if (find(anotherNtracking.begin(), anotherNtracking.end(), theTable[anothercount + tracking].j) != anotherNtracking.end()) {
                cout << "\t";
            }


            tracking = tracking + totalNode - 1;

        }
        cout << endl;
    }
}
void printFWD(vector<int> Link, vector<int> Destination, int totalNode, int src)
{
   
    printf("Destination \t Link\n");
    for (int i = 0; i < totalNode - 1; i++)
        printf("%d \t\t (%d,%d)\n", Destination[i] + 1, src + 1, Link[i] + 1);
}

// driver program to test above function
int main()
{
    vector<int> Link;                           //the vector that holds the adjacent nodes of the source node that would lead to the destination node
    vector<int> Destination;                    //the destination node (source node excluded)
    vector<information>finalResultmindis;       //holds all the inoformation of nodes with the least-cost paths
    vector<int> index404;                       //store indexes that have not found the adjacent node lead to itself from the source node
    bool neighbornode = true;       
    size_t counting = 0;
    int initialfrmi;
    information atemp;
    vector <int> Nprime;
    vector<information> theTable;               //we use i to navigagte the source, and j to navigate the column. Basically, like a dictionary to lookup
    vector<size_t> dist;                           // The output vector.  dist[i] will hold the shortest distance from src to i
    vector<bool> sptSet;                        // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
    ifstream textfile;
    string thefile;
    string myText;
    stringstream ss;
    string substring;
    string anotherstring;
    string temp;
    int count = 0;
    int line = 0;
    string node;
    string flag;
    cout << "mylinkstate ";
    getline(cin, myText);                       //read in the file name, the source node, the flag
    stringstream iput(myText);
    getline(iput, thefile, ' ');
    getline(iput, node, ' ');
    getline(iput, flag, ' ');
    textfile.open(thefile);
    if (!textfile.is_open())                    //error check whether the file can be opened or not
    {
        cout << "Error opening file";       
        return -1;
    }
    ss << textfile.rdbuf();
    textfile.close();
    string totalNodes;
    getline(ss, totalNodes);                                              //read the first line to get the total nodes 
    size_t total;
    total = stoi(totalNodes);                                             //since what we read in from the file is a string datatype, we have to convert it to an int to do the later calculation
    size_t nodeval = stoi(node);
    nodeval = nodeval - 1;                                                //all calculation is based of the index made from array/ vector, so the actual value of the node is 1 greater than the array/vector's index
    vector<vector<int>> graph(total * total, vector<int>(3, 0));          //2d array(total nodes ^2 x 3) with each row has the nodes number and the least cost path between them
    auto start = high_resolution_clock::now();                            //timestamp starts
    while (getline(ss, anotherstring)) {                                  //read the file line by line
        substring = anotherstring;
        stringstream iss(substring);
        getline(iss, temp, ' ');
        count = 0;
        while (count < 3) {
            int testing;
            testing = stoi(temp);                                
            graph[line][count] = testing;                                //store the cost to the correspond index of the 2d vector
            getline(iss, temp, ' ');
            ++count;
        }
        ++line;
    }
    int keeptrack = 0;
    vector<vector<int>> theMatrix(total, vector<int>(total, 0));        //create a matrix with column is the destination and the rows are the source, the value within each cell is the cost from the source to the destination
    for (size_t i = 0; i < total; i++) {                                   //valule placed in each index is from the graph vector above
        for (size_t j = 0; j < total; j++) {
            theMatrix[i][j] = graph[j + keeptrack][2];
        }
        keeptrack = keeptrack + total;
    }
    for (size_t i = 0; i < total; i++) {
        for (size_t j = 0; j < total; j++) {
            if (theMatrix[i][j] == 1073741824) {                        //if the cost from the source to the destination is infinitive, we place it with a 0 
                theMatrix[i][j] = 0;
            }
        }

    }

    // Initialize all distances as INFINITE and stpSet[] as false
    for (size_t i = 0; i < total; i++)
        dist.push_back(1073741824), sptSet.push_back(false);

    // Distance of source vertex from itself is always 0
    dist[nodeval] = 0;
    information mintemp;
    // Find shortest path for all vertices
    for (size_t i = 0; i < total - 1; i++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. v is always equal to src in the first iteration.
        size_t min = 1073741824, min_index;
        for (size_t v = 0; v < total; v++) {

            if (sptSet[v] == false && dist[v] < min) {                  //if the distance is smaller than min and the vertice is not yet proceeded,update min and min_index
                min = dist[v], min_index = v;
                for (size_t a = 0; a < theTable.size(); a++) {
                    if (theTable[a].cost == dist[v] && theTable[a].j == v) {
                        mintemp.cost = min;                             
                        mintemp.i = theTable[a].i;
                        mintemp.j = min_index;
                        break;
                    }

                }
            }
            else if (dist[v] == min) {                                  //if the distance is equal to min value, we haave to check which source is most close to the source node inserted by the user
                if (i == 0) {
                    min = dist[v], min_index = v;                       //if i =0, the sptset is not yet develop, so we can update min and min_index
                }
                else {
                    information tempp;                                  //if not, we look up the source from theTable vector
                    for (size_t a = 0; a < theTable.size(); a++) {
                        if (theTable[a].cost == dist[v] && theTable[a].j == v) { 
                            tempp.cost = dist[v];
                            tempp.i = theTable[a].i;
                            tempp.j = v;
                            break;
                        }

                    }
                    int minindexinN;
                    int temppindexinN;
                    for (size_t d = 0; d < Nprime.size(); d++) {
                        if (Nprime[d] == mintemp.i) {                   //after look up the source, we need to check the index at Nprime vector to see which one is closer to the source node 
                            minindexinN = d;
                        }
                        if (Nprime[d] == tempp.i) {
                            temppindexinN = d;
                        }
                    }
                    if (temppindexinN < minindexinN) {                  //if the min index is farther from the source node than the other, we update the min and min_index
                        min = dist[v], min_index = v;
                    }
                    else {                                              //if not, leave it as it is
                    }
                }

            }
        }
        Nprime.push_back(min_index);                                    //for every updated min_index we store the value in to nprime
        sptSet[min_index] = true;                                       //and set the sptSet at the min index to true so that we don't have to check it in the next loop
        // Update dist value of the adjacent vertices of the picked vertex.
        for (size_t v = 0; v < total; v++) {
            // Update dist[v] only if is not in sptSet, there is an edge from
            // adjacent node to v, and total weight of path from src to  v through adjacent node is
            // smaller than current value of dist[v]
            information tempo;
            if (!sptSet[v] && theMatrix[min_index][v] && dist[min_index] != 1073741824 && dist[min_index] + theMatrix[min_index][v] < dist[v]) {
                dist[v] = dist[min_index] + theMatrix[min_index][v];
                tempo.j = v;
                tempo.i = min_index;
                tempo.cost = dist[v];
                theTable.push_back(tempo);                                  //we also update theTable for later on
            }
            else if (theTable.size() >= total - 1) {
                for (size_t a = 0; a < theTable.size(); a++) {
                    if (theTable[a].cost == dist[v] && theTable[a].j == v) {
                        tempo.cost = dist[v];
                        tempo.i = theTable[a].i;
                        tempo.j = v;
                        theTable.push_back(tempo);
                        break;
                    }

                }

            }
            else if (dist[v] == 1073741824) {
                tempo.j = v;
                tempo.i = min_index;
                tempo.cost = dist[v];
                theTable.push_back(tempo);
            }

        }
    }
    for (size_t i = 0; i < total; i++) {                               //since the previous loop found the path up until total node -1, we use this loop to add in the final node
        if (i != nodeval && find(Nprime.begin(), Nprime.end(), i) == Nprime.end()) {
            Nprime.push_back(i);
        }
    }
    auto stop0 = high_resolution_clock::now();                      //the end timestamp 
    //we create fowarding table here. intiallly, we create the Link vector with the nodes that are adjacent to the source node.
    //then we go through theTable vector to find which node has its source as the adjacent nodes and store its Link to the link vector. At the same time, 
    //we update the destination vector to keep track of which nodes has been processed. For the nodes that has its source not from the adjacent nodes,
    //we look it up in the Link vector to see if the updated node has its source from the adjacent nodes or not. if so, we push the value of that node with the adjcent found from that median node search.

    for (size_t j = 0; j < total - 1; j++) {
        while (counting < theTable.size())
        {
            initialfrmi = theTable[j].i;
            if (theTable[counting + j].i != initialfrmi) {
                neighbornode = false;
                break;
            }
            counting = counting + total - 1;
        }
        if (neighbornode == true) {
            Link.push_back(theTable[j].j);                  //neighbornode
            Destination.push_back(theTable[j].i);           //src
        }
        counting = 0;
        neighbornode = true;
    }
    counting = 0;
    size_t i = theTable.size() - 1;
    while (i<theTable.size() && i> theTable.size() - total) {
        if (find(Link.begin(), Link.end(), theTable[i].j) == Link.end()) {          //not found
            atemp.i = theTable[i].i;
            atemp.j = theTable[i].j;
            finalResultmindis.push_back(atemp);              //infos of node that is not the neighbor of the src
        }
        i--;
    }
    while (Link.size() < total - 1) {                           //loop unitl gather them all
        for (size_t i = 0; i < finalResultmindis.size(); i++) {
            if (find(Link.begin(), Link.end(), finalResultmindis[i].i) != Link.end()) {
                Link.push_back(finalResultmindis[i].i);
                Destination.push_back(finalResultmindis[i].j);
            }
            else {
                index404.push_back(i);
            }
        }
        for (size_t i = 0; i < index404.size(); i++) {
            for (size_t j = 0; j < Destination.size(); j++) {
                if (Destination[j] == finalResultmindis[index404[i]].i) {
                    Link.push_back(Link[j]);
                    Destination.push_back(finalResultmindis[index404[i]].j);
                }
            }

        }
    }
    for (size_t i = 0; i < Destination.size(); i++) {
        if (Destination[i] == nodeval) {
            Destination[i] = Link[i];
        }
    }
    //sorting out in ascending order (of the destination nodes)
    int key, anotherkey;
    for (size_t i = 1; i < Destination.size(); i++)
    {
        key = Destination[i];
        anotherkey = Link[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && Destination[j] > key)
        {
            Destination[j + 1] = Destination[j];
            Link[j + 1] = Link[j];
            j = j - 1;
        }
        Destination[j + 1] = key;
        Link[j + 1] = anotherkey;
    }
    if (flag == "0") {              //print the fowarding table if flag is 0. otherwise, print both the routing table and the fowarding table

        printFWD(Link, Destination, total, nodeval);
    }
    else if (flag == "1") {
        printEachIteration(theTable, Nprime, total);
        printFWD(Link, Destination, total, nodeval);
    }
    else {
        cout << "invalid flag";
    }
    std::chrono::duration<double, std::milli> fp_ms =stop0 - start;             //calculate the excution time and print it out
    cout << "Time taken by function: " << fp_ms.count() << " millisecond(s)" << endl;
    return 0;
}

