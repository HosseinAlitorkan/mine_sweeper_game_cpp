#include <iostream>
#include<stdlib.h>
#include <Windows.h>
#include<fstream>
#include<string.h>
#include<time.h>
using namespace std;

//Globals variables
const int ar1 = 30, ar2 = 30;
int level,timegame;
ofstream write;
ifstream read;
bool loss = false;
int bombsi = 0,flagcounter=0,flg=0;
struct kho
{
	char nema = '*', me = '0';
}z[ar1][ar2];
void nemayesh()
{
	
	cout << endl << "  ";
	for (int i = 0; i < ar2; ++i)
	{
		cout << i<<" ";
		if (i < 10)
			cout << " ";
	}
	cout << endl;
	for (int i = 0; i < ar1 ; ++i)
	{
		
		cout << i << "|";
		if (i < 10)
			cout << " ";
		for (int j = 0; j < ar2; ++j)
		{
			cout << z[i][j].nema << "  ";
		}
		cout <<'|'<<i<< endl;
	}
	cout << "  ";
	for (int i = 0; i < ar2; ++i)
	{
		cout << i << " ";
		if (i < 10)
			cout << " ";
	}
	cout << endl << "flag number:" << flagcounter << endl;
}
void bomber()
{
	int i = 0, a, b;
	while (i != 20)
	{
		srand(time(0));
		a = rand() % 30 ;
		b = rand() % 30 ;
		if (z[a][b].me != '&')
		{
			++i;
			z[a][b].me = '&';
			for (int j = a - 1; j < a + 2; ++j)
			{
				for (int k = b - 1; k < b + 2; ++k)
				{ 
					if (j>=0 && j<30 && k>=0 && k<30)
					{ 
						if (z[j][k].me != '&')
						{
							z[j][k].me += 1;
						}
					}
				}
			}
		}

	}

}
void flag(int x, int y)
{
	z[x][y].nema = '@';
	flagcounter += 1;
	if (z[x][y].me == '&')
	{
		bombsi += 1;
	}
}
void unflag(int x, int y)
{
	if (z[x][y].nema == '@')
	{
		flagcounter = flagcounter - 1;
		z[x][y].nema = '*';
		if (z[x][y].me == '&')
		{
			bombsi = bombsi - 1;
		}
	}
}
void check22(int x,int y)
{
	if (x >= 0 && y >= 0 && x < 30 && y < 30 && z[x][y].nema == '*' && z[x][y].me != '&')
	{
		if (z[x][y].me == '0'  && z[x][y].nema != '@' &&flg<2)
		{
			z[x][y].nema = z[x][y].me;
			check22(x, y - 1);
			check22(x, y + 1);
			check22(x - 1, y - 1);
			check22(x - 1, y + 1);
			check22(x - 1, y);
			check22(x + 1, y + 1);
			check22(x + 1, y - 1);
			check22(x + 1, y);
			flg += 1;
		}
		else if (z[x][y].me != '0'&&z[x][y].me != '&' &&z[x][y].nema != '@')
		{
			z[x][y].nema = z[x][y].me;
		}
	}


}
void check12(int x, int y)
{
	if (x >= 0 && y >= 0 && x < 30 && y < 30 && z[x][y].nema=='*' && z[x][y].me!='&')
	{
		if (z[x][y].me == '0'  && z[x][y].nema != '@')
		{
			z[x][y].nema = z[x][y].me;
			check12(x, y - 1);
			check12(x, y + 1);
			check12(x - 1, y - 1);
			check12(x - 1, y + 1);
			check12(x - 1, y);
			check12(x + 1, y + 1);
			check12(x + 1, y - 1);
			check12(x + 1, y);
			
		}
		else if (z[x][y].me != '0'&&z[x][y].me != '&' &&z[x][y].nema!='@')
		{
			z[x][y].nema = z[x][y].me;
		}
	}


}
void check(int x,int y)
{
	if (z[x][y].me == '&')
	{
		loss = true;
		for (int i = 0; i < 30; ++i)
		{
			for (int j = 0; j < 30; ++j)
			{
				if (z[i][j].me == '&')
				{
					z[i][j].nema = '&';
				}
			}
		}
		
	}
	else
	{
		if (level == 1)
		{
			check12(x, y);
		}
		else if (level == 2)
		{
			check22(x, y);
			flg = 0;
		}
	}
} 
int end()
{
	if (bombsi == 20 && flagcounter == 20)
		return 1;
	else
	{
		return 0;
	}
}
void startgame()
{
	int x, y, a;
	bomber();
	clock_t zaman1, zaman2;
	zaman1 = clock();
	while (!loss && !end())
	{
		nemayesh();
		cout << endl <<"you must find 20 bombes"<<endl<< "please enter 1 to check a home or entet 2 to flag a home or enter 3 to unflag a home:";
		cin >> a;
		cout << endl << "plese enter location of home:" << endl << "enter x:";
		cin >> y;
		cout << "enter y:";
		cin >> x;
		if (x >= 0 && y >= 0 && x < 30 && y < 30)
		{
			if (a == 1)
			{
				check(x, y);
			}
			else if (a == 2)
			{
				flag(x, y);
			}
			else if (a == 3)
			{
				unflag(x, y);
			}
			else
			{
				cout << "out of range =error"<<endl;
				system("pause");
			}
		}
		else
		{
			cout << "out of range=error"<<endl;
			system("pause");
		}
		system("cls");
	}
	zaman2 = clock() - zaman1;
	timegame = zaman2 / 1000;
	if (loss)
	{
		nemayesh();
		cout << endl << "===Game Over==="<<endl;	
	}
	else
	{
		cout << "===you are winer===" << endl << "Time(s):" << timegame << endl;
	}
	system("pause");
}
void sign()
{
	char name[50], pass[11];
	cout << endl << "sign in:" << endl << "please enter your user name(max 40 char):";
	write.open("e:\\game.txt", ios::app);
	cin >> name;
	write << name << endl;
	cout << "please enter your password(max 10 char):";
	cin >> pass;
	write << pass <<endl;
	cout << endl << "you are signed in " << endl;
	write.close();
	system("pause");
}
int  login()
{

	char  na[50], pa[11], name[50], pass[11];;
	cout << "login:" << endl << "please enter your user name:";
	cin >> name;
	cout << "please enter your password:";
	cin >> pass;
	read.open("e:\\game.txt");
	for (int i = 0; i < 1000; i++)
	{
		read >> na >> pa;
		if (strcmp(name, na) == 0 && strcmp(pass, pa) == 0)
		{
			cout << "you are loged in" <<endl;
			return 1;
		}
	}

	cout << endl << "error";
	system("pause");
	return 0;
}
void setting()
{
	cout << "setting:" << endl << "1_background=black & text=red" << endl << "2_background=yello & text=red"<<endl<<"3_background=black & text=light red"<<endl;
	int a;
	cin >> a;
	switch (a)
	{
	case 1:
		system("color 4");
		break;
	case 2:
		system("color e4");
		break;
	case  3:
		system("color c");
		break;
	default:
		system("color f");
		break;
	}

}
void setup()
{
	while (1)
	{
		cout << "In the name of Allah" << endl << "Wellcom to minesweeper game" << endl;
		cout << "1_sign in" << endl << "2_log in" <<endl<< "3_setting" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			sign();
		}
		else if (a == 2)
		{
			if (login())
			{
				break;
			}
		}
		else if (a == 3)
		{
			setting();
		}
		else
		{
			cout << "out of range =error";
		}
		system("cls");
	}
	cout << "choose the level of game:" << endl << "1_easy" << endl << "2_hard" << endl;
	
	cin >> level;
	cout << endl << "please wait ..." << endl;
	return ;
}
int main()
{
	
	setup();
	startgame();
	cout << endl << "good luck ...out" << endl;
	system("pause");
	return 0;
}
