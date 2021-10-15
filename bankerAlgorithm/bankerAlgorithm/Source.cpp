#include <iostream>
#include <cmath>
#include <string>
#include <conio.h>
using namespace std;

// global variables 
int i =0; // counter
int j=0;
int k=0;
int n = 0; // number of processes
int m =0; // number of resources
int maxMatrix[100][100]; // max requests of the process 
int allocationMatrix[100][100]; // allocation matrix 
int needMatrix[100][100]; // need matrix = max-alloc
int available[100]; // availabillity matrix
int resultmatrix[100]; // to cout the sequence of processes
int finished[100]; // flag matrix
bool safe=true; // check safety
int flag=0; // to check if all need elemnts < available elements
int index=0; // index of the result matrix
int enquiry=0; // check the user selection
int processEnquiry;// immediate process number
int requested[100];// request array
int requestFlag=0;
int requestFlag_2=0;

// functions
// show error 
void showerror()
{
	cout<<"ERROR";
	exit(0);
}
// processes and resources number 
void get_m_n()
{
	// get number of processes and resources
	cout<< "Please enter your processes number \n";
	cin>>n;
	// get number of resources
	cout<< "Please enter your resources number \n";
	cin>>m;
}
// function allocation matrix
void getAllocationMatrix()
{
	cout << "Please enter your Allocation matrix \n ";
	for (i=0; i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			cin>>allocationMatrix[i][j];
		}
	}
}
// function max matrix
void getMaxMatrix()
{
	cout << "Please enter your Max matrix \n ";
	for (i=0; i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			cin>> maxMatrix[i][j];
		}
	}
}
// availability
void getAvailability()
{
	cout<<"please enter your available matrix \n";
		for(i=0;i<m;i++)
		{
			cin>>available[i];
		}
}
// need matrix
void setNeedMatrix()
{
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			needMatrix[i][j]=maxMatrix[i][j]-allocationMatrix[i][j];
		}
	}
}
// print need matrix
void printNeed ()
{
	cout<<"The need matrix is: \n";
	// table
	for(i=0;i<m;i++)
	{
		cout<<"  R"<<i;
	}
	cout<<"\n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if (j==0)
			{
				cout<<"P"<<i<<" ";
			}
			cout<<needMatrix[i][j]<<"   ";
		}
		cout<<"\n";
	}
}
// intializing flag matrix "finished"to check if all processes have finished
void setFinished()
{
	for(i=0;i<n;i++)
	{
		finished[i]=0;
	}
}
// get user's enquiry
void userEnquiry()
{
	cout<<"please to check if the system is in a safe state press 0, for immediate request press 1: ";
	cin>>enquiry;
}
// banker with time complexity n^2 * m o(n^2 * m)
void banker()
{
	for(k=0;k<n;k++)
	{
		for (i=0;i<n;i++)
		{		
			flag=0;
			if (finished[i]== 0 )
			{
				for(j=0;j<m;j++)
				{
					// check if any element int the need matrix is greater than the available
					if (needMatrix[i][j]>available[j])
					{
						flag=1;
						break;
					}
				}
				if(flag == 0)
				{
					for(j=0;j<m;j++)
					{
						available[j]= available[j] + allocationMatrix[i][j];
					}
					finished[i]=1; // set process finished 
					resultmatrix[index]=i; // to print the sequence
					index++;				
				}
			}
		}
	}
	
}
// check safety 
void checkSafety()
{
	for(i=0;i<n;i++)
	{
		if (!finished[i])
		{
			safe=false;
		}
	}
}
// immediate request
void immediateRequest()
{
	cout<<"please enter the process number: \n";
	cin>>processEnquiry;
	cout<<"please enter the process request: \n";
	for(j=0;j<m;j++)
	{
		cin>> requested[j];
	}
	// check if the request is less than availabe
	for(j=0;j<m;j++)
	{
		if (requested[j]>needMatrix[processEnquiry][j])
		{
			requestFlag=1;
			
			break;
		}
	}
	if (requestFlag==0)
	{
		// check if requested is less than available
		for(j=0;j<m;j++)
		{
			if (requested[j]>available[j])
			{
				requestFlag_2=1;
				break;
			}
		}
		// this means requested can be granted
		if (requestFlag_2==0)
		{
			// available = available-request 
			for(j=0;j<m;j++)
			{
				available[j]=available[j]-requested[j];
				allocationMatrix[processEnquiry][j]=allocationMatrix[processEnquiry][j]+requested[j];
				needMatrix[processEnquiry][j]=needMatrix[processEnquiry][j]- requested[j];
			}
			banker();
		}
	}
	



}
// print result
void printResult()
{
	if (enquiry==0)
	{
		// start of safety algorithm
		banker();
		// end of safety algorithm
		
		// check safety; 
		checkSafety();
	
		if (safe)
		{
			cout<<"Yes, safe state <";
			for (i=0;i<n;i++)
			{
				cout<<"P"<<resultmatrix[i];
				if(i != n-1)
				{
					cout<<",";
				}
			}
			
			cout<<">";
		}
		else 
			cout<<"the system is not in a safe state"; 
	}
	else if (enquiry==1)
	{
		// request algorithm
		immediateRequest();
			//banker();
			checkSafety();
	
			if (safe)
			{
				cout<<"Yes request can be granted with safe state <P"<<processEnquiry<<"req,";
				for (i=0;i<n;i++)
				{
					cout<<"P"<<resultmatrix[i];
					if(i != n-1)
					{
						cout<<",";
					}
				}
			
				cout<<">";
			}
			else 
				cout<<"No, request can't be granted immediately";

		}

	else
	{
		showerror();
	}
}
// main
int main()
{
	// start of getting m and n
	get_m_n();
	// end of getting m and n 

	// satrt of getting allocation matrix
	getAllocationMatrix();
	// end of getting allocation matrix
	
	// satrt of getting max matrix
	getMaxMatrix();
	// end of getting max matrix

	// satrt of getting availability matrix
	getAvailability();
	// end of getting availability matrix

	// start printing need matrix
	setNeedMatrix();
	printNeed();
	// end of printing need matrix

	// start of initializing 
	setFinished();
	// end of initializing

	// check the user's enquiry
	userEnquiry();
	// end of user enquiry

	//start of printing result
	printResult();
	// end of printing the result 
	cout<<"\n";
	getch();
	return 0;
}
