//code by 180-fz201812.23   如果玩野局请注释掉第88行重新编译。 
#include<bits/stdc++.h>
#include<conio.h>
#include<fstream>
#define isbig(x)   x.size()==1&&'A'<=x[0]&&x[0]<='Z'
#define issmall(x) x.size()==1&&'a'<=x[0]&&x[0]<='z'
#define Cvt(st) if(rep.find(st)!=rep.end())st=rep[st];
typedef long long ll;
using namespace std;
ifstream in;
ofstream out;
const int N=1000,M=1000;
map<string,string>rep;
map<int,bool>idvis; 
char ch;
const int IC=5;
string ind[IC]; 
string blk;
struct song{
	int id,size;
	string name[M+5];
	int fa;
	bool operator <(const song x){
		return this->id<x.id;
	}
}a[N+5]; 
set<string>opened;
int n,ret,win;
int _(char x){
	int cnt=0;
	for(int i=7;i>=0;--i){
		if(!(x&(1<<i))) break;
		cnt++;
	}
	if(cnt==0) cnt++;//spj for no UTF-8 need
	return cnt;
}
bool cmp1(song x,song y){return x.id<y.id;}
bool legal(song a){
	int cnt1=0,cnt2=0;
	for(int i=1;i<=a.size;++i){
		cnt1+=(isbig(a.name[i])||issmall(a.name[i]));
		cnt2+=(a.name[i]!=" ");
	}
	cnt1<<=1;
	return cnt1>=cnt2;
} 
bool check(string cur){
	if(opened.find(cur)!=opened.end()) return 0;
	if(!issmall(cur)) return 1;
	cur[0]^=32;
	return opened.find(cur)==opened.end(); 
}
int main(){
	printf("使用前须知：由于C++的命令行窗口不支持输出部分特殊字符，故所有的游戏内操作均涉及文件。控制台仅输出提示信息。\n最多只支持%d人，歌曲长度只支持%d个字符。\n任意键继续。\n",N,M);
	ch=getch();
	puts("从don't_modify_me中读取提示信息中...");
	in.open("don't_modify_me");
	for(int i=0;i<IC;++i) getline(in,ind[i]);
	string st,ed;
	while(getline(in,ed)){
		getline(in,st);
		rep[st]=ed;
	}
	in.close();
	L2:puts("从list.txt中读取玩家信息中...");
	in.open("list.txt");
	idvis.clear();
	while(in>>a[++n].id){
		if(idvis.find(a[n].id)!=idvis.end()){
			in.close();
			puts("错误，id重复。任意键重新读取玩家信息。");
			ch=getch();
			n=0;
			goto L2; 
		}
		idvis[a[n].id]=1;
		string name;
		getline(in,name);
		int lst;
		a[n].size=0;
		for(int i=1;i<name.size();i+=lst){
			string tmp="";
			lst=_(name[i]);
			a[n].name[++a[n].size]=name.substr(i,lst);
			Cvt(a[n].name[a[n].size]);
		}
		if(!legal(a[n])) a[n].fa=a[n].id; else //如果玩野局（即不要曲名合理性审查）把这一行注释掉 
		a[n].fa=-1;
	}
	--n;
	in.close();
	if(n<=1){
		puts("错误，少于2个玩家的信息被放出。任意键重新读取玩家信息。");
		ch=getch();
		n=0;
		goto L2; 
	}
	sort(a+1,a+n+1,cmp1);
	ret=n;
	opened.insert(" ");//blank need to be shown 
	puts("读取完毕。");
	for(int opcnt=1;ret>1;++opcnt){
		printf("-----------------第%d次操作开始-----------------\n",opcnt);
		out.open("out.txt");
		out<<ind[0];
		for(set<string>::iterator it=opened.begin();it!=opened.end();++it){
			if(*it==" ") continue;
			out<<*it<<' ';
		}
		out<<endl<<endl;
		out<<ind[1]<<endl;
		for(int i=1;i<=n;++i){
			if(a[i].fa!=-1) continue;
			out<<a[i].id<<' ';
			for(int j=1;j<=a[i].size;++j){
				string cur=a[i].name[j];
				if(check(cur)) out<<"*"; else
				if(cur=="*") out<<ind[4]; else
				out<<cur;
			}
			out<<endl;
		}
		out<<endl;
		out<<ind[2];
		for(int i=1;i<=n;++i){
			if(a[i].fa==-1) continue;
			out<<a[i].id<<"("<<a[i].fa<<") ";
		}
		out.close();
		system("start out.txt"); 
		puts("当前游戏状态已保存至out.txt中，已重新打开该文件。");
		L1:puts("请在同目录下的cmd.txt中输入命令：一个字符表示要开的字符，或两个数字分别表示被开的玩家编号及执行操作的玩家编号（用一个空格隔开）。请不要添加任何其他字符。");
		ch=getch();
		string nw;
		in.open("cmd.txt");
		getline(in,nw);
		in.close();
		if(nw==""){
			puts("错误：没有找到任何输入。请重新输入合法命令，保存好后在本窗口任意键继续。");
			goto L1; 
		}
//		if(nw=="STOP") break; //本行调试用，用于快速结束游戏 
		int cntblk=1;
		for(int i=0;i<nw.size();++i) cntblk+=(nw[i]==' ');
		switch(cntblk){
			case 1:{
				if(_(nw[0])!=nw.size()){//Multiple characters
					puts("错误：输入了多个字符。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				if(isbig(nw)) nw[0]^=0x20;
				if(opened.find(nw)!=opened.end()){//Duplicated request
					puts("错误：该字符已被开。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
//				cout<<"找到要开的字符为"<<nw<<endl; 
				opened.insert(nw);
				break;
			}
			case 2:{
				for(int i=0;i<nw.size();++i){
					if(isdigit(nw[i])||nw[i]==' ') continue;
					puts("错误：玩家编号中含有非法字符。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				int x,y,px,py;
				stringstream ss;
				ss<<nw;ss>>x>>y;
				px=py=-1;
				for(int i=1;i<=n;++i){
					if(a[i].id==x) px=i;
					if(a[i].id==y) py=i;
				}
				if(px==-1||py==-1){//User not found
					puts("错误：输入了不存在的玩家编号。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				if(a[px].fa!=-1||a[py].fa!=-1){// executer(ee) is dead
					puts("错误：输入的两位玩家编号对应的玩家中有人已被开。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				} 
				win=py;
				a[px].fa=a[py].id;
				ret--;
				break;
			}
			default:{
				printf("命令不合法，请重新输入合法操作。\n",ch);
				goto L1;
				break;
			}
		}
		puts("操作成功。");
	}
	out.open("out.txt");
	out<<ind[0];
	for(set<string>::iterator it=opened.begin();it!=opened.end();++it){
		out<<*it<<' ';
	}
	out<<endl<<endl<<ind[3]<<endl;
	for(int i=1;i<=n;++i){
		out<<a[i].id<<' ';
		for(int j=1;j<=a[i].size;++j){
			string cur=a[i].name[j];
			out<<cur;
		}
		out<<endl;
	}
	out<<endl<<ind[2];
	for(int i=1;i<=n;++i){
		if(a[i].fa==-1) continue;
		out<<a[i].id<<"("<<a[i].fa<<") ";
	}
	out.close();
	system("notepad out.txt"); 
	printf("游戏结束，%d号玩家胜利。\n完整的结算信息已放至out.txt中。任意键关闭程序。",a[win].id);
	ch=getch(); 
	return 0;}
