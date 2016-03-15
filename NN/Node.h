#ifndef _NODE_H
#define _NODE_H
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include "readindata.h"
using namespace std;
class Node{
public:
	double output;   //ouput
	vector<double> inputWs;   //weights of inputs : w0, w1, w2.....
	double delta;     //  ¦Ä
	Node(int numOfInput);
	void printNode();

};

void Node::printNode()
{
	cout<<"Weight:";
	for(int i=0;i<inputWs.size();i++)
	{
		cout<<"w"<<i<<":"<<inputWs[i]<<" ,";
	}
	cout<<endl<<"Output = "<<output<<endl;
}


Node::Node(int numOfInput)
{
	for(int i=0;i<numOfInput;i++)
	{
		inputWs.push_back(rand() / double(RAND_MAX) - 0.5);  //initialized with a random weight -0.5~0.5
		
	}
	delta=0;
}





#endif 