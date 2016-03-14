#include<iostream>
#include<vector>
#include "readindata.h"
#include "Net.h"
using namespace std;

int main()
{

	
	vector<int> net;
	net.push_back(3);
	net.push_back(2);
	net.push_back(2);
	Net ANN(net);
	


	vector<double> tuple;
	tuple.push_back(200);
	tuple.push_back(1);
	tuple.push_back(1);
	ANN.forward(tuple);
	ANN.printNet();
	
	vector<double> res;

	ANN.getResults(res);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<endl;	
	}


	cout<<"Hello World!";
}