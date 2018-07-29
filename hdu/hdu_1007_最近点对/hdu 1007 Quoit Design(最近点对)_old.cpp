#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

typedef double db;

const int M = 100005;
const db INF = 1e9;
const db NZ = 0.005;
const db EPS = 1e-6;

struct node
{
    double x,y;
    int id;
}nd[M];

node tnd[M];
double res;
int n;
int point_1,point_2;
double x[M],y[M];

void init();
void sol();
void divide(int s,int q,double mid);
double pdistance(int i,int j);
void merge(int s,int qmid,int q,double mid);

bool cmp(const node & a,const node & b)
{
    if(a.x == b.x) return a.y > b.y;
    return a.x < b.x;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        if(n == 0) break;
        init();
        sol();
    }
    return 0;
}

double pdistance(int i,int j)
{
    return sqrt((nd[i].x-nd[j].x)*(nd[i].x - nd[j].x) + (nd[i].y-nd[j].y)*(nd[i].y-nd[j].y));
}

void init()
{
    for(int i = 0;i < n;i++)
    {
        scanf("%lf%lf",&nd[i].x,&nd[i].y);
        nd[i].id = i+1;
    }
    res = INF;
    for(int i = 0;i < n;i++)
    {
        x[nd[i].id] = nd[nd[i].id-1].x;
        y[nd[i].id] = nd[nd[i].id-1].y;
    }
    sort(nd,nd+n,cmp);
    return;
}

void sol()
{
    double mid;
    mid = (nd[0].x+nd[n-1].x)/(2.0);
    divide(0,n-1,mid);
    
    int id1,id2;
    id1 = point_1;
    id2 = point_2;
    res /= 2;
    if(fabs(res) <NZ) res = 0.0;
    printf("%.2lf\n",res);
    return;
}

void divide(int s,int q,double mid)
{
    int pmid;
    db d;
    if(nd[s].x -nd[q].x > -EPS && nd[s].x - nd[q].x < EPS)
    {
        for(int i = s;i < q;i++)
        {
            d = pdistance(i,i+1);
            if(res > d)
            {
                res = d;
                point_1 = i;
                point_2 = i + 1;
            }
        }
        return;
    }
    for(pmid = s;nd[pmid].x - mid < -EPS;pmid++);
    pmid--;
    divide(s,pmid,(nd[s].x + nd[pmid].x) / 2.0);
    divide(pmid + 1,q,(nd[pmid + 1].x + nd[q].x) / 2.0);
    merge(s,pmid,q,mid);
    return;
}

void merge(int s,int pmid,int q,double mid)
{
    int pt1,pt2,pt,cnt;
    db d;
    pt1 = s,pt2 = pmid + 1;
    pt = s;
    
    while(pt1 <= pmid && pt2 <= q)
    {
        if(nd[pt2].y - nd[pt1].y > EPS)
            tnd[pt++] = nd[pt2++];
        else
            tnd[pt++] = nd[pt1++];
    }
    while(pt1 <= pmid)
        tnd[pt++] = nd[pt1++];
    while(pt2 <= q)
        tnd[pt++] = nd[pt2++];
    
    for(int i = s; i <= q;i++)
        nd[i] = tnd[i];
    for(int i = s;i <= q;i++)
    {
        if(nd[i].x - mid < res + EPS || mid - nd[i].x < res + EPS)
        {
            cnt = 0;
            for(int j = i + 1;j <= q && cnt <= 6 && nd[i].y - nd[j].y <= res + EPS;j++)
            {
                d = pdistance(i,j);
                if(d + EPS < res)
                {
                    res = d;
                    point_1 = i;
                    point_2 = j;
                }
                cnt++;
            }
        }
    }
    return;
}
        
