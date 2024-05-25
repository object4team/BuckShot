#include<iostream>
#include<cstdlib>
#include<conio.h>
using namespace std;
//플레이어 클래스
class Player {
private: //아이템이 있다면 아이템 저장공간
    string item[3] = {};

public: // 라이프, 턴
    int life = 5;
    bool turn = false;
    bool is_turn(Player other)
    {
        if (other.turn == false)
        {
            turn = true;
        }
        return turn;
    }
};
class ShootGun // 샷건 클래스
{
public: //총 총알갯수, 실탄, 공포탄, 현재 총알 쏜 횟수
    int total_bullet; //총 총알갯수
    int RealBullet_num; //실탄
    int FakeBullet_num;// 공포탄
    int tmp = 0; //현재 총알
    string tmp_bullet[8] = { "" }; //총알집
    ShootGun(int total_bullet = 0, int RealBullet_num = 0, int FakeBullet_num = 0) : total_bullet(total_bullet), RealBullet_num(RealBullet_num), FakeBullet_num(FakeBullet_num) {}
    void InitiateShootGun() //샷건 초기화 함수
    {
        srand(time(NULL));
        total_bullet = rand() % 7 + 2; //최소 2발 최대 8발 장전
        FakeBullet_num = rand() % total_bullet; //최소 0발 최대 (총 총알 갯수 -1)
        RealBullet_num = total_bullet - FakeBullet_num; //공포탄을 제외한 나머지
        for (int i = RealBullet_num; i > 0; i--) //실탄 넣기
        {
            int num = 0;
            while (tmp_bullet[num] != "" && tmp_bullet[num] != "RealBullet") //빈 총알집 찾기
            {
                num = rand() % total_bullet;
            }
            tmp_bullet[num] = "RealBullet"; //실탄 넣기
        }
        for (int i = total_bullet - 1; i > 0; i--) //공포탄 넣기
        {
            if (tmp_bullet[i] != "" && tmp_bullet[i] != "RealBullet") //빈 총알집 찾기
            {
                tmp_bullet[i] = "FakeBullet"; //공포탄 넣기
            }
        }

    }
    void Shoot(Player player) //사격
    {
        if (tmp_bullet[tmp++] == "Fake_Bullet")
        {
            //Fake(); 공포탄일때 UI출력
        }
        else
        {
            //Real(); //실탄일 때 UI출력
            player.life--; //라이프 줄어들기
            InitiateShootGun(); //샷건 초기화
        }
        if (player.life == 0)
        {

            system("cls");
            //gameOver(); 게임오버일 때 UI출력
        }

    }
};
void Choose(Player player, Player other, ShootGun shootgun) //플래이어가 자신한테 쏠지 상대방한테 쏠지 정하기
{
    if (player.is_turn(other)) //Player의 턴이라면
    {
        char key = ' ';
        while ((key != 'S' && key != 's' && key != 'A' && key != 'a')) //S 혹은 A를 받을때까지
        {
            key = getch(); //키를 입력받기
            system("cls");
        }
        if (key == 'S' || key == 's')
        {
            shootgun.Shoot(other); //상대방 쏘기
            player.turn = false;
        }
        else
        {
            shootgun.Shoot(player); //자신 쏘기
            player.turn = false;
        }
    }
}
void RussianGame()
{
    Player player1;
    Player player2;
    ShootGun shootgun;
    shootgun.InitiateShootGun();
    while (player1.life != 0 && player2.life != 0)
    {
        Choose(player1, player2, shootgun);
        Choose(player2, player1, shootgun);
    }
}