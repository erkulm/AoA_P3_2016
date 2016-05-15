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
#include <stack>


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
    for (int i = 0; i < 20; i++) {
        vertices[i] = NULL;
    }
}

Vertex::Vertex(){
    from = NULL;
    to = NULL;
    weight = 0;
}

int fordFulkersen(Node *start, Node *sink);

bool dfs(Node *start, Node *sink, stack<Vertex*> *v);

int main(int argc, const char * argv[]) {
    stack<Vertex> v;
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
        start->name = "start";
        Node *sink = new Node();
        sink->name = "sink";
        in >> numberOfObjects;
        in >> numberOfRobots;
        Node *objects[20];
        Node *robots[20];
        if (numberOfObjects < 20 && numberOfRobots < 20) {
            for (int i = 0; i < numberOfObjects; i++) {
                for (int j = 0; j <numberOfRobots; j++) {
                    int temp;
                    in >> temp;
                    cout<<temp<<"   ";
                    if (temp == 1) {
                        
                        
                        graph[i][j] = 1;
                        // a new vertex from start node to the ith node
                        if (objects[i] == NULL) {
                            objects[i] = new Node();
                            objects[i]->name = "object_" + to_string(i);
                        }
                        
                        Vertex *tempVertex = new Vertex();
                        tempVertex->from = start;
                        tempVertex->to = objects[i];
                        tempVertex->weight = 1;
                        start->vertices[start->vertexSize] = tempVertex;
                        start->vertexSize++;
                        
                        
                        // a new vertex from ith node to the jth robot;
                        if (robots[j] == NULL) {
                            robots[j] = new Node();
                            robots[j]->name = "robot_" + to_string(j);
                        }
    
                        Vertex *objectToRobot = new Vertex();
                        objectToRobot->from = objects[i];
                        objectToRobot->to = robots[j];
                        objectToRobot->weight = 1;
                        objects[i]->vertices[objects[i]->vertexSize] = objectToRobot;
                        objects[i]->vertexSize++;
                        
                    }
                }
            }
            for (int i=0; i<numberOfRobots; i++) {
                int weight;
                in>>weight;
                Vertex *robotToSink = new Vertex();
                robotToSink->from = robots[i];
                robotToSink->to = sink;
                robotToSink->weight = weight;
                robots[i]->vertices[0] = robotToSink;
                robots[i]->vertexSize++;
            }
            
            cout<<endl<<"flow = " <<fordFulkersen(start, sink)<<endl;
        }
    }
    
    
    else{
        cerr<<"Input file not found"<<endl;
        return 1;
    }
    
    return 0;
}

bool dfs(Node * start, Node *sink, stack<Vertex *> *v){
    if (start == NULL) {
        throw "Start Node Can't be Null";
    }
    else{
        if (start == sink) {
            return true;
        }
        for (int i = 0; i<20; i++) {
            if (start->vertices[i] != NULL && start->vertices[i]->weight > 0) {
                start->vertices[i]->weight--;
                v->push(start->vertices[i]);
                bool temp;
                temp = dfs(start->vertices[i]->to, sink, v);
                if (temp == true) {
                    return true;
                }
            }
            else{
                if(v->size() > 0)
                    v->pop();
            }
        }
    }
    return false;
}

int fordFulkersen(Node *start, Node *sink){
    int flow = 0;
    int pathFlow = INT_MAX;
    stack<Vertex*> v;
    ofstream out;
    out.open("/users/mahmut/Desktop/outputTemp.txt");
    while(dfs(start,sink,&v)){
        // because the flow will always be one
        // no bactracking needed
        flow++;
        while(v.size()>0){
            Vertex *temp = v.top();
            out<<temp->from->name<<"->"<<temp->to->name<<endl;
            v.pop();
        }
    }
    out.close();
    return flow;
}
