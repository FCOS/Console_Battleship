#pragma once
#include"ship.h"

const int MAX_FLEET_SIZE = 5;


class fleet {

public:

	battle_ship* ships[MAX_FLEET_SIZE];
	bool alive;

	fleet();
	bool is_alive();

};