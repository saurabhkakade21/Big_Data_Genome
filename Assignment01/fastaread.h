#ifndef FASTAREAD_H
#define FASTAREAD_H
#endif

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class FASTAread{
public:
char** head;
char** dataseq;
int noflines;
string filepath;
ifstream input;

FASTAread(){
        cout<< "constructor called"<< endl;
        }
        
FASTAread(string fp){
filepath=fp;
input.open(filepath.c_str());
}


void read(int no_lines){
        noflines=no_lines;
        head=new char*[no_lines];
        dataseq= new char*[no_lines];
        for(int i=0;i<=no_lines;i++){
                head[i]=new char[50];
                dataseq[i]=new char[50];
        }
        for(int i=0;i<=no_lines;i++){
                input>>head[i];
                input>>dataseq[i];
        }
}
int strcmps(char *p, char*q){
        for(int i=0;i<50;i++){
        if(p[i]-q[i]>0){
                return 1;
}
        else if (p[i]-q[i]<0){
                return -1;
}
        else{
 continue;
        }
}
}

void merge_sort(char *arr[], int a, int b, int c)
{
    int x, y, z;
    int f1 = b - a + 1;
    int f2 =  c - b;
    char  *left[f1];
    char  *right[f2];
        for (x = 0; x < f1; x++)
        left[x] = arr[a + x];
        for (y = 0; y < f2; y++)
        right[y] = arr[b + 1+ y];


    x = 0;
    y = 0;
    z = a;
    while (x < f1 && y < f2)
    {
        if (strcmps(left[x],right[y])<0)
        {
            arr[z] = left[x];
            x++;
        }
        else
        {
            arr[z] = right[y];
            y++;
        }
        z++;
    }

    while (x < f1)
    {
        arr[z] = left[x];
        x++;
        z++;
    }

    while (y < f2)
    {
        arr[z] = right[y];
        y++;
        z++;
    }
}

void my_merge_sort(char *arr[], int a, int c)
{
    if (a < c)
    {
        int b = a+(c-a)/2;
        my_merge_sort(arr, a, b);
        my_merge_sort(arr, b+1, c);

        merge_sort(arr, a, b, c);
    }
}

void sort_data(){
cout << "sorting started" << endl;
my_merge_sort(dataseq,0,noflines-1);
cout << "after sorting" << endl;
for(int i=0;i<20;i++){
        cout << dataseq[i] << endl;
}

}

void compute_statistics()
{
no_char_cnt();
no_reads();
unique_seq_frag();
}

void no_char_cnt(){
int counta=0;
int countc=0;
int countg=0;
int countt=0;
for(int i=0;i<noflines;i++)
{
for(int j=0;j<50;j++)
{
if(dataseq[i][j]=='A')
counta++;
else if(dataseq[i][j]=='C')
countc++;
else if(dataseq[i][j]=='G')
countg++;
else if(dataseq[i][j]=='T')
countt++;
else{
int n=0;
n++;
}
}

}
cout << "A:"<<counta << endl;
cout << "C:"<<countc << endl;
cout << "G:"<<countg << endl;
cout << "T:"<<countt << endl;
}

void no_reads()
{
cout << "entered read:" << endl;
int outarr[14] = {0};
for(int i=0;i<noflines;i++)
{
int l=0;
int j=0;
int cnt = 11;
while(cnt != 0){
if(head[i][j] == '_'){
j= j + 1;
break;
}
cnt--;
j++;
}
int c = 0;
for(int k = 0; k < 28;k++){
  if(head[i][j] != '_'){
     outarr[c] = outarr[c] + (int)head[i][j] - '0';
     c++;
     }
  j++;

}
}
for(int t = 0 ; t < 14; t++)
{
cout <<"Dataset" <<  t+1 << "is:" << outarr[t] << endl;
}
}

void unique_seq_frag(){
int head_frag=0;
int data_frag=0;
for(int k=0;k<noflines;k++){
 head_frag++;
}
for(int m=0;m<noflines;m++){
data_frag++;
}
cout << "UNIQUE DATA FRAGMENTS:" << head_frag+data_frag << endl;
}

void delete_my_array(){
cout << "Array deleted sucessfully" << endl;
}
~FASTAread(){
delete[] head;
delete[] dataseq;
delete_my_array();
}
};

