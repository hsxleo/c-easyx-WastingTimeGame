#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")//��Ƶ

IMAGE background;  //����ͼ

struct card {
	int style;  //��ɫ  ���� ��Ƭ  ÷�� ����  �ֱ�Ϊ 3 4 5 6
	int num;    //��ֵ 1 - 13
};

struct card hide[60];   //����������52����
int hide_index = 1;   //�����ڼ�������
struct card show[10];    //��ʾ������6����

int choose[2];  //ѡ��������Ƶ��±� 
int flg = 0;  //�Ƿ��п����ƶ�����
int flg_i = 0;  //�����ƶ����±�

int main();

//��ʾ
void hint() {
	int i;
	flg = 0;
	for (i = 1; i <= 6; i++) {
		if (show[i].num == show[i+3].num || show[i].style == show[i+3].style ) { // �ұߵ���ͬ�����ֻ��߻�ɫ
			flg = 1;
			flg_i = i;
			return;
		}
		else if (show[i].num == show[i + 1].num || show[i].style == show[i + 1].style) { //���ڵ���ͬ�����ֻ��߻�ɫ
			flg = 2;
			flg_i = i;
			return;
		}
	}
}

//���������
void randCard() {
	int i, j, k = 1;
	srand(unsigned(time(NULL)));   //���ʱ������
	for (i = 1; i <= 13; i++) {   //��˳��ֵ��hide
		for (j = 3; j <= 6; j++) {
			hide[k].num = i;
			hide[k].style = j;
			k++;
		}
	}

	int n = 50;   //�������⽻��50��
	while (n--) {
		int t1 = rand() % (k-1) + 1;
		int t2 = rand() % (k-1) + 1;
		struct card tmp = hide[t1];
		hide[t1] = hide[t2];
		hide[t2] = tmp;
	}

	//��6���Ƹ�show[]
	for (i = 1; i <= 6; i++) {
		show[i] = hide[hide_index++];
	}
}

//������Ϸ
void drawGame() {
	putimage(0, 0, &background);  //���ñ���ͼƬ

	//���� ���¿�ʼ �� �˳���Ϸ
	settextcolor(BLACK);          //����������ɫ
	settextstyle(30, 0, "������κ"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��
	outtextxy(800, 250, "��Ϸ��ʾ");
	outtextxy(800, 300, "���¿�ʼ");
	outtextxy(800, 350, "���ز˵�");

	//��ʽ ��ɫ ����
	setcolor(BLACK);          //������ɫ
	settextstyle(23,0, "terminal"); //����������ʽ
	setlinestyle(PS_SOLID);  //ʵ��
	//����6������
	int i;
	for (i = 1; i <= 6; i++) {
		rectangle(170 + i * 80, 150, 170 + (i + 1) * 80, 270);
	}

	//���6����
	char str[10], str2[10];
	for (i = 1; i <= 6; i++) {
		if (show[i].num != 0) {  //0Ϊû����
			//�жϻ�ɫ
			if (show[i].style <= 4) {
				setcolor(RED);
				sprintf(str, "%c", show[i].style);
			}
			else {
				setcolor(BLACK);
				sprintf(str, "%c", show[i].style);
			}


			//�ж�����
			switch (show[i].num) {
			case 1:
				strcat(str, "A");
				break;
			case 11:
				strcat(str, "J");
				break;
			case 12:
				strcat(str, "Q");
				break;
			case 13:
				strcat(str, "K");
				break;
			default:
				sprintf(str2, "%d", show[i].num);
				strcat(str, str2);
				break;
			}
			outtextxy(200 + i * 80, 200, str);
		}
	}

}

//��Ϸ����
void playGame() {
	MOUSEMSG m;  //������   ������ȡ�����Ϣ
	int n = 0;    //ÿ�����ж�һ��
	while (1) {
		//��ȡ���λ��
		m = GetMouseMsg();
		hint();
		if (flg == 0) {  //û�п����ƶ�������  ��Ϸʧ��
			settextcolor(RED);          //����������ɫ
			settextstyle(45, 0, "������κ"); //����������ʽ
			setbkmode(TRANSPARENT);       //���ֱ���͸��
			outtextxy(400, 60, "��Ϸʧ��");
		}
		int i;
		if (m.x >= 800 && m.x <= 920 && m.y >= 250 && m.y <= 280) {   //��Ϸ��ʾ
			if (m.uMsg == WM_LBUTTONDOWN) {   //��갴��
				hint();   //��Ϸ��ʾ
				if (flg == 1) {
					setcolor(GREEN);
					setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //�Ӵ�����
					rectangle(170 + flg_i * 80, 150, 170 + (flg_i + 1) * 80, 270);   //�̿������
					rectangle(170 + (flg_i + 3) * 80, 150, 170 + (flg_i + 4) * 80, 270);   //�̿������
				}
				else if (flg == 2) {
					setcolor(GREEN);
					setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //�Ӵ�����
					rectangle(170 + flg_i * 80, 150, 170 + (flg_i + 1) * 80, 270);   //�̿������
					rectangle(170 + (flg_i + 1) * 80, 150, 170 + (flg_i + 2) * 80, 270);   //�̿������
				}
			}
		}
		else if (m.x >= 800 && m.x <= 920 && m.y >= 300 && m.y <= 330) {   //���¿�ʼ
			if (m.uMsg == WM_LBUTTONDOWN) {   //��갴��
				main();   //���¿�ʼ��Ϸ
			}
		}
		else if (m.x >= 800 && m.x <= 920 && m.y >= 350 && m.y <= 380) {  //�˳���Ϸ
			if (m.uMsg == WM_LBUTTONDOWN) {   //��갴��
				exit(0);   //�˳���Ϸ
			}
		}
		else {
			for (i = 1; i <= 6; i++) {
				if (m.x >= 170 + i * 80 && m.x <= 170 + (i + 1) * 80 && m.y >= 150 && m.y <= 270) {   //�ж����λ��
					if (m.uMsg == WM_LBUTTONDOWN) {   //��갴��
						choose[n] = i;  //ѡ��һ��
						setcolor(RED);
						setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //�Ӵ�����
						rectangle(170 + i * 80, 150, 170 + (i + 1) * 80, 270);   //��ѡ�е�ͼƬ�ú�������
						n++;
						break;
					}
				}
			}
			if (n > 1) {  //�����Ƶ�ʱ��
				n = 0;  
				if(choose[1] - choose[0] == 1 || choose[1] - choose[0] == 3){  //���ڻ����ұߵ�
					if (show[choose[0]].num == show[choose[1]].num || show[choose[0]].style == show[choose[1]].style) {  //��ͬ�����ֻ��߻�ɫ
						show[choose[1]] = show[choose[0]];  //������
						show[choose[0]] = hide[hide_index++];  //ԭ���ĵط�����
					}
				}
				Sleep(300);  //����0.3��
				cleardevice();  //��ջ���
				drawGame();
				if (hide_index == 56) {  //��Ϸʤ��
					settextcolor(RED);          //����������ɫ
					settextstyle(45, 0, "������κ"); //����������ʽ
					setbkmode(TRANSPARENT);       //���ֱ���͸��
					outtextxy(400, 60, "��Ϸʤ��");
				}
			}
		}
	}
}

int main() {
	//��������
	mciSendString("open music.mp3 alias game", nullptr, 0, nullptr);
	mciSendString("play game repeat", nullptr, 0, nullptr);

	//��ʼ��
	memset(hide, 0, sizeof(hide));
	memset(show, 0, sizeof(show));
	hide_index = 1;

	//������Դ
	loadimage(&background, "background.jpg", 1000, 400);  //��ȡ����ͼƬ
	initgraph(1000, 400);  //���ɻ���

	randCard();
	drawGame();
	playGame();
}