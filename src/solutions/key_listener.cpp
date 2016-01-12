#include "key_press_t.hpp"
#include "common/timestamp.h"
#include <iostream>
#include <lcm/lcm-cpp.hpp>

using namespace std;

class Handle{
public:

	Handle(){
		messagesRecieved = 0;
		startProducer = 0;
		startSystem = 0;
	}

	void recieve(const lcm::ReceiveBuffer* rbuf,
       			const std::string& chan, 
                 	const key_press_t* msg){
		messagesRecieved++;
		if(startProducer == 0 && startSystem == 0){
			startSystem = utime_now();
			startProducer = msg->timestamp;
			cout << "System time: 1 word per minute/n";
			cout << "Producer time: 1 word per minute/n";
			return;
		}
		double sysTime = ((utime_now() - startSystem) / 60000000.0);
		double prodTime = ((msg->timestamp - startProducer) / 60000000.0);
		if(sysTime == 0 || prodTime == 0){
			cout << "System time: " << messagesRecieved << endl;
			cout << "Producer time: " << messagesRecieved << endl;
			return;
		}
		cout << "System time: " << (double)(messagesRecieved) / sysTime << endl;
		cout << "Producer time: " << (double)(messagesRecieved) / prodTime << endl;
	}
private:
	int messagesRecieved;
	int64_t startProducer;
	int64_t startSystem;
};

int main(int argc, char** argv){
	lcm::LCM lcm;
	if(!lcm.good()){
		return 1;
	}
	Handle hand;
	lcm.subscribe("A0_KEY_PRESS", &Handle::recieve, &hand);
	while(0 == lcm.handle());
	return 0;
}
