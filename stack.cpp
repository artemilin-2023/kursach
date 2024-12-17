using database::core::stack::stack;

namespace database {
namespace core {
namespace stack {

#pragma region node

	template<class T>
	node<T>::node(T data) {
		this->data = data;
		next = nullptr;
	}

	template<class T>
	node<T>::node(T data, node<T>* next) {
		this->data = data;
		this->next = next;
	}

#pragma endregion


#pragma region stack

	template<class T>
	stack<T>::stack() {
		peek = nullptr;
		tail = nullptr;
		_size = 0;
	}

	template<class T>
	stack<T>::~stack() {
		auto current = peek;
		while (current != nullptr) {
			auto next = current->next;
			delete current;
			current = next;
		}
	}

	template<class T>
	node<T>* stack<T>::begin() const { return peek; }

	template<class T>
	node<T>* stack<T>::end() const { return tail; }

	template<class T>
	bool stack<T>::empty() const { return peek == nullptr; }

	template<class T>
	int stack<T>::size() const { return _size; }

	template<class T>
	void stack<T>::clear() {
		auto current = peek;
		while (current != nullptr) {
			auto next = current->next;
			delete current;
			current = next;
		}

		peek = nullptr;
		tail = nullptr;
		_size = 0;
	}

	template<class T>
	void stack<T>::push(T data) {
		auto newNode = new node(data, peek);
		if (peek == nullptr) { // add first node
			peek = newNode;
			tail = newNode;
		}
		else {
			peek = newNode;
		}
	}

	template<class T>
	T stack<T>::top() { 
		if (peek == nullptr)
			throw std::runtime_error("stack is empty.");
		return peek->data; 
	}

	template<class T>
	T stack<T>::pop() {
		auto newPeek = peek->next;
		auto result = peek->data;

		delete peek;
		peek = newPeek;

		if (peek == nullptr)
			tail = nullptr;
		
		return result;
	}


#pragma endregion

}
}
}
