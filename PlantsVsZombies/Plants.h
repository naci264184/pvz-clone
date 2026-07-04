#pragma once

#include"easyx.h"
#include"imagedata.h"
#include"projectiles.h"


//植物

//1.类
struct zwlx
{
	int x;
	int y;
	int kc_bh;			//为卡槽中的第几种植物
	int tp;				//为当前第几张图片
	int sj = 0;			//用于判断是否产生释放物（播放释放物的第一动画）

	int h = 0;			//行
	int l = 0;			//列

	int xl = 300;		//植物的血量
	int zt = 1;			//植物的状态（部分植物具有多种状态，如：坚果（完整、破损、残缺）
};

//2.方法_声明
void dy_zwnr(int i, int zl, int zt = 1);	//打印植物内容（参数：植物数组中的第i个植物，该植物的种类）
void cxpl_zw(int wz);						//重新排列植物数组

//3.数据
zwlx zw[45];
int zw_sl = 0;								//当前植物数量
int jg_xl = 4000;							//坚果的血量

//方法_实现
void dy_zwnr(int i, int zl, int zt)
{
	if (zl == 1)
	{
		putimage(zw[i].x, zw[i].y, &xrk_hb[zw[i].tp], SRCAND);	//将向日葵_黑白打印在种植位置

		setfillcolor(WHITE);									//将填充颜色设置为白色
		floodfill(zw[i].x + 32, zw[i].y + 22, BLACK, 1);		//从黑色区域开始，只要相邻处为黑色，就填充为白色
		putimage(zw[i].x, zw[i].y, &xrk_sc[zw[i].tp], SRCAND);	//将向日葵_色彩打印在种植位置处	
	}
	else if (zl == 2)
	{
		putimage(zw[i].x, zw[i].y, &wdss_hb[zw[i].tp], SRCAND);	//将豌豆射手_黑白打印在种植位置处	

		setfillcolor(WHITE);									//将填充颜色设置为白色
		floodfill(zw[i].x + 32, zw[i].y + 22, BLACK, 1);		//从黑色区域开始，只要相邻处为黑色，就填充为白色
		putimage(zw[i].x, zw[i].y, &wdss_sc[zw[i].tp], SRCAND);	//将豌豆射手_色彩打印在种植位置处
	}
	else if (zl == 3)
	{
		if (zt == 1)					//如果坚果状态为：完整
		{
			putimage(zw[i].x, zw[i].y, &jg_hb[zw[i].tp], SRCAND);	//将坚果_黑白打印在种植位置处	

			setfillcolor(WHITE);									//将填充颜色设置为白色
			floodfill(zw[i].x + 32, zw[i].y + 22, BLACK, 1);		//从黑色区域开始，只要相邻处为黑色，就填充为白色
			putimage(zw[i].x, zw[i].y, &jg_sc[zw[i].tp], SRCAND);	//将坚果_色彩打印在种植位置处
		}
		else if (zt == 2)				//如果坚果状态为：破损
		{
			putimage(zw[i].x, zw[i].y, &jg_ps_hb[zw[i].tp], SRCAND);	//将坚果_黑白打印在种植位置处	

			setfillcolor(WHITE);										//将填充颜色设置为白色
			floodfill(zw[i].x + 32, zw[i].y + 22, BLACK, 1);			//从黑色区域开始，只要相邻处为黑色，就填充为白色
			putimage(zw[i].x, zw[i].y, &jg_ps_sc[zw[i].tp], SRCAND);	//将坚果_色彩打印在种植位置处
		}
		else if (zt == 3)				//如果坚果状态为：残缺
		{
			putimage(zw[i].x, zw[i].y, &jg_wx_hb[zw[i].tp], SRCAND);	//将坚果_黑白打印在种植位置处	

			setfillcolor(WHITE);										//将填充颜色设置为白色
			floodfill(zw[i].x + 32, zw[i].y + 22, BLACK, 1);			//从黑色区域开始，只要相邻处为黑色，就填充为白色
			putimage(zw[i].x, zw[i].y, &jg_wx_sc[zw[i].tp], SRCAND);	//将坚果_色彩打印在种植位置处
		}
	}
}
void cxpl_zw(int wz)					//重新排列植物数组
{
	for (int i = wz;i < zw_sl - 1;i++)
	{
		zw[i] = zw[i + 1];
	}
	zw_sl--;
}
