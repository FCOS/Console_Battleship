#include "ship.h"

//constructor
battle_ship::battle_ship(int start_x, int start_y, int _size, int _dir) {
	//x an y of the bow of the ship
	bow_x = start_x;
	bow_y = start_y;
	size = _size;
	//this sets 2 variables used for maths later
	if (_dir == 1) {
		horizontal = 1;
		vertical = 0;
	}
	else {
		horizontal = 0;
		vertical = 1;
	}
	
	//sets up variables
	for (int i = 0; i < size; i++) {
		hit[i] = false;
	}
	alive = true;
	placed = false;

}

//check if ship is still alive
void battle_ship::is_alive() {
	for (int i = 0; i < size; i++) {
		if (hit[i] == false) {
			return;
		}
	}
	alive = false;
	return;
}