#pragma once

//类
#include"Plants.h"
#include"Zombies.h"
#include"Projectiles.h"
#include"LawnMower.h"
#include"Sunlight.h"

#include"easyx.h"
#include"ImageData.h"


//图像渲染


//方法_声明

//1.游戏循环_静态内容渲染
void RenderStaticContent(int& jxjg, int& yg_zzx, int& yg_zzy, bool& cz_dj, bool& ygjx_pd, bool& ygdj_pd, int& ygyd_x, int& ygyd_y);

//2.其他_方法
void sbcdyzw(ExMessage& xx, bool sbzj_ax, int kc_bh);	//鼠标处打印植物
void dy_cz(int wz1, int wz2);							//打印铲子
void myz_wzcj(int wz_pyl, int wz_dc_pyl);				//获取每一帧的完整场景（参数：位置_偏移量，位置_单次_偏移量）
void myz_wzcj_bxg(int wz_pyl, bool sf_dyjs);			//获取每一帧的完整场景，但不修改坐标（参数：位置_偏移量，是否打印僵尸）

//方法_实现
void RenderStaticContent(int& jxjg, int& yg_zzx, int& yg_zzy, bool& cz_dj, bool& ygjx_pd, bool& ygdj_pd, int& ygyd_x, int& ygyd_y)
{
	//创建变量
	int ym = 1000;			//1秒


	//1.重新打印基础场景内容
	cleardevice();				//清屏（下面的打印场景本身似乎就会覆盖掉原内容，这里似乎可以不加清屏）
	putimage(0, 0, &wzcj);		//将完整场景打印出来

	//2.打印铲子
	if (cz_dj == false)			//如果铲子没有被点击
	{
		dy_cz(648, 0);			//则将铲子打印在铲子容器的位置
	}

	//3.打印阳光字体（经反复测试，这里的条件判断不能移到dy_ygzt()函数里，具体原因我也不清楚，反正别动）
	if (yg_sl < 10)				//阳光数量为一位数时的阳光打印位置
	{
		ygzt_x = 91;
	}
	else if (yg_sl > 9 && yg_sl < 100)	//阳光数量为两位数时的阳光打印位置
	{
		ygzt_x = 87;
	}
	else if (yg_sl > 99)				//阳光数量为三位数时的阳光打印位置
	{
		ygzt_x = 83;
	}
	dy_ygzt(ygzt_x, ygzt_y, ygsl_zt.c_str());	//在指定位置打印阳光数量字体	
	
	
	//4.打印场景阳光
	//4.1 场景阳光未被点击，则让它竖直下落
	if (ygjx_pd)								//如果为阳光降下的时候
	{
		dy_yg(yg_zzy);							//打印阳光
	}
	//4.2 场景阳光已被点击，往终点方向移动
	else											//如果不为阳光降下的时候
	{
		if (ygdj_pd)								//如果该轮阳光还没有到终点
		{
			dy_yg2(yg_zzx2, ygdj_pd, ygyd_x, ygyd_y);
		}
		else										//如果阳光到终点了，当前场景无阳光
		{
			jxjg -= yx_jg;							//更新降下间隔
			if (jxjg <= 0)							//如果降下间隔为0了，则开始新一轮降下
			{
				ygjx_pd = true;						//让阳光降下赋值为真
				jxjg += yg_jg;						//刷新下次的降下间隔
				cxsc_yg(yg_zzx, yg_zzy);			//重新生成阳光的位置
				yg_dqx = yg_zzx;					//阳光当前的x坐标=阳光最终的x坐标
				yg_dqy = 0;
				//cout << "已生成阳光" << endl;
			}
			//cout << "阳光未生成，降下间隔还有：" << jxjg << endl;
		}

	}

}
void sbcdyzw(ExMessage& xx, bool sbzj_ax, int kc_bh)				//鼠标处打印植物
{
	if (sbzj_ax)				//如果鼠标处于按下状态
	{
		//1.鼠标处打印内容（鼠标按下时，按住了植物）
		IMAGE* hb_hm = &xrk_hb[0];			//黑白画面（绘图设备）
		IMAGE* sc_hm = &xrk_hb[0];			//色彩画面（绘图设备）

		//按住的植物为向日葵
		if (kc_bh == 1)
		{
			hb_hm = &xrk_hb[0];
			sc_hm = &xrk_sc[0];
		}
		//按住的植物为豌豆射手
		else if (kc_bh == 2)
		{
			hb_hm = &wdss_hb[0];
			sc_hm = &wdss_sc[0];
		}
		//按住的植物为坚果
		else if (kc_bh == 3)
		{
			hb_hm = &jg_hb[0];
			sc_hm = &jg_sc[0];
		}

		//2.打印位置的偏移量
		int py_x = 0;			//偏移位置（用于确定图片在鼠标的中心点）
		int py_y = 0;
		if (kc_bh >= 1)
		{
			py_x = 35;
			py_y = 35;
		}
		else if (kc_bh == -2)
		{
			py_x = 40;
			py_y = 40;
		}

		//3.在鼠标位置打印对应内容
		if (kc_bh >= 1)							//如果卡槽编号大于0（大于0的编号都为），则填充位置都一样
		{
			putimage(xx.x - py_x, xx.y - py_y, hb_hm, SRCAND);			//将植物_黑白打印在当前鼠标处

			setfillcolor(WHITE);										//将填充颜色设置为白色
			floodfill(xx.x - py_x + 32, xx.y - py_y + 22, BLACK, 1);	//从黑色区域开始，只要相邻处为黑色，就填充为白色
			putimage(xx.x - py_x, xx.y - py_y, sc_hm, SRCAND);			//将植物_色彩打印在当前鼠标处

		}
		else if (kc_bh == -2)
		{
			putimage(xx.x - py_x, xx.y - py_y, &cz_hb, SRCAND);			//将第二个植物卡槽_黑白打印在当前鼠标处

			setfillcolor(WHITE);										//将填充颜色设置为白色
			floodfill(xx.x - py_x + 25, xx.y - py_y + 56, BLACK, 1);	//从黑色区域开始，只要相邻处为黑色，就填充为白色
			putimage(xx.x - py_x, xx.y - py_y, &cz_sc, SRCAND);			//将第二个植物卡槽_色彩打印在当前鼠标处
		}
	}
}
void dy_cz(int wz1, int wz2)
{
	putimage(wz1, wz2, &cz_hb, SRCAND);					//将铲子_黑白打印在场景(648,0)处

	setfillcolor(WHITE);								//将填充颜色设置为白色
	floodfill(wz1 + 25, wz2 + 56, BLACK, 1);			//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(wz1, wz2, &cz_sc, SRCAND);					//将铲子_色彩打印在场景(648,0)处
}
void myz_wzcj(int wz_pyl, int wz_dc_pyl)				//每一帧的完整场景（带有坐标向右偏移，用于播放游戏失败）
{
	//cleardevice();				//清屏

	//创建临时路径变量
	string GameBackground = Raw_Misc_GameBackground;	//游戏场景路径

	//1.打印背景（场景）
	IMAGE temp_cj = { ck_c + 650,ck_k };			//临时场景

	loadimage(&temp_cj, GameBackground.c_str(), ck_c + 650, ck_k);	//将图片加载到临时场景中
	SetWorkingImage(&temp_cj);						//设置当前绘图设备为临时场景

	getimage(&cj, 230 - wz_pyl, 0, ck_c + 230 - wz_pyl, ck_k);		//截取部分，给场景

	SetWorkingImage(NULL);							//设置当前绘图设备设置为图形界面窗口
	putimage(0, 0, &cj);							//将场景打印在当前绘图窗口上

	//2.打印其场景他内容
	//2.1 打印种子银行
	putimage(57 + wz_pyl, 0, &zzyh_hb, SRCAND);				//将种子银行_黑白打印在场景(57,0)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(59 + wz_pyl, 0, BLACK, 1);					//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(57 + wz_pyl, 0, &zzyh_sc, SRCAND);				//将种子银行_色彩打印在场景(57,0)处

	//2.2 打印铲子容器
	putimage(650 + wz_pyl, 0, &czrq_hb, SRCAND);			//将铲子容器_黑白打印在场景(650,0)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(652 + wz_pyl, 0, BLACK, 1);					//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(650 + wz_pyl, 0, &czrq_sc, SRCAND);			//将铲子容器_色彩打印在场景(650,0)处	

	//2.3 打印向日葵卡片
	putimage(135 + wz_pyl, 7, &xrkkp_hb, SRCAND);					//将向日葵卡片_黑白打印在场景(135,7)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(140 + wz_pyl, 12, BLACK, 1);							//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(135 + wz_pyl, 7, &xrkkp_sc, SRCAND);					//将向日葵卡片_色彩打印在场景(135,7)处

	//2.4 打印豌豆射手卡片
	putimage(187 + wz_pyl, 7, &wdsskp_hb, SRCAND);					//将豌豆射手卡片_黑白打印在场景(187,7)处
	setfillcolor(WHITE);											//将填充颜色设置为白色
	floodfill(192 + wz_pyl, 12, BLACK, 1);							//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(187 + wz_pyl, 7, &wdsskp_sc, SRCAND);					//将豌豆射手卡片_色彩打印在场景(187,7)处

	//2.5 打印坚果卡片
	putimage(239 + wz_pyl, 7, &jgkp_hb, SRCAND);
	setfillcolor(WHITE);
	floodfill(244 + wz_pyl, 12, BLACK, 1);
	putimage(239 + wz_pyl, 7, &jgkp_sc, SRCAND);

	//2.6 打印阳光数量字体
	dy_ygzt(ygzt_x + wz_pyl, ygzt_y, ygsl_zt.c_str());

	//2.7 打印铲子
	dy_cz(648 + wz_pyl, 0);

	//3.打印动态内容
	//3.1 打印植物
	for (int i = 0;i < zw_sl;i++)
	{
		zw[i].x += wz_dc_pyl;				//所有植物的x坐标都增加该值
		dy_zwnr(i, zw[i].kc_bh);
	}

	//3.2 打印僵尸
	for (int i = 0;i < js_sl;i++)
	{
		//cout << "僵尸x坐标：" << js[i].x << endl;
		js[i].x += wz_dc_pyl;
		//cout << "僵尸x坐标：" << js[i].x << endl;

		dy_jsnr(i);
	}

	//3.3 打印释放物（向日葵产生的阳光、豌豆射手产生的豌豆）
	for (int i = 0;i < sfw_sl;i++)
	{
		sfw[i].x += wz_dc_pyl;

		if (sfw[i].lx == 1)
		{
			dy_ygnr(i);
		}
		else if (sfw[i].lx == 2)
		{
			dy_wdnr(i);
		}
	}

	//3.4 打印小推车
	for (int i = 0;i < 5;i++)
	{
		//跳过已消失的小推车
		if (xtc[i].xs)
		{
			continue;
		}

		//小推车x坐标右移，并打印小推车
		if (sb_sfdyqtnr)
		{
			xtc[i].x += wz_dc_pyl;
			dy_xtcnr(i, xtc[0].y + i * 100);
		}
	}

	//4.打印其他动态内容
	//4.1 打印场景生成的阳光
	if (sb_sfdyqtnr)
	{
		yg_dqx += wz_dc_pyl;
		dy_cjyg();
	}

	//将所有内容，交给完整场景
	getimage(&wzcj, 0, 0, ck_c, ck_k);						//将当前画面截取给完整场景
}
void myz_wzcj_bxg(int wz_pyl, bool sf_dyjs)
{
	//创建临时路径变量
	string GameBackground = Raw_Misc_GameBackground;	//游戏场景路径

	//1.打印背景（场景）
	IMAGE temp_cj = { ck_c + 650,ck_k };			//临时场景

	loadimage(&temp_cj, GameBackground.c_str(), ck_c + 650, ck_k);	//将图片加载到临时场景中
	SetWorkingImage(&temp_cj);						//设置当前绘图设备为临时场景

	getimage(&cj, 230 - wz_pyl, 0, ck_c + 230 - wz_pyl, ck_k);		//截取部分，给场景

	SetWorkingImage(NULL);							//设置当前绘图设备设置为图形界面窗口
	putimage(0, 0, &cj);							//将场景打印在当前绘图窗口上

	//2.打印其场景他内容
	//2.1 打印种子银行
	putimage(57 + wz_pyl, 0, &zzyh_hb, SRCAND);				//将种子银行_黑白打印在场景(57,0)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(59 + wz_pyl, 0, BLACK, 1);					//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(57 + wz_pyl, 0, &zzyh_sc, SRCAND);				//将种子银行_色彩打印在场景(57,0)处

	//2.2 打印铲子容器
	putimage(650 + wz_pyl, 0, &czrq_hb, SRCAND);			//将铲子容器_黑白打印在场景(650,0)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(652 + wz_pyl, 0, BLACK, 1);					//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(650 + wz_pyl, 0, &czrq_sc, SRCAND);			//将铲子容器_色彩打印在场景(650,0)处	

	//2.3 打印向日葵卡片
	putimage(135 + wz_pyl, 7, &xrkkp_hb, SRCAND);					//将向日葵卡片_黑白打印在场景(135,7)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(140 + wz_pyl, 12, BLACK, 1);							//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(135 + wz_pyl, 7, &xrkkp_sc, SRCAND);					//将向日葵卡片_色彩打印在场景(135,7)处

	//2.4 打印豌豆射手卡片
	putimage(187 + wz_pyl, 7, &wdsskp_hb, SRCAND);					//将豌豆射手卡片_黑白打印在场景(187,7)处
	setfillcolor(WHITE);											//将填充颜色设置为白色
	floodfill(192 + wz_pyl, 12, BLACK, 1);							//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(187 + wz_pyl, 7, &wdsskp_sc, SRCAND);					//将豌豆射手卡片_色彩打印在场景(187,7)处

	//2.5 打印坚果卡片
	putimage(239 + wz_pyl, 7, &jgkp_hb, SRCAND);
	setfillcolor(WHITE);
	floodfill(244 + wz_pyl, 12, BLACK, 1);
	putimage(239 + wz_pyl, 7, &jgkp_sc, SRCAND);

	//2.6 打印阳光数量字体
	dy_ygzt(ygzt_x + wz_pyl, ygzt_y, ygsl_zt.c_str());

	//2.7 打印铲子
	dy_cz(648 + wz_pyl, 0);

	//3.打印动态内容
	//3.1 打印植物
	for (int i = 0;i < zw_sl;i++)
	{
		dy_zwnr(i, zw[i].kc_bh);
	}

	//3.2 打印僵尸
	for (int i = 0;i < js_sl;i++)
	{
		if (sf_dyjs)
		{
			dy_jsnr(i);
		}
	}

	//3.3 打印释放物（向日葵产生的阳光、豌豆射手产生的豌豆）
	for (int i = 0;i < sfw_sl;i++)
	{
		if (sfw[i].lx == 1)
		{
			dy_ygnr(i);
		}
		else if (sfw[i].lx == 2)
		{
			dy_wdnr(i);
		}
	}

	//3.4 打印小推车
	for (int i = 0;i < 5;i++)
	{
		//跳过已消失的小推车
		if (xtc[i].xs)
		{
			continue;
		}

		//小推车x坐标右移，并打印小推车
		if (sb_sfdyqtnr)
		{
			dy_xtcnr(i, xtc[0].y + i * 100);
		}
	}

	//4.打印其他动态内容
	//4.1 打印场景生成的阳光
	if (sb_sfdyqtnr)
	{
		dy_cjyg();
	}

	//将所有内容，交给完整场景
	getimage(&wzcj, 0, 0, ck_c, ck_k);						//将当前画面截取给完整场景
}
