//code by 180-fz201812.23
#include<bits/stdc++.h>
#include<conio.h>
#include<fstream>
#include<windows.h>
typedef long long ll;
using namespace std;
const int C=4;
int cfg[C];
string st[C-1][3]={"Ұ��","����","��Ϸģʽ","������","����","�Ƿ���к��������","������","����","���������Ƿ���"};
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
		puts("��ǰ��Ϸģʽ��");
		for(int ind=0;ind<C-1;++ind) cout<<"��Ŀ��"<<st[ind][2]<<"��Ŀǰ��״̬�ǣ�"<<st[ind][cfg[ind]]<<endl;
		printf("Ŀǰÿλ��Ҵ�������Ϊ%d\n\n",cfg[3]);
		puts("��ѡ�������\n1--��������\n2--��������\n3--���ò���������\n9--�������ò��˳�����\n\n�벻Ҫ��;ǿ���˳����������ÿ����޷����棡����"); 
		char ch=getch();
		switch(ch){
			case '1':{
				int ind;
				do{
					load();
					puts("��ѡ��Ҫ�޸ĵ���Ŀ��\n1--��Ϸģʽ\n2--�Ƿ���к��������\n3--���������Ƿ���\n4--ÿλ��Ҵ�������������Ұ�ֲ���Ч��");
					ch=getch();
					ind=(ch^'0')-1;
				}while(ind<0||ind>C-1);
				if(ind==C-1){
					double tmp; 
					printf("Ŀǰÿλ��Ҵ�������Ϊ%d�������·�������ĺ���ҵĴ���������\n",cfg[C-1]);
					scanf("%lf",&tmp);
					cfg[C-1]=tmp;
					cfg[C-1]=max(cfg[C-1],1);
				}else{
					cout<<"��Ŀ��"<<st[ind][2]<<"��Ŀǰ��״̬�ǣ�"<<st[ind][cfg[ind]]<<endl;
					cout<<"Ҫ�����������"<<st[ind][cfg[ind]^1]<<"���� ��--Y ��--������";
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
				puts("��Ч���������������������");
				break;
			}
		}
	}
	return 0;}
