// flappybird01.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "bird.h"
#include "scence.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "pipes.h"
#include "status.h"
#include "endstatus.h"
#include "scence.h"


#pragma comment(lib,"Winmm.lib")

#define DELTA_TIME 1
#define LEN 5




int BACKGROUND_SCROLL_SPEED = 8;
int GROUND_SCROLL_SPEED = 10;
int BACKGROUND_LOOPING_POINT = 413;
int GROUND_LOOPING_POINT = 514;
int backgroundScroll;
int groundScroll;
int smallFont = 8;
int mediumFont = 16;
int flappyFont = 28;
int hugeFont = 56;


void a_sleep(DWORD ms);

void startup()
{
	scrolling = true;
	scence_init();
}

void updateWithoutInput(int dt)
{
	
	switch (currentStatus()) {
	case TitleStatus:
		title_update(dt);
		backgroundScroll = 0;
		groundScroll = 0;		
		break;

	case CountStatus:
		count_update(dt);
		break;
	case PlayStatus:
		//FlushMouseMsgBuffer();

		play_update(dt);
		backgroundScroll = (backgroundScroll + BACKGROUND_SCROLL_SPEED * dt)
			% BACKGROUND_LOOPING_POINT;
		groundScroll = (groundScroll + GROUND_SCROLL_SPEED * dt)
			% GROUND_LOOPING_POINT;

		break;
	case ScoreStatus:
		score_update(dt);
		break;
	case EndStatus:
		scence_init();
		statusChange(TitleStatus);
		break;
	}
		

}
void updateWithInput()
{

}

void show()
{
	putimage(-backgroundScroll, 0, &background);
	putimage(-groundScroll, WINDOW_HEIGHT - 16, &ground);
	
	switch (currentStatus()) {
	case 0:
		title_render();
		break;
	case 1:
		count_render();
		break;
	case 2:
		play_render();		
		break;
	
	case 3:
		score_render();
		break;
	}
	FlushBatchDraw();

	a_sleep(60);

}

void gameover()
{
	EndBatchDraw();
}

void a_sleep(DWORD ms) 
{
	static clock_t oldclock = clock();		// 静态变量，记录上一次 tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// 更新 tick

	if (clock() > oldclock)					// 如果已经超时，无需延时
		oldclock = clock();
	else
		while (clock() < oldclock)			// 延时
			Sleep(1);						// 释放 CPU 控制权，降低 CPU 占用率
}

int main()
{	
	srand((unsigned)time(NULL));
	startup();
	while (1)
	{
		show();  // 显示画面
		updateWithoutInput(DELTA_TIME);  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	gameover();     // 游戏结束、后续处理
	return 0;
}


