#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>



int getch_noblock() {  //для того чтобы значение считывались с клавиатуру постоянно
    if (_kbhit())
        return _getch();
    else
        return -1;
}

int place[20][67]; // y-i x-j
int xhead[67], yhead[20]; //координаты головы змейки 
int xapple, yapple; //координаты яблока 
int hanta = 1; //хвост
bool left, right = true, down, up;
char mmove;
char nickname[5];
int point0, point1, point2, point3, point4, point5; //баллы
char name0[10], name1[10], name2[10], name3[10], name4[10], name5[10]; //имена
char name[10];
int Level, point=0;
int count = 0; //игры сыгранные

int game() //рисовка поля и змейки и яблока и со временем хвоста
{
    system("cls");
    printf("+-------------------------------------------------------------------+\n");
    for (int i = 0; i < 20; i++)
    {
        printf("|");
        for (int j = 0; j < 67; j++)
        {
            if (place[i][j] == 0)
                printf(" ");
            if (place[i][j] == -1)
            {
                printf("@"); //голова
                place[i][j] = 0;
            }
            if (place[i][j] > 0)
            {
                printf("6"); //хвост
                place[i][j] = 0; 
            }
            if (place[i][j] == -2)
                printf("2"); //яблоко
          
        }
        printf("|\n");
    }
    printf("+-------------------------------------------------------------------+\n");
    printf("%d\n", point); //баллы
}
int start() //начало, приветсвие, ввод имени и выборка уровня
{

    int level = 0;
    do
    {
        int u;
        system("cls");
        printf("Hey! \n Welcome to the /SNAKE/ game! \n What is your nickname?\n");
        printf("Please, after writing your name write 1\n");
        fgets(name, 10,stdin);
        scanf("%d", &u);
        printf("Excellent!\n Are you ready???");
        printf("Haha You don't have choice!\n But you can choose level ^-^\n ");
        printf("Please, write number:\n 1 - easy\n 2 - normal\n 3 - hard\n");
        scanf("%d", &level);
        printf("Okei, let's start!");
        if ((level >= 4) || (level < 0))
            level = 1;
        if (level == 1)
            Level = 300;
        if (level == 2)
            Level = 200;
        if (level == 3)
            Level = 100;
    } while (level == 0);
  
}
int head() //генерация координат головы
{
    xhead[0] = 1 + (rand() % (66 - 1 + 1));
    yhead[0] = 1 + (rand() % (19 - 1 + 1));
    
}
int apple() //генерация координат головы
{
    xapple = 1 + (rand() % (66 - 1 + 1));
    yapple = 1 + (rand() % (19 - 1 + 1));
    place[yapple][xapple] = -2;
}
int move() //направления движения
{
    mmove = getch_noblock(); 

    if (((mmove == 'a') || (mmove == 'A')) && (!right)) //лево
    {
        left = true;
        down = false;
        up = false;
    }
    if (((mmove == 'w') || (mmove == 'W')) && (!down)) //вверх
    {
        left = false;
        right = false;
        up = true;
    }
    if (((mmove == 'd') || (mmove == 'D')) && (!left)) //право
    {
        right = true;
        down = false;
        up = false;
    }
    if (((mmove == 's') || (mmove == 'S')) && (!up)) //вниз
    {
        left = false;
        right = false;
        down = true;
    }
}
int moving() //движение
{
    if (left == true)
    {
        xhead[0]--;
    }
    if (up == true)
    {
        yhead[0]--;
    }
    if (right == true)
    {
        xhead[0]++;
    }
    if (down == true)
    {
        yhead[0]++;
    }
    
    for (int i = hanta; i > 0; i--) //движение хвоста
    {
        xhead[i] = xhead[i - 1];
        yhead[i] = yhead[i - 1];
        place[yhead[i]][xhead[i]] = 1;
    }
    if ((yapple == yhead[0]) && (xhead[0] == xapple)) //пересечение головы и яблока
    {
        point++;
        hanta++; //добавление длинны хвоста
        apple();
    }
    
   
}

int losing() //проигрыш
{
    system("pause");
    system("cls");
    count++; //прибавление к числу проигранных игр 
    printf("GAME OVER\n");
    for (int i = 0; i < 67; i++) 	//обнуление змеюки
    {
        xhead[i] = 0;
    }
    for (int i = 0; i < 20; i++) 	
    {
        yhead[i] = 0;
    }
    for (int i = 0; i < 20; i++)  //обнуление пространства 
    {
        for (int j = 0; j < 67; j++)
        {
            place[i][j] = 0;
        }
    }
    //большая сортировка от значимости проигранных игр 
    if (count == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            name1[i] = name[i];
        }
        point1 = point;
        printf("Highscores:\n");
        printf("1. ");
        printf("%s ", &name1);
        printf("scores: %d\n", point1);
    }
   
    if (count == 2)
    {
        for (int i = 0; i < 10; i++)
        {
            name2[i] = name[i];
        }
        point2 = point;
        if (point2 > point1)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name2[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name2[i] = name1[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name1[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point2;
            point2 = point1;
            point1 = point0;
            point0 = 0;
        }
        printf("Highscores:\n");
        printf("1. ");
        printf("%s ", &name1);      
        printf("scores: %d\n", point1);
        printf("2. ");
        printf("%s ", &name2);
        printf("scores: %d\n", point2);
    }
    if (count == 3)
    {
        for (int i = 0; i < 10; i++)
        {
            name3[i] = name[i];
        }
        point3 = point;
        if (point3 > point1)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name3[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name3[i] = name1[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name1[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point3;
            point3 = point1;
            point1 = point0;
            point0 = 0;
        }
        if (point3 > point2)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name3[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name3[i] = name2[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name2[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point3;
            point3 = point2;
            point2 = point0;
            point0 = 0;
        }
        printf("Highscores:\n");
        printf("1. ");
        printf("%s ", &name1);
        printf("scores: %d\n", point1);
        printf("2. ");
        printf("%s ", &name2);
        printf("scores: %d\n", point2);
        printf("3. ");
        printf("%s ", &name3);
        printf("scores: %d\n", point3);
    }
    if (count == 4)
    {
        for (int i = 0; i < 10; i++)
        {
            name4[i] = name[i];
        }
        point4 = point;
        if (point4 > point1)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name4[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name4[i] = name1[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name1[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point4;
            point4 = point1;
            point1 = point0;
            point0 = 0;
        }
        if (point4 > point2)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name4[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name4[i] = name2[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name2[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point4;
            point4 = point2;
            point2 = point0;
            point0 = 0;
        }
        if (point4 > point3)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name4[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name4[i] = name3[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name3[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point4;
            point4 = point3;
            point3 = point0;
            point0 = 0;
        }
        printf("Highscores:\n");
        printf("1. ");
        printf("%s ", &name1);
        printf("scores: %d\n", point1);
        printf("2. ");
        printf("%s ", &name2);
        printf("scores: %d\n", point2);
        printf("3. ");
        printf("%s ", &name3);
        printf("scores: %d\n", point3);
        printf("4. ");
        printf("%s ", &name4);
        printf("scores: %d\n", point4);
    }
    if (count == 5)
    {
        for (int i = 0; i < 10; i++)
        {
            name5[i] = name[i];
        }
        point5 = point;
        if (point5 > point1)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name5[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name5[i] = name1[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name1[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point5;
            point5 = point1;
            point1 = point0;
            point0 = 0;
        }
        if (point5 > point2)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name5[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name5[i] = name2[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name2[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point5;
            point5 = point2;
            point2 = point0;
            point0 = 0;
        }
        if (point5 > point3)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name5[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name5[i] = name3[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name3[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point5;
            point5 = point3;
            point3 = point0;
            point0 = 0;
        }
        if (point5 > point4)
        {
            for (int i = 0; i < 10; i++)
            {
                name0[i] = name5[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name5[i] = name4[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name4[i] = name0[i];
            }
            for (int i = 0; i < 10; i++)
            {
                name0[i] = 0;
            }
            point0 = point5;
            point5 = point4;
            point4 = point0;
            point0 = 0;
            printf("Highscores:\n");
            printf("1. ");
            printf("%s ", &name1);
            printf("scores: %d\n", point1);
            printf("2. ");
            printf("%s ", &name2);
            printf("scores: %d\n", point2);
            printf("3. ");
            printf("%s ", &name3);
            printf("scores: %d\n", point3);
            printf("4. ");
            printf("%s ", &name4);
            printf("scores: %d\n", point4);
            printf("5. ");
            printf("%s ", &name5);
            printf("scores: %d\n", point5);
            system("pause");
        }
    }

    if (count == 6) { // если играется 6 раз, то его результаты не учитываются и просто идет вывод рекордной табл 
        printf("Highscores:\n");
        printf("1. ");
        printf("%s ", &name1);
        printf("scores: %d\n", point1);
        printf("2. ");
        printf("%s ", &name2);
        printf("scores: %d\n", point2);
        printf("3. ");
        printf("%s ", &name3);
        printf("scores: %d\n", point3);
        printf("4. ");
        printf("%s ", &name4);
        printf("scores: %d\n", point4);
        printf("5. ");
        printf("%s ", &name5);
        printf("scores: %d\n", point5);
        system("pause");
        printf("Thanks for playing this SNAKE game, with love Aiten ^_^");
        exit(0); //выход из игры
    }
    if (count < 6) //если играется менее 6 раз то все обнуляется и по новой запускается игра
    {
        memset(name, 0, 10);
        system("pause");
        hanta = 1;
        point = 0;
        Level = 0;
        right = true;
        left = false;
        up = false;
        down = false;
        main();
    }
   
}


int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    start();
    head();
    apple();
    place[yhead[0]][xhead[0]] = -1;
    place[yapple][xapple] = -2;
    game();
    Sleep(3000); //задержка на 3 секунды перед игрой чтобы игрок смог ориентироваться
    do
    {
        Sleep(Level);
        move();
        if ((yhead[0] >= 19) || (yhead[0] <= 0)) //сталкновение со стенами
            losing();
        if ((xhead[0] >= 66) || (xhead[0] <= 0))
            losing();
        for (int i = hanta; i > 1; i--) //столкновение с хвостом
        {
            if (hanta > 4 && xhead[0] == xhead[i] && yhead[0] == yhead[i])
                losing();
        }
        moving();
        place[yhead[0]][xhead[0]] = -1;
        game();
    } while (mmove != 'z');
    
    
    return 0;
}