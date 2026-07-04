#pragma once

#include"GameData.h"
#include<iostream>

//调试工具模块


//游戏测试开关（发布版本请把这两个数值设为false）
bool cs_sb = 0;					//测试游戏失败用（赋值为1则开启测试，赋值为0则取消开启测试）
bool sb_sfdyqtnr = 0;			//游戏失败时，是否打印其他内容（小推车、场景阳光）


//方法_声明
void dy_bsnr();							//打印波数和已生成僵尸内容
void cs_yxms();							//测试游戏模式（测试内容：窗口长为1100、是否开启了游戏失败模式）

//方法_实现
void dy_bsnr()				//打印_波数内容
{
	//1.打印基础提示内容
	if (cs_sb)
	{
		cout << "第一天（测试模式已开启）" << endl;
	}
	else
	{
		cout << "第一天" << endl;
	}
	cout << "僵尸数量：" << zjssl << endl;


	//2.打印波数和已生成僵尸
	for (int i = 0;i < xygjs_bh;i++)
	{
		if (i == 0)
		{
			cout << endl;
			cout << "第一波（1~2）" << endl;
		}
		else if (i == 2)
		{
			cout << endl;
			cout << "第二波（3~4）" << endl;
		}
		else if (i == 4)
		{
			cout << endl;
			cout << "第三波（5~7）" << endl;
		}
		else if (i == 7)
		{
			cout << endl;
			cout << "第四波（8~10）" << endl;
		}

		cout << "已生成第" << i + 1 << "只僵尸" << endl;
	}

	//如果游戏胜利，并且已经开始播放游戏胜利音
	if (yx_sfsl && sf_ybfslyp)
	{
		cout << endl;
		cout << "游戏胜利" << endl;
	}

}
void cs_yxms()
{
	//1.草坪位置（窗口长为1100）
	if (ck_c == 1100)
	{
		cp_zzb_x = 88;			//草坪最左边
		cp_yg_x = 100;			//草坪一格的宽度
		cp_ts_x = 10;			//草坪_特殊x_差距
		zw_zxzzwz_x = 5;		//植物种植位置（植物中心位置，在图片中的x坐标）、种植在草坪时的偏移量
		yg_z_x = 120;			//阳光生成范围的x轴左边
		yg_y_x = 920;			//阳光生成范围的x轴右边

		for (int i = 0;i < 5;i++)
		{
			xtc[i].x = 38;
		}
	}

	//2.如果开启了游戏失败测试
	//测试游戏失败1（加快僵尸出现时间），共三处
	if (cs_sb)
	{
		js_cxjg = 13;			//僵尸出现间隔、22
		js_cxjg2 = 4;			//"一大波僵尸即将来袭"时的僵尸出现间隔（即后期的出怪速度）、14
		bs_jg = 3;				//波数_间隔、10
		sjpc = 1;				//僵尸生成间隔的随机偏差（不得大于或等于僵尸出现间隔）、4
		sgjs_cxsj = 2;			//首个僵尸_出现时间、25

		zjssl = 3;				//总僵尸数量
	}
}
