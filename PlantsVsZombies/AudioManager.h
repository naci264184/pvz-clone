#pragma once

#include <Windows.h>
#include<string>
using namespace std;

//游戏音乐
string Audio_yxjmy = "Assets/Audio/BGM/Start.wma";				//游戏启动音乐
string Audio_zwxzy = "Assets/Audio/BGM/Ready.mp3";				//游戏准备环节音乐
string Audio_yxy = "Assets/Audio/BGM/Gameplay.mp3";				//游戏进行时的音乐
string Audio_yxsly = "Assets/Audio/BGM/Victory.mp3";			//游戏胜利音乐
string Audio_yxsby = "Assets/Audio/BGM/Defeat.mp3";				//游戏失败音乐

//游戏音效

//背景音效（背景氛围）
string Audio_jscxy = "Assets/Audio/SFX/Ambience/ZombieAppear.mp3";	//僵尸出现音
string Audio_jsjs = "Assets/Audio/SFX/Ambience/ZombieGroan.mp3";	//僵尸叫声

//交互音效（玩家操作反馈音效）
string Audio_czy = "Assets/Audio/SFX/Interaction/Shovel.mp3";		//铲子铲除植物音效
string Audio_hqygy = "Assets/Audio/SFX/Interaction/SunCollect.mp3";	//点击收集阳光音效
string Audio_zzzwy = "Assets/Audio/SFX/Interaction/Plant.mp3";		//种植植物音效

//植物音效
string Audio_wdmzy = "Assets/Audio/SFX/Plants/PeaHit.mp3";		//豌豆命中音效

//音频设备
string mysong = "mysong";						//游戏音乐统一使用的设备

string Audio_jscxy_sb = "Audio_jscxy_sb";		//僵尸出现音
string Audio_jsjs_sb = "Audio_jsjs_sb";			//僵尸叫声

string Audio_czy_sb = "Audio_czy_sb";			//铲子
string Audio_hqygy_sb = "Audio_hqygy_sb";		//获取阳光
string Audio_zzzwy_sb = "Audio_zzzwy_sb";		//种植植物

string Audio_wdmzy_sb = "Audio_wdmzy_sb";		//豌豆命中



//音频_方法
void Play_audio(const string& file_path, const string& alias, bool sf_xhbf = false);
void Turn_off_audio(const string& alias);



void Play_audio(const string& file_path, const string& alias, bool sf_xhbf)
{
	string close_cmd = "close " + alias;
	string open_cmd = "open " + file_path + " alias " + alias;
	string play_cmd = "play " + alias;

	//如果要求循环播放
	if (sf_xhbf)
	{
		play_cmd = "play " + alias + " repeat";
	}

	// 1.关闭旧音频
	mciSendString(close_cmd.c_str(), NULL, 0, NULL);

	// 2.打开音频
	mciSendString(open_cmd.c_str(), NULL, 0, NULL);

	// 3.播放音频
	mciSendString(play_cmd.c_str(), NULL, 0, NULL);
}
void Turn_off_audio(const string& alias)
{
	std::string close_cmd = "close " + alias;
	mciSendString(close_cmd.c_str(), NULL, 0, NULL);
}