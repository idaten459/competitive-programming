/*
leetcode用
*/

//*
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};//*/


template<typename T>
struct node_t {
	T val;
	node_t* left;
	node_t* right;
	node_t* parent;
	node_t(T x) : val(x), left(NULL), right(NULL), parent(NULL) {}
	node_t(T x, node_t* p) : val(x), left(NULL), right(NULL), parent(p) {}
};

void dfs(TreeNode* v1, node_t<int>* v2) {
	if (v1->left != NULL) {
		v2->left = new node_t<int>(v1->left->val, v2);
		dfs(v1->left, v2->left);
	}
	if (v1->right != NULL) {
		v2->right = new node_t<int>(v1->right->val, v2);
		dfs(v1->right, v2->right);
	}
}

node_t<int>* convertNode_t(TreeNode* root) {
	using node = node_t<int>;
	node* res = new node(root->val);
	dfs(root, res);
	return res;
}
