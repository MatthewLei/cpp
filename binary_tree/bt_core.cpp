#include <iostream>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

template <typename BinaryTreeType>
void print_inorder(BinaryTreeType* root) {
    if (root == NULL) {
	return;
    }
    print_inorder(root->left);
    std::cout << root->val << " ";
    print_inorder(root->right);
}

void insert_bt(TreeNode* root, int val) {
    if (root == NULL) {
	std::cout << "will not insert node into NULL root\n";
	return;
    }
    while (root != NULL) {
	if (val < root->val) {
	    if (root->left == NULL) {
		TreeNode* newNode = new TreeNode(val);
		root->left = newNode;
		break;
	    }
	    root = root->left;
	} else if (val > root->val) {
	    if (root->right == NULL) {
		TreeNode* newNode = new TreeNode(val);
		root->right = newNode;
		break;
	    }
	    root = root->right;
	} else {
	    std::cerr << "current implementation assumes unique numbers\n";
	    exit(0);
	}
    }
}


void flatten_inorder(TreeNode* root, std::vector<int>* vec) {
    if (root == NULL) {
	return;
    }
    flatten_inorder(root->left, vec);
    vec.push_back(root->val);
    flatten_inorder(root->right, vec);
}

int main() {
    TreeNode* root = new TreeNode(10);
    insert_bt(root, 5);
    insert_bt(root, 4);
    insert_bt(root, 7);
    insert_bt(root, 2);
    insert_bt(root, 9);
    insert_bt(root, 1);

    print_inorder<TreeNode>(root);
    std::cout << std::endl;

    std::vector<int> final;
    flatten_inorder(root, &final);

    for (auto x : final) {
	std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
