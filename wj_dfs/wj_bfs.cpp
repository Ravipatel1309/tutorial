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
map<pair<int, int>, set<pair<int, int>>> mp;
bool bfs(int jug1, int jug2, pair<int, int> goal)
{
    // visited[{0, 0}] = true;
    map<pair<int, int>, bool> visited;
    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty())
    {
        pair<int, int> top = q.front();
        q.pop();
        if (top == goal)
        {
            return true;
        }
        if (!visited[top])
        {
            visited[top] = true;
            // fill
            if (top.first < jug1)
            {
                if (!visited[{jug1, top.second}])
                {
                    q.push({jug1, top.second});
                    traversal_path.push_back({top, {jug1, top.second}});
                }
            }
            if (top.second < jug2)
            {
                if (!visited[{top.first, jug2}])
                {
                    q.push({top.first, jug2});
                    traversal_path.push_back({top, {top.first, jug2}});
                }
            }
            // empty
            if (top.first > 0)
            {
                if (!visited[{0, top.second}])
                {
                    q.push({0, top.second});
                    traversal_path.push_back({top, {0, top.second}});
                }
            }
            if (top.second > 0)
            {
                if (!visited[{top.first, 0}])
                {
                    q.push({top.first, 0});
                    traversal_path.push_back({top, {top.first, 0}});
                }
            }
            // transfer
            if (top.first > 0 and top.second < jug2)
            {
                if (top.first + top.second <= jug2)
                {
                    if (!visited[{0, top.first + top.second}])
                    {
                        q.push({0, top.first + top.second});
                        traversal_path.push_back({top, {0, top.first + top.second}});
                    }
                }
                else
                {
                    if (!visited[{top.first + top.second - jug2, jug2}])
                    {
                        q.push({top.first + top.second - jug2, jug2});
                        traversal_path.push_back({top, {top.first + top.second - jug2, jug2}});
                    }
                }
            }
            if (top.second > 0 and top.first < jug1)
            {
                if (top.first + top.second <= jug1)
                {
                    if (!visited[{top.first + top.second, 0}])
                    {
                        q.push({top.first + top.second, 0});
                        traversal_path.push_back({top, {top.first + top.second, 0}});
                    }
                }
                else
                {
                    if (!visited[{jug1, top.first + top.second - jug1}])
                    {
                        q.push({jug1, top.first + top.second - jug1});
                        traversal_path.push_back({top, {jug1, top.first + top.second - jug1}});
                    }
                }
            }
        }
    }
    // if solution not exists
    return false;
}
int main()
{
    FASTIO;
    int jug1 = 4;
    int jug2 = 3;
    pair<int, int> goal = {2, 0};
    if (bfs(jug1, jug2, goal))
    {
        cout << "\n*** Solution Exist ***\n";
        pair<int, int> node = goal;
        reverse(all(traversal_path));
        vector<pair<int, int>> path;
        path.push_back(goal);
        for (auto i : traversal_path)
        {
            if (i.second == node)
            {
                node = i.first;
                path.push_back(node);
            }
        }
        reverse(all(path));
        for (auto i : path)
            cout << i.first << " " << i.second << "\n";
    }
    else
        cout << "\n*** Solution Not Exist ***\n";
    return 0;
}