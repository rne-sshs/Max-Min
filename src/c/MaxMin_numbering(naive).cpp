#include <bits/stdc++.h>
#define double long double
using namespace std;
double mX[1001];
double mY[1001];
double wX[1001];
double wY[1001];
int N;
const double eps = 1e-9;
const int INF = 1e9;
int A[1005];
int B[1005];
int dis[1005];
bool used[1005];
vector<vector<int>> adj;
double ds(int x, int y) {
    return sqrt((mX[x]-wX[y])*(mX[x]-wX[y])+(mY[x]-wY[y])*(mY[x]-wY[y]));
}
void bfs() {
    queue<int> Q;
    for(int i = 0; i < N; i++) {
        if(!used[i]) {
            dis[i] = 0;
            Q.push(i);
        }
        else dis[i] = INF;
    }
    while(!Q.empty()) {
        int a = Q.front();
        Q.pop();
        for(int b : adj[a]) {
            if(B[b]!=-1&&dis[B[b]]==INF) {
                dis[B[b]] = dis[a]+1;
                Q.push(B[b]);
            }
        }
    }
}
bool dfs(int a) {
    for(int b : adj[a]) {
        if(B[b]==-1||dis[B[b]]==dis[a]+1&&dfs(B[b])) {
            used[a] = true;
            A[a]= b;
            B[b] = a;
            return true;
        }
    }
    return false;
}
signed main() {
    ifstream myFile("Data.txt");
    myFile >> N;
    for(int i = 0; i <N; i++) {
        myFile >> mX[i] >> mY[i];
    }
    for(int i = 0; i <N;i ++) {
        myFile >> wX[i] >> wY[i];
    }
    myFile.close();
    double l = 0, r = 1000000;
    while(abs(l-r)>eps) {
        double mid = (l+r)/2;
        adj.clear();
        adj.resize(N);
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(ds(i,j)<=mid) {
                    adj[i].push_back(j);
                }
            }
        }
        for(int i = 0; i < N; i++) {
            A[i] = B[i] = -1;
            used[i] = false;
            dis[i] = 0;
        }
        int match = 0;
        while(true) {
            bfs();
            int flow = 0;
            for(int i = 0; i < N; i++) {
                if(!used[i]&&dfs(i)) flow++;
            }
            if(flow==0) break;
            match += flow;
        }
        if(match == N) r = mid;
        else l = mid;
    }
    double mid = r;
    adj.clear();
    adj.resize(N);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(ds(i,j)<=mid) {
                adj[i].push_back(j);
            }
        }
    }
    for(int i = 0; i < N; i++) {
        A[i] = B[i] = -1;
        used[i] = false;
        dis[i] = 0;
    }
    int match = 0;
    while(true) {
        bfs();
        int flow = 0;
        for(int i = 0; i < N; i++) {
            if(!used[i]&&dfs(i)) flow++;
        }
        if(flow==0) break;
        match += flow;
    }
    assert(match == N);
    for(int i=0;i<N;i++) cout << A[i] <<' ';
    cout << '\n' << fixed << setprecision(30) << r << '\n';
    for(int i = 0 ; i < N; i++){
        cout << i <<"th \n";
        cout << mX[i] <<' ' << mY[i] << '\n';
        cout << wX[A[i]] <<' ' << wY[A[i]] << '\n';
        cout << ds(i, A[i]) << '\n';
    }
}
