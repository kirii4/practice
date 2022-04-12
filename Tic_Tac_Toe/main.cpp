#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <string.h>
#include <random>
#include <chrono>

int32_t __fastcall getRandomNum(int32_t min, int32_t max)
{
	const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937_64 generator(seed);
	std::uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}

enum Field : char {
	EMPTY = '-',
	X = 'X',
	O = 'O'
};	

enum GameStage {
	IN_PROGRESS,
	DRAW,
	CPU_WON,
	PLAYER_WON
};

#pragma pack(push,1)
typedef struct tic_tac_toe {
	Field playingField[3][3];
	Field player, cpu;
	GameStage stage{ IN_PROGRESS };
	uint8_t step;
}game;
#pragma pack(pop)

typedef struct Coord {
	size_t x{0U};
	size_t y{0U};
}coord;

void __fastcall startgame(game& play) {
	for (auto i = 0U; i < 3; i++) {
		for (auto j = 0U; j < 3; j++) {
			play.playingField[i][j] = EMPTY;
		}
	}
	
	if (getRandomNum(1, 1000) > 500) { // player first
		play.player = X;
		play.cpu = O;
		play.step = 0;
	}else {		// cpu first
		play.player = O;
		play.cpu = X;
		play.step = 1;
	}
}

void __fastcall playerStep(coord& move, game& play) {
	do {
		std::cout << "¬ведите координату х(1-3): ";
		std::cin >> move.x;
		move.x--;
		std::cout << "¬ведите координату y(1-3): ";
		std::cin >> move.y;
		move.y--;
	} while ((move.x > 2 || move.x < 0) ||
			(move.x > 2 || move.x < 0) ||
			play.playingField[move.y][move.x] != EMPTY);
	play.playingField[move.y][move.x] = play.player;
}

void __fastcall cpuStep(game& play) {
	//частные случаи(игрок в выйгрышном положении)
	if (play.playingField[0][0] == EMPTY &&
		((play.playingField[1][0] == play.cpu && play.playingField[2][0] == play.cpu) ||  // | ?-- |  ?XX |  ?-- |
		(play.playingField[0][1] == play.cpu && play.playingField[0][1] == play.cpu) ||   // | -X- |  --- |  X-- |
		(play.playingField[1][1] == play.cpu && play.playingField[2][2] == play.cpu))) {  // | --X |  --- |  X-- |
		play.playingField[0][0] = play.cpu;
	}else if (play.playingField[2][0] == EMPTY &&
		((play.playingField[0][0] == play.cpu && play.playingField[1][0] == play.cpu) ||  // | --? |  --? |  XX? |
		(play.playingField[2][1] == play.cpu && play.playingField[2][2] == play.cpu) ||	  // | -X- |  --X |  --- |
		(play.playingField[0][2] == play.cpu && play.playingField[1][1] == play.cpu))) {  // | X-- |  --X |  --- |
		play.playingField[2][0] = play.cpu;
	}else if (play.playingField[2][2] == EMPTY &&
		((play.playingField[0][0] == play.cpu && play.playingField[1][1] == play.cpu) ||  // | X-- |  --- |  --X |
		(play.playingField[0][2] == play.cpu && play.playingField[1][2] == play.cpu) ||   // | -X- |  --- |  --X |
		(play.playingField[2][0] == play.cpu && play.playingField[2][1] == play.cpu))) {  // | --? |  XX? |  --? |
		play.playingField[2][2] = play.cpu;
	}else if (play.playingField[0][2] == EMPTY &&
		((play.playingField[0][0] == play.cpu && play.playingField[0][1] == play.cpu) ||  // | --X |  --- |  X-- |
		(play.playingField[2][2] == play.cpu && play.playingField[1][2] == play.cpu) ||   // | -X- |  --- |  X-- |
		(play.playingField[2][0] == play.cpu && play.playingField[1][1] == play.cpu))) {  // | ?-- |  ?XX |  ?-- |
		play.playingField[0][2] = play.cpu;
	}else if (play.playingField[1][0] == EMPTY &&
		(play.playingField[1][1] == play.cpu && play.playingField[1][2] == play.cpu)) {        // | -?- | 
		play.playingField[1][0] = play.cpu;													   // | -X- | 
	}																						   // | -X- |  
	else if (play.playingField[1][2] == EMPTY &&
		(play.playingField[1][0] == play.cpu && play.playingField[1][1] == play.cpu)) {        // | -X- | 
		play.playingField[1][2] = play.cpu;													   // | -X- | 
	}																						   // | -?- |
	else if (play.playingField[0][1] == EMPTY &&
		(play.playingField[0][0] == play.cpu && play.playingField[0][2] == play.cpu)) {        // | X-- | 
		play.playingField[0][1] = play.cpu;													   // | ?-- | 
	}																						   // | X-- |
	else if (play.playingField[1][1] == EMPTY &&
		(play.playingField[1][0] == play.cpu && play.playingField[1][3] == play.cpu)) {        // | -X- | 
		play.playingField[1][1] = play.cpu;													   // | -?- | 
	}																						   // | -X- |
	else if (play.playingField[2][1] == EMPTY &&
		(play.playingField[2][0] == play.cpu && play.playingField[2][2] == play.cpu)) {        // | --X | 
		play.playingField[2][1] = play.cpu;													   // | --? | 
	}																						   // | --X |
	else if (play.playingField[1][0] == EMPTY &&
		(play.playingField[0][0] == play.cpu && play.playingField[2][0] == play.cpu)) {		   // | X?X | 
		play.playingField[1][0] = play.cpu;													   // | --- | 
	}																						   // | --- |
	else if (play.playingField[1][1] == EMPTY &&
		(play.playingField[0][1] == play.cpu && play.playingField[2][1] == play.cpu)) {		   // | --- | 
		play.playingField[1][1] = play.cpu;													   // | X?X | 
	}																						   // | --- |
	else if (play.playingField[1][2] == EMPTY &&
		(play.playingField[0][2] == play.cpu && play.playingField[2][2] == play.cpu)) {        // | --- | 
		play.playingField[1][2] = play.cpu;													   // | --- | 
	}																						   // | X?X |
	else if (play.playingField[1][2] == EMPTY &&
		(play.playingField[1][0] == play.cpu && play.playingField[1][1] == play.cpu)) {		   // | --- | 
		play.playingField[1][2] = play.cpu;													   // | XX? | 
	}																						   // | --- |  
	else//частные случаи(CPU в выйгрышном положении) 
	if (play.playingField[0][0] == EMPTY &&
		((play.playingField[1][0] == play.player && play.playingField[2][0] == play.player) ||  // | ?-- |  ?XX |  ?-- |
		(play.playingField[0][1] == play.player && play.playingField[0][1] == play.player) ||   // | -X- |  --- |  X-- |
		(play.playingField[1][1] == play.player && play.playingField[2][2] == play.player))) {  // | --X |  --- |  X-- |
		play.playingField[0][0] = play.cpu;
	}else if (play.playingField[2][0] == EMPTY &&
		((play.playingField[0][0] == play.player && play.playingField[1][0] == play.player) ||  // | --? |  --? |  XX? |
		(play.playingField[2][1] == play.player && play.playingField[2][2] == play.player) ||	// | -X- |  --X |  --- |
		(play.playingField[0][2] == play.player && play.playingField[1][1] == play.player))) {  // | X-- |  --X |  --- |
		play.playingField[2][0] = play.cpu;
	}else if (play.playingField[2][2] == EMPTY &&
		((play.playingField[0][0] == play.player && play.playingField[1][1] == play.player) ||  // | X-- |  --- |  --X |
		(play.playingField[0][2] == play.player && play.playingField[1][2] == play.player) ||   // | -X- |  --- |  --X |
		(play.playingField[2][0] == play.player && play.playingField[2][1] == play.player))) {  // | --? |  XX? |  --? |
		play.playingField[2][2] = play.cpu;
	}else if (play.playingField[0][2] == EMPTY &&
		((play.playingField[0][0] == play.player && play.playingField[0][1] == play.player) ||  // | --X |  --- |  X-- |
		(play.playingField[2][2] == play.player && play.playingField[1][2] == play.player) ||   // | -X- |  --- |  X-- |
		(play.playingField[2][0] == play.player && play.playingField[1][1] == play.player))) {  // | ?-- |  ?XX |  ?-- |
		play.playingField[0][2] = play.cpu;
	}else if (play.playingField[1][0] == EMPTY &&
		(play.playingField[1][1] == play.player && play.playingField[1][2] == play.player)) {  // | -?- | 
		play.playingField[1][0] = play.cpu;													   // | -X- | 
	}																						   // | -X- |  
	else if (play.playingField[1][2] == EMPTY &&
		(play.playingField[1][0] == play.player && play.playingField[1][1] == play.player)) {  // | -X- | 
		play.playingField[1][2] = play.cpu;													   // | -X- | 
	}																						   // | -?- |
	else if (play.playingField[0][1] == EMPTY &&
		(play.playingField[0][0] == play.player && play.playingField[0][2] == play.player)) {  // | X-- | 
		play.playingField[0][1] = play.cpu;													   // | ?-- | 
	}																						   // | X-- |
	else if (play.playingField[1][1] == EMPTY &&
		(play.playingField[1][0] == play.player && play.playingField[1][3] == play.player)) {  // | -X- | 
		play.playingField[1][1] = play.cpu;													   // | -?- | 
	}																						   // | -X- |
	else if (play.playingField[2][1] == EMPTY &&
		(play.playingField[2][0] == play.player && play.playingField[2][2] == play.player)) {  // | --X | 
		play.playingField[2][1] = play.cpu;													   // | --? | 
	}																						   // | --X |
	else if (play.playingField[1][0] == EMPTY &&
		(play.playingField[0][0] == play.player && play.playingField[2][0] == play.player)) {  // | X?X | 
		play.playingField[1][0] = play.cpu;													   // | --- | 
	}																						   // | --- |
	else if (play.playingField[1][1] == EMPTY &&
		(play.playingField[0][1] == play.player && play.playingField[2][1] == play.player)) {  // | --- | 
		play.playingField[1][1] = play.cpu;													   // | X?X | 
	}																						   // | --- |
	else if (play.playingField[1][2] == EMPTY &&
		(play.playingField[0][2] == play.player && play.playingField[2][2] == play.player)) {  // | --- | 
		play.playingField[1][2] = play.cpu;													   // | --- | 
	}																						   // | X?X |
	else if (play.playingField[1][2] == EMPTY &&
		(play.playingField[1][0] == play.player && play.playingField[1][1] == play.player)) {  // | --- | 
		play.playingField[1][2] = play.cpu;													   // | XX? | 
	}																						   // | --- |  
	else//общие случаи
	if (play.playingField[1][1] == EMPTY) {
		play.playingField[1][1] = play.cpu;
	}else {
		int x = getRandomNum(1, 1000) % 3, y = getRandomNum(1, 1000) % 3;
		while (play.playingField[x][y] == play.player || play.playingField[x][y] == play.cpu) {
			y = getRandomNum(1, 1000) % 3;
			x = getRandomNum(1, 1000) % 3;
		}
		play.playingField[x][y] = play.cpu;
	}
}

void __fastcall checkGame(game& play){
	if ((play.playingField[0][0] == play.playingField[1][1] && play.playingField[1][1] == play.playingField[2][2]) ||
		(play.playingField[0][2] == play.playingField[1][1] && play.playingField[1][1] == play.playingField[2][0]) ||
		(play.playingField[1][0] == play.playingField[1][1] && play.playingField[1][1] == play.playingField[1][2]) ||
		(play.playingField[0][1] == play.playingField[1][1] && play.playingField[1][1] == play.playingField[2][1])) {
		if (play.playingField[1][1] == play.player) {
			play.stage = PLAYER_WON;
		}else if (play.playingField[1][1] == play.cpu) {
			play.stage = CPU_WON;
		}
	}
	
	if ((play.playingField[0][0] == play.playingField[0][1] && play.playingField[0][1] == play.playingField[0][2]) ||
		(play.playingField[0][0] == play.playingField[1][0] && play.playingField[1][0] == play.playingField[2][0])) {
		if (play.playingField[0][0] == play.player) {
			play.stage = PLAYER_WON;
		}
		else if (play.playingField[0][0] == play.cpu) {
			play.stage = CPU_WON;
		}
	}

	if ((play.playingField[2][2] == play.playingField[2][1] && play.playingField[2][1] == play.playingField[2][0]) ||
		(play.playingField[2][2] == play.playingField[1][2] && play.playingField[1][2] == play.playingField[0][2])) {
		if (play.playingField[2][2] == play.player) {
			play.stage = PLAYER_WON;
		}
		else if (play.playingField[2][2] == play.cpu) {
			play.stage = CPU_WON;
		}
	}

	uint8_t check = 0;
	for (auto i = 0U; i < 3; i++) {
		for (auto j = 0U; j < 3; j++) {
			if (play.playingField[i][j] != EMPTY) {
				check++;
			}
		}
	}
	if (check == 9) {
		play.stage = DRAW;
	}
}

void __fastcall endGame(game play) {
	if (play.stage == PLAYER_WON) {
		std::cout << "Player WON!!!" << std::endl;
	}
	else if (play.stage == CPU_WON) {
		std::cout << "CPU WON!!!" << std::endl;
	}
	else if (play.stage == DRAW) {
		std::cout << "DRAW!!!" << std::endl;
	}
}

void __fastcall printBoard(game& play) {
	system("cls");
	std::cout << "   1 2 3 x\n";
	for (auto i = 0U; i < 3; i++) {
		std::cout << "  +-+-+-+\n";
		std::cout << i + 1 << " ";
		for (auto j = 0U; j < 3; j++) {
			std::cout << '|' << play.playingField[i][j];
		}
		std::cout << "|\n";
	}
	std::cout << "  +-+-+-+\n";
	std::cout << "y\n";
	std::cout << "\nPlayer: " << play.player << std::endl;
	std::cout << "CPU: " << play.cpu << std::endl;
}

//	  1 2 3  x
//	 +-+-+-+
// 1 |-|-|-|
//	 +-+-+-+
// 2 |-|-|-|
//	 +-+-+-+
// 3 |-|-|-|
//	 +-+-+-+
// y
	
int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	coord move;
	game play;
	startgame(play);
	do {
	printBoard(play);
	if (play.step % 2 == 0) {
		playerStep(move, play);
		play.step++;
	}
	else {
		cpuStep(play);
		play.step++;
	}
	checkGame(play);
	} while (play.stage == IN_PROGRESS);
	printBoard(play);
	endGame(play);
	return 0;
}