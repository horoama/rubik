#include <stdio.h>
#include <stdlib.h>

#define FRONT (0)
#define UP (1)
#define RIGHT (2)
#define LEFT (3)
#define DOWN (4)
#define BACK (5)
#define BUF_SIZE (256)
//red 1 ; blue 2; yellow 3; white 4; green 5; orange 6;
void Input_Side(int side);
void Input();
void Search();
int SearchCenter();
int Check();
void View();
void SpinSurface(int side);
void SpinFront();
void SpinRight();
void SpinUp();
void SpinLeft();
void SpinMiddle();
void SpinDown();
void ColorStr(int color);
void Shaffle();
int Spin(char* str);
int Color[6][3][3]={0};
int Hand();
void Help();

int main()
{
    char buf[BUF_SIZE];
    /*
       while(Check()==0)
       {
	SearchCenter();
       }
    */
  Input();
//  SpinFront();
//  SpinRight();
  View();
  while(1)
  {
      fgets(buf,BUF_SIZE,stdin);
      if(Spin(buf)==0)
	  break;
  }
  return 0;
}
int Spin(char* str)
{
    int i=0,flag=1;
    while(*(str+i) != '\n')
	{
	    if(*(str+i)=='f')
		SpinFront();
	    if(*(str+i)=='r')
		SpinRight();
	    if(*(str+i)=='l')
		SpinLeft();
	    if(*(str+i)=='u' || *(str+i)=='t')
		SpinUp();
	    if(*(str+i)=='n')
		Input();
	    if(*(str+i)=='m')
		SpinMiddle();
	    if(*(str+i)=='d')
		SpinDown();
	    i++;
	}
    if(*str=='\n')
	Hand();
    if(*str==' ')
	HandUp();
    if(*str=='s')
	Shaffle();
    if(*str=='h' || *str=='?')
	Help();

	View();
	if(*(str+i-1)=='0')
	    flag=0;
    return flag;
}
void SpinSurface(int side)
{
 int Temp[6][3][3]={0};
 int i;
 for(i=0;i<3;i++)
   {
     Temp[side][i][2]=Color[side][0][i];
     Temp[side][2][2-i]=Color[side][i][2];
     Temp[side][i][0]=Color[side][2][i];
     Temp[side][0][i]=Color[side][2-i][0];
   }
 for(i=0;i<3;i++)
   {
     Color[side][i][2]=Temp[side][i][2];
     Color[side][2][2-i]=Temp[side][2][2-i];
     Color[side][i][0]=Temp[side][i][0];
     Color[side][0][i]=Temp[side][0][i];
  }
}
void SpinMiddle()
{
    SpinRight();
    SpinRight();
    SpinRight();
    SpinLeft();
    HandUp();
}
void SpinUp()
{
 int Temp[6][3][3]={0};
 int i;
 for(i=0;i<3;i++)
   {
     Temp[FRONT][0][i]=Color[RIGHT][0][i];
     Temp[LEFT][0][i]=Color[FRONT][0][i];
     Temp[BACK][0][i]=Color[LEFT][0][i];
     Temp[RIGHT][0][i]=Color[BACK][0][i];
   }
 for(i=0;i<3;i++)
   {
     Color[FRONT][0][i]=Temp[FRONT][0][i];
     Color[LEFT][0][i]=Temp[LEFT][0][i];
     Color[BACK][0][i]=Temp[BACK][0][i];
     Color[RIGHT][0][i]=Temp[RIGHT][0][i];
  }
 SpinSurface(UP);
}
void SpinFront()
{
  int Temp[6][3][3]={0};
  int i;
  for(i=0;i<3;i++)
    {
      Temp[RIGHT][i][0]=Color[UP][2][i];//上を右に
      Temp[DOWN][0][2-i]=Color[RIGHT][i][0];//右を下
      Temp[LEFT][i][2]=Color[DOWN][0][i];//下を左
      Temp[UP][2][2-i]=Color[LEFT][i][2];//左を上に

    }
  for(i=0;i<3;i++)
    {
      Color[RIGHT][i][0]=Temp[RIGHT][i][0];
      Color[DOWN][0][2-i]=Temp[DOWN][0][2-i];
      Color[LEFT][i][2]=Temp[LEFT][i][2];
      Color[UP][2][2-i]=Temp[UP][2][2-i];
    }
  SpinSurface(FRONT);
}
void SpinRight()
{
    int Temp[6][3][3]={0};

    int i;
    for(i=0;i<3;i++)
    {
	Temp[UP][i][2]=Color[FRONT][i][2];//up from front
	Temp[FRONT][i][2]=Color[DOWN][i][2];//front from down
	Temp[DOWN][i][2]=Color[BACK][2-i][0];//down from back
	Temp[BACK][i][0]=Color[UP][2-i][2];//back from up
    }
    for(i=0;i<3;i++)
    {
	Color[UP][i][2]=Temp[UP][i][2];
	Color[FRONT][i][2]=Temp[FRONT][i][2];
	Color[DOWN][i][2]=Temp[DOWN][i][2];
	Color[BACK][i][0]=Temp[BACK][i][0];
    }
    SpinSurface(RIGHT);
}
void SpinLeft()
{
    Hand();
    Hand();
    SpinRight();
    Hand();
    Hand();
}
void SpinDown()
{
    HandUp();
    HandUp();
    SpinUp();
    SpinUp();
    SpinUp();
    HandUp();
    HandUp();
}
/*解法処理
int Check()
{
  int flag=1,i,j;
  for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
	  if(Color[1][i][j]!=Color[1][1][1])
	    {
		flag=0;
	    }
	}
    }
  return flag;
}*/
int Hand()
{
    int Temp[6][3][3]={0};
    int i,j;
    for(i=0;i<3;i++)
    {
	for(j=0;j<3;j++)
	{
	    Temp[LEFT][i][j]=Color[FRONT][i][j];//up from front
	    Temp[FRONT][i][j]=Color[RIGHT][i][j];//front from down
	    Temp[BACK][i][j]=Color[LEFT][i][j];//down from back
	    Temp[RIGHT][i][j]=Color[BACK][i][j];//back from up
	}
    }
    for(i=0;i<3;i++)
    {
	for(j=0;j<3;j++)
	{
	Color[LEFT][i][j]=Temp[LEFT][i][j];
	Color[FRONT][i][j]=Temp[FRONT][i][j];
	Color[BACK][i][j]=Temp[BACK][i][j];
	Color[RIGHT][i][j]=Temp[RIGHT][i][j];

	}
    }
    SpinSurface(UP);
    SpinSurface(DOWN);
    SpinSurface(DOWN);
    SpinSurface(DOWN);
return 0;
}
int HandUp()
{
int Temp[6][3][3]={0};
    int i,j;
    for(i=0;i<3;i++)
    {
	for(j=0;j<3;j++)
	{
	    Temp[UP][i][j]=Color[FRONT][i][j];//up from front
	    Temp[FRONT][i][j]=Color[DOWN][i][j];//front from down
	    Temp[BACK][i][j]=Color[UP][2-i][2-j];//down from back
	    Temp[DOWN][i][j]=Color[BACK][2-i][2-j];//back from up
	}
    }
    for(i=0;i<3;i++)
    {
	for(j=0;j<3;j++)
	{
	Color[UP][i][j]=Temp[UP][i][j];
	Color[FRONT][i][j]=Temp[FRONT][i][j];
	Color[BACK][i][j]=Temp[BACK][i][j];
	Color[DOWN][i][j]=Temp[DOWN][i][j];

	}
    }
    SpinSurface(RIGHT);
    SpinSurface(LEFT);
    SpinSurface(LEFT);
    SpinSurface(LEFT);
return 0;
}
void Input()
{
  printf("front\n");
  Input_Side(0);
  printf("up\n");
  Input_Side(1);
  printf("right\n");
  Input_Side(2);
  printf("left\n");
  Input_Side(3);
  printf("down\n");
  Input_Side(4);
  printf("back\n");
  Input_Side(5);

}
void Input_Side(int side)
{
  int i,j,k,x=0;
  char buf[BUF_SIZE];
  FILE *fp;
  fp=fopen("a.dat","r");
      if(fp==NULL){
	  //失敗と表示し終了
	  printf("ファイルオープン失敗\n");
      }
      fseek(fp,side*9,SEEK_SET);
  for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
	{
	    x=0;
	  fread(buf,sizeof(char),1,fp);
	  //fscanf(fp,"%",buf);
	  if(*buf=='r')
	    x=1;
	  if(*buf=='b')
	    x=2;
	  if(*buf=='y')
	    x=3;
	  if(*buf=='w')
	    x=4;
	  if(*buf=='g')
	    x=5;
	  if(*buf=='o')
	    x=6;
	  Color[side][i][j]=x;
	}
    }
  fclose(fp);
}
void View()
{
  int i,j,k;
      for(j=0;j<3;j++)
	{
	    printf("      ");
	    for(k=0;k<3;k++)
	    {
		ColorStr(Color[UP][j][k]);
	    }
	  printf("\n");
	}
      for(j=0;j<3;j++)
	{
	    for(k=0;k<3;k++)
		ColorStr(Color[LEFT][j][k]);
	    for(k=0;k<3;k++)
		ColorStr(Color[FRONT][j][k]);
	    for(k=0;k<3;k++)
		ColorStr(Color[RIGHT][j][k]);
	    for(k=0;k<3;k++)
		ColorStr(Color[BACK][j][k]);
	    printf("\n");
	}
      for(j=0;j<3;j++)
      {
	  printf("      ");
	  for(k=0;k<3;k++)
	  {
	      ColorStr(Color[DOWN][j][k]);
	  }
	  printf("\n");
      }
      printf("\n");
}
void ColorStr(int color)
{
    switch (color)
    {
	case 1:
	    printf("\x1b[31m");
	    break;
	case 2:
	    printf("\x1b[34m");
	    break;
	case 3:
	    printf("\x1b[33m");
	    break;
	case 4:
	    printf("\x1b[37m");
	    break;
	case 5:
	    printf("\x1b[32m");
	    break;
	case 6:
	    printf("\x1b[35m");
	    break;
	default:
	    printf("\x1b[36m");
	    break;
    }
    printf("■ ");
    printf("\x1b[39m");
}
void Shaffle()
{
    int x,i=0;
    srand((unsigned int)time(NULL));
    while(i<30)
    {
	i++;
	x=rand()%7;
	switch(x)
	{
	    case 0:
		SpinRight();
		break;
	    case 1:
		SpinLeft();
		break;
	    case 2:
		SpinUp();
		break;
	    case 3:
		SpinFront();
		break;
	    case 4:
		SpinDown();
		break;
	    case 5:
		HandUp();
		break;
	    case 6:
		Hand();
		break;
	    default:
		SpinRight();
	}
    }
}
void Help()
{
    printf("sでシャッフル\nr で右の面を時計回りに９０度回転\nf で前面を時計回りに９０度回転\nu で上面を時計回りに９０度回転\nl で左の面を時計回りに９０度回転\nm で前面の中央を上に９０度回転\nd で下面を半時計回りに９０度回転\n何も入力せずにエンターを押すと上から見て時計回りにに持ち替え\nスペースを一回入力してエンターで右から見て時計回りに持ち替え\nやめるときは 0 だけを入力しエンター\n");
    /*    printf(" s でシャッフル\n r で右の面を時計回りに９０度回転\n
	  f で前面を時計回りに９０度回転\n
	  u で上面を時計回りに９０度回転\n
	  l で左の面を時計回りに９０度回転\n
	  m で前面の中央を上に９０度回転\n
	  d で下面を半時計回りに９０度回転\n
	  何も入力せずにエンターを押すと上から見て時計回りにに持ち替え\n
	  スペースを一回入力してエンターで右から見て時計回りに持ち替え\n
	  やめるときは 0 だけを入力しエンター\n");
	  */
}
/*解法処理
  int SearchCenter(int color)
  {
  int i,j;
  for(i=0;i<6;i++)
  {
  if(i==4)//下面から移動
  {
  if(Color[i][0][1]==color)
  {
  while(1)
  {
  if(Color[1][2][1]==Color[1][1][1])
  {
  printf("ffcf'f'c'");
  break;
  }
  }
  }
  if(Color[i][1][0]==color)
  {
  }
  if(Color[i][1][2]==color)
  {
  }
  if(Color[i][2][1]==color)
  {
  }
  }
  }
  }
  */
/*int Search(int color)
  {
  for(i=0;i<3;i++)
  {
  for(j=0;j<3;j++)
  {
  if(side[i][j]==color)
  {
  if(side[i][j]==)
  }
  }
  }
  }*/

