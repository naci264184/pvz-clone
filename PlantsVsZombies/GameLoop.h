#pragma once

//类
#include"Plants.h"
#include"Zombies.h"
#include"Projectiles.h"
#include"LawnMower.h"

//加载动画、主菜单
#include"LoadingScreen.h"
#include"MainMenu.h"

//图片、音频
#include"ImageLoader.h"
#include"AudioManager.h"

//数据
#include"GameData.h"
#include"ImageData.h"


//工具
#include"Utils.h"
#include"DebugTools.h"

//游戏循环
#include"GameOverLogic.h"				//游戏结局
#include"GameClock.h"					//游戏计时模块
#include"EventManager.h"				//消息处理
#include"Renderer.h"					//渲染（涉及游戏循环中，必须的静态渲染）

//其他
#include"Sunlight.h"


//游戏循环



//方法_声明

//1.游戏循环
void GameLoop();						//游戏循环

//2.其他（涉及多个类）
void dy_zw();							//打印植物
void dy_sfw();							//打印释放物
void dy_xtc();							//打印小推车



//方法_实现
void GameLoop()				//游戏循环
{
	//场景阳光_产生判断
	bool ygjx_pd = false;	//判断是否需要下落阳光
	bool ygdj_pd = false;	//判断是否点击了阳光
	
	//阳光移动速度
	int ygyd_x = 0;			//当点击了阳光后，阳光移动一次的x轴距离
	int ygyd_y = 0;

	//场景阳光_移动终点的坐标
	int yg_zzx = 0;			//场景阳光竖直下落的最终坐标（非收集框位置的坐标）
	int yg_zzy = 0;	

	//场景阳光产生间隔
	int jxjg = yg_jg;		//每轮阳光降下时间间隔

	int kc_bh = 0;			//当前为第几个卡槽（卡槽_编号）、点击内容：1（第一个植物卡槽）、2（第二个植物卡槽）、-1（阳光）、-2（铲子）
	

	//铲子是否被点击
	bool cz_dj = false;

	//记录鼠标状态
	ExMessage xx;			//消息
	POINT xxzb = { 0,0 };	//消息的坐标
	bool sbzj_ax = false;	//记录鼠标左键是否处于按下状态（用于判断是否需要在鼠标处打印内容）
	bool yx_sfzt = false;	//记录游戏是否暂停
	


	jscxsj_sz();				//僵尸出现时间_初始化

	flushmessage();				//清空消息缓冲区

	//如果当前游戏时间大于最后一只僵尸的出现时间+偏移量，且当前僵尸数量为0，并且当前游戏时间大约最后一个僵尸的消失时间+偏移量，则游戏结束
	while (!(dq_game_time > js_cxsj[zjssl - 1] + 300 && js_sl == 0) || !(dq_game_time > zh_js_swsj + yxsl_pyl))
	{
		//1.判断游戏暂停
		if (yx_sfzt)
		{
			goto yx_zt;
		}

		//2.渲染静态内容（打印静态基础内容）
		RenderStaticContent(jxjg, yg_zzx, yg_zzy, cz_dj, ygjx_pd, ygdj_pd, ygyd_x, ygyd_y);

		//3.生成僵尸
		//僵尸第一次出现
		if (js_sfcx())
		{
			//播放僵尸出现音
			Play_audio(Audio_jscxy, Audio_jscxy_sb);
		}
		//生成僵尸
		if (CheckZombieSpawnTimer())
		{
			sc_js();
		}


		//4.打印动态内容（植物、僵尸、释放物、小推车）
		dy_zw();					//打印植物
		dy_xtc();					//打印小推车
		dy_js();					//打印僵尸
		dy_sfw();					//打印释放物
		sbcdyzw(xx, sbzj_ax, kc_bh);//判断是否需要在鼠标处打印植物		

		//5.游戏结局判断
		//游戏胜利判断
		CheckWinCondition();

		//游戏失败判断
		if (CheckLoseCondition())
		{
			exit(0);
		}
		

		//6.游戏切帧、游戏时间累计
		Sleep(yx_jg);				//由于系统运行的很快，将接收消息放在延时前面会来不及接收消息，就进入延时了，然后进入下次循环又清空消息缓冲区了
		dq_game_time += yx_jg;		//只有把消息判断放在延时后面才能检测出来


		//游戏暂停
	yx_zt:

		//7.消息处理
		xx = ProcessEvents(xxzb, sbzj_ax, yx_sfzt, cz_dj, kc_bh, ygjx_pd, ygdj_pd, ygyd_x, ygyd_y);
	}
}
void dy_zw()
{
	for (int i = 0;i < zw_sl;i++)
	{
		//1.判定植物死亡
		if (zw[i].xl == 0)				//如果植物的血量为0
		{
			cxpl_zw(i);
			i--;
			continue;
		}

		//2.打印图片内容

		//2.1 向日葵的图片打印
		if (zw[i].kc_bh == 1)
		{
			//打印_植物图片
			dy_zwnr(i, 1);

			//更新图片逻辑
			zw[i].tp++;
			if (zw[i].tp == xrk_tpsl)
			{
				zw[i].tp = 0;
			}

			//阳光生成逻辑
			if (zw[i].sj >= xrk_jg)					//如果植物的时间大于或等于向日葵的生产阳光的间隔
			{
				sfwlx temp;							//产生一个阳光
				temp.x = zw[i].x + 47 - 39;
				temp.y = zw[i].y + 23 - 36;
				temp.lx = 1;						//释放物的类型为1（阳光）

				sfw[sfw_sl] = temp;
				sfw_sl++;

				zw[i].sj -= xrk_jg;
			}
			zw[i].sj += yx_jg;					//植物释放释放物的时间间隔增加
		}

		//2.2 豌豆射手的图片打印
		else if (zw[i].kc_bh == 2)
		{
			//打印_植物图片
			dy_zwnr(i, 2);

			//更新图片逻辑
			zw[i].tp++;								//切换下一张图片
			if (zw[i].tp == wdss_tpsl)				//如果该图片为最后一张图片的下一张
			{
				zw[i].tp = 0;						//就切换为第一张
			}

			//攻击判断逻辑
			int temp_pd = false;
			int x_cj;
			for (int j = 0;j < js_sl;j++)
			{
				x_cj = zw[i].x - js[j].x - 57;
				if (zw[i].h == js[j].h && x_cj <= 7)		//如果该行有僵尸，且该僵尸在植物前面
				{

					temp_pd = true;
					if (zw[i].sj >= wdss_jg)				//如果植物的时间大于或等于豌豆射手的释放豌豆的间隔
					{
						sfwlx temp;							//产生一个豌豆
						temp.x = zw[i].x + 67 - 4;
						temp.y = zw[i].y;
						temp.h = zw[i].h;
						temp.lx = 2;						//释放物的类型为2（豌豆）

						sfw[sfw_sl] = temp;
						sfw_sl++;

						zw[i].sj -= wdss_jg;
					}
					zw[i].sj += yx_jg;						//植物释放释放物的时间增加
					break;
				}
			}
			if (temp_pd == false)						//该行没有僵尸
			{
				zw[i].sj = 0;							//植物释放释放物的时间重置
			}
		}

		//2.3 坚果的图片打印
		else if (zw[i].kc_bh == 3)
		{
			//判断坚果状态
			if (zw[i].xl <= 2666 && zw[i].xl > 1333)
			{
				zw[i].zt = 2;
			}
			else if (zw[i].xl <= 1333)
			{
				zw[i].zt = 3;
			}

			//更新图片逻辑
			zw[i].tp++;									//切换下一张图片

			if (zw[i].zt == 1 && zw[i].tp == jg_tpsl)			//坚果完整状态
			{
				zw[i].tp = 0;
			}
			else if (zw[i].zt == 2 && zw[i].tp >= jg_ps_tpsl)	//坚果破损状态
			{
				zw[i].tp = 0;
			}
			else if (zw[i].zt == 3 && zw[i].tp >= jg_wx_tpsl)	//坚果残缺状态
			{
				zw[i].tp = 0;
			}

			//打印_植物图片
			dy_zwnr(i, 3, zw[i].zt);
		}
	}
}
void dy_sfw()
{
	int ygwz_pyl_x = 37;		//阳光位置偏移量_x
	int ygwz_pyl_y = 37;		//阳光位置偏移量_y

	//遍历所有释放物
	for (int i = 0;i < sfw_sl;i++)
	{
		//1.阳光
		if (sfw[i].lx == 1)					//如果释放物类型为阳光
		{
			//1.1 打印阳光
			dy_ygnr(i);

			sfw[i].tp++;
			//gxlj2(yg_lj2, sfw[i].tp);			//更新下次图片为下一张


			//1.2 阳光未被点击
			if (sfw[i].yg_dj == 0)					//如果没有点击到阳光
			{
				if (sfw[i].sj < 600)				//如果释放物的时间小于0.5秒
				{
					sfw[i].y -= 4;					//y坐标-=2
				}
				else if (sfw[i].sj >= 600 && sfw[i].sj <= 1800)  //如果释放物的时间在0.5~1秒内
				{
					sfw[i].y += 4;					//y坐标+=2
				}
			}

			//1.3 阳光已被点击（阳光移动算法）
			else
			{
				//让向日葵阳光移动一次
				sfw[i].x -= sfw[i].yg_ydx;	//让阳光移动一次
				sfw[i].y -= sfw[i].yg_ydy;


				//判断向日葵阳光是否到达终点
				if (sfw[i].x <= yg_zzx2 - ygwz_pyl_x && sfw[i].y <= yg_zzy2 - ygwz_pyl_y)
				{
					gxyg_sl(25);			//更新阳光数量
					cxpl_sfw(i);
					i--;
					continue;
				}				

			}


			//1.4 是否重置图片的当前张数
			if (sfw[i].tp == yg_tpsl)			//如果为最后一张图片的下一张
			{
				sfw[i].tp = 0;					//则切换为第一张
			}

			sfw[i].sj += yx_jg;
		}

		//2.豌豆
		else if (sfw[i].lx == 2)				//如果释放物类型为豌豆
		{
			//2.1 如果豌豆到达屏幕右边尽头
			if (sfw[i].x >= ck_c)				//如果该豌豆的位置在屏幕右边，超出屏幕了
			{
				cxpl_sfw(i);
				i--;
				continue;
			}

			//2.2 打印豌豆
			dy_wdnr(i);

			//2.3 碰撞检测
			int js_pz_z_yxwz = 0;					//僵尸_碰撞_左_有效位置
			int js_pz_y_yxwz = 0;					//僵尸_碰撞_右_有效位置
			int wd_pz_z_yxwz = 0;					//豌豆_碰撞_左_有效位置
			int wd_pz_y_yxwz = 0;					//豌豆_碰撞_右_有效位置			

			bool temp_pd = false;

			//（1）遍历所有僵尸，一个一个检测
			for (int j = 0;j < js_sl;j++)
			{
				js_pz_z_yxwz = js[j].x + 65;						//僵尸_碰撞_左边的有效位置为x为+65
				js_pz_y_yxwz = js[j].x + 129;						//僵尸_碰撞_右边的有效位置为x为+129
				wd_pz_z_yxwz = sfw[i].x + 8;						//豌豆_碰撞_左边的有效位置为x为+8
				wd_pz_y_yxwz = sfw[i].x + 48;						//豌豆_碰撞_右边的有效位置为x为+48

				/*/如果想用范围的方式
				int pz_min = wd_pz_y_yxwz - js_pz_z_yxwz;			//碰撞范围最小值（碰撞开始，豌豆右侧==僵尸左侧）
				int pz_max = wd_pz_z_yxwz - js_pz_y_yxwz;			//碰撞范围最大值（豌豆生成在僵尸位置的碰撞，豌豆左侧==僵尸右侧）

				if (pz_max <= 0 && sfw[i].h == js[j].h)
				//*/

				// 碰撞条件：豌豆右边界 > 僵尸左边界  且  豌豆左边界 < 僵尸右边界
				if (wd_pz_y_yxwz >= js_pz_z_yxwz && wd_pz_z_yxwz <= js_pz_y_yxwz && sfw[i].h == js[j].h)
				{
					//播放豌豆命中音效
					Play_audio(Audio_wdmzy, Audio_wdmzy_sb);

					js[j].xl -= wd_sh;								//让僵尸扣血
					cxpl_sfw(i);									//命中后删除该释放物（豌豆）
					i--;
					temp_pd = true;
					break;
				}
				//cout << "gd_cj：" << gd_cj << endl;
				//cout << "sfw[i].x - 80 + 27：" << sfw[i].x - 80 + 27 << endl;
				//cout << "js[j].y：" << js[j].y << endl;
				//system("pause");
			}

			//（2）豌豆碰到僵尸，跳过后面的豌豆坐标赋值（该豌豆已被删除，后面的sfw[i]是其他豌豆）
			if (temp_pd)
			{
				continue;
			}

			//2.4 更新豌豆的x坐标
			sfw[i].x += wd_ys;
		}
	}

}
void dy_xtc()
{
	int temp_y = 113;
	int x_cj = 0;

	//遍历所有小推车
	for (int i = 0;i < 5;i++)								//打印小推车
	{
		//1.如果小推车已经消失
		if (xtc[i].xs)										//如果该小推车已经消失
		{
			temp_y += 100;
			continue;										//则跳过该小推车
		}

		//2.如果小推车没有启动
		if (xtc[i].qd == false)								//如果小推车没有被启动
		{
			//打印小推车
			dy_xtcnr(i, temp_y);
		}
		//3.如果小推车已启动（且未消失）
		else												//如果小推车正在往右移动（消灭僵尸中）
		{
			//3.1 判断是否跑到窗口右尽头
			if (xtc[i].x >= ck_c)							//如果小推车的位置到窗口后面了
			{
				xtc[i].xs = true;							//则消失该小推车
			}

			//3.2 判断是否碰撞到僵尸
			for (int j = 0;j < js_sl;j++)							//遍历所有僵尸
			{
				x_cj = xtc[i].x - js[j].x + 13;
				if (x_cj <= 70 && x_cj >= 0 && i + 1 == js[j].h)	//如果僵尸的x坐标在小推车的位置，而且小推车与僵尸同行
				{
					js[j].xl = 0;
				}
			}

			//3.3 打印小推车
			dy_xtcnr(i, temp_y);

			//3.4 更新小推车x坐标
			xtc[i].x += 30;
		}
		temp_y += 100;
	}
}
