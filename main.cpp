#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
	T element;
	Node<T>* next;

	Node(T e = T(), Node<T>* n = nullptr)
		: element(e), next(n) {
	}
};

template<typename T>
class List {
	Node<T>* head;

public:
	List() : head(nullptr) {}

	Node<T>* list_head() const {
		return head;
	}

	bool empty() const {
		return head == nullptr;
	}

	void push_front(T value) {
		head = new Node<T>(value, head);
	}

	void push_end(T value) {
		if (empty()) {
			push_front(value);
			return;
		}
		Node<T>* ptr = head;
		for (; ptr->next != nullptr; ptr = ptr->next) {
		}

		ptr->next = new Node<T>(value, nullptr);
	}

	int size() const {
		int count = 0;
		for (Node<T>* ptr = head; ptr; ptr = ptr->next) {
			count++;
		}
		return count;
	}

	void erase(T n) {
		if (empty()) {
			return;
		}
		while (list_head() && list_head()->element == n) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		for (Node<T>* ptr = list_head(); ptr && ptr->next;) {
			if (ptr->next->element == n) {
				Node<T>* temp = ptr->next;
				ptr->next = temp->next;
				delete temp;
				temp = nullptr;
			}
			else {
				ptr = ptr->next;
			}
		}
	}

	~List() {
		while (head) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
};

template<typename T>
class Tree {
	T value;
	Tree<T>* parent;
	List<Tree<T>*> children;
public:
	Tree(T n = T(), Tree<T>* p = nullptr)
		: value(n), parent(p) {
		if(p != nullptr) p->attach(this);
	}

	T retrieve() const {
		return value;
	}

	Tree<T>* retrieveParent() const {
		return parent;
	}

	int degree() const {
		return children.size();
	}

	bool is_root() const {
		return parent == nullptr;
	}

	bool is_leaf() const {
		return children.size() == 0;
	}

	Tree<T>* child(int n) {
		if (n < 0 || n >= degree()) {
			return nullptr;
		}

		Node<Tree<T>*>* ptr = children.list_head();
		for (int i = 0; i < n; i++)
			ptr = ptr->next;

		return ptr->element;
	}

	int size() {
		int count = 1;
		for (Node<Tree<T>*>* ptr = children.list_head(); ptr; ptr = ptr->next) {
			count += ptr->element->size();
		}
		return count;
	}

	int height() {
		int count = 0;
		for (Node<Tree<T>*>* ptr = children.list_head(); ptr; ptr = ptr->next) {
			count = std::max(count, 1 + ptr->element->height());
		}
		return count;
	}

	void attach(Tree<T>* tree) {
		if (!(tree->is_root())) {
			tree->detach();
		}
		tree->parent = this;
		children.push_end(tree);
	}

	void detach() {
		if (is_root()) {
			return;
		}
		parent->children.erase(this);
		parent = nullptr;
	}

	~Tree() {
		Node<Tree<T>*>* ptr = children.list_head();
		while (ptr) {
			delete ptr->element;
			ptr = ptr->next;
		}
	}
};

int main() {
	Tree<int>* root = new Tree<int>(10);
	Tree<int>* c3 = new Tree<int>(40, root);

	Tree<int>* c1 = new Tree<int>(20);
	Tree<int>* c2 = new Tree<int>(30);

	root->attach(c1);
	root->attach(c2);

	cout << root->child(0)->retrieve() << endl;
	cout << root->child(1)->retrieve() << endl;
	cout << root->child(2)->retrieve() << endl;
}
