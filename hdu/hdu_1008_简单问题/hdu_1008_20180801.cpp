#include <iostream>
#include <cstdio>

using namespace std;

void solve(int N) {
    int current = 0;
    int result = 0;
    int des;
    for (int i = 0; i < N;i++){
        scanf("%d", &des);
        if(des > current) {
            result += (des - current) * 6;
        }else if(des < current) {
            result += (current - des) * 4;
        }
        result += 5;
        current = des;
    }
    printf("%d\n", result);
}

int main(){
    int N;
    while(scanf("%d",&N) != EOF){
        if(N == 0)
            break;
        solve(N);
    }
    return 0;
}
