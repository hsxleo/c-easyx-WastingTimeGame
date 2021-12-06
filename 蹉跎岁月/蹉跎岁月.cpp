#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")//音频

IMAGE background;  //背景图

struct card {
	int style;  //花色  红桃 方片  梅花 黑桃  分别为 3 4 5 6
	int num;    //数值 1 - 13
};

struct card hide[60];   //用于随机存放52张牌
int hide_index = 1;   //发到第几张牌了
struct card show[10];    //显示出来的6张牌

int choose[2];  //选择的两张牌的下标 
int flg = 0;  //是否还有可以移动的牌
int flg_i = 0;  //可以移动的下标

int main();

//提示
void hint() {
	int i;
	flg = 0;
	for (i = 1; i <= 6; i++) {
		if (show[i].num == show[i+3].num || show[i].style == show[i+3].style ) { // 右边的相同的数字或者花色
			flg = 1;
			flg_i = i;
			return;
		}
		else if (show[i].num == show[i + 1].num || show[i].style == show[i + 1].style) { //相邻的相同的数字或者花色
			flg = 2;
			flg_i = i;
			return;
		}
	}
}

//随机生成牌
void randCard() {
	int i, j, k = 1;
	srand(unsigned(time(NULL)));   //随机时间种子
	for (i = 1; i <= 13; i++) {   //按顺序赋值给hide
		for (j = 3; j <= 6; j++) {
			hide[k].num = i;
			hide[k].style = j;
			k++;
		}
	}

	int n = 50;   //两两随意交换50次
	while (n--) {
		int t1 = rand() % (k-1) + 1;
		int t2 = rand() % (k-1) + 1;
		struct card tmp = hide[t1];
		hide[t1] = hide[t2];
		hide[t2] = tmp;
	}

	//发6张牌给show[]
	for (i = 1; i <= 6; i++) {
		show[i] = hide[hide_index++];
	}
}

//绘制游戏
void drawGame() {
	putimage(0, 0, &background);  //放置背景图片

	//绘制 重新开始 和 退出游戏
	settextcolor(BLACK);          //设置字体颜色
	settextstyle(30, 0, "华文新魏"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明
	outtextxy(800, 250, "游戏提示");
	outtextxy(800, 300, "重新开始");
	outtextxy(800, 350, "返回菜单");

	//样式 颜色 设置
	setcolor(BLACK);          //设置颜色
	settextstyle(23,0, "terminal"); //设置文字样式
	setlinestyle(PS_SOLID);  //实线
	//绘制6个矩形
	int i;
	for (i = 1; i <= 6; i++) {
		rectangle(170 + i * 80, 150, 170 + (i + 1) * 80, 270);
	}

	//输出6张牌
	char str[10], str2[10];
	for (i = 1; i <= 6; i++) {
		if (show[i].num != 0) {  //0为没有牌
			//判断花色
			if (show[i].style <= 4) {
				setcolor(RED);
				sprintf(str, "%c", show[i].style);
			}
			else {
				setcolor(BLACK);
				sprintf(str, "%c", show[i].style);
			}


			//判断数字
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

//游戏进行
void playGame() {
	MOUSEMSG m;  //鼠标变量   用来获取鼠标信息
	int n = 0;    //每两次判断一次
	while (1) {
		//获取鼠标位置
		m = GetMouseMsg();
		hint();
		if (flg == 0) {  //没有可以移动的牌了  游戏失败
			settextcolor(RED);          //设置字体颜色
			settextstyle(45, 0, "华文新魏"); //设置文字样式
			setbkmode(TRANSPARENT);       //文字背景透明
			outtextxy(400, 60, "游戏失败");
		}
		int i;
		if (m.x >= 800 && m.x <= 920 && m.y >= 250 && m.y <= 280) {   //游戏提示
			if (m.uMsg == WM_LBUTTONDOWN) {   //鼠标按下
				hint();   //游戏提示
				if (flg == 1) {
					setcolor(GREEN);
					setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //加粗虚线
					rectangle(170 + flg_i * 80, 150, 170 + (flg_i + 1) * 80, 270);   //绿框框起来
					rectangle(170 + (flg_i + 3) * 80, 150, 170 + (flg_i + 4) * 80, 270);   //绿框框起来
				}
				else if (flg == 2) {
					setcolor(GREEN);
					setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //加粗虚线
					rectangle(170 + flg_i * 80, 150, 170 + (flg_i + 1) * 80, 270);   //绿框框起来
					rectangle(170 + (flg_i + 1) * 80, 150, 170 + (flg_i + 2) * 80, 270);   //绿框框起来
				}
			}
		}
		else if (m.x >= 800 && m.x <= 920 && m.y >= 300 && m.y <= 330) {   //重新开始
			if (m.uMsg == WM_LBUTTONDOWN) {   //鼠标按下
				main();   //重新开始游戏
			}
		}
		else if (m.x >= 800 && m.x <= 920 && m.y >= 350 && m.y <= 380) {  //退出游戏
			if (m.uMsg == WM_LBUTTONDOWN) {   //鼠标按下
				exit(0);   //退出游戏
			}
		}
		else {
			for (i = 1; i <= 6; i++) {
				if (m.x >= 170 + i * 80 && m.x <= 170 + (i + 1) * 80 && m.y >= 150 && m.y <= 270) {   //判断鼠标位置
					if (m.uMsg == WM_LBUTTONDOWN) {   //鼠标按下
						choose[n] = i;  //选择一个
						setcolor(RED);
						setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //加粗虚线
						rectangle(170 + i * 80, 150, 170 + (i + 1) * 80, 270);   //把选中的图片用红框框起来
						n++;
						break;
					}
				}
			}
			if (n > 1) {  //两张牌的时候
				n = 0;  
				if(choose[1] - choose[0] == 1 || choose[1] - choose[0] == 3){  //相邻或者右边的
					if (show[choose[0]].num == show[choose[1]].num || show[choose[0]].style == show[choose[1]].style) {  //相同的数字或者花色
						show[choose[1]] = show[choose[0]];  //覆盖上
						show[choose[0]] = hide[hide_index++];  //原来的地方补牌
					}
				}
				Sleep(300);  //休眠0.3秒
				cleardevice();  //清空画布
				drawGame();
				if (hide_index == 56) {  //游戏胜利
					settextcolor(RED);          //设置字体颜色
					settextstyle(45, 0, "华文新魏"); //设置文字样式
					setbkmode(TRANSPARENT);       //文字背景透明
					outtextxy(400, 60, "游戏胜利");
				}
			}
		}
	}
}

int main() {
	//播放音乐
	mciSendString("open music.mp3 alias game", nullptr, 0, nullptr);
	mciSendString("play game repeat", nullptr, 0, nullptr);

	//初始化
	memset(hide, 0, sizeof(hide));
	memset(show, 0, sizeof(show));
	hide_index = 1;

	//加载资源
	loadimage(&background, "background.jpg", 1000, 400);  //读取背景图片
	initgraph(1000, 400);  //生成画布

	randCard();
	drawGame();
	playGame();
}