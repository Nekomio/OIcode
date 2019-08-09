#include <vector>
#include <cstring>
#include <cstdio>
#include <bitset>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAXN = 1e5 + 5;
int a[MAXN];
vector<int> T[MAXN], F[MAXN];
bitset<MAXN> TT, FF, ans1, ans2, ans;
int main() {
  int t = read();
  while (t--) {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
      a[i] = read();
      if (a[i] < 0) {
        F[-a[i]].push_back(i);
        FF[i] = 1;
      }
      else {
        T[a[i]].push_back(i);
        TT[i] = 1;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (FF.count() - F[i].size() + T[i].size() == m) {
        for (int j = 0; j < T[i].size(); j++)
          TT[T[i][j]] = 0, ans2[T[i][j]] = 1;
        for (int j = 0; j < F[i].size(); j++)
          FF[F[i][j]] = 0, ans1[F[i][j]] = 1;
        ans1 |= TT, ans2 |= FF;
        for (int j = 0; j < T[i].size(); j++)
          TT[T[i][j]] = 1;
        for (int j = 0; j < F[i].size(); j++)
          FF[F[i][j]] = 1;
      }
    }
    ans = ans1 ^ ans2;
    for (int i = 1; i <= n; i++) {
      if (ans[i] && ans1[i]) printf ("Lie\n");
      if (ans[i] && ans2[i]) printf ("Truth\n");
      if (!ans[i]) printf ("Not defined\n");
    }
    for (int i = 1; i <= n; i++) T[i].clear(), F[i].clear();
    TT.reset(), FF.reset(), ans1.reset(), ans2.reset(), ans.reset();
  }
}