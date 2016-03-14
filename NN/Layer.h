#ifndef _LAYER_H
#define _LAYER_H
#include "Node.h"
class Layer{
public:
	vector<Node> nodes;
	void printLayer();
};

void Layer::printLayer(){

	for(int i=1;i<nodes.size();i++)
	{
		cout<<"node "<<i<<" : ";
		nodes[i].printNode();
	}
	return;

}
#endif 