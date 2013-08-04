#include "graphics.h"
#include <stdio.h>
#include <conio.h>
#include "playgame.cpp"
#include<stdlib.h>
#include <malloc.h>


IMAGE img_mainUI[3];
IMAGE BG;
IMAGE Intro;
IMAGE exitpro;
void playgame();

void main()
{
	
    initgraph(640, 480);
	getimage(&BG,"Images\\Ã∞≥‘…ﬂ01.jpg");
	getimage(&Intro,"Images\\intro.jpg");
   
    getimage(&img_mainUI[0],"Images\\Ã∞≥‘…ﬂ01.jpg");
	getimage(&img_mainUI[1],"Images\\Ã∞≥‘…ﬂ02.jpg");
	getimage(&img_mainUI[2],"Images\\Ã∞≥‘…ﬂ03.jpg");
	getimage(&img_mainUI[3],"Images\\Ã∞≥‘…ﬂ04.jpg");
    putimage(0,0,&BG);
	char c;
	short state=0;
	
	do 
	{
        c=getch();
		if (c==13)
		{
			switch (state)
			{
			 case 0:playgame();
				  break;
			 case 1:continueplaygame();
				 break;
			 case 2:tiaozhanplaygame();
				 break;
			 case 3:putimage(0,0,&Intro);
				 getch();
				 break;
			}
		}
		else if (c==-32)
		{
			c=getch();
			switch (c)
			{
			case 72: state--;  //…œ
				if (state<0)
				{
				   state=3;
				} 
				break;
			case 80: state++;
				state=state%4;
				break;
			}

		}
		else if (c==27)
		{
			break;
		}
		putimage(0,0,&img_mainUI[state]);
	} while (c!=0);
    closegraph(); 
}