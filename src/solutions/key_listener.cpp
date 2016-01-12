#include "key_press_t.hpp"
#include "common/timestamp.h"
#include <iostream>
#include <lcm/lcm-cpp.hpp>

using namespace std;

class Handle{
public:
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
		cout << "System time: " << messagesRecieved / ((-startSystem + utime_now()) / 60000) << endl;
		cout << "Producer time: " << messagesRecieved / ((-startProducer + msg->timestamp) / 60000) << endl;
	}
private:
	int messagesRecieved = 0;
	int64_t startProducer = 0;
	int64_t startSystem = 0;
};

int main(int argc, char** argv){
	lcm::LCM lcm;
	if(!lcm.good()){
		return 1;
	}
	while(0 == lcm.handle());
	return 0;
}
