#include <bits/stdc++.h>
using namespace std;

vector<pair<vector<vector<int>>, vector<vector<int>>>> traversal_path;

bool bfs(vector<vector<int>> initial_state, vector<vector<int>> &goal_state, map<vector<vector<int>>, bool> &vis)
{
    queue<vector<vector<int>>> q;
    q.push(initial_state);

    while (!q.empty())
    {
        auto top = q.front();
        q.pop();
        if (top == goal_state)
        {
            traversal_path.push_back({top, goal_state});
            return true;
        }

        if (!vis[top])
        {
            vis[top] = true;
            int blanki = 0, blankj = 0;
            for (int i = 0; i < initial_state.size(); i++)
            {
                for (int j = 0; j < initial_state.size(); j++)
                {
                    if (top[i][j] == 0)
                    {
                        blanki = i;
                        blankj = j;
                        break;
                    }
                }
            }

            if (blanki + 1 < initial_state.size())
            {
                auto temp = top;
                swap(temp[blanki][blankj], temp[blanki + 1][blankj]);
                traversal_path.push_back({top, temp});
                q.push(temp);
            }
            if (blanki - 1 >= 0)
            {
                auto temp = top;
                swap(temp[blanki][blankj], temp[blanki - 1][blankj]);
                traversal_path.push_back({top, temp});
                q.push(temp);
            }
            if (blankj + 1 < initial_state.size())
            {
                auto temp = top;
                swap(temp[blanki][blankj], temp[blanki][blankj + 1]);
                traversal_path.push_back({top, temp});
                q.push(temp);
            }
            if (blankj - 1 >= 0)
            {
                auto temp = top;
                swap(temp[blanki][blankj], temp[blanki][blankj - 1]);
                traversal_path.push_back({top, temp});
                q.push(temp);
            }
        }
    }

    return false;
}

int main()
{
    vector<vector<int>> initial_state = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
    vector<vector<int>> goal_state = {{1, 2, 3}, {5, 8, 6}, {0, 7, 4}};
    map<vector<vector<int>>, bool> vis;

    int blanki = 0, blankj = 0;
    for (int i = 0; i < initial_state.size(); i++)
    {
        for (int j = 0; j < initial_state[0].size(); j++)
        {
            if (initial_state[i][j] == 0)
            {
                blanki = i;
                blankj = j;
                break;
            }
        }
    }

    if (bfs(initial_state, goal_state, vis))
    {
        vector<vector<vector<int>>> path;
        auto node = goal_state;
        reverse(traversal_path.begin(), traversal_path.end());

        for (auto i : traversal_path)
        {
            if (i.first == node)
            {
                path.push_back(i.second);
                node = i.second;
            }
        }

        path.push_back(initial_state);
        reverse(path.begin(), path.end());
        cout << "Path : \n";
        for (auto node : path)
        {
            for (auto i : node)
            {
                for (auto j : i)
                {
                    cout << j << " ";
                }
                cout << "\n";
            }
            cout << " | "
                 << "\n";
        }
    }
    else
    {
        cout << "No solution\n";
    }

    return 0;
}
