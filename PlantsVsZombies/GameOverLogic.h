#pragma once

#include"GameData.h"			//数据
#include"Zombies.h"				//类
#include"AudioManager.h"		//音频
#include"Renderer.h"			//游戏循环_渲染模块
#include<iostream>

//游戏结局模块


//方法_声明

//1.游戏结局
bool CheckWinCondition();			//游戏胜利结局
bool CheckLoseCondition();			//游戏失败结局

//2.其他_方法（游戏失败结局内容）
bool pd_yx_sb();					//判断游戏是否失败
void bf_yx_sbhm();					//播放_游戏失败画面
void js_yz_bh();					//僵尸从安全线进入到房子的y轴变化


//方法_实现
bool CheckWinCondition()
{
	if (sf_ybfslyp == false && yx_sfsl)			//如果游戏胜利，并且未播放游戏胜利音频
	{
		if (dq_game_time > zh_js_swsj + slh_djfyp * 1000)		//如果游戏胜利时间已经超过6秒
		{
			//关闭音乐3
			Turn_off_audio(mysong);

			//播放游戏胜利音
			Play_audio(Audio_yxsly, mysong);

			//更新已播放游戏胜利音，并打印游戏胜利
			sf_ybfslyp = true;
			system("cls");
			dy_bsnr();			
		}

		return true;
	}

	return false;
}
bool CheckLoseCondition()
{
	if (pd_yx_sb())				//如果游戏失败
	{
		cout << endl;
		cout << "游戏失败" << endl;
		bf_yx_sbhm();

		cout << "游戏结束" << endl;
		//system("pause");		

		return true;
	}

	return false;
}
bool pd_yx_sb()				//游戏失败
{
	int js_pz_z_yxwz = 0;					 // 僵尸左边界

	for (int i = 0;i < js_sl;i++)			//遍历所有僵尸
	{
		js_pz_z_yxwz = js[i].x + 75;		//房子的安全线

		if (js_pz_z_yxwz <= 0)				//如果某个僵尸已越过安全线
		{
			yg_aqx_bh = i;					//记录该僵尸的编号

			return true;					//游戏失败，返回true
		}
	}

	return false;
}
void bf_yx_sbhm()
{
	//关闭音乐3
	Turn_off_audio(mysong);

	Sleep(1500);

	int temp_xhbl_js = 1;			//偏移次数，这里用于计算每次移动的偏移量（偏移次数×遍历场景的播放速度=下一次移动的量）
	int temp_yz_sj = yx_jg - 50;	//一帧的时间 - 50
	int aqx_dfz_sj = 5000;			//僵尸从安全线走到房子需要花的时间

	//1.从右往左遍历
	for (int i = 230;i >= 0;i -= blcj_bfsd)	//初始x坐标必须跟上次播放的结尾一样，即650-图片x坐标_差距
	{
		//1.获取整个完整场景的所有内容
		myz_wzcj(blcj_bfsd * temp_xhbl_js, blcj_bfsd);

		//2.打印完整场景
		cleardevice();				//清屏
		putimage(0, 0, &wzcj);

		temp_xhbl_js++;
		Sleep(temp_yz_sj);
	}

	//2.让僵尸走入房子
	Sleep(1200);
	temp_yz_sj = yx_jg;

	//2.1 这里需要重新获取一次不带僵尸的完整场景（后面会单独打印僵尸），并且获取期间不能修改植物、僵尸类坐标数值
	temp_xhbl_js--;
	myz_wzcj_bxg(blcj_bfsd * temp_xhbl_js, false);

	//2.2 让僵尸走入房子
	for (int i = aqx_dfz_sj;i >= 0;i -= temp_yz_sj)
	{
		cleardevice();				//清屏
		putimage(0, 0, &wzcj);		//打印完整场景
		dy_js(yg_aqx_bh);			//仅更新越过安全线的僵尸（仅更新单个僵尸的图片切换、移动产生的x坐标，但仍然会打印所有僵尸的原图片）
		js_yz_bh();					//僵尸的y轴变化

		Sleep(temp_yz_sj);
	}

	//Sleep(1000);


	//播放游戏失败音
	Play_audio(Audio_yxsby, mysong);

	Sleep(12000);

	//关闭音乐
	Turn_off_audio(mysong);
}
void js_yz_bh()
{
	if (js[yg_aqx_bh].h == 1)
	{
		if (js[yg_aqx_bh].tp >= 7 - 1 && js[yg_aqx_bh].tp <= 20 - 1)	//如果当前僵尸的移动图片为第7~第20张，
		{
			js[yg_aqx_bh].y += 9;
		}
		else if (js[yg_aqx_bh].tp >= 26 - 1 && js[yg_aqx_bh].tp <= 33 - 1)//如果当前僵尸的移动图片为第26~第33张，
		{
			js[yg_aqx_bh].y += 9;
		}
	}
	else if (js[yg_aqx_bh].h == 2)
	{
		if (js[yg_aqx_bh].tp >= 7 - 1 && js[yg_aqx_bh].tp <= 20 - 1)	//如果当前僵尸的移动图片为第7~第20张，
		{
			js[yg_aqx_bh].y += 6;
		}
		else if (js[yg_aqx_bh].tp >= 26 - 1 && js[yg_aqx_bh].tp <= 33 - 1)//如果当前僵尸的移动图片为第26~第33张，
		{
			js[yg_aqx_bh].y += 4;
		}
	}
	else if (js[yg_aqx_bh].h == 4)
	{
		if (js[yg_aqx_bh].tp >= 7 - 1 && js[yg_aqx_bh].tp <= 20 - 1)	//如果当前僵尸的移动图片为第7~第20张，
		{
			js[yg_aqx_bh].y -= 2;
		}
		else if (js[yg_aqx_bh].tp >= 26 - 1 && js[yg_aqx_bh].tp <= 33 - 1)//如果当前僵尸的移动图片为第26~第33张，
		{
			js[yg_aqx_bh].y -= 2;
		}
	}
	else if (js[yg_aqx_bh].h == 5)
	{
		if (js[yg_aqx_bh].tp >= 7 - 1 && js[yg_aqx_bh].tp <= 20 - 1)	//如果当前僵尸的移动图片为第7~第20张，
		{
			js[yg_aqx_bh].y -= 6;
		}
		else if (js[yg_aqx_bh].tp >= 26 - 1 && js[yg_aqx_bh].tp <= 33 - 1)//如果当前僵尸的移动图片为第26~第33张，
		{
			js[yg_aqx_bh].y -= 6;
		}
	}
}
