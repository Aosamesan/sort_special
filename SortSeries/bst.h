#include<iostream>
#include<iomanip>

#ifndef __BST__
#define __BST__
using namespace std;

template<typename T>
class BSTNode{
public:
	BSTNode(const T& data = T(),
		BSTNode<T>* leftNode = NULL,
		BSTNode<T>* rightNode = NULL){
		this->data = data;
		this->leftNode = leftNode;
		this->rightNode = rightNode;
	}

	T& GetData(){
		return data;
	}

	const T& GetData() const{
		return data;
	}

	BSTNode<T>*& GetLeft(){
		return leftNode;
	}

	const BSTNode<T>*& GetLeft() const{
		return leftNode;
	}

	BSTNode<T>*& GetRight(){
		return rightNode;
	}

	const BSTNode<T>*& GetRight() const{
		return rightNode;
	}

	void SetData(const T& data){
		this->data = data;
	}

	void SetLeft(BSTNode<T>*& leftNode){
		this->leftNode = leftNode;
	}

	void SetRight(BSTNode<T>*& rightNode){
		this->rightNode = rightNode;
	}

	bool IsLeaf() const{
		return (leftNode == NULL && rightNode == NULL);
	}

private:
	T data;
	BSTNode<T>* leftNode;
	BSTNode<T>* rightNode;
};

template<typename T>
class BSTree{
public:
	BSTree(){
		rootNode = NULL;
	}

	BSTree(BSTree<T>& tree){
		rootNode = TreeCopy(tree.rootNode);
	}

	~BSTree(){
		TreeClear(rootNode);
	}

	size_t Size(){
		return TreeCount(rootNode);
	}

	BSTree<T>& operator=(const BSTree<T>& addend){
		if (this == &addend)
			return *this;
		TreeClear(rootNode);
		rootNode = TreeCopy(addend.rootNode);
	}

	void Insert(const T& data){
		BSTNode<T>* newNode = new BSTNode<T>(data);

		if (rootNode == NULL){
			rootNode = newNode;
		}
		else {
			TreeInsert(rootNode, newNode);
		}
	}

	void RemoveOne(T& data){
		if (rootNode == NULL)
			return;
		TreeRemove(rootNode, data);
	}

	void operator+=(BSTree<T>& addend){
		if (this == &addend){
			BSTNode<T>* copyed = TreeCopy(rootNode);
			TreeInsertAll(copyed);
			delete copyed;
		}
		else {
			TreeInsertAll(addend.rootNode);
		}
	}

	void Print(){
		TreePrintDepth(rootNode, 0);
	}

	template<typename Process>
	void BSTSort(Process push){
		BSTSortRecursive(rootNode, push);
	}

private:
	BSTNode<T>* rootNode;

	size_t TreeCount(const BSTNode<T>*& root){
		if (root == NULL)
			return 0;
		return TreeCount(root->GetLeft()) +
			TreeCount(root->GetRight()) + 1;
	}

	void TreeClear(BSTNode<T>*& root){
		if (root == NULL)
			return;
		TreeClear(root->GetLeft());
		TreeClear(root->GetRight());
		delete root;
		root = NULL;
	}

	BSTNode<T>* TreeCopy(BSTNode<T>* root){
		BSTNode<T>* leftSubtree;
		BSTNode<T>* rightSubtree;

		if (root == NULL)
			return NULL;
		leftSubtree = TreeCopy(root->GetLeft());
		rightSubtree = TreeCopy(root->GetRight());
		return new BSTNode<T>(root->GetData(), leftSubtree, rightSubtree);
	}

	void TreeInsert(BSTNode<T>*& root, BSTNode<T>*& newNode){
		if (root->GetData() >= newNode->GetData()){
			if (root->GetLeft() == NULL){
				root->SetLeft(newNode);
			}
			else {
				TreeInsert(root->GetLeft(), newNode);
			}
		}
		else {
			if (root->GetRight() == NULL){
				root->SetRight(newNode);
			}
			else {
				TreeInsert(root->GetRight(), newNode);
			}
		}
	}

	void TreeRemove(BSTNode<T>*& root, T& item){
		if (root == NULL)
			return;
		if (root->GetData() > item)
			TreeRemove(root->GetLeft(), item);
		else if (root->GetData() < item)
			TreeRemove(root->GetRight(), item);
		else{
			if (root->GetLeft() == NULL){
				BSTNode<T>* oldroot = root;
				if (root = oldroot->GetRight()){
					root->SetLeft(oldroot->GetLeft());
				}
				delete oldroot;
			}
			else {
				T maxData = root->GetData();
				TreeMaxRemove(root->GetLeft(), maxData);
				root->SetData(maxData);
			}
		}
	}

	void TreeMaxRemove(BSTNode<T>*& root, T& maxItem){
		if (root->GetRight() == NULL){
			maxItem = root->GetData();
			BSTNode<T>* oldroot = root;
			root = oldroot->GetLeft();
			delete root;
		}
		else {
			maxItem = root->GetRight()->GetData();
			TreeMaxRemove(root->GetRight(), maxItem);
		}
	}

	void TreeInsertAll(BSTNode<T>*& root){
		if (root == NULL)
			return;
		Insert(root->GetData());
		TreeInsertAll(root->GetLeft());
		TreeInsertAll(root->GetRight());
	}

	void TreePrint(BSTNode<T>*& root){
		if (root != NULL){
			cout << root->GetData() << endl;
			TreePrint(root->GetLeft());
			TreePrint(root->GetRight());
		}
	}

	void TreePrintDepth(BSTNode<T>*& root, size_t depth){
		if (root != NULL){
			TreePrintDepth(root->GetRight(), depth + 1);
			cout << setw(4 * depth) << "" << root->GetData() << endl;
			TreePrintDepth(root->GetLeft(), depth + 1);
		}
	}
	
	template<typename Process>
	void BSTSortRecursive(BSTNode<T>*& root, Process push){
		if (root == NULL)
			return;
		BSTSortRecursive(root->GetLeft(), push);
		push(root->GetData());
		BSTSortRecursive(root->GetRight(), push);
		return;
	}
};
#endif
