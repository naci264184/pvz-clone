#pragma once


//类
#include"easyx.h"
#include"sunlight.h"
#include"GameData.h"
#include"AudioManager.h"


//释放物

//1.类
struct sfwlx
{
	int lx;				//释放物类型，1为向日葵（阳光），2为豌豆（直线移动）
	int sj = 0;			//时间，用于判断是否播放释放物的第二动画
	int x;				//释放物位置
	int y;
	int tp = 0;			//某些释放物具体多张图片（如阳光）

	int yg_dj = 0;
	int yg_ydx;
	int yg_ydy;

	int h = 0;
};

//2.方法_声明
void dy_ygnr(int i);					//打印向日葵产生的阳光（参数：释放物数组中的第i个释放物）
void dy_wdnr(int i);					//打印豌豆射手发射的豌豆（参数：释放物数组中的第i个释放物）
void cxpl_sfw(int wz);					//重新排列释放物数组

//3.数据
sfwlx sfw[255];
int sfw_sl = 0;


//方法_实现
void dy_ygnr(int i)
{
	putimage(sfw[i].x, sfw[i].y, &yg_hb[sfw[i].tp], SRCAND);	//将阳光_黑白打印在指定位置

	setfillcolor(WHITE);										//将填充颜色设置为白色
	floodfill(sfw[i].x + 39, sfw[i].y + 42, BLACK, 1);			//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(sfw[i].x, sfw[i].y, &yg_sc[sfw[i].tp], SRCAND);	//将阳光_色彩打印在指定位置
}
void dy_wdnr(int i)
{
	putimage(sfw[i].x, sfw[i].y, &wd_hb, SRCAND);			//将豌豆_黑白打印在指定位置

	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(sfw[i].x + 15, sfw[i].y + 16, BLACK, 1);		//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(sfw[i].x, sfw[i].y, &wd_sc, SRCAND);			//将豌豆_色彩打印在指定位置
}
void cxpl_sfw(int wz)						//重新排列释放物数组
{
	for (int i = wz;i < sfw_sl - 1;i++)
	{
		sfw[i] = sfw[i + 1];
	}
	sfw_sl--;
}