# 剑指offer部分题目解析

## 二维数组中的查找
- 题目比较简单, 从一个边角开始根据题目遍历即可,

## 从尾到头打印单链表
- 可以使用递归或者vector insert

## 重建二叉树
- 根据前序遍历和中序遍历重建二叉树

```c++
TreeNode* reConstructBinaryTree(std::vector<int> pre, std::vector<int> vin) {
	if(vec.empty()) {
		return nullptr;
	}

	TreeNode *root = new TreeNode(pre[0]);
	std::vector<int> left_pre, left_in, right_pre, right_in;

	int tmp;
	for(int i = 0; i < vin.size(); i++) {
		if(pre[0] == vin[i]) {
			tmp = i;
			break;
		}
	}

	for(int i = 0; i < tmp; i++) {
		left_in.push_back(vin[i]);
		left_pre.push_back(pre[i+1]);
	}

	for(int i = tmp+1; i < vin.size(); i++) {
		right_in.push_back(vin[i]);
		right_pre.push_back(pre[i]);
	}

	root->left = reConstructBinaryTree(left_pre, left_in);
	root->right = reConstructBinaryTree(right_pre, right_in);

	return root;
}
```

## 旋转数组的最小数字
- 本质上还是用二分查找

```c++
int minNumberInRotateArray(std::vector<int> rotateArray) {
	if(rotateArray.empty()) {
		return 0;
	}

	int begin = 0, end = rotateArray.size()-1;
	int indexMid = begin;
	while(rotateArray[begin] >= rotateArray[end]) {
		if(end - begin == 1) {
			indexMid = end;
			break;
		}
		indexMid = (begin + end) / 2;
		if(rotateArray[begin] <= rotateArray[indexMid]) {
			begin = indexMid;
		}

		if(rotateArray[end] >= rotateArray[indexMid]) {
			end = indexMid;
		}
	}

	return rotateArray[indexMid];
}
```

## 调整数组顺序使奇数位于偶数的前面
- 冒泡排序或者前后指针

```C++
void reOrderArray(std::vector<int> &array) {
	if(array.empty()) {
		return;
	}

	for(int i = 0; i < array.size()-1; i++) {
		for(int j = 0; j < array.size()-1-i; j++) {
			if(array[j]%2 == 0 && array[j+1]%2 == 1) {
				std::swap(array[j], array[j+1]);
			}
		}
	}
}
```

## 链表的倒数第k个节点
- 一个指针先走k-1步

```c++
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
	if(pListHead == nullptr || k == 0) {
		return nullptr;
	}

	ListNode *pFast = pListHead;
	ListNode *pSlow = pListHead;

	for(unsigned int i = 0; i < k-1; i++) {
		if(pFast->next) {
			pFast = pFast->next;
		} else {
			return nullptr;
		}
	}

	while(pFast->next) {
		pSlow = pSlow->next;
		pFast = pFast->next;
	}

	return pSlow;
}
```

## 反转链表
- 使用头删头插

## 合并两个排序链表
- 使用递归或者非递归

```c++
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
	if(pHead1 == nullptr) {
		return pHead2;
	}

	if(pHead2 == nullptr) {
		return pHead1;
	}

	ListNode *node = nullptr;
	if(pHead1->val < pHead2->val) {
		node = pHead1;
		node->next = Merge(pHead1->next, pHead2);
	} else {
		node = pHead2;
		node->next = Merge(pHead1, pHead2->next);
	}

	retrun node;
}
```

## 复杂链表的复制
- 先对每个节点进制复制一遍

```c++
RandomListNode* Clone(RandomListNode* pHead) {
	if(pHead == nullptr) {
		return nullptr;
	}

	RandomListNode *node = pHead;
	RandomListNode *newNode = nullptr, *cur = nullptr, *tmp = nullptr;

	// 复制原来的链表
	while(node) {
		newNode = new(node->val);
		newNode->next = node->next;
		node->next = newNode;
		node = newNode->next;
	}

	// 复制复杂关系
	node = pHead;
	while(node) {
		if(node->random != nullptr) {
			node->next->random = node->random->next;
		}
		node = node->next->next;
	}

	// 断开链表
	node = pHead;
	cur = tmp = node->next;
	node->next = tmp->next;
	node = node->next;

	while(node) {
		tmp->next = node->next;
		tmp = tmp->next;
		node->next = tmp->next;
		node = node->next;
	}

	return cur;
}
```

## 两个链表的公共节点
- 让长的链表先走

```c++
int getLen(ListNode *node) {
	int len = 0;
	while(node) {
		node = node->next;
		len++;
	}

	return len;
}

ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2 ) {
	if(pHead1 == nullptr || pHead2 == nullptr) {
		return nullptr;
	}

	int len1 = getLen(pHead1);
	int lne2 = getLen(pHead2);

	int size = len1 - len2;
	ListNode *longList = pHead1;
	ListNode *shortList = pHead2;
	if(len1 < len2) {
		size = len2 - len1;
		longList = pHead2;
		shortList = pHead1;
	}

	while(size--) {
		longList = longList->next;
	}

	while(longList != shortList) {
		longList = longList->next;
		shortList = shortList->next;
	}

	return longList;
}
```

## 链表中环的入口节点
- 快慢指针

```c++
ListNode* EntryNodeOfLoop(ListNode* pHead) {
	if(pHead == nullptr) {
		return nullptr;
	}

	ListNode *fast = pHead;
	ListNode *slow = pHead;
	while(fast->next) {
		fast = fast->next->next;
		slow = slow->next;

		if(fast == slow) { // have cirle
			int count = 1;
			ListNode *node = fast->next;
			while(node != fast) {
				count++;
				node = node->next;
			}
			fast = pHead;
			slow = pHead;
			while(count--) {
				fast = fast->next;
			}

			while(slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
	}

	return nullptr;
}
```

## 删除链表中重复节点

```c++
ListNode* deleteDuplication(ListNode* pHead) {
	if(pHead == nullptr || pHead->next == nullptr) {
		return pHead;
	}

	ListNode *node = pHead;
	ListNode *next = *cur = nullptr;

	while(node) {
		next = node->next;
		int val = node->val;
		if(next != nullptr && val == next->val) {
			while(next != nullptr && val == next->val) {
				next = next->next;
			}
			if(cur == nullptr) {
				pHead = next;
			} else {
				cur->next = next;
			}
			node = next;
		} else {
			cur = node;
			node = node->next;
		}
	}

	return pHead;
}
```


## 树的子结构

```
bool isTrue(TreeNode * node1, TreeNode * node2) {
	if(!node2) {
		return true;
	}
	if(!node1) {
		return false;
	}

	return isTrue(node1->left, node2->right) &&
			isTrue(node1->right, node2->left);
}

bool HasSubtree(TreeNode * pRoot1, TreeNode * pRoot2) {
	bool res = false;
	if(pRoot1 != nullptr && pRoot2 != nullptr) {
		if(pRoot1->val == pRoot2->val) {
			res = isTrue(pRoot1, pRoot2);
		}

		if(!res) {
			res = isTrue(pRoot1->left, pRoot2);
		}
		if(!res) {
			res = isTrue(pRoot1->right, pRoot2);
		}
	}
	return res;
}
```

## 栈的压入弹出序列
- 模拟入栈判断出栈

```
bool IsPopOrder(std::vector<int> pushV, std::vector<int> popV) {
	std::stack<int> stackData;
	int id = 0;

	for(int i = 0; i < popV.size(); i++) {
		while(stackData.empty() || stackData.top() != popV[i]) {
			stackData.push(pushV[id++]);
		}
		if(stackData.top() == popV[i]) {
			stackData.pop();
		}
	}

	if(stackData.empty()) {
		return true;
	}

	return false;
}
```

## 从上到下打印二叉树

```
vector<int> PrintFromTopToBottom(TreeNode* root) {
	std::vector<int> res;
	std::queue<TreeNode*> q;

	if(root == nullptr) {
		return res;
	}

	q.push(root);

	while(!q.empty()) {
		TreeNode *node = q.front();
		q.pop();

		vec.push_back(node->val);

		if(node->left) {
			q.push(node->left);
		}
		if(node->right) {
			q.push(node->right);
		}
	}
}
```

## 二叉搜索树的后续遍历序列
- 根据搜索树性质

```
bool VerifySquenceOfBST(std::vector<int> sequence) {
	if(sequence.empty()) {
		return false;
	}

	int size = sequence.size(), i = 0;
	while(--size) {
		while(sequence[i++] < sequence[size]);
		while(sequence[i++] > sequence[size]);

		if(i < size) {
			return false;
		}
		i = 0;
	}
	return true;
}
```

## 二叉树中和为某一值的路径

```
std::vector<std::vector<int> > res;
std::vector<int> tmp;

std::vector<std::vector<int> > FindPath(TreeNode* root,int expectNumber) {
	if(root == nullptr) {
		return res;
	}

	tmp.push_back(root->val);
	if((root->val)-expectnumber == 0 && root->left == nullptr && root->right == nullptr) {
		res.push_back(tmp);
	}

	FindPath(root->left, expectNumber);
	FindPath(root->right, expectNumber);

	if(tmp.size() != 0) {
		tmp.pop_back();
	}

	return res;
}

// 2 offer 184

void FindPath(TreeNode *root, int expectNumber, std::vector<int>& path, int cur) {
	cur += root->val;
	path.push_back(root->val);

	bool isLeaf = root->left == nullptr && root->right == nullptr;
	if(cur == expectNumber && isLeaf) {
		print(path);
	}

	if(root->left) {
		FindPath(root->left, expectNumber, path, cur);
	}
	if(root->right) {
		FindPath(root->right, expectNumber, path, cur);
	}
	path.pop_back();


void FindPath(TreeNode* root,int expectNumber) {
	if(root == nullptr) {
		return;
	}
	std::vector<int> path;
	int cur = 0;
	FindPath(root, expectNumber, path, cur);
}
```

## 二叉搜索树与双向链表
- 想像一个深度为2的树

```
void convert(TreeNode *root, TreeNode *&node) {
	if(root == nullptr) {
		return;
	}
	convert(root->left, node);

	root->left = node;
	if(node) {
		node->right = root;
	}
	node = root;

	convert(root->right, node);
}

TreeNode* convert(TreeNode *root) {
	if(root == nullptr) {
		return nullptr;
	}
	TreeNode *node = nullptr;
	convert(root, node);

	TreeNode *res = root;
	while(root->left) {
		res = res->left;
	}
	return res;
}
```

## 二叉树的深度

```
int TreeDepth(TreeNode *root) {
	if(root == nullptr) {
		return 0;
	}

	if(root->left == nullptr && root->right == nullptr) {
		return 1;
	}

	int leftDepth = TreeDepth(root->left) + 1;
	int rightDepth = TreeDepth(root->right) + 1;

	return leftDepth > rightDepth ? leftDepth : rightDepth;
}
```

## 二叉树的中序下一个结点

```
TreeNode* getNext(TreeNode *pNode) {
	if(pNode == nullptr) {
		return nullptr;
	}

	TreeNode *pNext = nullptr;
	if(pNode->right != nullptr) {
		TreeNode *node = pNode->right;
		while(node->left) {
			node = node->left;
		}
		pNext = node;
	} else if (pNode->par != nullptr) {
		TreeNode *cur = pNode;
		TreeNode *parent = pNode->par;
		while(parent != nullptr && cur == parent->right) {
			cur = parent;
			parent = parent->par;
		}
		pNext = parent;
	}
	return pNext;
}
```

## 将二叉树打印成多行
- 使用两个变量存放当前行以及下一行
```
std::vector<std::vector<int> > Print(TreeNode* pRoot) {
	std::vector<std::vetor<int> > res;
	std::vector<int> tmp;
	if(pRoot == nullptr) {
		return res;
	}

	int thisNum = 1;
	int nextNum = 0;
	std::queue<TreeNode*> q;
	q.push(pRoot);

	while(!q.empty()) {
		TreeNode *node = q.front();
		q.pop();
		tmp.push_back(node->val);

		if(node->left) {
			q.push(node->left);
			++nextNum;
		}

		if(node->right) {
			q.push(node->right);
			++nextNum;
		}

		if(--thisNum == 0) {
			thisNum = nextNum;
			nextNum = 0;
			res.push_back(tmp);
			tmp.clear();
		}
	}

	return res;
}
```

## 按之字形打印二叉树
- 使用两个栈

```
std::vector<std::vector<int> > Print(TreeNode *root) {
	std::vector<std::vector<int> > res;
	if(root == nullptr) {
		return res;
	}

	std::stack<TreeNode*> leves[2];
	std::vector<int> tmp;
	int cur = 0, next = 1;

	leves[cur].push(root);
	while(!level[cur].empty() || !level[next].empty()) {
		TreeNode *node = level[cur].top();
		level[cur].pop();
		tmp.push_back(node->val);

		if(cur == 0) {
			if(node->left) {
				level[next].push(node->left);
			}
			if(node->right) {
				level[next].push(node->right);
			}
		} else {
			if(node->left) {
				level[next].push(node->right);
			}
			if(node->left) {
				level[next].push(node->left);
			}
		}

		if(level[cur].empty()) {
			res.push_back(tmp);
			tmp.clear();
			next = 1 - next;
			cur = 1 - cur;
		}
	}

	retrun res;
}
```


## 矩阵中的路径
- 回朔法

```
bool hasPath(char *matrix, int rows, int cols, int row, int col, char *str, int& pathLength, bool *visited) {
	if(str[pathLength] == '\0') {
		retur true;
	}

	bool hasPath = false;
	if(row >= 0 && row < rows && col >= 0 && col < cols\
			&& matrix[row*cols + col] == str[pathLength]\
			&& !visited[row*cols + col]) {
		++pathLength;
	}

	visited[row*cols + col] = true;

	hasPath = hasPath(matrix, rows, cols, row, col-1, str, pathLength, visited)
			|| hasPath(matrix, rows, cols, row, col+1, str, pathLength, visited)
			|| hasPath(matrix, rows, cols, row+1, col, str, pathLength, visited)
			|| hasPath(matrix, rows, cols, row-1, col, str, pathLength, visited);

	if(!hasPath) {
		--pathLength;
		visited[row*cols + col] = false;
	}
}

bool hasPath(char *matrix, int rows, int cols, char *str) {
	if(matrix == nullptr || rows < 1 || cols < 1 || str == nullptr) {
		return false;
	}

	bool visited = new bool[rows * cols];
	memset(visited, 0, rows * cols);

	int pathLength = 0;
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(hasPath(matrix, rows, cols, i, j, str, pathLength, visited)) {
				return true;
			}
		}
	}

	delete[] visited;
	return false;
}
```
