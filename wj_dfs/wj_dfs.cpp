#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define sz size()
#define vll vector<ll>
#define mp make_pair
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define no cout << "NO" << endl;
#define yes cout << "YES" << endl;
#define mod 1000000007
#define all(x) (x).begin(), (x).end()
#define SORT(v) sort(all(v))
#define REVSORT(v) sort(all(v), greater<int>())
#define MAX(v) max_element(all(v))
#define MIN(v) min_element(all(v))
#define rep(from, to) for (int i = from; i <= to; i++)
#define rep_back(from, to) for (int i = from; i >= to; i--)
#define take(v) rep(0, v.size()) cin >> v[i];
#define FASTIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
using namespace std;

/* ========== YOUR CODE HERE ========= */

vector<pair<pair<int, int>, pair<int, int>>> traversal_path;

bool dfs(int jug1, int jug2, int curr1, int curr2, pair<int, int> goal, map<pair<int, int>, bool> &visited)
{

    if (!visited[{curr1, curr2}] and (mp(curr1, curr2) == goal))
    {
        return true;
    }
    if (visited[{curr1, curr2}])
        return false;
    visited[{curr1, curr2}] = true;

    // fill
    if (curr1 < jug1 and !visited[{jug1, curr2}] and dfs(jug1, jug2, jug1, curr2, goal, visited))
    {
        traversal_path.push_back({{curr1, curr2}, {jug1, curr2}});
        return true;
    }
    if (curr2 < jug2 and !visited[{curr1, jug2}] and dfs(jug1, jug2, curr1, jug2, goal, visited))
    {
        traversal_path.push_back({{curr1, curr2}, {curr1, jug2}});
        return true;
    }

    // empty
    if (curr1 > 0 and !visited[{0, curr2}] and dfs(jug1, jug2, 0, curr2, goal, visited))
    {
        traversal_path.push_back({{curr1, curr2}, {0, curr2}});
        return true;
    }
    if (curr2 > 0 and !visited[{curr1, 0}] and dfs(jug1, jug2, curr1, 0, goal, visited))
    {
        traversal_path.push_back({{curr1, curr2}, {curr1, 0}});
        return true;
    }

    // transfer
    if (curr1 > 0 and curr2 < jug2)
    {
        if (curr1 + curr2 <= jug2 and !visited[{0, curr1 + curr2}] and dfs(jug1, jug2, 0, curr1 + curr2, goal, visited))
        {
            traversal_path.push_back({{curr1, curr2}, {0, curr1 + curr2}});
            return true;
        }
        else if (!visited[{curr1 + curr2 - jug2, jug2}] and dfs(jug1, jug2, curr1 + curr2 - jug2, jug2, goal, visited))
        {
            traversal_path.push_back({{curr1, curr2}, {curr1 + curr2 - jug2, jug2}});
            return true;
        }
    }
    if (curr2 > 0 and curr1 < jug1)
    {
        if (curr1 + curr2 <= jug1 and !visited[{curr1 + curr2, 0}] and dfs(jug1, jug2, curr1 + curr2, 0, goal, visited))
        {
            traversal_path.push_back({{curr1, curr2}, {curr1 + curr2, 0}});
            return true;
        }
        else if (!visited[{jug1, curr1 + curr2 - jug1}] and dfs(jug1, jug2, jug1, curr1 + curr2 - jug1, goal, visited))
        {
            traversal_path.push_back({{curr1, curr2}, {jug1, curr1 + curr2 - jug1}});
            return true;
        }
    }
    return false;
}

int main()
{
    FASTIO;
    int jug1 = 4;
    int jug2 = 3;
    pair<int, int> goal = {4, 2};
    map<pair<int, int>, bool> visited;
    visited[{0, 0}] = false;
    if (dfs(jug1, jug2, 0, 0, goal, visited))
    {
        cout << "\n*** Solution Exist ***\n";
        reverse(all(traversal_path));
        pair<int, int> node = goal;
        for (auto i : traversal_path)
        {
            cout << i.first.first << " " << i.first.second << " -> " << i.second.first << " " << i.second.second << "\n";
        }
    }
    else
    {
        cout << "\n*** Solution Not Exist ***\n";
    }
    return 0;
}
