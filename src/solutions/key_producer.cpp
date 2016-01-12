#include "key_press_t.hpp"
#include "common/timestamp.h"
#include <iostream>
#include <lcm/lcm-cpp.hpp>

using namespace std;

int main(){
	system("stty raw -echo");
	lcm::LCM lcm;
	if(!lcm.good()){
		return 1;
	}
	key_press_t press;
	char input;
	while(1){
		cin >> input;
		press.character = (int8_t)input;
		press.timestamp = utime_now();
		lcm.publish("A0_KEY_PRESS", &press);
	}
}
