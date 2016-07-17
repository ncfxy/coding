#include <cstdio>
#include <memory.h>
#include <string.h>

class NcfxyBinaryIndexedTree{// 树状数组
    private:
        int lowbit(int k){
            return k & (-k);
        }
    public:
        int* array;
        const int maxLength;
        NcfxyBinaryIndexedTree(int maxLength, int* array) :
            maxLength(maxLength) {
            this->array = array;
            memset(array, 0, sizeof(int) * maxLength);
        }

        int sum(int k){
            int result = 0;
            while (k > 0) {
                result += array[k];
                k -= lowbit(k);
            }
            return result;
        }
        void change(int k,int d){ // k位置加d
            while (k < maxLength) {
                array[k] += d;
                k += lowbit(k);
            }
        }
};

void hdu1541(){
    const int M = 32005;
    int n,x,y;
    int num[M], array[M];
    while(scanf("%d",&n)!=EOF){
        NcfxyBinaryIndexedTree binary(M,array);
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

void hdu1166(){
    const int M = 100005;
    int n,t,array[M];
    char str[10];
    while(scanf("%d",&t)!=EOF){
        for(int i = 1;i <= t;i++){
            NcfxyBinaryIndexedTree bit(M,array);
            scanf("%d",&n);
            for(int j = 1;j <= n;j++){
                int temp;
                scanf("%d",&temp);
                bit.change(j,temp);
            }
            printf("Case %d:\n",i);
            while(scanf("%s",&str)!=EOF){
                int a,b;
                if(str[0] == 'A'){
                    scanf("%d%d",&a,&b);
                    bit.change(a,b);
                }else if(str[0] == 'S'){
                    scanf("%d%d",&a,&b);
                    bit.change(a,-b);
                }else if(str[0] == 'Q'){
                    scanf("%d%d",&a,&b);
                    printf("%d\n",bit.sum(b) - bit.sum(a-1));
                }else{
                    break;
                }
            }
        }
    }
}

int main(){
    //hdu1541();
    hdu1166();
    return 0;
}
