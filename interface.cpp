#include "interface.h"
#include "mywindows.h"

int interval;
void DrawGameFrame()
{
    gotoXY(GameFrame_X + GameFrame_Width - 7, GameFrame_Y - 2);
    color(11);
    printf("俄 罗 斯 方 块");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 13, GameFrame_Y + 7);
    color(3);
    printf("下一个方块：");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 3, GameFrame_Y + 7);
    color(2);
    printf("**********");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 3, GameFrame_Y + 13);
    color(2);
    printf("**********");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 3, GameFrame_Y + 14);
    color(14);
    printf("↑：旋转方块");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 3, GameFrame_Y + 16);
    printf("space：暂停/继续");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 3, GameFrame_Y + 18);
    printf("↓：立即下落");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 3, GameFrame_Y + 20);
    printf("R: 重新开始");

    gotoXY(GameFrame_X + 2 * GameFrame_Width + 3, GameFrame_Y + 22);
    printf("Esc ：退出");
    color(15);
    int i, j;
    for (i = 2; i < 2 * GameFrame_Width - 2; i += 2) {
        gotoXY(GameFrame_X + i, GameFrame_Y);
        printf("—");
    }

    for (i = 2; i < 2 * GameFrame_Width - 2; i += 2) {
        gotoXY(GameFrame_X + i, GameFrame_Y + GameFrame_Height);
        printf("—");
        //a[GameFrame_X + i][GameFrame_Y + GameFrame_Height] = 2;
    }

    for (i = 1; i < GameFrame_Height; i++) {
        gotoXY(GameFrame_X, GameFrame_Y + i);
        printf("|");
        //a[GameFrame_X][GameFrame_Y + i] = 2;
    }

    for (i = 1; i < GameFrame_Height; i++) {
        gotoXY(GameFrame_X + 2 * GameFrame_Width - 2, GameFrame_Y + i);
        printf("|");
        //a[GameFrame_X + 2 * GameFrame_Width - 2][GameFrame_Y + i] = 2;
    }
}
void printEND()
{   
    int n;
    system("cls");
    gotoXY(29, 7);
    printf("   \n");
    color(12);
    printf("\t\t\t■■■■   ■     ■   ■■     \n");
    printf("\t\t\t■         ■■   ■   ■  ■   \n");
    printf("\t\t\t■■■     ■  ■ ■   ■   ■  \n");
    printf("\t\t\t■         ■   ■■   ■  ■   \n");
    printf("\t\t\t■■■■   ■     ■   ■■     \n");
    gotoXY(30, 16);
    color(11);
    printf("1.再玩一次");
    gotoXY(30, 18);
    printf("2.查看排名并退出游戏\n");
    gotoXY(32, 20);
    printf("请选择1 2：");
    color(11);
    gotoXY(32, 22);
    showCursor();
    scanf("%d", &n);
    switch (n) {
    case 1:
        system("cls");
        welcome();
        break;
    case 2:
        intoFile();
        close();
    }

}
void close()
{
    exit(0);
}
void setting()
{
    int n;
    system("cls");
    printf("\n    1 简单\n");
    printf("    2 中等\n");
    printf("    3 困难\n");
    printf("    4 自定义\n");
    printf("    请选择难度：");
    scanf("%d", &n);
    switch (n) {
    case 1:
        interval = 500;
        break;
    case 2:
        interval = 300;
        break;
    case 3:
        interval = 200;
        break;
    case 4:
        printf("    以多大间隔下降一次(单位 ms):");
        scanf("%d", &interval);
        break;
    }
    printf("按任意键返回");
    hideCursor();
    _getch();
    showCursor();
    system("cls");
    welcome();
}
void music()
{
    int n;
    system("cls");
    printf("\n    1 开\n");
    printf("    2 关\n");
    printf("    请选择音乐开\\关：");
    scanf("%d", &n);
    switch (n) {
    case 1:
        open_music();
        break;
    case 2:
        close_music();
        break;
    }
    printf("按任意键返回");
    hideCursor();
    _getch();
    showCursor();
    system("cls");
    welcome();

}
void open_music() {
    //这里的music.mp3需要放在文件debug中
    
    mciSendString(L"open .\\Debug\\FC.MP3 alias bgm", NULL, 0, NULL);
    mciSendString(L"play bgm repeat", NULL, 0, NULL);
    mciSendString(L"setaudio bgm volume to 100", 0, 0, 0);
    
    //printf("sagfasdgasdgas");
}
void close_music()
{
    mciSendString(L"stop bgm", NULL, 0, NULL);
}
void regulation() {
    int i, j = 1;
    system("cls");
    color(13);
    gotoXY(34, 3);
    printf("游戏规则");
    color(2);
    for (i = 6; i <= 18; i++)   //输出上下边框===
    {
        for (j = 12; j <= 70; j++)  //输出左右边框||
        {
            gotoXY(j, i);
            if (i == 6 || i == 18) printf("—");
            else if (j == 12 || j == 69) printf("|");
        }
    }
    color(12);
    gotoXY(16, 7);
    printf("tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整");
    gotoXY(22, 9);
    printf("方块的位置和方向，使它们在屏幕底部拼出完整的");
    gotoXY(22, 11);
    printf("一行或几行");
    color(14);
    gotoXY(16, 13);
    printf("tip2: 每消除一行，积分增加100");
    color(11);
    gotoXY(16, 15);
    printf("tip3: 尽可能获得更多的积分");
    color(10);
    gotoXY(16, 17);
    printf("tip4: 提升等级会使方块下落速度加快，游戏难度加大");
    _getch();
    system("cls");
    welcome();
}

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void welcome()
{
    int n;
              
    if (1) {
        color(15);
        gotoXY(20, 5);
        printf("■■■■");
        color(9);
        gotoXY(20, 6);
        printf("■■");
        color(11);
        gotoXY(24, 6);
        printf("■■");
        color(9);
        gotoXY(22, 7);
        printf("■");
        color(11);
        gotoXY(24, 7);
        printf("■");
        color(9);
        gotoXY(22, 8);
        printf("■");
        color(11);
        gotoXY(24, 8);
        printf("■");
        color(15);
        gotoXY(22, 9);
        printf("■■");
        color(15);
        gotoXY(22, 10);
        printf("■■");
        //E
        color(14);
        gotoXY(31, 5);
        printf("■■■");
        color(14);
        gotoXY(31, 6);
        printf("■");
        color(15);
        gotoXY(33, 6);
        printf("■");
        color(15);
        gotoXY(31, 7);
        printf("■■■");
        color(15);
        gotoXY(31, 8);
        printf("■■");
        color(15);
        gotoXY(31, 9);
        printf("■");
        color(10);
        gotoXY(33, 9);
        printf("■");
        color(15);
        gotoXY(31, 10);
        printf("■");
        color(10);
        gotoXY(33, 10);
        printf("■■■");
        //T
        color(15);
        gotoXY(40, 5);
        printf("■■■■");
        color(5);
        gotoXY(40, 6);
        printf("■■");
        color(13);
        gotoXY(44, 6);
        printf("■■");
        color(5);
        gotoXY(42, 7);
        printf("■");
        color(13);
        gotoXY(44, 7);
        printf("■");
        color(5);
        gotoXY(42, 8);
        printf("■");
        color(13);
        gotoXY(44, 8);
        printf("■");
        color(15);
        gotoXY(42, 9);
        printf("■■");
        color(15);
        gotoXY(42, 10);
        printf("■■");
        //R
        color(2);
        gotoXY(52, 5);
        printf("■");
        color(1);
        gotoXY(54, 5);
        printf("■■■");

        color(2);
        gotoXY(52, 6);
        printf("■");
        color(1);
        gotoXY(58, 6);
        printf("■");

        color(1);
        gotoXY(52, 7);
        printf("■■");
        color(2);
        gotoXY(56, 7);
        printf("■■");

        color(1);
        gotoXY(52, 8);
        printf("■");
        color(2);
        gotoXY(54, 8);
        printf("■");

        color(1);
        gotoXY(52, 9);
        printf("■");
        color(2);
        gotoXY(56, 9);
        printf("■");

        color(1);
        gotoXY(52, 10);
        printf("■");
        color(2);
        gotoXY(58, 10);
        printf("■");
        //i
        color(15);
        gotoXY(64, 5);
        printf("■■");
        color(15);
        gotoXY(64, 6);
        printf("■■");

        color(13);
        gotoXY(64, 8);
        printf("■");
        color(11);
        gotoXY(66, 8);
        printf("■");
        color(13);
        gotoXY(64, 9);
        printf("■");
        color(11);
        gotoXY(66, 9);
        printf("■");
        color(13);
        gotoXY(64, 10);
        printf("■");
        color(11);
        gotoXY(66, 10);
        printf("■");
        //S
        color(5);
        gotoXY(74, 5);
        printf("■■■");
        color(15);
        gotoXY(72, 6);
        printf("■");
        color(5);
        gotoXY(74, 6);
        printf("■");
        color(15);
        gotoXY(72, 7);
        printf("■■■");
        color(15);
        gotoXY(72, 8);
        printf("■■■");
        color(5);
        gotoXY(74, 9);
        printf("■");
        color(15);
        gotoXY(76, 9);
        printf("■");
        color(5);
        gotoXY(70, 10);
        printf("■■■");

        color(12);
        gotoXY(45, 12);
        printf("WELCOME");

        //花
        gotoXY(84, 21);
        color(12);
        printf("(_)");  	//红花上边花瓣

        gotoXY(82, 22);
        printf("(_)");      //红花左边花瓣

        gotoXY(86, 22);
        printf("(_)");      //红花右边花瓣

        gotoXY(84, 23);
        printf("(_)");      //红花下边花瓣

        gotoXY(85, 22);      //红花花蕊
        color(6);
        printf("@");

        gotoXY(90, 20);
        color(13);
        printf("(_)");      //粉花左边花瓣

        gotoXY(94, 20);
        printf("(_)");      //粉花右边花瓣

        gotoXY(92, 19);
        printf("(_)");      //粉花上边花瓣

        gotoXY(92, 21);
        printf("(_)");      //粉花下边花瓣

        gotoXY(93, 20);
        color(6);
        printf("@");

        gotoXY(89, 22);
        printf("|");

        gotoXY(90, 21);
        printf("/");

        gotoXY(88, 23);
        printf("\\|");

        gotoXY(88, 24);
        printf("`|/");

        gotoXY(88, 25);
        printf("\\|");

        gotoXY(89, 26);
        printf("| /");

        gotoXY(89, 27);
        printf("|");

        gotoXY(85, 27);
        color(10);
        printf("\\\\\\\\");      //草地

        gotoXY(91, 27);
        printf("//");

        gotoXY(85, 28);//18
        color(2);
        printf("^^^^^^^^");

        gotoXY(84, 14);
        color(9);
        printf("温州大学");

        gotoXY(84, 16);
        color(11);
        printf("朱金辉");
        int i, j = 1;
        color(14);          			//黄色边框
        for (i = 13; i <= 28; i++)   	//输出上下边框===
        {
            for (j = 21; j <= 79; j++)  //输出左右边框||
            {
                gotoXY(j, i);
                if (i == 13 || i == 28) printf("—");
                else if (j == 21 || j == 79) printf("|");
            }
        }
    }

    color(11);
    gotoXY(30, 16);
    printf("1.开始游戏");
    gotoXY(56, 16);
    printf("2.设置难度");
    gotoXY(30, 20);
    printf("3.规则说明");
    gotoXY(56, 20);
    printf("4.查看排名\n");
    gotoXY(30, 24);
    printf("5.音乐\n");
    gotoXY(56, 24);
    printf("6.退出游戏\n");


    color(236);
    gotoXY(42, 26);
    printf("请选择 1 2 3 4 5 6：");

    ////music();
    color(15);
    scanf("%d", &n);


    switch (n) {
    case 1:
        system("cls");
        DrawGameFrame();
        gamePlay();
        break;
    case 2:
        setting();
        break;
    case 3:
        regulation();
        break;
        //case 4:
        //    outFile();
        //    _getch();
        //    system("cls");
        //    welcome();
        //    break;
    case 5:
        music();
        break;
    case 6:
        close();
        break;
    }


    
    
 }

 /********************************
 double interval=1000;
	pretime = 0;
	while (1) {
		currenttime = clock();
		if (currenttime-pretime>=  interval) {      
			pretime = currenttime;
           
			printf("aa\n ");
		}
			
	}
 ********************************/
 void gamePlay()
 {
     
     clock_t currenttime, pretime=0;   
     Tetris* tetris = CreateTetris();
     init();
     initHandle();
     if (interval == 0)interval = 300;   
     setTetris(tetris, GameFrame_X + GameFrame_Width, GameFrame_Y + 2, 1, 0);  
     initwall();
     while (1) {
         printScore();
         Rotate(tetris);
         PrintTetris(tetris);       
         while (1) {
             pretime = clock();
             while (1) {
                 currenttime = clock();
                 PrintTetris(tetris);                   
                 Sleep(30);                  
                 CleanTetris(tetris);
                 KeyBored(tetris);               
                 if (currenttime - pretime >= interval) {
                     break;
                 }
             }

             tetris->y++;                            //如果没有操作指令，方块向下移动
             if (ifMove(tetris) == 0)                //如果向下移动且不可动，方块放在此处
             {
                 tetris->y--;
                 PrintTetris(tetris);
                 Fixed_Tetris(tetris);
                 Del_FullLine(tetris);
                 color(15);
                 break;
             }

         }
         if (isLose(tetris)) {
             printEND();
             break;
         }

         setTetris(tetris, GameFrame_X + GameFrame_Width, GameFrame_Y + 2, 2, 0);

     }

 }

 


 



