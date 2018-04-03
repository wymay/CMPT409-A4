//Robots on Ice

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int direction[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int surround[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

void print_map(unsigned long long map, int n, int m)
{
  for (int i = n - 1; i >= 0; i--)
  {
    for (int j = 0; j < m; j++)
      cout << (((map >> (i * m + j)) & 1) % 2);
    cout << endl;
  }
  cout << endl;
}

int distance(int x1, int y1, int x2, int y2)
{
  return abs(x1 - x2) + abs(y1 - y2);
}

bool divided(unsigned long long map, int n, int m, int x, int y, int visited)
{
  int v[8], count = 0;
  for (int i = 0; i < 8; i++)
  {
    int xx = x + surround[i][0], yy = y + surround[i][1];
    v[i] = xx >= n || xx < 0 || yy >= m || yy < 0 || (((map >> (xx * m + yy)) & 1ull) ^ visited);
  }
  for (int i = 0; i < 8; i++)
  {
    if (v[i] != v[(i + 1) % 8])
      count++;
  }
  return count >= 4;
}

int main()
{
  int n, m;
  cin >> n >> m;
  for (int t = 1; n != 0 && m != 0; cin >> n >> m, t++)
  {
    int p1x, p1y, p2x, p2y, p3x, p3y;
    cin >> p1x >> p1y;
    cin >> p2x >> p2y;
    cin >> p3x >> p3y;

    map<pair<unsigned long long, int>, unsigned long long> f, f1;
    vector<pair<unsigned long long, int>> current, next;
    auto start = make_pair(1ull, 0);
    f[start] = 1;
    current.push_back(start);

    for (int i = 2; i <= n * m / 2; i++)
    {
      for (int j = 0, s = current.size(); j < s; j++)
      {
        int x = current[j].second / m, y = current[j].second % m;
        for (int k = 0; k < 4; k++)
        {
          int xx = x + direction[k][0], yy = y + direction[k][1];

          if (!(xx < n && yy < m && xx >= 0 && yy >= 0))
            continue;

          if ((current[j].first >> (xx * m + yy)) & 1ull)
            continue;

          unsigned long long new_map = current[j].first | (1ull << (xx * m + yy));

          if (xx == p1x && yy == p1y && i != n * m / 4)
            continue;
          if (xx == p2x && yy == p2y && i != n * m / 2)
            continue;
          if (xx == p3x && yy == p3y && i != n * m * 3 / 4)
            continue;
          if (xx == 0 && yy == 1 && i != n * m)
            continue;

          if (i <= n * m / 4)
          {
            int t = n * m / 4 - i;
            if (distance(xx, yy, p1x, p1y) > t)
              continue;
          }
          else if (i <= n * m / 2)
          {
            int t = n * m / 2 - i;
            if (distance(xx, yy, p2x, p2y) > t)
              continue;
          }

          if (divided(new_map, n, m, xx, yy, 0))
            continue;

          auto p = make_pair(new_map, xx * m + yy);
          if (f1.find(p) == f1.end())
            next.push_back(p);
          f1[p] += f[current[j]];
          // cout << x << "," << y << " -> ";
          // cout << xx << "," << yy << ":";
          // cout << p.first << " " << p.second << endl;
        }
      }
      // cout << i << ": " << next.size() << endl;

      swap(current, next);
      next.clear();

      swap(f, f1);
      f1.clear();
    }

    map<pair<unsigned long long, int>, unsigned long long> f0;
    swap(f0, f);
    f.clear();
    f1.clear();
    start = make_pair(n * m == 64 ? ~0ull : ((1ull << (n * m)) - 1ull), 1);
    f[start] = 1;
    current.clear();
    next.clear();
    current.push_back(start);

    for (int i = n * m - 1; i >= n * m / 2; i--)
    {
      for (int j = 0, s = current.size(); j < s; j++)
      {
        int x = current[j].second / m, y = current[j].second % m;
        unsigned long long new_map = current[j].first ^ (1ull << (x * m + y));
        for (int k = 0; k < 4; k++)
        {
          int xx = x + direction[k][0], yy = y + direction[k][1];

          if (!(xx < n && yy < m && xx >= 0 && yy >= 0))
            continue;

          if (((current[j].first >> (xx * m + yy)) & 1ull) == 0)
            continue;

          if (xx == p1x && yy == p1y && i != n * m / 4)
            continue;
          if (xx == p2x && yy == p2y && i != n * m / 2)
            continue;
          if (xx == p3x && yy == p3y && i != n * m * 3 / 4)
            continue;
          if (xx == 0 && yy == 0 && i != 1)
            continue;

          if (i >= n * m * 3 / 4)
          {
            int t = i - n * m * 3 / 4;
            if (distance(xx, yy, p3x, p3y) > t)
              continue;
          }
          else if (i >= n * m / 2)
          {
            int t = i - n * m / 2;
            if (distance(xx, yy, p2x, p2y) > t)
              continue;
          }

          if (divided(new_map, n, m, xx, yy, 1))
            continue;

          auto p = make_pair(new_map, xx * m + yy);
          if (f1.find(p) == f1.end())
            next.push_back(p);
          f1[p] += f[current[j]];
          // cout << x << "," << y << " -> ";
          // cout << xx << "," << yy << ":";
          // cout << p.first << " " << p.second << endl;
        }
      }
      // cout << i << ": " << next.size() << endl;

      swap(current, next);
      next.clear();

      swap(f, f1);
      f1.clear();
    }

    unsigned long long ans = 0;
    for (int i = 0, s = current.size(); i < s; i++)
    {
      ans += f0[current[i]] * f[current[i]];
    }
    cout << "Case " << t << ": " << ans << endl;
  }
}