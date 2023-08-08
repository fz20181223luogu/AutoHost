//code by 180-fz201812.23
#include<bits/stdc++.h>
#include<conio.h>
#include<fstream>
#include<windows.h>
typedef long long ll;
using namespace std;
const int C=4;
int cfg[C];
string st[C-1][3]={"野局","开盒","游戏模式","不进行","进行","是否进行合理性审查","不保留","保留","被开词条是否保留"};
ifstream in;
ofstream out;
void load(){
	system("cls");
	printf("Loading");
	putchar('.');
	Sleep(50); 
	putchar('.');
	Sleep(50); 
	putchar('.');
	Sleep(50); 
	system("cls");
}
void save(){
	out.open("settings.txt");
	for(int i=0;i<C;++i) out<<cfg[i]<<' ';
	out.close();
} 
int main(){
	in.open("settings.txt");
	for(int i=0;i<C;++i) in>>cfg[i];
	in.close();
	for(int i=0;i<C-1;++i) cfg[i]=!!cfg[i];
	while(1){
		load();
		puts("当前游戏模式：");
		for(int ind=0;ind<C-1;++ind) cout<<"项目“"<<st[ind][2]<<"”目前的状态是："<<st[ind][cfg[ind]]<<endl;
		printf("目前每位玩家词条数量为%d\n\n",cfg[3]);
		puts("请选择操作：\n1--更改设置\n2--保存设置\n3--重置并保存设置\n9--保存设置并退出程序\n\n请不要中途强制退出，否则设置可能无法保存！！！"); 
		char ch=getch();
		switch(ch){
			case '1':{
				int ind;
				do{
					load();
					puts("请选择要修改的项目：\n1--游戏模式\n2--是否进行合理性审查\n3--被开词条是否保留\n4--每位玩家词条数量（该项野局不生效）");
					ch=getch();
					ind=(ch^'0')-1;
				}while(ind<0||ind>C-1);
				if(ind==C-1){
					double tmp; 
					printf("目前每位玩家词条数量为%d，请在下方输入更改后玩家的词条数量：\n",cfg[C-1]);
					scanf("%lf",&tmp);
					cfg[C-1]=tmp;
					cfg[C-1]=max(cfg[C-1],1);
				}else{
					cout<<"项目“"<<st[ind][2]<<"”目前的状态是："<<st[ind][cfg[ind]]<<endl;
					cout<<"要将其更改至“"<<st[ind][cfg[ind]^1]<<"”吗？ 是--Y 否--其他键";
					ch=getch();
					if(ch=='y') cfg[ind]^=1;
				}
				break;
			}
			case '2':{
				save();
				break;
			}
			case '3':{
				cfg[0]=1,cfg[1]=1,cfg[2]=0,cfg[3]=1;
				save();
				break;
			}
			case '9':{
				save();
				return 0;
			}
			default:{
				puts("无效操作，请重新输入操作。");
				break;
			}
		}
	}
	return 0;}
