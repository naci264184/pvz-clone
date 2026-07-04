#pragma once

#include"ImageData.h"
#include"Utils.h"

//图片加载


//方法_声明
//1.图像处理_通用方法
void hqtx(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj, int tc_x = 5, int tc_y = 5);
void hqtx(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj, int num, int ls_c, int ls_k, int tc_x = 5, int tc_y = 5);//重载版本，获取图像前，将图片拉伸到指定大小
void hqtx(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj, string bs, int ls_c, int ls_k, int tc_x, int tc_y);
void hq_sct(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj);		//获取色彩图部分（将获取图像分为3部分用于获取图片画面分为一段一段的图片（文字））
void hq_hbt(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj);		//获取黑白图部分

//2.制作游戏画面
void hq_cj();							//获取场景
void cshtp();							//初始化每张图片的图像（黑白和色彩）
void hq_wzcj();							//获取完整的场景
void csh_scwz();						//初始化_输出文字（将获取图像函数分为3部分：获取色彩图部分、设置黑色填充部分（该函数）、获取黑白图部分））
void dqhm(IMAGE& hm, const char* lj);	//读取画面（将当前图形界面窗口中的画面加载到文件中），参数：记录着对应画面的绘图窗口，要保存到的文件路径
void hq_jzhm();							//获取加载画面（获取所有加工完的画面至文件中）

//3.获取游戏画面
void hq_yxhm();							//获取游戏画面（将文件中所有加工完的画面读取进来）



//方法_实现
void hqtx(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj, int tc_x, int tc_y)		//获取图像，获取一张图片的黑白图、色彩图
{
	//获取一张图片的黑白图、色彩图，参数：(黑白画面的绘图设备，色彩画面的绘图设备，图片的路径，海水填充开始的x轴，y轴）

	tc_x += 100;
	tc_y += 100;

	int k = getwidth();									//获取图形界面窗口的宽度、高度
	int g = getheight();

	Resize(NULL, k + 100, g + 100);						//将图形界面窗口的高度和宽度增长100个像素点

	loadimage(&hb_hm, lj);								//将图片加载到黑白画面中
	putimage(100, 100, &hb_hm);							//将黑白画面打印在图形界面窗口(100,100)位置处

	setfillcolor(WHITE);								//将填充颜色设置为白色
	floodfill(0, 0, BLACK, 1);							//从非图片区域开始，只要相邻处为黑色，就填充为白色
	getimage(&sc_hm, 100, 100, k + 100, g + 100);		//将当前画面获取给色彩画面

	setfillcolor(BLACK);								//将填充颜色设置为黑色
	floodfill(tc_x, tc_y, WHITE, 0);					//从图片区域(tc_x,tc_y)开始，只要没有碰到白色，就填充为黑色
	getimage(&hb_hm, 100, 100, k + 100, g + 100);		//将当前画面获取给黑白画面

	Resize(NULL, k, g);									//将图形界面窗口的高度和宽度设置回来
	cleardevice();										//为防止干扰下次操作，进行清屏
}
void hqtx(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj, int num, int ls_c, int ls_k, int tc_x, int tc_y)		//重载版本，获取图像前，将图片拉伸到指定大小
{
	//最后两个参数是至关重要的，最后两个参数指的是颜色填充算法的"填充开始坐标"（从该坐标位置处进行海水填充）

	tc_x += 100;
	tc_y += 100;

	int k = getwidth();									//获取图形界面窗口的宽度、高度
	int g = getheight();

	Resize(NULL, k + 400, g + 200);						//将图形界面窗口的高度和宽度增长100个像素点

	loadimage(&hb_hm, lj, ls_c, ls_k);					//将图片拉伸到指定长度后，加载到黑白画面中
	putimage(100, 100, &hb_hm);							//将黑白画面打印在图形界面窗口(100,100)位置处
	//system("pause");
	setfillcolor(WHITE);								//将填充颜色设置为白色
	floodfill(0, 0, BLACK, 1);							//从非图片区域开始，只要相邻处为黑色，就填充为白色
	getimage(&sc_hm, 100, 100, k + 100, g + 100);		//将当前画面获取给色彩画面

	setfillcolor(BLACK);								//将填充颜色设置为黑色
	
	/*/
	if (num == 2)
	{
		//设置一个颜色，用该颜色进行海水填充
		COLORREF temp_ys = getpixel(155, 143);			//设置的颜色
		floodfill(tc_x, tc_y, temp_ys | WHITE, 0);		//进行海水填充
	}
	
	//*/
	floodfill(tc_x, tc_y, WHITE, 0);					//从图片区域(tc_x,tc_y)开始，只要没有碰到白色，就填充为黑色

	getimage(&hb_hm, 100, 100, k + 100, g + 100);		//将当前画面获取给黑白画面
	//system("pause");

	Resize(NULL, k, g);									//将图形界面窗口的高度和宽度设置回来
	cleardevice();										//为防止干扰下次操作，进行清屏
}
void hqtx(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj, string bs, int ls_c, int ls_k, int tc_x, int tc_y)		//重载版本，获取图像前，将图片拉伸到指定大小
{
	tc_x += 100;
	tc_y += 100;

	int k = getwidth();									//获取图形界面窗口的宽度、高度
	int g = getheight();

	Resize(NULL, k + 400, g + 100);						//将图形界面窗口的高度和宽度增长100个像素点

	setbkcolor(WHITE);
	cleardevice();
	setbkcolor(BLACK);									//更改完背景色后记得改回来，不然后面的清屏操作又会重新打印白色背景

	loadimage(&hb_hm, lj, ls_c, ls_k);					//将图片拉伸到指定长度后，加载到黑白画面中
	putimage(100, 100, &hb_hm);							//将黑白画面打印在图形界面窗口(100,100)位置处
	//system("pause");

	//setfillcolor(WHITE);								//将填充颜色设置为白色
	//floodfill(0, 0, BLACK, 1);						//从非图片区域开始，只要相邻处为黑色，就填充为白色
	//system("pause");

	COLORREF ys;
	int R;
	int G;
	int B;


	//63,75,35,50,75,90,30,50
	int fw_x1[2] = { 163,175 };
	int fw_x2[2] = { 175,190 };
	int fw_y1[2] = { 135,130 };
	int fw_y2[2] = { 150,150 };


	//设置指定位置"不填充"（2~4是僵尸攻击和僵尸移动所使用的坐标，5是坚果使用的坐标）
	if (bs == "1")
	{
		/*/
		fw_x1[0] = 168;
		fw_x1[1] = 180;
		fw_y1[0] = 142;
		fw_y1[1] = 152;

		fw_x2[0] = 183;
		fw_x2[1] = 203;
		fw_y2[0] = 137;
		fw_y2[1] = 155;
		//*/

		fw_x1[0] += 3;
		fw_x2[1] += 6;

		//fw_y1[0] += 1;			//这里-1或+1似乎都会变得更糟
	}
	else if (bs == "2")
	{
		/*/僵尸移动过程中，眼睛变化位置太大了，这样不准确
		fw_x1[0] = 171;
		fw_x1[1] = 184;
		fw_y1[0] = 140;
		fw_y1[1] = 151;

		fw_x2[0] = 188;
		fw_x2[1] = 205;
		fw_y2[0] = 136;
		fw_y2[1] = 153;
		//*/

		//*/
		fw_x1[0] += 4;
		fw_x2[1] += 6;

		fw_y1[0] -= 4;
		//*/
	}
	else if (bs == "3")
	{
		fw_x1[0] = 171;
		fw_x1[1] = 179;
		fw_y1[0] = 137;
		fw_y1[1] = 148;

		fw_x2[0] = 183;
		fw_x2[1] = 205;
		fw_y2[0] = 134;
		fw_y2[1] = 150;
	}
	else if (bs == "4")
	{
		fw_x1[0] = 174;
		fw_x1[1] = 181;
		fw_y1[0] = 137;
		fw_y1[1] = 148;

		fw_x2[0] = 183;
		fw_x2[1] = 205;
		fw_y2[0] = 134;
		fw_y2[1] = 150;
	}
	else if (bs == "5")
	{
		fw_x1[0] = 117;				//由于填充算法中，窗口的长和宽会被分别临时拉长100像素点
		fw_x1[1] = 138;				//所以，要让最终坐标加100（即，这里原本是38，要让它变138）
		fw_y1[0] = 118;
		fw_y1[1] = 139;

		fw_x2[0] = 139;
		fw_x2[1] = 159;
		fw_y2[0] = 120;
		fw_y2[1] = 135;
	}
	else if (bs == "6")
	{
		fw_x1[0] = 117;
		fw_x1[1] = 138;
		fw_y1[0] = 118;
		fw_y1[1] = 139;

		fw_x2[0] = 139;
		fw_x2[1] = 155;
		fw_y2[0] = 118;
		fw_y2[1] = 135;
	}

	int sz_cj1 = -35;
	int sz_cj2 = 35;


	//1.跳过指定区域进行海水填充
	for (int x = 100;x < ls_c + 100;x++)						//遍历图像中的每一个像素点
	{
		for (int y = 100;y < ls_k + 100;y++)
		{
			bool temp_pd = false;
			for (int i = 0;i < 2;i++)
			{
				if (x >= fw_x1[i] && x <= fw_x2[i] && y >= fw_y1[i] && y <= fw_y2[i])	//则当该坐标为该指定区域时，跳过
				{
					temp_pd = true;
					break;
				}
			}

			if (temp_pd)
			{
				continue;
			}

			ys = getpixel(x, y);		//查看当前点的颜色

			R = GetRValue(ys);					//获取当前像素点的红、绿、蓝数值
			G = GetGValue(ys);
			B = GetBValue(ys);

			//*/如果该点的红绿蓝数值相差不超过20，说明3个3原色数值接近，则该颜色为灰度颜色（白、黑、灰）
			if (R - G >= sz_cj1 && R - G < sz_cj2 && R - B >= sz_cj1 && R - B < sz_cj2 && G - B >= sz_cj1 && G - B < sz_cj2)
			{
				if (R >= 220)
				{
					putpixel(x, y, WHITE);			//则将该点绘制成白色
				}
			}
			if (R == G && R == B && G == B)			//如果三个颜色数值相同
			{
				putpixel(x, y, WHITE);
			}
		}
	}

	//system("pause");
	getimage(&sc_hm, 100, 100, k + 100, g + 100);		//将当前画面获取给色彩画面

	setfillcolor(BLACK);								//将填充颜色设置为黑色

	/*/
	if (num == 2)
	{
		COLORREF temp_ys = getpixel(155, 143);
		floodfill(tc_x, tc_y, temp_ys | WHITE, 0);
	}
	else
	{
	//*/
	floodfill(tc_x, tc_y, WHITE, 0);					//从图片区域(tc_x,tc_y)开始，只要没有碰到白色，就填充为黑色

	setfillcolor(BLACK);								//将填充颜色设置为黑色

	//2.对刚刚跳过的区域，进行一次强制填充
	if (bs == "3" || bs == "4" || bs == "5" || bs == "6")
	{
		solidrectangle(fw_x1[0], fw_y1[0], fw_x1[1], fw_y1[1]);	//填充该区域
		solidrectangle(fw_x2[0], fw_y2[0], fw_x2[1], fw_y2[1]);	//填充该区域
	}

	//system("pause");
	getimage(&hb_hm, 100, 100, k + 100, g + 100);		//将当前画面获取给黑白画面

	Resize(NULL, k, g);									//将图形界面窗口的高度和宽度设置回来
	cleardevice();										//为防止干扰下次操作，进行清屏
}
void hq_sct(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj)	//颜色填充前的准备内容
{
	Resize(NULL, ck_c + 100, ck_k + 100);				//将图形界面窗口的高度和宽度增长100个像素点

	loadimage(&hb_hm, lj);								//将图片加载到黑白画面中
	putimage(100, 100, &hb_hm);							//将黑白画面打印在图形界面窗口(100,100)位置处

	setfillcolor(WHITE);								//将填充颜色设置为白色
	floodfill(0, 0, BLACK, 1);							//从非图片区域开始，只要相邻处为黑色，就填充为白色
}
void hq_hbt(IMAGE& hb_hm, IMAGE& sc_hm, LPCSTR lj)	//颜色填充完后的执行内容
{
	getimage(&hb_hm, 100, 100, ck_c + 100, ck_k + 100);	//将当前画面获取给黑白画面

	Resize(NULL, ck_c, ck_k);							//将图形界面窗口的高度和宽度设置回来
	cleardevice();										//为防止干扰下次操作，进行清屏
}

void hq_cj()										//获取场景
{
	//初始化场景

	IMAGE temp_cj = { ck_c + 650,ck_k };			//临时场景

	loadimage(&temp_cj, Raw_Misc_GameBackground.c_str(), ck_c + 650, ck_k);	//将场景图片加载到临时场景中
	SetWorkingImage(&temp_cj);						//设置当前绘图设备为临时场景

	getimage(&cj, 230, 0, ck_c + 230, ck_k);		//截取部分，给场景

	SetWorkingImage(NULL);							//将当前绘图设备设置为图形界面窗口

	cleardevice();									//为防止干扰下次操作，进行清屏
}
void cshtp()					//使用原始素材文件，获取所有资源的黑白、色彩图片
{
	//创建变量
	int temp_sz = 1;			//文件编号
	sl = 1;						//编号位数


	//1.阳光
	for (int i = 0;i < yg_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		hqtx(yg_hb[i], yg_sc[i], Raw_Sunlight.c_str(), 1, 75, 75, 39, 42);

		//更新文件编号
		gxlj2(Raw_Sunlight, temp_sz,sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;


	//2.子弹
	hqtx(wd_hb, wd_sc, Projectiles.c_str(), 1, 30, 30, 15, 16);	//初始化豌豆

	//3.向日葵
	hqtx(xrkkp_hb, xrkkp_sc, Raw_Sunflower_kp.c_str(), 1, 50, 70);
	for (int i = 0;i < xrk_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		hqtx(xrk_hb[i], xrk_sc[i], Raw_Sunflower.c_str(), 2, 70, 70, 32, 22);

		//更新文件编号
		gxlj2(Raw_Sunflower, temp_sz, sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;

	//4.豌豆射手
	hqtx(wdsskp_hb, wdsskp_sc, Raw_Peashooter_kp.c_str(), 1, 50, 70);
	for (int i = 0;i < wdss_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		hqtx(wdss_hb[i], wdss_sc[i], Raw_Peashooter.c_str(), 1, 70, 70, 32, 22);

		//更新文件编号
		gxlj2(Raw_Peashooter, temp_sz, sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;

	//5.坚果
	//卡片
	hqtx(jgkp_hb, jgkp_sc, Raw_WallNut_kp.c_str(), 1, 50, 70);

	//（1）完整状态
	for (int i = 0;i < jg_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		if (i >= 0 && i <= 16)						//第1到第17张，指定填充区域需要更往右边
		{
			hqtx(jg_hb[i], jg_sc[i], Raw_WallNut_Whole.c_str(), "5", 70, 70, 41, 40);		//获取每张坚果的黑白、色彩图
		}
		else
		{
			hqtx(jg_hb[i], jg_sc[i], Raw_WallNut_Whole.c_str(), "6", 70, 70, 41, 40);
		}

		//更新文件编号
		gxlj2(Raw_WallNut_Whole, temp_sz, sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;
	
	//（2）破损状态
	for (int i = 0;i < jg_ps_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		hqtx(jg_ps_hb[i], jg_ps_sc[i], Raw_WallNut_Damaged.c_str(), "5", 70, 70, 41, 40);

		//更新文件编号
		gxlj2(Raw_WallNut_Damaged, temp_sz, sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;

	//（3）残缺状态
	for (int i = 0;i < jg_wx_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		hqtx(jg_wx_hb[i], jg_wx_sc[i], Raw_WallNut_Broken.c_str(), "5", 70, 70, 41, 40);

		//更新文件编号
		gxlj2(Raw_WallNut_Broken, temp_sz, sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;

	//6.僵尸
	//（1）攻击
	for (int i = 0;i < jsgj_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		if (i >= 0 && i <= 2)
		{
			hqtx(jsgj_hb[i], jsgj_sc[i], Raw_Zombies_Attack.c_str(), "3", 155, 134, 94, 67);
		}
		else if (i == 7 || i == 8)
		{
			hqtx(jsgj_hb[i], jsgj_sc[i], Raw_Zombies_Attack.c_str(), "3", 155, 134, 94, 67);
		}
		else
		{
			hqtx(jsgj_hb[i], jsgj_sc[i], Raw_Zombies_Attack.c_str(), "4", 155, 134, 94, 67);
		}

		//更新文件编号
		gxlj2(Raw_Zombies_Attack, temp_sz, sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;
	
	//（2）移动
	for (int i = 0;i < jsyd_tpsl;i++)
	{
		//根据提供的原始素材，制作黑白、色彩图
		if (i >= 7 && i <= 18)
		{
			hqtx(jsyd_hb[i], jsyd_sc[i], Raw_Zombies_Move.c_str(), "2", 155, 134, 94, 67);		//获取每张僵尸的黑白、色彩图
		}
		else if (i >= 25 && i < 33)
		{
			hqtx(jsyd_hb[i], jsyd_sc[i], Raw_Zombies_Move.c_str(), "1", 155, 134, 94, 67);		//获取每张僵尸的黑白、色彩图
		}
		else
		{
			hqtx(jsyd_hb[i], jsyd_sc[i], Raw_Zombies_Move.c_str(), "-1", 155, 134, 94, 67);
		}

		//更新文件编号
		gxlj2(Raw_Zombies_Move, temp_sz, sl);			//更新路径
	}
	sl = 1;
	temp_sz = 1;

	//7.场景内容
	hqtx(zzyh_hb, zzyh_sc, Raw_Misc_SeedBank.c_str());
	hqtx(cz_hb, cz_sc, Raw_Misc_Shovel.c_str(), 1, 80, 80, 26, 56);
	hqtx(czrq_hb, czrq_sc, Raw_Misc_ShovelContainer.c_str(), 1, 73, 75);
	hqtx(xtc_hb, xtc_sc, Raw_Misc_LawnMower.c_str(), 40, 30);

}
void hq_wzcj()
{
	//打印基础场景
	putimage(0, 0, &cj);									//将场景打印在当前绘图窗口上

	//1.打印种子银行_黑白，然后打印种子银行_色彩（后面一样）
	putimage(57, 0, &zzyh_hb, SRCAND);						//将种子银行_黑白打印在场景(57,0)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(59, 0, BLACK, 1);								//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(57, 0, &zzyh_sc, SRCAND);						//将种子银行_色彩打印在场景(57,0)处

	//2.打印铲子容器
	putimage(650, 0, &czrq_hb, SRCAND);						//将铲子容器_黑白打印在场景(650,0)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(652, 0, BLACK, 1);							//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(650, 0, &czrq_sc, SRCAND);						//将铲子容器_色彩打印在场景(650,0)处	

	//3.打印向日葵_卡片
	putimage(135, 7, &xrkkp_hb, SRCAND);					//将向日葵卡片_黑白打印在场景(135,7)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(140, 12, BLACK, 1);							//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(135, 7, &xrkkp_sc, SRCAND);					//将向日葵卡片_色彩打印在场景(135,7)处

	//4.打印豌豆射手_卡片
	putimage(187, 7, &wdsskp_hb, SRCAND);					//将豌豆射手卡片_黑白打印在场景(187,7)处
	setfillcolor(WHITE);									//将填充颜色设置为白色
	floodfill(192, 12, BLACK, 1);							//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(187, 7, &wdsskp_sc, SRCAND);					//将豌豆射手卡片_色彩打印在场景(187,7)处

	//5.打印坚果_卡片
	putimage(239, 7, &jgkp_hb, SRCAND);
	setfillcolor(WHITE);
	floodfill(244, 12, BLACK, 1);
	putimage(239, 7, &jgkp_sc, SRCAND);

	//将画面赋值给完整场景
	getimage(&wzcj, 0, 0, ck_c, ck_k);						//将当前画面截取给完整场景
	cleardevice();											//为防止干扰下次操作，进行清屏
}
void csh_scwz()									//颜色每处的每处填充（包括黑色填充白色、非白色填充为黑色）
{
	//获取"好..."的黑白、色彩图
	hq_sct(h_hb, h_sc, Raw_Misc_Prompt_Ready.c_str());
	floodfill(26 + 100, 42 + 100, BLACK, 1);			//从非图片区域开始，只要相邻处为黑色，就填充为白色（注意：由于图片目前在(100,100)，坐标值需要加上100）
	getimage(&h_sc, 100, 100, ck_c + 100, ck_k + 100);	//将当前画面获取给色彩画面
	setfillcolor(BLACK);								//将填充颜色设置为黑色
	floodfill(20 + 100, 28 + 100, WHITE, 0);			//从图片区域(tc_x,tc_y)开始，只要没有碰到白色，就填充为黑色（每有一个文字就有填充一次）
	floodfill(60 + 100, 43 + 100, WHITE, 0);
	floodfill(119 + 100, 45 + 100, WHITE, 0);
	floodfill(171 + 100, 45 + 100, WHITE, 0);
	floodfill(229 + 100, 45 + 100, WHITE, 0);
	hq_hbt(h_hb, h_sc, Raw_Misc_Prompt_Ready.c_str());

	//获取"准备..."的黑白、色彩图
	hq_sct(zb_hb, zb_sc, Raw_Misc_Prompt_Set.c_str());
	floodfill(137 + 100, 27 + 100, BLACK, 1);
	floodfill(126 + 100, 61 + 100, BLACK, 1);
	floodfill(126 + 100, 75 + 100, BLACK, 1);
	floodfill(145 + 100, 60 + 100, BLACK, 1);
	getimage(&zb_sc, 100, 100, ck_c + 100, ck_k + 100);	//将当前画面获取给色彩画面
	setfillcolor(BLACK);								//将填充颜色设置为黑色
	floodfill(17 + 100, 29 + 100, WHITE, 0);			//准的两点水的第一点
	floodfill(17 + 100, 62 + 100, WHITE, 0);			//第二点
	floodfill(38 + 100, 42 + 100, WHITE, 0);			//准的右边
	floodfill(138 + 100, 38 + 100, WHITE, 0);			//备的上面
	floodfill(136 + 100, 66 + 100, WHITE, 0);			//备的下面
	floodfill(212 + 100, 43 + 100, WHITE, 0);
	floodfill(266 + 100, 43 + 100, WHITE, 0);
	floodfill(320 + 100, 43 + 100, WHITE, 0);
	hq_hbt(zb_hb, zb_sc, Raw_Misc_Prompt_Set.c_str());

	//获取"开始！"的黑白、色彩图
	hq_sct(ks_hb, ks_sc, Raw_Misc_Prompt_Go.c_str());
	floodfill(46 + 100, 27 + 100, BLACK, 1);
	floodfill(114 + 100, 47 + 100, BLACK, 1);
	floodfill(150 + 100, 65 + 100, BLACK, 1);
	getimage(&ks_sc, 100, 100, ck_c + 100, ck_k + 100);	//将当前画面获取给色彩画面
	setfillcolor(BLACK);								//将填充颜色设置为黑色
	floodfill(58 + 100, 43 + 100, WHITE, 0);			//开
	floodfill(123 + 100, 45 + 100, WHITE, 0);			//始的"女"字旁
	floodfill(149 + 100, 39 + 100, WHITE, 0);			//始的""
	floodfill(155 + 100, 79 + 100, WHITE, 0);			//始的"口"
	floodfill(202 + 100, 71 + 100, WHITE, 0);			//！的"·"
	floodfill(204 + 100, 27 + 100, WHITE, 0);			//！的"l"
	hq_hbt(ks_hb, ks_sc, Raw_Misc_Prompt_Go.c_str());
}
void dqhm(IMAGE& hm, const char* lj)			//获取加载画面
{
	cleardevice();					//清屏
	putimage(0, 0, &hm);			//将画面打印出来
	saveimage(lj, NULL);			//将当前画面读取到图片中
}
void hq_jzhm()
{
	//创建变量
	int temp_bh1 = 1;				//记录"图片_黑白"编号
	int temp_bh2 = 1;				//记录"图片_色彩"编号
	int temp_sl1 = 1;				//记录"图片_黑白"编号的位数
	int temp_sl2 = 1;				//记录"图片_色彩"编号的位数


	//1.阳光
	for (int i = 0;i < yg_tpsl;i++)
	{
		//读取图片内容
		dqhm(yg_hb[i], Sunlight_hb.c_str());			//黑白
		dqhm(yg_sc[i], Sunlight_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Sunlight_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Sunlight_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//2.子弹
	dqhm(wd_hb, Projectiles_hb.c_str());
	dqhm(wd_sc, Projectiles_sc.c_str());


	//3.向日葵
	dqhm(xrkkp_hb, Sunflower_kp_hb.c_str());
	dqhm(xrkkp_sc, Sunflower_kp_sc.c_str());

	for (int i = 0;i < xrk_tpsl;i++)
	{
		//读取图片内容
		dqhm(xrk_hb[i], Sunflower_hb.c_str());			//黑白
		dqhm(xrk_sc[i], Sunflower_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Sunflower_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Sunflower_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//4.豌豆射手
	dqhm(wdsskp_hb, Peashooter_kp_hb.c_str());
	dqhm(wdsskp_sc, Peashooter_kp_sc.c_str());

	for (int i = 0;i < wdss_tpsl;i++)
	{
		//读取图片内容
		dqhm(wdss_hb[i], Peashooter_hb.c_str());			//黑白
		dqhm(wdss_sc[i], Peashooter_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Peashooter_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Peashooter_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//5.坚果
	//卡片
	dqhm(jgkp_hb, WallNut_kp_hb.c_str());
	dqhm(jgkp_sc, WallNut_kp_sc.c_str());

	//（1）完整状态
	for (int i = 0;i < jg_tpsl;i++)
	{
		//读取图片内容
		dqhm(jg_hb[i], WallNut_Whole_hb.c_str());			//黑白
		dqhm(jg_sc[i], WallNut_Whole_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(WallNut_Whole_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(WallNut_Whole_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//（2）破损状态
	for (int i = 0;i < jg_ps_tpsl;i++)
	{
		//读取图片内容
		dqhm(jg_ps_hb[i], WallNut_Damaged_hb.c_str());			//黑白
		dqhm(jg_ps_sc[i], WallNut_Damaged_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(WallNut_Damaged_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(WallNut_Damaged_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//（3）残缺状态
	for (int i = 0;i < jg_wx_tpsl;i++)
	{
		//读取图片内容
		dqhm(jg_wx_hb[i], WallNut_Broken_hb.c_str());			//黑白
		dqhm(jg_wx_sc[i], WallNut_Broken_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(WallNut_Broken_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(WallNut_Broken_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//6.僵尸
	//（1）攻击状态
	for (int i = 0;i < jsgj_tpsl;i++)
	{
		//读取图片内容
		dqhm(jsgj_hb[i], Zombies_Attack_hb.c_str());			//黑白
		dqhm(jsgj_sc[i], Zombies_Attack_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Zombies_Attack_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Zombies_Attack_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//（2）移动状态
	for (int i = 0;i < jsyd_tpsl;i++)
	{
		//读取图片内容
		dqhm(jsyd_hb[i], Zombies_Move_hb.c_str());			//黑白
		dqhm(jsyd_sc[i], Zombies_Move_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Zombies_Move_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Zombies_Move_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//7.场景和场景内容
	dqhm(cj, Misc_GameBackground.c_str());						//将图片加载到画面中
	dqhm(wzcj, Misc_GameBackground_wz.c_str());

	//种子银行
	dqhm(zzyh_hb, Misc_SeedBank_hb.c_str());
	dqhm(zzyh_sc, Misc_SeedBank_sc.c_str());

	//铲子
	dqhm(cz_hb, Misc_Shovel_hb.c_str());
	dqhm(cz_sc, Misc_Shovel_sc.c_str());

	//铲子容器
	dqhm(czrq_hb, Misc_ShovelContainer_hb.c_str());
	dqhm(czrq_sc, Misc_ShovelContainer_sc.c_str());

	//小推车
	dqhm(xtc_hb, Misc_LawnMower_hb.c_str());
	dqhm(xtc_sc, Misc_LawnMower_sc.c_str());

	//提示内容
	dqhm(h_hb, Misc_Prompt_Ready_hb.c_str());
	dqhm(h_sc, Misc_Prompt_Ready_sc.c_str());

	dqhm(zb_hb, Misc_Prompt_Set_hb.c_str());
	dqhm(zb_sc, Misc_Prompt_Set_sc.c_str());

	dqhm(ks_hb, Misc_Prompt_Go_hb.c_str());
	dqhm(ks_sc, Misc_Prompt_Go_sc.c_str());

}

void hq_yxhm()
{
	//创建变量
	int temp_bh1 = 1;				//记录"图片_黑白"编号
	int temp_bh2 = 1;				//记录"图片_色彩"编号
	int temp_sl1 = 1;				//记录"图片_黑白"编号的位数
	int temp_sl2 = 1;				//记录"图片_色彩"编号的位数


	//1.阳光
	for (int i = 0;i < yg_tpsl;i++)
	{
		//读取图片内容
		loadimage(&yg_hb[i], Sunlight_hb.c_str());			//黑白
		loadimage(&yg_sc[i], Sunlight_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Sunlight_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Sunlight_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//2.子弹
	loadimage(&wd_hb, Projectiles_hb.c_str());
	loadimage(&wd_sc, Projectiles_sc.c_str());


	//3.向日葵
	loadimage(&xrkkp_hb, Sunflower_kp_hb.c_str());
	loadimage(&xrkkp_sc, Sunflower_kp_sc.c_str());

	for (int i = 0;i < xrk_tpsl;i++)
	{
		//读取图片内容
		loadimage(&xrk_hb[i], Sunflower_hb.c_str());			//黑白
		loadimage(&xrk_sc[i], Sunflower_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Sunflower_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Sunflower_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//4.豌豆射手
	loadimage(&wdsskp_hb, Peashooter_kp_hb.c_str());
	loadimage(&wdsskp_sc, Peashooter_kp_sc.c_str());

	for (int i = 0;i < wdss_tpsl;i++)
	{
		//读取图片内容
		loadimage(&wdss_hb[i], Peashooter_hb.c_str());			//黑白
		loadimage(&wdss_sc[i], Peashooter_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Peashooter_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Peashooter_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//5.坚果
	//卡片
	loadimage(&jgkp_hb, WallNut_kp_hb.c_str());
	loadimage(&jgkp_sc, WallNut_kp_sc.c_str());

	//（1）完整状态
	for (int i = 0;i < jg_tpsl;i++)
	{
		//读取图片内容
		loadimage(&jg_hb[i], WallNut_Whole_hb.c_str());			//黑白
		loadimage(&jg_sc[i], WallNut_Whole_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(WallNut_Whole_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(WallNut_Whole_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//（2）破损状态
	for (int i = 0;i < jg_ps_tpsl;i++)
	{
		//读取图片内容
		loadimage(&jg_ps_hb[i], WallNut_Damaged_hb.c_str());			//黑白
		loadimage(&jg_ps_sc[i], WallNut_Damaged_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(WallNut_Damaged_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(WallNut_Damaged_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//（3）残缺状态
	for (int i = 0;i < jg_wx_tpsl;i++)
	{
		//读取图片内容
		loadimage(&jg_wx_hb[i], WallNut_Broken_hb.c_str());			//黑白
		loadimage(&jg_wx_sc[i], WallNut_Broken_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(WallNut_Broken_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(WallNut_Broken_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//6.僵尸
	//（1）攻击状态
	for (int i = 0;i < jsgj_tpsl;i++)
	{
		//读取图片内容
		loadimage(&jsgj_hb[i], Zombies_Attack_hb.c_str());			//黑白
		loadimage(&jsgj_sc[i], Zombies_Attack_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Zombies_Attack_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Zombies_Attack_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;

	//（2）移动状态
	for (int i = 0;i < jsyd_tpsl;i++)
	{
		//读取图片内容
		loadimage(&jsyd_hb[i], Zombies_Move_hb.c_str());			//黑白
		loadimage(&jsyd_sc[i], Zombies_Move_sc.c_str());			//色彩

		//更新文件名称编号
		gxlj2(Zombies_Move_hb, temp_bh1, temp_sl1);				//更新"黑白图片"编号
		gxlj2(Zombies_Move_sc, temp_bh2, temp_sl2);				//更新"色彩图片"编号

	}

	//重置文件名称编号数据
	temp_bh1 = 1;
	temp_bh2 = 1;
	temp_sl1 = 1;
	temp_sl2 = 1;


	//7.场景和场景内容
	loadimage(&cj, Misc_GameBackground.c_str());						//将图片加载到画面中
	loadimage(&wzcj, Misc_GameBackground_wz.c_str());

	//种子银行
	loadimage(&zzyh_hb, Misc_SeedBank_hb.c_str());
	loadimage(&zzyh_sc, Misc_SeedBank_sc.c_str());

	//铲子
	loadimage(&cz_hb, Misc_Shovel_hb.c_str());
	loadimage(&cz_sc, Misc_Shovel_sc.c_str());

	//铲子容器
	loadimage(&czrq_hb, Misc_ShovelContainer_hb.c_str());
	loadimage(&czrq_sc, Misc_ShovelContainer_sc.c_str());

	//小推车
	loadimage(&xtc_hb, Misc_LawnMower_hb.c_str());
	loadimage(&xtc_sc, Misc_LawnMower_sc.c_str());

	//提示内容
	loadimage(&h_hb, Misc_Prompt_Ready_hb.c_str());
	loadimage(&h_sc, Misc_Prompt_Ready_sc.c_str());

	loadimage(&zb_hb, Misc_Prompt_Set_hb.c_str());
	loadimage(&zb_sc, Misc_Prompt_Set_sc.c_str());

	loadimage(&ks_hb, Misc_Prompt_Go_hb.c_str());
	loadimage(&ks_sc, Misc_Prompt_Go_sc.c_str());

}