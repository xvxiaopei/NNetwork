#include<iostream>
#include<vector>
#include<assert.h>
#include "readindata.h"
#include "Net.h"
using namespace std;

double MSE(vector<double> vali,vector<double> res)
{

	assert(vali.size()==res.size());
	double sum=0;
	for(int i=0;i<vali.size();i++)
	{
		sum+=pow(res[i]-vali[i],2);
	}
	return sum/vali.size();

}

void AN(string in,string out,vector<int> net)
{
	/****************************************read in data**************************************/
	ofstream myfile (out);
	myfile<<"Read in Control File from: "<<in<<"...";
	readindata a(in);
	myfile<<"Complete!"<<endl;
	a.shuffleData();     //randomly shuffle
	a.printData();
	//a.getNumData();   //convert data to input data
	/****************************************read in data**************************************/


	/****************************************construct net**************************************/
	//
	myfile<<"ConstructANN...";
	net.insert(net.begin(),a.numOfAttr-1); //input nodes:each has 1 node with k values(scale to 0-1)
	net.push_back(a.attrVal[a.targetAttr].size());  //output nodes
	Net T(net);
	myfile<<"Complete!"<<endl;
	T.printNet();
	myfile<<"Num of layers: "<<T.layers.size()<<endl;
	for(int i=0;i< T.layers.size();i++)
	{
		myfile<<"Layer "<<i<<" has "<<T.layers[i].nodes.size()-1<< " nodes."<<endl;
	}
	myfile<<"Learning rate is "<<T.learningRate<<endl;
	/****************************************construct net**************************************/


	/**************************************** ten fold ******************************************/
	for(int i=0;i<10;i++)
	{        
		cout<<i<<" fold"<<endl;
		Net ANN(net);
		vector<readindata> div=a.divide(i);    //3 dataset :train 60%; validation 30%; test 10%
		//for(int i=0;i<div.size();i++)  div[i].printData();
		for(int k=0;k<3;k++) {div[k].getNumData();}
		myfile<<i<<" th fold------------------------------------------------------\n";

		/**************************************** training **************************************/
		// first 10 times
		int n=0;
		while(n<200){
			for(int i=0;i<div[0].numdata.size();i++)
			{
			//cout<<i<<": "<<a.numdata[i].size()<<endl;
				ANN.forward(div[0].numdata[i]);
				ANN.backward(div[0].output[i]);
				ANN.update();
			}
			//cout<<n<<endl;
			n++;
		}


		//stop criterion(validation data)
		double lastMSE=0;
		double curMSE=INT_MAX;
		vector<double> res;
		do{                               
			lastMSE= curMSE;
			curMSE=0;
			for(int i=0;i<div[0].numdata.size();i++)  //validation
			{
			//cout<<i<<": "<<a.numdata[i].size()<<endl;
				ANN.forward(div[0].numdata[i]);
				ANN.backward(div[0].output[i]);
				ANN.update();
			}

			for(int i=0;i<div[1].numdata.size();i++) //training
			{
				//cout<<i<<": "<<a.numdata[i].size()<<endl;
				ANN.forward(div[1].numdata[i]);
				ANN.getResults(res);
				curMSE+=MSE(div[1].output[i],res);
			}
			curMSE/=div[1].numdata.size();
			n++;
			if(n%50==0) {cout<<n<<" : "<<curMSE<<endl;}
			if(n>500) break;
			if((lastMSE-curMSE)/lastMSE<0.000002)break;
		}while(curMSE<lastMSE);
	   /**************************************** training **************************************/
		myfile<<n<<" iterations, accuracy: ";
       /**************************************** test ******************************************/
		int acc=0;
		for(int i=0;i<div[2].numdata.size();i++)
		{
		//cout<<i<<": "<<a.numdata[i].size()<<endl;
			ANN.forward(div[2].numdata[i]);
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
			if(div[2].output[i][maxIn]==1) acc++;

		}
		//cout<<acc<<" / "<<div[2].numdata.size()<<" = ";
		myfile<<(double)acc/div[2].numdata.size()<<endl;


	   /**************************************** test ******************************************/
	}
    /**************************************** ten fold ******************************************/
	myfile.close();
}


int main()
{

	srand(time(0));
	string in,out;
	vector<int> net;
	



	cout<<"1.Car Evaluation Data Set (http://archive.ics.uci.edu/ml/datasets/Car+Evaluation)"<<endl;
    cout<<"2.Nursery Data Set (http://archive.ics.uci.edu/ml/datasets/Nursery)"<<endl;
	cout<<"3.BLOGGER Data Set (http://archive.ics.uci.edu/ml/datasets/BLOGGER#)"<<endl;
	cout<<"4.Mushroom Data Set (http://archive.ics.uci.edu/ml/datasets/Mushroom)"<<endl;
	cout<<"5.Congressional Voting Records Data Set(http://archive.ics.uci.edu/ml/datasets/Congressional+Voting+Records)"<<endl;
	cout<<"Please choose the dataset:";
	
	int choose=0;
	cin>>choose;
	switch (choose)
	{
		case 1:{in="./data/car/dataConforCar.txt";out="./data/car/output.txt";break;}
		case 2:{in="./data/nursery/dataConforNur.txt";out="./data/nursery/output.txt";break;} 
		case 3:{in="./data/blog/dataConforBlog.txt"; out="./data/blog/output.txt";break;}
		case 4:{in="./data/mush/dataConforMsh.txt";out="./data/mush/output.txt";break;}
		default:{in="./data/vote/dataConforVote.txt"; out="./data/vote/output.txt";break;}
	}

	int numofLayer=0;

	cout<<"Please enter the num of hidden layers: ";
	cin>>numofLayer;
	
	for(int i=0;i<numofLayer;i++)
	{
		int x;
		cout<<"Please enter num of nodes in hidden layer "<<i+1<<": ";
		cin>>x;
		net.push_back(x);
	}
	AN(in,out,net);

	
	
	

	

	/*
	in="./data/car/dataConforCar.txt";

 out="./data/car/outputL0.txt";
 AN(in,out,net);

 out="./data/car/outputL1_5.txt";
 net.push_back(5);
 AN(in,out,net);

 out="./data/car/outputL1_10.txt";
 net[0]=10;
 AN(in,out,net);

 out="./data/car/outputL1_5_L2_5.txt";
 net[0]=5;
 net.push_back(5);
 AN(in,out,net);
 out="./data/car/outputL1_5_L2_10.txt";
 net[1]=10;
 AN(in,out,net);

 out="./data/car/outputL1_10_L2_10.txt";
 net[0]=10;
 AN(in,out,net);

 */


/*
 //vote
 net.clear();
 in="./data/vote/dataConforVote.txt";

 out="./data/vote/outputL0.txt";
 AN(in,out,net);

 out="./data/vote/outputL1_5.txt";
 net.push_back(5);
 AN(in,out,net);

 out="./data/vote/outputL1_10.txt";
 net[0]=10;
 AN(in,out,net);

 out="./data/vote/outputL1_5_L2_5.txt";
 net[0]=5;
 net.push_back(5);
 AN(in,out,net);

 out="./data/vote/outputL1_5_L2_10.txt";
 net[1]=10;
 AN(in,out,net);

 out="./data/vote/outputL1_10_L2_10.txt";
 net[0]=10;
 AN(in,out,net);


 //nursery
 net.clear();
 in="./data/nursery/dataConforNur.txt";
 
 out="./data/nursery/outputL0.txt";
 AN(in,out,net);

 out="./data/nursery/outputL1_5.txt";
 net.push_back(5);
 AN(in,out,net);

 out="./data/nursery/outputL1_10.txt";
 net[0]=10;
 AN(in,out,net);
	

	/*
	//blog
	net.clear();
	in="./data/blog/dataConforBlog.txt"; 

	out="./data/blog/outputL0.txt";
	AN(in,out,net);

	out="./data/blog/outputL1_5.txt";
	net.push_back(5);
	AN(in,out,net);

	out="./data/blog/outputL1_10.txt";
	net[0]=10;
	AN(in,out,net);
	*/


	//mush
	/*
	net.clear();
	in="./data/mush/dataConforMsh.txt";

	out="./data/mush/outputL0.txt";
	AN(in,out,net);

	out="./data/mush/outputL1_5.txt";
	net.push_back(5);
	AN(in,out,net);

	out="./data/mush/outputL1_10.txt";
	net[0]=10;
	AN(in,out,net);
	*/
	

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