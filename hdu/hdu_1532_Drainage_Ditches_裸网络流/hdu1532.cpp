#include <stdio.h>  //hdu1532
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXNUM = 2100000000 ;   //权值上限
const int MAXPT = 290 ;            //顶点数上限
const int MAXEG = MAXPT*MAXPT*2 ; //边数上限
const int MAXQUE = 200000 ;	 // 队列长度
//    s = 1 ; // 源点  t = n ; // 汇点
class MNF_SAP{
	private:
		//int m,n;
    	int s,t,top;
    	int d[MAXPT];     //距离标号
    	int pre[MAXPT];   //前置顶点
    	int flow[MAXPT];  //到当前点为止，所有弧的最小值
    	int cur[MAXPT];   //当前弧
    	int cnt[MAXPT];   //k标号出现次数
    	int que[MAXPT*2],ft,rt;
    	bool vis[MAXPT];
    	void init_d(){
        	int i,u;
        	memset(vis,0,sizeof(vis));
        	ft=rt=0;
        	d[t]=0;
        	vis[t]=true;
        	que[++rt]=t;
        	while(ft!=rt){
            	u=que[(++ft)%MAXQUE];
            	for(i=gra[u]; i; i=E[i].next){
                	if(!vis[E[i].v] && !E[i].w){
                    	d[E[i].v]=d[u]+1;
                    	vis[E[i].v]=true;
                    	que[(++rt)%MAXQUE]=E[i].v;
                	}
                }
        	}
    	}
	public:
    	struct{
        	int v,w,next;
    	} E[MAXEG];
    	int n;   // 点数
    	int gra[MAXPT];
    	MNF_SAP(){top=1;}
    	~MNF_SAP(){}
    	int SAP(){
    	    int u,v,i,maxflow=0;   //总最大流
    	    s=1;
    	    t=n;
    	    u=s;
    	    flow[s]=MAXNUM;
    	    for(i=1; i<=n; i++) cur[i]=gra[i]; //当前弧初始化
    	    init_d();
    	    for(i=1; i<=n; i++)
    	        cnt[d[i]]++;
    	    cnt[0]=n;
    	    while(d[s]<n){
    	        for(i=cur[u]; i; i=E[i].next)        //找允许弧
    	            if(E[i].w && d[E[i].v]+1==d[u]) break;
    	        if(i){ //存在允许弧
    	            cur[u]=i;         //设置当前弧
    	            v=E[i].v;
    	            if(E[i].w<flow[u]) flow[v]=E[i].w;
    	            else flow[v]=flow[u];  //标记当前顶点为止经过的最小弧
    	            u=v;
    	            pre[v]=i;  //前置顶点边号
    	            if(u==t){
    	                do{
    	                    E[pre[u]].w-=flow[t];          //正向弧减a[t]
    	                    E[pre[u]^1].w+=flow[t];        //通过异或操作找反向弧
    	                    u=E[pre[u]^1].v;
    	                }
    	                while(u!=s);
    	                maxflow+=flow[t];
    	                //memset(flow,0,sizeof(flow));
    	                flow[s]=MAXNUM;
    	            }
    	        }else{   //不存在允许弧
    	            if(--cnt[d[u]]==0) break;   //间隙优化
    	            d[u]=n;
    	            cur[u]=gra[u];
    	            for(i=gra[u]; i; i=E[i].next)
    	                if(E[i].w && d[E[i].v]+1<d[u])
    	                    d[u]=d[E[i].v]+1;       //修改距离标号为 最小的非允许弧加1
    	            cnt[d[u]]++;
    	            if(u!=s) u=E[pre[u]^1].v;
    	        }
    	    }
    	    return maxflow;
    	}
    	void addedge(int x,int y,int z){
			E[++top].v = y ; E[top].next = gra[x] ; E[top].w = z ; gra[x] = top ;
        	E[++top].v = x ; E[top].next = gra[y] ; E[top].w = 0 ; gra[y] = top ;
		}
};

int main(){
    MNF_SAP ob ;
    int k ;
    int i,j;
    int numedge,numpoint;
    int x,y,z;
    while(scanf("%d%d",&numedge,&numpoint)!=EOF){
        ob.n = numpoint ;
        memset(ob.gra,0,sizeof(ob.gra));
        for(i=0;i<numedge;i++){
            scanf("%d%d%d",&x,&y,&z);
            ob.addedge(x,y,z);
        }
        printf("%d\n",ob.SAP());
    }
    return 0;
}