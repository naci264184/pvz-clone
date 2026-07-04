#pragma once

#include"ImageData.h"
#include"DebugTools.h"
#include"Utils.h"
#include"AudioManager.h"
#include"Zombies.h"

//游戏时间累计模块

//方法_声明
bool js_sfcx();
bool CheckZombieSpawnTimer();

//方法_实现
bool js_sfcx()
{
	int ym = 1000;

	if (dq_game_time >= (sgjs_cxsj - 5) * ym && sfybf_jscxy == false)
	{
		//播放僵尸出现音
		//Play_audio(Audio_jscxy, Audio_jscxy_sb);
		sfybf_jscxy = true;

		return true;
	}
	return false;
}
bool CheckZombieSpawnTimer()
{
	if (xygjs_bh < zjssl)					//如果下一个生成的僵尸的编号，没有超过总僵尸数量
	{
		if (dq_game_time >= js_cxsj[xygjs_bh])		//如果已达到下一个僵尸的出现时间
		{
			//（1）生成僵尸
			//sc_js();						//已移动到游戏循环中
			xygjs_bh++;

			//（2）在生成第1和第5个僵尸时，播放音频
			if (xygjs_bh == 1 || xygjs_bh == 5)
			{
				//播放僵尸叫声
				Play_audio(Audio_jsjs, Audio_jsjs_sb);
			}

			//（3）打印_波数和已生成僵尸内容
			system("cls");
			dy_bsnr();

			return true;
		}
	}

	return false;
}
