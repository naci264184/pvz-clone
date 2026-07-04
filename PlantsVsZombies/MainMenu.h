#pragma once

#include"easyx.h"
#include"ImageData.h"
#include"Utils.h"
#include<iostream>

//主菜单


//方法_声明
bool yx_xzjm();							//游戏选择界面


//方法_实现
bool yx_xzjm()
{
	//1.文件路径变量初始化
	string temp_MainMenu = MainMenu;

	bh = 0;
	sl = 0;

	hqbh(temp_MainMenu);								//获取编号、编号的数字长度（数字的位数）


	//2.绘图设备、消息变量初始化
	IMAGE xzjm;									//选择界面
	IMAGE qdhm;									//游戏启动画面
	ExMessage xx;								//判断鼠标点击
	bool temp_pd = false;						//判断是否可以停止播放画面，进行下一阶段
	flushmessage();								//清空消息缓冲区

	//3.画面中，按钮的坐标
	//（1）窗口大小为（900，600）的情况
	//"开始冒险吧"按钮
	int ksmx_min_x = 460;			//"开始冒险吧"的左侧x坐标
	int ksmx_max_x = 820;			//"开始冒险吧"的右侧x坐标
	int ksmx_min_y = 80;			//"开始冒险吧"的上面y坐标
	int ksmx_max_y = 181;			//"开始冒险吧"的下面y坐标

	//"退出"按钮
	int tc_min_x = 793;				//"退出"的左侧x坐标
	int tc_max_x = 876;				//"退出"的右侧x坐标
	int tc_min_y = 480;				//"退出"的上面y坐标
	int tc_max_y = 550;				//"退出"的下面y坐标

	//（2）窗口大小为（1100，600）的情况
	//"开始冒险吧"按钮
	if (ck_c == 1100)
	{
		ksmx_min_x = 560;			//"开始冒险吧"的左侧x坐标
		ksmx_max_x = 1000;			//"开始冒险吧"的右侧x坐标
		ksmx_min_y = 75;			//"开始冒险吧"的上面y坐标
		ksmx_max_y = 175;			//"开始冒险吧"的下面y坐标

		//2.2 "退出"按钮
		tc_min_x = 969;				//"退出"的左侧x坐标
		tc_max_x = 1072;			//"退出"的右侧x坐标
	}

	//4.遍历所有图片
	for (int i = 0;i < 29;i++)
	{
		//4.1 如果某张图片打开失败，则跳过这张图片
		if (!IsFileAccessible(temp_MainMenu))						//如果打开失败
		{
			gxlj2(temp_MainMenu, bh,sl);
			continue;
		}

		//4.2 打印该图片
		loadimage(&qdhm, temp_MainMenu.c_str(), ck_c, ck_k);
		putimage(0, 0, &qdhm);						//将启动画面打印在当前绘图窗口上

		Sleep(33);									//每秒30帧

		//4.3 更新图片的路径
		gxlj2(temp_MainMenu, bh,sl);


		//4.4 获取鼠标消息，判断接下来"进入游戏"或者"返回"
		if (i >= 9)
		{
			while (peekmessage(&xx, 1))					//获取一个消息，且仅获取鼠标消息，只要有消息，就会一直进入判断
			{
				if (xx.message == 0x202)				//如果为鼠标左键弹起
				{
					//如果按下"开始冒险吧"（后面会直接进入游戏）
					if (xx.x >= ksmx_min_x && xx.x <= ksmx_max_x && xx.y >= ksmx_min_y && xx.y <= ksmx_max_y)
					{
						temp_pd = true;
						break;
					}
					//如果按下"退出"（后面会返回游戏启动画面的最后一张图）
					else if (xx.x >= tc_min_x && xx.x <= tc_max_x && xx.y >= tc_min_y && xx.y <= tc_max_y)
					{
						system("cls");
						cout << "返回" << endl;

						return true;
					}
				}
			}
		}
		else
		{
			flushmessage();								//清空消息缓冲区
		}
		if (temp_pd)
		{
			break;
		}
	}


	//4.已经遍历完所有图片，如果还没有进入下一环节，则在这里继续判断：接下来"进入游戏"或者"返回"
	sl = 1;
	if (temp_pd == false)							//如果过程中没有获取到消息
	{
		while (1)
		{
			xx = getmessage();
			if (xx.message == WM_LBUTTONUP)			//如果为鼠标左键弹起
			{

				//如果按下"开始冒险吧"（后面会直接进入游戏）
				if (xx.x >= ksmx_min_x && xx.x <= ksmx_max_x && xx.y >= ksmx_min_y && xx.y <= ksmx_max_y)
				{
					temp_pd = true;
					break;
				}
				//如果按下"退出"（后面会返回游戏启动画面的最后一张图）
				else if (xx.x >= tc_min_x && xx.x <= tc_max_x && xx.y >= tc_min_y && xx.y <= tc_max_y)
				{
					system("cls");
					cout << "返回" << endl;

					return true;
				}
			}
		}
	}

	return false;
}
