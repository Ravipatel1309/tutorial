#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define FASTIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
using namespace std;
/* ========== YOUR CODE HERE ========= */
int size;
class Node
{
public:
    vector<vector<int>> board;
    int depth, misplaced;
    Node *parent;
    Node()
    {
        depth = 0;
        misplaced = 0;
        parent = NULL;
    }
    static int heuristic(Node start, Node goal)
    {
        int count = 0;
        for (int i = 0; i < start.board.size(); i++)
        {
            for (int j = 0; j < start.board.size(); j++)
            {
                if (start.board[i][j] != 0 and start.board[i][j] != goal.board[i][j])
                {
                    count++;
                }
            }
        }
        return count;
    }
    bool operator==(Node a)
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (this->board[i][j] != a.board[i][j])
                    return false;
        return true;
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
};
bool compare(Node a, Node b)
{
    return a.misplaced < b.misplaced;
}
bool isinset(Node a, vector<Node> b)
{
    for (int i = 0; i < b.size(); i++)
        if (a == b[i])
            return true;
    return false;
}
void addChild(Node current, Node goal, int newi, int newj, int blanki, int blankj, vector<Node> &openset,
              vector<Node> &closeset)
{
    Node newNode = current;
    swap(newNode.board[newi][newj], newNode.board[blanki][blankj]);
    if (!isinset(newNode, openset) and !isinset(newNode, closeset))
    {
        newNode.depth = current.depth + 1;
        newNode.misplaced = newNode.depth + Node::heuristic(newNode, goal);
        Node *temp = new Node;
        *temp = current;
        newNode.parent = temp;
        openset.push_back(newNode);
    }
}
void getChilds(Node current, Node goal, vector<Node> &openset, vector<Node> &closeset)
{
    int blanki, blankj;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (current.board[i][j] == 0)
            {
                blanki = i;
                blankj = j;
                break;
            }
        }
    }
    int i = blanki;
    int j = blankj;
    if (i - 1 >= 0)
    {
        addChild(current, goal, i - 1, j, blanki, blankj, openset, closeset);
    }
    if (i + 1 < size)
    {
        addChild(current, goal, i + 1, j, blanki, blankj, openset, closeset);
    }
    if (j - 1 >= 0)
    {
        addChild(current, goal, i, j - 1, blanki, blankj, openset, closeset);
    }
    if (j + 1 < size)
    {
        addChild(current, goal, i, j + 1, blanki, blankj, openset, closeset);
    }
}
bool reconstruct_path(Node current, vector<Node> &came_from)
{
    // cout << "Generating path ...\n";
    Node *temp = &current;
    while (temp != NULL)
    {
        came_from.push_back(*temp);
        temp = temp->parent;
    }
    return true;
}
vector<Node> path;
bool solve(Node start, Node goal)
{
    vector<Node> openset;
    vector<Node> closeset;
    start.depth = 0;
    start.misplaced = start.depth + Node ::heuristic(start, goal);
    openset.push_back(start);
    while (!openset.empty())
    {
        sort(all(openset), compare);
        Node current = openset[0];
        if (current == goal)
        {
            return reconstruct_path(current, path);
        }
        openset.erase(openset.begin());
        closeset.push_back(current);
        getChilds(current, goal, openset, closeset);
    }
    return false;
}
int main()
{
    FASTIO;
    int n = 3;
    size = n;
    Node initial_state;
    initial_state.board = {{2, 8, 3}, {1, 6, 4}, {7, 0, 5}};
    Node goal_state;
    goal_state.board = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
    if (solve(initial_state, goal_state))
    {
        cout << "Solved\n";
        cout << "\n************\n";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            path[i].print();
            if (i != 0)
                cout << "\n | \n\n";
        }
        cout << "\n************\n";
    }
    else
    {
        cout << "Fail\n";
    }
    return 0;
}