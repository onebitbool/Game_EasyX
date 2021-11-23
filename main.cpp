#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "key.h"
#include "move.h"
#include "Settings.h"
#include "role.h"
#include "image.h"
#include "bullet.h"
#include "show.h"
#include "image.h"
#include "control.h"

void startgame() {
	bullet_time1 = bullet_time2 = clock();
	role[0].lives = 5;
	role[1].lives = 5;
	reborn(role[0]);
	reborn(role[1]);
}

void initgame() {
	initbullet();
	initimagelinks();
	hpwidth = gameimage.hp.getwidth();
	hpheight = gameimage.hp.getheight();

	LOGFONT myfont;
	gettextstyle(&myfont);
	myfont.lfHeight = 12;
	myfont.lfWeight = FW_NORMAL;
	_tcscpy_s(myfont.lfFaceName, _T("����"));
	myfont.lfQuality = PROOF_QUALITY;
	settextstyle(&myfont);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	role[0].num = 0;
	role[1].num = 1;

	return;
}

int centerx(IMAGE& back, IMAGE& front) {
	return (back.getwidth() - front.getwidth()) / 2;
}

int main () {
	ExMessage m;
	clock_t time;
	initgraph (width, height, EW_SHOWCONSOLE);
	initimage();
	initgame();
	state = menu;
	while (1) {
		while (state == menu) {
			putimage(0, 0, &gameimage.start);
			m = getmessage(EM_MOUSE);
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 428 && m.y < 498) {
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
			}
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 544 && m.y < 613) {
				return 0;
			}
		}
		while (state == game) {
			time = clock();
			BeginBatchDraw();
			putimage(0, 0, &gameimage.background1);
			putimage(centerx(gameimage.background1, gameimage.background2[0]), 0, &gameimage.background2[0], SRCAND);
			putimage(centerx(gameimage.background1, gameimage.background2[1]), 0, &gameimage.background2[1], SRCINVERT);
			showpanel();
			showrole();
			initkey();
			getorder();
			move1(role[0], clock() - time);
			move2(role[1], clock() - time);
			updataimage();
			updatabullet();
			death();
			EndBatchDraw();
		}
		while (state == over) {
			m = getmessage(EM_MOUSE);
			if (m.lbutton && m.x > 837 && m.y > 545 && m.y < 600) {
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
				time = clock();
			}
			if (m.lbutton && m.x < 330 && m.y > 545 && m.y < 600) {
				state = menu;
				flushmessage(EM_MOUSE);
			}
		}
	}
	return 0;
}