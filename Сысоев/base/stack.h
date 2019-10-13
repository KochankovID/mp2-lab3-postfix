#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
public:
	// Конструкторы ----------------------------------------------------------------------------------------
	TStack() :size_buf(increase), top_el(-1) { initialization_new_buffer(); }  // Конструктор по умолчанию
	TStack(const TStack& copy) :size_buf(copy.size_buf), top_el(copy.top_el) {  // Конструктор копирования
		initialization_new_buffer();
		for (int i = 0; i < copy.top_el+1; i++) {
			pMem[i] = copy.pMem[i];
		}
	}
	TStack(TStack&& copy) :size(copy.size), top_el(copy.top_el) {  // Мув-конструктор
		pMem = copy.pMem;
		copy.pMem = nullptr;
	}

	// Методы ----------------------------------------------------------------------------------------------
	void push(const T& element);  // Добавление элемента
	T pop();  // Получение верхнего элемента с удалением из стека
	T& top();  // Доступ к верхнему элементу стека
	bool isEmpty();  // Проверка на пустоту стека
	bool isFull();  // Проверка на заполненность стека
	int size() { return top_el + 1; };  // Возвращает кол-во элементов в стеке

	// Деструктор ------------------------------------------------------------------------------------------
	~TStack() {
		delete[] pMem;
	}
private:
	// Скрытые методы --------------------------------------------------------------------------------------
	void increase_buffer();  // Увеличение размера динамического массива без потери данных
	void initialization_new_buffer();  // Инициализация нового динамического массива размера size

	// Поля ------------------------------------------------------------------------------------------------
	const int increase = 10;  // Размер увеличения буфера стека
	int size_buf;  // Размер буфера стека
	int top_el;  // Индекс вехрнего элемента стека
	T* pMem;  // Указатель на буфер стека
};

#endif

template<class T>
inline void TStack<T>::push(const T& element)
{
	if (isFull()) {
		throw std::runtime_error("Стек переполнен! Невозможно добавить элемент!");
	}
	if (top_el >= size_buf - 1) {
		increase_buffer();
	}
	top_el++;
	pMem[top_el] = element;
}

template<class T>
inline T TStack<T>::pop()
{
	if (isEmpty()) {
		throw std::runtime_error("Стек пуст! Извлечение невозможно!");
	}
	return pMem[top_el--];
}

template<class T>
inline T& TStack<T>::top()
{
	if (isEmpty()) {
		throw std::runtime_error("Стек пуст! Получить доступ к верхнему элементу невозможно!");
	}
	return pMem[top_el];
}

template<class T>
inline bool TStack<T>::isEmpty()
{
	if (top_el < 0) {
		return true;
	}
	return false;
}

template<class T>
inline bool TStack<T>::isFull()
{
	if (top_el >= MaxStackSize - 1) {
		return true;
	}
	return false;
}

template<class T>
inline void TStack<T>::initialization_new_buffer()
{
	pMem = new T[size_buf]();
}

template<class T>
inline void TStack<T>::increase_buffer()
{
	T* arr_copy = new T[top_el];
	for (int i = 0; i < top_el; i++) {
		arr_copy[i] = pMem[i];
	}
	delete[] pMem;
	size_buf += increase;
	pMem = new T[size_buf];
	for (int i = 0; i < top_el; i++) {
		pMem[i] = arr_copy[i];
	}
	delete[] arr_copy;
}
