#pragma once

#include"easyx.h"
#include"Plants.h"
#include"Projectiles.h"
#include"LawnMower.h"
#include"DebugTools.h"

//僵尸

//1.类
struct jslx
{
	int x;
	int y;
	int js_lx;			//僵尸类型（目前只有一种僵尸，先不管）
	int tp = 0;			//当前为第几张图片
	int xl = 100;		//僵尸的血量
	int js_ydsd = 3;	//僵尸_移动速度
	int js_ydsd2 = 4;	//僵尸_第二移动速度

	bool dddh = false;	//是否播放倒地动画
	int dd_tp = 0;		//倒地动画图片张数

	bool jsgj = false;	//僵尸攻击
	int gj_tp = 0;		//攻击图片张数

	int h = 0;

	int sh = 50;		//僵尸的攻击伤害
	int gj_sj = 0;		//僵尸的攻击时间
	//zwlx* js_zw;		//僵尸的攻击对象
};

//2.方法_声明
void jscxsj_sz();				//僵尸出现时间_设置
void sc_js();					//生成僵尸
void dy_jsnr(int i);			//打印僵尸内容（参数：僵尸数组中的第i个僵尸）
void dy_js(int sf_jgxdgjs = -1);//打印僵尸（参数：是否_仅更新单个僵尸（有默认参数，默认参数为-1），输入大于或等于0的编号时，只更新这个僵尸的坐标）
void cxpl_js(int wz);			//重新排列僵尸数组

//3.数据
jslx js[255];
int js_sl = 0;					//当前僵尸数量
zwlx* js_gjdx[255];				//僵尸攻击对象

//方法_实现
void jscxsj_sz()				//僵尸出现时间_设置
{
	//调整僵尸出现的随机偏差值
	if (js_cxjg <= sjpc)		//如果僵尸出现间隔，小于或等于随机偏差（那么随机偏差会变成负数）
	{
		sjpc = js_cxjg - 1;		//让随机偏差一定要比js_cxjg小		
	}
	if (sjpc < 0)				//第二部保险，如果随机偏差为负数
	{
		sjpc = 0;				//则让随即偏差变为0
	}

	//设置僵尸出现时间
	int ym = 1000;

	//首个僵尸_出现时间
	js_cxsj[0] = sgjs_cxsj * ym;

	//第2~10个僵尸的出现时间
	for (int i = 1;i < zjssl;i++)
	{
		//测试游戏失败3（加快进入"一大波僵尸即将来袭"状态），共三处
		if (cs_sb && i == 2)
		{
			js_cxjg = js_cxjg2;	//则减少僵尸出现间隔（加快僵尸出现速度）
		}
		//正常内容
		else if (i == 4)		//当波次来到第三波（游戏后期）
		{
			js_cxjg = js_cxjg2;	//则减少僵尸出现间隔（加快僵尸出现速度）
		}

		js_cxsj[i] = js_cxsj[i - 1] + sc_sjfw(js_cxjg, sjpc, ym);		//上一个僵尸的出现时间 + 16~24秒

		if (i == 2 || i == 4 || i == 7)		//如果为该僵尸为新的波次
		{
			js_cxsj[i] += sc_sjfw(bs_jg, sjpc, ym);
		}
	}
}
void sc_js()					//生成僵尸
{
	//int js_temp_h = rand() % 5 + 1;			//僵尸出现在哪行
	int js_temp_h = GetRandomNumber(1, 5);		//僵尸出现在哪行

	int js_temp_x = ck_c - 34;					//僵尸的x坐标

	//*/测试游戏失败2（修改僵尸出现的起始x坐标，并且固定行数，取消原随机结果），共三处
	if (cs_sb)
	{
		js_temp_x = 200;
		js_temp_h = 4;
	}
	//*/

	int js_temp_y = js_temp_h * 100 + 61;		//僵尸的y坐标

	js_temp_x -= 62;
	js_temp_y -= 127;					//僵尸的脚位于图片的127的y坐标

	//测试用
	//js_temp_x = 150;


	if (js_temp_h == 4)
	{
		js_temp_y -= 10;				//如果在第4行，y坐标需要-10
	}

	jslx js_temp;						//生成一个临时僵尸类型变量
	js_temp.x = js_temp_x;				//将这些属性赋值给临时僵尸类型变量
	js_temp.y = js_temp_y;
	js_temp.h = js_temp_h;
	js_temp.tp = 0;

	js[js_sl] = js_temp;				//将该临时僵尸类型变量赋值给僵尸
	js_sl++;							//让僵尸的数量加1
}
void dy_jsnr(int i)
{
	if (js[i].jsgj)													//如果僵尸处于攻击状态，打印攻击画面
	{
		putimage(js[i].x, js[i].y, &jsgj_hb[js[i].gj_tp], SRCAND);	//将僵尸_黑白打印在指定位置

		setfillcolor(WHITE);										//将填充颜色设置为白色
		floodfill(js[i].x + 94, js[i].y + 67, BLACK, 1);			//从黑色区域开始，只要相邻处为黑色，就填充为白色
		putimage(js[i].x, js[i].y, &jsgj_sc[js[i].gj_tp], SRCAND);	//将僵尸移动_色彩打印在指定位置
	}
	else														//否则，打印移动画面
	{
		putimage(js[i].x, js[i].y, &jsyd_hb[js[i].tp], SRCAND);	//将僵尸_黑白打印在指定位置

		setfillcolor(WHITE);									//将填充颜色设置为白色
		floodfill(js[i].x + 94, js[i].y + 67, BLACK, 1);		//从黑色区域开始，只要相邻处为黑色，就填充为白色
		putimage(js[i].x, js[i].y, &jsyd_sc[js[i].tp], SRCAND);	//将僵尸移动_色彩打印在指定位置
	}
}
void dy_js(int sf_jgxdgjs)			//参数：是否_仅更新单个僵尸（有默认参数，默认参数为-1），输入大于或等于0的编号时，只更新这个编号的僵尸的坐标
{
	int x_cj = 0;					//x轴的差距

	for (int i = 0;i < js_sl;i++)
	{
		//1.判断僵尸是否死亡
		if (js[i].xl <= 0)										//如果僵尸的血量为0
		{
			cxpl_js(i);

			//cout << "僵尸死亡" << endl;
			ysw_js_sl++;						//记录已死亡僵尸数量+1

			if (ysw_js_sl == zjssl)				//如果已死亡僵尸数，等于总僵尸数
			{
				zh_js_swsj = dq_game_time;		//将最后一个僵尸的死亡时间，设置为当前游戏时间
				//cout << "最后一个僵尸的死亡时间：" << zh_js_swsj << endl;


				//游戏胜利记录
				yx_sfsl = true;
			}

			i--;
			continue;
		}

		//2.判断僵尸图片打印内容
		dy_jsnr(i);

		//当为特殊情况（仅允许更新单个僵尸时），跳过后面的逻辑处理（图片更新、坐标移动）内容
		if (sf_jgxdgjs != -1 && i != sf_jgxdgjs)	//当只允许打印一个僵尸，且当前僵尸就不为指定僵尸时
		{
			continue;								//跳过该僵尸的打印
		}

		//3.判断僵尸执行逻辑
		//3.1 判断僵尸前面是否有植物，是否进入攻击状态
		int pd = false;
		for (int j = 0;j < zw_sl;j++)						//遍历所有植物
		{
			x_cj = zw[j].x - js[i].x;						//x轴的差距
			if (x_cj >= 6 && x_cj <= 65 && zw[j].h == js[i].h)	//如果植物的位置在僵尸前面
			{
				js[i].jsgj = true;							//则记录僵尸开始攻击
				pd = true;									//记录僵尸前面有植物
				js_gjdx[i] = &zw[j];						//将僵尸的攻击对象记录为该植物
				break;
			}
		}

		if (pd == false)					//如果僵尸前面并没有植物
		{
			js[i].jsgj = false;				//将僵尸的攻击状态设置为否
		}

		//3.2 僵尸处于攻击状态的内容
		if (js[i].jsgj)						//如果僵尸处于攻击状态
		{
			js[i].gj_tp++;					//更新下次图片为下一张
			if (js[i].gj_tp == jsgj_tpsl)	//如果为最后一张图片，就更新为第一张
			{
				js[i].gj_tp = 0;
			}

			if (js[i].gj_sj >= jsgj_jg)		//如果僵尸的攻击时间大于或等于500
			{
				js[i].gj_sj -= jsgj_jg;		//让时间减少500
				js_gjdx[i]->xl -= js[i].sh;	//让对应植物的血量减少，减少数值为僵尸的伤害数值
				if (js_gjdx[i]->xl <= 0)	//如果植物的血量为0了
				{
					js[i].jsgj = false;		//则僵尸退出攻击状态
					js[i].gj_sj = 0;		//重置攻击时间
					js[i].gj_tp = 0;		//重置攻击图片
					js[i].tp = 0;			//重置僵尸移动图片
				}
			}
			js[i].gj_sj += yx_jg;				//让攻击时间增加
		}

		//3.3 僵尸的坐标是否触碰到小推车逻辑、僵尸移动逻辑
		else								//如果僵尸不处于攻击状态（僵尸_移动）
		{
			int x_cj2 = 0;
			for (int j = 0;j < 5;j++)
			{
				x_cj2 = xtc[j].x - js[i].x - 13;
				if (x_cj2 <= 2 && x_cj2 >= -2 && js[i].h == j + 1)		//如果僵尸的x位置在小推车前面，且僵尸与小推车同行
				{
					xtc[j].qd = true;		//则启动该小推车
					break;
				}

			}
			js[i].tp++;						//更新下次图片为下一张

			if (js[i].tp >= 7 - 1 && js[i].tp <= 20 - 1)	//如果当前僵尸的移动图片为第7~第20张，
			{
				js[i].x -= js[i].js_ydsd;					//则让僵尸的x轴往前移动一段距离（让僵尸移动一段距离）
			}
			else if (js[i].tp >= 26 - 1 && js[i].tp <= 33 - 1)//如果当前僵尸的移动图片为第26~第33张，
			{
				js[i].x -= js[i].js_ydsd2;					//则让僵尸的x轴往前移动一段距离（让僵尸移动一段距离）
			}

			if (js[i].tp == jsyd_tpsl)			//如果僵尸的当前移动图片，已经播放到最后一张
			{
				js[i].tp = 0;					//则设置为第一张
			}
		}
	}
}
void cxpl_js(int wz)						//重新排列僵尸数组
{
	for (int i = wz;i < js_sl - 1;i++)
	{
		js[i] = js[i + 1];
	}
	js_sl--;
}