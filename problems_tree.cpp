//
// Created by zyl on 2020/2/22.
//
#include "function_defs.h"


TreeNode* Solution::buildTree(vector<int>& inOrder, vector<int>& postOrder) {
    TreeNode* root = new TreeNode(postOrder[postOrder.size() - 1]);
    if (inOrder.size() == 1)
        return root;
    vector<int> new_inOrder;
    vector<int> new_postOrder;
    for (int i = 0; i < inOrder.size(); i++) {
        if (inOrder[i] == postOrder[postOrder.size() - 1]) {
            if (i > 0) {
                new_inOrder.assign(inOrder.begin(), inOrder.begin()+i);
                new_postOrder.assign(postOrder.begin(), postOrder.begin()+i);
                root->left = buildTree(new_inOrder, new_postOrder);
            }
            if (!new_inOrder.empty())
                new_inOrder.clear();
            if (!new_postOrder.empty())
                new_postOrder.clear();
            if (i < postOrder.size()-1) {
                new_inOrder.assign(inOrder.begin()+i+1, inOrder.end());
                new_postOrder.assign(postOrder.begin()+i, postOrder.end()-1);
                root->right = buildTree(new_inOrder, new_postOrder);
            }
        }
    }
    return root;
}


vector<vector<int>> Solution::zigzagLevelOrder(TreeNode* root) {
    if (!root)
        return {};
    vector<TreeNode*> vctStack1;
    vector<TreeNode*> vctStack2;
    vctStack1.push_back(root);
    vector<int> temp;
    vector<vector<int>> result;
    TreeNode* top = NULL;
    bool Flag = false;
    while (!vctStack1.empty() || !vctStack2.empty()) {
        if (vctStack2.empty() && Flag) {
            Flag = false;
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
        }
        if (vctStack1.empty() && !Flag) {
            Flag = true;
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
        }
        if (Flag) {
            top = vctStack2[vctStack2.size()-1];
            vctStack2.pop_back();
            temp.push_back(top->val);
            if (top->right)
                vctStack1.push_back(top->right);
            if (top->left)
                vctStack1.push_back(top->left);
        }
        else {
            top = vctStack1[vctStack1.size()-1];
            vctStack1.pop_back();
            temp.push_back(top->val);
            if (top->left)
                vctStack2.push_back(top->left);
            if (top->right)
                vctStack2.push_back(top->right);
        }
    }
    if (!temp.empty())
        result.push_back(temp);
    return result;
}


void inOrder(TreeNode* root, vector<int>& vctRes) {
    if (root->left)
        inOrder(root->left, vctRes);
    vctRes.push_back(root->val);
    if (root->right)
        inOrder(root->right, vctRes);
}


vector<int> getVecTree(TreeNode* root) {
    if (!root)
        return {};
    vector<int> vctRes;
    inOrder(root, vctRes);
    return vctRes;
}

vector<int> Solution::getAllElements(TreeNode *root1, TreeNode *root2) {
    vector<int> vctTree1 = getVecTree(root1);
    vector<int> vctTree2 = getVecTree(root2);
    if (vctTree1.empty())
        return vctTree2;
    if (vctTree2.empty())
        return vctTree1;
    vector<int> vctRes;
    int i, j;
    i = 0;
    j = 0;
    while (i < vctTree1.size() || j < vctTree2.size()) {
        if (j == vctTree2.size())
            vctRes.push_back(vctTree1[i++]);
        else if (i == vctTree1.size())
            vctRes.push_back(vctTree2[j++]);
        else if (vctTree1[i] < vctTree2[j])
            vctRes.push_back(vctTree1[i++]);
        else
            vctRes.push_back(vctTree2[j++]);
    }
    return vctRes;
}


int depth(TreeNode* root) {
    if (root) {
        int depth_left = depth(root->left);
        int depth_right = depth(root->right);
        if (depth_left >= depth_right)
            return ++depth_left;
        else
            return ++depth_right;
    }
    return 0;
}

/*****************************************************************/
/* Solution: 1. Compute depth of left and depth of right         */
/*           2. Compute the sum of depths of left and right      */
/*           3. Compare the sum and the depth_left and depth_right
 *              and return the minimum                           */
/*****************************************************************/
int Solution::diameterOfBinaryTree(TreeNode* root) {
    if (!root)
        return 0;
    int d = 0;
    int dl = 0;
    int dr = 0;
    d += depth(root->left);
    dl = diameterOfBinaryTree(root->left);
    d += depth(root->right);
    dr = diameterOfBinaryTree(root->right);
    if (d <= 2)
        return d;
    if (d <= dl)
        d = dl;
    if (d <= dr)
        d = dr;
    return d;
}



// 不同搜索二叉树|
int Solution::numTrees(int n) {
    vector<int> vctRes;
    int j = 0;
    int k = 0;
    int iTemp = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0)
            vctRes.push_back(1);
        else {
            j = 1;
            k = i+1;
            iTemp = 0;
            while (j <= k) {
                if (j == 1)
                    iTemp += 2 * vctRes[i-1];
                else if (j == k)
                    iTemp += vctRes[j-1-1] * vctRes[i-j];
                else
                    iTemp += 2 * vctRes[j-1-1] * vctRes[i-j-1];
                j++;
                k--;
            }
            vctRes.push_back(iTemp);
        }
    }
    return vctRes[n-1];
}


TreeNode* addTreeValue(int m, TreeNode* treeNode) {
    TreeNode* pRes = nullptr;
    if (nullptr != treeNode) {
        pRes = new TreeNode(treeNode->val + m);
        if (treeNode->left)
            pRes->left = addTreeValue(m, treeNode->left);
        if (treeNode->right)
            pRes->right = addTreeValue(m, treeNode->right);
    }
    return pRes;
}

// 不同搜索二叉树||
vector<TreeNode*> Solution::generateTrees(int n) {
    vector<vector<TreeNode*> > vctRes;
    vector<TreeNode*> vctTmpRes;
    if (n == 1) {
        auto* pNode = new TreeNode(1);
        vctTmpRes.push_back(pNode);
        return vctTmpRes;
    }
    TreeNode* pNode = nullptr;
    for (int i = 0; i < n; i++) {
        if (!vctTmpRes.empty())
            vctTmpRes.clear();
        if (i == 0) {
            pNode = new TreeNode(1);
            vctTmpRes.push_back(pNode);
        }
        else {
            for (int j = 1; j <= i+1; j++) {
                if (j == 1) {
                    for (int k = 0; k < vctRes[i-j].size(); k++) {
                        pNode = new TreeNode(j);
                        pNode->right = addTreeValue(j, vctRes[i-j][k]);
                        vctTmpRes.push_back(pNode);
                    }
                }
                else if (j == i+1) {
                    for (auto & k : vctRes[i-1]) {
                        pNode = new TreeNode(j);
                        pNode->left = addTreeValue(0, k);
                        vctTmpRes.push_back(pNode);
                    }
                }
                else {
                    for (int k = 0; k < vctRes[j-1-1].size(); k++) {
                        for (int m = 0; m < vctRes[i-j].size(); m++) {
                            pNode = new TreeNode(j);
                            pNode->left = addTreeValue(0, vctRes[j-1-1][k]);
                            pNode->right = addTreeValue(j, vctRes[i-j][m]);
                            vctTmpRes.push_back(pNode);
                        }
                    }
                }
            }
        }
        vctRes.push_back(vctTmpRes);
    }
    return vctRes[n-1];
}


/*****************************************************************/
/* Description: Given a binary tree, find its maximum depth
 * Solution 1:  recurrence
 * Solution 2:  level traverse
 * follow up: how to print the route of max depth? */
/*****************************************************************/
int Solution::maxDepth(TreeNode *root) {
    if (!root)
        return 0;
    queue<TreeNode*> level_nodes;
    int depth = 0;

    level_nodes.push(root);
    while (!level_nodes.empty()) {
        int size = level_nodes.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = level_nodes.front();
            if (node->left)
                level_nodes.push(node->left);
            if (node->right)
                level_nodes.push(node->right);
            level_nodes.pop();
        }
        depth++;
    }
    return depth;
}