#include "../Queue/Queue.h"
#include <iostream>
using namespace std;

template <typename T>
Node<T>::Node(T data) : data(data), left(NULL), right(NULL) {}


template <typename T>
AVLTree<T>::AVLTree() : root(NULL) {}


template <typename T>
AVLTree<T>::AVLTree(T &data) {
	root = new Node<T>(data);
}


template <typename T>
AVLTree<T>::~AVLTree() {
	destroy_recursive(root);
}

template <typename T>
void AVLTree<T>::destroy_recursive(Node<T> *node) {
	if (node) {
		destroy_recursive(node->left);
		destroy_recursive(node->right);
		delete node;
	}
}


template <typename T>
void AVLTree<T>::insert(const T &data) {
	root = insert_node(root, data);
}


template <typename T>
Node<T>* AVLTree<T>::insert_node(Node<T> *curr, const T &data) {
	if (!curr)
		return new Node<T>(data);

	if (data < curr->data)
		curr->left = insert_node(curr->left, data);
	else if (data > curr->data)
		curr->right = insert_node(curr->right, data);

	return curr;
}

template <typename T>
void AVLTree<T>::remove(const T &data) {
	root = remove_node(root, data);
}


template <typename T>
Node<T>* AVLTree<T>::remove_node(Node<T> *curr, const T &data) {
	if (!curr)
		return NULL;
	else if (curr->data == data) {
		if (!curr->left)
			return curr->right;
		else if (!curr->right) {
			return curr->left;
		} else {
			Node<T> *min = get_and_disconnect_min(curr->right);
			min->left = curr->left;

			if (min != curr->right)
				min->right = curr->right;

			return min;
		}
	}

	if (data < curr->data)
		curr->left = remove_node(curr->left, data);
	else if (data > curr->data)
		curr->right = remove_node(curr->right, data);

	return curr;
}


template <typename T>
Node<T>* AVLTree<T>::get_and_disconnect_min(Node<T>* node) {
	
	Node<T> *parent = NULL;

	while(node && node->left) {
		parent = node;
		node = node->left;
	}

	if (parent)
		parent->left = node->right;

	return node;
}


template <typename T>
int AVLTree<T>::get_height(Node<T> *curr) {
	if (!curr)
		return 0;

	return max(1 + get_height(curr->left), 1 + get_height(curr->right));
}


template <typename T>
void AVLTree<T>::print_tree() {
    int height = get_height(root); 
    
    for (int i = 0; i < height; i++) { 
        printLevel(root, i); 
        cout << endl;
    }
}
  
template <typename T>
void AVLTree<T>::printLevel(Node<T>* curr, int level) 
{ 
    if (!curr)
        cout << " * "; 
    else if (level == 0) 
        cout <<  " " << curr->data << " "; 
    else if (level > 0) 
    {
        printLevel(curr->left, level - 1); 
        printLevel(curr->right, level - 1); 
    }
} 


template <typename T>
void AVLTree<T>::bfs() {
	Queue<Node<T>*> to_visit;
	Node<T> *curr;

	cout << "BFS: ";
	to_visit.push(root);

	while(!to_visit.isEmpty()) {
		curr = to_visit.pop();
		cout << curr->data << " ";
		
		if (curr->left)
			to_visit.push(curr->left);
		if (curr->right)
			to_visit.push(curr->right);
	}

	cout << endl;
}


template <typename T>
void AVLTree<T>::dfs_inorder() {
	cout << "Inorder: ";
	inorder(root);
	cout << endl;
}

template <typename T>
void AVLTree<T>::inorder(Node<T>* curr) {

	if (!curr)
		return;
	
	inorder(curr->left);

	cout << curr->data << " ";

	inorder(curr->right);

}


template <typename T>
void AVLTree<T>::dfs_preorder() {
	cout << "Preorder: ";
	preorder(root);
	cout << endl;
}


template <typename T>
void AVLTree<T>::preorder(Node<T>* curr) {

	if (!curr)
		return;

	cout << curr->data << " ";

	preorder(curr->left);
	preorder(curr->right);

}


template <typename T>
void AVLTree<T>::dfs_postorder() {
	cout << "Postorder: ";
	postorder(root);
	cout << endl;
}


template <typename T>
void AVLTree<T>::postorder(Node<T>* curr) {

	if (!curr)
		return;

	preorder(curr->left);
	preorder(curr->right);

	cout << curr->data << " ";
}


template <typename T>
bool AVLTree<T>::find(const T& data) {
	Node<T> *curr = root;
	while(curr) {
		if (curr->data == data)
			return true;
		if (curr->data > data) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}

	return false;
}