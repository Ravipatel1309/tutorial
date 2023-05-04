#include <bits/stdc++.h>
using namespace std;

vector<pair<pair<int, int>, pair<int, int>>> traversal_path;

bool dfs(int curr1, int curr2, int jug1, int jug2, pair<int, int> &goal, map<pair<int, int>, bool> &vis)
{

    if (!vis[{curr1, curr2}] && make_pair(curr1, curr2) == goal)
        return true;

    if (vis[{curr1, curr2}])
        return false;

    vis[{curr1, curr2}] = true;

    //fill
    if (curr1 < jug1 && !vis[{jug1, curr2}] && dfs(jug1, curr2, jug1, jug2, goal, vis))
    {
        traversal_path.push_back({{curr1, curr2}, {jug1, curr2}});
        return true;
    }
    if (curr2 < jug2 && !vis[{curr1, jug2}] && dfs(curr1, jug2, jug1, jug2, goal, vis))
    {
        traversal_path.push_back({{curr1, curr2}, {curr1, jug2}});
        return true;
    }

    //empty
    if (curr1 > 0 && !vis[{0, curr2}] && dfs(0, curr2, jug1, jug2, goal, vis))
    {
        traversal_path.push_back({{curr1, curr2}, {0, curr2}});
        return true;
    }
    if (curr2 > 0 && !vis[{curr1, 0}] && dfs(curr1, 0, jug1, jug2, goal, vis))
    {
        traversal_path.push_back({{curr1, curr2}, {curr1, 0}});
        return true;
    }

    //transfer
    if (curr1 > 0 && curr2 < jug2)
    {
        if (curr1 + curr2 <= jug2 && !vis[{0, curr1 + curr2}] && dfs(0, curr1 + curr2, jug1, jug2, goal, vis))
        {
            traversal_path.push_back({{curr1, curr2}, {0, curr1 + curr2}});
            return true;
        }
        else if (!vis[{curr1 + curr2 - jug2, jug2}] && dfs(curr1 + curr2 - jug2, jug2, jug1, jug2, goal, vis))
        {
            traversal_path.push_back({{curr1, curr2}, {curr1 + curr2 - jug2, jug2}});
            return true;
        }
    }

    if (curr2 > 0 && curr1 < jug1)
    {
        if (curr1 + curr2 <= jug1 && !vis[{curr1 + curr2, 0}] && dfs(curr1 + curr2, 0, jug1, jug2, goal, vis))
        {
            traversal_path.push_back({{curr1, curr2}, {curr1 + curr2, 0}});
            return true;
        }
        else if (!vis[{jug1, curr1 + curr2 - jug1}] && dfs(jug1, curr1 + curr2 - jug1, jug1, jug2, goal, vis))
        {
            traversal_path.push_back({{curr1, curr2}, {jug1, curr1 + curr2 - jug1}});
            return true;
        }
    }

    return false;
}

int main()
{
    int jug1 = 4;
    int jug2 = 3;

    pair<int, int> goal = {4, 2};
    map<pair<int, int>, bool> visited;

    if (dfs(0, 0, jug1, jug2, goal, visited))
    {
        cout << "***Solution Exist***" << endl;
        reverse(traversal_path.begin(), traversal_path.end());

        for (auto &t : traversal_path)
        {
            cout << t.first.first << "," << t.first.second << " -> " << t.second.first << "," << t.second.second << endl;
        }
    }
    else
    {
        cout << "***Solution does not Exist***" << endl;
    }

    return 0;
}