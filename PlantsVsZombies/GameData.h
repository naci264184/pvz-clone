#pragma once

#include<easyx.h>
#include<string>
using namespace std;

//游戏数据


//1.程序数据
//窗口大小
int ck_c = 900;
const int ck_k = 600;

//游戏帧率
int yx_jg = 125;			//游戏帧率、125（8帧）
int blcj_bfsd = 18;			//关卡开始的遍历场景，图片切换速度

//游戏时间
int dq_game_time = 0;					//当前游戏时间
int zh_js_swsj = 0;						//游戏胜利时间（最后一个僵尸的消失时间）
int slh_djfyp = 6;						//游戏胜利后，多久放胜利音频
int yxsl_pyl = slh_djfyp + 14 * 1000;	//游戏胜利后，游戏结束时间（游戏胜利_偏移量）


//2.游戏状态
int ysw_js_sl = 0;					//已死亡僵尸数量
bool yx_sfsl = false;				//游戏是否胜利
bool sf_ybfslyp = false;			//是否已播放胜利音频
bool sfybf_jscxy = false;			//是否已播放僵尸出现音


//3.阳光数据
//阳光数量
string ygsl_zt = "50";				//阳光数量_字体
int yg_sl = 50;						//阳光数量
int ygzt_x = 83;					//阳光字体打印位置（这里为三位数时的x坐标，无论为多少位数，y坐标始终为64）
int ygzt_y = 64;

//场景阳光生成范围
int yg_z_x = 80;			//阳光生成范围的x轴左边
int yg_y_x = 790;			//阳光生成范围的x轴右边

//场景阳光_坐标
int yg_dqx = 0;				//阳光的当前坐标
int yg_dqy = 0;
int yg_tp = 0;				//当前为阳光的第几张图片

//场景阳光、向日葵阳光最终坐标
int yg_zzx2 = 110 - 37;		//阳光移动的终点x坐标
int yg_zzy2 = 66;			//阳光移动的终点y坐标

//阳光降下间隔
int yg_jg = 9600;			//阳光下落间隔、9600
int yg_zxydsd = 12;			//阳光最小移动速度

//4.植物数据
int xrk_jg = 22000;			//向日葵产阳光间隔、21000
int wdss_jg = 1900;			//豌豆射手发射豌豆间隔、1900
int wd_ys = 50;				//豌豆移动速度
int wd_sh = 10;				//豌豆的伤害


//5.僵尸数据
//僵尸数量
int zjssl = 7;				//总僵尸数量，设置为7个或10个最好
int xygjs_bh = 0;			//下一个出现的僵尸_编号

//僵尸出现时间
int js_cxsj[255];
int sgjs_cxsj = 25;			//首个僵尸_出现时间、25
int bs_jg = 10;				//波数_间隔、10
int js_cxjg = 22;			//僵尸出现间隔、22
int js_cxjg2 = 14;			//"一大波僵尸即将来袭"时的僵尸出现间隔（即后期的出怪速度）、14
int sjpc = 4;				//僵尸生成间隔的随机偏差（不得大于或等于僵尸出现间隔）、4

//其他数据
int yg_aqx_bh = 0;			//越过安全线的僵尸的编号
int jsgj_jg = 500;			//僵尸攻击间隔、500（虽然游戏帧率按150来算，但是攻击间隔会保留溢出的数值，下次攻击间隔判定时会补上上次溢出值）


//6.草坪位置（窗口长为900）
int cp_zzb_x = 50;			//草坪最左边
int cp_yg_x = 88;			//草坪一格的宽度
int cp_ts_x = 9;			//草坪_特殊x_差距
int zw_zxzzwz_x = -27;		//植物种植位置（植物中心位置，在图片中的x坐标）、种植在草坪时的x轴偏移量


//7.程序开始时创建指定目录（这些目录用于存放"用原始素材处理"得到的"游戏资源"）
namespace fs = std::filesystem;		//将fs设置为命名空间filesystem

//阳光
string sunlight_processed_dir = "Assets/Sunlight";

//子弹
string projectiles_processed_dir = "Assets/Projectiles";

//向日葵
string sunflower_processed_dir = "Assets/Plants/Sunflower";

//豌豆射手
string peashooter_processed_dir = "Assets/Plants/Peashooter";

//坚果
string WallNut_whole_processed_dir = "Assets/Plants/WallNut/Whole";
string WallNut_damaged_processed_dir = "Assets/Plants/WallNut/Damaged";
string WallNut_broken_processed_dir = "Assets/Plants/WallNut/Broken";

//僵尸
string zombies_attack_processed_dir = "Assets/Zombies/Attack";
string zombies_move_processed_dir = "Assets/Zombies/Move";

//场景和场景内容
string Misc_processed_dir = "Assets/Misc";
