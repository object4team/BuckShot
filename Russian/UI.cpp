#include "Russian.h"

class UI {

public :
	void PrintUI(int pLife, int cLife, int totalBullet, int currBullet, int fake, int real, bool playerTurn) {
		system("cls");
		PrintTitle();
		verticalLine();

		printPlayerHealth(pLife);
		bulletBoard(totalBullet, fake, real, currBullet);

		std::cout << "Player Turn: " << playerTurn << "\n";
		verticalLine();
	}
	void printPlayerHealth(int pLife){
		std::cout << "頂 羹溘 ";
		for (int i = 0; i < 5; i++) {
			if(i < pLife)
				std::cout << "Ⅵ";
			else
				std::cout << "Ⅴ";
		}
		std::cout << "\n";
	}
	void bulletBoard(int totalB, int fakeB, int realB, int currB) {
		//﹤ ﹥
		std::cout << "旨";
		for(int i = 0; i < totalB; i++) {
			std::cout << "收收";
		}
		std::cout << "旬\n";

		std::cout << "早";
		for(int i = 0; i < totalB - currB; i++) {
			if(i < realB)
				std::cout << "﹥";
			else
				std::cout << "﹤";
		}
		for(int i = 0; i < currB; i++) {
			std::cout << " *";
		}
		std::cout << "早\n";

		std::cout << "曲";
		for (int i = 0; i < totalB; i++) {
			std::cout << "收收";
		}
		std::cout << "旭";
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
            "|_______/  \\______/  \\_______/|__/  \\__/ \\______/ |__/  |__/ \\______/    \\___/        |__/  |__/ \\______/  \\______/ |__/ \\_______/   \\___/   \\___/   \\_______/\n"
            "\n";
	}

	void verticalLine() {
		for (int i = 0; i < 80; i++)
			std::cout << "﹥";
		std::cout << "\n";
	}

	void printCentered(const std::string& text) {
		int padding = (160 - text.size()) / 2;
		std::cout << std::setw(padding) << "" << text << std::endl;
	}

};