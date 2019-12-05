/******************************
文件名称：main.cpp
文件描述：实现一个有界面的打字练习游戏
编译环境：VS2013
最后修改：<2019.12.4><创建工程><Romeo>
********************************/
#include "letter.h"

TARLETTER * pLetter = NULL;

int main()
{
	//图形界面编程
	//有界面，有窗口
	//初始化一个窗口，宽，高
	//初始化完成一个窗口后，在窗口里相当于有一个坐标系,横坐标x，纵y
	initgraph(WND_WIDTH, WND_HEIGHT);
	setbkcolor(BLACK); //设置背景颜色为红色
	cleardevice();   //用设置好的红色去刷新背景
	Welcome();
	PlayGame();
	closegraph();	//关闭窗口
	return 0;
}

//欢迎界面
void Welcome()
{

	IMAGE backImg; //IMAGE是一个类，用来保存图片的类
	//加载图片
	//loadimage(&backImg, L"./res/背景.jpg", WND_WIDTH, WND_HEIGHT);
	//loadimage(&backImg, L"./res/背景.jpg", WND_WIDTH, WND_HEIGHT);
	loadimage(&backImg, L"IMAGE", MAKEINTRESOURCE(IDR_IMAGE1), WND_WIDTH, WND_HEIGHT);

	//输出出来
	putimage(0, 0, &backImg);

	//设置透明风格
	setbkmode(TRANSPARENT);
	PlaySound(LPCWSTR(IDR_WAVE1), NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);
	//PlaySound(L"./res/字母歌.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	settextstyle(70, 0, L"微软雅黑"); //设置字体格式
	settextcolor(BLUE);            //设置字体的颜色
	outtextxy(200, 50, L"打字母游戏"); //在指定的位置（坐标）输出文本

	settextstyle(25, 0, L"宋体");
	settextcolor(YELLOW);
	outtextxy(75, 200, L"♥ Romeo");
	outtextxy(75, 250, L"♥ Ver:1.0");
	outtextxy(75, 300, L"♥ 欢迎修改");

	int colorR = 255;
	int colorG = 0;
	int speed = 5;
	//kbhit()检测键盘是否有消息
	while (!_kbhit())
	{
		//!_kbhit(),一旦有键盘消息
		//设置字体的颜色
		settextcolor(RGB(colorR, colorG, 0));
		outtextxy(250, 430, L"按任意键继续...");
		colorR -= speed;
		colorG += speed;
		if (colorR <= 0 || colorR >= 255)
		{
			speed = -speed;
		}
		Sleep(20);
	}



}

//开始游戏
void PlayGame()
{

	cleardevice();
	outtextxy(200, 200, L"请切换为英文输入哦~");
	Sleep(1500);
	DWORD tPre, tNow; //time pre, time now
	//创建链表
	createList();
	cleardevice();
	char cKeyLetter; //键盘的输入字母
	IMAGE boomImg; //IMAGE是一个类，用来保存图片的类
	//加载图片
	//loadimage(&boomImg, L"./res/boom.jpg", 50, 50);
	loadimage(&boomImg, L"IMAGE", MAKEINTRESOURCE(IDR_IMAGE2), 65, 65);
	tPre = timeGetTime(); //获取系统时间
	while (1)
	{
		tNow = timeGetTime();//获取系统时间
		if (tNow - tPre >= 600) //1s间隔
		{
			addLetterNode();
			tPre = tNow;
		}
		Sleep(25);
		TARLETTER* pTemp = pLetter->pNext;
		cleardevice();
		int i = 0;
		while (pTemp != NULL)
		{

			outtextxy(pTemp->x, pTemp->y, pTemp->ch);
			++i;
			pTemp->y += i;
			pTemp = pTemp->pNext;
		}

		if (_kbhit())
		{

			cKeyLetter = _getch(); //获取到键盘的输入
			TARLETTER* pTemp = pLetter->pNext;
			TARLETTER* pPre = pLetter;
			while (pTemp != NULL)
			{
				if (pTemp->ch == cKeyLetter || pTemp->ch + 32 == cKeyLetter)
				{
					putimage(pTemp->x, pTemp->y, &boomImg);
					Sleep(50);
					pPre->pNext = pTemp->pNext;
					free(pTemp);
					break;
				}
				else
				{
					pTemp = pTemp->pNext;
					pPre = pPre->pNext;
				}
			}

		}
		/*for (nLetterY = 0; nLetterY < WND_HEIGHT; nLetterY += 4)
		{
		cleardevice(); //清楚痕迹
		outtextxy(nLetterX, nLetterY, cTarLetter);

		Sleep(20);

		if (_kbhit()) //有键盘按下
		{
		cKeyLetter = _getch(); //用变量保存按下的字符
		if (cKeyLetter == cTarLetter || cKeyLetter == cTarLetter + 32)
		{
		//不管按下的的是大写字母还是小写字母
		//输出出来
		putimage(nLetterX, nLetterY, &boomImg);
		Sleep(130);
		break;
		}
		}
		}*/
	}
}


//创建链表
void createList()
{
	pLetter = (TARLETTER*)malloc(sizeof(TARLETTER));
	pLetter->pNext = NULL;
}



//添加节点
void addLetterNode()
{
	TARLETTER* pTemp = NULL;
	TARLETTER* pNew = NULL;

	pTemp = pLetter;

	//pTemp指向最后节点
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
	}

	//开辟内存
	pNew = (TARLETTER*)malloc(sizeof(TARLETTER));
	pNew->ch = rand() % 26 + 65; //填充节点的数据
	pNew->x = rand() % (WND_WIDTH - 25);
	pNew->y = 0;
	//链表连接 
	pNew->pNext = NULL;
	pTemp->pNext = pNew;
}