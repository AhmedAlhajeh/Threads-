#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "thread.h"
#include "SharedObject.h"
using namespace std;

struct MyShared{
//The shared values that will be used for all threads between the writer and reader
	int threadID, reportID, timePassed;
};

class WriterThread : public Thread{
	public:
		bool	flag;
		int 	ThreadNumber;
		int	ThreadDelay;
		
		WriterThread(int number, int DelayTime):Thread(8*1000){
			this->ThreadNumber = number;
			this->ThreadDelay = DelayTime;
		}
                //memory that will contain all the shared variables for threads
		virtual long ThreadMain(void) override{
			//declare a memory variable so the thread can access it 
			Shared<MyShared> sharedMemory ("sharedMemory");
			//reportID will start counting from 1
			int reportID = 1;

			while(true)
			{
				if(flag){//Exit loop to end the thread
					break;
				}
				
				//making sure the properties of the threads we are dealing with can be shared
				sharedMemory->threadID = ThreadNumber;
				sharedMemory->reportID = reportID;
				sharedMemory->timePassed = ThreadDelay;
				
				reportID++; //incrementing
				
				sleep(ThreadDelay);
			}
			return 0;
		}
};

int main(void)
{
	int threadId = 1;
	vector<WriterThread*> WriterArray; //Creating an array for threads
	
	std::cout << "I am a Writer" << std::endl;
	
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	
	while(true){
		int N; //sleep time
		string DataInput;
		
		cout << "Would you like to create a writer thread?";
		cin >> DataInput;
		if(DataInput == "yes" || DataInput == "y"){
			//Create a thread with sleep time N
			cout << "What is the delay time for this thread?";
			cin >> N;
			//using user input to create threads
			WriterThread* thread = new WriterThread(threadId, N);
			//incarementing thread ID evrytime we say yes 
			threadId++;
			WriterArray.push_back(thread); //adding thread to the array
		}
		else if(DataInput == "no"){
			//cancel the threads, wait for them to die, and exit. 
			int j = WriterArray.size();
			for(int i = 0; i < j; i++){
				WriterArray[i]->flag = true;
				delete WriterArray[i];
			}	
			break;
		}
		else{
			cout << " Invalid input. Enter either (yes/y) or no";
		}
	}
	return 0;
}




