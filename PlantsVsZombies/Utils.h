#pragma once


#include <Windows.h>
#include<string>
using namespace std;
#include<fstream>
#include <random>

//工具


//临时文本路径
string temp_text_dir = "temp/logs";				//目录
string temp_text_path = "temp/logs/text.txt";	//文件


//声明
//通用_方法
bool IsFileAccessible(string& lj);				//判断路径是否存在
int GetRandomNumber(int min, int max);			//生成随机数
int zfzsz(string& str, int len);				//字符转数字
string szzzf(int num);							//数字转字符

//其他_方法
void gxlj(string& lj, int& wz, int num);		//更新路径，参数：需要更新的路径，路径中"."的位置，当前为第几张图
void hqbh(string& wj_lj);						//获取编号
void gxlj2(string& lj, int& num, int& temp_sl);	//更新路径2
int sc_sjfw(int jc_sj, int sj_fw, int dw);		//生成_随机范围，参数：基础时间，随机范围，单位
void EnsureAssetDirectoriesExist();				//创建temp/logs目录
void InitializeAssetStorage();					//创建"原始素材处理后的资源"的存放目录


//实现
//通用_方法
bool IsFileAccessible(string& lj)							//判断文件（路径）是否可以打开
{
	ifstream ifs;
	ifs.open(lj, ios::in | ios::binary);
	if (ifs.is_open())							//如果打开成功
	{
		ifs.close();
		return true;							//返回true
	}
	else										//否则（打开失败）
	{
		ifs.close();
		return false;							//返回false
	}
}
int GetRandomNumber(int min, int max)		//参数：最小值, 最大值
{
	// 1. 引擎（含种子）：整个程序只播种一次，并且不长期占用 random_device 资源
	static std::mt19937 gen(std::random_device{}());

	// 2. 分布规则：不用 static，每次根据传入的参数动态创建（极轻量，无性能负担）
	std::uniform_int_distribution<int> dist(min, max);

	// 每次调用只执行这一句，返回不同的数
	return dist(gen);
}
int zfzsz(string& str, int len)			//字符转数字（由于数组传进函数后，长度固定为8，无法靠str.size()在函数里获取长度，所以长度需要传进来）
{
	int s = 0;
	int sz[255];
	int wz = 0;

	for (int i = 0;i < len;i++)
	{
		sz[wz] = str[i];
		wz++;
	}

	for (int i = 0;i < wz;i++)
	{
		s = s * 10 + (sz[i] - 48);
	}

	return s;
}
string szzzf(int num)
{
	string sz;
	fstream fs;

	fs.open(temp_text_path, ios::out);
	fs << num << endl;					//将数字传到文件中
	fs.close();

	fs.open(temp_text_path, ios::in);
	getline(fs, sz);					//再将文件中的内容读回字符串中
	fs.close();

	return sz;
}

//其他_方法
void gxlj(string& lj, int& wz, int num)
{
	if (num < 9)
	{
		lj.insert(wz, 1, (num + 49));
	}
	else if (num == 9)
	{
		lj.insert(wz, 1, '1');
		wz++;
	}
	else if (num == 19)
	{
		lj.erase(wz - 1, 1);
		lj.insert(wz - 1, 1, '2');
	}
	if (num >= 9 && num < 19)
	{
		lj.insert(wz, 1, (num - 9 + 48));
	}
	if (num >= 19 && num < 29)
	{
		lj.insert(wz, 1, (num - 19 + 48));
	}
}
void hqbh(string& wj_lj)							//获取编号（获取文件名的编号）
{
	string temp = wj_lj;							//将路径赋值给临时变量
	int wz = temp.rfind(".");						//查找路径中，最后一个"."的位置	

	if (wz > 0)
	{
		bh = temp.substr(wz - 1, 1)[0] - 48;		//获取.前面的一个编号
		sl = 1;
	}
	if (wz > 1)
	{
		bh2 = temp.substr(wz - 2, 1)[0] - 48;		//获取.前两个位置的字符
		if (bh2 >= 0 && bh2 <= 9)					//如果该字符为数字
		{
			bh = bh2 * 10 + bh;						//让这个数字加入编号
			sl = 2;
		}
	}
	if (wz > 2)
	{
		bh2 = temp.substr(wz - 3, 1)[0] - 48;		//获取.前三个位置的字符
		if (bh2 >= 0 && bh2 <= 9)					//如果该字符为数字
		{
			bh = bh2 * 100 + bh;					//让这个数字加入编号
			sl = 3;
		}
	}
}
void gxlj2(string& lj, int& num, int& temp_sl)			//参数：路径，当前编号
{
	int wz = lj.rfind(".");
	string temp = lj.substr(wz - temp_sl, temp_sl);
	int s = zfzsz(temp, temp.size());
	s++;
	temp = szzzf(s);
	lj.replace(wz - temp_sl, temp_sl, temp);

	if (num == 9)
	{
		temp_sl = 2;
	}
	else if (num == 99)
	{
		temp_sl = 3;
	}

	num++;
}
int sc_sjfw(int jc_sj, int sj_fw, int dw)		//参数：基础时间，随机范围，单位（如：基础时间为16，范围为+-4，单位为1000（即秒））
{
	return GetRandomNumber(jc_sj - sj_fw, jc_sj + sj_fw) * dw;
}
void EnsureAssetDirectoriesExist()
{
	//在当前目录下，创建一个临时数据目录，如果目录存在会自动跳过
	fs::create_directories(temp_text_dir);
}
void InitializeAssetStorage()
{
	//尝试执行try里的内容，如果try的内容会导致程序崩溃，则立即执行catch里的内容
	try
	{
		// 直接引用变量，不写重复的字面值
		vector<string> required_dirs =
		{
			sunlight_processed_dir,
			projectiles_processed_dir,
			sunflower_processed_dir,
			peashooter_processed_dir,
			WallNut_whole_processed_dir,
			WallNut_damaged_processed_dir,
			WallNut_broken_processed_dir,
			zombies_attack_processed_dir,
			zombies_move_processed_dir,
			Misc_processed_dir
		};

		for (const auto& dir : required_dirs)
		{
			fs::create_directories(dir);
		}
	}
	catch (const fs::filesystem_error& e)
	{
		std::cerr << "错误：游戏无法创建必要的资源文件夹，无法正常运行！" << std::endl;
		std::cerr << "请尝试【以管理员身份运行】本游戏，或检查磁盘是否已满。" << std::endl;
		std::cerr << "详细信息：" << e.what() << std::endl;
		//std::cerr << "目录创建失败：" << e.what() << std::endl;

		cin.get();
		exit(-1);
	}
}
