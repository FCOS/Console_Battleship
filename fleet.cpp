#include "fleet.h"

//Constructor
fleet::fleet() {

	for (int i = 0; i < MAX_FLEET_SIZE; i++) {
		ships[i] = 0;
	}
	alive = false;

}

//checks if fleet is still alive
bool fleet::is_alive() {
	for (int i = 0; i < MAX_FLEET_SIZE; i++) {
		if (ships[i]->alive == true) {
			return true;
		}
	}
	return false;
}