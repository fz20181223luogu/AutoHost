//V2.0 code by 180-fz201812.23
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
const int N=50,M=150,L=10,C=4,IC=6;  //N=player_mxcnt M=song_mxlen L=player_mxlive C=config_cnt IC=indicator_cnt
map<string,string>rep;
map<int,bool>idvis;
char ch;
string ind[IC]; //[已开：,剩余：,已亖：,答案：,＊,下家：] 直接写入会出现out.txt转码错误，故需从外部文件读入 
int cfg[C];
string blk;
int n,ret,win;
set<string>opened;
struct song{
	string st[M+5];
	int size,fa;
}; 
struct player{
	int id;
	song name[L+5];
	bool operator <(const player x){
		return this->id<x.id;
	}
	bool dead(){
		for(int i=1;i<=cfg[3];++i){
			if(name[i].fa==-1) return 0;
		}
		return 1;
	}
}a[N+5]; 
int _(char x){
	int cnt=0;
	for(int i=7;i>=0;--i){
		if(!(x&(1<<i))) break;
		cnt++;
	}
	if(!(cnt>>1)) cnt^=1;//spj for no UTF-8 need
	return cnt;
}
bool cmp1(player x,player y){return x.id<y.id;}
bool legal(song a){
	int cnt1=0,cnt2=0;
	for(int i=1;i<=a.size;++i){
		cnt1+=(isbig(a.st[i])||issmall(a.st[i]));
		cnt2+=(a.st[i]!=" ");
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
bool read1(){
	idvis.clear();
	string name;
	while(getline(in,name)){
		stringstream ss;
		ss<<name;ss>>a[++n].id;
		ss.clear();
		if(idvis.find(a[n].id)!=idvis.end()){
			in.close();
			puts("错误，id重复。任意键重新读取玩家信息。");
			ch=getch();
			n=0;
			return 1; 
		}
		idvis[a[n].id]=1;
		for(int l=1;l<=cfg[3];++l){
			if(!getline(in,name)){
				in.close();
				puts("错误，歌曲数量与玩家数量不匹配。任意键重新读取玩家信息。");
				ch=getch();
				n=0;
				return 1; 
			}
			int lst;
			a[n].name[l].size=0;
			for(int i=0;i<name.size();i+=lst){
				string tmp="";
				lst=_(name[i]);
				a[n].name[l].st[++a[n].name[l].size]=name.substr(i,lst);
				Cvt(a[n].name[l].st[a[n].name[l].size]);
			}
			if(!legal(a[n].name[l])&&cfg[1]) a[n].name[l].fa=a[n].id; else 
			a[n].name[l].fa=-1;
		}
	}
	return 0;
}
void read2(){
	idvis.clear();
	string name;
	int l=1;
	while(getline(in,name)){
		a[++n].id=n;
		int lst;
		a[n].name[l].size=0;
		for(int i=0;i<name.size();i+=lst){
			string tmp="";
			lst=_(name[i]);
			a[n].name[l].st[++a[n].name[l].size]=name.substr(i,lst);
			Cvt(a[n].name[l].st[a[n].name[l].size]);
		}
		if(!legal(a[n].name[l])&&cfg[1]) a[n].name[l].fa=a[n].id; else 
			a[n].name[l].fa=-1;
	}
}
void print(int cond,int &nxt){//cond=2--print+upd cond=1--print cond=0--no_print
	out.open("out.txt");
	out<<ind[0];//已开字符 
	for(set<string>::iterator it=opened.begin();it!=opened.end();++it){
		if(*it==" ") continue;
		out<<*it<<' ';
	}
	out<<endl<<endl;
	out<<ind[cond?1:3]<<endl;//1--剩余 3--答案
	for(int i=1;i<=n;++i){
		for(int l=1;l<=cfg[3];++l){
			if(a[i].name[l].fa!=-1&&cond) continue;
			out<<a[i].id;
			if(cfg[3]>1) out<<'-'<<l;
			out<<' ';
			for(int j=1;j<=a[i].name[l].size;++j){
				string cur=a[i].name[l].st[j];
				if(check(cur)&&cond) out<<"*"; else
				if(cur=="*"&&cond) out<<ind[4]; else //＊
				out<<cur;
			}
			out<<endl;
		}
	}
	out<<endl;
	out<<ind[2];//已亖词条 
	for(int i=1;i<=n;++i){
		for(int l=1;l<=cfg[3];++l){
			if(a[i].name[l].fa==-1) continue;
			out<<a[i].id;
			if(cfg[3]>1) out<<'-'<<l;
			out<<"("<<a[i].name[l].fa<<") ";
		}
	}
//	if(cond!=0&&cfg[0]){
//		out<<endl<<endl;
//		out<<ind[5];//下一个开 
//		if(cond==2){
//			do{
//				++nxt;
//				if(nxt>n) nxt=1;
//			}while(a[nxt].dead());	
//		}
//		out<<a[nxt].id;
//	}
	out.close();
	system("start out.txt"); 
}
int main(){
printf("自助主持 V2.1 By 180-fz201812.23\n\
使用前须知：由于C++的命令行窗口不支持输出部分特殊字符，故所有的游戏内操作均涉及文件。控制台仅输出提示信息。\n\
最多只支持%d人，歌曲长度只支持%d个字符，每位玩家最多%d条命。\n\
请确认settings.txt中的配置是否正确，若正确则任意键继续。可使用项目另配的config.exe进行可视化修改。\n",N,M,L);
	ch=getch();
	puts("从don't_modify_me.db中读取提示信息中...");
	in.open("don't_modify_me.db");
	for(int i=0;i<IC;++i) getline(in,ind[i]);
	string st,ed;
	while(getline(in,ed)){
		getline(in,st);
		rep[st]=ed;
	}
	in.close();
	puts("从settings.txt中读取玩家信息中...");
	in.open("settings.txt");
	for(int i=0;i<=C;++i)in>>cfg[i]; 
	in.close();
	for(int i=0;i<C-1;++i) cfg[i]=!!cfg[i];
	L2:puts("从list.txt中读取玩家信息中...");
	in.open("list.txt");
	if(cfg[0]){
		bool stat=read1(); //开盒 
		if(stat) goto L2;
	}
	else read2(); //野局 
	in.close();
	if(cfg[0]!=0&&n<=1){
		printf("错误，仅有%d个玩家的信息被放出。任意键重新读取玩家信息。\n",n);
		ch=getch();
		n=0;
		goto L2; 
	}
	sort(a+1,a+n+1,cmp1);
	ret=n;
	opened.insert(" ");//blank need to be shown 
	puts("读取完毕。");
	int nxt=0,lst=2;
	bool forcestop=0;
	for(int opcnt=1;ret>cfg[0];++opcnt){
		printf("-----------------第%d次操作开始-----------------\n",opcnt);
		print(lst,nxt);
		puts("当前游戏状态已保存至out.txt中，已重新打开该文件。");
		L1:puts("请在同目录下的cmd.txt中输入合法命令（格式可见附带readme.md），且请不要添加任何其他字符。");
		ch=getch();
		string nw;
		in.open("cmd.txt");
		int op;stringstream ss;
		getline(in,nw);
		if(nw=="STOP"){
			forcestop=1;
			break;
		}
		ss<<nw;ss>>op;
		ss.clear();
		getline(in,nw);
		switch(op){
			case 1:{
				in.close();
				if(nw==""){
					puts("错误：没有找到要开的字符。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
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
					in.close();
					goto L1; 
				}
				int x,y,px,py;
				stringstream ss;
				ss<<nw;ss>>x>>y;
				ss.clear();
				px=py=-1;
				int l=-1;
				in>>l;
				in.close();
				for(int i=1;i<=n;++i){
					if(a[i].id==x) px=i;
					if(a[i].id==y) py=i;
				}
				if(px==-1||py==-1){//User not found
					puts("错误：输入了不存在的玩家编号。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				if(l==-1){
					if(cfg[0]==0||cfg[3]==1) l=1;
					else{//Number not found
						puts("错误：输入了不存在的玩家给出词条编号。请重新输入合法命令，保存好后在本窗口任意键继续。");
						goto L1; 
					}
				}
				if(l>cfg[3]){
					puts("错误：输入了不存在的玩家给出词条编号。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				} 
				if(a[px].dead()||a[py].dead()){// executer(ee) is dead
					puts("错误：输入的两位玩家编号对应的玩家中有人已被开。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				} 
				if(a[px].name[l].fa!=-1){// number is dead
					puts("错误：输入的词条编号已被开。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				} 
				win=py;
				a[px].name[l].fa=a[py].id;
				if(a[px].dead())ret--;
				break;
			}
			case 3:{
				in.close();
				if(nw==""){
					puts("错误：没有找到要开的字符。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				if(_(nw[0])!=nw.size()){//Multiple characters
					puts("错误：输入了多个字符。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				if(isbig(nw)) nw[0]^=0x20;
				if(opened.find(nw)==opened.end()){//Duplicated request
					puts("错误：该字符未被开。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
//				cout<<"找到要开的字符为"<<nw<<endl; 
				opened.erase(nw);
				break;
			}
			case 4:{
				for(int i=0;i<nw.size();++i){
					if(isdigit(nw[i])||nw[i]==' ') continue;
					puts("错误：玩家编号中含有非法字符。请重新输入合法命令，保存好后在本窗口任意键继续。");
					in.close();
					goto L1; 
				}
				int x,px;
				stringstream ss;
				ss<<nw;ss>>x;
				ss.clear();
				px=-1;
				int l=-1;
				in>>l;
				in.close();
				for(int i=1;i<=n;++i){
					if(a[i].id==x) px=i;
				}
				if(px==-1){//User not found
					puts("错误：输入了不存在的玩家编号。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				if(l==-1){
					if(cfg[0]==0||cfg[3]==1) l=1;
					else{//Number not found
						puts("错误：输入了不存在的玩家给出词条编号。请重新输入合法命令，保存好后在本窗口任意键继续。");
						goto L1; 
					}
				}
				if(l>cfg[3]){
					puts("错误：输入了不存在的玩家给出词条编号。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				}
				if(a[px].name[l].fa==-1){// number is dead
					puts("错误：输入的词条编号未被开。请重新输入合法命令，保存好后在本窗口任意键继续。");
					goto L1; 
				} 
				if(a[px].dead())ret++;
				a[px].name[l].fa=-1;
				break;
			}
			default:{
				printf("命令不合法，请重新输入合法操作。\n",ch);
				goto L1;
				break;
			}
		}
		lst=(op==1?2:1);
		puts("操作成功。");
	}
	print(0,nxt);
	printf("游戏结束。");
	if(cfg[0]&&!forcestop) printf("%d号玩家胜利。",a[win].id);
	printf("\n完整的结算信息已放至out.txt中。任意键关闭程序。");
	ch=getch(); 
	return 0;}
