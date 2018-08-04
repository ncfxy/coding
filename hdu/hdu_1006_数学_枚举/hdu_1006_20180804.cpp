#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int allDayTime = 12 * 60 * 60;
const double eps = 0.0000001;

// 角速度
double speedH = 1.0 / 120;
double speedM = 1.0 / 10;
double speedS = 6.0;

// 相对角速度
double speedHM = speedM - speedH;
double speedHS = speedS - speedH;
double speedMS = speedS - speedM;

// 相对周期
double periodHM = 360.0 / speedHM;
double periodHS = 360.0 / speedHS;
double periodMS = 360.0 / speedMS;

void solve(double degree){
    double sum = 0.0;
    double start[3], end[3]; // 开始和结束的时间;
    double i[3], j[3];
    start[0] = degree / speedHM;
    start[1] = degree / speedHS;
    start[2] = degree / speedMS;

    end[0] = (360.0 - degree) / speedHM;
    end[1] = (360.0 - degree) / speedHS;
    end[2] = (360.0 - degree) / speedMS;

    for (i[0] = start[0], j[0] = end[0]; j[0] < allDayTime + eps; i[0] += periodHM, j[0] += periodHM){
        for (i[1] = start[1], j[1] = end[1]; j[1] < allDayTime + eps; i[1] += periodHS, j[1] += periodHS){
            if(i[1] > j[0])
                break;
            if(j[1] < i[0])
                continue;
            for (i[2] = start[2], j[2] = end[2]; j[2] < allDayTime + eps; i[2] += periodMS, j[2] += periodMS){
                if (i[2] > j[1])
                    break;
                if (j[2] < i[1])
                    continue;
                double from = max(max(i[0], i[1]), i[2]);
                double to = min(min(j[0], j[1]), j[2]);
                sum += max(0.0, to - from);
            }
        }
    }

    printf("%.3lf\n", sum * 100.0 / allDayTime);
}

int main(){
    double N;
    while(scanf("%lf", &N) != EOF){
        if(N == -1)
            break;
        solve(N);
    }
}