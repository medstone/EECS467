#include "key_press_t.hpp"
#include <sys/time.h>

using namespace std;

int main(){
	lcm::LCM lcm;
	if(!lcm.good){
		return 1;
	}
	key_press_t press;
	char input;
	timeval stamp;
	while(1){
		cin >> input;
		press.character = (int8_t)input;
		gettimeofdat(&stamp, NULL);
		press.timestamp = stamp.tv_usec;
		cout << press.character << " " << press.timestamp << endl;
	}
}
