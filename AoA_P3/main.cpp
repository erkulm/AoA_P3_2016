//
//  main.cpp
//  AoA_P3
//
//  Created by Mahmut Erkul on 13/05/16.
//  Copyright © 2016 Mahmut Erkul. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Vertex;
class Node{
public:
    string name;
    int vertexSize;
    Vertex *vertices[20];
    Node();
};

class Vertex{
public:
    int weight;
    Node *from;
    Node *to;
    Vertex();
};

Node::Node(){
    vertexSize = 0;
}

Vertex::Vertex(){
    
}

int main(int argc, const char * argv[]) {
    int graph[20][20]; //shows the edges: if a value is NULL then there is no adge between the nodes else the integer value represents the flow variable
    int numberOfRobots;
    int numberOfObjects;
    ifstream in;
    in.open("/users/mahmut/Downloads/input.txt");
    int a;
    int j;
    for (a = 0; a < 20; a++) {
        for (j = 0; j < 20; j++) {
            graph[a][j] = NULL;
        }
    }
    if (in.is_open()) {
        Node *start = new Node();
        Node *sink = new Node();
        in >> numberOfObjects;
        in >> numberOfRobots;
        Node *objects[20];
        Node *robots[20];
        if (numberOfObjects < 20 && numberOfRobots < 20) {
            for (int i = 0; i < numberOfObjects; i++) {
                for (int j = 0; j <numberOfRobots; j++) {
                    int temp;
                    in >> temp;
                    if (graph[i][j] == NULL && temp == 1) {
                        
                        
                        graph[i][j] = 1;
                        // a new vertex from start node to the ith node
                        objects[i] = new Node();
                        objects[i]->name = "object_" + new string(i);
                        Vertex *tempVertex = new Vertex();
                        tempVertex->from = start;
                        tempVertex->to = objects[i];
                        tempVertex->weight = 1;
                        start->vertices[start->vertexSize] = tempVertex;
                        start->vertexSize++;
                        
                        
                        // a new vertex from ith node to the jth robot;
                        
                        robots[j] = new Node();
                        Vertex *objectToRobot = new Vertex();
                        objectToRobot->from = objects[i];
                        objectToRobot->to = robots[j];
                        objectToRobot->weight = 1;
                        objects[i]->vertices[objects[i]->vertexSize] = objectToRobot;
                        objects[i]->vertexSize++;
                        
                    } else if(temp == 1){
                        graph[i][j]++;
                    }
                }
            }
        }
    }
    
    
    else{
        cerr<<"Input file not found"<<endl;
        return 1;
    }
    
    return 0;
}
