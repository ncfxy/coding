#include <cstdio>
#include <cstring>

using namespace std;

#define N 10000000
int main() {
    int phi[N +1];
    bool prime[N +1];
    memset(prime, true, sizeof(prime));
    for(int i = 2;i * i <=N; i++) {
        if(prime[i]) {
            for(int j = i * i;j <= N;j += i) {
                prime[j] = false;
            }
        }
    } // 求出N以内的素数
    for(int i = 1; i <= N; i++) {
        phi[i] = i;
    }
    for(int i = 2; i <= N; i++) {
        if(prime[i]) {
            for(int j = i; j <= N; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }// N 以内的所有欧拉函数值
}