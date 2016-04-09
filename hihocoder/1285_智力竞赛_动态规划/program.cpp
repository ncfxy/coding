#include <iostream>
#include <string.h>

using namespace std;

int dp[1005][1005];
int A[1005];
int q,n,m,s,t;

const int inf = 0x7f7f7f7f;

int getCost(int indexA,int rightNum){
    int result = (A[indexA] - s * rightNum);
    if(result > 0){
        if(result % t == 0){
            return result/t;
        }else{
            return result/t + 1;
        }
    }else{
        return 0;
    }

}

int main(){
    cin >> q;
    while(q--){
        cin >>n >>m >>s >> t;
        for(int i = 1;i <= n;i++){
            cin >>A[i];
        }
        memset(dp,inf,sizeof(dp));
        for(int j=0;j<=m;j++)
        {
            dp[j][0]=0;
        }
        for(int i = 1;i <= n;i++){
                int num=0;
                if(A[i]%s == 0)num=A[i]/s;
                else num = A[i]/s+1;
            for(int rightNumber = 0; rightNumber <= num;rightNumber++){
                int faultNumber = getCost(i,rightNumber);
                for(int j = 0;j <=m;j++){
                    if(j +rightNumber+faultNumber<=m){
                        dp[j +rightNumber+faultNumber][i] = min(dp[j][i-1]+rightNumber,dp[j +rightNumber+faultNumber][i]);
                    }
                }
            }
        }
        int myMin = inf;
        for(int j = 0; j <= m;j++){
            if(dp[j][n] < myMin){
                myMin = dp[j][n];
            }
        }
        if(myMin > m)cout <<"No"<<endl;
        else cout <<myMin << endl;
    }
    return 0;
}
