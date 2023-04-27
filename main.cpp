// lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<fstream>
#include "ArgumentManager.h"
#include<queue>

struct InCount {

    int vertex;
    int count;
    InCount() {
        vertex = 0;
        count = 0;
    }
    InCount(int vertex, int count) {
        this->vertex = vertex;
        this->count = count;
    }
};

void checkCounts(int* arr, InCount* InCounts,int counter,int j, int vertices,bool** adj);
bool Search(int* arr,int vertex, int vertices);
bool verifyCounts(InCount* InCounts,int vertices);

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    ifstream fin("input1.txt");
    ofstream fout("output1.txt");

    int vertices = 0; fin >> vertices;
    int u = 0; int v = 0;

    cout << vertices << endl;
    InCount* InCounts = new InCount[vertices];


    bool** adj = new bool*[vertices];
    for (int i = 0; i < vertices; i++) {
        adj[i] = new bool[vertices];
        for (int j = 0; j < vertices; j++) {
            adj[i][j] = false;
        }
    }


    for (int i = 0; i < vertices; i++) {
        InCounts[i].vertex = i;
    }

    while (fin >> u >> v) {
        adj[u][v] = true;
        InCounts[v].count++;
    }
    //verify at least one InCount count has 0 -> comfirms no cycles
    if (!(verifyCounts(InCounts,vertices) )) {
        fout << "No Topological Sorting Exists!";
        return 0;
    }


    for (int row = 0; row < vertices; row++) {
        for (int col = 0; col < vertices; col++) {
            if (adj[row][col]) {

                cout << "+ ";
            }
            else {
                cout << "- ";
            }
        }
        cout << endl;
    }



    for (int i = 0; i < vertices; i++) {
        cout << InCounts[i].vertex << " " << InCounts[i].count << endl;
    }

    int* arr = new int[vertices]; int counter = 0; int j = 0;

    checkCounts(arr, InCounts,counter,j, vertices, adj);
    
    cout << "RESULT" << endl;
    for (int i = 0; i < vertices; i++) {
        fout << arr[i] << " ";
    }

    return 0;
}

void checkCounts(int* arr, InCount* InCounts,int counter,int j, int vertices, bool** adj) {
    if (arr[vertices - 1] > 0) { //if element in last value -> array is full
        return;
    }

    queue<int> myQ;
    cout << "COUNTER " << counter << endl; counter++;
    for (int i = 0; i < vertices; i++) {
        if (InCounts[i].count == 0) {
            if (!(Search(arr, InCounts[i].vertex, vertices))) {
                myQ.push(InCounts[i].vertex); //push 0,1
            }
        }
    }

    //where is connection coming from
    while (!myQ.empty()) {
        for (int i = 0; i < vertices; i++) {
            if (adj[myQ.front()][i]) {// check whole row
                InCounts[i].count--;
            }
        }
        arr[j] = myQ.front();
        j++;
        myQ.pop();
    }


    cout << endl;
    for (int i = 0; i < vertices; i++) {
        cout << InCounts[i].vertex << " " << InCounts[i].count << endl;
    }

    cout << "RESULT" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << arr[i] << endl;
    }

    checkCounts(arr, InCounts,counter,j, vertices, adj);
}

bool Search(int* arr,int vertex,int vertices) {
    for (int i = 0; i < vertices; i++) {
        if (vertex == arr[i]) {
            return true;
        }
    }
    return false;
}

bool verifyCounts(InCount* InCounts,int vertices) {
    for (int i = 0; i < vertices; i++) {
        if (InCounts[i].count == 0) {
            return true;
        }
    }
    return false;
}
