#pragma once

#include"easyx.h"

//类
#include"Plants.h"
#include"Zombies.h"
#include"Projectiles.h"
#include"LawnMower.h"

//图片、音频、游戏数据
#include"ImageData.h"
#include"AudioManager.h"
#include"DebugTools.h"

#include<iostream>

//消息处理模块

//方法_声明
ExMessage ProcessEvents(POINT& xxzb,bool& sbzj_ax, bool& yx_sfzt, bool& cz_dj, int& kc_bh, bool& ygjx_pd, bool& ygdj_pd, int& ygyd_x, int& ygyd_y);


//方法_实现
ExMessage ProcessEvents(POINT& xxzb,bool& sbzj_ax, bool& yx_sfzt, bool& cz_dj, int& kc_bh, bool& ygjx_pd, bool& ygdj_pd, int& ygyd_x, int& ygyd_y)
{
	//1.创建变量
	ExMessage xx;			//消息

	//植物卡槽位置
	int zwkc1_x = 0;		//第一个植物卡槽的位置
	int zwkc1_y = 0;
	int zwkc2_x = 0;		//第二个植物卡槽的位置
	int zwkc2_y = 0;

	//种子位置
	int zzwz_h = 0;			//种植位置的行
	int zzwz_l = 0;			//列
	int zzwz_x = 0;			//种植位置的坐标
	int zzwz_y = 0;

	


	//2.消息循环
	while (peekmessage(&xx, -1))
	{
		//鼠标消息
		if (xx.message >= WM_MOUSEFIRST && xx.message <= WM_MOUSELAST)
		{

			//（1）左键按下
			if (xx.message == 0x201 && !yx_sfzt && sbzj_ax == false)		//如果按下了鼠标左键
			{
				sbzj_ax = true;				//更新一下状态

				//（1）判断按下的位置属于什么
				if (xx.x >= 135 && xx.x <= 185 && xx.y >= 7 && xx.y <= 77)	//如果当前鼠标的位置在第一个植物卡槽的位置（向日葵的位置）
				{
					if (yg_sl >= 50)							//如果当前阳光数量大于或等于50
					{
						kc_bh = 1;								//则记录当前点击的内容为第一个植物卡槽

						putimage(xx.x - 25, xx.y - 25, &xrk_hb[0], SRCAND);		//将第一个植物卡槽_黑白打印在当前鼠标处

						setfillcolor(WHITE);									//将填充颜色设置为白色
						floodfill(xx.x - 25 + 32, xx.y - 25 + 22, BLACK, 1);	//从黑色区域开始，只要相邻处为黑色，就填充为白色
						putimage(xx.x - 25, xx.y - 25, &xrk_sc[0], SRCAND);		//将第一个植物卡槽_色彩打印在当前鼠标处
					}
					else			//不够阳光则记录什么都没点到
					{
						kc_bh = 0;
					}
				}
				else if (xx.x >= 187 && xx.x <= 237 && xx.y >= 7 && xx.y <= 77)	//如果当前鼠标的位置在第二个植物卡槽的位置（豌豆射手的位置）
				{
					if (yg_sl >= 100)							//如果阳光数量大于或等于100
					{
						kc_bh = 2;								//则记录当前点击的内容为第二个植物卡槽

						putimage(xx.x - 25, xx.y - 25, &wdss_hb[0], SRCAND);	//将第二个植物卡槽_黑白打印在当前鼠标处

						setfillcolor(WHITE);									//将填充颜色设置为白色
						floodfill(xx.x - 25 + 32, xx.y - 25 + 22, BLACK, 1);	//从黑色区域开始，只要相邻处为黑色，就填充为白色
						putimage(xx.x - 25, xx.y - 25, &wdss_sc[0], SRCAND);	//将第二个植物卡槽_色彩打印在当前鼠标处
					}
					else			//不够阳光则记录什么都没点到
					{
						kc_bh = 0;
					}
				}
				else if (xx.x >= 239 && xx.x <= 289 && xx.y >= 7 && xx.y <= 77)	//如果当前鼠标的位置在第二个植物卡槽的位置（豌豆射手的位置）
				{
					if (yg_sl >= 50)							//如果阳光数量大于或等于100
					{
						kc_bh = 3;								//则记录当前点击的内容为第3个植物卡槽

						putimage(xx.x - 25, xx.y - 25, &jg_hb[0], SRCAND);	//将第3个植物卡槽_黑白打印在当前鼠标处

						setfillcolor(WHITE);									//将填充颜色设置为白色
						floodfill(xx.x - 25 + 32, xx.y - 25 + 22, BLACK, 1);	//从黑色区域开始，只要相邻处为黑色，就填充为白色
						putimage(xx.x - 25, xx.y - 25, &jg_sc[0], SRCAND);	//将第3个植物卡槽_色彩打印在当前鼠标处
					}
					else			//不够阳光则记录什么都没点到
					{
						kc_bh = 0;
					}
				}
				//如果当前鼠标的位置在"由场景生成"的阳光的当前位置
				else if (xx.x >= yg_dqx + 7 && xx.x <= yg_dqx + 67 && xx.y >= yg_dqy + 7 && xx.y <= yg_dqy + 67)
				{
					if (ygdj_pd == false && ygjx_pd)		//如果当前阳光没有被点击，且当前阳光处于降下状态
					{
						//播放获取阳光音效
						Play_audio(Audio_hqygy, Audio_hqygy_sb);

						kc_bh = -1;							//则记录当前点击的内容为阳光
						ygdj_pd = true;						//记录阳光已经被点击到
						ygjx_pd = false;					//记录阳光不降下

						//生成阳光后，计算阳光移动速度
						CalculateSunlightSpeed(yg_dqx, yg_dqy, ygyd_x, ygyd_y);

					}
				}
				else if (xx.x >= 662 && xx.x <= 715 && xx.y >= 12 && xx.y <= 68)	//如果鼠标的位置在铲子中
				{
					kc_bh = -2;			//记录点击的内容为铲子
					cz_dj = true;		//记录铲子被点击到
				}
				else					//其他
				{
					kc_bh = 0;			//则记录什么都没点到
				}

				//（2）如果当前鼠标的位置在"由向日葵产生"的阳光的当前位置
				for (int i = 0;i < sfw_sl;i++)						//遍历所有释放物
				{
					if (sfw[i].lx == 1)								//如果该释放物类型为阳光
					{
						if (xx.x >= sfw[i].x + 7 && xx.x <= sfw[i].x + 67 && xx.y >= sfw[i].y + 7 && xx.y <= sfw[i].y + 67)		//如果鼠标在该释放物上
						{
							//播放获取阳光音效
							Play_audio(Audio_hqygy, Audio_hqygy_sb);

							sfw[i].yg_dj = 1;						//更新点击到阳光


							//生成阳光后，计算阳光移动速度
							CalculateSunlightSpeed(sfw[i].x, sfw[i].y, sfw[i].yg_ydx, sfw[i].yg_ydy, sfw[i].x, sfw[i].y);
						}
					}
				}

			}

			//（2）左键弹起
			else if (xx.message == 0x202 && !yx_sfzt && sbzj_ax == true)		//如果鼠标左键弹起
			{
				sbzj_ax = false;				//则记录鼠标左键按下状态取消

				if (kc_bh > 0)					//且如果当前选中内容为某种植物
				{
					int cp_tswz = cp_zzb_x + cp_yg_x * 3;	//窗口长度为1100时，这个值为290，窗口长度为900时，为226
					int cp_tswz2 = cp_zzb_x + cp_yg_x * 9;	//窗口长度为1100时，这个值为990，窗口长度为900时，为842

					if (xx.x >= cp_zzb_x && xx.x < cp_tswz2 + cp_ts_x && xx.y >= 86 && xx.y < 576)	//查看当前鼠标是否在草坪的位置
					{
						if (xx.x >= cp_tswz - cp_ts_x && xx.x <= cp_tswz)			//如果在该位置（280~290或218~226）
						{
							zzwz_l = 3;							//则在第3列（从左到右第三块竖着的草坪）
						}
						else if (xx.x >= cp_tswz2 && xx.x <= cp_tswz2 + cp_ts_x)	//如果在该位置（990~1100或842~851）
						{
							zzwz_l = 9;							//则在第9列（从左到右第九块竖着的草坪）
						}
						else									//其他
						{
							//zzwz_l = (xx.x - 90) / 100 + 1;	//0~99（第一列的x范围，（第一列x坐标-90）÷100=0）、100~199（第二列）
							zzwz_l = (xx.x - cp_zzb_x) / cp_yg_x + 1;
						}

						zzwz_h = (xx.y - 76) / 100 + 1;			//根据鼠标当前的y坐标，来判断植物在第几行							

						zzwz_x = zzwz_l * cp_yg_x + zw_zxzzwz_x;//种植的x坐标根据列乘以一定数值获取到
						zzwz_y = (zzwz_h - 1) * 100 + 86;

						bool tempzw_pd = false;
						for (int i = 0;i < zw_sl;i++)			//遍历所有已经种植的植物
						{
							if (zzwz_x == zw[i].x && zzwz_y == zw[i].y)		//如果当前种植的位置已经有植物了
							{
								tempzw_pd = true;
								break;
							}
						}
						if (tempzw_pd)										//则跳过该次植物种植
						{
							continue;
						}

						//播放种植植物音效
						Play_audio(Audio_zzzwy, Audio_zzzwy_sb);

						zwlx temp_zw;					//创建一个植物
						temp_zw.x = zzwz_x;				//将属性赋值给该植物
						temp_zw.y = zzwz_y;
						temp_zw.h = zzwz_h;
						temp_zw.l = zzwz_l;

						if (kc_bh == 3)					//如果为坚果，则血量设置为3000
						{
							temp_zw.xl = jg_xl;
						}

						temp_zw.kc_bh = kc_bh;
						temp_zw.tp = 0;
						zw[zw_sl] = temp_zw;			//加入该植物数组中
						zw_sl++;						//植物数组数量加1

						if (kc_bh == 1)					//如果为向日葵
						{
							gxyg_sl(-50);				//让当前阳光数量减50
						}
						else if (kc_bh == 2)			//如果为豌豆射手
						{
							gxyg_sl(-100);				//让当前阳光数量减100
						}
						else if (kc_bh == 3)
						{
							gxyg_sl(-50);
						}
						kc_bh = 0;						//刷新卡槽编号
					}
				}
				else if (kc_bh == -2)
				{
					cz_dj = false;								//更新一下铲子没有被点击到

					int cp_tswz = cp_zzb_x + cp_yg_x * 3;	//窗口长度为1100时，这个值为290，窗口长度为900时，为226
					int cp_tswz2 = cp_zzb_x + cp_yg_x * 9;	//窗口长度为1100时，这个值为990，窗口长度为900时，为842

					if (xx.x >= cp_zzb_x && xx.x < cp_tswz2 + cp_ts_x && xx.y >= 86 && xx.y < 576)	//查看当前鼠标是否在草坪的位置
					{
						if (xx.x >= cp_tswz - cp_ts_x && xx.x <= cp_tswz)			//如果在该位置
						{
							zzwz_l = 3;							//则在第3列（从左到右第三块竖着的草坪）
						}
						else if (xx.x >= cp_tswz2 && xx.x <= cp_tswz2 + cp_ts_x)	//如果在该位置
						{
							zzwz_l = 9;							//则在第9列（从左到右第九块竖着的草坪）
						}
						else									//其他
						{
							zzwz_l = (xx.x - cp_zzb_x) / cp_yg_x + 1;		//0~99（除以100，结果为0，+1后，就是第一列）、100~199（第二列）
						}

						zzwz_h = (xx.y - 76) / 100 + 1;			//根据鼠标当前的y坐标，来判断植物在第几行							

						bool tempzw_pd = false;
						int temp_zw_wz = 0;
						for (int i = 0;i < zw_sl;i++)			//遍历所有已经种植的植物
						{
							if (zzwz_h == zw[i].h && zzwz_l == zw[i].l)		//如果当前种植的位置已经有植物了
							{
								tempzw_pd = true;				//则记录一下
								temp_zw_wz = i;
								break;
							}
						}
						if (tempzw_pd)							//如果该位置确实有植物
						{
							//播放铲子音效
							Play_audio(Audio_czy, Audio_czy_sb);

							cxpl_zw(temp_zw_wz);				//删去该植物
						}
					}
				}
			}

			//（3）鼠标移动
			if (xx.message == 0x200)			//如果移动了鼠标
			{
				//刷新记录的坐标
				xxzb.x = xx.x;
				xxzb.y = xx.y;

				//cout << "鼠标的坐标记录值更新：消息的x坐标:" << xxzb.x << "\t\t消息的y坐标:" << xxzb.y << endl;
			}
		}

		//键盘消息
		else if (xx.message == WM_KEYDOWN || xx.message == WM_KEYUP)
		{
			//空格键消息
			if (xx.vkcode == VK_SPACE)
			{
				//按下按键
				if (xx.message == WM_KEYDOWN)
				{
					if (!yx_sfzt)				//如果当前为未暂停
					{
						yx_sfzt = true;
						cout << "游戏暂停" << endl;
					}
					else						//如果已经处于暂停状态
					{
						yx_sfzt = false;		//取消游戏暂停
						//cout << "游戏继续" << endl;

						//打印_波数和已生成僵尸内容
						system("cls");
						dy_bsnr();
					}
				}
				//按键弹起
				else if (xx.message == WM_KEYUP)
				{
					/*/将该次消息的坐标，设置游戏暂停前鼠标位置的坐标
					xx.x = xxzb.x;
					xx.y = xxzb.y;
					//cout << "空格键弹起" << endl;
					//*/
				}
			}
		}

		//字符消息
		else if (xx.message == WM_CHAR)
		{
			/*/字符消息：空格
			if (xx.wParam == ' ')
			{
				//将该次消息的坐标，设置游戏暂停前鼠标位置的坐标
				xx.x = xxzb.x;
				xx.y = xxzb.y;
				//cout << "空格字符消息" << endl;
			}
			//*/

			//字符消息：0
			if (xx.wParam == '0')
			{
				cout << "游戏退出" << endl;
				exit(0);
			}
		}
	}

	
	//刷新消息坐标（让消息的坐标，永远等于鼠标的位置，而不是被键盘和字符消息的（0，0）覆盖）
	xx.x = xxzb.x;
	xx.y = xxzb.y;

	return xx;
}
