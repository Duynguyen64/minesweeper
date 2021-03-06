// Mine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

void display_table(int boxes_height, int boxes_width, char **matrice, bool game_over) {
	cout << "      ";
	for (int i = 0; i < boxes_width; i++) {
		if (i <= 9)
			cout << " " << i << " ";
		else {
			cout << i << " ";
		}
		if ((i + 1) == boxes_width) {
			cout << endl;
		}

	}
	cout << "      ";
	for (int i = 0; i < boxes_width; i++) {
		cout << "---";
		if ((i + 1) == boxes_width) {
			cout << endl;
		}
	}

	for (int i = 0; i < boxes_height; i++) {
		if (i < 10)
			cout << " ";
		cout << " " << i << " | ";
		for (int j = 0; j < boxes_width; j++) {
			if (matrice[i][j] == NULL) {
				matrice[i][j] = ' ';
				cout << "[" << matrice[i][j] << "]";
			}
			else if (matrice[i][j] == 'X' && game_over == false) {
				cout << "[ ]";
			}
			else {
				cout << "[" << matrice[i][j] << "]";
			}
		}
		cout << " | " << i << endl;
	}
	cout << "      ";
	for (int i = 0; i < boxes_width; i++) {
		cout << "---";
		if ((i + 1) == boxes_width) {
			cout << endl;
		}
	}
	cout << "      ";
	for (int i = 0; i < boxes_width; i++) {
		if (i <= 9)
			cout << " " << i << " ";
		else {
			cout << i << " ";
		}
		if ((i + 1) == boxes_width) {
			cout << endl;
		}
	}
	cout << endl;
}

void random_mines(int boxes_height, int boxes_width,int num_mines, char **matrice) {
	int rand_col;
	int rand_lig;
	for (int i = 0; i < num_mines; i++) {
		rand_col = rand() % boxes_width;
		rand_lig = rand() % boxes_height;
		if (matrice[rand_lig][rand_col] == 'X') {
			i--;
		}
		matrice[rand_lig][rand_col] = 'X';
	}	
}

bool check_format(int guess_line, int guess_column, int boxes_height, int boxes_width,char **matrice) {
	if (guess_line >= boxes_height || guess_column >= boxes_width || guess_column < 0 || guess_line < 0) {
		cout << endl;
		cout << "Error !!! Please enter right number !!! \n" <<  endl;
		this_thread::sleep_for(chrono::milliseconds(2000));
		cout << "==============================================================" << endl;
		return true;
	}
	else if (matrice[guess_line][guess_column] != ' ' && matrice[guess_line][guess_column] != 'X') {
		cout << endl;
		cout << "The box is not empty\n" << endl;
		this_thread::sleep_for(chrono::milliseconds(2000));
		cout << "==============================================================" << endl;
		return true;
	}
	else
		return false;
}

bool win_lose(int guess_line, int guess_column, int boxes_height, int boxes_width,  char **matrice)	 {
	if (matrice[guess_line][guess_column] == 'X') {
		cout << "BBOOOOOMMMMM !!! YOU LOSE !!! :( " << endl;
		this_thread::sleep_for(chrono::milliseconds(2000));
		return true;
		}
	else {
		for (int i = 0; i < boxes_height; i++) {
			for (int j = 0; j < boxes_width; j++) {
				if (matrice[i][j] == ' ') {
					return false;
				}
			}
		}
		cout << "OMG !!! YOU WIN !!! GGWP !!! :D " << endl;
		this_thread::sleep_for(chrono::milliseconds(2000));
		return true;
	}
}

int count_mines(int guess_line, int guess_column, int boxes_height, int boxes_width, char **matrice) {
	int mines_around = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (((guess_line + i) >= 0) && ((guess_column + j) >= 0) && ((guess_column + j) < boxes_width) && ((guess_line + i) < boxes_height)) {
					if (matrice[guess_line + i][guess_column + j] == 'X')
						mines_around++;
			}
		}
	}
	return mines_around;
}

void find_save_case(int guess_line, int guess_column, int boxes_height, int boxes_width, char **matrice)  {
	int mines_around = 0;
	int char_mines = ' ';

	matrice[guess_line][guess_column] = '-';

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (((guess_line + i) >= 0) && ((guess_column + j) >= 0) && ((guess_column + j) < boxes_width) && ((guess_line + i) < boxes_height)) {
				if (((guess_line + i) != guess_line) || ((guess_column + j) != guess_column) ) {
					if (matrice[guess_line + i][guess_column + j] == ' ') {
						mines_around = count_mines(guess_line + i, guess_column + j, boxes_height, boxes_width, matrice);
						if (mines_around == 0) {
							find_save_case(guess_line + i, guess_column + j, boxes_height, boxes_width, matrice);
						}
						else {
							char_mines = mines_around + '0';
							matrice[guess_line + i][guess_column + j] = char_mines;
						}
					}
				}
			}
		}
	}
}

void welcome() {
	cout << "||======================================================================||" << endl;
	cout << "||                                                                      ||" << endl;
	cout << "||                       <(^.^<)  WELCOME  (>^.^)>                      ||" << endl;
	cout << "||                            GAME MINESWEEPER                          ||" << endl;
	cout << "||                           Made by  Zuy_Noo64                         ||" << endl;
	cout << "||                                                                      ||" << endl;
	cout << "||======================================================================||\n" << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));
	cout << "                            ARE YOU READYYYY ?????\n" << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));
	cout << "                             LET'S PLAYYYYY !!!!" << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));
}

int main()
{
	int boxes_width = 0;
	int boxes_height = 0;
	int guess_column = 0;
	int guess_line = 0;
	int num_mines = 0;
	int mines_around = 0;
	char **matrice;
	bool wrong_format = false;
	bool game_over = false;

	welcome();

	//be requested from the user
	while (true) {
		cout << "\nHow many boxes in width ?" << "  ";
		cin >> boxes_width;

		cout << "\nHow many boxes in height ?" << "  ";
		cin >> boxes_height;

		cout << "\nHow many mines ?" << "  ";
		cin >> num_mines;
		cout << endl;
		if ((boxes_height * boxes_width) > num_mines && boxes_height >= 0 && boxes_width >= 0 && num_mines >= 0) {
			break;
		}
		if (boxes_height < 0 || boxes_width < 0 || num_mines < 0)
			cout << "??? boxes mines negatif ??? What is this ???\n";
		else 
			cout << "\nSo many mines in this map. Are you kidding me ?\n" << endl;
		this_thread::sleep_for(chrono::milliseconds(2000));
	}

	//declare line and column
	matrice = new char*[boxes_height];
	for (int i = 0; i < boxes_height; i++)
		matrice[i] = new char[boxes_width];
	for (int i = 0; i < boxes_height; i++) {
		for (int j = 0; j < boxes_width; j++) {
			matrice[i][j] = NULL;
		}
	}

	//display table
	display_table(boxes_height, boxes_width, matrice, game_over);

	random_mines(boxes_height, boxes_width, num_mines, matrice);

	cout << "==============================================================" << endl;

	while (true) {
		
		cout << "\nEnter column number between 0 and " << boxes_width - 1 << " : ";
		cin >> guess_column;

		cout << "\nEnter line number between 0 and  " << boxes_height - 1 << " : ";
		cin >> guess_line;
		cout << endl;
		while (check_format(guess_line, guess_column, boxes_height, boxes_width,matrice)) {
			cout << "\nEnter column number between 0 and " << boxes_width - 1 << " : ";
			cin >> guess_column;

			cout << "\nEnter line number between 0 and  " << boxes_height - 1 << " : ";
			cin >> guess_line;
			cout << endl;
		}
		//lose or not
		cout << endl;
		if (win_lose(guess_line, guess_column, boxes_height, boxes_width, matrice)) {
			game_over = true;
			break;
		}

		//find number mines around
		mines_around = count_mines(guess_line, guess_column, boxes_height, boxes_width, matrice);

		//no mines => find another save case
		if (mines_around == 0) {
			find_save_case(guess_line, guess_column, boxes_height, boxes_width, matrice);
		}
		else {
			int char_mines = mines_around + '0';
			matrice[guess_line][guess_column] = char_mines;
		}

		display_table(boxes_height, boxes_width, matrice, game_over);

		//win or not
		if (win_lose(guess_line, guess_column, boxes_height, boxes_width, matrice)) {
			game_over = true;
			break;
		}
		cout << "==============================================================" << endl;
	}
	cout << "\n" << endl;
	display_table(boxes_height, boxes_width, matrice, game_over);
	cout << "G A M E  O V E R\n" << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));
	int again;
	cout << "ENTER 1 FOR EXIT" << endl;
	cin >> again;
	exit(0);
    return 0;
}
