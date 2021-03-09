#include <conio.h>
#include <stdio.h>
#include <bios.h>

void main()
{
int ck,m=0,i;
int k[10]={0};

clrscr();
while (ck!=129)
	{
	ck=inp(0x60);
	if (ck==k[m-1])
		continue;
	if (m==10)
		{
		for (i=0; i<9; i++)
			k[i]=k[i+1];
		k[9]=ck;
		}
	else
		k[m++]=ck;

	gotoxy(20,10);
	bioskey(0);
	for (i=0; i<m; i++)
		printf("%3d ",k[i]);

	}

}