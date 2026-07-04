#pragma once

#include<easyx.h>
#include<string>
using namespace std;
#include"GameData.h"

//图片数据


//1.未经处理的原始素材

//阳光
string Raw_Sunlight = "Assets/RawAssets/Sunlight/yg1.png";

//子弹
string Projectiles = "Assets/RawAssets/Projectiles/wd.png";

//向日葵
string Raw_Sunflower_kp = "Assets/RawAssets/Plants/Sunflower/xrk_kp.png";
string Raw_Sunflower = "Assets/RawAssets/Plants/Sunflower/xrk1.png";

//豌豆射手
string Raw_Peashooter_kp = "Assets/RawAssets/Plants/Peashooter/wd_kp.png";
string Raw_Peashooter = "Assets/RawAssets/Plants/Peashooter/wd1.png";

//坚果
string Raw_WallNut_kp = "Assets/RawAssets/Plants/WallNut/jg_kp.png";
string Raw_WallNut_Whole = "Assets/RawAssets/Plants/WallNut/Whole/jg1.jpg";
string Raw_WallNut_Damaged = "Assets/RawAssets/Plants/WallNut/Damaged/jg1.jpg";
string Raw_WallNut_Broken = "Assets/RawAssets/Plants/WallNut/Broken/jg1.jpg";

//僵尸
string Raw_Zombies_Attack = "Assets/RawAssets/Zombies/Attack/jsgj1.png";
string Raw_Zombies_Move = "Assets/RawAssets/Zombies/Move/jsyd1.jpg";

//其他（场景和场景内容）
string Raw_Misc_GameBackground = "Assets/RawAssets/Misc/GameBackground.jpg";
string Raw_Misc_SeedBank = "Assets/RawAssets/Misc/SeedBank.png";
string Raw_Misc_Shovel = "Assets/RawAssets/Misc/Shovel.png";
string Raw_Misc_ShovelContainer = "Assets/RawAssets/Misc/ShovelContainer.png";
string Raw_Misc_LawnMower = "Assets/RawAssets/Misc/LawnMower.png";
string Raw_Misc_Prompt_Ready = "Assets/RawAssets/Misc/Prompt_Ready.png";
string Raw_Misc_Prompt_Set = "Assets/RawAssets/Misc/Prompt_Set.png";
string Raw_Misc_Prompt_Go = "Assets/RawAssets/Misc/Prompt_Go.png";


//2.经过处理过的游戏资源

//游戏加载动画
string Splash = "Assets/Splash/yxqdhm1.jpg";
string MainMenu = "Assets/MainMenu/xzjm1.jpg";

//阳光
string Sunlight_hb = "Assets/Sunlight/yg_hb1.png";
string Sunlight_sc = "Assets/Sunlight/yg_sc1.png";

//子弹
string Projectiles_hb = "Assets/Projectiles/wd_hb.png";
string Projectiles_sc = "Assets/Projectiles/wd_sc.png";

//向日葵
string Sunflower_kp_hb = "Assets/Plants/Sunflower/xrk_kp_hb.png";
string Sunflower_kp_sc = "Assets/Plants/Sunflower/xrk_kp_sc.png";
string Sunflower_hb = "Assets/Plants/Sunflower/xrk_hb1.png";
string Sunflower_sc = "Assets/Plants/Sunflower/xrk_sc1.png";

//豌豆射手
string Peashooter_kp_hb = "Assets/Plants/Peashooter/wdss_kp_hb.png";
string Peashooter_kp_sc = "Assets/Plants/Peashooter/wdss_kp_sc.png";
string Peashooter_hb = "Assets/Plants/Peashooter/wdss_hb1.png";
string Peashooter_sc = "Assets/Plants/Peashooter/wdss_sc1.png";

//坚果
string WallNut_kp_hb = "Assets/Plants/WallNut/jg_kp_hb.png";
string WallNut_kp_sc = "Assets/Plants/WallNut/jg_kp_sc.png";
string WallNut_Whole_hb = "Assets/Plants/WallNut/Whole/jg_hb1.png";
string WallNut_Whole_sc = "Assets/Plants/WallNut/Whole/jg_sc1.png";
string WallNut_Damaged_hb = "Assets/Plants/WallNut/Damaged/jg_hb1.png";
string WallNut_Damaged_sc = "Assets/Plants/WallNut/Damaged/jg_sc1.png";
string WallNut_Broken_hb = "Assets/Plants/WallNut/Broken/jg_hb1.png";
string WallNut_Broken_sc = "Assets/Plants/WallNut/Broken/jg_sc1.png";

//僵尸
string Zombies_Attack_hb = "Assets/Zombies/Attack/jsgj_hb1.png";
string Zombies_Attack_sc = "Assets/Zombies/Attack/jsgj_sc1.png";
string Zombies_Move_hb = "Assets/Zombies/Move/jsyd_hb1.png";
string Zombies_Move_sc = "Assets/Zombies/Move/jsyd_sc1.png";

//其他（场景和场景内容）
//场景
string Misc_GameBackground = "Assets/Misc/GameBackground.png";
string Misc_GameBackground_wz = "Assets/Misc/GameBackground_wz.png";

//种子银行
string Misc_SeedBank_hb = "Assets/Misc/SeedBank_hb.png";
string Misc_SeedBank_sc = "Assets/Misc/SeedBank_sc.png";

//铲子
string Misc_Shovel_hb = "Assets/Misc/Shovel_hb.png";
string Misc_Shovel_sc = "Assets/Misc/Shovel_sc.png";

//铲子容器
string Misc_ShovelContainer_hb = "Assets/Misc/ShovelContainer_hb.png";
string Misc_ShovelContainer_sc = "Assets/Misc/ShovelContainer_sc.png";

//小推车
string Misc_LawnMower_hb = "Assets/Misc/LawnMower_hb.png";
string Misc_LawnMower_sc = "Assets/Misc/LawnMower_sc.png";

//提示内容
string Misc_Prompt_Ready_hb = "Assets/Misc/Prompt_Ready_hb.png";
string Misc_Prompt_Ready_sc = "Assets/Misc/Prompt_Ready_sc.png";

string Misc_Prompt_Set_hb = "Assets/Misc/Prompt_Set_hb.png";
string Misc_Prompt_Set_sc = "Assets/Misc/Prompt_Set_sc.png";

string Misc_Prompt_Go_hb = "Assets/Misc/Prompt_Go_hb.png";
string Misc_Prompt_Go_sc = "Assets/Misc/Prompt_Go_sc.png";




//图片画面绘图设备（仅包括需要贴的图片，不包括场景）
//其他
IMAGE zzyh_hb = { ck_c, ck_k };			//种子银行_黑白
IMAGE zzyh_sc = { ck_c, ck_k };			//种子银行_色彩
IMAGE czrq_hb = { ck_c, ck_k };			//铲子容器
IMAGE czrq_sc = { ck_c, ck_k };
IMAGE cz_hb = { ck_c, ck_k };			//铲子
IMAGE cz_sc = { ck_c, ck_k };
IMAGE xtc_hb = { ck_c, ck_k };			//小推车
IMAGE xtc_sc = { ck_c, ck_k };
IMAGE h_hb = { ck_c, ck_k };			//好
IMAGE h_sc = { ck_c, ck_k };
IMAGE zb_hb = { ck_c, ck_k };			//准备
IMAGE zb_sc = { ck_c, ck_k };
IMAGE ks_hb = { ck_c, ck_k };			//开始
IMAGE ks_sc = { ck_c, ck_k };
IMAGE yg_hb[21];			//阳光
IMAGE yg_sc[21];

//植物
IMAGE xrkkp_hb;			//向日葵卡片
IMAGE xrkkp_sc;
IMAGE xrk_hb[18];		//向日葵
IMAGE xrk_sc[18];

IMAGE wdsskp_hb;		//豌豆射手卡片
IMAGE wdsskp_sc;
IMAGE wdss_hb[26];		//豌豆射手
IMAGE wdss_sc[26];
IMAGE wd_hb;			//豌豆
IMAGE wd_sc;

IMAGE jgkp_hb;			//坚果卡片
IMAGE jgkp_sc;
IMAGE* jg_htsb_hb;		//坚果绘图设备
IMAGE* jg_htsb_sc;
IMAGE jg_hb[32];		//坚果
IMAGE jg_sc[32];
IMAGE jg_ps_hb[32];		//破损坚果
IMAGE jg_ps_sc[32];
IMAGE jg_wx_hb[32];		//危险坚果
IMAGE jg_wx_sc[32];

//僵尸
IMAGE jsyd_hb[33];
IMAGE jsyd_sc[33];
IMAGE jsdd_hb[10];
IMAGE jsdd_sc[10];
IMAGE jsgj_hb[22];
IMAGE jsgj_sc[22];

//游戏场景
IMAGE cj = { ck_c, ck_k };			//场景
IMAGE wzcj = { ck_c, ck_k };		//完整场景

//图片数量
int yg_tpsl = 21;
int xrk_tpsl = 18;
int wdss_tpsl = 26;
int jg_tpsl = 32;
int jg_ps_tpsl = 11;
int jg_wx_tpsl = 15;
int jsyd_tpsl = 33;
int jsdd_tpsl = 10;
int jsgj_tpsl = 22;

//图片路径的数字编号
int bh = 0;							//编号
int sl = 1;							//数字的位数（1为1位数，2为2位数）
int bh2 = 0;