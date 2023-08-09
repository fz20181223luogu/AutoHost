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
string ind[IC]; //[�ѿ���,ʣ�ࣺ,�с���,�𰸣�,��,�¼ң�] ֱ��д������out.txtת����󣬹�����ⲿ�ļ����� 
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
			puts("����id�ظ�����������¶�ȡ�����Ϣ��");
			ch=getch();
			n=0;
			return 1; 
		}
		idvis[a[n].id]=1;
		for(int l=1;l<=cfg[3];++l){
			if(!getline(in,name)){
				in.close();
				puts("���󣬸������������������ƥ�䡣��������¶�ȡ�����Ϣ��");
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
	out<<ind[0];//�ѿ��ַ� 
	for(set<string>::iterator it=opened.begin();it!=opened.end();++it){
		if(*it==" ") continue;
		out<<*it<<' ';
	}
	out<<endl<<endl;
	out<<ind[cond?1:3]<<endl;//1--ʣ�� 3--��
	for(int i=1;i<=n;++i){
		for(int l=1;l<=cfg[3];++l){
			if(a[i].name[l].fa!=-1&&cond) continue;
			out<<a[i].id;
			if(cfg[3]>1) out<<'-'<<l;
			out<<' ';
			for(int j=1;j<=a[i].name[l].size;++j){
				string cur=a[i].name[l].st[j];
				if(check(cur)&&cond) out<<"*"; else
				if(cur=="*"&&cond) out<<ind[4]; else //��
				out<<cur;
			}
			out<<endl;
		}
	}
	out<<endl;
	out<<ind[2];//�с����� 
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
//		out<<ind[5];//��һ���� 
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
printf("�������� V2.1 By 180-fz201812.23\n\
ʹ��ǰ��֪������C++�������д��ڲ�֧��������������ַ��������е���Ϸ�ڲ������漰�ļ�������̨�������ʾ��Ϣ��\n\
���ֻ֧��%d�ˣ���������ֻ֧��%d���ַ���ÿλ������%d������\n\
��ȷ��settings.txt�е������Ƿ���ȷ������ȷ���������������ʹ����Ŀ�����config.exe���п��ӻ��޸ġ�\n",N,M,L);
	ch=getch();
	puts("��don't_modify_me.db�ж�ȡ��ʾ��Ϣ��...");
	in.open("don't_modify_me.db");
	for(int i=0;i<IC;++i) getline(in,ind[i]);
	string st,ed;
	while(getline(in,ed)){
		getline(in,st);
		rep[st]=ed;
	}
	in.close();
	puts("��settings.txt�ж�ȡ�����Ϣ��...");
	in.open("settings.txt");
	for(int i=0;i<=C;++i)in>>cfg[i]; 
	in.close();
	for(int i=0;i<C-1;++i) cfg[i]=!!cfg[i];
	L2:puts("��list.txt�ж�ȡ�����Ϣ��...");
	in.open("list.txt");
	if(cfg[0]){
		bool stat=read1(); //���� 
		if(stat) goto L2;
	}
	else read2(); //Ұ�� 
	in.close();
	if(cfg[0]!=0&&n<=1){
		printf("���󣬽���%d����ҵ���Ϣ���ų�����������¶�ȡ�����Ϣ��\n",n);
		ch=getch();
		n=0;
		goto L2; 
	}
	sort(a+1,a+n+1,cmp1);
	ret=n;
	opened.insert(" ");//blank need to be shown 
	puts("��ȡ��ϡ�");
	int nxt=0,lst=2;
	bool forcestop=0;
	for(int opcnt=1;ret>cfg[0];++opcnt){
		printf("-----------------��%d�β�����ʼ-----------------\n",opcnt);
		print(lst,nxt);
		puts("��ǰ��Ϸ״̬�ѱ�����out.txt�У������´򿪸��ļ���");
		L1:puts("����ͬĿ¼�µ�cmd.txt������Ϸ������ʽ�ɼ�����readme.md�������벻Ҫ����κ������ַ���");
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
					puts("����û���ҵ�Ҫ�����ַ�������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(_(nw[0])!=nw.size()){//Multiple characters
					puts("���������˶���ַ�������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(isbig(nw)) nw[0]^=0x20;
				if(opened.find(nw)!=opened.end()){//Duplicated request
					puts("���󣺸��ַ��ѱ���������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
//				cout<<"�ҵ�Ҫ�����ַ�Ϊ"<<nw<<endl; 
				opened.insert(nw);
				break;
			}
			case 2:{
				for(int i=0;i<nw.size();++i){
					if(isdigit(nw[i])||nw[i]==' ') continue;
					puts("������ұ���к��зǷ��ַ�������������Ϸ��������ú��ڱ����������������");
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
					puts("���������˲����ڵ���ұ�š�����������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(l==-1){
					if(cfg[0]==0||cfg[3]==1) l=1;
					else{//Number not found
						puts("���������˲����ڵ���Ҹ���������š�����������Ϸ��������ú��ڱ����������������");
						goto L1; 
					}
				}
				if(l>cfg[3]){
					puts("���������˲����ڵ���Ҹ���������š�����������Ϸ��������ú��ڱ����������������");
					goto L1; 
				} 
				if(a[px].dead()||a[py].dead()){// executer(ee) is dead
					puts("�����������λ��ұ�Ŷ�Ӧ������������ѱ���������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				} 
				if(a[px].name[l].fa!=-1){// number is dead
					puts("��������Ĵ�������ѱ���������������Ϸ��������ú��ڱ����������������");
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
					puts("����û���ҵ�Ҫ�����ַ�������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(_(nw[0])!=nw.size()){//Multiple characters
					puts("���������˶���ַ�������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(isbig(nw)) nw[0]^=0x20;
				if(opened.find(nw)==opened.end()){//Duplicated request
					puts("���󣺸��ַ�δ����������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
//				cout<<"�ҵ�Ҫ�����ַ�Ϊ"<<nw<<endl; 
				opened.erase(nw);
				break;
			}
			case 4:{
				for(int i=0;i<nw.size();++i){
					if(isdigit(nw[i])||nw[i]==' ') continue;
					puts("������ұ���к��зǷ��ַ�������������Ϸ��������ú��ڱ����������������");
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
					puts("���������˲����ڵ���ұ�š�����������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(l==-1){
					if(cfg[0]==0||cfg[3]==1) l=1;
					else{//Number not found
						puts("���������˲����ڵ���Ҹ���������š�����������Ϸ��������ú��ڱ����������������");
						goto L1; 
					}
				}
				if(l>cfg[3]){
					puts("���������˲����ڵ���Ҹ���������š�����������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(a[px].name[l].fa==-1){// number is dead
					puts("��������Ĵ������δ����������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				} 
				if(a[px].dead())ret++;
				a[px].name[l].fa=-1;
				break;
			}
			default:{
				printf("����Ϸ�������������Ϸ�������\n",ch);
				goto L1;
				break;
			}
		}
		lst=(op==1?2:1);
		puts("�����ɹ���");
	}
	print(0,nxt);
	printf("��Ϸ������");
	if(cfg[0]&&!forcestop) printf("%d�����ʤ����",a[win].id);
	printf("\n�����Ľ�����Ϣ�ѷ���out.txt�С�������رճ���");
	ch=getch(); 
	return 0;}
