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

	T pop_front() {
		T val = 0;
		if (empty()) {
			throw std::runtime_error("Empty");
		}
		else {
			Node<T>* temp = head;
			head = head->next;
			val = temp->element;
			delete temp;
			temp = nullptr;
		}
		return val;
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

	T pop_end() {
		T val = 0;
		if (empty() || (head != nullptr && head->next == nullptr)) {
			pop_front();
		}
		else {
			for (Node<T>* ptr = head; ptr != nullptr; ptr = ptr->next) {
				if (ptr->next->next == nullptr) {
					val = ptr->next->element;
					delete ptr->next;
					ptr->next = nullptr;
					break;
				}
			}
		}
		return val;
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
		while (head && head->element == n) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		for (Node<T>* ptr = head; ptr && ptr->next;) {
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
class Queue {
	List<T> l;
public:
	bool empty() const {
		return l.empty();
	}
	T top() const {
		if (!empty()) {
			l.list_head->retrieve();
		}
		else {
			throw std::runtime_error("Empty");
		}
	}
	void push(T n) {
		l.push_end(n);
	}
	T pop() {
		return l.pop_front();
	}
};

template<typename T>
class Stack {
	List<T> l;
public:
	bool empty() {
		return l.empty();
	}
	T top() {
		return l.end();
	}
	void push(T n) {
		l.push_end(n);
	}
	T pop() {
		return l.pop_end();
	}
	void display() {
		l.display();
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

	void bft() {
		Queue<Tree<T>*> q;
		q.push(this);
		while (!q.empty()) {
			Tree<T>* p = q.pop();
			cout << p->retrieve();
			for (Node<Tree<T>*>* ptr = p->children.list_head(); ptr != nullptr; ptr = ptr->next) {
				q.push(ptr->element);
			}
		}
	}

	void dft() {
		cout << retrieve();
		for (Node<Tree<T>*>* ptr = children.list_head(); ptr != nullptr; ptr = ptr->next) {
			ptr->element->dft();
		}
	}

	void dft2() {
		for (Node<Tree<T>*>* ptr = children.list_head(); ptr != nullptr; ptr = ptr->next) {
			ptr->element->dft2();
		}
		cout << retrieve();
	}

	void dft3() {
		Stack<Tree<T>*> s;
		s.push(this);
		while (!s.empty()) {
			Tree<T>* p = s.pop();
			cout << p->retrieve();
			for (Node<Tree<T>*>* ptr = p->children.list_head(); ptr != nullptr; ptr = ptr->next) {
				s.push(ptr->element);
			}
		}
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
	Tree<string>* a = new Tree<string>("A");
	Tree<string>* b = new Tree<string>("B", a);
	Tree<string>* d = new Tree<string>("D", b);
	Tree<string>* u = new Tree<string>("U", a);
	Tree<string>* l = new Tree<string>("L", u);
	Tree<string>* w = new Tree<string>("W", a);
	Tree<string>* a2 = new Tree<string>("A", w);
	Tree<string>* h = new Tree<string>("H", a2);
	Tree<string>* a3 = new Tree<string>("A", w);
	Tree<string>* b2 = new Tree<string>("B", a3);
	a->dft();
	cout << endl;
	a->dft2();
	cout << endl;
	a->bft();
	cout << endl;
}
