#define LOG_TAG "Main"
 
#include <utils/Log.h>
#include <utils/threads.h>
#include "MyThread.h"
 
using namespace android;
 
int main()
{
	sp<MyThread>  thread = new MyThread;
	thread->run("MyThread", PRIORITY_URGENT_DISPLAY);
	while(1){
	   if (!thread->isRunning()) {
		ALOGD("main thread->isRunning == false");
		break;	   
	    }	
        }
	ALOGD("main end");
	return 0;
}
