#include <Windows.h>
#include<iostream>
using namespace std;
#include<easyx.h>
#include<fstream>
#include<string>
#include<ctime>
#include <mmsystem.h>
#include<dsound.h>
#pragma comment(lib, "WINMM.LIB")
#include <random>
#include <filesystem>

#include"GameLoop.h"


int main()
{
	//1.游戏准备环节
	//1.1 创建窗口
	initgraph(ck_c, ck_k, 0);							//0（默认）为隐藏终端、1为显示

	//1.2 渲染画面第一帧
	IMAGE temp;
	loadimage(&temp, Splash.c_str(), ck_c, ck_k);		//先打印游戏启动画面的第一张图片
	putimage(0, 0, &temp);


	//1.3 播放游戏启动音乐
	//播放音乐1（游戏界面音）
	Play_audio(Audio_yxjmy, mysong, true);

	//1.4 确保资源目录存在
	EnsureAssetDirectoriesExist();		//确保资源目录存在（确保"temp/logs"存在）
	InitializeAssetStorage();			//初始化资产存储（确保各资源目录存在）

	//1.5 判断游戏测试模块是否开启
	cs_yxms();							//测试内容

	//1.6 将预加载资源图片获取到当前进程
	/*/获取游戏画面素材	
	hq_cj();							//获取场景
	cshtp();							//初始化每张图片的黑白、色彩图
	hq_wzcj();							//获取完整场景
	csh_scwz();							//初始化输出文字

	hq_jzhm();							//将对应画面内容写出到图片中
	//*/
	
	//获取游戏画面
	hq_yxhm();

	//1.7 设置游戏字体
	settextcolor(BLACK);				//将文字颜色设置为黑色
	setbkmode(1);						//将文字输出时的背景设置为：透明

	//2.游戏启动环节
	//2.1 播放游戏启动画面
	bool sf_bfzhyz = false;				//是否_仅播放最后一张
	A:
	yx_qdhm(sf_bfzhyz);					//游戏启动画面
	sf_bfzhyz = false;
	
	//2.2 进入游戏选择界面	
	if (yx_xzjm())
	{		
		sf_bfzhyz = true;
		goto A;
	}

	//2.3 游戏即将开始，切换音乐
	//关闭音乐1
	Turn_off_audio(mysong);

	//播放音乐2（植物选择音）
	Play_audio(Audio_zwxzy, mysong, true);
	system("cls");
	
	//3.游戏环节
	//3.1 进入游戏关卡，遍历场景	
	if (cs_sb)
	{
		cout << "第一天（测试模式已开启）" << endl;
	}
	else
	{
		cout << "第一天" << endl;
	}
	
	cout << "僵尸数量：" << zjssl << endl;

	blcj();
	Sleep(600);


	//3.2 打印游戏开始前的提示内容
	dy_tsnr();							//打印：好...准备...开始！

	
	//3.3 游戏开始
	//关闭音乐2
	Turn_off_audio(mysong);

	//播放音乐3（游戏音）
	Play_audio(Audio_yxy, mysong, true);

	srand((unsigned int)time(NULL));

	GameLoop();
	


	//3.4 游戏结束
	//关闭音频
	Turn_off_audio(mysong);				//关闭音乐

	Turn_off_audio(Audio_jscxy_sb);		//关闭僵尸出现音
	Turn_off_audio(Audio_jsjs_sb);		//关闭僵尸叫声

	Turn_off_audio(Audio_czy_sb);		//关闭铲子音
	Turn_off_audio(Audio_hqygy_sb);		//关闭获取阳光音
	Turn_off_audio(Audio_zzzwy_sb);		//关闭种植植物音
	
	Turn_off_audio(Audio_wdmzy_sb);		//关闭豌豆命中音

	//关闭窗口
	closegraph();


	return 0;
}
