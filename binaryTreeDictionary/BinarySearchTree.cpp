#include "bst.h"



// Creates an empty binary tree
BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
}

// Creates a binary tree with an initial value to store
BinarySearchTree::BinarySearchTree(string word)
{
	insert(word);
}

//Copy helper function
Node* copyHelper(Node *root)
{
	Node *newRoot;
	if(root != nullptr)
	{
		newRoot = new Node;
		newRoot->data=root->data;
		newRoot->left=copyHelper(root->left);
		newRoot->right=copyHelper(root->right);
	}
	else return nullptr;
	return newRoot;
}
// Creates a binary tree by copying an existing tree
BinarySearchTree::BinarySearchTree(const BinarySearchTree &rhs)
{
	root = copyHelper(rhs.root);
}

// Destroys (cleans up) the tree
BinarySearchTree::~BinarySearchTree()
{
	while(root != nullptr)
	{
		string str = root->data;
		remove(str);
	}
}

Node* insertHelper(Node *t, string word)
{
	if(t == nullptr)
	{
		t = new Node;
		t->data = word;
		t->left = nullptr;
		t->right = nullptr;
	}
	else if(word < t->data)
	{
		t->left = insertHelper(t->left, word);
	}
	else if(word > t->data)
	{
		t->right = insertHelper(t->right, word);
	}
	return t;
}

// Adds a word to the tree
void BinarySearchTree::insert(string word)
{	
	root = insertHelper(root, word);
}

//finding minimum value
Node* findMin(Node* t)
{
	Node* current;
	current = t;
	
	while(current->left != nullptr)
		current = current->left;
	return current;
}

//remove helper function
Node* removeHelper(Node* t, string word)
{
	if(t == nullptr) 
		return nullptr;
	if(word < t->data)
	{
		t->left = removeHelper(t->left, word);
	}
	else if(word > t->data)
	{
		t->right = removeHelper(t->right, word);
	}
	else
	{
		if(t->left == nullptr)
		{
			Node* temp;
			temp = t->right;
			delete t;
			return temp;
		}
		else if(t->right == nullptr)
		{
			Node* temp;
			temp = t->left;
			delete t;
			return temp;
		}
		else if(t->left && t->right)
		{
			Node* temp;
			temp = findMin(t->right);
			t->data = temp->data;
			t->right = removeHelper(t->right, temp->data);
		}
	}
	return t;
}

// Removes a word from the tree
void BinarySearchTree::remove(string word)
{
	root = removeHelper(root, word);
}

bool existsHelper(Node *r, string word)
{
	if(r == nullptr)
	{
		return false;
	}
	if(r->data == word)
	{
		return true;
	}

	bool exists1 = existsHelper(r->left, word);
	bool exists2 = existsHelper(r->right, word);

	return exists1 || exists2;
}
// Checks if a word is in the tree
bool BinarySearchTree::exists(string word) const
{
  	return existsHelper(root,word);
}

//inorder helper function
std::string inorderHelper(Node *root)
{
	if(root == nullptr)
	{	
		return "";
	}
	else
	{
		return inorderHelper(root->left)
		+ root->data + " "
		+ inorderHelper(root->right);
	}
}

// Prints the tree to standard out in numerical order
std::string BinarySearchTree::inorder() const
{
	string str = inorderHelper(root);
	int len = str.length();
	
	if(len > 1 && str[len -1] == ' ')
	{
		str.pop_back();
	}
    return str;
}

//preorder helper function
std::string preorderHelper(Node *root)
{
	if(root == nullptr)
	{	
		return "";
	}
	else
	{
		return root->data + " "
		+ preorderHelper(root->left)
		+ preorderHelper(root->right);
	}
}

// Prints the tree in pre-order
std::string BinarySearchTree::preorder() const
{
    string str = preorderHelper(root);
	int len = str.length();
	
	if(len > 1 && str[len -1] == ' ')
	{
		str.pop_back();
	}
    return str;
}

//postorder helper function
std::string postorderHelper(Node *root)
{
	if(root == nullptr)
	{	
		return "";
	}
	else
	{
		return postorderHelper(root->left)
		+ postorderHelper(root->right)
		+ root->data + " ";
	}
}

// Prints the tree in post-order
std::string BinarySearchTree::postorder() const
{
    string str = postorderHelper(root);
	int len = str.length();
	
	if(len > 1 && str[len -1] == ' ')
	{
		str.pop_back();
	}
    return str;
}


// Checks if two trees are equal
bool BinarySearchTree::operator==(const BinarySearchTree &other) const
{
    return true;
}

// Checks if two trees are not equal
bool BinarySearchTree::operator!=(const BinarySearchTree &other) const
{
    return true;
}


// Reads in words from an input stream into the tree
std::istream& operator>>(std::istream &in, BinarySearchTree &tree)
{
	std::string word;
	while(in)
	{
		in >> word;
		tree.insert(word);
	}
    return in;
}

// Writes the words, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const BinarySearchTree &tree)
{
	out << tree.inorder();
    return out;
}
