#include<iostream>
#include<cstdlib>
#include<conio.h>
using namespace std;
//�÷��̾� Ŭ����
class Player {
private: //�������� �ִٸ� ������ �������
    string item[3] = {};

public: // ������, ��
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
class ShootGun // ���� Ŭ����
{
public: //�� �Ѿ˰���, ��ź, ����ź, ���� �Ѿ� �� Ƚ��
    int total_bullet; //�� �Ѿ˰���
    int RealBullet_num; //��ź
    int FakeBullet_num;// ����ź
    int tmp = 0; //���� �Ѿ�
    string tmp_bullet[8] = { "" }; //�Ѿ���
    ShootGun(int total_bullet = 0, int RealBullet_num = 0, int FakeBullet_num = 0) : total_bullet(total_bullet), RealBullet_num(RealBullet_num), FakeBullet_num(FakeBullet_num) {}
    void InitiateShootGun() //���� �ʱ�ȭ �Լ�
    {
        srand(time(NULL));
        total_bullet = rand() % 7 + 2; //�ּ� 2�� �ִ� 8�� ����
        FakeBullet_num = rand() % total_bullet; //�ּ� 0�� �ִ� (�� �Ѿ� ���� -1)
        RealBullet_num = total_bullet - FakeBullet_num; //����ź�� ������ ������
        for (int i = RealBullet_num; i > 0; i--) //��ź �ֱ�
        {
            int num = 0;
            while (tmp_bullet[num] != "" && tmp_bullet[num] != "RealBullet") //�� �Ѿ��� ã��
            {
                num = rand() % total_bullet;
            }
            tmp_bullet[num] = "RealBullet"; //��ź �ֱ�
        }
        for (int i = total_bullet - 1; i > 0; i--) //����ź �ֱ�
        {
            if (tmp_bullet[i] != "" && tmp_bullet[i] != "RealBullet") //�� �Ѿ��� ã��
            {
                tmp_bullet[i] = "FakeBullet"; //����ź �ֱ�
            }
        }

    }
    void Shoot(Player player) //���
    {
        if (tmp_bullet[tmp++] == "Fake_Bullet")
        {
            //Fake(); ����ź�϶� UI���
        }
        else
        {
            //Real(); //��ź�� �� UI���
            player.life--; //������ �پ���
            InitiateShootGun(); //���� �ʱ�ȭ
        }
        if (player.life == 0)
        {

            system("cls");
            //gameOver(); ���ӿ����� �� UI���
        }

    }
};
void Choose(Player player, Player other, ShootGun shootgun) //�÷��̾ �ڽ����� ���� �������� ���� ���ϱ�
{
    if (player.is_turn(other)) //Player�� ���̶��
    {
        char key = ' ';
        while ((key != 'S' && key != 's' && key != 'A' && key != 'a')) //S Ȥ�� A�� ����������
        {
            key = getch(); //Ű�� �Է¹ޱ�
            system("cls");
        }
        if (key == 'S' || key == 's')
        {
            shootgun.Shoot(other); //���� ���
            player.turn = false;
        }
        else
        {
            shootgun.Shoot(player); //�ڽ� ���
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