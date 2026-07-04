#pragma once

#include"easyx.h"
#include"ImageData.h"
#include"Utils.h"
#include<iostream>

//加载动画


//方法_声明
void yx_qdhm(bool sf_bfzhyzt = false);	//游戏启动画面，参数：是否播放最后一张图（默认为否）
void blcj();							//遍历场景
void dy_tsnr();							//打印提示内容（游戏开始时的提示（好...准备...开始！））

//方法_实现
void yx_qdhm(bool sf_bfzhyzt)
{
	//1.文件路径变量初始化
	string temp_Splash = Splash;

	bh = 0;
	sl = 0;

	//如果要求仅播放一张图片（需要修改两处）
	int jbfyz_zs = 0;		//仅播放一张图片时，从那张开始
	if (sf_bfzhyzt)			//如果要求仅播放一张图片
	{
		//方案一（长动画）
		temp_Splash = "Assets/Splash/yxqdhm47.jpg";	//图片从第113张开始播放（推荐：47、71、57）
		jbfyz_zs = 47;								//从第113张开始播放（最好：47、71）

	}

	hqbh(temp_Splash);								//获取编号、编号的数字长度（数字的位数）


	//2.绘图设备、消息变量初始化
	IMAGE qdhm;										//游戏启动画面

	ExMessage xx;									//判断鼠标点击
	bool temp_pd = false;							//判断是否可以停止播放画面，进行下一阶段
	flushmessage();									//清空消息缓冲区


	//3.遍历所有图片
	for (int i = 0;i < 139;i++)
	{
		//3.1 如果要求仅播放一张图片
		if (sf_bfzhyzt)			//如果要求仅播放一张图片
		{
			i = jbfyz_zs - 1;			//图片从第113张开始播放，i为0时为1，112时为113
			sf_bfzhyzt = false;
		}
		cout << temp_Splash << endl;
		//cout << "编号：" << bh << endl;

		//3.2 如果某张图片打开失败，则跳过这张图片
		if (!IsFileAccessible(temp_Splash))						//如果打开失败
		{
			gxlj2(temp_Splash, bh,sl);
			continue;
		}

		//3.3 打印该图片
		loadimage(&qdhm, temp_Splash.c_str(), ck_c, ck_k);
		putimage(0, 0, &qdhm);							//将启动画面打印在当前绘图窗口上

		Sleep(33);										//每秒30帧


		//3.4 更新图片的路径
		gxlj2(temp_Splash, bh, sl);


		//3.5 获取鼠标消息，判断是否退出播放启动画面环节
		if (i >= 112)	//如果当前为第113张图片
		{
			while (peekmessage(&xx, 1))					//获取一个消息，且仅获取鼠标消息，只要有消息，就会一直进入判断
			{
				if (xx.message == 0x202)				//如果为鼠标左键弹起
				{
					temp_pd = true;
					break;
				}
			}
		}
		else
		{
			flushmessage();									//清空消息缓冲区
		}

		//如果按下了鼠标左键
		if (temp_pd)
		{
			break;
		}
	}


	//4.已经遍历完所有图片，如果还没有退出进入下一环节，则在这里继续判断"是否退出播放启动画面环节"，直到退出
	sl = 1;											//使用完更新路径2后，需要重置一下编号数量，以免影响下一个使用更新路径2的路径

	if (temp_pd == false)							//如果过程中没有获取到鼠标左键弹起消息
	{
		while (1)
		{
			xx = getmessage();						//则在这里获取一次
			if (xx.message == 0x202)
			{
				break;
			}
		}
	}
	temp_pd = false;



}
void blcj()
{
	IMAGE temp_cj = { ck_c + 650,ck_k };				//临时场景
	string GameBackground = Raw_Misc_GameBackground;	//游戏场景路径


	//从左往右遍历
	for (int i = 0;i < 651;i += blcj_bfsd)
	{
		loadimage(&temp_cj, GameBackground.c_str(), ck_c + 650, ck_k);	//将图片加载到临时场景中
		SetWorkingImage(&temp_cj);						//设置当前绘图设备为临时场景

		getimage(&cj, i, 0, ck_c + i, ck_k);			//截取部分，给场景

		SetWorkingImage(NULL);							//设置当前绘图设备设置为图形界面窗口
		putimage(0, 0, &cj);							//将场景打印在当前绘图窗口上

		Sleep(20);

		if (i == 0)										//如果是第一次展示，则延时1秒
		{
			Sleep(1000);
		}
	}

	Sleep(1600);										//延时1.6秒

	int temp_tpx_cj = 650 % blcj_bfsd;					//图片x坐标_差距（计算场景从左遍历到最右端的过程中，x最大值）

	//从右往左遍历
	for (int i = 650 - temp_tpx_cj;i >= 230;i -= blcj_bfsd)	//初始x坐标必须跟上次播放的结尾一样，即650-图片x坐标_差距
	{
		loadimage(&temp_cj, GameBackground.c_str(), ck_c + 650, ck_k);	//将图片加载到临时场景中
		SetWorkingImage(&temp_cj);						//设置当前绘图设备为临时场景

		getimage(&cj, i, 0, ck_c + i, ck_k);			//截取部分，给场景

		SetWorkingImage(NULL);							//设置当前绘图设备设置为图形界面窗口
		putimage(0, 0, &cj);							//将场景打印在当前绘图窗口上

		Sleep(20);
	}

	//*/打印最后一张（场景的x轴最小值）z
	loadimage(&temp_cj, GameBackground.c_str(), ck_c + 650, ck_k);	//将图片加载到临时场景中
	SetWorkingImage(&temp_cj);						//设置当前绘图设备为临时场景

	getimage(&cj, 230, 0, ck_c + 230, ck_k);		//截取部分，给场景

	SetWorkingImage(NULL);							//设置当前绘图设备设置为图形界面窗口
	putimage(0, 0, &cj);							//将场景打印在当前绘图窗口上
	//*/
}
void dy_tsnr()
{
	setfillcolor(WHITE);						//将填充颜色设置为白色

	//打印：好
	int wz_x = 0;
	if (ck_c == 1100)
	{
		wz_x = 432;								//窗口长度：1100
	}
	else if (ck_c == 900)
	{
		wz_x = 332;								//窗口长度：900
	}
	//cout << wz_x << endl;

	int wz_y = 260;
	wz_y -= 20;

	putimage(wz_x, wz_y, &h_hb, SRCAND);		//叠加黑白图
	floodfill(wz_x + 20, wz_y + 28, BLACK, 1);	//将黑白填充为白色
	floodfill(wz_x + 60, wz_y + 43, BLACK, 1);
	floodfill(wz_x + 119, wz_y + 45, BLACK, 1);
	floodfill(wz_x + 171, wz_y + 45, BLACK, 1);
	floodfill(wz_x + 229, wz_y + 45, BLACK, 1);
	putimage(wz_x, wz_y, &h_sc, SRCAND);		//叠加色彩图

	Sleep(1000);								//延时1秒
	cleardevice();								//清屏


	//打印：准备...
	if (ck_c == 1100)
	{
		wz_x = 382;								//窗口长度：1100
	}
	else if (ck_c == 900)
	{
		wz_x = 282;								//窗口长度：900
	}

	wz_y = 256;
	wz_y -= 20;

	putimage(0, 0, &cj);						//打印场景

	putimage(wz_x, wz_y, &zb_hb, SRCAND);		//叠加黑白图
	floodfill(wz_x + 17, wz_y + 29, BLACK, 1);	//将黑白填充为白色
	floodfill(wz_x + 17, wz_y + 62, BLACK, 1);
	floodfill(wz_x + 38, wz_y + 42, BLACK, 1);
	floodfill(wz_x + 138, wz_y + 38, BLACK, 1);
	floodfill(wz_x + 136, wz_y + 66, BLACK, 1);
	floodfill(wz_x + 212, wz_y + 43, BLACK, 1);
	floodfill(wz_x + 266, wz_y + 43, BLACK, 1);
	floodfill(wz_x + 320, wz_y + 43, BLACK, 1);
	putimage(wz_x, wz_y, &zb_sc, SRCAND);		//叠加色彩图

	Sleep(1000);								//延时1秒
	cleardevice();								//清屏


	//打印：开始！
	if (ck_c == 1100)
	{
		wz_x = 424;								//窗口长度：1100
	}
	else if (ck_c == 900)
	{
		wz_x = 324;								//窗口长度：900
	}

	wz_y = 258;
	wz_y -= 20;

	putimage(0, 0, &cj);						//打印场景

	putimage(wz_x, wz_y, &ks_hb, SRCAND);		//叠加黑白图
	floodfill(wz_x + 58, wz_y + 43, BLACK, 1);	//将黑白填充为白色
	floodfill(wz_x + 123, wz_y + 45, BLACK, 1);
	floodfill(wz_x + 149, wz_y + 39, BLACK, 1);
	floodfill(wz_x + 155, wz_y + 79, BLACK, 1);
	floodfill(wz_x + 202, wz_y + 71, BLACK, 1);
	floodfill(wz_x + 204, wz_y + 27, BLACK, 1);
	putimage(wz_x, wz_y, &ks_sc, SRCAND);		//叠加色彩图

	Sleep(1000);								//延时1秒
	//cleardevice();							//清屏
}