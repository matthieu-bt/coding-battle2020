#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

const int INF = 1000000000;

// The following implementation of the Stoer-Wagner min cut algorithm
// comes from a Stanford ACM-ICPC notebook, available at :
// https://github.com/jaehyunp/stanfordacm.

pair<int, VI> GetMinCut(VVI &weights)
{
  int N = weights.size();
  VI used(N), cut, best_cut;
  int best_weight = -1;

  for (int phase = N - 1; phase >= 0; phase--)
  {
    VI w = weights[0];
    VI added = used;
    int prev, last = 0;
    for (int i = 0; i < phase; i++)
    {
      prev = last;
      last = -1;
      for (int j = 1; j < N; j++)
        if (!added[j] && (last == -1 || w[j] > w[last]))
          last = j;
      if (i == phase - 1)
      {
        for (int j = 0; j < N; j++)
          weights[prev][j] += weights[last][j];
        for (int j = 0; j < N; j++)
          weights[j][prev] = weights[prev][j];
        used[last] = true;
        cut.push_back(last);
        if (best_weight == -1 || w[last] < best_weight)
        {
          best_cut = cut;
          best_weight = w[last];
        }
      }
      else
      {
        for (int j = 0; j < N; j++)
          w[j] += weights[last][j];
        added[last] = true;
      }
    }
  }
  return make_pair(best_weight, best_cut);
}

int main()
{
  int n, m;
  cin >> n >> m;
  VVI weights(n, VI(n));
  for (int j = 0; j < m; j++)
  {
    int a, b;
    cin >> a >> b;
    // Since we're looking a count of edges to be removed,
    // all weights are set to 1
    weights[a - 1][b - 1] = weights[b - 1][a - 1] = 1;
  }
  pair<int, VI> res = GetMinCut(weights);
  cout << res.first << endl;
}
