#include "tetris.h"
#include "mywindows.h"
#include <time.h>
int map[100][100];

int i, j;
int list_number=0;
//俄罗斯方块形状
int block[BLOCK_COUNT * 4][BLOCK_WIDTH][BLOCK_HEIGHT] = {
    // | 形方块
    { 0,0,0,0,0,
      0,0,1,0,0,
      0,0,1,0,0,
      0,0,1,0,0,
      0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
    // L 形方块
   { 0,0,0,0,0,
     0,0,1,0,0,
     0,0,1,0,0,
     0,0,1,1,0,
     0,0,0,0,0 },
   { 0,0,0,0,0,
   0,0,0,1,0,
   0,1,1,1,0,
   0,0,0,0,0,
   0,0,0,0,0 },
   { 0,0,0,0,0,
     0,1,1,0,0,
     0,0,1,0,0,
     0,0,1,0,0,
     0,0,0,0,0 },
   { 0,0,0,0,0,
   0,0,0,0,0,
   0,1,1,1,0,
   0,1,0,0,0,
   0,0,0,0,0 },
   // 田 形方块
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   // T 形方块
   { 0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
   // Z 形方块
 { 0,0,0,0,0,
   0,1,1,0,0,
   0,0,1,1,0,
   0,0,0,0,0,
   0,0,0,0,0 },
   { 0,0,0,0,0,
   0,0,1,0,0,
   0,1,1,0,0,
   0,1,0,0,0,
   0,0,0,0,0 },
 { 0,0,0,0,0,
   0,0,1,1,0,
   0,1,1,0,0,
   0,0,0,0,0,
   0,0,0,0,0 },
   { 0,0,0,0,0,
   0,1,0,0,0,
   0,1,1,0,0,
   0,0,1,0,0,
   0,0,0,0,0 },
};
int score=0;
int nextshape=-1;
int isguide = -1;

/********************************
 
*********************************/


void init()
{
    score = 0;
    nextshape = -1;
    memset(map, 0, sizeof(map));
}

void setTetris(Tetris* tetris,int x,int y,int shape, int shape_dir)
{
    tetris->x = x;
    tetris->y = y;
    tetris->shape = shape;
    tetris->shape_dir = shape_dir;
    
}
Tetris* CreateTetris()
{
    Tetris* tetris = (Tetris*)malloc(sizeof(Tetris));
    setTetris(tetris,0,0,0,0);
    tetris->isguide = -1;
    tetris->isauto = -1;
    return tetris;
}


void PrintTetris(struct Tetris* tetris)
{   
    int x = tetris->x;
    int y = tetris->y;
    int shape = tetris->shape;
    int dir = tetris->shape_dir;
    
    for (j = 0; j < BLOCK_HEIGHT; j++) {
        
        for (i = 0; i < BLOCK_WIDTH; i++) {
            gotoXY(x - 4+2*i, y - 2 +j);
            switch (shape) {
            case 0:color(14); break;
            case 1:color(9); break;
            case 2:color(7); break;
            case 3:color(11); break;
            case 4:color(13); break;
            }
            if(block[4*shape+dir][j][i])                  
                printf("■");

        }
            
    }
    color(15);
        
}

void PrintHollowTetris(Tetris* tetris)
{
    int x = tetris->x;
    int y = tetris->y;
    int shape = tetris->shape;
    int dir = tetris->shape_dir;

    for (j = 0; j < BLOCK_HEIGHT; j++) {

        for (i = 0; i < BLOCK_WIDTH; i++) {
            gotoXY(x - 4 + 2 * i, y - 2 + j);
            switch (shape) {
            case 0:color(14); break;
            case 1:color(9); break;
            case 2:color(7); break;
            case 3:color(11); break;
            case 4:color(13); break;
            }
            if (block[4 * shape + dir][j][i])
                printf("□");

        }

    }
    color(15);
}

void CleanTetris(struct Tetris* tetris)
{
    int x = tetris->x;
    int y = tetris->y;
    int shape = tetris->shape;
    int dir = tetris->shape_dir;
    for (j = 0; j < BLOCK_HEIGHT; j++) {

        for (i = 0; i < BLOCK_WIDTH; i++) {
            gotoXY(x - 4 + 2 * i, y - 2 + j);

            if (block[4 * shape + dir][j][i])
                printf("  ");

        }

    }
}

void initwall()
{
    for (i = 2; i <= 2 * GameFrame_Width - 2; i += 2) {     
        map[GameFrame_X + i][GameFrame_Y + GameFrame_Height] = 2;
    }

    for (i = 1; i <= GameFrame_Height; i++) {
        
        map[GameFrame_X][GameFrame_Y + i] = 2;
    }

    for (i = 1; i <= GameFrame_Width; i++) {
        
        map[GameFrame_X + 2 * GameFrame_Width - 2][GameFrame_Y + i] = 2;
    }
    map[GameFrame_X + 2 * GameFrame_Width - 2][GameFrame_Y + GameFrame_Width+1] = 2;
}

Tetris* KeyBored(Tetris* tetris)
{   
    int temp = tetris->x;
    int shape_index = tetris->shape_dir;
    char ch;//接收键盘按键
    
    if (_kbhit()) {
        ch = _getch();
        //printf("%d",ch);
        
        if (ch == KEY_LEFT)		//按 ←键
        {
            
            tetris->x -= 2;
        }
        if (ch == KEY_RIGHT)    //按 →键
        {
            
            tetris->x += 2;
        }
        if (ch == KEY_UP)       //按 ↑键 
        {
            
            tetris->shape_dir = (tetris->shape_dir + 1) % 4;
        }
        if (ch == KEY_DOWN)     //按 ↓键
        {   
            
            while (1) {
                tetris->y++;
                if (ifMove(tetris) == 0) {
                    break;
                }
            }
            tetris->y--;            
        }       
        
        if (ch == KEY_SPACE) {
            //PrintTetris(tetris);
            //while (1) {
            //    if (_kbhit())            //再按空格键，继续游戏
            //    {
            //        ch = _getch();
            //        if (ch == KEY_SPACE) {
            //            CleanTetris(tetris);
            //            break;
            //        }
            //    }
            //}
            PrintTetris(tetris);
            system("pause>nul");

        }
        if (ch == 114) {        //r 重新开始
            system("cls");
            DrawGameFrame();
            gamePlay();
        }
        if (ch == 27)           //esc 关闭
        {
            close();
        }
        if (ch == 102) {        //f 自动功能
            tetris->isauto = -tetris->isauto;
            gotoXY(GameFrame_X + 2 * GameFrame_Width + 23, GameFrame_Y + 16);
            
            if (tetris->isauto == 1) {
                color(12);
                printf("f: 半自动");
                color(15);
            }
            else {
                color(14);
                printf("f: 半自动");
            }
            
        }
        if (ch == 103) {        //g 辅助功能
            tetris->isguide = -tetris->isguide;
            gotoXY(GameFrame_X + 2 * GameFrame_Width + 23, GameFrame_Y + 18);
            

            if (tetris->isguide == 1) {
                color(12);
                printf("g: 提示");
                color(15);
            }
            else {
                color(14);
                printf("g: 提示");
            }
        }
        if (ch == 110) {           //n 换下一个
            nextshape = (rand() % 5);
            for (j = 0; j < BLOCK_HEIGHT; j++) {        //打印下一个tetris

                for (i = 0; i < BLOCK_WIDTH; i++) {
                    //x - 4 + 2 * i, y - 2 + j
                    gotoXY(GameFrame_X + 2 * GameFrame_Width + 6 - 4 + 2 * i, GameFrame_Y + 10 - 2 + j);

                    if (block[4 * nextshape][j][i])
                        printf("■");
                    else
                        printf("  ");
                }

            }
        }

        
        if (ifMove(tetris) == 0) {
            
            tetris->shape_dir = shape_index;
            tetris->x = temp;
        }
        else {            
        }
    }
    else {
        
    }
    return tetris;
}

int ifMove(Tetris* tetris)
{
    int x = tetris->x;
    int y = tetris->y;
    int shape = tetris->shape;
    int dir = tetris->shape_dir;
    for (j = 0; j < BLOCK_HEIGHT; j++) {
        for (i = 0; i < BLOCK_WIDTH; i++) {
            if (block[4 * shape+dir][j][i] == 1 && map[x - 4 + 2 * i][y - 2 + j] != 0) {
                
                return 0;
            }
           
            
        }
    }


    return 1;
}

void Del_FullLine(Tetris* tetris)
{
    int sor;
    int k, del_rows = 0;                            //分别用于记录某行方块的个数和删除方块的行数的变量
    for (j = GameFrame_Y + GameFrame_Height - 1; j >= GameFrame_Y + 1; j--) {
        k = 0;
        for (i = GameFrame_X + 2; i < GameFrame_X + 2 * GameFrame_Width - 2; i += 2) {
            if (map[i][j] == 1)                     //竖坐标依次从下往上，横坐标依次由左至右判断是否满行
            {
                k++;                                //记录此行方块的个数
                if (k == GameFrame_Width - 2)       //如果满行
                {
                    for (k = GameFrame_X + 2; k < GameFrame_X + 2 * GameFrame_Width - 2; k += 2)//删除满行的方块
                    {
                        map[k][j] = 0;
                        gotoXY(k, j);
                        printf("  ");
                        //      					Sleep(1);
                    }
                    for (k = j - 1; k > GameFrame_Y; k--) //如果删除行以上的位置有方块，则先清除，再将方块下移一个位置
                    {
                        int n = (rand() % 5) ;
                        switch (n)
                        {
                        case 0:color(14); break;
                        case 1:color(9); break;
                        case 2:color(7); break;
                        case 3:color(11); break;
                        case 4:color(13); break;
                        default:
                            break;
                        }
                        
                        for (i = GameFrame_X + 2; i < GameFrame_X + 2 * GameFrame_Width - 2; i += 2) {
                            if (map[i][k] == 1) {
                                map[i][k] = 0;
                                gotoXY(i, k);
                                printf("  ");
                                map[i][k + 1] = 1;
                                gotoXY(i, k + 1);
                                printf("■");
                            }
                        }
                    }
                    j++;   //方块下移后，重新判断删除行是否满行
                    del_rows++; //记录删除方块的行数
                }
            }
        }
    }
    score += 100 * del_rows; //每删除一行，得100分
    
}

void Fixed_Tetris(Tetris* tetris)
{
    int x = tetris->x;
    int y = tetris->y;
    int shape = tetris->shape;
    int dir = tetris->shape_dir;
    for (j = 0; j < BLOCK_HEIGHT; j++) {
        for (i = 0; i < BLOCK_WIDTH; i++) {
            if (block[4 * shape+dir][j][i] == 1 ) {
                map[x - 4 + 2 * i][y - 2 + j] = 1;              
            }
        }
    }
    
}

void Rotate(Tetris* tetris)
{
    srand(time(NULL));
    if (nextshape == -1) {
        //tetris->shape = (rand() % 5);
        tetris->shape = 0;
    }
    else {
        tetris->shape = nextshape;
    }
    nextshape = (rand() % 5);

    for (j = 0; j < BLOCK_HEIGHT; j++) {        //打印下一个tetris

        for (i = 0; i < BLOCK_WIDTH; i++) {
            //x - 4 + 2 * i, y - 2 + j
            gotoXY(GameFrame_X+2*GameFrame_Width+6-4+2*i,GameFrame_Y+10-2+j);

            if (block[4 * nextshape][j][i])
                printf("■");
            else
                printf("  ");
        }

    }
    
}

bool isLose(Tetris* tetris)
{
    for (i = tetris->y - 2; i < tetris->y + 2; i++)
    {
        if (i == GameFrame_Y) {
            return true;
        }
    }
    return false;
}

void changeLevel(int grade)
{

}

int getScore()
{
    return score;
}

void printScore()
{
    gotoXY(GameFrame_X + 2 * GameFrame_Width + 6 - 3 , GameFrame_Y +4);
    printf("Score: %d 分", score);
}
void intoFile()
{
    char buf[100] = {'\0'};
    system("cls");
    FILE* f;
    errno_t err = fopen_s(&f, ".\\Debug\\top.txt", "a+");
    if (err != 0) {
        printf("open failed");
        close();
    }
    getchar();
   
    printf("输入名字：");

    scanf("%s", buf);
    fprintf(f, "%s", buf);          //name

    fputc('\n', f);

    _itoa(score, buf, 10);          //score  
    fprintf(f, "%s", buf);

    fputc('\n', f);
    fclose(f);



    printf("按任意键");
    hideCursor();
    _getch();


}

void outFile()
{
    FILE* f;
    errno_t err = fopen_s(&f, ".\\Debug\\top.txt", "a+");
    if (err != 0) {
        printf("open failed");
        close();
    }

    char name[10][50];  
    int score[10];
    char c[1000];
    int flag=1;
    int max=0;
    list_number = 0;
    while (!feof(f)) {
        fscanf(f, "%s", name[list_number]);
        fscanf(f, "%d", &score[list_number]);
        list_number++;
    }
    list_number--;
    for (int i = 0; i < list_number; i++) {
        if (score[i] > score[max])max = i;
        printf("%s:\n            %10d\n", name[i], score[i]);
    }
    printf("\n\n\n\n全场最高  %s:  %10d\n", name[max], score[max]);
    
    fclose(f);
   
    
    
}

void calGuideTetris(Tetris *guideTetris)
{ 
    

    while (1) {
        guideTetris->y++;
        if (ifMove(guideTetris) == 0) {
            break;
        }
    }
    guideTetris->y--;
}

bool autoFall(Tetris* tetris)
{
    int leftX = 100;
    int leftY = 0;
    int rightX = 0;
    int rightY = 0;
    int x = tetris->x;
    int y = tetris->y;
    int shape = tetris->shape;
    int d = tetris->shape_dir;
    for (j = 0; j < BLOCK_HEIGHT; j++) {
        for (i = 0; i < BLOCK_WIDTH; i++) {
            if (block[4 * shape + d][j][i]) {
                if (leftX > i)leftX = i;
                if (rightX < i)rightX = i;
                if (leftX==i && leftY < j)leftY = j;
                if (rightX==i &&rightY < j)rightY = j;
            }
        }
    }
    //gotoXY(x - 4 + 2 * i, y - 2 + j);
    leftX = x - 4 + 2 * leftX;
    leftY = y - 2 + leftY;

    rightX = x - 4 + 2 * rightX;
    rightY = y - 2 + rightY;
    if (shape == 3 && d == 0 && map[x][y+1]) {
        if (  map[leftX][leftY + 1]  && map[rightX][rightY + 1])return true;       
    }
    else if (shape == 1 && d == 1) {
        
    }
    else if (shape == 1 && d == 3) {

    }
    else {
        if(map[leftX - 2][leftY] && map[leftX][leftY + 1] && map[rightX + 2][rightY] && map[rightX][rightY + 1])return true; }
    
    //map[38][22]



    int n = tetris->shape;  
    switch ( 4*n + d ) {
    case 0: // | 形方块    
        
        break;
    case 1:
        if (map[x-2][y + 1] && map[x+2][y + 1] && map[x][y+1] )return true;
    case 4:// L 形方块
        
      
        break;
    case 5:
        if (map[x - 2][y + 1] && map[x + 2][y + 1] && map[x][y + 1])return true;
        break;
    case 6:
        if (map[x - 2][y ] && map[x -2][y + 1] &&map[x][y+2])return true;
        break;
    case 7:
        if (map[x][y+1 ] && map[x +2][y+1 ] && map[x-2][y + 2])return true;
        break;
    case 8:// 田 形方块
        
        if (map[x - 2][y + 1] == 2 && map[x][y + 1] == 2)return true;
        break;
    case 12:   // T 形方块                 //
       
        break;
    case 13:
        if (map[x][y + 1] && map[x + 2][y + 2] && map[x + 4][y + 1])return true;
        
        break;
    case 14:
       
        if (map[x - 2][y + 1] && map[x + 2][y + 1] && map[x][y + 1])return true;
        break;
    case 15:
        if (map[x][y+1] && map[x -2][y + 2] && map[x - 4][y + 1])return true;
        break;
    case 16:// Z 形方块	
        
        if (map[x-2][y]&&map[x+2][y+1] && map[x][y + 1])return true;
        break;
    case 17:
        if (map[x][y+1] && map[x -2][y + 2] && map[x - 4][y + 1])return true;
        break;
    case 18:
        if (map[x - 2][y+1] && map[x + 2][y ] && map[x][y + 1])return true;
        break;
    case 19:
        if (map[x-2][y + 1] && map[x][y + 2] && map[x+2][y + 1])return true;
        break;
    default:
        return false;
    }
    return false;
}



