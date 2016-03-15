#include<iostream>
#include<vector>
#include "readindata.h"
#include "Net.h"
using namespace std;

int main()
{

	srand(time(0));
		//string in="./data/mush/dataConforMsh.txt";
	//string out="./data/mush/output2.txt";

	//string in="./data/nursery/dataConforNur.txt";
	//string out="./data/nursery/output2.txt";
	
	//string in="./data/vote/dataConforVote.txt";
	//string out="./data/vote/output3.txt";

	//string in="./data/blog/dataConforBlog.txt";
	//string out="./data/blog/output3.txt";

	string in="./data/car/dataConforCar.txt";
	string out="./data/car/output.txt";


	ofstream myfile (out);
	myfile<<"Read in Control File from: "<<in<<endl;
	readindata a(in);
	myfile<<"Complete!"<<endl;
	a.printData();
	a.getNumData();   //convert data to input data
	
	
	//construct net
	vector<int> net;
	net.push_back(a.numOfAttr-1); //input nodes:each has 1 node with k values(scale to 0-1)
	net.push_back(10);   //hidden nodes
	net.push_back(5);
	net.push_back(a.attrVal[a.targetAttr].size());  //output nodes
	Net ANN(net);
	ANN.printNet();

	//training
	int n=0;
	while(n<300){
		for(int i=0;i<a.numdata.size();i++)
		{
		//cout<<i<<": "<<a.numdata[i].size()<<endl;
			ANN.forward(a.numdata[i]);
			ANN.backward(a.output[i]);
			ANN.update();
		}
		//cout<<n<<endl;
		n++;
	}


	//validation
	vector<double> res;
	int acc=0;
	for(int i=0;i<a.numdata.size();i++)
	{
		//cout<<i<<": "<<a.numdata[i].size()<<endl;
		ANN.forward(a.numdata[i]);
		ANN.getResults(res);
		
		double max=0;
		int maxIn=0;
		for(int i=0;i<res.size();i++)
		{
			if(res[i]>max){
				max=res[i];
				maxIn=i;
			}
		}
		if(a.output[i][maxIn]==1) acc++;

	}
	cout<<(double)acc/a.numdata.size()<<endl;


	cout<<"Hello World!";
}


void test1(){

	vector<int> net;
	net.push_back(3);
	//net.push_back(2);
	net.push_back(2);
	Net ANN(net);
	


	vector<double> tuple;
	tuple.push_back(0.7);
	tuple.push_back(0.5);
	tuple.push_back(0.9);
	
	
	vector<double> res;



	vector<double> target;
	target.push_back(0.5);
	target.push_back(0.5);


	for(int i=0;i<1000;i++)
	{
		ANN.forward(tuple);
		//ANN.printNet();
		ANN.backward(target);
		ANN.update();
	}

	ANN.getResults(res);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<endl;	
	}
	
}