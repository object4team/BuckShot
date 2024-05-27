#include "Russian.h"
#include "UI.cpp"

//�÷��̾� Ŭ����
class Player {
public: // ������, ��
    int life = 5;
};

class Shotgun // ���� Ŭ����
{
public:
    int total_bullet; // �Ѿ� ����
    bool magazine[8]; //�Ѿ���
    int currBullet; //���� �Ѿ� �� Ƚ��
    int fakeBulletNum; //����ź ����
    int realBulletNum; //��ź ����

    bool playerTurn = true; //�÷��̾� ������ �ƴ���

    UI ui;

    void InitiateShotgun() //���� �ʱ�ȭ �Լ�
    {
        srand(time(NULL));
        currBullet = 0; //���� �Ѿ� �� Ƚ�� �ʱ�ȭ
        total_bullet = rand() % 7 + 2; //�ּ� 2�� �ִ� 8�� ����

        if (total_bullet == 2) // �Ѿ��� 2���� ���
        {
            fakeBulletNum = 1; // ����ź 1��
            realBulletNum = 1; // ��ź 1��
        }
        else
        {
            fakeBulletNum = rand() % (total_bullet - 1) + 1; //�ּ� 1��, �ִ� (�� �Ѿ� ���� - 1)��
            realBulletNum = total_bullet - fakeBulletNum; //����ź�� ������ ������
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

    void random_shuffle(bool* begin, bool* end) //�Ѿ� ����
    {
        for (int i = 0; i < total_bullet; i++)
        {
            int j = rand() % total_bullet;
            bool tmp = begin[i];
            begin[i] = begin[j];
            begin[j] = tmp;
        }
    }
    
    bool Shoot(Player& target, Player& player, Player& computer, Shotgun shotgun) //���
    {
        if (magazine[currBullet++] == false) //��ź�� �ƴҶ�
        {
            Sleep(800);
            cout << "ƽ, ����ź�̾����ϴ�" << endl;
            Sleep(700);
            fakeBulletNum--; //����ź ���� ���̱�

            if (currBullet == total_bullet) // �Ѿ��� ��� �������� ��
            {
                cout << "��� �Ѿ��� �� �����߽��ϴ�. źâ�� ��ȯ�մϴ�." << endl;
                Sleep(1000);
                InitiateShotgun(); // ������
            }
            return false;
        }
        else // ��ź�϶�
        {
            Sleep(800);
		    ui.ShootEffect();
            ui.PrintUI(player.life, computer.life, shotgun.total_bullet, shotgun.currBullet, shotgun.fakeBulletNum, shotgun.realBulletNum, shotgun.playerTurn);
            cout << "��! ��ź�̾����ϴ�" << endl;
            Sleep(1000);
            //ui.printAtBottom(20);

            realBulletNum--; //��ź ���� ���̱�
            player.life--; //������ �پ���
            if (currBullet == total_bullet && player.life != 0) // �Ѿ��� ��� �����ϰ� ���� ����� ���� �ʾ��� ��
            {
                cout << "��� �Ѿ��� �� �����߽��ϴ�. źâ�� ��ȯ�մϴ�." << endl;
                Sleep(1000);
                InitiateShotgun(); // ������
            }
            return true;
        }
    }

};


void PlayerTurn(Player& player, Player& computer, Shotgun& shotgun, UI& ui) // �÷��̾��� �ൿ ����
{
	char key = ' ';
    ui.printCentered("���濡�� ����(��), �ڽſ��� ���� �����ϼ���(��)");
    ui.printCentered("�ڽſ��� ����ź�� �� ��� ���ʸ� ������ �� �ֽ��ϴ�.");
    _getch();

    while ((key != 72 && key != 80)) // �� ����Ű(72) Ȥ�� �Ʒ� ����Ű(80)�� ����������
    {
        key = _getch(); //Ű�� �Է¹ޱ�
        if (key == 0 || key == 224) // ����Ű�� �Է¹ޱ� ���� ó��
        {
            key = _getch();
        }
    }

    if (key == 72) // �� ����Ű, ��� ���
    {
        cout << "��뿡�� ����մϴ�." << endl;
        Sleep(1000);
        shotgun.Shoot(computer, player, computer, shotgun); // ���� ���
        shotgun.playerTurn = false; // ���� ������ �Ѿ��
    }
    else if (key == 80) // �Ʒ� ����Ű, �ڽ� ���
    {
        cout << "�ڽ��� ���ϴ�." << endl;
        Sleep(1000);
        if (shotgun.Shoot(player, player, computer, shotgun) == true) { // ��ź�̾��� ��
            shotgun.playerTurn = false; // ���� ������ �Ѿ��
        }
    }
}

void EnemyTurn(Player& computer, Player& player, Shotgun& shotgun, UI& ui) // ��ǻ�Ͱ� �ڽ����� ���� �������� ���� ���ϱ�
{
    cout << "������ ���Դϴ�." << endl;
    Sleep(1000);
    // ��ź�� ����ź�� ������ ����Ͽ� �ൿ ����
    if (shotgun.realBulletNum > shotgun.fakeBulletNum) // ��ź�� �� ������ �÷��̾� ���
    {
        cout << "�÷��̾�� �ѱ��� �ܴ��ϴ�." << endl;
        Sleep(1000);
        shotgun.Shoot(player, player, computer, shotgun);
        shotgun.playerTurn = true; // �÷��̾� ������ �Ѿ��
    }

    else if (shotgun.realBulletNum == shotgun.fakeBulletNum) {
        // ��ź�� ����ź�� ������ ������ �������� ����
        int random = rand() % 2;
        if (random == 0) // �ڽ� ���
        {
            cout << "�ڽ��� ���� �ѱ��� �ܴ��ϴ�." << endl;
            Sleep(1000);
            shotgun.Shoot(computer, player, computer, shotgun);
        }
        else // �÷��̾� ���
        {
            cout << "�÷��̾�� �ѱ��� �ܴ��ϴ�." << endl;
            Sleep(1000);
            shotgun.Shoot(player, player, computer, shotgun);
            shotgun.playerTurn = true; // �÷��̾� ������ �Ѿ��
        }
    }
    else // ����ź�� �� ������ �ڽ� ���
    {
        cout << "�ڽ��� ���� �ѱ��� �ܴ��ϴ�." << endl;
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

        if(shotgun.playerTurn == true) // �÷��̾� ��
            PlayerTurn(player, computer, shotgun, ui);
        else
            EnemyTurn(computer, player, shotgun, ui);
    }
    if(player.life == 0)
        ui.printCentered("�÷��̾ �й��߽��ϴ�.");
	else
        ui.printCentered("�÷��̾ �¸��߽��ϴ�.");
}