#define LOG_TAG "MyThread"
 
#include <utils/Log.h>
#include "MyThread.h"
 
namespace android {
 
	MyThread::MyThread() :
			Thread(false) {
		ALOGD("MyThread");
	}
	  
	bool MyThread::threadLoop() {
		ALOGD("threadLoop hasRunCount = %d",hasRunCount);
		hasRunCount++;
		if (hasRunCount == 10) {
			return false;		
		}
		return true;
	}
	void MyThread::onFirstRef() {
		ALOGD("onFirstRef");
	}
	status_t MyThread::readyToRun() {
		ALOGD("readyToRun");
		return 0;
	}
	void MyThread::requestExit() {
		ALOGD("requestExit");
	}
}
