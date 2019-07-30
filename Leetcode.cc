#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <unordered_set>
#include <unordered_map>


// 模拟实现的循环队列
class MyCircularQueue {
public:
	/** Initialize your data structure here. Set the size of the queue to be k. */
	MyCircularQueue(int k) {
		_queue.reserve(k);
		_head = -1;
		_tail = -1;
		_size = k;
	}

	/** Insert an element into the circular queue. Return true if the operation is successful. */
	bool enQueue(int value) { // 入队
		if(isFull()) {
			return false;
		}

		if(isEmpty()) {
			_head = 0;
		}

		_tail = (_tail+1) % _size;
		_queue[_tail] = value;
		return true;
	}

	/** Delete an element from the circular queue. Return true if the operation is successful. */
	bool deQueue() { // 出队 
		if(isEmpty()) {
			return false;
		}

		if(_head == _tail) {
			_head = _tail = -1;
			return true;
		}

		_head = (_head+1) % _size;
		return true;
	}

	/** Get the front item from the queue. */
	int Front() {
		if(isEmpty()) {
			return -1;
		}
		return _queue[_head];
	}

	/** Get the last item from the queue. */
	int Rear() {
		if(isEmpty()) {
			return -1;
		}
		return _queue[_tail];
	}

	/** Checks whether the circular queue is empty or not. */
	bool isEmpty() {
		return _head == -1;
	}

	/** Checks whether the circular queue is full or not. */
	bool isFull() {
		return (_tail+1)%_size == _head;	
	}

private:
	std::vector<int> _queue;
	int _head;
	int _tail;
	int _size;
};

// 重建二叉树

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


TreeNode* reConstructBinaryTree(std::vector<int> pre, std::vector<int> vin) {
	if(pre.empty() || vin.empty()) {
		return nullptr;
	}

	TreeNode *root = new TreeNode(pre[0]);
	std::vector<int> pre_left, pre_right, vin_left, vin_right;

	int mid = 0;
	for(size_t i = 0; i < vin.size(); ++i) {
		if(pre[0] == vin[i]) {
			mid = i;
			break;
		}
	}

	for(int i = 0; i < mid; ++i) {
		vin_left.push_back(vin[i]);
		pre_left.push_back(pre[i+1]);
	}

	for(size_t i = mid+1; i < vin.size(); ++i) {
		vin_right.push_back(vin[i]);
		pre_right.push_back(pre[i]);
	}

	root->left = reConstructBinaryTree(pre_left, vin_left);
	root->right = reConstructBinaryTree(pre_right, vin_right);

	return root;
}


// 旋转数组的最小数字
int minNumberInRotateArray(std::vector<int> rotateArray) {
	if(rotateArray.empty()) {
		return 0;
	}

	int left = 0;
	int right = rotateArray.size()-1;
	int mid = left;

	while(rotateArray[left] >= rotateArray[right]) {
		if(right - left == 1) {
			mid = right;
			break;
		}

		mid = (right + left) / 2;
		if(rotateArray[left] <= rotateArray[mid]) {
			left = mid;
		}

		if(rotateArray[right] >= rotateArray[mid]) {
			right = mid;
		}
	}

	return rotateArray[mid];
}

// unique-paths
// 简单的dp问题, F(i,j) 表示从左上角到目前位置的最大路径,
// 由于知识向右或者向下, 所以只需要看 F(i-1, j) 和 F(i, j-1) 即可

int uniquePaths(int m, int n) {
	if(m <= 0 || n <= 0) {
		return 0;
	}

	// 边界条件不论如何走都是 1, 所以初始化为1
	std::vector<std::vector<int>> pathSum(m, std::vector<int>(n, 1));

	for(int i = 1; i < m; ++i) {
		for(int j = 1; j < n; ++j) {
			pathSum[i][j] = pathSum[i][j-1] + pathSum[i-1][j];
		}
	}

	return pathSum[m-1][n-1];
}


// 如果当前矩阵中有障碍物, 那么就走不通, 这时候分两种情况
// 如果为 1, 就直接为0, 如果不为1, 就按之前的状态方程
// [
//   [0,0,0],
//   [0,1,0],
//   [0,0,0]
// ]   pathSum = 2

int uniquePathsWithObstacles(std::vector<std::vector<int> > &obstacleGrid) {
	if(obstacleGrid.empty()) {
		return 0;
	}

	int row = obstacleGrid.size();
	int col = obstacleGrid[0].size();

	std::vector<std::vector<int>> pathSum(row, std::vector<int>(col, 0));

	// init row
	for(int i = 0; i < col; ++i) {
		if(!obstacleGrid[0][i]) {
			pathSum[0][i] = 1;
		} else {
			break;
		}
	}

	// init col
	for(int i = 0; i < row; ++i) {
		if(obstacleGrid[i][0] == 0) {
			pathSum[i][0] = 1;
		} else {
			break;
		}
	}

	for(int i = 1; i < row; ++i) {
		for(int j = 1; j < col; ++j) {
			if(obstacleGrid[i][j] == 1) {
				pathSum[i][j] = 0;
			} else {
				pathSum[i][j] = pathSum[i-1][j] + pathSum[i][j-1];
			}
		}
	}

	return pathSum[row-1][col-1];
}

// 需要走的最少路径 需要注意初始条件的判断
// minimum-path-sum
int minPathSum(std::vector<std::vector<int> > &grid) {
	if(grid.empty()) {
		return 0;
	}

	int row = grid.size();
	int col = grid[0].size();

	std::vector<std::vector<int>> minPath(row, std::vector<int>(col, 0));
	minPath[0][0] = grid[0][0];

	for(int i = 1; i < col; ++i) {
		minPath[0][i] = grid[0][i] + minPath[0][i-1];
	}
 
	for(int i = 1; i < row; ++i) {
		minPath[i][0] = grid[i][0] + minPath[i-1][0];
	}

	for(int i = 1; i < row; ++i) {
		for(int j = 1; j < col; ++j) {
			minPath[i][j] = std::min(minPath[i-1][j], minPath[i][j-1]) + grid[i][j];
		}
	}

	return minPath[row-1][col-1];
}


// offer 最大连续字数组的和
int FindGreatestSumOfSubArray(std::vector<int> array) {
	if(array.empty()) {
		return 0;
	}

	int cur = array[0];
	int sum = array[0];

	for(size_t i = 1; i < array.size(); ++i) {
		cur = cur < 0 ? array[i] : array[i] + cur;
		sum = cur < sum ? sum : cur;
	}

	return sum;
}

// 单词分割 
bool wordBreak(std::string s, std::unordered_set<std::string> &dict) {
	if(dict.empty() || s.empty()) {
		return false;
	}

	size_t max_len = 0;
	for(auto& e : dict) {
		if(max_len < e.size()) {
			max_len = e.size();
		}
	}

	std::vector<bool> res(s.size()+1, false);
	res[0] = true; // 虚拟位

	for(size_t i = 1; i <= s.size(); ++i) {
		for(size_t j = i-1; j >= 0; --j) {
			if(i-j > max_len) 
				break;

			if(res[j] && dict.find(s.substr(i, i-j)) != dict.end()) {
				res[i] = true;
				break;
			}
		}
	}

	return res[s.size()];
}


// 查找最短路径, 使用逆向思维
// [
//  [2],
//  [3,4],
//  [6,5,7],
//  [4,1,8,3]
// ]


int minimumTotal(std::vector<std::vector<int> > &triangle) {
	if(triangle.empty()) {
		return 0;
	}

	std::vector<std::vector<int>> res(triangle);
	int line = triangle.size();

	for(int i = line-2; i >= 0; --i) {
		for(int j = 0; j <= i; ++j) {
			res[i][j] = std::min(res[i+1][j], res[i+1][j+1]) + triangle[i][j];
		}
	}

	return res[0][0];
}


// dp of 01 backage
// @m, 表示背包容量
// @A, 表示每个物品的大小
// @V, 表示每个物品的价值

int backPackII(int m, std::vector<int> A, std::vector<int> V) {
	if(m < 1 || A.empty() || V.empty()) {
		return 0;
	}

	int N = A.size() + 1;
	int M = m + 1;

	std::vector<std::vector<int>> res(N, std::vector<int>(M, 0));
 
	for(int i = 1; i < N; ++i) {
		for(int j = 1; j < M; ++j) {
			// j表示现在的背包容量, A[i-1]表示第一个物品的大小
			if(A[i-1] > j) { // 表示现在放不下
				res[i][j] = res[i-1][j];
			} else { // 现在考虑放与不放的问题
				res[i][j] = std::max(res[i-1][j], res[i-1][j-A[i-1]]+V[i-1]);
			}
		}
	}

	return res[N-1][M-1];
}

// leetcode 打家劫舍
// 你是一个专业的小偷，计划偷窃沿街的房屋。
// 每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装
// 有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
//
// 给定一个代表每个房屋存放金额的非负整数数组，
// 计算你在不触动警报装置的情况下，能够偷窃到的最高金额。

int rob(std::vector<int>& nums) {
	if(nums.empty()) {
		return 0;
	}

	if(nums.size() == 1) {
		return nums[0];
	}

	if(nums.size() == 2) {
		return std::max(nums[0], nums[1]);
	}

	std::vector<int> dp(nums.size());
	dp[0] = nums[0];
	dp[1] = nums[0] > nums[1] ? nums[0] : nums[1];

	for(size_t i = 2; i < nums.size(); ++i) {
		dp[i] = std::max(dp[i-1], nums[i] + dp[i-2]);
	}

	return dp[nums.size()-1];
}


// leetcode 49 字谜分组
// 核心思想使用 hash 映射
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
	std::vector<std::vector<std::string>> res;
	if(strs.empty()) {
		return res;
	}

	std::unordered_map<std::string, std::vector<std::string>> fix;

	for(auto s : strs) {
		std::string str = s;
		std::sort(str.begin(), str.end());
		fix[str].push_back(s);
	}

	for(auto e : fix) {
		res.push_back(e.second);
	}

	return res;
}

// leetcode  ** 无重复字符的最长子串 **, dp思想
int lengthOfLongestSubstring(std::string s) {
	if(s.empty()) {
		return 0;
	}

	int res = 0, leftIndex = 0, size = s.size();
	std::unordered_map<char, int> count;

	for(int i = 0; i < size; ++i) {
		leftIndex = std::max(leftIndex, count[s[i]]);
		count[s[i]] = i + 1;
		res = std::max(res, i-leftIndex+1);
	}

	return res;
}


// 递增的三元子序列， 遍历一次
bool increasingTriplet(std::vector<int>& nums) {
	if(nums.size() < 3) {
		return false;
	}

	std::vector<int> res;
	res.push_back(nums[0]);

	for(size_t i = 1; i < nums.size(); ++i) {
		if(nums[i] > res.back()) {
			res.push_back(nums[i]);
			if(nums.size() == 3) {
				return true;
			}
		} else if (nums[i] < res[0]) {
			res[0] = nums[i];
		}

		if(nums.size() == 2 && nums[i] > res[0] && nums[i] < res[1]) {
			res[1] = nums[i];
		}
	}

	return false;
}

// 二叉搜素书中第K小的元素

// static void inOrder(TreeNode *root, std::vector<int>& res) {
// 	if(!root) {
// 		return;
// 	}
// 
// 	inOrder(root->left, res);
// 	res.push_back(root->val);
// 	inOrder(root->right, res);
// }
// 
// int kthSmallest(TreeNode* root, int k) {
// 	if(!root || k <= 0) {
// 		return 0;
// 	}
// 
// 	std::vector<int> res;
// 	inOrder(root, res);
// 
// 	return res[k-1];
// }
// 迭代
int kthSmallest(TreeNode* root, int k) {
	if(!root || k <= 0) {
		return 0;
	}

	std::stack<TreeNode*> s;
	std::vector<int> res;

	while(root || !s.empty()) {
		while(root) {
			s.push(root);
			root = root->left;
		}

		TreeNode *top = s.top();
		s.pop();
		res.push_back(top->val);
		if((int)res.size() == k) {
			break;
		}
		root = top->right;
	}

	return res[k-1];
}


struct Node {
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() {}

	Node(int _val, Node* _left, Node* _right, Node* _next) {
		val = _val;
		left = _left;
		right = _right;
		next = _next;

	}
};

// 给定一个完美二叉树, 填充每个节点的下一个右侧结点
// 使用递归
Node *connect(Node *root) {
	if(!root) {
		return root;
	}

	if(root->left) {
		root->left->next = root->right;
	}

	if(root->right) {
		root->right->next = root->next ? root->next->left : NULL;
	}

	connect(root->left);
	connect(root->right);

	return root;
}


// 零钱兑换 
// 输入: coins = [1, 2, 5], amount = 11
// 输出: 3 
// 解释: 11 = 5 + 5 + 1

int coinChange(std::vector<int>& coins, int amount) {
	if(coins.empty() || amount <= 0) {
		return 0;
	}

	std::vector<int> dp(amount+1, amount+1);
	int size = coins.size();
	dp[0] = 0;

	for(int i = 1; i <= amount; ++i) {
		for(int j = 0; j < size; ++j) {
			if(i < coins[j]) {
				continue;
			}

			dp[i] = std::min(dp[i], dp[i-coins[j]]+1);
		}
	}
	if(dp[amount] > amount) {
		return -1;
	}

	return dp[amount];
}

// Longest Increasing Subsequence
int lengthOfLIS(std::vector<int>& nums) {
	if(nums.empty()) {
		return 0;
	}
	std::vector<int> dp(nums.size(), 1);
	int res = 1;

	for(size_t i = 0; i < nums.size(); ++i) {
		for(size_t j = 0; j < i; ++j) {
			if(nums[i] > nums[j]) {
				dp[i] = std::max(dp[i], dp[j]+1);
				res = std::max(res, dp[i]);
			}
		}
	}

	return res;
}

// 最长公共子串
int findLongest(std::string A, int n, std::string B, int m) {
	if(n <= 0 || m <= 0) {
		return 0;
	}

	std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
	int res = 0;

	// init row
	for(int i = 0; i < m; ++i) {
		if(A[0] == B[i]) {
			dp[0][i] = 1;
		}
	}

	for(int i = 0; i < n; ++i) {
		if(A[i] == B[0]) {
			dp[i][0] = 1;
		}
	}

	for(int i = 1; i < n; ++i) {
		for(int j = 1; j < m; ++j) {
			if(A[i] == B[j]) {
				dp[i][j] = dp[i-1][j-1] + 1;
				res = std::max(res, dp[i][j]);
			}
		}
	}

	return res;
}

int main()
{
	std::vector<int> vec{1, 2, 5};
	std::cout << coinChange(vec, 11) << std::endl;
	return 0;
}
