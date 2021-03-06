//
// Created by zyl on 2020/3/14.
//

#include "include/algorithms_data_structures.h"

void BFS(vector<vector<char>>& grid, int m, int n) {
    int nr = grid.size();
    int nc = grid[0].size();
    queue<pair<int, int>> q;
    vector<vector<int>> dirs = {{1, 0}, {0, 1},
                                {-1, 0}, {0, -1}};
    q.emplace(m, n);
    grid[m][n] = '0';
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int x = q.front().first;
            int y = q.front().second;
            for (int j = 0; j < 4; j++) {
                int r = x + dirs[j][0];
                int c = y + dirs[j][1];
                if (r >= 0 && r <= nr - 1 && c >= 0 && c <= nc - 1 && grid[r][c] == '1') {
                    q.emplace(r, c);
                    grid[r][c] = '0';
                }
            }
            q.pop();
        }
    }
}

bool findNewNode(vector<vector<char> > &grid, vector<vector<int> > &visited, pair<int, int> &p, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1' && visited[i][j] == 0) {
                p = make_pair(i, j);
                visited[i][j] = 1;
                return true;
            }
        }
    }
    return false;
}

int Solution::numIsLands(vector<vector<char> > &grid) {
    int result = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '1') {
                BFS(grid, i, j);
                result++;
            }
        }
    }
    return result;
}


bool findNewNodePro(vector<vector<int> > &grid, vector<vector<int> > &visited, pair<int, int> &p) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 1 && visited[i][j] == 0) {
                p = make_pair(i, j);
                visited[i][j] = 1;
                return true;
            }
        }
    }
    return false;
}

int Solution::maxAreaOfIsland(vector<vector<int> > &grid) {
    if (grid.empty())
        return 0;
    queue<pair<int, int>> q;
    vector<int> zeros(grid[0].size(), 0);
    vector<vector<int>> visited(grid.size(), zeros);
    int result = 0;
    int temp_result = 0;
    while (true) {
        temp_result = 0;
        if (q.empty()) {
            pair<int, int> p;
            if (findNewNodePro(grid, visited, p))
                q.push(p);
            else
                break;
        }
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int m = q.front().first;
                int n = q.front().second;
                pair<int, int> p;
                if (m > 0) {
                    if (grid[m-1][n] == 1 && visited[m-1][n] == 0) {
                        p = make_pair(m-1, n);
                        q.push(p);
                        visited[m-1][n] = 1;
                    }
                }
                if (m < grid.size()-1) {
                    if (grid[m+1][n] == 1 && visited[m+1][n] == 0) {
                        p = make_pair(m+1, n);
                        q.push(p);
                        visited[m+1][n] = 1;
                    }
                }
                if (n > 0) {
                    if (grid[m][n-1] == 1 && visited[m][n-1] == 0) {
                        p = make_pair(m, n-1);
                        q.push(p);
                        visited[m][n-1] = 1;
                    }
                }
                if (n < grid[0].size()-1) {
                    if (grid[m][n+1] == 1 && visited[m][n+1] == 0) {
                        p = make_pair(m, n+1);
                        q.push(p);
                        visited[m][n+1] = 1;
                    }
                }
                q.pop();
                temp_result++;
            }
        }
        if (temp_result > result)
            result = temp_result;
    }
    return result;
}


int Solution::islandPerimeter(vector<vector<int> > &grid) {
    int res = 0, m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j]) {
                res += 4;
                if (i > 0 && grid[i - 1][j]) res -= 2;
                if (j > 0 && grid[i][j - 1]) res -= 2;
            }
        }
    }
    return res;
}


int Solution::orangesRotting(vector<vector<int>>& grid) {
    vector<vector<int>> temp = grid;
    bool flag = true;
    int m = grid.size();
    int n = grid[0].size();
    int time = 0;
    while (flag) {
        time++;
        flag = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (temp[i][j] == 2) {
                    if (i > 0) {
                        if (temp[i-1][j] == 1) {
                            grid[i-1][j] = 2;
                            flag = true;
                        }
                    }
                    if (i < m-1) {
                        if (temp[i+1][j] == 1) {
                            grid[i+1][j] = 2;
                            flag = true;
                        }
                    }
                    if (j > 0) {
                        if (temp[i][j-1] == 1) {
                            grid[i][j-1] = 2;
                            flag = true;
                        }
                    }
                    if (j < n-1) {
                        if (temp[i][j+1] == 1) {
                            grid[i][j+1] = 2;
                            flag = true;
                        }
                    }
                    grid[i][j] = -1;
                }
            }
        }
        temp = grid;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1)
                return -1;
        }
    }
    return --time;
}

/**
 * https://leetcode-cn.com/problems/open-the-lock/
 * @param deadends
 * @param target
 * @return
 */
int Solution::openLock(vector<string> &deadends, string target) {
    unordered_set<string> set_deadends(deadends.begin(), deadends.end());
    queue<string> store;
    if (set_deadends.find("0000") != set_deadends.end()) {
        return -1;
    }
    store.push("0000");
    set_deadends.insert("0000");
    if (target == "0000") {
        return 0;
    }
    int res = 1;
    while (!store.empty()) {
        int size = store.size();
        for (int i = 0; i < size; i++) {
            string cur = store.front();
            string tmp;
            for (int k = 0; k < 4; k++) {
                tmp = cur;
                int t = tmp[k] - '0';
                t - 1 < 0 ? t = 9 : t--;
                tmp[k] = '0' + t;
                if (set_deadends.find(tmp) == set_deadends.end()) {
                    if (tmp == target) {
                        return res;
                    }
                    store.push(tmp);
                    set_deadends.insert(tmp);
                }
                tmp = cur;
                t = tmp[k] - '0';
                tmp[k] = '0' + (t + 1) % 10;
                if (set_deadends.find(tmp) == set_deadends.end()) {
                    if (tmp == target) {
                        return res;
                    }
                    store.push(tmp);
                    set_deadends.insert(tmp);
                }
            }
            store.pop();
        }
        res += 1;
    }
    return -1;
}


/**************************************************************************************/
/* First solution:   BFS
 *                   1. Process special situation
 *                   2. Use a vector to store cases, cases[0] and cases[sum] is 1
 *                      Other is 2
 *                   3. Start BFS, use a queue to store results, queue element is
 *                      pair<int, int> that store current case
 *                   4. The branches of BFS search including several different
 *                      situations
 * Optimization:     solve a solution: a*x + b*y = z, in which a and b are integers and
 *                   a*x and b*y are less than common multiple of x,y*/
/**************************************************************************************/
bool Solution::canMeasureWater(int x, int y, int z) {
    if (z > x+y)
        return false;
    int large = 0;
    int small = 0;
    int b = 0;
    if (x > y) {
        large = x;
        small = y;
    } else {
        large = y;
        small = x;
    }
    while ((b*large-z) % small != 0) {
        b++;
        if (b*large % small == 0)
            return false;
    }
    return true;
}


/**************************************************************************/
/* Description: Given an N x N grid containing only values 0 and 1,
 * where 0 represents water and 1 represents land, find a water
 * cell such that its distance to the nearest land cell is maximized
 * and return the distance. The distance used in this problem is
 * the Manhattan distance: the distance between two cells
 * (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
 * If no land or water exists in the grid, return -1.
 *
 * Solution 1:  BFS,
 *              1. Find positions that contain 1 and push them into queue
 *              2. Find four directions, if any unvisited, push them
 * Solution 2:  How to optimize? */
/**************************************************************************/
int Solution::maxDistance(vector<vector<int> > &grid) {
    queue<pair<int, int>> positions;
    int N = grid.size();
    vector<int> init(N, 0);
    vector<vector<int>> visited(N, init);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j]) {
                positions.push(make_pair(i, j));
                visited[i][j] = 1;
            }
        }
    }
    int res = 0;
    while (!positions.empty()) {
        int size = positions.size();
        bool flag = false;
        for (int i = 0; i < size; i++) {
            pair<int, int> position = positions.front();
            int m = position.first;
            int n = position.second;
            if (m > 0 && !visited[m-1][n]) {
                flag = true;
                visited[m-1][n] = 1;
                positions.push(make_pair(m-1, n));
            }
            if (m < N-1 && !visited[m+1][n]) {
                flag = true;
                visited[m+1][n] = 1;
                positions.push(make_pair(m+1, n));
            }
            if (n > 0 && !visited[m][n-1]) {
                flag = true;
                visited[m][n-1] = 1;
                positions.push(make_pair(m, n-1));
            }
            if (n < N-1 && !visited[m][n+1]) {
                flag = true;
                visited[m][n+1] = 1;
                positions.push(make_pair(m, n+1));
            }
            positions.pop();
        }
        if (flag) res++;
    }
    if (!res)
        return -1;
    else
        return res;
}


/***********************************************************************************************/
/* Description: Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each
 * cell */
/***********************************************************************************************/
vector<vector<int>> Solution::updateMatrix(vector<vector<int> > &matrix) {
    vector<vector<int>> result = matrix;
    queue<pair<int, int>> distances;
    vector<vector<int>> direction = {{0, 1}, {1, 0},
                                     {-1, 0}, {0, -1}};
    int m = matrix.size();
    int n = matrix[0].size();

    // find 0 elements and initialize queue
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!matrix[i][j]) {
                distances.emplace(i, j);
                matrix[i][j] = -1;
            }
        }
    }

    // BFS
    while (!distances.empty()) {
        auto [a, b] = distances.front();
        distances.pop();
        int ref = result[a][b];
        for (auto direct: direction) {
            int c = a + direct[0];
            int d = b + direct[1];
            if (c >= 0 && c <= m - 1 && d >= 0 && d <= n-1 && matrix[c][d] > 0) {
                result[c][d] = ref + 1;
                matrix[c][d] = -1;
                distances.emplace(c, d);
            }
        }
    }

    return result;
}


/**
 * https://leetcode-cn.com/problems/surrounded-regions/
 * TODO: optimization
 *       1. find the 'O' that is on the border
 *       2. dfs/bfs the 'O' in the border and denote the path you traverse as "cannot be transformed to 'X' "
 *       3. traverse the matrix, change 'O' to 'X'
 * @param board
 */
void Solution::solve(vector<vector<char>> &board) {
    int m = board.size();
    int n = board[0].size();
    queue<pair<int, int>> store;
    vector<pair<int, int>> temp;
    vector<vector<int>> direct = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    vector<vector<int>> visited(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O' && !visited[i][j]) {
                temp.clear();
                store.emplace(i, j);
                visited[i][j] = 1;
                bool flag = false;
                while (!store.empty()) {
                    int size = store.size();
                    for (int k = 0; k < size; k++) {
                        int p = store.front().first;
                        int q = store.front().second;
                        if (p == 0 || p == m - 1 || q == 0 || q == n - 1) flag = true;
                        temp.emplace_back(p, q);
                        for (auto d : direct) {
                            int x = p + d[0], y = q + d[1];
                            if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'O' && !visited[x][y]) {
                                store.emplace(x, y);
                                visited[x][y] = 1;
                            }
                        }
                        store.pop();
                    }
                }
                if (!flag) {
                    for (auto t : temp) {
                        board[t.first][t.second] = 'X';
                    }
                }
            }
        }
    }
}


/**
 * https://leetcode-cn.com/problems/clone-graph/
 * TODO: implement DFS
 * @param node
 * @return
 */
Node* Solution::cloneGraph(Node *node) {
    if (!node) return nullptr;
    // BFS
    Node* new_node = new Node(node->val);
    queue<Node*> org_store;
    queue<Node*> new_store;
    org_store.push(node);
    unordered_map<Node*, Node*> correspond;
    new_store.push(new_node);
    correspond.emplace(node, new_node);
    while (!org_store.empty()) {
        int size = org_store.size();
        for (int i = 0; i < size; i++) {
            Node* org_node = org_store.front();
            Node* cur_node = new_store.front();
            for (int j = 0; j < org_node->neighbors.size(); j++) {
                auto it = correspond.find(org_node->neighbors[j]);
                if (it == correspond.end()) {
                    cur_node->neighbors.push_back(new Node(org_node->neighbors[j]->val));
                    org_store.push(org_node->neighbors[j]);
                    new_store.push(cur_node->neighbors[j]);
                    correspond.emplace(org_node->neighbors[j], cur_node->neighbors[j]);
                } else cur_node->neighbors.push_back(it->second);
            }
            org_store.pop();
            new_store.pop();
        }
    }
    return new_node;
}


/**
 * https://leetcode-cn.com/problems/remove-boxes/
 * TODO: Implement
 * @param boxes
 * @return
 */
int Solution::removeBoxes(vector<int> &boxes) {

}


/**
 * https://leetcode-cn.com/problems/flood-fill/
 * @param image
 * @param sr
 * @param sc
 * @param newColor
 * @return
 */

void dfs(vector<vector<int>>& image, int x, int y, int cur_color, int new_color) {
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int m = image.size(), n = image[0].size();
    for (auto d : directions) {
        int xx = x + d[0], yy = y + d[1];
        if (xx >= 0 && xx < m && yy >= 0 && yy < n && image[xx][yy] == cur_color) {
            image[xx][yy] = new_color;
            dfs(image, xx, yy, cur_color, new_color);
        }
    }
}

vector<vector<int>> Solution::floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
    // BFS
    /*int init_pixel = image[sr][sc];
    if (init_pixel == newColor) return image;
    queue<pair<int, int>> store;
    store.emplace(sr, sc);
    vector<vector<int>> directs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    int m = image.size(), n = image[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0));
    image[sr][sc] = newColor;
    while (!store.empty()) {
        int size = store.size();
        for (int i = 0; i < size; i++) {
            int x = store.front().first, y = store.front().second;
            for (auto direct : directs) {
                int x_ = x + direct[0];
                int y_ = y + direct[1];
                if (x_ >= 0 && x_ < m && y_ >= 0 && y_ < n && image[x_][y_] == init_pixel) {
                    store.emplace(x_, y_);
                    image[x_][y_] = newColor;
                }
            }
            store.pop();
        }
    }
    return image;*/

    // DFS
    int cur_color = image[sr][sc];
    if (cur_color == newColor) return image;
    image[sr][sc] = newColor;
    dfs(image, sr, sc, cur_color, newColor);
    return image;
}


/**
 * https://leetcode-cn.com/problems/minesweeper/
 * @param board
 * @param click
 * @return
 */
vector<vector<char>> Solution::updateBoard(vector<vector<char>> &board, vector<int> &click) {
    if (board[click[0]][click[1]] == 'M') {
        board[click[0]][click[1]] = 'X';
        return board;
    }
    queue<pair<int, int>> store;
    store.emplace(click[0], click[1]);
    vector<vector<int>> directs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int m = board.size(), n = board[0].size();
    board[click[0]][click[1]] = '-';
    while (!store.empty()) {
        int size = store.size();
        for (int i = 0; i < size; i++) {
            int a = store.front().first, b = store.front().second;
            int num_mines = 0;
            vector<pair<int, int>> temp;
            for (auto d : directs) {
                int x = a + d[0], y = b + d[1];
                if (x >= 0 && x < m && y >= 0 && y < n) {
                    if (board[x][y] == 'M') {
                        num_mines++;
                    }
                    else if (board[x][y] == 'E' && num_mines == 0) temp.emplace_back(x, y);
                }
            }
            if (num_mines == 0) {
                board[a][b] = 'B';
                for (auto e : temp) {
                    store.emplace(e.first, e.second);
                    board[e.first][e.second] = '-';
                }
            } else board[a][b] = num_mines + '0';
            store.pop();
            temp.clear();
        }
    }
    return board;
}


/**
 * https://leetcode-cn.com/problems/keys-and-rooms/
 * @param rooms
 * @return
 */
bool Solution::canVisitAllRooms(vector<vector<int>> &rooms) {
    queue<int> store;
    store.push(0);
    int N = rooms.size();
    vector<int> visited(N, 0);
    visited[0] = 1;
    int count = 1;
    while (!store.empty()) {
        int size = store.size();
        for (int i = 0; i < size; i++) {
            int cur = store.front();
            for (int next : rooms[cur]) {
                if (!visited[next]) {
                    visited[next] = 1;
                    store.push(next);
                    count++;
                }
            }
            store.pop();
        }
    }
    return count == N;
}


/**
 * https://leetcode-cn.com/problems/combination-sum-iii/
 * @param k
 * @param n
 * @return
 */
void dfs(int num, int count, int cur_sum, vector<int> cur_comb, int k, int n, vector<vector<int>>& res) {
    if (count == k) {
        if (cur_sum == n) {
            res.push_back(cur_comb);
        }
        return;
    }
    for (int i = num + 1; i <= 9; i++) {
        int next_sum = cur_sum + i;
        cur_comb[count] = i;
        dfs(i, count + 1, next_sum, cur_comb, k, n, res);
        cur_comb[count] = 0;
    }
}

vector<vector<int>> Solution::combinationSum3(int k, int n) {
    vector<int> cur_comb(k, 0);
    vector<vector<int>> res;
    cur_comb[0] = 1;
    int count = 0;
    for (int i = 1; i <= 9; i++) {
        cur_comb[0] = i;
        dfs(i, count + 1, i, cur_comb, k, n, res);
        cur_comb[0] = 0;
    }
    return res;
}


/**
 * https://leetcode-cn.com/problems/word-search/
 * @param board
 * @param word
 * @return
 */
vector<vector<int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void dfsWord(int x, int y, const string& word, string& cur_res, bool& res, vector<vector<int>>& visited,
             vector<vector<char>>& board) {
    if (cur_res == word) {
        res = true;
        return;
    }
    if (cur_res.size() >= word.size()) return;
    int p = (int) cur_res.size() - 1;
    if (cur_res[p] != word[p]) return;
    int m = visited.size(), n = visited[0].size();
    for (auto d : directions) {
        int a = x + d[0], b = y + d[1];
        if (a >= 0 && a < m && b >= 0 && b < n && !visited[a][b]) {
            visited[a][b] = 1;
            cur_res.push_back(board[a][b]);
            dfsWord(a, b, word, cur_res, res, visited, board);
            if (res) return;
            visited[a][b] = 0;
            cur_res.pop_back();
        }
    }
}

bool Solution::exist(vector<vector<char>> &board, const string& word) {
    int m = board.size(), n = board[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0));
    bool res = false;
    string cur_res;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0]) {
                visited[i][j] = 1;
                cur_res.push_back(board[i][j]);
                dfsWord(i, j, word, cur_res, res, visited, board);
                visited[i][j] = 0;
                cur_res.pop_back();
                if (res) return res;
            }
        }
    }
    return res;
}


/**
 * https://leetcode-cn.com/problems/permutations-ii/
 * @param nums
 * @return
 */
void dfs(vector<int>& cur, vector<vector<int>>& res, vector<int>& nums,
         vector<int>& visited, int& id, unordered_set<int>& store) {
    int n = nums.size();
    if (cur.size() == n && store.find(id) == store.end()) {
        store.insert(id);
        res.push_back(cur);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cur.push_back(nums[i]);
            visited[i] = 1;
            id = id * 10 + nums[i];
            dfs(cur, res, nums, visited, id, store);
            visited[i] = 0;
            id = (id - nums[i]) / 10;
            cur.pop_back();
        }
    }
}

vector<vector<int>> Solution::permuteUnique(vector<int> &nums) {
    int n = nums.size();
    unordered_set<int> store;
    vector<int> visited(n, 0);
    vector<int> cur;
    vector<vector<int>> res;
    int id = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cur.push_back(nums[i]);
            visited[i] = 1;
            id = id * 10 + nums[i];
            dfs(cur, res, nums, visited, id, store);
            visited[i] = 0;
            id = (id - nums[i]) / 10;
            cur.pop_back();
        }
    }
    return res;
}

/**
 * https://leetcode-cn.com/problems/bricks-falling-when-hit/
 * @param grid
 * @param hits
 * @return
 */
void BFSWithoutFirstLine(vector<vector<int>>& grid, vector<vector<int>>& visited,
                         vector<vector<vector<pair<int,int>>>> &dependencies,
                         int a, int b, bool flag, int& drop) {
    if (flag) {
        if (grid[a][b] <= 1) {
            return;
        }
    }
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> directs = {{1,0},{0,1},{-1,0},{0,-1}};
    queue<pair<int, int>> store;
    if (flag) {
        grid[a][b]--;
    } else {
        grid[a][b]++;
    }
    store.emplace(a, b);
    visited[a][b] = 1;
    while (!store.empty()) {
        int size = store.size();
        for (int i = 0; i < size; i++) {
            pair<int, int> front = store.front();
            int x = front.first, y = front.second;
            if (!flag) {
                for (auto d : directs) {
                    int p = x + d[0], q = y + d[1];
                    if (p > 0 && p < m && q >= 0 && q < n && !visited[p][q]) {
                        if (grid[p][q]) {
                            visited[p][q] = 1;
                            dependencies[x][y].emplace_back(p, q);
                            grid[p][q]++;
                            store.emplace(p, q);
                        }
                    }
                }
            } else {
                for (auto d : dependencies[x][y]) {
                    int p = d.first, q = d.second;
                    if (!visited[p][q]) {
                        if (grid[p][q] > 1) {
                            grid[p][q]--;
                            visited[p][q] = 1;
                            if (grid[p][q] == 1) {
                                drop++;
                            }
                            store.emplace(p, q);
                        }
                    }
                }
            }
            store.pop();
        }
    }
}

vector<int> Solution::hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits) {
    // 1. indexing
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0));
    vector<vector<int>> vis = visited;
    vector<vector<vector<pair<int,int>>>>
    dependencies(m, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>()));
    int drop = 0;
    for (int i = 0; i < n; i++) {
        if (grid[0][i]) {
            vis = visited;
            BFSWithoutFirstLine(grid, vis, dependencies, 0, i, false, drop);
        }
    }
    // 2. Calculate drops
    vector<int> res;
    for (auto hit : hits) {
        drop = 0;
        vis = visited;
        BFSWithoutFirstLine(grid, vis, dependencies, hit[0], hit[1], true, drop);
        res.push_back(drop);
    }
    return res;
}