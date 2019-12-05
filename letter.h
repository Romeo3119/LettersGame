#pragma once
#include <stdio.h>
#include <graphics.h>
#include <conio.h> //kbhit
//包含多媒体设备接口的头文件和库文件
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")

#include <time.h>
#include <stdlib.h>
#include "resource.h"

#define WND_WIDTH 640
#define WND_HEIGHT 480

typedef struct Node{
	char ch; //字母
	int x;
	int y;
	struct Node* pNext;
}TARLETTER;

void Welcome();
void PlayGame();
//创建链表
void createList();

//添加节点
void addLetterNode();