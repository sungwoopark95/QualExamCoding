#include <iostream>
#include "bst.h"

using namespace std;

void BST::Insert(int key) {
  Node* z = new Node(key);

  Node* x = this->root;
  Node* y = nullptr;

  while (x != nullptr) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  // found the location - insert z with parent y
  z->parent = y;

  if (y == nullptr) {
    root = z;
  }
  else if (z->key < y->key) {
    y->left = z;
  }
  else {
    y->right = z;
  }
}

void BST::transplant(Node* u, Node* v){
	if (u->parent == nullptr) {
		root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else{
		u->parent->right = v;
	}

	if (v != nullptr) {
		v->parent = u->parent;
	}
}

void BST::Delete(Node* z) {
  Node* y;

	if (z->left == nullptr) {
		transplant(z, z->right);
	}
  else if (z->right == nullptr) {
		transplant(z, z->left);
	}
  else {
		y = Minimum(z->right);
		if (y->parent != z) {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
	}
}

void BST::Preorder(Node* node) {
  if (node != nullptr) {
    cout << node->key << " ";
    Preorder(node->left);
    Preorder(node->right);
  } 
}

void BST::Inorder(Node* node) {
  if (node != nullptr) {
    Inorder(node->left);
    cout << node->key << " ";
    Inorder(node->right);
  } 
}

void BST::Postorder(Node* node) {
  if (node != nullptr) {
    Postorder(node->left);
    Postorder(node->right);
    cout << node->key << " ";
  } 
}

BST::Node* BST::Search(Node* node, int key) {
  if (node == nullptr || key == node->key) {
    return node;
  }

  if (key < node->key)
    return Search(node->left, key);
  else
    return Search(node->right, key);
}

BST::Node* BST::Maximum(Node* node) {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

BST::Node* BST::Minimum(Node* node) {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

BST::Node* BST::Successor(Node* x) {
  if (x->right != nullptr) {
    return Minimum(x->right);
  }

  Node* y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

BST::Node* BST::Predecessor(Node* x) {
  if (x->left != nullptr) {
    return Maximum(x->left);
  }

  Node* y = x->parent;
  while (y != nullptr && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

void BST::_print(Node* root, string indent, bool last) {
  // cout<< "_print() is called" <<endl;
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "`----";
      indent += "     ";
    } else {
      cout << "|----";
      indent += "|    ";
    }

    cout << root->key << endl;

    _print(root->left, indent, false);
    _print(root->right, indent, true);
  }
}

void BST::Print() {
  // cout<< "Print() is called" <<endl;
  if (GetRoot() != nullptr)
    _print(GetRoot(), " ", true);
    
}
