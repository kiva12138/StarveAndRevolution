#include <afxwin.h>
#include <string>
#include <mmsystem.h>

struct Fish1 {
	CBitmap * fishBMP;
	CBitmap * fishSBMP;
	int xCen;
	int yCen;
	bool exist;
	int speed;
	int len;//半径检测
	int direction;
};

struct Fish2 {
	CBitmap * fishBMP;
	CBitmap * fishSBMP;
	int xCen;
	int yCen;
	bool exist;
	int speed;
	int len;//半径检测
	int direction;
};

struct Fish3 {
	CBitmap * fishBMP;
	CBitmap * fishSBMP;
	int xCen;
	int yCen;
	bool exist;
	int speed;
	int len;//半径检测
	int direction;
};

struct Fish4 {
	CBitmap * fishBMP;
	CBitmap * fishSBMP;
	int xCen;
	int yCen;
	bool exist;
	int speed;
	int len;//半径检测
	int direction;
};

struct Fish5{
	CBitmap * fishBMP;
	CBitmap * fishSBMP;
	int xCen;
	int yCen;
	bool exist;
	int speed;
	int len;//半径检测
	int direction;//1 from left, 2 from right
};

class CMyWnd :public CFrameWnd {
public:
	CBitmap * backGroundBMP;
	CBitmap * startBackGroundBMP;
	CBitmap * player1BMP;
	CBitmap * player1SBMP;
	CBitmap * player2BMP;
	CBitmap * player2SBMP;
	CBitmap * player1RBMP;
	CBitmap * player1RSBMP;
	CBitmap * player2RBMP;
	CBitmap * player2RSBMP;
	CBitmap * titleBMP;
	CBitmap * startGameBMP;
	CBitmap * selectBackBMP;
	CBitmap * selectPlayerBMP;
	CBitmap * oneToTwoBMP;
	CBitmap * oneToFourBMP;
	CBitmap * titleSBMP;
	CBitmap * startGameSBMP;
	CBitmap * selectBackSBMP;
	CBitmap * selectPlayerSBMP;
	CBitmap * oneToTwoSBMP;
	CBitmap * oneToFourSBMP;
	CBitmap * quitBMP;
	CBitmap * quitSBMP;
	CBitmap * shellBMP;
	CBitmap * shellSBMP;
	CBitmap * fish1LBMP;
	CBitmap * fish1LSBMP;
	CBitmap * fish1RBMP;
	CBitmap * fish1RSBMP;
	CBitmap * fish2LBMP;
	CBitmap * fish2LSBMP;
	CBitmap * fish2RBMP;
	CBitmap * fish2RSBMP;
	CBitmap * fish3LBMP;
	CBitmap * fish3LSBMP;
	CBitmap * fish3RBMP;
	CBitmap * fish3RSBMP;
	CBitmap * fish4LBMP;
	CBitmap * fish4LSBMP;
	CBitmap * fish4RBMP;
	CBitmap * fish4RSBMP;
	CBitmap * fish5LBMP;
	CBitmap * fish5LSBMP;
	CBitmap * fish5RBMP;
	CBitmap * fish5RSBMP;
	CBitmap * scoreBMP;
	CBitmap * scoreSBMP;
	CBitmap * lastScoreBMP;
	CBitmap * lastScoreSBMP;
	CBitmap * winBMP;
	CBitmap * winSBMP;
	CBitmap * failBMP;
	CBitmap * failSBMP;
	CBitmap * reStartBMP;
	CBitmap * reStartSBMP;
	CBitmap * yummyBMP;
	CBitmap * yummySBMP;
	CBitmap * levelBMP;
	CBitmap * levelSBMP;
	Fish1 fish1[5];
	Fish2 fish2[4];
	Fish3 fish3[3];
	Fish4 fish4[2];
	Fish5 fish5;
	CDC * mdc;
	CWinThread* myThread;
	CPoint lastPoint;
	RECT rect;
	int sleepTime = 50;
	int windWidth = 2560;
	int windHeight = 1440;
	int playerXPos = 1000;
	int playerYPos = 0;
	int playerNum = 1;
	int gameTime = 0;
	int shellTime = 0;
	int shellXPos = 0;
	int shellYPos = 1150;
	int points = 0;
	int yummyX;
	int yummyY;
	int yummyTime;
	int level; //1--4
	bool startedGame;
	bool finishedAction;
	bool inited = false;
	bool directionLeft = true;
	bool shellOut = false;
	bool exitMark = false;
	bool gameOver = false;
	bool ifWin = false;
	bool yummyExist = false;
	
	
public:
	CMyWnd() {
		rect;
		rect.bottom = windHeight;
		rect.top = 0;
		rect.left = 0;
		rect.right = windWidth;
		Create(NULL,"饥饿与进化", WS_DLGFRAME, rect);
		CClientDC dc(this);
		mdc = new CDC;
		mdc->CreateCompatibleDC(&dc);
	}
	
	VOID PaintScreen();
	VOID PaintStartScreen();
	VOID PaintEndScreen();
	VOID InitVaribles();
	VOID CheckCrash();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
};

class CMyApp : public CWinApp {
	BOOL InitInstance();
};

CMyApp TheApp;
CMyWnd *pf;

UINT myProc(LPVOID pParam) {
	pf->InitVaribles();
	pf->inited = true;
	while (1) {
		if (!pf->inited) {
			pf->InitVaribles();
			pf->inited = true;
		}
		if (pf->startedGame && !pf->gameOver) {
			if (!pf->finishedAction) {
				pf->playerYPos += 25;
				if (pf->playerYPos > 700) {
					pf->finishedAction = true;
				}
			}
			pf->PaintScreen();
		}else if (pf->startedGame && pf->gameOver) {
			pf->PaintEndScreen();
		}
		else if (!pf->startedGame) {
			pf->PaintStartScreen();
		}

		Sleep(pf->sleepTime);
		if (pf->startedGame && !pf->gameOver) {
			pf->CheckCrash();
			pf->gameTime += pf->sleepTime;
			if (pf->gameTime >= 20000) {
				pf->gameTime = 0;
			}
			
			if (pf->gameTime == 2500) {//3.1 1.2
				for (int j = 0, i = 0; j < 5; j++) {
					if (!pf->fish1[j].exist) {
						pf->fish1[j].exist = true;
						i++;
						srand((int)time(0) + j);
						pf->fish1[j].direction = rand() % 2 + 1;
						if (pf->fish1[j].direction == 1) {
							pf->fish1[j].xCen = -200;
							pf->fish1[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish1[j].fishBMP = pf->fish1RBMP;
							pf->fish1[j].fishSBMP = pf->fish1RSBMP;
						}
						else if (pf->fish1[j].direction == 2) {
							pf->fish1[j].xCen = 2700;
							pf->fish1[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish1[j].fishBMP = pf->fish1LBMP;
							pf->fish1[j].fishSBMP = pf->fish1LSBMP;
						}
					}
					if (i == 3) {
						break;
					}
				}
				for (int j = 0, i = 0; j < 4; j++) {
					if (!pf->fish2[j].exist) {
						pf->fish2[j].exist = true;
						i++;
						srand((int)time(0)+j*2);
						pf->fish2[j].direction = rand() % 2 + 1;
						if (pf->fish2[j].direction == 1) {
							pf->fish2[j].xCen = -200;
							pf->fish2[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish2[j].fishBMP = pf->fish2RBMP;
							pf->fish2[j].fishSBMP = pf->fish2RSBMP;
						}
						else if (pf->fish2[j].direction == 2) {
							pf->fish2[j].xCen = 2700;
							pf->fish2[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish2[j].fishBMP = pf->fish2LBMP;
							pf->fish2[j].fishSBMP = pf->fish2LSBMP;
						}
					}
					if (i == 1) {
						break;
					}
				}
			}
			else if (pf->gameTime == 7500 ) {//2.1 2.2 1.3
				for (int j = 0, i = 0; j < 5; j++) {
					if (!pf->fish1[j].exist) {
						pf->fish1[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish1[j].direction = rand() % 2 + 1;
						if (pf->fish1[j].direction == 1) {
							pf->fish1[j].xCen = -200;
							pf->fish1[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish1[j].fishBMP = pf->fish1RBMP;
							pf->fish1[j].fishSBMP = pf->fish1RSBMP;
						}
						else if (pf->fish1[j].direction == 2) {
							pf->fish1[j].xCen = 2700;
							pf->fish1[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish1[j].fishBMP = pf->fish1LBMP;
							pf->fish1[j].fishSBMP = pf->fish1LSBMP;
						}
					}
					if (i == 2) {
						break;
					}
				}
				for (int j = 0, i = 0; j < 4; j++) {
					if (!pf->fish2[j].exist) {
						pf->fish2[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish2[j].direction = rand() % 2 + 1;
						if (pf->fish2[j].direction == 1) {
							pf->fish2[j].xCen = -200;
							pf->fish2[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish2[j].fishBMP = pf->fish2RBMP;
							pf->fish2[j].fishSBMP = pf->fish2RSBMP;
						}
						else if (pf->fish2[j].direction == 2) {
							pf->fish2[j].xCen = 2700;
							pf->fish2[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish2[j].fishBMP = pf->fish2LBMP;
							pf->fish2[j].fishSBMP = pf->fish2LSBMP;
						}
					}
					if (i == 2) {
						break;
					}
				}
				for (int j = 0, i = 0; j < 3; j++) {
					if (!pf->fish3[j].exist) {
						pf->fish3[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish3[j].direction = rand() % 2 + 1;
						if (pf->fish3[j].direction == 1) {
							pf->fish3[j].xCen = -200;
							pf->fish3[j].yCen = (rand() % 10 + 1) * 100+100;
							pf->fish3[j].fishBMP = pf->fish3RBMP;
							pf->fish3[j].fishSBMP = pf->fish3RSBMP;
						}
						else if (pf->fish3[j].direction == 2) {
							pf->fish3[j].xCen = 2700;
							pf->fish3[j].yCen = (rand() % 10 + 1) * 100+100;
							pf->fish3[j].fishBMP = pf->fish3LBMP;
							pf->fish3[j].fishSBMP = pf->fish3LSBMP;
						}
					}
					if (i == 2) {
						break;
					}
				}
			}
			else if (pf->gameTime == 12500) { // 1.2 1.3 1.4
				for (int j = 0, i = 0; j < 4; j++) {
					if (!pf->fish2[j].exist) {
						pf->fish2[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish2[j].direction = rand() % 2 + 1;
						if (pf->fish2[j].direction == 1) {
							pf->fish2[j].xCen = -200;
							pf->fish2[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish2[j].fishBMP = pf->fish2RBMP;
							pf->fish2[j].fishSBMP = pf->fish2RSBMP;
						}
						else if (pf->fish2[j].direction == 2) {
							pf->fish2[j].xCen = 2700;
							pf->fish2[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish2[j].fishBMP = pf->fish2LBMP;
							pf->fish2[j].fishSBMP = pf->fish2LSBMP;
						}
					}
					if (i == 1) {
						break;
					}
				}
				for (int j = 0, i = 0; j < 3; j++) {
					if (!pf->fish3[j].exist) {
						pf->fish3[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish3[j].direction = rand() % 2 + 1;
						if (pf->fish3[j].direction == 1) {
							pf->fish3[j].xCen = -200;
							pf->fish3[j].yCen = (rand() % 10 + 1) * 100+100;
							pf->fish3[j].fishBMP = pf->fish3RBMP;
							pf->fish3[j].fishSBMP = pf->fish3RSBMP;
						}
						else if (pf->fish3[j].direction == 2) {
							pf->fish3[j].xCen = 2700;
							pf->fish3[j].yCen = (rand() % 10 + 1) * 100+100;
							pf->fish3[j].fishBMP = pf->fish3LBMP;
							pf->fish3[j].fishSBMP = pf->fish3LSBMP;
						}
					}
					if (i == 1) {
						break;
					}
				}
				for (int j = 0, i = 0; j < 2; j++) {
					if (!pf->fish4[j].exist) {
						pf->fish4[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish4[j].direction = rand() % 2 + 1;
						if (pf->fish4[j].direction == 1) {
							pf->fish4[j].xCen = -200;
							pf->fish4[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish4[j].fishBMP = pf->fish4RBMP;
							pf->fish4[j].fishSBMP = pf->fish4RSBMP;
						}
						else if (pf->fish4[j].direction == 2) {
							pf->fish4[j].xCen = 2700;
							pf->fish4[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish4[j].fishBMP = pf->fish4LBMP;
							pf->fish4[j].fishSBMP = pf->fish4LSBMP;
						}
					}
					if (i == 1) {
						break;
					}
				}
			}
			else if (pf->gameTime == 17500) { // 1.3 1.4 1.5
				for (int j = 0, i = 0; j < 3; j++) {
					if (!pf->fish3[j].exist) {
						pf->fish3[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish3[j].direction = rand() % 2 + 1;
						if (pf->fish3[j].direction == 1) {
							pf->fish3[j].xCen = -200;
							pf->fish3[j].yCen = (rand() % 10 + 1) * 100+100;
							pf->fish3[j].fishBMP = pf->fish3RBMP;
							pf->fish3[j].fishSBMP = pf->fish3RSBMP;
						}
						else if (pf->fish3[j].direction == 2) {
							pf->fish3[j].xCen = 2700;
							pf->fish3[j].yCen = (rand() % 10 + 1) * 100+100;
							pf->fish3[j].fishBMP = pf->fish3LBMP;
							pf->fish3[j].fishSBMP = pf->fish3LSBMP;
						}
					}
					if (i == 1) {
						break;
					}
				}
				for (int j = 0, i = 0; j < 2; j++) {
					if (!pf->fish4[j].exist) {
						pf->fish4[j].exist = true;
						i++;
						srand((int)time(0)+j);
						pf->fish4[j].direction = rand() % 2 + 1;
						if (pf->fish4[j].direction == 1) {
							pf->fish4[j].xCen = -200;
							pf->fish4[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish4[j].fishBMP = pf->fish4RBMP;
							pf->fish4[j].fishSBMP = pf->fish4RSBMP;
						}
						else if (pf->fish4[j].direction == 2) {
							pf->fish4[j].xCen = 2700;
							pf->fish4[j].yCen = (rand() % 10 + 1) * 100;
							pf->fish4[j].fishBMP = pf->fish4LBMP;
							pf->fish4[j].fishSBMP = pf->fish4LSBMP;
						}
					}
					if (i == 1) {
						break;
					}
				}
				if (!pf->fish5.exist) {
					pf->fish5.exist = true;
					srand((int)time(0));
					pf->fish5.direction = rand() % 2 + 1;
					if (pf->fish5.direction == 1) {
						pf->fish5.xCen = -200;
						pf->fish5.yCen = (rand() % 10 + 1) * 100;
						pf->fish5.fishBMP = pf->fish5RBMP;
						pf->fish5.fishSBMP = pf->fish5RSBMP;
					}
					else if (pf->fish5.direction == 2) {
						pf->fish5.xCen = 2700;
						pf->fish5.yCen = (rand() % 10 + 1) * 100;
						pf->fish5.fishBMP = pf->fish5LBMP;
						pf->fish5.fishSBMP = pf->fish5LSBMP;
					}
				}
				
			}
			//MoveFish
			for (int i = 0; i < 5; i++) {
				if (pf->fish1[i].exist) {
					if (pf->fish1[i].direction == 1) {
						pf->fish1[i].xCen += pf->fish1[i].speed;
					}
					else if (pf->fish1[i].direction == 2) {
						pf->fish1[i].xCen -= pf->fish1[i].speed;
					}
					
					if (pf->fish1[i].xCen < -900 || pf->fish1[i].xCen > 3500) {
						pf->fish1[i].exist = false;
					}
				}
			}
			for (int i = 0; i < 4; i++) {
				if (pf->fish2[i].exist) {
					if (pf->fish2[i].direction == 1) {
						pf->fish2[i].xCen += pf->fish2[i].speed;
					}
					else if (pf->fish2[i].direction == 2) {
						pf->fish2[i].xCen -= pf->fish2[i].speed;
					}

					if (pf->fish2[i].xCen < -900 || pf->fish2[i].xCen > 3500) {
						pf->fish2[i].exist = false;
					}
				}
			}
			for (int i = 0; i < 3; i++) {
				if (pf->fish3[i].exist) {
					if (pf->fish3[i].direction == 1) {
						pf->fish3[i].xCen += pf->fish3[i].speed;
					}
					else if (pf->fish3[i].direction == 2) {
						pf->fish3[i].xCen -= pf->fish3[i].speed;
					}

					if (pf->fish3[i].xCen < -900 || pf->fish3[i].xCen > 3500) {
						pf->fish3[i].exist = false;
					}
				}
			}
			for (int i = 0; i < 2; i++) {
				if (pf->fish4[i].exist) {
					if (pf->fish4[i].direction == 1) {
						pf->fish4[i].xCen += pf->fish4[i].speed;
					}
					else if (pf->fish4[i].direction == 2) {
						pf->fish4[i].xCen -= pf->fish4[i].speed;
					}

					if (pf->fish4[i].xCen < -900 || pf->fish4[i].xCen > 3500) {
						pf->fish4[i].exist = false;
					}
				}
			}
			if (pf->fish5.exist) {
				if (pf->fish5.direction == 1) {
					pf->fish5.xCen += pf->fish5.speed;
				}
				else if (pf->fish5.direction == 2) {
					pf->fish5.xCen -= pf->fish5.speed;
				}

				if (pf->fish5.xCen < -900 || pf->fish5.xCen > 3500) {
					pf->fish5.exist = false;
				}
			}

			
			if (pf->yummyExist) {
				pf->yummyTime += pf->sleepTime;
				if (pf->yummyTime >= 400) {
					pf->yummyExist = false;
					pf->yummyTime = 0;
				}
			}
			if (!pf->shellOut) {
				pf->shellTime += pf->sleepTime;
				if (pf->shellTime >= 15000) {
					pf->shellTime = 0;
					pf->shellOut = true;
					srand((int)time(0));
					pf->shellXPos = (rand() % 10 + 1) * 200;
				}
			}
		}
		if (pf->exitMark) {
			return 0;
		}
	}
}

BOOL CMyApp::InitInstance() {
	pf = new CMyWnd;
	pf->ShowWindow(m_nCmdShow);
	pf->UpdateWindow();
	m_pMainWnd = pf;

	pf->myThread = AfxBeginThread(myProc, NULL);
	PlaySound("music.wav", NULL, SND_ASYNC|SND_LOOP|SND_FILENAME);


	return TRUE;
}

VOID CMyWnd::PaintScreen() {
	CClientDC dc(this);
	CDC *mdcBuffer = new CDC;
	mdcBuffer->CreateCompatibleDC(&dc);
	CBitmap * bmpBuffer = new CBitmap;
	bmpBuffer->CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	mdcBuffer->SelectObject(bmpBuffer);

	mdc->SelectObject(backGroundBMP);
	mdcBuffer->BitBlt(0, 0, windWidth, windHeight, mdc, 0, 0, SRCCOPY);

	//显示分数
	mdc->SelectObject(levelSBMP);
	mdcBuffer->BitBlt(600, -25, 150, 150, mdc, 0, 0, SRCAND);
	mdc->SelectObject(levelBMP);
	mdcBuffer->BitBlt(600, -25, 150, 150, mdc, 0, 0, SRCPAINT);
	char levelToDisplay[100];
	sprintf_s(levelToDisplay, "%d      (Press ESC To Exit)", level);
	mdcBuffer->SelectObject(CreateFont(-100 ,-50, 0, 0, 
		1000, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS, 
		CLIP_DEFAULT_PRECIS, VARIABLE_PITCH | PROOF_QUALITY, FF_DONTCARE, "宋体"));
	mdcBuffer->SetTextColor(200);
	SetBkMode(*mdcBuffer, TRANSPARENT);
	mdcBuffer->TextOutA(750, 0, levelToDisplay);

	mdc->SelectObject(scoreSBMP);
	mdcBuffer->BitBlt(0, 0, 300, 100, mdc, 0, 0, SRCAND);
	mdc->SelectObject(scoreBMP);
	mdcBuffer->BitBlt(0, 0, 300, 100, mdc, 0, 0, SRCPAINT);
	char pointsToDisplay[20];
	sprintf_s(pointsToDisplay, "%d", points);
	mdcBuffer->SelectObject(CreateFont(-100, -50, 0, 0,
		1000, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS,
		CLIP_DEFAULT_PRECIS, VARIABLE_PITCH | PROOF_QUALITY, FF_DONTCARE, "宋体"));
	mdcBuffer->SetTextColor(200);
	SetBkMode(*mdcBuffer, TRANSPARENT);
	mdcBuffer->TextOutA(300, 0, pointsToDisplay);

	if (playerNum == 1 && directionLeft) {
		mdc->SelectObject(player1SBMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCAND);

		mdc->SelectObject(player1BMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCPAINT);
	}
	else if (playerNum == 1 && !directionLeft) {
		mdc->SelectObject(player1RSBMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCAND);

		mdc->SelectObject(player1RBMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCPAINT);
	}
	else if (playerNum == 2 && directionLeft) {
		mdc->SelectObject(player2SBMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCAND);

		mdc->SelectObject(player2BMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCPAINT);
	}
	else if (playerNum == 2 && !directionLeft) {
		mdc->SelectObject(player2RSBMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCAND);

		mdc->SelectObject(player2RBMP);
		mdcBuffer->BitBlt(playerXPos, playerYPos, 400, 400, mdc, 0, 0, SRCPAINT);
	}

	if (shellOut) {
		mdc->SelectObject(shellSBMP);
		mdcBuffer->BitBlt(shellXPos, shellYPos, 200, 200, mdc, 0, 0, SRCAND);

		mdc->SelectObject(shellBMP);
		mdcBuffer->BitBlt(shellXPos, shellYPos, 200, 200, mdc, 0, 0, SRCPAINT);
	}

	if (yummyExist) {
		mdc->SelectObject(yummySBMP);
		mdcBuffer->BitBlt(yummyX, yummyY, 400, 400, mdc, 0, 0, SRCAND);

		mdc->SelectObject(yummyBMP);
		mdcBuffer->BitBlt(yummyX, yummyY, 400, 400, mdc, 0, 0, SRCPAINT);
	}

	for (int i = 0; i < 5; i++) {
		if (pf->fish1[i].exist) {
			mdc->SelectObject(fish1[i].fishSBMP);
			mdcBuffer->BitBlt(fish1[i].xCen-80, fish1[i].yCen-100, 160, 200, mdc, 0, 0, SRCAND);

			mdc->SelectObject(fish1[i].fishBMP);
			mdcBuffer->BitBlt(fish1[i].xCen - 80, fish1[i].yCen - 100, 160, 200, mdc, 0, 0, SRCPAINT);
		}
	}
	
	for (int i = 0; i < 4; i++) {
		if (pf->fish2[i].exist) {
			mdc->SelectObject(fish2[i].fishSBMP);
			mdcBuffer->BitBlt(fish2[i].xCen - 100, fish2[i].yCen - 100, 200, 200, mdc, 0, 0, SRCAND);

			mdc->SelectObject(fish2[i].fishBMP);
			mdcBuffer->BitBlt(fish2[i].xCen - 100, fish2[i].yCen - 100, 200, 200, mdc, 0, 0, SRCPAINT);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (pf->fish3[i].exist) {
			mdc->SelectObject(fish3[i].fishSBMP);
			mdcBuffer->BitBlt(fish3[i].xCen - 200, fish3[i].yCen - 200, 400, 400, mdc, 0, 0, SRCAND);

			mdc->SelectObject(fish3[i].fishBMP);
			mdcBuffer->BitBlt(fish3[i].xCen - 200, fish3[i].yCen - 200, 400, 400, mdc, 0, 0, SRCPAINT);
		}
	}
	for (int i = 0; i < 2; i++) {
		if (pf->fish4[i].exist) {
			mdc->SelectObject(fish4[i].fishSBMP);
			mdcBuffer->BitBlt(fish4[i].xCen - (500 - 200 * (pf->fish4[i].direction - 2)), fish4[i].yCen - 300, 1000, 500, mdc, 0, 0, SRCAND);

			mdc->SelectObject(fish4[i].fishBMP);
			mdcBuffer->BitBlt(fish4[i].xCen - (500 - 200*(pf->fish4[i].direction-2)), fish4[i].yCen - 300, 1000, 500, mdc, 0, 0, SRCPAINT);
		}
	}
	if (pf->fish5.exist) {
		mdc->SelectObject(fish5.fishSBMP);
		mdcBuffer->BitBlt(fish5.xCen - 300, fish5.yCen - 300, 600, 600, mdc, 0, 0, SRCAND);

		mdc->SelectObject(fish5.fishBMP);
		mdcBuffer->BitBlt(fish5.xCen - 300, fish5.yCen - 300, 600, 600, mdc, 0, 0, SRCPAINT);
	}
	

	dc.BitBlt(0, 0, rect.right, rect.bottom, mdcBuffer, 0, 0, SRCCOPY);
}

VOID CMyWnd::PaintStartScreen() {
	CClientDC dc(this);
	CDC *mdcBuffer = new CDC;
	mdcBuffer->CreateCompatibleDC(&dc);
	CBitmap * bmpBuffer = new CBitmap;
	bmpBuffer->CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	mdcBuffer->SelectObject(bmpBuffer);

	mdc->SelectObject(startBackGroundBMP);
	mdcBuffer->BitBlt(0, 0, windWidth, windHeight, mdc, 0, 0, SRCCOPY);

	mdc->SelectObject(titleSBMP);
	mdcBuffer->BitBlt(618, 100, 1336, 356, mdc, 0, 0, SRCAND);
	mdc->SelectObject(titleBMP);
	mdcBuffer->BitBlt(618, 100, 1336, 356, mdc, 0, 0, SRCPAINT);

	mdc->SelectObject(startGameSBMP);
	mdcBuffer->BitBlt(1052, 500, 456, 149, mdc, 0, 0, SRCAND);
	mdc->SelectObject(startGameBMP);
	mdcBuffer->BitBlt(1052, 500, 456, 149, mdc, 0, 0, SRCPAINT);

	mdc->SelectObject(selectBackSBMP);
	mdcBuffer->BitBlt(800, 700, 444, 149, mdc, 0, 0, SRCAND);
	mdc->SelectObject(selectBackBMP);
	mdcBuffer->BitBlt(800, 700, 444, 149, mdc, 0, 0, SRCPAINT);

	mdc->SelectObject(oneToFourSBMP);
	mdcBuffer->BitBlt(1300, 700, 554, 127, mdc, 0, 0, SRCAND);
	mdc->SelectObject(oneToFourBMP);
	mdcBuffer->BitBlt(1300, 700, 554, 127, mdc, 0, 0, SRCPAINT);

	mdc->SelectObject(selectPlayerSBMP);
	mdcBuffer->BitBlt(800, 900, 429, 140, mdc, 0, 0, SRCAND);
	mdc->SelectObject(selectPlayerBMP);
	mdcBuffer->BitBlt(800, 900, 429, 140, mdc, 0, 0, SRCPAINT);

	mdc->SelectObject(oneToTwoSBMP);
	mdcBuffer->BitBlt(1300, 900, 311, 132, mdc, 0, 0, SRCAND);
	mdc->SelectObject(oneToTwoBMP);
	mdcBuffer->BitBlt(1300, 900, 311, 132, mdc, 0, 0, SRCPAINT);

	mdc->SelectObject(quitSBMP);
	mdcBuffer->BitBlt(1075, 1100, 390, 130, mdc, 0, 0, SRCAND);
	mdc->SelectObject(quitBMP);
	mdcBuffer->BitBlt(1075, 1100, 390, 130, mdc, 0, 0, SRCPAINT);

	dc.BitBlt(0, 0, rect.right, rect.bottom, mdcBuffer, 0, 0, SRCCOPY);
}

VOID CMyWnd::PaintEndScreen() {
	CClientDC dc(this);
	CDC *mdcBuffer = new CDC;
	mdcBuffer->CreateCompatibleDC(&dc);
	CBitmap * bmpBuffer = new CBitmap;
	bmpBuffer->CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	mdcBuffer->SelectObject(bmpBuffer);

	mdc->SelectObject(backGroundBMP);
	mdcBuffer->BitBlt(0, 0, windWidth, windHeight, mdc, 0, 0, SRCCOPY);

	if (ifWin) {
		mdc->SelectObject(winSBMP);
		mdcBuffer->BitBlt(800, 100, 1000, 500, mdc, 0, 0, SRCAND);
		mdc->SelectObject(winBMP);
		mdcBuffer->BitBlt(800, 100, 1000, 500, mdc, 0, 0, SRCPAINT);

	}
	else if (!ifWin) {
		mdc->SelectObject(failSBMP);
		mdcBuffer->BitBlt(800, 0, 1000, 750, mdc, 0, 0, SRCAND);
		mdc->SelectObject(failBMP);
		mdcBuffer->BitBlt(800, 0, 1000, 750, mdc, 0, 0, SRCPAINT);
	}

	mdc->SelectObject(lastScoreSBMP);
	mdcBuffer->BitBlt(940, 600, 400, 200, mdc, 0, 0, SRCAND);
	mdc->SelectObject(lastScoreBMP);
	mdcBuffer->BitBlt(940, 600, 400, 200, mdc, 0, 0, SRCPAINT);
	char pointsToDisplay[20];
	sprintf_s(pointsToDisplay, "%d", points);
	mdcBuffer->SelectObject(CreateFont(-100, -50, 0, 0,
		1000, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS,
		CLIP_DEFAULT_PRECIS, VARIABLE_PITCH | PROOF_QUALITY, FF_DONTCARE, "宋体"));
	mdcBuffer->SetTextColor(200);
	SetBkMode(*mdcBuffer, TRANSPARENT);
	mdcBuffer->TextOutA(1380, 700, pointsToDisplay);

	mdc->SelectObject(reStartSBMP);
	mdcBuffer->BitBlt(1052, 900, 450, 150, mdc, 0, 0, SRCAND);
	mdc->SelectObject(reStartBMP);
	mdcBuffer->BitBlt(1052, 900, 450, 150, mdc, 0, 0, SRCPAINT);

	mdc->SelectObject(quitSBMP);
	mdcBuffer->BitBlt(1075, 1100, 390, 130, mdc, 0, 0, SRCAND);
	mdc->SelectObject(quitBMP);
	mdcBuffer->BitBlt(1075, 1100, 390, 130, mdc, 0, 0, SRCPAINT);

	dc.BitBlt(0, 0, rect.right, rect.bottom, mdcBuffer, 0, 0, SRCCOPY);
}

VOID CMyWnd::InitVaribles() {
	backGroundBMP = new CBitmap;
	startBackGroundBMP = new CBitmap;
	player1BMP = new CBitmap;
	player1SBMP = new CBitmap;
	player2BMP = new CBitmap;
	player2SBMP = new CBitmap;
	player1RBMP = new CBitmap;
	player1RSBMP = new CBitmap;
	player2RBMP = new CBitmap;
	player2RSBMP = new CBitmap;
	titleBMP = new CBitmap;
	startGameBMP = new CBitmap;
	selectBackBMP = new CBitmap;
	selectPlayerBMP = new CBitmap;
	oneToTwoBMP = new CBitmap;
	oneToFourBMP = new CBitmap;
	titleSBMP = new CBitmap;
	startGameSBMP = new CBitmap;
	selectBackSBMP = new CBitmap;
	selectPlayerSBMP = new CBitmap;
	oneToTwoSBMP = new CBitmap;
	oneToFourSBMP = new CBitmap;
	quitBMP = new CBitmap;
	quitSBMP = new CBitmap;
	shellBMP = new CBitmap;
	shellSBMP = new CBitmap;
	fish1LBMP = new CBitmap;
	fish1LSBMP = new CBitmap;
	fish1RBMP = new CBitmap;
	fish1RSBMP = new CBitmap;
	fish2LBMP = new CBitmap;
	fish2LSBMP = new CBitmap;
	fish2RBMP = new CBitmap;
	fish2RSBMP = new CBitmap;
	fish3LBMP = new CBitmap;
	fish3LSBMP = new CBitmap;
	fish3RBMP = new CBitmap;
	fish3RSBMP = new CBitmap;
	fish4LBMP = new CBitmap;
	fish4LSBMP = new CBitmap;
	fish4RBMP = new CBitmap;
	fish4RSBMP = new CBitmap;
	fish5LBMP = new CBitmap;
	fish5LSBMP = new CBitmap;
	fish5RBMP = new CBitmap;
	fish5RSBMP = new CBitmap;
	scoreBMP = new CBitmap;
	scoreSBMP = new CBitmap;
	lastScoreBMP = new CBitmap;
	lastScoreSBMP = new CBitmap;
	winBMP = new CBitmap;
	winSBMP = new CBitmap;
	failBMP = new CBitmap;
	failSBMP = new CBitmap;
	reStartBMP = new CBitmap;
	reStartSBMP = new CBitmap;
	fish5.fishBMP = new CBitmap;
	fish5.fishSBMP = new CBitmap;
	yummyBMP = new CBitmap;
	yummySBMP = new CBitmap;
	levelBMP = new CBitmap;
	levelSBMP = new CBitmap;
	fish5.exist = false;
	fish5.speed = 50;
	fish5.len = 300;
	for (int i = 0; i < 2; i++) {
		fish4[i].fishBMP = new CBitmap;
		fish4[i].fishSBMP = new CBitmap;
		fish4[i].exist = false;
		fish4[i].len = 150;
		fish4[i].speed = 40;
	}
	for (int i = 0; i < 3; i++) {
		fish3[i].fishBMP = new CBitmap;
		fish3[i].fishSBMP = new CBitmap;
		fish3[i].exist = false;
		fish3[i].len = 100;
		fish3[i].speed = 30;
	}
	for (int i = 0; i < 4; i++) {
		fish2[i].fishBMP = new CBitmap;
		fish2[i].fishSBMP = new CBitmap; 
		fish2[i].exist = false;
		fish2[i].len = 75;
		fish2[i].speed = 20;
	}
	for (int i = 0; i < 5; i++) {
		fish1[i].fishBMP = new CBitmap;
		fish1[i].fishSBMP = new CBitmap;
		fish1[i].exist = false;
		fish1[i].len = 60;
		fish1[i].speed = 20;
	}

	backGroundBMP->m_hObject = LoadImage(NULL, "backGround2.bmp", IMAGE_BITMAP, windWidth, windHeight, LR_LOADFROMFILE);
	startBackGroundBMP->m_hObject = LoadImage(NULL, "backGround2.bmp", IMAGE_BITMAP, windWidth, windHeight, LR_LOADFROMFILE);
	player1BMP->m_hObject = LoadImage(NULL, "player.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	player1SBMP->m_hObject = LoadImage(NULL, "playerS.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	player2BMP->m_hObject = LoadImage(NULL, "player2.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	player2SBMP->m_hObject = LoadImage(NULL, "player2S.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	player1RBMP->m_hObject = LoadImage(NULL, "playerR.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	player1RSBMP->m_hObject = LoadImage(NULL, "playerRS.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	player2RBMP->m_hObject = LoadImage(NULL, "player2R.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	player2RSBMP->m_hObject = LoadImage(NULL, "player2RS.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);

	titleBMP->m_hObject = LoadImage(NULL, "Title.bmp", IMAGE_BITMAP, 1336, 356, LR_LOADFROMFILE);
	startGameBMP->m_hObject = LoadImage(NULL, "startGame.bmp", IMAGE_BITMAP, 456, 149, LR_LOADFROMFILE);
	selectBackBMP->m_hObject = LoadImage(NULL, "backSelect.bmp", IMAGE_BITMAP, 444, 149, LR_LOADFROMFILE);
	selectPlayerBMP->m_hObject = LoadImage(NULL, "playerSelect.bmp", IMAGE_BITMAP, 429, 140, LR_LOADFROMFILE);
	oneToTwoBMP->m_hObject = LoadImage(NULL, "oneToTwo.bmp", IMAGE_BITMAP, 311, 132, LR_LOADFROMFILE);
	oneToFourBMP->m_hObject = LoadImage(NULL, "oneToFour.bmp", IMAGE_BITMAP, 554, 127, LR_LOADFROMFILE);
	quitBMP->m_hObject = LoadImage(NULL, "quit.bmp", IMAGE_BITMAP, 390, 130, LR_LOADFROMFILE);
	titleSBMP->m_hObject = LoadImage(NULL, "TitleS.bmp", IMAGE_BITMAP, 1336, 356, LR_LOADFROMFILE);
	startGameSBMP->m_hObject = LoadImage(NULL, "startGameS.bmp", IMAGE_BITMAP, 456, 149, LR_LOADFROMFILE);
	selectBackSBMP->m_hObject = LoadImage(NULL, "backSelectS.bmp", IMAGE_BITMAP, 444, 149, LR_LOADFROMFILE);
	selectPlayerSBMP->m_hObject = LoadImage(NULL, "playerSelectS.bmp", IMAGE_BITMAP, 429, 140, LR_LOADFROMFILE);
	oneToTwoSBMP->m_hObject = LoadImage(NULL, "oneToTwoS.bmp", IMAGE_BITMAP, 311, 132, LR_LOADFROMFILE);
	oneToFourSBMP->m_hObject = LoadImage(NULL, "oneToFourS.bmp", IMAGE_BITMAP, 554, 127, LR_LOADFROMFILE);
	quitSBMP->m_hObject = LoadImage(NULL, "quitS.bmp", IMAGE_BITMAP, 390, 130, LR_LOADFROMFILE);

	shellBMP->m_hObject = LoadImage(NULL, "shell.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	shellSBMP->m_hObject = LoadImage(NULL, "shellS.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	fish1LBMP->m_hObject = LoadImage(NULL, "fish1L.bmp", IMAGE_BITMAP, 160, 200, LR_LOADFROMFILE);
	fish1LSBMP->m_hObject = LoadImage(NULL, "fish1LS.bmp", IMAGE_BITMAP, 160, 200, LR_LOADFROMFILE);
	fish1RBMP->m_hObject = LoadImage(NULL, "fish1R.bmp", IMAGE_BITMAP, 160, 200, LR_LOADFROMFILE);
	fish1RSBMP->m_hObject = LoadImage(NULL, "fish1RS.bmp", IMAGE_BITMAP, 160, 200, LR_LOADFROMFILE);
	fish2LBMP->m_hObject = LoadImage(NULL, "fish2L.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	fish2LSBMP->m_hObject = LoadImage(NULL, "fish2LS.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	fish2RBMP->m_hObject = LoadImage(NULL, "fish2R.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	fish2RSBMP->m_hObject = LoadImage(NULL, "fish2RS.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
	fish3LBMP->m_hObject = LoadImage(NULL, "fish3L.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	fish3LSBMP->m_hObject = LoadImage(NULL, "fish3LS.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	fish3RBMP->m_hObject = LoadImage(NULL, "fish3R.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	fish3RSBMP->m_hObject = LoadImage(NULL, "fish3RS.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	fish4LBMP->m_hObject = LoadImage(NULL, "fish4L.bmp", IMAGE_BITMAP, 1000, 500, LR_LOADFROMFILE);
	fish4LSBMP->m_hObject = LoadImage(NULL, "fish4LS.bmp", IMAGE_BITMAP, 1000, 500, LR_LOADFROMFILE);
	fish4RBMP->m_hObject = LoadImage(NULL, "fish4R.bmp", IMAGE_BITMAP, 1000, 500, LR_LOADFROMFILE);
	fish4RSBMP->m_hObject = LoadImage(NULL, "fish4RS.bmp", IMAGE_BITMAP, 1000, 500, LR_LOADFROMFILE);
	fish5LBMP->m_hObject = LoadImage(NULL, "fish5L.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);;
	fish5LSBMP->m_hObject = LoadImage(NULL, "fish5LS.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
	fish5RBMP->m_hObject = LoadImage(NULL, "fish5R.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
	fish5RSBMP->m_hObject = LoadImage(NULL, "fish5RS.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
	scoreBMP->m_hObject = LoadImage(NULL, "score.bmp", IMAGE_BITMAP, 300, 100, LR_LOADFROMFILE);
	scoreSBMP->m_hObject = LoadImage(NULL, "scoreS.bmp", IMAGE_BITMAP, 300, 100, LR_LOADFROMFILE);

	lastScoreBMP->m_hObject = LoadImage(NULL, "lastScore.bmp", IMAGE_BITMAP, 400, 200, LR_LOADFROMFILE);
	lastScoreSBMP->m_hObject = LoadImage(NULL, "lastScoreS.bmp", IMAGE_BITMAP, 400, 200, LR_LOADFROMFILE);
	winBMP->m_hObject = LoadImage(NULL, "win.bmp", IMAGE_BITMAP, 1000, 500, LR_LOADFROMFILE);
	winSBMP->m_hObject = LoadImage(NULL, "winS.bmp", IMAGE_BITMAP, 1000, 500, LR_LOADFROMFILE);
	failBMP->m_hObject = LoadImage(NULL, "fail.bmp", IMAGE_BITMAP, 1000, 750, LR_LOADFROMFILE);
	failSBMP->m_hObject = LoadImage(NULL, "failS.bmp", IMAGE_BITMAP, 1000, 750, LR_LOADFROMFILE);
	reStartBMP->m_hObject = LoadImage(NULL, "restart.bmp", IMAGE_BITMAP, 450, 150, LR_LOADFROMFILE);
	reStartSBMP->m_hObject = LoadImage(NULL, "restartS.bmp", IMAGE_BITMAP, 450, 150, LR_LOADFROMFILE);
	yummyBMP->m_hObject = LoadImage(NULL, "yummy.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	yummySBMP->m_hObject = LoadImage(NULL, "yummyS.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	levelBMP->m_hObject = LoadImage(NULL, "level.bmp", IMAGE_BITMAP, 150, 150, LR_LOADFROMFILE);
	levelSBMP->m_hObject = LoadImage(NULL, "levelS.bmp", IMAGE_BITMAP, 150, 150, LR_LOADFROMFILE);

	startedGame = false;
	finishedAction = false;
	playerYPos = 0;
	playerXPos = 1000;
	lastPoint.x = playerXPos;
	lastPoint.y = playerYPos;
	directionLeft = true;
	playerNum = 1;
	gameTime = 0;
	shellOut = false;
	shellTime = 0;
	shellXPos = 0;
	shellYPos = 1150;
	yummyX = -400;
	yummyY = -400;
	yummyTime = 0;
	level = 1;

	points = 0;
	exitMark = false;
	gameOver = false;
	ifWin = false;
}

VOID CMyWnd::CheckCrash() {
	int playerCenterX;
	int playerCenterY;
	int playerLen;
	if (playerNum == 1) {
		playerLen = 100;
		if (directionLeft) {
			playerCenterX = playerXPos - 50;
			playerCenterY = playerYPos;
		}
		else {
			playerCenterX = playerXPos + 100;
			playerCenterY = playerYPos;
		}
	}
	else if (playerNum == 2) {
		playerLen = 100;
		if (directionLeft) {
			playerCenterX = playerXPos -50;
			playerCenterY = playerYPos;
		}
		else {
			playerCenterX = playerXPos + 100;
			playerCenterY = playerYPos;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (pf->fish1[i].exist) {
			if (pow((playerLen + fish1[i].len), 2) >= (pow(abs(playerCenterX - fish1[i].xCen+150), 2) + pow(abs(playerCenterY - fish1[i].yCen + 150), 2))) {
				fish1[i].exist = false;
				yummyExist = true;
				yummyX = (playerCenterX + fish1[i].xCen + 150)/2 -150;
				yummyY = (playerCenterY + fish1[i].yCen + 150) / 2 -200;
				points += 50;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (pf->fish2[i].exist) {
			if (pow((playerLen + fish2[i].len), 2) >= (pow(abs(playerCenterX - fish2[i].xCen + 150), 2) + pow(abs(playerCenterY - fish2[i].yCen + 150), 2))) {
				if (level >= 2) {
					fish2[i].exist = false;
					points += 100;
				}
				else if (level <2) {
					gameOver = true;
					ifWin = false;
					
				}
				yummyExist = true;
				yummyX = (playerCenterX + fish2[i].xCen + 150) / 2 - 150;
				yummyY = (playerCenterY + fish2[i].yCen + 150) / 2 - 200;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (pf->fish3[i].exist) {
			if (pow((playerLen + fish3[i].len), 2) >= (pow(abs(playerCenterX - fish3[i].xCen + 150), 2) + pow(abs(playerCenterY - fish3[i].yCen + 150), 2))) {
				if (level >= 3) {
					fish3[i].exist = false;
					points += 150;
				}
				else if (level < 3) {
					gameOver = true;
					ifWin = false;

				}
				yummyExist = true;
				yummyX = (playerCenterX + fish3[i].xCen + 150) / 2 - 150;
				yummyY = (playerCenterY + fish3[i].yCen + 150) / 2 - 200;
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		if (pf->fish4[i].exist) {
			if (pow((playerLen + fish4[i].len), 2) >= (pow(abs(playerCenterX - fish4[i].xCen + 150), 2) + pow(abs(playerCenterY - fish4[i].yCen + 150), 2))) {
				if (level >= 4) {
					fish4[i].exist = false;
					points += 200;
				}
				else if (level < 4) {
					gameOver = true;
					ifWin = false;

				}
				yummyExist = true;
				yummyX = (playerCenterX + fish4[i].xCen + 150) / 2 - 150;
				yummyY = (playerCenterY + fish4[i].yCen + 150) / 2 - 200;
			}
		}
	}

	if (pf->fish5.exist) {
		if (pow((playerLen + fish5.len), 2) >= (pow(abs(playerCenterX - fish5.xCen + 150), 2) + pow(abs(playerCenterY - fish5.yCen + 150), 2))) {
			gameOver = true;
			ifWin = false;
			yummyExist = true;
			yummyX = (playerCenterX + fish5.xCen + 150) / 2 - 150;
			yummyY = (playerCenterY + fish5.yCen + 150) / 2 - 200;
		}
	}

	if (pow((playerLen + 100 ), 2) >= (pow(abs(playerCenterX - shellXPos +100), 2)+ pow(abs(playerCenterY - shellYPos + 100), 2)) ) {
		if (shellOut) {
			points += 100;
			yummyX = (playerCenterX + shellXPos + 100) / 2 - 100;
			yummyY = (playerCenterY + shellYPos + 100) / 2 - 100;
			yummyExist = true;
		}
		
		shellOut = false;
	}

	if (points >= 200 && points <500) {
		level = 2;
	}
	else if (points >= 500 && points < 900) {
		level = 3;
	}
	else if (points >= 900 && points < 1400) {
		level = 3;
	}
	else if (points >= 1400) {
		level = 4;
	}

	if (points >= 2000) {
		gameOver = true;
		ifWin = true;
	}

}

BEGIN_MESSAGE_MAP(CMyWnd, CFrameWnd)
	
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

void CMyWnd::OnLButtonUp(UINT nFlags, CPoint point)
{	
	if (!startedGame) {
		if (point.x > 1100 && point.x < 1500 && point.y > 500 && point.y < 650) {
			startedGame = true;
		}
		else if (point.x > 850 && point.x < 1250 && point.y > 700 && point.y < 850) {
			MessageBox("请选择背景图片", "提示");
		}
		else if (point.x > 850 && point.x < 1250 && point.y > 900 && point.y < 1050) {
			MessageBox("请选择你要控制的角色", "提示");
		}
		else if (point.x > 1330 && point.x < 1400 && point.y > 700 && point.y < 850) {
			backGroundBMP->m_hObject = LoadImage(NULL, "backGround.bmp", IMAGE_BITMAP, windWidth, windHeight, LR_LOADFROMFILE);
			MessageBox("您已经选择了背景图片一", "提示");
		}
		else if (point.x > 1470 && point.x < 1590 && point.y > 700 && point.y < 850) {
			backGroundBMP->m_hObject = LoadImage(NULL, "backGround2.bmp", IMAGE_BITMAP, windWidth, windHeight, LR_LOADFROMFILE);
			MessageBox("您已经选择了背景图片二", "提示");
		}
		else if (point.x > 1510 && point.x < 1730 && point.y > 700 && point.y < 850) {
			backGroundBMP->m_hObject = LoadImage(NULL, "backGround3.bmp", IMAGE_BITMAP, windWidth, windHeight, LR_LOADFROMFILE);
			MessageBox("您已经选择了背景图片三", "提示");
		}
		else if (point.x > 1650 && point.x < 1870 && point.y > 700 && point.y < 850) {
			backGroundBMP->m_hObject = LoadImage(NULL, "backGround4.bmp", IMAGE_BITMAP, windWidth, windHeight, LR_LOADFROMFILE);
			MessageBox("您已经选择了背景图片四", "提示");
		}
		else if (point.x > 1330 && point.x < 1400 && point.y > 900 && point.y < 1050) {
			playerNum = 1;
			MessageBox("您已经选择了角色图片一", "提示");
		}
		else if (point.x > 1470 && point.x < 1590 && point.y > 900 && point.y < 1050) {
			playerNum = 2;
			MessageBox("您已经选择了角色图片二", "提示");
		}else if (point.x > 1100 && point.x < 1500 && point.y > 1100 && point.y < 1300) {
			exitMark = true;
			PostMessage(WM_CLOSE);
		}
	}
	else if (startedGame && gameOver) {
		if (point.x > 1050 && point.x < 1450 && point.y > 1100 && point.y < 1200) {
			exitMark = true;
			PostMessage(WM_CLOSE);
		}
		else if (point.x > 1050 && point.x < 1500 && point.y > 900 && point.y < 1050) {
			inited = false;
			startedGame = false;
		}
	}else if (startedGame && !gameOver) {
	}

	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CMyWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_ESCAPE) {
		startedGame = false;
		inited = false;
	}
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (startedGame && !gameOver) {
		playerXPos = point.x;
		playerYPos = point.y;
		
		if (point.x >= lastPoint.x) {
			directionLeft = false;
		}
		else {
			directionLeft = true;
		}
		lastPoint.x = point.x;
		lastPoint.y = point.y;
		
		while (ShowCursor(false) >= 0) {
			ShowCursor(false);
		}
	}
	else if (!startedGame) {
		while (ShowCursor(true) < 0) {
			ShowCursor(true);
		}
	}
	else if (startedGame && gameOver) {
		while (ShowCursor(true) < 0) {
			ShowCursor(true);
		}
	}

	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMyWnd::OnClose()
{
	Sleep(500);
	CFrameWnd::OnClose();
}
