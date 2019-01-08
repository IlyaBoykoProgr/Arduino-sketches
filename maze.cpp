/*
 programm made by IllyaBoyko https://github.com/IllyaBoykoProgr
 start programm via terminal: 'maze play' to play or 'maze help' to help
*/
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#ifdef WINDOWS
 #include<windows.h>
 #include<conio.h>
 #define WAIT(h) Sleep(h)
 #define CLEAR for(int i;i<100;i++)cout<<'\n'
#else
 #include<ctime>
 #include<termios.h>
 #include<unistd.h>
 #define WAIT(h) usleep(h)
 #define CLEAR system("clear");
 char getch(){
 struct termios oldt,newt;
 int ch;
 tcgetattr( STDIN_FILENO, &oldt );
 newt = oldt;
 newt.c_lflag &= ~( ICANON | ECHO );
 tcsetattr( STDIN_FILENO, TCSANOW, &newt );
 ch = getchar();
 tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
 return ch;}
#endif
#define HEIGHT 20//любое кол-во строк      |any count of strings(vertical)
#define WIDTH HEIGHT*2 //любое кол-во длины строки|any count of column(horisontal)
using namespace std;
bool deadend(int, int, int**, int, int); // Вспомогательная функция, определяет тупики
void visual(int**, int, int, int); // Изображение результата с помощью консольной графики
void mazemake(int**, int, int); // Собственно алгоритм
void win(int**,int,int);
void help();
int c=rand()%4;
unsigned int mazescomplete;

class person{
 int x,y;
 public:
  void start(){y=3;x=3;}
  int getx(){return x;}
  int gety(){return y;}
  void up(int** maze,bool cheats){
  if(maze[x-1][y]==0&&!cheats)return;//if wall
  x--;}
  void down(int** maze,bool cheats){
  if(maze[x+1][y]==0&&!cheats)return;//if wall
  x++;}
  void left(int** maze,bool cheats){
  if(maze[x][y-1]==0&&!cheats)return;//if wall
  y--;}
  void right(int** maze,bool cheats){
  if(maze[x][y+1]==0&&!cheats)return;//if wall
  y++;}
};
person Iam;

int main(int argc, char *argv[]){
ifstream temp1("data");
if(temp1.is_open()==0){
 ofstream temp0("data");
 temp0<<'0';
 temp0.close();
}
temp1>>mazescomplete;
temp1.close();
bool walkthroughwalls=0;
if(argc>1)switch(*argv[1]){
 case 'h':
  help();
  cout<<"maze version- version\nmaze play- play\nmaze cheat- cheats(walk through walls)\nmaze invisible- invisible walls\n\nThanks for using terminal!\n";
  return 0;
 case 'v':
  cout<<"Version: 2.4\nBugs and help update+data.\n";
  return 0;
 case 'c':
 walkthroughwalls=1;
 cout<<"You can walk through walls\n";
 case 'p':
 break;
 case 'i':
 c=4;
 cout<<"Walls are invisible\n";
 break;
 case '\0':
 default:
  cout<<"start programm using terminal!'./maze help' to help menu\n";
  return 0;
}
Iam.start();
setlocale(LC_ALL,"Russian");
srand((unsigned)time(NULL));
int height = HEIGHT, width = WIDTH;
if(height%2==0)height++;
if(width%2==0)width++;
if(height<6)height=7;
if(width<6)width=7;
int** maze = new int*[height];
for(int i = 0; i < height; i++) maze[i] = new int[width];
mazemake(maze, height, width);
visual(maze,height,width,c);
cout<<"\n press N to new maze.Press ? to see the help menu.Press Esc to quit\n";
switch(getch()){
 case 'n':
 case 'N':
  main(argc,argv);
  break;
 case '?':
 case '/':
   help();
  break;
 case '':
  return 0;
  }
while(1){
 switch(getch()){
  case 'w':
  case 'ц':
 Iam.up(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.up(maze,walkthroughwalls);
 break;
  case 'a':
  case 'ф':
 Iam.left(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.left(maze,walkthroughwalls);
 break;
  case 's':
  case 'ы':
 Iam.down(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.down(maze,walkthroughwalls);
 break;
  case 'd':
  case 'в':
 Iam.right(maze,walkthroughwalls);
 maze[Iam.getx()][Iam.gety()]=2;
 Iam.right(maze,walkthroughwalls);
 break;
  case '0':
 c=rand()%4;
 break;
  case '\E':
 main(argc,argv);
 break;
  case '?':
  case '/':
 help();
 getch();
 break;
 }
 visual(maze,height,width,c);
 maze[Iam.getx()][Iam.gety()]=2;
 if(Iam.getx()==height-2&&Iam.gety()==width-2){
  win(maze,height,width);
  mazescomplete++;
  remove("data");
  ofstream temp2("data");
  temp2<<mazescomplete;
  temp2.close();
  main(argc,argv);
 }
}
}

void help(){
 CLEAR;
   cout<<"This game is a maze game.\n"<<
   "All you need is come to the exit(it's red).Press WASD to move your person.\n"<<
   "ESC-quit.Different colour-0.\n"<<
   "If you want to change size of maze, you need to find this in the code of programm:\n"<<
   "'#define HEIGHT\n#define WIDTH'\n"<<
   "What is what you'll read.\nThen rebuild the programm.\n"<<
   "Completed mazes now: ";
   ifstream temp4("data");
   char read[20];
   temp4>>read;
   cout<<read<<'\n';
}

bool deadend(int x, int y, int** maze, int height, int width){
	int a = 0;

	if(x != 1){
		if(maze[y][x-2] == 1)
			a+=1;
		}
	else a+=1;

	if(y != 1){
		if(maze[y-2][x] == 1)
			a+=1;
		}
	else a+=1;

	if(x != width-2){
		if(maze[y][x+2] == 1)
			a+=1;
		}
	else a+=1;

	if(y != height-2){
		if(maze[y+2][x] == 1)
			a+=1;
		}
	else a+=1;

	if(a == 4)
		return 1;
	return 0;
}

void win(int** maze, int height,int width){
 int cels=0;
 for(int x=0;x<height;x++)for(int y=0;y<width;y++)if(maze[x][y]==0)cels++;
 for(int i=0;i<height*width-cels;i++){
  int x=rand()%height,y=rand()%width;
  if(maze[x][y]==0){i--;continue;}
  maze[x][y]=0;
  visual(maze,height,width,rand()%4);
  WAIT(100);
 }
 cout<<"\nYOU WON!!!\n";
}

void visual(int** maze, int height, int width,int c){
 CLEAR;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
		    if(i==height-2&&j==width-2){
		    #ifdef WINDOWS
		    cout<<"O";
		    #else
		    cout<<"\E[41m \E[0m";
		    #endif
		    continue;}
		    if(Iam.getx()==i && Iam.gety()==j){
		    #ifdef WINDOWS
		    cout<<"Я";
		    #else
		    cout<<"\E[42m \E[0m";
		    #endif
		    continue;}
			switch(maze[i][j]){
				case 0:
				#ifdef WINDOWS
				cout<<"%";break;
				#else
				switch(c){
				 case 0:
				 cout<<"\E[43;33m";break;
				 case 1:
				 cout<<"\E[44;34m";break;
				 case 2:
				 cout<<"\E[45;35m";break;
				 case 3:
				 cout<<"\E[46;36m";break;
				 case 4:
				 cout<<"\E[40;30m";break;//invisible
				}
				cout<<"0\E[0m"; break;
				 #endif
				case 1: cout<<" "; break;
				case 2: cout<<"\E[47m*\E[0m";break;
			}
        }
		cout<<endl;
    }
   // cout<<"x:"<<Iam.getx()<<" y:"<<Iam.gety()<<'\n';
}

void mazemake(int** maze, int height, int width){
	int x, y, c, a;

	for(int i = 0; i < height; i++) // Массив заполняется землей-ноликами
		for(int j = 0; j < width; j++)
			maze[i][j] = 0;

	x = 3; y = 3; a = 0; // Точка приземления крота и счетчик
	while(a < 1000000){ // Да, простите, костыль, иначе есть как, но лень
		maze[y][x] = 1; a++;
		while(1){ // Бесконечный цикл, который прерывается только тупиком
			c = rand()%4; // Напоминаю, что крот прорывает
			switch(c){  // по две клетки в одном направлении за прыжок
				case 0: if(y != 1)
					if(maze[y-2][x] == 0){ // Вверх
                                        maze[y-1][x] = 1;
					maze[y-2][x] = 1;
					y-=2;
				}
				case 1: if(y != height-2)
					if(maze[y+2][x] == 0){ // Вниз
					maze[y+1][x] = 1;
					maze[y+2][x] = 1;
					y+=2;
				}
				case 2: if(x != 1)
					if(maze[y][x-2] == 0){ // Налево
					maze[y][x-1] = 1;
					maze[y][x-2] = 1;
					x-=2;
				}
				case 3: if(x != width-2)
					if(maze[y][x+2] == 0){ // Направо
					maze[y][x+1] = 1;
					maze[y][x+2] = 1;
					x+=2;
				}
			}
			if(deadend(x,y,maze,height,width))
			   break;
		}

		if(deadend(x,y,maze,height,width)) // Вытаскиваем крота из тупика
			do{
				x = 2*(rand()%((width-1)/2))+1;
				y = 2*(rand()%((height-1)/2))+1;
			}
			while(maze[y][x] != 1);
	}
}