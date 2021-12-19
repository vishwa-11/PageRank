#include <iostream>
#include <vector>
using namespace std;
#include <map>
#include <iomanip>

//main structure for adjacency list objects
class AdjList {


public:
    int n;
    int p;
    int V;

    //keeps track of each node's outward neighbors. the string is the
    //name of each webpage and there's a vector of the names of it's outward
    //neighbors
    map<string, vector<string>> neighborsMap;

    //a map associating each webpage to its initial rank value
    map<string, float> r;

    //takes in user input in order to initialize the object's member variables
    AdjList() {
        int no_of_lines, power_iterations;
        string from, to;
        cin >> no_of_lines;
        cin >> power_iterations;

        n = no_of_lines;
        p = power_iterations;
        V = 0;

        map<string, vector<string>>::iterator iter;

        bool match;

        for (int i = 0; i < n; i++) {
            cin >> from;
            cin >> to;

            //check to see if 'from' already exists in neighborsMap
            //note: the size of neighborsMap is V
            for (iter = neighborsMap.begin(); iter != neighborsMap.end(); iter++) {
                if (iter->first == from) {
                    match = true;
                    break;
                }
            }

            //if the from string doesn't already exist in the map,
            //we initialize a new map value
            if (!match) {
                vector<string> neighbors;
                neighborsMap[from] = neighbors;
                V++;
            }

            neighborsMap[from].push_back(to);

            match = false;

            //we need to check if the to string is also already
            //present in the map
            for (iter = neighborsMap.begin(); iter != neighborsMap.end(); iter++) {
                if (iter->first == to) {
                    match = true;
                    break;
                }
            }

            if (!match) {
                vector<string> neighbors;
                neighborsMap[to] = neighbors;
                V++;
            }

            match = false;
        }

        //initialize the r vector
        for (iter = neighborsMap.begin(); iter != neighborsMap.end(); iter++) {
            r[iter->first] = ((float)1 / (float)V);
        }
    }

    //this method carries out power iteration
    void Iterate() {
        //this map represents r at time t + 1
        map<string, float> r2;

        map<string, vector<string>>::iterator iter;

        map<string, vector<string>>::iterator iter2;

        map<string, float>::iterator iter3;

        //used to save the rank of each node
        float r_value = 0;

        //this uses the data structures I used in my adjacency list
        //class to simulate a form of matrix multiplication
        for (int i = 0; i < p - 1; i++) {
            for (iter = neighborsMap.begin(); iter != neighborsMap.end(); iter++) {
                //if the given node is a neighbor for another node
                //then add 1 divided by the number of out neighbors of the other node
                //times the rank of the other node at time t
                for (iter2 = neighborsMap.begin(); iter2 != neighborsMap.end(); iter2++) {
                    for (int j = 0; j < iter2->second.size(); j++) {
                        if (iter->first == iter2->second[j]) {
                            r_value += (float)1 / (float)iter2->second.size() * r[iter2->first];
                        }
                    }
                }
                r2[iter->first] = r_value;
                r_value = 0;
            }

            //equate r to r2 so that we can calculate the r map for the next increment
            //of time
            for (iter3 = r.begin(); iter3 != r.end(); iter3++) {
                iter3->second = r2[iter3->first];
            }
        }

        //set the precision of the rank of each webpage
        for (iter3 = r.begin(); iter3 != r.end(); iter3++) {
            cout << iter3->first << " ";
            cout << setprecision (2) << fixed << iter3->second;
            cout << endl;
        }
    }

};

int main() {
    //initialize an adjacency list
    //this also collects input on the values of n, p and V
    AdjList list = AdjList();

    //carry out power iteration
    list.Iterate();

    return 0;
}
