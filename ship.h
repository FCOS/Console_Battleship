#pragma once
const int MAX_SIZE = 5;


class battle_ship {
public:
	int bow_x;
	int bow_y;
	int size;
	int vertical;
	int horizontal;
	bool placed=false;
	bool hit[MAX_SIZE];

	bool alive;

	battle_ship(int start_x, int start_y, int size, int dir);
	void is_alive();
};