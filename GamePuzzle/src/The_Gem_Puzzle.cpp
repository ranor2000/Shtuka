#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h> 
#include <vector>
#include <string>
#include "3rd-party/graphics.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct ba { int tx; int ty; char* s = new char[255]; };

struct sp { int scor; char* n = new char[10]; char* name = new char[10]; sp* next; };

void sort(sp** head, int val) {
	sp* p = *head;
	sp* temp;
	while (val > 0) {
		p = *head;
		while (p->next != NULL) {
			if (p->scor > p->next->scor) {
				temp = new sp;
				temp->name = p->name;
				temp->n = p->n;
				temp->scor = p->scor;
				p->name = p->next->name;
				p->n = p->next->n;
				p->scor = p->next->scor;
				p->next->name = temp->name;
				p->next->n = temp->n;
				p->next->scor = temp->scor;
				p = p->next;
			}
			else {
				p = p->next;
			}
		}
		val--;
	}
}

void savescore(sp* head) {
	sp* p = head;
	FILE* fn, * fs;
	fn = fopen("name_player.txt", "w");
	fs = fopen("scor_player.txt", "w");
	while (p) {
		fprintf(fn, "%s\n", p->name);
		fprintf(fs, "%s\n", p->n);
		p = p->next;
	}
	fclose(fn);
	fclose(fs);
}

int loadscore(sp** head) {
	sp* p;
	int n = 0;
	FILE* fn, * fs;
	fn = fopen("name_player.txt", "r");
	fs = fopen("scor_player.txt", "r");

	
// P.S. программа не работает без готовых результатов
	while (!feof(fs)) {
		p = new sp;
		fscanf(fn, "%s", p->name);
		fscanf(fs, "%s", p->n);
		if (atoi(p->n) > 0) {
			p->next = *head;
			p->scor = atoi(p->n);
			*head = p;
			n++;
		}
	}
	fclose(fn);
	fclose(fs);
	return n;
}

void prin(ba* a) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			bar(j * (getmaxx() / 4) + 10, i * (getmaxy() / 4) + 10, (j + 1) * (getmaxx() / 4) - 10, (i + 1) * (getmaxy() / 4) - 10);
			outtextxy(a[i * 4 + j].tx, a[i * 4 + j].ty, a[i * 4 + j].s);
		}
}

int recmo(int a, int n, ba* rec) {
	int t, i;
	switch (a) {
	case 87:
	yt:for (i = 4; i < 16; i++)
		if (rec[i].s == "  ") {
			t = rec[i].tx;
			rec[i].tx = rec[i - 4].tx;
			rec[i - 4].tx = t;
			rec[i].s = rec[i - 4].s;
			rec[i - 4].s = (char*)"  ";
			n++;
			break;
		}break;
	case 83:
	yd:for (i = 0; i < 12; i++)
		if (rec[i].s == "  ") {
			t = rec[i].tx;
			rec[i].tx = rec[i + 4].tx;
			rec[i + 4].tx = t;
			rec[i].s = rec[i + 4].s;
			rec[i + 4].s = (char*)"  ";
			n++;
			break;
		}break;
	case 68:
	xr:for (i = 0; i < 16; i++)
		if (rec[i].s == "  " && i % 4 != 3) {
			t = rec[i].tx + getmaxx() / 4;
			rec[i].tx = rec[i + 1].tx - getmaxx() / 4;
			rec[i + 1].tx = t;
			rec[i].s = rec[i + 1].s;
			rec[i + 1].s = (char*)"  ";
			n++;
			break;
		}break;
	case 65:
	xl:for (i = 0; i < 16; i++)
		if (rec[i].s == "  " && i % 4 != 0) {
			t = rec[i].tx - getmaxx() / 4;
			rec[i].tx = rec[i - 1].tx + getmaxx() / 4;
			rec[i - 1].tx = t;
			t = rec[i].ty;
			rec[i].ty = rec[i - 1].ty;
			rec[i - 1].ty = t;
			rec[i].s = rec[i - 1].s;
			rec[i - 1].s = (char*)"  ";
			n++;
			break;
		}break;
	case 119:
		goto yt;
	case 115:
		goto yd;
	case 100:
		goto xr;
	case 97:
		goto xl;
	default: break;
	}
	return n;
}

void newboard(ba* rec) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			;
			_itoa(i * 4 + j + 1, rec[i * 4 + j].s, 10);
			if (atoi(rec[i * 4 + j].s) < 10)
				rec[i * 4 + j].tx = 50 + (j) * (getmaxx() / 4);
			else
				rec[i * 4 + j].tx = 30 + (j) * (getmaxx() / 4);
			rec[i * 4 + j].ty = 20 + (i) * (getmaxy() / 4);
		}
	}
	rec[15].s = (char*)"  ";
	for (int i = 0; i < 1000; i++) {
		switch (rand() % 4) {
		case 0: recmo(87, 0, rec); break;
		case 1: recmo(83, 0, rec); break;
		case 2: recmo(68, 0, rec); break;
		case 3: recmo(65, 0, rec); break;
		}
	}
}

void globscor(sp* head) {
	int n = 0;
	cleardevice();
	sp* p = head;
	while (p) {
		outtextxy(20, n, p->name);
		outtextxy(480, n, p->n);
		p = p->next;
		n += 80;
	}
	savescore(head);
	getch();
}

void score(sp* head, int n, int v) {
	cleardevice();
	sp* p;
	int a, i = 0;
	char* b = new char[10], * sc = new char[255];
	outtextxy(40, getmaxy() / 2 - 160, (char*)"Enter youre");
	outtextxy(180, getmaxy() / 2 - 80, (char*)"name:");
	bar(40, getmaxy() / 2, 90, getmaxy() / 2 + 60);
	outtextxy(40, getmaxy() / 2 + 80, (char*)"Score:");
	_itoa(n, sc, 10);
	outtextxy(340, getmaxy() / 2 + 80, sc);
	while (i < 11) {
		a = getch();
		if (a == 27)break;
		else if (a == 8 && i > 0) {
			b[i] = ' ';
			outtextxy(40, getmaxy() / 2, b);
			i--;
			bar(i * 51 + 40, getmaxy() / 2 + 10, i * 51 + 90, getmaxy() / 2 + 80);
		}
		else if (a == 13) {
			p = new sp;
			p->scor = n;
			p->n = sc;
			p->name = b;
			p->next = head;
			head = p;
			v++;
			sort(&head, v);
			globscor(head);
			break;
		}
		else if (i < 9 && a>32 && a < 127) {
			b[i] = a;
			outtextxy(40, getmaxy() / 2, b);
			i++;
			bar(i * 51 + 40, getmaxy() / 2 + 10, i * 51 + 90, getmaxy() / 2 + 80);
		}
	}
	cleardevice();
}

int pobeda(ba* rec) {
	int n = 0;
	for (int i = 0; i < 15; i++) {
		if (atoi(rec[i].s) == i + 1)n++;
		else return 0;;
	}
	if (n == 14)return 1;
}

int main(int argc, char** argv) {
	int GrDr, GrMod, rez, a, n, val = 0;
	ba* rec;
	struct sp* head;
	head = NULL;
	val = loadscore(&head);
	sp* p = head;
	sort(&head, val);


	GrDr = DETECT;
	initgraph(&GrDr, &GrMod, (char*)" ");
	rez = graphresult();
	if (rez != grOk) {
		printf("Initialization failed: %s\n", grapherrormsg(rez));
		printf("Press any key");
		getch();
		exit(1);
	}

	settextstyle(0, 0, 10);
	srand(time(NULL));
	while (1) {
		rec = new ba[16];
		n = 0;
		outtextxy(100, getmaxy() / 2 - 80, (char*)"Press<F>");
		outtextxy(100, getmaxy() / 2, (char*)"To Start");
		a = getch();
		if (a == 27)break;
		if (a == 102) {
			newboard(rec);
			while (true) {
				cleardevice();
				prin(rec);
				a = getch();
				if (a == 27) { delete []rec; break; }
				n = recmo(a, n, rec);
				if (pobeda(rec) == 1) {
					delete []rec;
					score(head, n, val);
					break;
				}
			}
		}
		cleardevice();
	}
	closegraph();
	return 0;
}