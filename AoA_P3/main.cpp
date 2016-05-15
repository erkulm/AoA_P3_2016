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

const int MAX_SIZE = 20;

using namespace std;

class Vertex;
class Node{
public:
    string name;
    int vertexSize;
    Vertex *vertices[MAX_SIZE];
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
    for (int i = 0; i < MAX_SIZE; i++) {
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
    int graph[MAX_SIZE][MAX_SIZE]; //shows the edges: if a value is NULL then there is no adge between the nodes else the integer value represents the flow variable
    int numberOfRobots;
    int numberOfObjects;
    ifstream in;
    in.open("/users/mahmut/Downloads/input.txt");
    int a;
    int j;
    for (a = 0; a < MAX_SIZE; a++) {
        for (j = 0; j < MAX_SIZE; j++) {
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
        Node *objects[MAX_SIZE];
        Node *robots[MAX_SIZE];
        if (numberOfObjects < MAX_SIZE && numberOfRobots < MAX_SIZE) {
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
            int flow = fordFulkersen(start, sink);
            cout<<endl<<"flow = " <<flow<<endl;
            if (flow<numberOfObjects) {
                cerr<<"No viable option is found!"<<endl;
                ofstream out;
                out.open("/users/mahmut/desktop/outputTemp.txt");
                out <<"No viable option is found!"<<endl;
                out.close();
            }
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
        for (int i = 0; i<MAX_SIZE; i++) {
            if (start->vertices[i] != NULL && start->vertices[i]->weight > 0) {
                start->vertices[i]->weight--;
                v->push(start->vertices[i]);
                bool temp;
                temp = dfs(start->vertices[i]->to, sink, v);
                if (temp == true) {
                    return true;
                }
            }
            else if (start->vertices[i] == NULL)
                break;
            else if(v->size() > 0)
                    v->pop();
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
        // the path_flow will always be one
        // because an object can be carried by only one robot
        flow++;
        while(v.size()>0){
            // updating the residual graph
            // printing out vertices in the graph
            Vertex *temp = v.top();
            out<<temp->from->name<<"->"<<temp->to->name<<endl;
            Vertex *newVertex = new  Vertex();
            newVertex->from = temp->to;
            newVertex->to = temp->from;
            newVertex->weight = 1;
            temp->from->vertices[temp->from->vertexSize++] = newVertex;
            v.pop();
        }
    }
    out.close();
    return flow;
}
