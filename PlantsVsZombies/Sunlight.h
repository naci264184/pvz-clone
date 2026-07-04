#pragma once

#include"ImageData.h"
#include"Utils.h"

//阳光（场景阳光）

//方法_声明
void dy_cjyg();								//打印场景阳光
void dy_yg(int& yg_zzy);					//打印阳光
void dy_yg2(int& yg_zzx2, bool& ygdj_pd, int ygyd_x, int ygyd_y);//打印阳光2（点击了阳光后的打印阳光）
void gxyg_sl(int num);						//更新阳光数量（参数：阳光数量的更改量）
void dy_ygzt(int x, int y, string yg_zt);	//打印阳光字体内容（参数：打印的x轴，y轴，阳光字体内容）
void cxsc_yg(int& yg_zzx, int& yg_zzy);		//重新生成一个阳光
void CalculateSunlightSpeed(int& yg_dqx, int& yg_dqy, int& ygyd_x, int& ygyd_y, int sfwwz_x = -1, int sfwwz_y = -1);

//方法_实现
void dy_cjyg()
{
	putimage(yg_dqx, yg_dqy, &yg_hb[yg_tp], SRCAND);	//将阳光_黑白打印在场景(yg_ddx,yg_ddy)处
	setfillcolor(WHITE);								//将填充颜色设置为白色
	floodfill(yg_dqx + 39, yg_dqy + 42, BLACK, 1);		//从黑色区域开始，只要相邻处为黑色，就填充为白色
	putimage(yg_dqx, yg_dqy, &yg_sc[yg_tp], SRCAND);	//将阳光_色彩打印在场景(yg_dqx,yg_dqy)处
}
void dy_yg(int& yg_zzy)
{
	//1.更新场景阳光y坐标
	if (yg_dqy < yg_zzy)	//只要阳光当前的y坐标，小于阳光最终的y坐标，就更新坐标
	{
		yg_dqy += 4;		//就让阳光当前y坐标+4

		if (yg_dqy >= yg_zzy)	//如果阳光的当前y坐标大于阳光最终y坐标了
		{
			yg_dqy = yg_zzy;	//将阳光当前的y坐标等于阳光最终的y坐标
		}
	}


	//2.打印场景阳光
	dy_cjyg();

	//3.更新图片
	yg_tp++;				//然后切换下一张阳光图片
	if (yg_tp == yg_tpsl)	//如果当前为最后一张阳光图片的后一张
	{
		yg_tp = 0;			//将当前图片设置为第一张
	}
}
void dy_yg2(int& yg_zzx2, bool& ygdj_pd, int ygyd_x, int ygyd_y)
{
	int ygwz_pyl_x = 37;		//阳光位置偏移量_x
	int ygwz_pyl_y = 37;		//阳光位置偏移量_y

	//1.场景阳光移动一次
	yg_dqx -= ygyd_x;		//让阳光移动一次
	yg_dqy -= ygyd_y;


	//2.判断场景阳光是否移动到最终位置
	if ((yg_dqx <= yg_zzx2 - ygwz_pyl_x && yg_dqy <= yg_zzy2 - ygwz_pyl_y) || yg_dqx <= yg_zzx2 - ygwz_pyl_x / 2)
	{
		//yg_dqx = yg_zzx2;	//将阳光当前的x坐标等于阳光最终的x坐标（由于不是小数，移动的距离不精准，这里如果让阳光当前x赋值为阳光最终x会让阳光右移）
		ygdj_pd = false;	//开始新一轮阳光，记录当前阳光点击为否
		gxyg_sl(25);		//更新阳光数量
	}

	//3.打印场景阳光
	dy_cjyg();

	//4.切换下一张场景阳光图片
	yg_tp++;				//然后切换下一张阳光图片
	if (yg_tp == yg_tpsl)	//如果当前为最后一张阳光图片的后一张
	{
		yg_tp = 0;			//将当前图片设置为第一张
	}
}
void gxyg_sl(int num)
{

	yg_sl += num;						//将阳光数量，加上传进来的数值
	ygsl_zt = szzzf(yg_sl);				//将该数字转换为字符串类型
}
void dy_ygzt(int x, int y, string yg_zt)
{
	outtextxy(x, y, yg_zt.c_str());
}
void cxsc_yg(int& yg_zzx, int& yg_zzy)
{
	//yg_zzx = rand() % 801 + 120;			//阳光的x坐标范围为：120~920
	//yg_zzy = rand() % 401 + 140;			//y坐标范围为：140~540

	yg_zzx = GetRandomNumber(yg_z_x, yg_y_x);	//阳光的x坐标范围为：120~920（窗口长度为1100）、80~790（窗口长度为900）
	yg_zzy = GetRandomNumber(140, 540);			//y坐标范围为：140~540
}
void CalculateSunlightSpeed(int& yg_dqx, int& yg_dqy, int& ygyd_x, int& ygyd_y, int sfwwz_x, int sfwwz_y)
{

	//受阳光最小移动速度影响，阳光移动的x坐标会变高，计算受阳光最小移动速度影响后的阳光移动时间
	int yg_ydsj = 0;		//阳光x坐标移速提高后，也应该根据阳光移动总时间，计算阳光y坐标提高的速度
	int temp_yd_y = 0;		//临时y轴移动速度

	int yg_x_jl = 0;		//阳光x轴移动的距离（阳光当前x坐标 - 阳光最终x坐标）
	int yg_y_jl = 0;		//阳光y轴移动的距离（阳光当前y坐标 - 阳光最终y坐标）


	//计算阳光移动距离
	yg_x_jl = yg_dqx + 37 - yg_zzx2;
	yg_y_jl = yg_dqy + 37 - yg_zzy2;

	//防止除以0的情况出现
	if (yg_x_jl == 0)
	{
		yg_x_jl = 1;
	}
	if (yg_y_jl == 0)
	{
		yg_y_jl = 1;
	}

	ygyd_x = yg_x_jl / 8;		//阳光的中心位置在（阳光当前x+36，阳光当前y+37）
	ygyd_y = yg_y_jl / 8;		//而除以8为：1.2秒到达终点（150×8=1200）

	//防止除以0的情况出现
	if (ygyd_x == 0)
	{
		ygyd_x = 1;
	}
	if (ygyd_y == 0)
	{
		ygyd_y = 1;
	}

	//保证阳光最小移动速度不低于一定值
	if (ygyd_x < yg_zxydsd)
	{
		//（1）提高阳光移动的x坐标速度
		ygyd_x = yg_zxydsd;


		//（2）计算阳光移动时间
		yg_ydsj = yg_x_jl / ygyd_x;		//阳光移动时间 = 阳光离终点的距离（坐标）÷ 阳光移动速度

		//（3）防止除以0的情况出现
		if (yg_ydsj == 0)				//当阳光离终点的距离(11) < 阳光移动速度时(12)，阳光的移动时间为0
		{
			yg_ydsj = 1;
		}

		//（4）相应提高y坐标移动速度
		temp_yd_y = yg_y_jl / yg_ydsj;

		//（5）如果阳光的y轴变化特别大
		if (temp_yd_y > ygyd_y * 2)
		{
			//速度变化上限只能是原来的两倍
			ygyd_y *= 2;

			//重新计算阳光移动时间
			yg_ydsj = yg_y_jl / ygyd_y;

			//防止除以0的情况出现
			if (yg_ydsj == 0)
			{
				yg_ydsj = 1;
			}

			ygyd_x = yg_x_jl / yg_ydsj;
		}
		//否则，让y保持原来的提高值
		else
		{
			ygyd_y = temp_yd_y;
		}

		//（6）保证移动值不为负数
		if (ygyd_x <= 0)
		{
			ygyd_x = 1;
		}
		if (ygyd_y <= 0)
		{
			ygyd_y = 1;
		}

		//（7）如果为第一列植物
		if (sfwwz_x >= 50 && sfwwz_x <= 110)		//900的窗口长时，位置在69
		{
			if (sfwwz_y >= 40 && sfwwz_y <= 120)	//不固定，因为向日葵刚产生阳光时，阳光会动
			{
				ygyd_x += 6;
				ygyd_y += 10;

				//cout << "第1列，第1行" << endl;
			}
			else if (sfwwz_y >= 340 && sfwwz_y <= 420 || sfwwz_y >= 440 && sfwwz_y <= 520)
			{
				ygyd_y -= 10;
				//cout << "第1列，第4、5行" << endl;

			}
		}
	}
}
