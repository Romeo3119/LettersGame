#pragma once
#include <stdio.h>
#include <graphics.h>
#include <conio.h> //kbhit
//������ý���豸�ӿڵ�ͷ�ļ��Ϳ��ļ�
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")

#include <time.h>
#include <stdlib.h>
#include "resource.h"

#define WND_WIDTH 640
#define WND_HEIGHT 480

typedef struct Node{
	char ch; //��ĸ
	int x;
	int y;
	struct Node* pNext;
}TARLETTER;

void Welcome();
void PlayGame();
//��������
void createList();

//��ӽڵ�
void addLetterNode();