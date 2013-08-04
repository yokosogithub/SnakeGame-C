struct SNAKE_NODE
{
	int x;
	int y;
	short direction;          //0:up  1:right 2:down 3:left
	short type;               //
	struct SNAKE_NODE *next;
	struct SNAKE_NODE *pre;
	
} *snakeHead,*snakeTail;

struct FOOD
{
	int x;
	int y;
	short type;
} food;

IMAGE img_snake[9];
IMAGE img_food[10];
IMAGE img_wall[2];
IMAGE gameover;
IMAGE exitgame;
IMAGE gamebg;

FILE *fp1;
FILE *fp2;
FILE *fp3;
FILE *fp4;

int score=0;
int *readscore=NULL;
int *highscore=NULL;
struct FOOD *readfood;

void loadImage()
{

	getimage(&img_snake[0],"Images\\snakHeadUp.gif");
	getimage(&img_snake[1],"Images\\snakHeadRight.gif");
	getimage(&img_snake[2],"Images\\snakHeadDown.gif");
	getimage(&img_snake[3],"Images\\snakHeadLeft.gif");
	getimage(&img_snake[4],"Images\\snakbody.gif");
	getimage(&img_snake[5],"Images\\snakTailUp.gif");
	getimage(&img_snake[6],"Images\\snakTailRight.gif");
	getimage(&img_snake[7],"Images\\snakTailDown.gif");
	getimage(&img_snake[8],"Images\\snakTailLeft.gif");

	getimage(&img_food[0],"Images\\food0.gif");
	getimage(&img_food[1],"Images\\food1.gif");
	getimage(&img_food[2],"Images\\food2.gif");
	getimage(&img_food[3],"Images\\food3.gif");
	getimage(&img_food[4],"Images\\food4.gif");
	getimage(&img_food[5],"Images\\food5.gif");
	getimage(&img_food[6],"Images\\food6.gif");
	getimage(&img_food[7],"Images\\food7.gif");
	getimage(&img_food[8],"Images\\food8.gif");
	getimage(&img_food[9],"Images\\food9.gif");

	getimage(&img_wall[0],"Images\\wall1.gif");
	getimage(&img_wall[1],"Images\\wall2.gif");

    getimage(&gameover,"Images\\gameover.jpg");

	getimage(&exitgame,"Images\\exitgame.jpg");
	
	getimage(&gamebg,"Images\\gamebg.jpg");
    

}

void initiateSnake()
{
	struct SNAKE_NODE *node;
	snakeHead = (struct SNAKE_NODE *)malloc(sizeof(struct SNAKE_NODE));
	snakeHead->direction = 1;
	snakeHead->type = 0;
	snakeHead->x = 150;
	snakeHead->y = 150;

	snakeHead->pre = NULL;

	node = (struct SNAKE_NODE *)malloc(sizeof(struct SNAKE_NODE));	
	node->direction = 1;
	node->type = 4;
	node->x = 135;
	node->y = 150;

	snakeHead->next = node;
	node->pre = snakeHead;
	

     
	snakeTail = (struct SNAKE_NODE *)malloc(sizeof(struct SNAKE_NODE));	
	snakeTail->direction = 1;
	snakeTail->type = 5;
	snakeTail->x = 120;
	snakeTail->y = 150;

	node->next = snakeTail;
	snakeTail->pre = node;
	snakeTail->next = NULL;

	food.x = 300;
	food.y = 300;
	food.type = 0;

}


void drawSnake()
{
	struct SNAKE_NODE *node;
	node = snakeHead;
	while(node != NULL)
	{	
		if(node->type == 4)
			putimage(node->x,node->y,&img_snake[4]);
		else
			putimage(node->x,node->y,&img_snake[node->type+node->direction]);
		node = node->next;
	}
}

void drawFood()
{
	putimage(food.x,food.y,&img_food[food.type]);
}

void drawFrame()
{
	int i;
	for(i=0;i<21;i++)
	{
		putimage(i*30,0,&img_wall[0]);
		putimage(i*30,465,&img_wall[0]);
		putimage(0,i*30,&img_wall[1]);
		putimage(540,i*30,&img_wall[1]);
		putimage(625,i*30,&img_wall[1]);
	}
}

void moveSnake()
{
	struct SNAKE_NODE *node;
	node = snakeTail;
	while(node != snakeHead)
	{
		node->x = node->pre->x;
		node->y = node->pre->y;
		node->direction = node->pre->direction;
		node = node ->pre;
	}
	switch(snakeHead->direction)
	{
	case 0:
		snakeHead->y -= 15;break;
	case 1:
		snakeHead->x += 15;break;
	case 2:
		snakeHead->y += 15;break;
	case 3:
		snakeHead->x -= 15;break;
	}
    cleardevice();
}

bool ifTouchFood()
{
	int x,y;
	x = snakeHead->x;
	y = snakeHead->y;
	switch(snakeHead->direction)
	{
	case 0:
		y -= 15;break;
	case 1:
		x += 15;break;
	case 2:
		y += 15;break;
	case 3:
		x -= 15;break;
	}
	if((x == food.x) &&(y == food.y))
		return true;
	else
		return false;
}

void eatFood()
{
	struct SNAKE_NODE *node;

	node = (struct SNAKE_NODE *)malloc(sizeof(struct SNAKE_NODE));	
	node->direction = snakeHead->direction;
	node->type = 4;
	node->x = snakeHead->x;
	node->y = snakeHead->y;

	node->pre = snakeHead;
	node->next = snakeHead->next;
	
	snakeHead->next->pre = node;
	snakeHead->next = node;
	

	switch(snakeHead->direction)
	{
	case 0:
		snakeHead->y -= 15;break;
	case 1:
		snakeHead->x += 15;break;
	case 2:
		snakeHead->y += 15;break;
	case 3:
		snakeHead->x -= 15;break;
	}
    food.x = rand()%20*15+15;
	food.y = rand()%30*15+15;//产生随机的食物，但是不能在墙中
}

bool WalldeadSnake()
{
	int x,y;
	x = snakeHead->next->x;
	y = snakeHead->next->y;
	if((x <15 || x>525 || y<15 || y>465))
		return true;
	else
		return false;
}

bool eatself()
{
	int x,y;
	x=snakeHead->x;
	y=snakeHead->y;
	struct SNAKE_NODE *temp;
	int k=0;
    temp=snakeHead->next;
	while (temp!=NULL)
	{
		if (x == temp->x && y == temp->y)
		{
			k=1;
		}
        temp=temp->next;
	}
    if (k==1)
    {
		return true;
    }
	else 
	{
		return false;
	}
}


void Gameover()
{
    clearviewport();
    putimage(0,0,&gameover);
}

void Exitgame()
{
	cleardevice();
	cleardevice();
    putimage(0,0,&exitgame);
}
void Savegame()
{
	struct SNAKE_NODE *temp;
	temp=snakeHead;
    fp1=fopen("snake.txt","w");
	for (;temp!=NULL;temp=temp->next)
	{
		fwrite(temp,sizeof(struct SNAKE_NODE),1,fp1);
	}
	fclose(fp1);
}

void Savescore(int score)
{
	fp2=fopen("score.txt","w");
	fwrite(&score,sizeof(int),1,fp2);
	fclose(fp2);
}

void Savehighscore(int score)
{
	fp3=fopen("highscore.txt","w");
	fwrite(&score,sizeof(int),1,fp3);
	fclose(fp3);
}

void Savefood(struct FOOD food)
{
	fp4=fopen("food.txt","w");
	fwrite(&food,sizeof(struct FOOD),1,fp4);
	fclose(fp4);
}

void Loadscore()
{
	fp2=fopen("score.txt","r");
    int *tempscore;
	tempscore=(int *)malloc(sizeof(int));
	fread(tempscore,sizeof(int),1,fp2);
	readscore=tempscore;
	fclose(fp2);
}

void Loadhighscore()
{
    fp3=fopen("highscore.txt","r");
	int *temp;
	temp=(int *)malloc(sizeof(int));
	fread(temp,sizeof(int),1,fp3);
	highscore=temp;
	fclose(fp3);
}

void Loadgame()
{
	fp1=fopen("snake.txt","r");
	snakeHead=NULL;
    snakeTail=NULL;
	struct SNAKE_NODE *tem1,*tem2;
	tem1=tem2=(struct SNAKE_NODE*)malloc(sizeof(struct SNAKE_NODE));
	snakeHead=tem1;
	fread(tem1,sizeof(struct SNAKE_NODE),1,fp1);
	while(!feof(fp1))
	{
		tem1=(struct SNAKE_NODE*)malloc(sizeof(struct SNAKE_NODE));
		fread(tem1,sizeof(struct SNAKE_NODE),1,fp1);
		tem1->pre=tem2;
		tem2->next=tem1;
		tem2=tem1;
	}
	snakeTail=tem2->pre;
	tem2->next=snakeTail;
    snakeTail->next=NULL;
	fclose(fp1);
}

void Loadfood()
{
	fp4=fopen("food.txt","r");
    readfood=NULL;
	struct FOOD *temp;
	temp=(struct FOOD*)malloc(sizeof(struct FOOD));
	fread(temp,sizeof(struct FOOD),1,fp4);
	readfood=temp;
	fclose(fp4);
}

void playgame()
{
	int n=1;
	char a[11];
	char b[11];
	score=0;
    Loadhighscore();
	loadImage();
	initiateSnake(); 
	BeginBatchDraw();
	while(1)
	{
        if(kbhit())
		{
            
			char c;
			c= getch();
			switch(c)
			{
			case 'w':
				if (snakeHead->direction!=2)
				{
                snakeHead->direction = 0;
				}
				break;
			case 's':
				if (snakeHead->direction!=0)
				{
                snakeHead->direction = 2;
				}
				break;
			case 'a':
				if (snakeHead->direction!=1)
				{
                snakeHead->direction = 3;
				}
				break;
			case 'd':
				if (snakeHead->direction!=3)
				{
                snakeHead->direction = 1;
				}
				break;
			case 'c':
				Savegame();
                Savescore(score);
				Savefood(food);
                outtextxy(560,200,"储存成功");
				break;
			case  27:
				n=0;
				break;
			case  32:
                getch();
			 	break;
				
			}
		}
        putimage(15,15,&gamebg);
		drawFrame();
        drawFood();
		drawSnake();
        sprintf(a,"%d",score);
		if ((fp3=fopen("highscore.txt","r"))==NULL)
		{
			sprintf(b,"%d",score);
		}
		else
		{
            sprintf(b,"%d",*highscore);
			if (*highscore<score)
			{
                outtextxy(570,340," 新纪录");
				outtextxy(560,360,"!!诞生!!");
				sprintf(b,"%d",score);
			}
		}
        outtextxy(555,30,"当前分数");
		outtextxy(575,55,a);
		outtextxy(555,80,"------------------");
		outtextxy(560,100,"'c'--储存");
		outtextxy(553,120,"'Esc'--退出");
		outtextxy(557,140,"'□'--暂停");
        outtextxy(555,220,"------------------");
		outtextxy(570,240,"历史");
		outtextxy(560,260,"最高分:");
        outtextxy(575,280,b);
        outtextxy(555,320,"------------------");
		FlushBatchDraw();
        Sleep(100);
		if(ifTouchFood())
		{	
			eatFood();
		    score+=10;
		}
		else if (WalldeadSnake())
		{
			Gameover();
			break;
		}
		else if (eatself())
		{
            Gameover();
			break;
		}
		else if (n==0)
		{
			Exitgame();
			break;
		}
		else	moveSnake();
	}
	if (fp3==NULL)
	{
		Savehighscore(score);
	}
	else
	{
		if (*highscore<score)
		{
			Savehighscore(score);
		}
	}
    EndBatchDraw();
	getch();
}

void continueplaygame()
{
	char a[11];
	char b[11];
	int n=1;
	if ((fp1=fopen("snake.txt","r"))==NULL || (fp2=fopen("score.txt","r"))==NULL || (fp3=fopen("highscore.txt","r"))==NULL || (fp4=fopen("food.txt","r"))==NULL)
	{
      playgame();
	  n=2;
	}
	else
	{ 
    Loadgame();
    Loadscore();
	Loadhighscore();
    Loadfood();
	BeginBatchDraw();
    loadImage();
	food.x = readfood->x;
	food.y = readfood->y;
	food.type = readfood->type;
	while(1)
	{
		if(kbhit())
		{
			
			char c;
			c= getch();
			switch(c)
			{
			case 'w':
				if (snakeHead->direction!=2)
				{
					snakeHead->direction = 0;
				}
				break;
			case 's':
				if (snakeHead->direction!=0)
				{
					snakeHead->direction = 2;
				}
				break;
			case 'a':
				if (snakeHead->direction!=1)
				{
					snakeHead->direction = 3;
				}
				break;
			case 'd':
				if (snakeHead->direction!=3)
				{
					snakeHead->direction = 1;
				}
				break;
			case 'c':
				Savegame();
				Savescore(*readscore);
				Savefood(food);
				outtextxy(560,200,"储存成功");
				break;
			case  27:
				n=0;
				break;
			case  32:
                getch();
			 	break;
			}
		}
		drawFrame();
		drawFood();
		drawSnake();
		sprintf(a,"%d",*readscore);
	    sprintf(b,"%d",*highscore);
		if (*highscore<*readscore)
		{
            outtextxy(570,340," 新纪录");
			outtextxy(560,360,"!!诞生!!");
			sprintf(b,"%d",*readscore);
		}
        outtextxy(555,30,"当前分数");
		outtextxy(575,55,a);
		outtextxy(555,80,"------------------");
		outtextxy(560,100,"'c'--储存");
		outtextxy(553,120,"'Esc'--退出");
		outtextxy(557,140,"'□'--暂停");
        outtextxy(555,220,"------------------");
		outtextxy(570,240,"历史");
		outtextxy(560,260,"最高分:");
        outtextxy(575,280,b);
        outtextxy(555,320,"------------------");
		FlushBatchDraw();
		Sleep(100);
		if(ifTouchFood())
		{	
			eatFood();
		    *readscore+=10;
		}
		else if (WalldeadSnake())
		{
			Gameover();
			break;
		}
		else if (eatself())
		{
			Gameover();
			break;
		}
		else if (n==0)
		{
			Exitgame();
			break;
		}
		else	moveSnake();
	}
	if (*highscore<*readscore && n!=2)
	{
       Savehighscore(*readscore);
	}
	EndBatchDraw();
	getch();
	}
}
	

void tiaozhanplaygame()
{
	int speed=0;
	int i=0;
	int n=1;
	int N=1;
	char a[11];
	score=0;
	loadImage();
	initiateSnake(); 
	BeginBatchDraw();
	while(1)
	{
        if(kbhit())
		{
            
			char c;
			c= getch();
			switch(c)
			{
			case 'w':
				if (snakeHead->direction!=2)
				{
					snakeHead->direction = 0;
				}
				break;
			case 's':
				if (snakeHead->direction!=0)
				{
					snakeHead->direction = 2;
				}
				break;
			case 'a':
				if (snakeHead->direction!=1)
				{
					snakeHead->direction = 3;
				}
				break;
			case 'd':
				if (snakeHead->direction!=3)
				{
					snakeHead->direction = 1;
				}
				break;
			case  27:
				n=2;
				break;
			case  32:
                getch();
			 	break;
			}
		}
		if (score%50==0 && score!=0)
		{
			N+=1;
			N=N%10;
		}
		for (i=0;i<N;i++)
		{
			putimage(120+i*15,60+i*30,&img_wall[1]);
			if (snakeHead->next->x>=120+i*15 && snakeHead->next->x<=135+i*15 && snakeHead->next->y>=60+i*15 && snakeHead->next->y<=90+i*15)
			{
				n=0;
				break;
			}
		}
        drawFrame();
        drawFood();
		drawSnake();
        sprintf(a,"%d",score);
        outtextxy(570,30,"分数:");
		outtextxy(570,55,a);
		outtextxy(553,80,"暂不能存档");
		outtextxy(553,120,"'Esc'--退出");
		outtextxy(557,140,"'□'--暂停");
        FlushBatchDraw();
        if (score%150==0 && score<=300 && score>0)
        {
		  speed+=2;	
        }
		if (score%150==0 && score>300 && score>0)
		{
		  speed+=5;
		}
		if (speed==80)
		{
			speed=20;
		}
        Sleep(120-speed);
		if(ifTouchFood())
		{	
			eatFood();
		    score+=10;
		}
		else if (WalldeadSnake())
		{
			Gameover();
			break;
		}
		else if (eatself())
		{
            Gameover();
			break;
		}
		else if (n==0)
		{
			Gameover();
			break;
		}
		else if (n==2)
		{
			Exitgame();
			break;
		}
		else	moveSnake();
	}
    EndBatchDraw();
	getch();
}
