#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };

struct mirror {
    int x, y, z;
};

int n, ex, ey;
char a[50][50];
int dist[50][50][4];
queue<mirror> q;

bool move(int x, int y, int z) {
    if (x < 0 || x >= n || y < 0 || y >= n) return false;
    if (dist[x][y][z] == '*') return false;
    return true;
}

void bfs() {
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y, z = q.front().z; q.pop();
        if (x == ex && y == ey) {
            cout << dist[x][y][z];
            return;
        }
        int nx = x + dx[z], ny = y + dy[z];
        while (move(nx, ny, z) && a[nx][ny] == '.') 
            nx += dx[z], ny += dy[z];
        
        if (move(nx, ny, z) && a[nx][ny] == '!') {
            dist[nx][ny][z] = dist[x][y][z];
            q.push({ nx, ny, z });
            int k = z < 2 ? 2 : 0;
            for (int i = k; i < k + 2; i++) {
                if (dist[nx][ny][i] == -1) {
                    dist[nx][ny][i] = dist[x][y][z] + 1;
                    q.push({ nx, ny, i });
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    memset(dist, -1, sizeof(dist));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = s[j];
            if (a[i][j] == '#') {
                if (q.empty()) {
                    for (int k = 0; k < 4; k++) {
                        q.push({ i, j, k });
                        dist[i][j][k] = 0;
                    }
                }
                else ex = i, ey = j;
                a[i][j] = '!';
            }
        }
    }
    bfs();
    return 0;
}