#ifndef _NET_H
#define _NET_H

#include "Layer.h"
class Net{
private:
	int numOfL;       //number of layers
	vector<Layer> layers;
public:
	void printNet();
	Net(const vector<int> net);
	void getResults(vector<double> &res);
	void forward(vector<double> &tuple);
	void backward(vector<double> &res);

};

void Net::printNet()
{
	for(int i=0;i<layers.size();i++)
	{
		cout<<"Layer "<<i<<" :"<<endl;
		layers[i].printLayer();
		cout<<endl;
	}
	

}

void Net::getResults(vector<double> &res)
{
	res.clear();
	for (int i = 1; i < layers[numOfL-1].nodes.size();i++) {
		res.push_back(layers[numOfL-1].nodes[i].output);
    }
}

Net::Net(const vector<int> net)
{
	numOfL=net.size();
	for(int i=0;i<numOfL;i++)
	{
		layers.push_back(Layer());  //add layers
		cout<<"Made a layer "<<i<<endl;
		for(int j=0;j<=net[i];j++)    //contains a bias input
		{
			layers[i].nodes.push_back(Node((i==0||j==-0)?0:net[i-1]+1));  //input layer's node and bias node don't have inputs
			if(j==0)layers[i].nodes[j].output=1; //bias initialized with 1
			cout<<"Made a Node in "<<i<<endl;
		}
	}
}

void Net::forward(vector<double> &tuple)
{
	if(tuple.size()!=layers[0].nodes.size()-1) 
	{
		cout<<"Invalid input tuple."<<endl;
		return;
	}

	
	for(int i=0;i<tuple.size();i++)           //initialized the input
		layers[0].nodes[i+1].output=tuple[i];
	

	for(int i=1;i<layers.size();i++)  //for every layer
	{
		//for every node in this layer except bias node
		for(int j=1;j<layers[i].nodes.size();j++)    //0 is bias node
		{
			layers[i].nodes[j].update();
			double sum=0;
			for(int k=0;k<layers[i-1].nodes.size();k++)
			{
				sum+=layers[i-1].nodes[k].output*layers[i].nodes[j].inputWs[k];
				
			}
			layers[i].nodes[j].output=1.0 / (1.0 + exp(-sum));  //sigmoid
		}
	}


}



#endif 