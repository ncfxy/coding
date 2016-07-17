#include <cstdio>
#include <memory.h>

const int M = 32005;

class NcfxyBinaryIndexedTree{// 树状数组
    private:
        int c[M];
    public:
        NcfxyBinaryIndexedTree(){memset(c,0,sizeof(c));}
        int lowbit(int k){
            return k & (-k);
        }
        int sum(int k){
            int s = 0;
            while(k > 0){
                s += c[k];
                k -= lowbit(k);
            }
            return s;
        }
        void change(int k,int d){ // k位置加d
            while(k < M){
                c[k] += d;
                k += lowbit(k);
            }
            return;
        }
};

void hdu1541(){
    int n,x,y;
    int num[32005];
    while(scanf("%d",&n)!=EOF){
        NcfxyBinaryIndexedTree binary;
        memset(num,0,sizeof(num));
        for(int i = 0;i < n;i++){
            scanf("%d%d",&x,&y);
            num[binary.sum(x+1)]++;
            binary.change(x+1,1);
        }
        for(int i = 0;i < n;i++){
            printf("%d\n",num[i]);
        }
    }
}

int main(){
    hdu1541();
    return 0;
}
