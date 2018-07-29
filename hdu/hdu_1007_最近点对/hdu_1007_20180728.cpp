#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct Node
{
    double x;
    double y;
}nd[100005];

bool cmpX(Node &n1, Node &n2)
{
    return n1.x < n2.x;
}

bool cmpY(Node &n1, Node &n2)
{
    return n1.y < n2.y;
}

double pdistance(int i, int j)
{
    return sqrt((nd[i].x - nd[j].x) * (nd[i].x - nd[j].x) + (nd[i].y - nd[j].y) * (nd[i].y - nd[j].y));
}

double find(int left, int right)
{
    if (right - left == 1)
    {
        return pdistance(left, right);
    }
    int mid = (left + right) / 2;
    double res = min(find(left, mid), find(mid, right));
    Node midNode;
    midNode.x = nd[mid].x;
    midNode.y = nd[mid].y;
    sort(&nd[left], &nd[right], cmpY);
    for (int i = left; i < right; i++)
    {
        if(nd[i].x - midNode.x < res && midNode.x - nd[i].x < res){
            for (int j = i + 1; j <= right;j++){
                if(nd[j].y - nd[i].y > res){
                    break;
                }
                double res2 = pdistance(i, j);
                res = min(res, res2);
            }
        }
    }
    return res;
}

void init(int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%lf%lf", &nd[i].x, &nd[i].y);
    }
    sort(nd, nd + N, cmpX);
}

void solve(int N)
{
    printf("%.2lf%\n", find(0, N - 1) / 2);
}

int main()
{
    int N;
    while (scanf("%d", &N) != EOF)
    {
        if(N == 0)
            break;
        init(N);
        solve(N);
    }
}