﻿#include "Russian.h"
#include <sstream>;
class UI {

public :
	void PrintUI(int pLife, int cLife, int totalBullet, int currBullet, int fake, int real, bool playerTurn) {
		system("cls");
		PrintTitle();
		verticalLine();

		printPlayerHealth(pLife);
		printDealerHealth(cLife);
		bulletBoard(totalBullet, fake, real, currBullet);

		//std::cout << "Player Turn: " << playerTurn << "\n";
		verticalLine();
	}
	void printPlayerHealth(int pLife){
		std::cout << "\n내 체력 ";
		for (int i = 0; i < 5; i++) {
			if(i < pLife)
				std::cout << "♥";
			else
				std::cout << "♡";
		}
		std::cout << "\n";
	}
	void printDealerHealth(int cLife) {
		std::cout << "상대 체력 ";
		for (int i = 0; i < 5; i++) {
			if (i < cLife)
				std::cout << "♥";
			else
				std::cout << "♡";
		}
		std::cout << "\n";
	}
	void bulletBoard(int totalB, int fakeB, int realB, int currB) {
		//□ ■
		std::cout << "┏";
		for(int i = 0; i < totalB; i++) {
			std::cout << "━━";
		}
		std::cout << "┓\n";

		std::cout << "┃";
		for(int i = 0; i < totalB - currB; i++) {
			if(i < realB)
				std::cout << "■";
			else
				std::cout << "□";
		}
		for(int i = 0; i < currB; i++) {
			std::cout << " *";
		}
		std::cout << "┃ ■ : 실탄 개수  □ : 공포탄 개수\n";

		std::cout << "┗";
		for (int i = 0; i < totalB; i++) {
			std::cout << "━━";
		}
		std::cout << "┛";
		std::cout << "\n";
	}


	void PrintTitle() {
        std::cout << "\n /$$$$$$$                      /$$        /$$$$$$  /$$                   /$$           /$$$$$$$                      /$$             /$$     /$$              \n"
            "| $$__  $$                    | $$       /$$__  $$| $$                  | $$          | $$__  $$                    | $$            | $$    | $$              \n"
            "| $$  \\ $$ /$$   /$$  /$$$$$$$| $$   /$$| $$  \\__/| $$$$$$$   /$$$$$$  /$$$$$$        | $$  \\ $$  /$$$$$$  /$$   /$$| $$  /$$$$$$  /$$$$$$ /$$$$$$    /$$$$$$ \n"
            "| $$$$$$$ | $$  | $$ /$$_____/| $$  /$$/|  $$$$$$ | $$__  $$ /$$__  $$|_  $$_/        | $$$$$$$/ /$$__  $$| $$  | $$| $$ /$$__  $$|_  $$_/|_  $$_/   /$$__  $$\n"
            "| $$__  $$| $$  | $$| $$      | $$$$$$/  \\____  $$| $$  \\ $$| $$  \\ $$  | $$          | $$__  $$| $$  \\ $$| $$  | $$| $$| $$$$$$$$  | $$    | $$    | $$$$$$$$\n"
            "| $$  \\ $$| $$  | $$| $$      | $$_  $$  /$$  \\ $$| $$  | $$| $$  | $$  | $$ /$$      | $$  \\ $$| $$  | $$| $$  | $$| $$| $$_____/  | $$ /$$| $$ /$$| $$_____/\n"
            "| $$$$$$$/|  $$$$$$/|  $$$$$$$| $$ \\  $$|  $$$$$$/| $$  | $$|  $$$$$$/  |  $$$$/      | $$  | $$|  $$$$$$/|  $$$$$$/| $$|  $$$$$$$  |  $$$$/|  $$$$/|  $$$$$$$\n"
            "|_______/  \\______/  \\_______/|__/  \\__/ \\______/ |__/  |__/ \\______/    \\___/        |__/  |__/ \\______/  \\______/ |__/ \\_______/   \\___/   \\___/   \\_______/\n";
	}

	void verticalLine() {
		std::cout << "\n";
		for (int i = 0; i < 160; i++)
			std::cout << "=";
		std::cout << "\n";
	}

	void printAtBottom(int consoleHeight) {
		for (int i = 0; i < consoleHeight; ++i) {
			std::cout << "\n";
		}
		verticalLine();
	}

	void printCentered(const std::string& text) {
		int padding = (160 - text.size()) / 2;
		std::cout << std::setw(padding) << "" << text << std::endl;
	}


	void ShootEffect() {
		system("cls");
		std::ostringstream oss;
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 80; j++) {
				oss << "■";
			}
			std::cout << "\n" << std::endl;
		}
		std:cout << oss.str();
		Sleep(500);
		system("cls");
	}
};