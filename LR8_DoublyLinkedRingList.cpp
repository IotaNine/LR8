#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>

template <typename T>
struct element
{
    element* next;
    element* prev;
    T data;
};

template <typename T>
struct List
{
    element<T>* first;
    unsigned int size;
};

template <typename T>
void Constructor(List<T>& list)
{
    list.first = nullptr;
    list.size = 0;
    std::cout << "List is created" << std::endl;
}

template <typename T>
void Destructor(List<T>& list)
{
    if (list.size == 0)
    {
        std::cout << "List is empty" << std::endl;
    }
    else
    {
        while (list.size != 1)
        {
            list.first = list.first->next;
            delete list.first->prev;
            list.size--;
        }
        delete list.first;
        list.size--;
        std::cout << "List is destroyed" << std::endl;
    }
}

template <typename T>
unsigned int Size(List<T>& list)
{
    return list.size;
}

template <typename T>
void PushFront(List<T>& list, T data)
{
    element<T>* new_element = new element<T>;
    if (list.size == 0)
    {
        list.first = new_element;
        list.first->next = new_element;
        list.first->prev = new_element;
    }
    else
    {
        new_element->next = list.first;
        new_element->prev = list.first->prev;
        list.first->prev->next = new_element;
        list.first->prev = new_element;
        list.first = new_element;
    }
    new_element->data = data;
    list.size++;
}

template <typename T>
void PushBack(List<T>& list, T data)
{
    element<T>* new_element = new element<T>;
    if (list.size == 0)
    {
        list.first = new_element;
        list.first->next = new_element;
        list.first->prev = new_element;
    }
    else
    {
        new_element->next = list.first;
        new_element->prev = list.first->prev;
        list.first->prev->next = new_element;
        list.first->prev = new_element;
    }
    new_element->data = data;
    list.size++;
}

template <typename T>
void Push(List<T>& list, T data, unsigned int index)  //Добавление элемента по индексу
{
    if (index == 0 or index > list.size)
    {
        std::cout << "Index must belong to [1, " << list.size << "]" << std::endl;
    }
    else
    {
        element<T>* new_element = new element<T>;
        new_element->next = list.first;
        for (unsigned int i = 1; i < index; i++) 
        {
            new_element->next = new_element->next->next;
        }
        new_element->prev = new_element->next->prev;
        new_element->prev->next = new_element;
        new_element->next->prev = new_element;
        new_element->data = data;
        list.size++;
    }
}

template <typename T>
void Push(List<T>& list, T data, element<T>* spot)  //Добаление элемента по указателю
{
    element<T>* new_element = new element<T>;
    new_element->next = spot->next;
    new_element->prev = spot;
    spot->next->prev = new_element;
    spot->next = new_element;
    new_element->data = spot->data;
    list.size++;
}

template <typename T>
T PopFront(List<T>& list)
{
    if (list.size != 0)
    {
        T data = list.first->data;
        element<T>* buff = list.first;
        list.first->prev->next = list.first->next;
        list.first->next->prev = list.first->prev;
        list.first = list.first->next;
        delete buff;
        list.size--;
        return data;
    }
}

template <typename T>
T PopBack(List<T>& list)
{
    if (list.size != 0)
    {
        T data = list.first->prev->data;
        element<T>* buff = list.first->prev;
        list.first->prev = list.first->prev->prev;
        list.first->prev->next = list.first;
        delete buff;
        list.size--;
        return data;
    }
}

template <typename T>
T Pop(List<T>& list, unsigned int index)  //Извлечение элемента по индексу
{
    if (index == 0 or index > list.size)
    {
        std::cout << "Index must belong to [1, " << list.size << "]" << std::endl;
    }
    else
    {
        element<T>* buff = list.first;
        for (unsigned int i = 1; i < index; i++)
        {
            buff = buff->next;
        }
        buff->prev->next = buff->next;
        buff->next->prev = buff->prev;
        T data = buff->data;
        delete buff;
        list.size--;
        return data;
    }
}

template <typename T>
T Pop(List<T>& list, element<T>* spot)  //Извлечение элемента по указателю
{
    T data = spot->data;
    element<T>* buff = spot;
    spot->prev->next = spot->next;
    spot->next->prev = spot->prev;
    delete buff;
    list.size--;
    return data;
}

template <typename T>
T GetData(List<T>& list, unsigned int index)
{
    if (index == 0 or index > list.size)
    {
        std::cout << "Index must belong to [1, " << list.size << "]" << std::endl;
    }
    else
    {
        element<T>* buff = list.first;
        for (unsigned int i = 1; i < index; i++)
        {
            buff = buff->next;
        }
        T data = buff->data;
        return data;
    }
}

template <typename T>
unsigned int GetIndex(List<T>& list, T data)
{
    element<T>* buff = list.first;
    unsigned int index = 1;
    while (buff->data != data)
    {
        buff = buff->next;
        index++;
        if (index > list.size)
        {
            index = 0;
            break;
        }
    }
    return index;
}

template <typename T>
void Print(List<T>& list)
{
    element<T>* buff = list.first;
    std::cout << "<< List info >>" << std::endl;
    if (list.size != 0)
    {
        for (unsigned int i = 0; i < list.size; i++)
        {
            std::cout << std::right << std::setw(log10(list.size) + 1);
            std::cout << i + 1 << ". " << buff->data << std::endl;
            buff = buff->next;
        }
    }
    else
    {
        std::cout << "List is empty" << std::endl;
    }
    std::cout << "<< End >>" << std::endl << std::endl;
}

int main()
{
    srand(time(NULL));
    unsigned int N = 0;
    List<int> A, B;
    Constructor(A);
    Constructor(B);
    std::cout << "Quantity of elements: ";
    std::cin >> N;
    for (unsigned int i = 0; i < N; i++)
    {
        PushBack(A, rand() % 21);
    }
    Print(A);
    PushFront(A, 111111);
    PushBack(A, 999999);
    Print(A);
    Push(A, 101010, 3);
    Print(A);
    std::cout << "Index of 3: " << GetIndex(A, 3) << std::endl;
    std::cout << "First element of list A: " << PopFront(A) << std::endl;
    std::cout << "First element of list B: " << PopFront(B) << std::endl;
    std::cout << "Last element of list A: " << PopBack(A) << std::endl;
    std::cout << "Last element of list B: " << PopBack(B) << std::endl;
    std::cout << "Fifth element of list A: " << GetData(A, 5) << std::endl;
    std::cout << "Fifth element of list A: " << Pop(A, 5) << std::endl;
    Print(A);
    Destructor(A);
    Destructor(B);
}