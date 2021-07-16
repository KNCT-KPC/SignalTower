#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define slp    sleep(2)
#define slp_M  sleep(5)
#define slp_L  sleep(7)
#define cls    system("cls")
#define dot    do{printf(".");sleep(1);printf(".");sleep(1);printf(".");sleep(1);}while(0)

void Look     (int);         //comsuch 01xx
void Move     (int);         //comsuch 02xx
void Pick     (int);         //comsuch 03xx
void Touch    (int);         //comsuch 04xx
void Use      (int);         //comsuch 05xx
void Ride     (int);         //comsuch 06xx
void Badcom   (int);         //comsuch 99xx
void Die      (int);         //comsuch 66xx
void kojo     (int);         //口上文
void sumdie   ();            //頭ぶつけたとき用
void com      (int *);       //メイン判別
int  subcom   (int,int,int); //共通値保存用　代入値、代入先、モード(書き込み0,読み込み1) structで作れなかったので代用してます
int  s_com   (int *,int);        //com上での判別->遷移関数です
void goal     (int);
char moji[1000];

struct lib
{
    int  id;
    char txt[1000];
};

int  rdm_go   (void)
{
    int s;
    srand(time(NULL));
    s = rand() % 2 + 1;
    return s;
}

int  main     (void)
{
    int stage = 0;                    //ステージ数
    int torch =0;                     //松明の状態 1=所持 2=着火済
    int rute_r = 0;
    int rute_l = 0;
    int rute_f = 0;
    int comsuch = 0;
    int sword = 0;
    int boat = 0;
    int button =0;
    int eda_loop = 0;
    int boat_time = 0;
    int r_go = 0;
    subcom(0,0,0);                    //subcom初期化
    while(1)//メインループ
    {
    if      (stage == 0 && torch == 0)
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 301)
            {
                torch = 1;
                subcom(torch,2,0);
                 
                break;
            }
        }
    }
    else if (stage == 0 && torch == 1)
    {   
        while(1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 501 || comsuch == 502)
            {
                torch = 2;
                subcom(torch,2,0);
                break;
            }
        }
    }
    else if (stage == 0 && torch == 2)//開始地点
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 201)
            {
                stage = 1;
                subcom(stage,1,0); 
                 break;
            }
        }
    }
    else if (stage == 1 && rute_f == 0 && rute_l == 0 && rute_r == 0)//分岐
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            slp;cls;
            if (comsuch == 201)
            {
                stage = 2; rute_f = 1; torch = 1; eda_loop++; 
                subcom(stage,1,0);subcom(rute_f,3,0); break;
            }
            else if (comsuch == 202)
            {
                stage = 2; rute_r = 1; eda_loop++; 
                    subcom(stage,1,0);subcom(rute_r,4,0); break;
            }
            else if (comsuch == 203)
            {
                stage = 2; rute_l = 1; eda_loop++;
                subcom(stage,1,0);subcom(rute_l,5,0); break;
            }
            else if (comsuch == 204)
            {
                stage--;eda_loop++;
                subcom(stage,1,0);
                break;
            }
        }
    }
    else if (stage == 2 && rute_r == 1)//右 1
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 201)
            {
                rute_r = 2; 
                subcom(rute_r,4,0);  break;
            }
            else if (comsuch == 402)
            {
                Die(660201);
            }
            else if (comsuch == 204)
            {
                stage--;
                subcom(stage,1,0);
                break;
            }
        }
    }
    else if (stage == 2 && rute_r == 2)//右 2
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 201)//前に進む
            {
                if (sword == 0)//枝１へ
                {
                    stage = 1; rute_r = 0; 
                    subcom(stage,1,0); subcom(rute_r,4,0);  break;
                }
                else if (sword == 1)//右３へ
                {
                    rute_r = 3;
                    subcom(rute_r,4,0);break;
                }
            }
            else if (comsuch == 204)
                {
                    rute_r--;
                    subcom(rute_r,4,0);
                    break;
                }
            else if (comsuch == 302)//剣を拾う
            {
                sword = 1;
                subcom(1,6,0);
                 
            }
        }
    }
    else if (stage == 2 && rute_r == 3)//右 3
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (button == 0)//ボタン放置
            {
                if (comsuch == 201)//前へ
                {
                    Die(661000);
                }
            }

            else if (comsuch == 403)//ボタン押す
            {
                button = 1;
                subcom(button,8,0);
            }
            
            else if (comsuch == 204)
            {
                rute_r--;
                subcom(rute_r,4,0);
                button = 0;
                subcom(button,8,0);
                break;
            }
            else if (button == 1)//ボタン押下
            {
                if (comsuch == 201 || comsuch == 205)
                {
                    stage = 3;
                    rute_r = 4;
                    subcom(stage,1,0);
                    subcom(rute_r,4,0);
                    break;
                }    
            }
        }
    }
    else if (stage == 3 && rute_r == 4)//右4
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 602)
            {
                boat = 2;
                rute_l = 5;
                subcom(rute_r,4,0);
                subcom(boat,7,0);  break;
            }
        }
    }
    else if (stage == 3 && rute_r == 5)//右5
    {
        cls;
        printf("あなたがトロッコに乗った瞬間、突然トロッコが唸りをあげて急加速した！\n");slp;
        printf("とっさにブレーキレバーを引いたら折れてしまった！\n");slp;
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 202)
            {
                goal(2);
            }
            else if (comsuch == 203)
            {
                rute_r = 0;
                rute_f = 2;
                stage = 4;
                boat_time = 0;
                subcom(rute_r,4,0);
                subcom(rute_f,3,0);
                subcom(stage,1,0);  break;
            }
            else if (boat_time == 5)
            {
                printf("\n\n長く考えすぎた！もう行くしかない！");slp;
                rute_r = 0;
                rute_f = 2;
                stage = 4;
                subcom(rute_r,4,0);
                subcom(rute_f,3,0);
                subcom(stage,1,0);  break;
               
            }
            boat_time++;
        }
    }   
    else if (stage == 2 && rute_f == 1)//正面
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 201 || comsuch == 202 || comsuch == 203 )//進む
            {
                r_go = rdm_go();
                if (r_go == 1)
                {
                    rute_l = 1;
                    rute_f = 0;
                    stage = 2;
                    subcom(rute_l,5,0);
                    subcom(rute_f,3,0);
                    subcom(stage,1,0);
                    break;
                }
                else if (r_go != 1)
                {
                    rute_r = 1;
                    rute_f = 0;
                    stage = 2;
                    subcom(rute_r,4,0);
                    subcom(rute_f,3,0);
                    subcom(stage,1,0);
                    break;
                }
            }
        }
    }
    else if (stage == 2 && rute_l == 1)//左1
    {
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 601)
            {
                boat = 1;
                rute_l = 2;
                subcom(rute_l,5,0);
                subcom(boat,7,0);  break;
            }
        }
    }
    else if (stage == 2 && rute_l == 2)//左2
    {
        cls;
        printf("あなたがボートに乗った瞬間、突然ボートが唸りをあげて急加速した！\n");slp;
        printf("よく見ると後ろに不釣り合いな大型エンジンが乗っている！\n");slp;
        while (1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 202)
            {
                goal(1);
            }
            else if (comsuch == 203)
            {
                rute_l = 0;
                rute_f = 2;
                stage = 4;
                boat_time = 0;
                subcom(rute_l,5,0);
                subcom(rute_f,3,0);
                subcom(stage,1,0);  break;
            }
            else if (boat_time == 5)
            {
                printf("\n\n長く考えすぎた！壁にぶつかる！");slp;
                cls;
                Die(6604);
            }
            boat_time++;
        }
    }     
    else if (stage == 4 && rute_f == 2)
    {   
        while(1)
        {
            kojo(eda_loop);
            com(&comsuch);
            cls;
            if (comsuch == 504)
            {
                goal(3);
            }
        }
    }
    }
return 0;
}
   
void Look     (int comback)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    int boat  = subcom(0,7,1);
    int button= subcom(0,8,1);
    if (comback >= 10101 && comback <= 10199)
    {
        
        if (stg == 0)
            {
                if (torch != 2)
            {
                printf("辺りは真っ暗だ。何も見えない。");
                slp;
            }   
            else if (torch == 2)
            {
                printf("灰色の床が松明によってオレンジに照らされている。\n洞窟は前方に広がっていて、周りは壁に囲まれている。\n\n");
                slp_M;
            }
        }
        
        
        else if (stg == 1)
            {
                printf("右の穴は狭く細いが、薄く光っている。\n正面の穴から、強く風が吹いている。\n左の穴からは水の流れる音がする。");
                slp_M;
            }
        
        
        if (stg == 2)
        {
            if (right == 1)
            {
                printf("天井に緑に光る物体があり、その明かりが細道全体を照らしている。洞窟は奥へと続いている。\n\n天井に手が届きそうだ。");
                slp_M;
            }
            else if (right == 2)
            {
                printf("あなたが剣を手に取った瞬間、体が勝手に動き目の前の階段を叩き切った。\nすると剣はポキンと折れてしまった。\n\n階段が消し飛び、通路が現れた。\n\n");
                slp_M;
            }
            else if (right == 3 && button == 0)
            {
                printf("小さな小部屋の壁にゲーミング発光するボタンがある。\n小部屋の脇には小さな通路があり、「入口」と書かれている。\n\n");
                slp_M;
            }
            else if (right == 3 && button == 1)
            {
                printf("ボタンは光を失った。\n壁が動いて現れたドアには「ファスト・パスをお持ちの方」と案内が書いてある。\n脇の通路は動いた壁によってふさがってしまったようだ\n\n");
                slp_M;
            }
            else if (fowd == 1)
            {
                printf("前からとてつもない強風が吹いていて目が開けられない！\n\n");
                slp_M;
            }
            else if (left == 1)
            {
                printf("小さな船着き場に、ボートが一艘係留されている。\n道はここて途切れているようだ。");
                slp_M;
            }
        }
        
        
        if (stg == 3)
        {
            if (right == 4)
            {
                printf("今まで通ってきたところとはまるで違う雰囲気の場所だ。\n廃墟のような駅のホームに不釣り合いなピカピカのトロッコが一台置かれている。\n");slp_M;
            }
            else if (right == 5)
            {
                printf("左のレールの先は2段縦ループだ！\n右のレールの先は3段うずまき横ループだ！\n");slp_M;
            }
            else if (left == 2)
            {
                printf("右の水路は流れが速い！\n左の水路は渦巻いている！");
            }
            
        }
        
        
    }
    else if (comback >= 10201 && comback <= 10299)//剣
    {
        if (stg == 2 && right == 2 && sword == 0) 
        {
            printf("鉛色に光る剣が広場の中央に落ちている。\nあなたでも扱えそうな大きさだ。");
            slp_M;
        }
        else if (sword == 1)
        {
            printf("おもちゃの剣だ。無茶苦茶軽い。");
            slp_M;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 10301 && comback <= 10399)//壁
    {
        if (stg == 0)
        {
            printf("壁は灰色のごつごつとした石灰岩だ。\n所々に手で掘った跡があるが、うまくいかなかったようだ。");
            slp_M;
        }
        else if (stg == 1)
        {
            printf("壁は灰色のごつごつとした石灰岩だ。\n左手法だったか右手法だったかであなたは首をひねっている。");
            slp_M;
        }
        else if (right == 1)
        {
            printf("壁は湿っぽく、苔でも生えそうだ。\nなんだかヌメヌメしている…");
            slp_M;
        }
        else if (right == 2)
        {
            printf("壁伝いに歩くと階段があった。\n階段は上につながっているようだが、階段があるところの壁だけが色が違う…");
            slp_M;
        }
        else if (right == 3 && button == 0)
        {
            printf("ゲーミングボタンのせいで壁は虹色に照らされている。");
            slp_M;
        }
        else if (right == 3 && button == 1)
        {
            printf("壁は落ち着きを取り戻した。");
            slp_M;
        }
        else if (right == 4)
        {
            printf("壁には朽ち切ったポスターが何枚か張ってある。");
            slp_M;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 10401 && comback <= 10499)//天井
    {
        if (stg == 0 || stg == 1)
        {
            printf("天井は背伸びすればぎりぎり届く高さにある。\nコウモリとかは特にいない。");
            slp_M;
        }
        else if (right == 1)
        {
            printf("緑色の物体としか表現のしようのない物がへばりついている。\n背を伸ばせば手が届きそうだ。");
            slp_M;
        }
        else if (right == 2)
        {
            printf("天井にはどう頑張っても手が届かなそうだ。");
            slp_M;
        }
        else if (right == 3 && button == 0)
        {
            printf("ゲーミングボタンのせいで天井は虹色に照らされている。");
            slp_M;
        }
        else if (right == 3 && button == 1)
        {
            printf("天井は落ち着きを取り戻した。");
            slp_M;
        }
        else if (right == 4)
        {
            printf("天井はトタン張りだ。ところどころ穴が開いている。");
            slp_M;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 10501 && comback <= 10599)//緑
    {
        if (right == 1)
        {
            printf("緑色の物体としか表現のしようのない物がへばりついている。\n背を伸ばせば手が届きそうだ。");
            slp_M;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 10601 && comback <= 10699)//ボタン
    {
        if (right == 3 && button == 0)
        {
            printf("ボタンはゲーミングPCよろしく七色発光している。少しまぶしい。");
            slp_M;
        }
        else if (right == 3 && button == 1)
        {
            printf("ボタンは光るのを止め、押された状態から戻らなくなっている。");
            slp_M;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 10701 && comback <= 10799)//ドア
    {
        if (right == 3 && button == 1)
        {
            printf("オレンジ色のドアだ。なぜか塗りたてのペンキのにおいがする。\n「ファスト・パスをお持ちの方」と案内が書いてある。");
            slp_M;
        }
        else
        {
            Badcom(999900);
        } 
    }
    else if (comback >= 10801 && comback <= 10899)//台座
    {
        if (fowd == 2)
        {
            printf("剣の台座だ。古ぼけている…");
            slp_M;
        } 
        else
        {
            Badcom(999900);
        }
    }
    else
    {
        Badcom(999900);
    }
}    

void Move     (int comback)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    if (comback >= 20100 && comback <= 20199 || comback >= 20500 && comback <= 20599 )//前進
    {
        if (stg == 0 &&  torch != 2)
        {
            printf("暗闇の中でめちゃくちゃに進んだせいで、頭を強くぶつけた。先に明かりを見つけよう。"); 
            slp;
            sumdie();
        }
        else if (stg == 0 && torch == 2 || right == 1|| right == 2 || right == 3)
        {
            printf("あなたは前へ進む");
            dot;
        }
        else if (left == 1 || right == 4)
        {
            printf("道は途切れている…");
            dot;
        }
        else if (left == 2)
        {
            printf("前には進めない！");
        }
        
        else if (fowd == 1)
        {
            printf("あなたはむちゃくちゃに進んだ");
            dot;printf("!");slp;
        }
        else if (stg == 1)
        {
            printf("あなたは正面の洞窟へ進む");
            dot;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 20200 && comback <= 20299)//右
    {
        if (stg == 0 &&  torch != 2)
        {
            printf("暗闇の中でめちゃくちゃに進んだせいで、頭を強くぶつけた。先に明かりを見つけよう。"); 
            slp;
            sumdie();
        }
        else if (stg == 1)
        {
            printf("あなたは右の穴へと進む");
            dot;
        }
        else if (left == 2 || left == 1)
        {
            printf("あなたは右へ舵を進めた！");
            slp;
        }
        else if (stg == 0 && torch == 2 || right == 1 || right == 2 || right == 3 || right == 4 || left == 1)
        {
            printf("右は壁だ。進めない");
            dot;
        }
        else if (fowd == 1)
        {
            printf("あなたはむちゃくちゃに進んだ");
            dot;printf("!");slp;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 20300 && comback <= 20399)//左
    {
        if (stg == 0 &&  torch != 2)
        {
            printf("暗闇の中でめちゃくちゃに進んだせいで、頭を強くぶつけた。先に明かりを見つけよう。"); 
            slp;
            sumdie();
        }
        else if (stg == 1)
        {
            printf("あなたはは左の穴へ進む");
            dot;
        }
        else if (left == 2)
        {
            printf("あなたは左へ舵を進めた！");
            slp;
        }
        else if (stg == 0 && torch == 2 || right == 1 || right == 2)
        {
            printf("左は壁だ。進めない");
            dot;
        }
        else if (fowd == 1)
        {
            printf("あなたはむちゃくちゃに進んだ");
            dot;printf("!");slp;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 20400 && comback <= 20499)//後ろ
    {
        if (stg == 0 &&  torch != 2)
        {
            printf("暗闇の中でめちゃくちゃに進んだせいで、頭を強くぶつけた。先に明かりを見つけよう。"); 
            slp;
            sumdie();
        }
        else if (comback == 20407)
        {
            printf("あなたはムーンウォークの意味を間違えていた…\n");slp;
            if (stg == 0)
            {
            printf("後ろは壁だ。");
            slp;
            }
            else if (left == 2 || right == 5)
            {
                printf("無理！");slp;
            }
            else if (fowd == 2)
            {
                printf("戻れそうにない…");slp;
            }
            else
            {
            printf("あなたは引き返す");
            dot;
            }
        }
        else if (stg == 0)
        {
            printf("後ろは壁だ。");
            slp;
        }
        else if (left == 2 || right == 5)
        {
            printf("無理！");slp;
        }
        else if (fowd == 2)
        {
            printf("戻れそうにない…");slp;
        }
        else
        {
            printf("あなたは引き返す");
            dot;
        }
    }
    else
    {
        Badcom(999900);
    }
}      

void Pick     (int comback)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    if (comback >= 30100 && comback <= 30199)//松明を拾う
    {
        if (stg == 0 && torch == 0)
        {
            printf("あなたは松明を拾った。"); 
            slp;
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 30200 && comback <= 30299)//剣を拾う
    {
        if (stg == 2)
        {
            printf("あなたが剣を手に取った瞬間、体が勝手に動き目の前の階段を叩き切った。\n\n階段が消し飛び、通路が現れた。\n\n"); 
            slp_L;
        }
        else if (sword == 1)
        {
            printf("剣はすでに持っている。");
            slp;
        }
        else
        {
        Badcom(999900);
        }
    }
    else
    {
        Badcom(999900);
    }
}      

void Touch    (int comback)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    int button = subcom(0,8,1);
    if (comback >= 40100 && comback <= 40199)//壁に触る
    {
        if (stg == 0 && torch == 0 || stg == 0 && torch == 1)
        {
            printf("壁がゴツゴツとしているのがなんとなくわかる。"); 
            slp;
        }
        else if (torch == 2)
        {
            Look(10301);
        }
        else
        {
            Badcom(999900);
        }
    }
    else if (comback >= 40300 && comback <= 40399)//ボタンを押す
    {
        if (right == 3 && button == 0)
        {
            printf("ボタンを押すと、轟音とともに壁がスライドしてドアが現れた。\nドアには「ファスト・パスをお持ちの方」と案内が書いてある。\n"); 
            slp_M;
        }
        else if (right == 3 && button == 1)
        {
            printf("すでにボタンは押されている。");
            slp;
        }
        else
        {
            Badcom(999900);
        }
    }
    if (comback >= 40400 && comback <= 40499)//緑のものにさわる
    {
        if (stg == 0 && torch == 0 || stg == 0 && torch == 1)
        {
            printf("緑のものに触れる…"); 
            slp;
            Die(660201);
        }
        else
        {
            Badcom(999900);
        }
    }
    else
    {
        Badcom(999900);
    }
}     

void Use      (int comback)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    if (comback >= 50100 && comback <= 50199)//松明に火を着ける
    {
        if (fowd == 1)
        {
            printf("松明に火をつけようとしたが、風で吹き消えてしまった！\n");
            printf("%d",comback); 
            slp;
        }
        else if (torch == 1)
        {
            printf("あなたは松明に火をつけた。"); 
            slp;
        }
        else if (stg == 0 && torch == 0)
        {
            printf("松明はあなたの隣に転がったままだ。\n");
            slp;
        }
        else
        {
            Badcom(999900);
        }
    }
    
    else if (comback >= 50200 && comback <= 50299)//マッチを使う
    {
        if (fowd == 1)
        {
            printf("マッチに火をつけようとしたが、風で吹き消えてしまった！\n");
            slp;
        }
        else if (torch == 1)
        {
            printf("あなたは松明に火をつけた。"); 
            slp;
        }
        else
        {
            Badcom(991000);
            slp;
        }
    }
    else if (comback >= 50400 && comback <= 50499)//剣を使う
    {
        if (fowd == 2)
        {
            printf("あなたは剣を台座にはめる\n"); 
            slp;
        }
        else
        {
            Badcom(999900);
        }
    }
    else
    {
        Badcom(999900);
    }
}     

void Ride     (int comback)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int boat  = subcom(0,7,1);
    int i = 0;
    if (comback >= 60100 && comback <= 60199)//ボートに乗る
    {
        if (left == 1)
        {
            printf("あなたはボートへと乗り込み、繋がっていた縄を外した");
            dot;
        }
        else if (left == 2)
        {
            printf("あなたはすでにボートの上に乗っている。"); 
            slp;
        }
    }
    else if (comback >= 60200 && comback <= 60299)
    {
        if (boat == 0)
        {
            printf("あなたはトロッコに乗り込んだ\n");
            dot;
        }
        else if (boat == 1)
        {
            printf("あなたはすでにトロッコに乗っている。"); 
            slp;
        }
        else
        {
            Badcom(999900);
        }
    }
    else
    {
        Badcom(999900);
    }
}   

void Die     (int comback)
{  
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    int boat  = subcom(0,7,1);
    if (comback >= 660100 && comback <= 660199)
    {
        printf("\n\nあなたは魔が差して自分に火をつけた");
        dot;
        exit(0);
    }
    else if (comback >= 660200 && comback <= 660299)
    {
        printf("\n\nあなたが緑のものに触れると、腕からは煙が上がり、溶けだした。\n\nあなたが痛みでもがいていると、上から緑のものが大量にこぼれ落ちてきた");
        dot;
        exit(0);
    }
    else if (comback >= 660300 && comback <= 660399)
    {
        printf("\n\nあなたは壁に何度も頭を打ち付け、自ら頭をかち割った");
        dot;
        exit(0);
    }
    else if (comback >= 660400 && comback <= 660499)
    {
        printf("\n\nあなたは壁に激突し、爆散した");
        dot;
        exit(0);
    }
    else if (comback >= 660500 && comback <= 660599)
    {
        if (left == 1)
        {
            printf("あなたは泳げない体質だった");
            dot;
            exit(0);
        }
        else if (left == 2)
        {
            printf("あなたはボートから飛び降りたが、高速回転するスクリューにぶつかって消し飛ばされた");
            dot;
            exit(0);
        }
        else if (right == 5)
        {
            printf("\n\nあなたはトロッコから飛び降りたが、後ろからやってきた「カメラ車」と書かれたトロッコにはねられた");
            dot;
            exit(0);
        }
        else
        {
            Badcom(999900);
        }
    }
     else if (comback >= 661000 && comback <= 661099)
    {
        printf("「スローパスはこちら」と書かれたほうを進むと、突如現れた殺人鬼に斬りかかられた！\n");slp;
        printf("あなたが最後に見たのは「スロー（ﾀｰ）」という文字だった");
        dot;
        slp;
        exit(0);
    }
    else if (comback == 669001)
    {
        printf("\n\nあなたは松明を「まつあき」と読んでしまったことをひどく後悔した");
        dot;
        printf("\n\nあなたは下を紙切って史んだ！");
        slp;exit(0);
    }
    else if (comback == 669002)
    {
        printf("\n\nあなたは松明を「まつみょう」と読んでしまったことをひどく後悔した");
        dot;
        printf("\n\nあなたは下を紙切って史んだ！");
        slp;exit(0);
    }
    else
        {
            Badcom(999900);
        }
}

void sumdie  ()
{
    static int baka;
    baka++;
    if (baka == 5)
    {
        Die(660300);
    }
}

void goal (int num)
{
    if (num == 1)
    {
        printf("あなたがボートを右に進めると、突如轟音と共に下から水が吹き上がってきた！\n");
        printf("ボートはぐんぐん上昇していき、ついに外に出た！\n");
        printf("お疲れさまでした。\n");
        slp_L;slp_L;exit;
    }
    else if (num == 2)
    {
        printf("５分ほど走るとトロッコは洞窟を抜け、一つの廃駅で止まった。\n");
        printf("駅名標には「明延鉱山　南第二抗口」と書かれている。\n気づけばスマホが手にあり、電波がしっかり入っていた。\n");
        printf("お疲れさまでした。\n");
        slp_L;slp_L;exit;
    }
    else if (num == 3)
    {
        printf("あなたが剣を台座にはめると、剣が赤く光り目の前の壁をぶった切った！\n");
        printf("気付くとあなたは自宅の前に立っていた…。\n");
        printf("お疲れさまでした。\n");
        slp_L;slp_L;exit;
    }
    else
        {
            Badcom(999900);
        }
}

void Badcom  (int comback)
{
    {
        int stg   = subcom(0,1,1);
        int torch = subcom(0,2,1);
        int fowd  = subcom(0,3,1);
        int right = subcom(0,4,1);
        int left  = subcom(0,5,1);
        int sword = subcom(0,6,1);
        if (comback == 990100 || comback == 990200) //進む、歩く
        {
            if  (stg == 0 && torch != 2)
            {
                printf("暗闇の中でめちゃくちゃに進んだせいで、頭を強くぶつけた。先に明かりを見つけよう。"); 
                slp;
                sumdie();
            }
        }
        else if (comback == 990700)//まつあき
        {
            Die(669000);
        }
        else if (comback == 990800)//まつみょう
        {
            Die(669002);
        }
        else if (comback == 990900)
        {
            printf("エンジンは吹き上がってしまって止まらない！");
            slp;
        }
        else if (comback == 999900)
        {
            printf("すみません、よく分かりません。");
            slp;  
        }
        
    }
}

void kojo    (int loop)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    int boat  = subcom(0,7,1);
    int button  = subcom(0,8,1);
    
    if (stg == 0)
    {
        if      (stg == 0 && torch == 0)
        {
            printf("あなたは気がつくと真っ暗な洞窟の中にいた。\n近くには火のともっていない松明が落ちている。\n\n");
 		    printf("行動を入力して下さい。\n\n");
        }
        else if (stg == 0 && torch == 1)
        {
            printf("あなたは暗い洞窟に立っている。手には火のついていない松明がある。\nあなたはポケットにマッチが入っていることに気がついた。\n\n");
 		    printf("行動を入力して下さい。\n\n");
        }
        else if (stg == 0 && torch == 2 && loop == 0)
        {
            printf("松明に火がつき、辺りが明るくなった。松明が暖かく、あなたは少し安心した。\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
        else if (stg == 0 && torch == 2 && loop != 0)
        {
            printf("あなたが最初にいたところだ。特に何もない。\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
    }
    
    if (stg == 1)
    {
        if (right == 0 && left == 0 && fowd ==0 && loop == 0)
        {
            printf("進んだ先は三つに枝分かれしている。松明の火が奥まで届かない。\n\n");
            printf("行動を入力して下さい。\n\n"); 
        }
        else if (right == 0 && left == 0 && fowd ==0 && loop != 0)
        {
            printf("進んだ先は三つに枝分かれしている。どうやら戻ってきてしまったようだ。\n\n");
            printf("行動を入力して下さい。\n\n"); 
        }
        else{printf("ERROR!!!!");slp_L;}
    }
    
    if (stg == 2)
    {
        if (right == 1)
        {
            printf("右の穴には、人がやっと一人通れるくらいの道が広がっている。天井が緑に光っている...\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
        else if (right == 2 && sword == 0)
        {
            printf("しばらく歩くと開けたところに出た。広場の真ん中には剣が落ちている。\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
        else if (right == 2 && sword == 1)
        {
            printf("剣はおもちゃの剣に変化した。階段がなくなり通路が現れた。\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
        else if (right == 3)
        {
            printf("通路を進むと、小部屋にたどり着いた。\n変なボタンがある。\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
        else if (fowd == 1)
        {
            printf("前から強烈な風が吹いている！松明が消えてしまった！\n\n");
 	        printf("行動を入力して下さい！\n\n"); 
        }
        else if (left == 1)
        {
            printf("進んだ先には小さな水路があり、ボートが浮かんでいる…\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
        else if (left == 2)
        {
            printf("目の前から壁が迫ってくる！右と左に水路がある！\n\n");
 	        printf("行動を入力して下さい！\n\n"); 
        }
    }
    
    if (stg == 3)
    {
        if (right == 4)
        {
            printf("あなたがドアを開けて進むと、駅のような場所にたどり着いた。\nトロッコが一台、線路上に放置されている。\n\n");
 	        printf("行動を入力して下さい。\n\n"); 
        }
        else if (right == 5)
        {
            printf("トロッコは猛スピードで分岐に差し掛かろうとしている！\nポイントは左に切れているが、右にも変えられそうだ！\n");
 	        printf("行動を入力して下さい！\n\n"); 
        }
    }
    
    if (stg == 4)
    {
        printf("着いた先は行き止まりの小部屋だ。剣を刺す台座のようなものがある…");
        printf("行動を入力して下さい。\n\n"); 
    }
    

}

int  subcom   (int num,int type,int mode)//代入する値、代入先、書0/読1
{
    static int stage;
    static int torch;
    static int foward;
    static int right;
    static int left;
    static int sword;
    static int boat;
    static int button;
    if (mode == 0)
    {
        if (type == 0)
        {
            stage = 0; torch = 0; foward = 0; right = 0; left = 0; sword = 0; boat = 0; button = 0;
            return 0;
        }
        else if (type == 1)
        {
            stage = num;
            return 0;
        }
        else if (type == 2)
        { 
            torch = num;
            return 0;
        }
        else if (type == 3)
        { 
            foward = num;
            return 0;
        }
        else if (type == 4)
        { 
            right = num;
            return 0;
        }
        else if (type == 5)
        { 
            left = num;
            return 0;
        }
        else if (type == 6)
        { 
            sword = num;
            return 0;
        }
        else if (type == 7)
        { 
            boat = num;
            return 0;
        }
        else if (type == 8)
        { 
            button = num;
            return 0;
        }
    }
    if (mode == 1)
    {
        if(type == 1)
        {
            return stage;
        }
        else if (type == 2)
        { 
            return torch;
        }
        else if (type == 3)
        { 
            return foward;
        }
        else if (type == 4)
        { 
            return right;
        }
        else if (type == 5)
        { 
            return left;
        }
        else if (type == 6)
        { 
            return sword;
        }
        else if (type == 7)
        { 
            return boat;
        }
        else if (type == 8)
        { 
            return button;
        }
    }
    return 0;
}

int  s_com    (int *comsuch_s,int combreak)
{
     struct lib s_comlib[500] =
    { 
        {   1,"進む"},
        {   2,"歩く"},
        { 101,"見る"},
        { 102,"みる"},
        { 103,"見回す"},
        { 104,"見渡す"},
        { 201,"前"},
        { 202,"後"},
        { 203,"右"},
        { 204,"左"},
        { 399,"マッチ"},
        { 302,"松明"},
        { 303,"たいまつ"},
        { 401,"使う"},
        { 402,"つかう"},
        { 500,"擦る"},
        { 601,"剣"},
        { 602,"つるぎ"},
        { 701,"自分"},
        { 702,"自分を"},
        { 703,"自分に"},
        { 801,"拾う"},
        { 802,"ひろう"},
        { 901,"火"},
        {1001,"手"},
        {1002,"掴む"},
        {1003,"つかむ"},
        {1101,"ボタン"},
        {1201,"押す"},
        {1202,"蹴る"},
        {1203,"おす"},
        {1301,"トロッコ"},
        {1401,"ボート"},
        {1501,"乗る"},
        {1502,"乗り込む"},
        {1503,"入る"},
        {1601,"火をつける"},
        {1602,"火を着ける"},
        {1603,"着火"},
    };
    int si = 0;
    int sids = 0;
    static int combr_on = 0;
    while (1)
        {
            if (si == 599)
            {
                sids = 7000;
                break;
            }
            else if(strcmp(s_comlib[si].txt,moji)==0)
            {
                sids = s_comlib[si].id;
                break;
            }
		    else{si++;}
        }
    if (combreak == 1)
    {
        if (combr_on == 1)
        {
            combr_on = 0;
            return 1;
        }
        else if (combr_on == 0)
        {
            combr_on = 0;
            return 0;
        }
    }
    if (sids == 1 || sids == 2)
    {
        printf("どっちへ？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[6].txt))
        {
            Move(20101);//前
            *comsuch_s = 201;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[7].txt))
        {
            Move(20401);//後ろ
            *comsuch_s = 204;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[8].txt))
        {
            Move(20201);//右
            *comsuch_s = 202;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[9].txt))
        {
            Move(20301);//左
            *comsuch_s = 203;
            combr_on = 1;
        }
    }
    else if (sids >= 100 && sids < 199)
    {
        printf("どっちへ？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[6].txt))
        {
            Move(20101);//前
            *comsuch_s = 201;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[7].txt))
        {
            Move(20401);//後ろ
            *comsuch_s = 204;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[8].txt))
        {
            Move(20201);//右
            *comsuch_s = 202;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[9].txt))
        {
            Move(20301);//左
            *comsuch_s = 203;
            combr_on = 1;
        }
    }
    else if (sids >= 300 && sids < 398)
    {
        printf("松明をどうする？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[23].txt))//火をつける
        {
            Use(50101);
            *comsuch_s = 501;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[21].txt))//拾う
        {
            Pick(30101);
            *comsuch_s = 301;
            combr_on = 1;
        }
    }
    else if (sids == 399)
    {
        printf("マッチをどうする？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[23].txt) || strstr(moji,s_comlib[15].txt))//火をつける
        {
            Use(50201);
            *comsuch_s = 502;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[18].txt))//自分
        {
            Die(660101);
            *comsuch_s = 6601;
            combr_on = 1;
        }
    }
    else if (sids >= 400 && sids < 499)
    {
        printf("何を使う？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[10].txt))//マッチ
        {
            Use(50213);
            *comsuch_s = 502;combr_on = 1;
        }
        else if (strstr(moji,s_comlib[12].txt) || strstr(moji,s_comlib[11].txt))//たいまつ
        {
            Use(50301);
            *comsuch_s = 503;
            combr_on = 1;
        }
    }
    
    else if (sids >= 600 && sids < 699)
    {
        printf("剣をどうする？");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[21].txt) || strstr(moji,s_comlib[22].txt) || strstr(moji,s_comlib[23].txt) || strstr(moji,s_comlib[24].txt) 
            || strstr(moji,s_comlib[25].txt) || strstr(moji,s_comlib[26].txt) || strstr(moji,s_comlib[27].txt))
        {
            Pick(30201);
            *comsuch_s = 302;
            combr_on = 1;
        }
    }
    else if (sids >= 800 && sids < 899)
    {

        printf("なにを？");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[10].txt))//マッチ
            {
                printf("マッチなら既に持っている。");
            }
        else if (strstr(moji,s_comlib[12].txt) || strstr(moji,s_comlib[11].txt))//たいまつ
        {
            Pick(30101);
            *comsuch_s = 301;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[16].txt) || strstr(moji,s_comlib[17].txt))//剣
        {
            Pick(30201);
            *comsuch_s = 302;
            combr_on = 1;
        }
    }
    else if (sids >= 1100 && sids < 1199 )
    {
        printf("ボタンをどうする？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[28].txt) || strstr(moji,s_comlib[29].txt) || strstr(moji,s_comlib[30].txt))//マッチ
        {
            Touch(40301);
            *comsuch_s = 402;
            combr_on = 1;
        }
    }
    else if (sids >= 1200 && sids < 1299 )
    {
        printf("なにを？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[27].txt))//ボタン
        {
            Touch(40301);
            *comsuch_s = 402;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[31].txt))
        {
            printf("トロッコは重く、動かない");
            combr_on = 1;
        }
    }
    else if (sids >= 1300 && sids < 1399 )
    {
        printf("トロッコをどうする？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[33].txt) || strstr(moji,s_comlib[34].txt) || strstr(moji,s_comlib[35].txt))//ボタン
        {
            Ride(60201);
            *comsuch_s = 602;
            combr_on = 1;
        }
    }
    else if (sids >= 1400 && sids < 1499 )
    {
        printf("ボートをどうする？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[33].txt) || strstr(moji,s_comlib[34].txt) || strstr(moji,s_comlib[35].txt))//ボタン
        {
            Ride(60101);
            *comsuch_s = 601;
            combr_on = 1;
        }
    }
    else if (sids >= 1500 && sids < 1599 )
    {
        printf("何に？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[31].txt))//トロッコ
        {
            Ride(60201);
            *comsuch_s = 602;
            combr_on = 1;
        }
        else if ( strstr(moji,s_comlib[32].txt))//船
        {
            Ride(60101);
            *comsuch_s = 601;
            combr_on = 1;
        }
    }
    else if (sids >= 1600 && sids < 1699 )
    {
        printf("何に火を着ける？\n\n");
        scanf("%s", moji);
        if (strstr(moji,s_comlib[11].txt) || strstr(moji,s_comlib[12].txt))//松明に
        {
            Use(50201);
            *comsuch_s = 502;
            combr_on = 1;
        }
        else if (strstr(moji,s_comlib[18].txt))//自分
        {
            Die(660101);
            *comsuch_s = 6601;
            combr_on = 1;
        }
    }
    else
    {
        combr_on =0;
    }
    return 0;
}

void com      (int *comsuch_c)
{
    int stg   = subcom(0,1,1);
    int torch = subcom(0,2,1);
    int fowd  = subcom(0,3,1);
    int right = subcom(0,4,1);
    int left  = subcom(0,5,1);
    int sword = subcom(0,6,1);
    int boat  = subcom(0,7,1);
    int button = subcom(0,8,1);

    int comback[90001];
    for (int i = 0; i < 90000; i++ ) {comback[i] = i;}
    struct lib comlib[700] =
    { 
        //===Lib look ここから====================================
        { 10101,"辺りを見回す"},
        { 10102,"辺りを見渡す"},
        { 10103,"辺りを見る"},
        { 10104,"あたりを見回す"},
        { 10105,"あたりを見渡す"},
        { 10106,"あたりを見る"},
        { 10107,"周りを見る"},
        { 10108,"周りを見渡す"},
        { 10109,"まわりを見る"},
        { 10110,"周辺を見る"},
        { 10111,"周辺を見渡す"},
        { 10112,"周辺を見回す"},
        { 10113,"周囲を見る"},
        { 10114,"周囲を見渡す"},
        { 10115,"周囲を見回す"},
        { 10116,"辺りを調べる"},
        { 10117,"あたりを調べる"},
        { 10118,"周りを調べる"},
        { 10119,"まわりを調べる"},
        { 10120,"周辺を調べる"},
        { 10101,"右を見回す"},
        { 10102,"右を見渡す"},
        { 10103,"右を見る"},
        { 10104,"左を見回す"},
        { 10105,"左を見渡す"},
        { 10106,"左を見る"},
        { 10104,"正面を見回す"},
        { 10105,"正面を見渡す"},
        { 10106,"正面を見る"},
        //---周囲を見回す　ここまで----------------------------------
        { 10201,"剣を見る"},
        { 10202,"落ちている剣を見る"},
        { 10203,"剣のことを見る"},
        { 10204,"剣を調べる"},
        { 10205,"剣のことを調べる"},
        { 10206,"落ちている剣を調べる"},
        { 10207,"落ちている剣のことを調べる"},
        { 10208,"落ちている剣のことを見る"},
        { 10209,"持っている剣を調べる"},
        { 10210,"持っている剣のことを調べる"},
        { 10211,"持っている剣のことを見る"},
        //---剣を調べる　ここまで-------------------------------------
        { 10301,"壁を見る"},
        { 10302,"かべのことを見る"},
        { 10303,"壁面を見る"},
        { 10304,"壁を調べる"},
        { 10305,"かべを調べる"},
        { 10306,"壁面を調べる"},
        { 10307,"洞窟の壁のことを調べる"},
        { 10308,"洞窟の壁のことを見る"},
        { 10307,"洞窟の壁を調べる"},
        { 10308,"洞窟の壁を見る"},
        //---壁を見る　ここまで----------------------------------------
        { 10401,"天井を見る"},
        { 10402,"天井のことを見る"},
        { 10403,"天井を見る"},
        { 10404,"天井を調べる"},
        { 10405,"てんじょうを調べる"},
        { 10406,"天井面を調べる"},
        { 10407,"洞窟の天井のことを調べる"},
        { 10408,"洞窟の天井のことを見る"},
        { 10407,"洞窟の天井を調べる"},
        { 10408,"洞窟の天井を見る"},
        //---天井をみる　ここまで-----------------------------------------
        { 10501,"緑のものを見る"},
        { 10052,"緑のものを調べる"},
        { 10503,"緑色を調べる"},
        { 10504,"緑色を見る"},
        { 10505,"緑を調べる"},
        { 10506,"緑を見る"},
        { 10507,"緑色の物体を調べる"},
        { 10508,"緑色の物体を見る"},
        { 10507,"緑色の物体のことを調べる"},
        { 10508,"緑色の物体のことを見る"},
        //-----緑を見る　ここまで-------------------------------------------
        { 10601,"ボタンを見る"},
        { 10602,"ボタンを調べる"},
        { 10603,"光るボタンを見る"},
        { 10604,"光るボタンを調べる"},
        { 10605,"変なボタンを見る"},
        { 10606,"変なボタンを調べる"},
        { 10607,"ボタンをみる"},
        { 10608,"ボタンをしらべる"},
        { 10609,"光るボタンをみる"},
        { 10610,"光るボタンをしらべる"},
        { 10611,"変なボタンをみる"},
        { 10612,"変なボタンをしらべる"},
        { 10601,"壁のボタンを見る"},
        { 10602,"壁のボタンを調べる"},
        { 10601,"壁の光るボタンを見る"},
        { 10602,"壁の光るボタンを調べる"},
        { 10601,"壁の変なボタンを見る"},
        { 10602,"壁の変なボタンを調べる"},
        //--------ボタン ここまで--------------------------------------------
        { 10701,"ドアを見る"},
        { 10702,"ドアを調べる"},
        { 10703,"壁のドアを見る"},
        { 10704,"壁のドアを調べる"},
        //--------ドア　ここまで---------------------------------------------
        { 10801,"台座を調べる"},
        { 10802,"剣の台座を調べる"},
        { 10803,"台座のことを調べる"},
        { 10804,"剣の台座のことを調べる"},
        { 10805,"台座を見る"},
        { 10806,"剣の台座を見る"},
        { 10807,"台座のことを見る"},
        { 10808,"剣の台座のことを見る"},
        //============look ここまで================================
        //============move ここから================================
        { 20101,"前に進む"},
        { 20102,"前へ進む"},
        { 20103,"前へと進む"},
        { 20104,"前方に進む"},
        { 20105,"前方へ進む"},
        { 20106,"前方へと進む"},
        { 20107,"前に歩く"},
        { 20108,"前へ歩く"},
        { 20109,"前へと歩く"},
        { 20110,"前へ行く"},
        { 20111,"前に行く"},
        { 20112,"前にいく"},
        { 20113,"前へいく"},
        { 20114,"前へ"},
        { 20115,"前進する"},
        { 20101,"正面に進む"},
        { 20102,"正面へ進む"},
        { 20103,"正面へと進む"},
        { 20104,"正面方に進む"},
        { 20105,"正面方へ進む"},
        { 20106,"正面方へと進む"},
        { 20107,"正面に歩く"},
        { 20108,"正面へ歩く"},
        { 20109,"正面へと歩く"},
        { 20110,"正面へ行く"},
        { 20111,"正面に行く"},
        { 20112,"正面にいく"},
        { 20113,"正面へいく"},
        { 20114,"正面へ"},
        { 20116,"正面の穴へ進む"},
        { 20117,"正面の穴に進む"},
        { 20118,"正面の穴へと進む"},
        { 20119,"正面の穴のほうへ進む"},
        { 20120,"正面の穴のほうに進む"},
        { 20121,"正面の穴のほうへと進む"},
        { 20122,"正面の穴の方へ進む"},
        { 20123,"正面の穴の方に進む"},
        { 20124,"正面の穴の方へと進む"},
        { 20116,"正面の穴へ歩く"},
        { 20117,"正面の穴に歩く"},
        { 20118,"正面の穴へと歩く"},
        { 20119,"正面の穴のほうへ歩く"},
        { 20120,"正面の穴のほうに歩く"},
        { 20121,"正面の穴のほうへと歩く"},
        { 20122,"正面の穴の方へ歩く"},
        { 20123,"正面の穴の方に歩く"},
        { 20124,"正面の穴の方へと歩く"},
        { 20125,"正面の穴へいく"},
        { 20126,"正面の穴にいく"},
        { 20127,"正面の穴へ行く"},
        { 20128,"正面の穴へ行く"},
        { 20129,"正面の穴"},
        { 20130,"正面の穴へ"},
        { 20116,"前の穴へ進む"},
        { 20117,"前の穴に進む"},
        { 20118,"前の穴へと進む"},
        { 20119,"前の穴のほうへ進む"},
        { 20120,"前の穴のほうに進む"},
        { 20121,"前の穴のほうへと進む"},
        { 20122,"前の穴の方へ進む"},
        { 20123,"前の穴の方に進む"},
        { 20124,"前の穴の方へと進む"},
        { 20116,"前の穴へ歩く"},
        { 20117,"前の穴に歩く"},
        { 20118,"前の穴へと歩く"},
        { 20119,"前の穴のほうへ歩く"},
        { 20120,"前の穴のほうに歩く"},
        { 20121,"前の穴のほうへと歩く"},
        { 20122,"前の穴の方へ歩く"},
        { 20123,"前の穴の方に歩く"},
        { 20124,"前の穴の方へと歩く"},
        { 20125,"前の穴へいく"},
        { 20126,"前の穴にいく"},
        { 20127,"前の穴へ行く"},
        { 20128,"前の穴へ行く"},
        { 20129,"前の穴"},
        { 20130,"前の穴へ"},
        //---------------前進 ここまで-----------------------------------
        { 20201,"右に進む"},
        { 20202,"右へ進む"},
        { 20203,"右へと進む"},
        { 20204,"右方に進む"},
        { 20205,"右方へ進む"},
        { 20206,"右方へと進む"},
        { 20207,"右前方に進む"},
        { 20208,"右前方へ進む"},
        { 20209,"右前方へと進む"},
        { 20210,"右に歩く"},
        { 20211,"右へ歩く"},
        { 20212,"右へと歩く"},
        { 20213,"右へ行く"},
        { 20214,"右に行く"},
        { 20215,"右にいく"},
        { 20216,"右へいく"},
        { 20217,"右の穴へ進む"},
        { 20218,"右の穴に進む"},
        { 20219,"右の穴へと進む"},
        { 20220,"右の穴のほうへ進む"},
        { 20221,"右の穴のほうに進む"},
        { 20222,"右の穴のほうへと進む"},
        { 20223,"右の穴の方へ進む"},
        { 20224,"右の穴の方に進む"},
        { 20225,"右の穴の方へと進む"},
        { 20217,"右の穴へ歩く"},
        { 20218,"右の穴に歩く"},
        { 20219,"右の穴へと歩く"},
        { 20220,"右の穴のほうへ歩く"},
        { 20221,"右の穴のほうに歩く"},
        { 20222,"右の穴のほうへと歩く"},
        { 20223,"右の穴の方へ歩く"},
        { 20224,"右の穴の方に歩く"},
        { 20225,"右の穴の方へと歩く"},
        { 20226,"右の穴へいく"},
        { 20227,"右の穴にいく"},
        { 20228,"右の穴へ行く"},
        { 20229,"右の穴へ行く"},
        { 20230,"右の穴"},
        { 20231,"右の穴へ"},
        //----------------右  ここまで-----------------------------------
        { 20301,"左に進む"},
        { 20302,"左へ進む"},
        { 20303,"左へと進む"},
        { 20304,"左方に進む"},
        { 20305,"左方へ進む"},
        { 20306,"左方へと進む"},
        { 20307,"左前方に進む"},
        { 20308,"左前方へ進む"},
        { 20309,"左前方へと進む"},
        { 20310,"左に歩く"},
        { 20311,"左へ歩く"},
        { 20312,"左へと歩く"},
        { 20313,"左へ行く"},
        { 20314,"左に行く"},
        { 20315,"左にいく"},
        { 20316,"左へいく"},
        { 20317,"左の穴へ進む"},
        { 20318,"左の穴に進む"},
        { 20319,"左の穴へと進む"},
        { 20320,"左の穴のほうへ進む"},
        { 20321,"左の穴のほうに進む"},
        { 20322,"左の穴のほうへと進む"},
        { 20323,"左の穴の方へ進む"},
        { 20324,"左の穴の方に進む"},
        { 20325,"左の穴の方へと進む"},
        { 20317,"左の穴へ歩く"},
        { 20318,"左の穴に歩く"},
        { 20319,"左の穴へと歩く"},
        { 20320,"左の穴のほうへ歩く"},
        { 20321,"左の穴のほうに歩く"},
        { 20322,"左の穴のほうへと歩く"},
        { 20323,"左の穴の方へ歩く"},
        { 20324,"左の穴の方に歩く"},
        { 20325,"左の穴の方へと歩く"},
        { 20326,"左の穴へいく"},
        { 20327,"左の穴にいく"},
        { 20328,"左の穴へ行く"},
        { 20329,"左の穴へ行く"},
        { 20330,"左の穴"},
        { 20331,"左の穴へ"},
        { 20332,"左の通路へ"},
        { 20333,"左の脇道へ"},
        //------------------左  ここまで---------------------------------------
        { 20401,"後ろへ進む"},
        { 20402,"戻る"},
        { 20403,"後ろへ進む"},
        { 20404,"一つ戻る"},
        { 20405,"分岐に戻る"},
        { 20406,"後ろに歩く"},
        { 20407,"ムーンウォークする"},
        { 20408,"後ろへ"},
        { 20409,"後方へ進む"},
        { 20401,"後ろに進む"},
        { 20402,"後方に進む"},
        { 20403,"後ろに歩く"},
        { 20404,"後方に歩く"},
        //--------------------------
        { 20501,"ドアへ進む"},
        { 20502,"ドアを開ける"},
        { 20503,"ドアのほうに行く"},
        { 20504,"ドアの方に行く"},
        { 20505,"ファストパスへ"},
        { 20506,"案内の方へ"},
        { 20507,"前のドアへ"},
        //==================Pick ここから======================================
        { 30101,"松明を拾う"},
        { 30102,"松明を取る"},
        { 30103,"松明をてに取る"},
        { 30104,"松明を手に取る"},
        { 30105,"たいまつを取る"},
        { 30106,"たいまつを拾う"},
        { 30107,"たいまつをてに取る"},
        { 30108,"たいまつを手に取る"},
        { 30109,"たいまつをひろう"},
        { 30110,"たいまつをとる"},
        { 30111,"たいまつをてにとる"},
        { 30112,"たいまつを手にとる"},
        //------------------松明　ここまで-------------------------------------------
        { 30201,"剣を拾う"},
        { 30202,"剣を取る"},
        { 30203,"剣を手に取る"},
        { 30204,"剣をひろう"},
        { 30205,"剣をとる"},
        { 30206,"剣をてにとる"},
        { 30207,"剣を手にとる"},
        { 30208,"剣をてに取る"},
        { 30209,"けんを手に取る"},
        { 30210,"けんを拾う"},
        { 30211,"けんを取る"},
        { 30212,"けんを手に取る"},
        { 30213,"けんをひろう"},
        { 30214,"けんをとる"},
        { 30215,"けんをてにとる"},
        { 30216,"けんを手にとる"},
        { 30217,"けんをてに取る"},
        { 30218,"けんを手に取る"},
        { 30219,"つるぎを拾う"},
        { 30220,"つるぎを取る"},
        { 30221,"つるぎを手に取る"},
        { 30222,"つるぎをひろう"},
        { 30223,"つるぎをとる"},
        { 30224,"つるぎをてにとる"},
        { 30225,"つるぎを手にとる"},
        { 30226,"つるぎをてに取る"},
        //================pick ここまで======================
        //================touch ここから=====================
        { 40101,"壁に触る"},
        { 40102,"壁にさわる"},
        { 40103,"壁に触れる"},
        { 40104,"壁にふれる"},
        { 40105,"かべに触る"},
        { 40106,"かべにさわる"},
        { 40107,"かべに触れる"},
        { 40108,"かべにふれる"},
        { 40109,"壁を触る"},
        { 40110,"壁をさわる"},
        { 40111,"壁を触れる"},
        { 40112,"壁をふれる"},
        { 40113,"かべを触る"},
        { 40114,"かべをさわる"},
        { 40115,"かべを触れる"},
        { 40116,"かべをふれる"},
        { 40117,"壁面に触る"},
        { 40118,"壁面にさわる"},
        { 40119,"壁面に触れる"},
        { 40120,"壁面にふれる"},
        { 40121,"へきめんに触る"},
        { 40122,"へきめんにさわる"},
        { 40123,"へきめんに触れる"},
        { 40124,"へきめんにふれる"},
        { 40125,"壁面を触る"},
        { 40126,"壁面をさわる"},
        { 40127,"壁面を触れる"},
        { 40128,"壁面をふれる"},
        { 40129,"へきめんを触る"},
        { 40130,"へきめんをさわる"},
        { 40131,"へきめんを触れる"},
        { 40132,"へきめんをふれる"},
        { 40133,"洞窟の壁に触る"},
        { 40134,"洞窟の壁にさわる"},
        { 40135,"洞窟の壁に触れる"},
        { 40136,"洞窟の壁にふれる"},
        { 40137,"どうくつのかべに触る"},
        { 40138,"どうくつのかべにさわる"},
        { 40139,"どうくつのかべに触れる"},
        { 40140,"どうくつのかべにふれる"},
        { 40141,"洞窟のかべに触る"},
        { 40142,"洞窟のかべにさわる"},
        { 40143,"洞窟のかべに触れる"},
        { 40144,"洞窟のかべにふれる"},
        { 40145,"洞窟の壁を触る"},
        { 40146,"洞窟の壁をさわる"},
        { 40147,"洞窟の壁を触れる"},
        { 40148,"洞窟の壁をふれる"},
        { 40149,"どうくつの壁を触る"},
        { 40150,"どうくつの壁をさわる"},
        { 40151,"どうくつの壁を触れる"},
        { 40152,"どうくつの壁をふれる"},
        { 40153,"洞窟の壁面に触る"},
        { 40154,"洞窟の壁面にさわる"},
        { 40155,"洞窟の壁面に触れる"},
        { 40156,"洞窟の壁面にふれる"},
        { 40157,"洞窟のへきめんに触る"},
        { 40158,"洞窟のへきめんにさわる"},
        { 40159,"洞窟のへきめんに触れる"},
        { 40160,"洞窟のへきめんにふれる"},
        { 40161,"洞窟の壁面を触る"},
        { 40162,"洞窟の壁面をさわる"},
        { 40163,"洞窟の壁面を触れる"},
        { 40164,"洞窟の壁面をふれる"},
        { 40165,"どうくつの壁面を触る"},
        { 40166,"どうくつの壁面をさわる"},
        { 40167,"どうくつの壁面を触れる"},
        { 40168,"どうくつの壁面をふれる"},
        //--------------------------壁 ここまで-------------------------------------------------
        { 40201,"天井に触る"},
        { 40202,"天井にさわる"},
        { 40203,"天井に触れる"},
        { 40204,"天井にふれる"},
        { 40205,"てんじょうに触る"},
        { 40206,"てんじょうにさわる"},
        { 40207,"てんじょうに触れる"},
        { 40208,"てんじょうにふれる"},
        { 40209,"天井を触る"},
        { 40210,"天井をさわる"},
        { 40211,"天井を触れる"},
        { 40212,"天井をふれる"},
        { 40213,"てんじょうを触る"},
        { 40214,"てんじょうをさわる"},
        { 40215,"てんじょうを触れる"},
        { 40216,"てんじょうをふれる"},
        { 40217,"天井面に触る"},
        { 40218,"天井面にさわる"},
        { 40219,"天井面に触れる"},
        { 40220,"天井面にふれる"},
        { 40221,"てんじょうめんに触る"},
        { 40222,"てんじょうめんにさわる"},
        { 40223,"てんじょうめんに触れる"},
        { 40224,"てんじょうめんにふれる"},
        { 40225,"天井面を触る"},
        { 40226,"天井面をさわる"},
        { 40227,"天井面を触れる"},
        { 40228,"天井面をふれる"},
        { 40229,"てんじょうめんを触る"},
        { 40230,"てんじょうめんをさわる"},
        { 40231,"てんじょうめんを触れる"},
        { 40232,"てんじょうめんをふれる"},
        { 40233,"洞窟の天井に触る"},
        { 40234,"洞窟の天井にさわる"},
        { 40235,"洞窟の天井に触れる"},
        { 40236,"洞窟の天井にふれる"},
        { 40237,"どうくつのてんじょうに触る"},
        { 40238,"どうくつのてんじょうにさわる"},
        { 40239,"どうくつのてんじょうに触れる"},
        { 40240,"どうくつのてんじょうにふれる"},
        { 40241,"洞窟のてんじょうに触る"},
        { 40242,"洞窟のてんじょうにさわる"},
        { 40243,"洞窟のてんじょうに触れる"},
        { 40244,"洞窟のてんじょうにふれる"},
        { 40245,"洞窟の天井を触る"},
        { 40246,"洞窟の天井をさわる"},
        { 40247,"洞窟の天井を触れる"},
        { 40248,"洞窟の天井をふれる"},
        { 40249,"どうくつの天井を触る"},
        { 40250,"どうくつの天井をさわる"},
        { 40251,"どうくつの天井を触れる"},
        { 40252,"どうくつの天井をふれる"},
        { 40253,"洞窟の天井面に触る"},
        { 40254,"洞窟の天井面にさわる"},
        { 40255,"洞窟の天井面に触れる"},
        { 40256,"洞窟の天井面にふれる"},
        { 40257,"洞窟のてんじょうめんに触る"},
        { 40258,"洞窟のてんじょうめんにさわる"},
        { 40259,"洞窟のてんじょうめんに触れる"},
        { 40260,"洞窟のてんじょうめんにふれる"},
        { 40261,"洞窟の天井面を触る"},
        { 40262,"洞窟の天井面をさわる"},
        { 40263,"洞窟の天井面を触れる"},
        { 40264,"洞窟の天井面をふれる"},
        { 40265,"どうくつの天井面を触る"},
        { 40266,"どうくつの天井面をさわる"},
        { 40267,"どうくつの天井面を触れる"},
        { 40268,"どうくつの天井面をふれる"}, 
        //------------天井　ここまで---------------------------------------------------------
        { 40301,"ボタンを押す"},
        { 40302,"ボタンをおす"},
        { 40303,"ボタンを蹴る"},
        { 40304,"ボタンをける"},
        { 40305,"ボタンに触る"},
        { 40306,"ボタンにさわる"},
        { 40307,"ボタンに触れる"},
        { 40308,"ボタンにふれる"},
        { 40309,"ボタンを触る"},
        { 40310,"ボタンをさわる"},
        //------------ボタン ここまで--------------------------------------------------------
        { 40401,"緑のものに触れる"},
        { 40402,"緑のものに触る"},
        { 40403,"緑のものにふれる"},
        { 40404,"緑のものにさわる"},
        { 40405,"緑の物体に触れる"},
        { 40406,"緑の物体に触る"},
        { 40407,"緑の物体にふれる"},
        { 40408,"緑の物体にさわる"},
        { 40409,"緑の物体を食べる"},
        { 40410,"緑のものを食べる"},
        { 40411,"天井の緑のものに触れる"},
        { 40412,"天井の緑のものに触る"},
        { 40413,"天井の緑のものにふれる"},
        { 40414,"天井の緑のものにさわる"},
        { 40415,"天井の緑の物体に触れる"},
        { 40416,"天井の緑の物体に触る"},
        { 40417,"天井の緑の物体にふれる"},
        { 40418,"天井の緑の物体にさわる"},
        { 40419,"天井の緑の物体を食べる"},
        { 40420,"天井の緑のものを食べる"},
        { 40421,"緑色のものに触れる"},
        { 40422,"緑色のものに触る"},
        { 40423,"緑色のものにふれる"},
        { 40424,"緑色のものにさわる"},
        { 40425,"緑色の物体に触れる"},
        { 40426,"緑色の物体に触る"},
        { 40427,"緑色の物体にふれる"},
        { 40428,"緑色の物体にさわる"},
        { 40429,"緑色の物体を食べる"},
        { 40420,"緑色のものを食べる"},
        { 40431,"天井の緑色のものに触れる"},
        { 40432,"天井の緑色のものに触る"},
        { 40433,"天井の緑色のものにふれる"},
        { 40434,"天井の緑色のものにさわる"},
        { 40435,"天井の緑色の物体に触れる"},
        { 40436,"天井の緑色の物体に触る"},
        { 40437,"天井の緑色の物体にふれる"},
        { 40438,"天井の緑色の物体にさわる"},
        { 40439,"天井の緑色の物体を食べる"},
        { 40440,"天井の緑色のものを食べる"},
        //=========================touch ここまで============================================
        //=========================Use   ここから============================================
        { 50101,"松明に火をつける"},
        { 50102,"松明に火を着ける"},
        { 50103,"松明にひをつける"},
        { 50104,"松明にひを着ける"},
        { 50105,"たいまつに火をつける"},
        { 50106,"たいまつに火を着ける"},
        { 50107,"たいまつにひをつける"},
        { 50108,"たいまつにひを着ける"},
        { 50109,"松明にマッチを使う"},
        { 50110,"松明にマッチをつかう"},
        { 50111,"松明にマッチを使って火を着ける"},
        { 50112,"松明にマッチを使って火をつける"},
        { 50113,"松明にマッチをつかって火をつける"},
        { 50114,"松明にマッチをつかって火を着ける"},
        { 50115,"松明にマッチを使ってひを着ける"},
        { 50116,"松明にマッチを使ってひをつける"},
        { 50117,"松明にマッチをつかってひをつける"},
        { 50118,"松明にマッチをつかってひを着ける"},
        { 50119,"たいまつにマッチを使う"},
        { 50120,"たいまつにマッチをつかう"},
        { 50121,"たいまつにマッチを使って火を着ける"},
        { 50122,"たいまつにマッチを使って火をつける"},
        { 50123,"たいまつにマッチをつかって火をつける"},
        { 50124,"たいまつにマッチをつかって火を着ける"},  
        { 50125,"たいまつにマッチを使ってひを着ける"},
        { 50126,"たいまつにマッチを使ってひをつける"},
        { 50127,"たいまつにマッチをつかってひをつける"},
        { 50128,"たいまつにマッチをつかってひを着ける"},
        //--------------------------松明 ここまで------------------------------------
        { 50201,"マッチに火を着ける"}, 
        { 50202,"マッチに火をつける"},
        { 50203,"マッチにひを着ける"},
        { 50204,"マッチで火を着ける"},
        { 50205,"マッチで火をつける"},
        { 50206,"マッチでひを着ける"},
        { 50207,"マッチを使って火を着ける"},
        { 50208,"マッチを使って火をつける"},
        { 50209,"マッチを使ってひを着ける"},
        { 50210,"マッチで着火する"},
        { 50211,"マッチに着火する"},
        { 50212,"マッチを使って着火する"},
        { 50213,"マッチをすって着火する"},
        { 50214,"マッチをすって火を着ける"},
        { 50215,"マッチをすって火をつける"},
        { 50216,"マッチをすってひを着ける"},
        { 50217,"マッチを擦って着火する"},
        { 50218,"マッチを擦って火を着ける"},
        { 50219,"マッチを擦って火をつける"},
        { 50220,"マッチを擦ってひを着ける"},
        { 50221,"マッチをする"},
        { 50222,"マッチを擦る"},
        { 50223,"マッチを使う"},
        { 50224,"マッチをつかう"},
        //-----------------------------マッチ　ここまで-------------------------------------------
        { 50301,"たいまつを使う"},  
        { 50302,"松明を使う"},
        { 50303,"松明をつかう"},
        { 50304,"たいまつをつかう"},
        { 50305,"たいまつを振る"},  
        { 50306,"松明を振る"},
        { 50307,"松明をふる"},
        { 50308,"たいまつをふる"},
        { 50309,"たいまつを振るう"},  
        { 50310,"松明を振るう"},
        { 50311,"松明をふるう"},
        { 50312,"たいまつをふるう"},
        { 50313,"たいまつを押し当てる"},  
        { 50314,"松明を押し当てる"},
        { 50315,"松明を押しあてる"},
        { 50316,"たいまつを押しあてる"},
        //------------------------------松明を使う　ここまで
        { 50401,"剣を使う"}, 
        { 50402,"剣をはめる"},
        { 50403,"剣を嵌める"},
        { 50404,"剣を入れる"},
        { 50405,"剣をいれる"},
        { 50406,"剣を刺す"},
        { 50407,"剣を刺しこむ"}, 
        { 50408,"剣を刺し込む"},
        { 50409,"剣を差し込む"},
        { 50410,"剣を差す"},
        { 50411,"剣を突っ込む"},
        { 50412,"剣をぶっさす"},
        { 50413,"台座に剣を使う"}, 
        { 50414,"台座に剣をはめる"},
        { 50415,"台座に剣を嵌める"},
        { 50416,"台座に剣を入れる"},
        { 50417,"台座に剣をいれる"},
        { 50418,"台座に剣を刺す"},
        { 50419,"台座に剣を刺しこむ"}, 
        { 50420,"台座に剣を刺し込む"},
        { 50421,"台座に剣を差し込む"},
        { 50422,"台座に剣を差す"},
        { 50423,"台座に剣を突っ込む"},
        { 50424,"台座に剣をぶっさす"},
        //============================Use ここまで================================================
        //===========================Ride ここから================================================
        { 60101,"船に乗る"},  
        { 60102,"船に乗り込む"},
        { 60103,"ボートに乗る"},
        { 60104,"ボートに乗り込む"},
        { 60105,"乗船する"},  
        { 60106,"ボートの中に入る"},
        { 60107,"ボートへ"},
        //-------------ボート　ここまで----------------------------------------------------------
        { 60201,"トロッコに乗る"},  
        { 60202,"トロッコに乗り込む"},
        { 60203,"トロッコの中に入る"},
        { 60204,"トロッコを動かす"},
        { 60205,"トロッコへ入る"},  
        { 60206,"トロッコへ乗る"},
        { 60207,"トロッコへ乗り込む"},
        //===========================Ride ここまで================================================
        //============================Die ここから================================================
        {660101,"自分に火を着ける"},           //if badcom(マッチ)後ならstrstr(自分)で6601
        {660102,"自分の服に火を着ける"},
        {660103,"自分に火を放つ"},
        {660104,"自分を燃やす"},
        {660105,"服に火を着ける"},
        //-----------------自己着火 ここまで------------------------------------------------------
        //6602 strstr(緑)で実行  if 右1-1なら天井で6602
        //6603 欠番 松明未着火時 move*5(baka==5)で実行
        {660501,"飛び降りる"},          
        {660502,"ボートから飛び降りる"},
        {660503,"トロッコから飛び降りる"},
        //============================Die ここまで=================================================
    	//============================B-C ここから=================================================
    	{990100,"進む"},
    	{990200,"歩く"},
    	{990300,"使う"},
        {990301,"擦る"},
    	{990501,"松明に使う"},
    	{990502,"たいまつに使う"},
    	{990700,"まつあき"},//strstr 自決コードに遷移
    	{990800,"まつみょう"},//同上
        {990900,"エンジンを止める"},
    	{999900,"すみません、よく分かりません"},//直接参照はせず、あくまで退避用として
        //=======B-C ここまで=============================================================================
    };
    int i = 0;
    int ids =0;
    char aho1[] = "まつあき";
    char aho2[] = "まつみょう";
    scanf("%s", moji);
    do
    {
    //判別処理(strstr)
        if (strstr(moji,aho1))
        {
            Die(669001);
        }
        else if (strstr(moji,aho2))
        {
            Badcom(669001);
        }
    //判別処理(strcmp)
        while (1)
        {
            if (i == 999)
            {
                ids = 7000;
                break;
            }
            else if(strcmp(comlib[i].txt,moji)==0)
            {
                ids = comlib[i].id;
                break;
            }
		    else{i++;}
        }
    //comsuchの生成
     
        *comsuch_c = (ids / 100);
    
    //二段階呼出
     s_com(comsuch_c,0);
            int br_such  = s_com(comsuch_c,1);
            if (br_such == 1)
            {
                break;
            }
    //呼出処理　
             if (ids >= 990000)                     {Badcom (ids);}
        else if (ids >= 660000 && ids < 669999)     {Die    (ids);}
        else if (ids >=  60000 && ids <  69999)     {Ride   (ids);}
        else if (ids >=  50000 && ids <  59999)     {Use    (ids);}
        else if (ids >=  40000 && ids <  49999)     {Touch  (ids);}
        else if (ids >=  30000 && ids <  39999)     {Pick   (ids);}
        else if (ids >=  20000 && ids <  29999)     {Move   (ids);}
        else if (ids >=  10000 && ids <  19999)     {Look   (ids);}
        else                                        {Badcom (999900);}
    }
    while (0); 
}