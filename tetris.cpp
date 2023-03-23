#include "tetris.h"
#include "mywindows.h"
#include <time.h>
int map[100][100];

int i, j;
//����˹������״
int block[BLOCK_COUNT * 4][BLOCK_WIDTH][BLOCK_HEIGHT] = {
    // | �η���
    { 0,0,0,0,0,
      0,0,1,0,0,
      0,0,1,0,0,
      0,0,1,0,0,
      0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
    // L �η���
   { 0,0,0,0,0,
     0,0,1,0,0,
     0,0,1,0,0,
     0,0,1,1,0,
     0,0,0,0,0 },
   { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
   // �� �η���
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   // T �η���
   { 0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
   // Z �η���
   { 0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0 },
   { 0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
};
int score=0;
int nextshape=-1;

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
                printf("��");

        }
            
    }
        
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
    for (i = 2; i < 2 * GameFrame_Width - 2; i += 2) {     
        map[GameFrame_X + i][GameFrame_Y + GameFrame_Height] = 2;
    }

    for (i = 1; i < GameFrame_Height; i++) {
        
        map[GameFrame_X][GameFrame_Y + i] = 2;
    }

    for (i = 1; i < GameFrame_Height; i++) {
        
        map[GameFrame_X + 2 * GameFrame_Width - 2][GameFrame_Y + i] = 2;
    }
}

Tetris* KeyBored(Tetris* tetris)
{   
    int temp = tetris->x;
    char ch;//���ռ��̰���
    
    if (_kbhit()) {
        ch = _getch();
        //printf("%d",ch);
        
        if (ch == KEY_LEFT)		//�� ����
        {
            tetris->flag = true;
            tetris->x -= 2;
        }
        if (ch == KEY_RIGHT)    //�� ����
        {
            tetris->flag = true,
            tetris->x += 2;
        }
        if (ch == KEY_UP)       //�� ���� 
        {
            tetris->flag = true;
            tetris->shape_dir = (tetris->shape_dir + 1) % 4;
        }
        if (ch == KEY_DOWN)     //�� ����
        {   
            tetris->flag = false;
            while (1) {
                tetris->y++;
                if (ifMove(tetris) == 0) {
                    break;
                }
            }
            tetris->y--;            
        }       
        if (ch == KEY_SPACE) {
            PrintTetris(tetris);
            while (1) {
                if (_kbhit())            //�ٰ��ո����������Ϸ
                {
                    ch = _getch();
                    if (ch == KEY_SPACE) {
                        CleanTetris(tetris);
                        break;
                    }
                }
            }
        }
        if (ch == 114) {
            
            gamePlay();
        }
        if (ch == 27)
        {
            close();
        }
        
        if (ifMove(tetris) == 0) {
            tetris->flag = false;
            tetris->x = temp;
        }
        else {            
        }
    }
    else {
        tetris->flag = false;
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
    int k, del_rows = 0;                            //�ֱ����ڼ�¼ĳ�з���ĸ�����ɾ������������ı���
    for (j = GameFrame_Y + GameFrame_Height - 1; j >= GameFrame_Y + 1; j--) {
        k = 0;
        for (i = GameFrame_X + 2; i < GameFrame_X + 2 * GameFrame_Width - 2; i += 2) {
            if (map[i][j] == 1)                     //���������δ������ϣ��������������������ж��Ƿ�����
            {
                k++;                                //��¼���з���ĸ���
                if (k == GameFrame_Width - 2)       //�������
                {
                    for (k = GameFrame_X + 2; k < GameFrame_X + 2 * GameFrame_Width - 2; k += 2)//ɾ�����еķ���
                    {
                        map[k][j] = 0;
                        gotoXY(k, j);
                        printf("  ");
                        //      					Sleep(1);
                    }
                    for (k = j - 1; k > GameFrame_Y; k--) //���ɾ�������ϵ�λ���з��飬����������ٽ���������һ��λ��
                    {
                        for (i = GameFrame_X + 2; i < GameFrame_X + 2 * GameFrame_Width - 2; i += 2) {
                            if (map[i][k] == 1) {
                                map[i][k] = 0;
                                gotoXY(i, k);
                                printf("  ");
                                map[i][k + 1] = 1;
                                gotoXY(i, k + 1);
                                printf("��");
                            }
                        }
                    }
                    j++;   //�������ƺ������ж�ɾ�����Ƿ�����
                    del_rows++; //��¼ɾ�����������
                }
            }
        }
    }
    score += 100 * del_rows; //ÿɾ��һ�У���100��
    
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
        tetris->shape = (rand() % 5);
    }
    else {
        tetris->shape = nextshape;
    }
    nextshape = (rand() % 5);

    for (j = 0; j < BLOCK_HEIGHT; j++) {        //��ӡ��һ��tetris

        for (i = 0; i < BLOCK_WIDTH; i++) {
            //x - 4 + 2 * i, y - 2 + j
            gotoXY(GameFrame_X+2*GameFrame_Width+6-4+2*i,GameFrame_Y+10-2+j);

            if (block[4 * nextshape][j][i])
                printf("��");
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
    printf("Score: %d ��", score);
}
void intoFile()
{
    char buf[100];
    system("cls");
    FILE* f;
    errno_t err = fopen_s(&f, ".\\Debug\\top.txt", "a");
    strcpy_s(buf, "\n");
    fgets(buf, 100, f);
    getchar();
    printf("�������֣�");

    scanf("%c", buf);
    fgets(buf, 100, f);

    strcpy_s(buf, "    ");
    fgets(buf, 100, f);
    
    _itoa(score, buf, 10);
    
    fgets(buf, 100, f);

    fclose(f);



    printf("��������˳�");
    hideCursor();
    _getch();


}

