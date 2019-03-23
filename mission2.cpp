#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
using namespace std;
class Number;
void Exchange(string&,string&,int &fh);
void input(string,vector<int>&);
Number operator+(const Number&X,const Number&Y);
Number operator-(const Number&X,const Number&Y);
Number operator*(const Number&X,const Number&Y);
Number operator>(const Number&X,const Number&Y);
Number operator<(const Number&X,const Number&Y);
ostream& operator<<(ostream &out,const Number&X);
istream& operator>>(istream &in ,const Number&X);
class Number{
public:
    Number(string a0,vector<int> A0,char FH0,int length0)://���캯��
        a(a0),A(A0),FH(FH0),length(length0){}
    void display(){//�������
        if(FH=='-') cout<<'-';
        cout<<a<<endl;
    }
    vector<int>A;//AΪ���ֵĵ���
    int length;//lengthΪ���ֳ���
    string a;//aΪ˳�������
    ~Number(){/*cout<<"��������"<<endl;*/}//��������
private:
    char FH;//����Ϊ+ 1������Ϊ- 0��
};

int main()
{
    string a,b;int fh=1;
    vector<int>A(1000),B(1000),M0(3000);
    char FHa='+',FHb='+';
    cin>>a>>b;
    if(a[0]=='-') {FHa='-';a.erase(0,1);} if(a[0]=='+') {a.erase(0,1);}//�жϷ��ţ���ɾ������
    if(b[0]=='-') {FHb='-';b.erase(0,1);} if(b[0]=='+') {b.erase(0,1);}//ͬ��
    Exchange(a,b,fh);//ʹ�����Ϊa>=b
    input(a,A);input(b,B);//��stringת��Ϊvector
    Number X(a,A,FHa,a.size()),Y(b,B,FHb,b.size()),M("0",M0,'+',0);
    cout<<"Addition     =";M=X+Y;M.display();//�ӷ�
    cout<<"Subtraction  =";M=X-Y;if(fh==-1)cout<<'-';M.display();//����
    cout<<"Multiply     =";M=X*Y;M.display();//�˷�
}

void input(string a,vector<int>&A)
{
    for(int i=0,j=0;i<a.size();i++){
        if(a[i]<='9'&&a[i]>='0') {A[j]=a[i]-'0';j++;}
    }//ɸѡ������
    int t;
    for(int i=0;i<a.size()/2;i++){
        t=A[i];A[i]=A[a.size()-1-i];A[a.size()-1-i]=t;
    }//ʹ���ֵ���洢
}

void Exchange(string&a,string&b,int &fh)//a>=b
{
    string c;
    if(a.size()<b.size()){c=a;a=b;b=c;fh=-1;}
    if(a.size()==b.size()) if(a<b) {c=a;a=b;b=c;fh=-1;}//�ж�a��b��С����ʹ��a>=b�����
}
Number operator+(const Number&X,const Number&Y)
{
    int t=0,cnt=0;
    vector<int> M(2000,0);
    for(int i=0;i<X.length+1;i++){
        M[i]=(t+X.A[i]+Y.A[i])%10;
        t=(t+X.A[i]+Y.A[i])/10;
    }//�ӷ�����
    if(t!=0) cnt=1;
    string a="";
    for(int i=X.length;i>=0;i--){
        if(M[i]==0&&i==X.length) continue;
        a=a+char(M[i]+'0');
    }//������������a��
    return Number(a,M,'+',X.length+cnt);
}
Number operator-(const Number&X0,const Number&Y0)
{
    int t=0,q=0;
    Number X(X0),Y(Y0);
    vector<int> M(2000,0);
    for(int i=0;i<X.length;i++){
        if(X.A[i]-Y.A[i]+t<0){
            M[i]=10+X.A[i]-Y.A[i];
            t=-1;
            X.A[i+1]--;
        }
        else{
            t=0;
            M[i]=X.A[i]-Y.A[i];
        }
    }//��������
    string a="";
    for(int i=X.length+Y.length;i>=0;i--){
        if(M[i]!=0) q=1;
        if(q==0) continue;
        a=a+char(M[i]+'0');
    }//�������a�У���ɾ�������0.
    if(q==0) cout<<'0';//���ȫΪ0ʱ�����һ��0
    return Number(a,M,'+',X.length);
}
Number operator*(const Number&X,const Number&Y)
{
    vector<int> M(3000,0);
    int t=0,p=0,q=0;string a="";
    for(int i=0;i<X.length;i++)
        for(int j=0;j<Y.length;j++){
            M[i+j]=M[i+j]+X.A[i]*Y.A[j];
             //cout<<"M["<<i+j<<"]="<<M[i+j]<<" ";
        }//�˷�����
    for(int i=0;i<X.length+Y.length+1;i++){
        p=M[i];
        M[i]=(M[i]+t)%10;
        t=(p+t)/10;
        //cout<<M[i]<<" ";
    }
   // cout<<"X.length+Y.length="<<X.length+Y.length<<endl;
    for(int i=X.length+Y.length;i>=0;i--){
        if(M[i]!=0) q=1;
        if(q==0) continue;
        a=a+char(M[i]+'0');
    }//�������a�У���ɾ�������0.
    if(q==0) cout<<'0';//���ȫΪ0ʱ�����һ��0
    return Number(a,M,'+',X.length+Y.length+1);
}
Number operator>(const Number&X,const Number&Y)
{
    string c;bool fh;
    if(X.a.size()<Y.a.size())    fh=false;
    if(X.a.size()==Y.a.size())   if(X.a<Y.a) fh=false;
    if(fh) return X;else return Y;//�������ʽ���������ز���ʽ��ߵ�����
}
Number operator<(const Number&X,const Number&Y)
{
    string c;bool fh;
    if(X.a.size()<Y.a.size())    fh=true;
    if(X.a.size()==Y.a.size())   if(X.a<Y.a) fh=true;
    if(fh) return X;else return Y;//�������ʽ���������ز���ʽ��ߵ�����
}
ostream& operator<<(ostream &out,const Number&X)
{
    out<<X.a<<endl;
    return out;
}
istream& operator>>(istream &in,Number&X)
{
    string b;
    in>>b;
    X.a=b;
    return in;
}








