#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "SharedObject.h"




using namespace std;
//The shared values that will be used for all threads between the writer and reader
struct MyShared{
	int threadID, reportID, timePassed;
};

int main(void)
{
	std::cout << "I am a reader" << std::endl;
	//declare a memory variable so the thread can access it 
	Shared<MyShared> sharedMemory ("sharedMemory");
	
	while(true){
	
	        
		
		cout << "Reader Thread: " << sharedMemory -> threadID << " " << sharedMemory -> reportID << " " << sharedMemory -> timePassed << endl;
		
		sleep(1);
	}
	
	return 0;
}
