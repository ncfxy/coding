#include <iostream>
#include <string>

using namespace std;

int nextArray[10000];
int m;

void Next(const char T[]) {
    memset(nextArray, 0, sizeof(nextArray));
    int j, t;
    t = nextArray[0] = -1;
    j = 0;
    m = strlen(T);
    while(j < m -1) {
        if (t < 0 || T[j] == T[t]) nextArray[++j] = ++t;
        else t = nextArray[t];
    }
    return;
}

int main() {
    string s = "abcdabce";
    const char *T = s.c_str();
    Next(T);
    for(int i = 0; i < m; i++) {
        cout << nextArray[i] << " ";
    }
    cout << endl;
    return 0;
}