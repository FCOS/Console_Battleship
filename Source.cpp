//Fergal O'Shea
//12-2016

#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include "ship.h"
#include "fleet.h"

//some variables
const int board_width = 24;
const int board_size = 12;
bool game_over = false;

//set up the board
struct Board {

	char line1[board_width] =  { "   0 1 2 3 4 5 6 7 8 9 " };
	char line2[board_width] =  { "A                      " };
	char line3[board_width] =  { "B                      " };
	char line4[board_width] =  { "C                      " };
	char line5[board_width] =  { "D                      " };
	char line6[board_width] =  { "E                      " };
	char line7[board_width] =  { "F                      " };
	char line8[board_width] =  { "G                      " };
	char line9[board_width] =  { "H                      " };
	char line10[board_width] = { "I                      " };
	char line11[board_width] = { "J                      " };

	char* rows[board_size] = { line1,line2,line3,line4,line5,line6,line7,line8,line9,line10, line11 };
};

//functions
void place_pieces(Board* board, fleet* player);
bool is_valid_move(fleet* player, battle_ship* ship);
void make_move(Board* board, fleet* player);

int main() {
	int turn = 1;
	//sets up first players pieces
	std::cout << "Player 1, prepare to place your pieces. Player 2, look away.";
	std::cout << "\nPlacing in 5, "; Sleep(1000);
	std::cout << "4, "; Sleep(1000);
	std::cout << "3, "; Sleep(1000);
	std::cout << "2, "; Sleep(1000);
	std::cout << "1, "; Sleep(1000);
	std::cout << "0 "; Sleep(1000);
	//creates a new fleet
	fleet* player_1 = new fleet;
	//cerates board for fleet
	Board* board1 = new Board;
	//sets up board
	place_pieces(board1, player_1);
	player_1->alive = true;


	//same, for p2
	std::cout << "Player 2, prepare to place your pieces. Player 1, look away.";
	std::cout << "\nPlacing in 5, "; Sleep(1000);
	std::cout << "4, "; Sleep(1000);
	std::cout << "3, "; Sleep(1000);
	std::cout << "2, "; Sleep(1000);
	std::cout << "1, "; Sleep(1000);
	std::cout << "0 "; Sleep(1000);
	fleet* player_2 = new fleet;
	Board* board2 = new Board;
	place_pieces(board2, player_2);
	player_2->alive = true;

	//runs while game is not over
	while (!game_over) {
		//p1 go
		std::cout << "It is player 1's turn. Player 2, look away now.";
		Sleep(3000);
		make_move(board1, player_2);

		//p2 go
		std::cout << "It is player 2's turn. Player 1, look away now.";
		Sleep(3000);
		make_move(board2, player_1);

	}
}


void place_pieces(Board* board, fleet* player) {
	//place all 5 ships
	for (int i = 1; i < 6; i++) {
		//starts ship in center
		int x = 5;
		int y = 5;
		int dir;
		int size = i;

		if (i == 1) {
			size = 2;
		}
		else if (i == 2) {
			size = 3;
		}

		//decide if vertical of hor
		std::cout << "\nPlease enter a direction. 1 for horizontal, 0 for vertical";
		std::cin >> dir;
		while (dir != 1 && dir != 0) {
			std::cout << "\nInvalid direction. 1 for Horizontal, 0 for Vertical :";
			std::cin >> dir;
		}

		//make new ship
		battle_ship* new_ship = new battle_ship(x, y, size, dir);

		//while ship is not placed
		while (!new_ship->placed) {
			Board* board = new Board;

			//if keys are pressed
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_RSHIFT)) {
				//limits to stop going off board, otherwise if left, go left etc
				if (dir == 0) {
					if (GetAsyncKeyState(VK_UP)) {
						if (new_ship->bow_y > 0) {
							new_ship->bow_y--;
						}
					}
					if (GetAsyncKeyState(VK_DOWN)) {
						if ((new_ship->bow_y + size - 1) < 9) {
							new_ship->bow_y++;
						}
					}
					if (GetAsyncKeyState(VK_LEFT)) {
						if (new_ship->bow_x > 0) {
							new_ship->bow_x--;
						}
					}
					if (GetAsyncKeyState(VK_RIGHT)) {
						if (new_ship->bow_x < 9) {
							new_ship->bow_x++;
						}
					}
				}
				else {
					if (GetAsyncKeyState(VK_UP)) {
						if (new_ship->bow_y > 0) {
							new_ship->bow_y--;
						}
					}
					if (GetAsyncKeyState(VK_DOWN)) {
						if (new_ship->bow_y < 9) {
							new_ship->bow_y++;
						}
					}
					if (GetAsyncKeyState(VK_LEFT)) {
						if (new_ship->bow_x > 0) {
							new_ship->bow_x--;
						}
					}
					if (GetAsyncKeyState(VK_RIGHT)) {
						if ((new_ship->bow_x+size-1) < 9) {
							new_ship->bow_x++;
						}
					}
				}
				//confirm placement
				if (GetAsyncKeyState(VK_RSHIFT)) {
					if (is_valid_move(player, new_ship)) {
						new_ship->placed = true;
					}
					else {
						std::cout << "Invlaid move, Ships may not be places on top of eachother";
						Sleep(1500);
					}
				}

			}

			//diplays current location of ship were placing
			for (int h = 0; h < new_ship->size; h++) {
				//fancy math
				board->rows[(new_ship->bow_y + 1) + ((h)*new_ship->vertical)][((new_ship->bow_x*2) + 3) + ((h*new_ship->horizontal) * 2)] = (char)178u;
				board->rows[(new_ship->bow_y + 1) + ((h)*new_ship->vertical)][((new_ship->bow_x * 2) + 4) + ((h*new_ship->horizontal) * 2)] = (char)178u;
				
			}

			//draws ships that are already placed
			int k = 0;
			while (player->ships[k] != NULL) {
				for (int f = 0; f < player->ships[k]->size;f++) {
					board->rows[(player->ships[k]->bow_y + 1) + ((f)*player->ships[k]->vertical)][((player->ships[k]->bow_x * 2) + 3) + ((f*player->ships[k]->horizontal) * 2)] = (char)178u;
					board->rows[(player->ships[k]->bow_y + 1) + ((f)*player->ships[k]->vertical)][((player->ships[k]->bow_x * 2) + 4) + ((f*player->ships[k]->horizontal) * 2)] = (char)178u;
				
							
				}
				k++;
			}

			//clears console
			system("cls");
			//this is actual print part. runs thorugh each row
			for (int p = 0; p < board_size - 1; p++) {
				std::cout << board->rows[p] << std::endl;
			}
			std::cout << "Use arrow keys to move ship, right shift to confirm placement";
		}
		//store ship in player
		player->ships[i-1] = new_ship;
	}

	system("cls");
}

void make_move(Board* board, fleet* player) {
	//clear console
	system("cls");
	std::string move;
	std::cout << "Make your move (in the form 'A4') :\n";

	//print board
	for (int p = 0; p < board_size - 1; p++) {
		std::cout << board->rows[p] << std::endl;
	}

	//get move
	std::cin >> move;

	//checks if valid
	if (move.size() != 2 || move[0] < 'A' || move[0] > 'J' || move[1] <'0' || move[1] > '9') {
		std::cout << "\nInvalid move, Please enter a valid move";
		std::cin >> move;
	}

	//converts char to int using ascii
	int x = move[1] - 48; //(0-9)
	int y = move[0] - 64; //(0-9)

	//for each ship
	for(int i =0;i<5;i++){
		//each pieace if ship
		for (int f = 0; f < player->ships[i]->size; f++) {
			//checks if piece is in x, y
				if (x == (player->ships[i]->bow_x) + (f*player->ships[i]->horizontal) && (y-1) == (player->ships[i]->bow_y) + (f*player->ships[i]->vertical)) {
					//set to hit, change board to full square
					player->ships[i]->hit[f] = true;
					board->rows[y][3 + (2*x)] = (char)178u;
					board->rows[y][4 + (2*x)] =  (char)178u;
				}
		}
	}

	//if not hit, give square half full paint
	if (board->rows[y][3 + (2 * x)] == ' ') {
		board->rows[y][3 + (2 * x)] = (char)176u;
		board->rows[y][4 + (2 * x)] = (char)176u;
	}

	//prints board with hits
	for (int p = 0; p < board_size - 1; p++) {
		std::cout << board->rows[p] << std::endl;
	}

	//checks if ships are still alive
	for (int i = 0; i < 5; i++) {
		player->ships[i]->is_alive();
	}

	//checks if player alive
	if (!(player->is_alive())) {
		//if player dead, set game over to false
		game_over = true;
		std::cout << "game over";
		Sleep(10000);
	}

	Sleep(5000);
	system("cls");

}

bool is_valid_move(fleet* player, battle_ship* ship) {
	//checks if one ship is on top of the other
	int i = 0;
	//for each ship
	while (player->ships[i] != NULL) {
		//for each segment of already placed ship
		for (int f = 0; f < player->ships[i]->size; f++) {
			//for each seg of ship being placed
			for (int t = 0; t < ship->size; t++) {
				//checks if =
				if ((ship->bow_x) + (t*ship->horizontal) == (player->ships[i]->bow_x) + (f*player->ships[i]->horizontal) && (ship->bow_y) + (t*ship->vertical) == (player->ships[i]->bow_y) + (f*player->ships[i]->vertical)) {
					//if equal, invalid move
					return false;
				}
			}
		}
		i++;
	}
	return true;
}
