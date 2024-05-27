#include "Russian.h"
#include "UI.cpp"

//플레이어 클래스
class Player {
public: // 라이프, 턴
    int life = 5;
};

class Shotgun // 샷건 클래스
{
public:
    int total_bullet; // 총알 갯수
    bool magazine[8]; //총알집
    int currBullet; //현재 총알 쏜 횟수
    int fakeBulletNum; //공포탄 갯수
    int realBulletNum; //실탄 갯수

    bool playerTurn = true; //플레이어 턴인지 아닌지

    UI ui;

    void InitiateShotgun() //샷건 초기화 함수
    {
        srand(time(NULL));
        currBullet = 0; //현재 총알 쏜 횟수 초기화
        total_bullet = rand() % 7 + 2; //최소 2발 최대 8발 장전

        if (total_bullet == 2) // 총알이 2발일 경우
        {
            fakeBulletNum = 1; // 공포탄 1발
            realBulletNum = 1; // 실탄 1발
        }
        else
        {
            fakeBulletNum = rand() % (total_bullet - 1) + 1; //최소 1발, 최대 (총 총알 갯수 - 1)발
            realBulletNum = total_bullet - fakeBulletNum; //공포탄을 제외한 나머지
        }

        for (int i = 0; i < total_bullet; i++)
        {
            if (i < realBulletNum)
                magazine[i] = true;
            else
                magazine[i] = false;
        }
        random_shuffle(magazine, magazine + total_bullet);
    }

    void random_shuffle(bool* begin, bool* end) //총알 섞기
    {
        for (int i = 0; i < total_bullet; i++)
        {
            int j = rand() % total_bullet;
            bool tmp = begin[i];
            begin[i] = begin[j];
            begin[j] = tmp;
        }
    }
    
    bool Shoot(Player& target, Player& player, Player& computer, Shotgun shotgun) //사격
    {
        if (magazine[currBullet++] == false) //실탄이 아닐때
        {
            Sleep(800);
            cout << "틱, 공포탄이었습니다" << endl;
            Sleep(700);
            fakeBulletNum--; //공포탄 갯수 줄이기

            if (currBullet == total_bullet) // 총알을 모두 소진했을 때
            {
                cout << "모든 총알을 다 소진했습니다. 탄창을 교환합니다." << endl;
                Sleep(1000);
                InitiateShotgun(); // 재장전
            }
            return false;
        }
        else // 실탄일때
        {
            Sleep(800);
		    ui.ShootEffect();
            ui.PrintUI(player.life, computer.life, shotgun.total_bullet, shotgun.currBullet, shotgun.fakeBulletNum, shotgun.realBulletNum, shotgun.playerTurn);
            cout << "빵! 실탄이었습니다" << endl;
            Sleep(1000);
            //ui.printAtBottom(20);

            realBulletNum--; //실탄 갯수 줄이기
            player.life--; //라이프 줄어들기
            if (currBullet == total_bullet && player.life != 0) // 총알을 모두 소진하고 맞은 사람이 죽지 않았을 때
            {
                cout << "모든 총알을 다 소진했습니다. 탄창을 교환합니다." << endl;
                Sleep(1000);
                InitiateShotgun(); // 재장전
            }
            return true;
        }
    }

};


void PlayerTurn(Player& player, Player& computer, Shotgun& shotgun, UI& ui) // 플레이어의 행동 선택
{
	char key = ' ';
    ui.printCentered("상대방에게 쏠지(↑), 자신에게 쏠지 선택하세요(↓)");
    ui.printCentered("자신에게 공포탄을 쏠 경우 차례를 유지할 수 있습니다.");
    _getch();

    while ((key != 72 && key != 80)) // 위 방향키(72) 혹은 아래 방향키(80)를 받을때까지
    {
        key = _getch(); //키를 입력받기
        if (key == 0 || key == 224) // 방향키를 입력받기 위한 처리
        {
            key = _getch();
        }
    }

    if (key == 72) // 위 방향키, 상대 사격
    {
        cout << "상대에게 사격합니다." << endl;
        Sleep(1000);
        shotgun.Shoot(computer, player, computer, shotgun); // 상대방 쏘기
        shotgun.playerTurn = false; // 상대방 턴으로 넘어가기
    }
    else if (key == 80) // 아래 방향키, 자신 사격
    {
        cout << "자신을 쏩니다." << endl;
        Sleep(1000);
        if (shotgun.Shoot(player, player, computer, shotgun) == true) { // 실탄이었을 때
            shotgun.playerTurn = false; // 상대방 턴으로 넘어가기
        }
    }
}

void EnemyTurn(Player& computer, Player& player, Shotgun& shotgun, UI& ui) // 컴퓨터가 자신한테 쏠지 상대방한테 쏠지 정하기
{
    cout << "상대방의 턴입니다." << endl;
    Sleep(1000);
    // 실탄과 공포탄의 개수를 고려하여 행동 결정
    if (shotgun.realBulletNum > shotgun.fakeBulletNum) // 실탄이 더 많으면 플레이어 사격
    {
        cout << "플레이어에게 총구를 겨눕니다." << endl;
        Sleep(1000);
        shotgun.Shoot(player, player, computer, shotgun);
        shotgun.playerTurn = true; // 플레이어 턴으로 넘어가기
    }

    else if (shotgun.realBulletNum == shotgun.fakeBulletNum) {
        // 실탄과 공포탄의 개수가 같으면 랜덤으로 결정
        int random = rand() % 2;
        if (random == 0) // 자신 사격
        {
            cout << "자신을 향해 총구를 겨눕니다." << endl;
            Sleep(1000);
            shotgun.Shoot(computer, player, computer, shotgun);
        }
        else // 플레이어 사격
        {
            cout << "플레이어에게 총구를 겨눕니다." << endl;
            Sleep(1000);
            shotgun.Shoot(player, player, computer, shotgun);
            shotgun.playerTurn = true; // 플레이어 턴으로 넘어가기
        }
    }
    else // 공포탄이 더 많으면 자신 사격
    {
        cout << "자신을 향해 총구를 겨눕니다." << endl;
        Sleep(1000);
        shotgun.Shoot(computer, player, computer, shotgun);
    }
}



void RussianGame()
{
    Player player;
    Player computer;
    Shotgun shotgun;
    shotgun.InitiateShotgun();
    UI ui;
    while (player.life != 0 && computer.life != 0)
    {
        ui.PrintUI(player.life,computer.life,shotgun.total_bullet,shotgun.currBullet,shotgun.fakeBulletNum,shotgun.realBulletNum,shotgun.playerTurn);

        if(shotgun.playerTurn == true) // 플레이어 턴
            PlayerTurn(player, computer, shotgun, ui);
        else
            EnemyTurn(computer, player, shotgun, ui);
    }
    if(player.life == 0)
        ui.printCentered("플레이어가 패배했습니다.");
	else
        ui.printCentered("플레이어가 승리했습니다.");
}