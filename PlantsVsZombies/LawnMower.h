#pragma once

#include"easyx.h"

//小推车

//1.类
struct xtclx
{
	//int x = 25;			//窗口长度为1100时，小推车打印的x轴位置
	int x = 0;				//窗口长度为900时，小推车打印的x轴位置
	int y = 113;
	bool qd = false;		//小推车是否被启动
	bool xs = false;		//小推车是否消失
};

//2.方法_声明
void dy_xtcnr(int i, int y);			//打印小推车内容（参数：小推车数组中的第i个小推车，小推车的y坐标）

//3.数据
xtclx xtc[5];


//方法_实现
void dy_xtcnr(int i, int y)
{
	putimage(xtc[i].x, y, &xtc_hb, SRCAND);		//将小推车_黑白打印在场景(25,temp_y)处

	setfillcolor(WHITE);								//将填充颜色设置为白色
	floodfill(xtc[i].x + 40, y + 30, BLACK, 1);	//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(xtc[i].x, y, &xtc_sc, SRCAND);		//将小推车_色彩打印在场景(25,temp_y)处
}
