//code by 180-fz201812.23   �����Ұ����ע�͵���88�����±��롣 
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
	printf("ʹ��ǰ��֪������C++�������д��ڲ�֧��������������ַ��������е���Ϸ�ڲ������漰�ļ�������̨�������ʾ��Ϣ��\n���ֻ֧��%d�ˣ���������ֻ֧��%d���ַ���\n�����������\n",N,M);
	ch=getch();
	puts("��don't_modify_me�ж�ȡ��ʾ��Ϣ��...");
	in.open("don't_modify_me");
	for(int i=0;i<IC;++i) getline(in,ind[i]);
	string st,ed;
	while(getline(in,ed)){
		getline(in,st);
		rep[st]=ed;
	}
	in.close();
	L2:puts("��list.txt�ж�ȡ�����Ϣ��...");
	in.open("list.txt");
	idvis.clear();
	while(in>>a[++n].id){
		if(idvis.find(a[n].id)!=idvis.end()){
			in.close();
			puts("����id�ظ�����������¶�ȡ�����Ϣ��");
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
		if(!legal(a[n])) a[n].fa=a[n].id; else //�����Ұ�֣�����Ҫ������������飩����һ��ע�͵� 
		a[n].fa=-1;
	}
	--n;
	in.close();
	if(n<=1){
		puts("��������2����ҵ���Ϣ���ų�����������¶�ȡ�����Ϣ��");
		ch=getch();
		n=0;
		goto L2; 
	}
	sort(a+1,a+n+1,cmp1);
	ret=n;
	opened.insert(" ");//blank need to be shown 
	puts("��ȡ��ϡ�");
	for(int opcnt=1;ret>1;++opcnt){
		printf("-----------------��%d�β�����ʼ-----------------\n",opcnt);
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
		puts("��ǰ��Ϸ״̬�ѱ�����out.txt�У������´򿪸��ļ���");
		L1:puts("����ͬĿ¼�µ�cmd.txt���������һ���ַ���ʾҪ�����ַ������������ֱַ��ʾ��������ұ�ż�ִ�в�������ұ�ţ���һ���ո���������벻Ҫ����κ������ַ���");
		ch=getch();
		string nw;
		in.open("cmd.txt");
		getline(in,nw);
		in.close();
		if(nw==""){
			puts("����û���ҵ��κ����롣����������Ϸ��������ú��ڱ����������������");
			goto L1; 
		}
//		if(nw=="STOP") break; //���е����ã����ڿ��ٽ�����Ϸ 
		int cntblk=1;
		for(int i=0;i<nw.size();++i) cntblk+=(nw[i]==' ');
		switch(cntblk){
			case 1:{
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
					puts("���������˲����ڵ���ұ�š�����������Ϸ��������ú��ڱ����������������");
					goto L1; 
				}
				if(a[px].fa!=-1||a[py].fa!=-1){// executer(ee) is dead
					puts("�����������λ��ұ�Ŷ�Ӧ������������ѱ���������������Ϸ��������ú��ڱ����������������");
					goto L1; 
				} 
				win=py;
				a[px].fa=a[py].id;
				ret--;
				break;
			}
			default:{
				printf("����Ϸ�������������Ϸ�������\n",ch);
				goto L1;
				break;
			}
		}
		puts("�����ɹ���");
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
	printf("��Ϸ������%d�����ʤ����\n�����Ľ�����Ϣ�ѷ���out.txt�С�������رճ���",a[win].id);
	ch=getch(); 
	return 0;}
