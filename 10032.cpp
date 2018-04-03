//Tug of war

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    int n;
    cin >> n;
    vector<int> weight(n);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
      cin >> weight[i];
      sum += weight[i];
    }

    int max_weight = sum / 2;
    vector<long long> dp(max_weight + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
      for (int j = max_weight; j >= weight[i]; j--)
      {
        dp[j] |= dp[j - weight[i]] << 1;
      }
    }

    int ans = [&]() -> int {
      if (n % 2 == 0)
      {
        for (int i = max_weight; i >= 0; i--)
          if (dp[i] & (1ll << (n / 2)))
            return i;
      }
      else
      {
        for (int i = max_weight; i >= 0; i--)
          if (dp[i] & (1ll << (n / 2)) || dp[i] & (1ll << (n / 2 + 1)))
            return i;
      }

    }();
    cout << ans << " " << sum - ans << endl;
    if (t != 0)
      cout << endl;
  }
}