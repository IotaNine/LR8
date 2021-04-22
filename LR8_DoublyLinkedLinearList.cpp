#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

struct Region
{
    std::string name;
    unsigned int population;
    std::string GetName() { return name; }
    unsigned int GetPopulation() { return population; }
    bool operator==(Region& Right)
    {
        if (this->population == Right.population)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

std::ostream& operator<<(std::ostream& stream, Region& region)
{
    std::cout << "Name: " << region.name << std::endl;
    std::cout << "Population: " << region.population << std::endl;
    return stream;
}

template <typename T, unsigned int space>
struct List
{
    T* data_point[space];
    unsigned int size;
};

template <typename T, unsigned int space>
void Constructor(List<T, space>& list)
{
    for (unsigned int i = 0; i < space; i++)
    {
        list.data_point[i] = nullptr;
    }
    list.size = 0;
    std::cout << "The list id created" << std::endl;
}

template <typename T, unsigned int space>
void Destructor(List<T, space>& list)
{
    for (unsigned int i = 0; i < space; i++)
    {
        delete list.data_point[i];
        list.data_point[i] = nullptr;
    }
    list.size = 0;
    std::cout << "The list id destroyed" << std::endl;
}

template <typename T, unsigned int space>
unsigned int Size(List<T, space>& list)
{
    return list.size;
}

template <typename T, unsigned int space>
void PushBack(List<T, space>& list, T data)
{
    if (list.size < space)
    {
        T* new_data_point = new T{ data };
        list.data_point[list.size] = new_data_point;
        list.size++;
    }
    else
    {
        std::cout << "No space left" << std::endl;
    }
}

template <typename T, unsigned int space>
void Push(List<T, space>& list, T data, unsigned int index)  //Добавление элемента по индексу
{
    if (list.size < space)
    {
        if (index <= list.size)
        {
            T* new_data_point = new T{ data };
            for (unsigned int i = list.size; i != index; i--)
            {
                std::swap(list.data_point[i], list.data_point[i - 1]);
            }
            list.data_point[index] = new_data_point;
            list.size++;
        }
        else
        {
            std::cout << "Index must belong to [" << 0 << ", " << list.size - 1 << "]";
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "No space left" << std::endl;
    }
}

template <typename T, unsigned int space>
T PopFront(List<T, space>& list)
{
    if (list.size > 0)
    {
        T data = *list.data_point[0];
        delete list.data_point[0];
        for (unsigned int i = 0; i < list.size; i++)
        {
            list.data_point[i] = list.data_point[i + 1];
        }
        list.data_point[list.size - 1] = nullptr;
        list.size--;
        return data;
    }
    else
    {
        std::cout << "The list is empty" << std::endl;
    }
}

template <typename T, unsigned int space>
T PopBack(List<T, space>& list)
{
    if(list.size > 0)
    {
    T data = *list.data_point[list.size - 1];
    delete list.data_point[list.size - 1];
    list.data_point[list.size - 1] = nullptr;
    list.size--;
    return data;
    }
    else
    {
        std::cout << "The list is empty" << std::endl;
    }
}

template <typename T, unsigned int space>
T Pop(List<T, space>& list, unsigned int index)
{
    if (list.size > 0)
    {
        T data = *list.data_point[index - 1];
        delete list.data_point[index - 1];
        for (unsigned int i = index - 1; i < list.size; i++)
        {
            list.data_point[i] = list.data_point[i + 1];
        }
        list.size--;
        return data;
    }
    else
    {
        std::cout << "The list is empty" << std::endl;
    }
}

template <typename T, unsigned int space>
T GetData(List<T, space>& list, unsigned int index)
{
    if (list.size > 0)
    {
        if (index - 1 < list.size)
        {
            return *list.data_point[index - 1];
        }
        else
        {
            std::cout << "Index must belong to [" << 0 << ", " << list.size - 1 << "]";
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "The list is empty" << std::endl;
    }
}

template <typename T, unsigned int space>
int GetIndex(List<T, space>& list, T data)
{
    for (unsigned int i = 0; i < list.size; i++)
    {
        if (*list.data_point[i] == data)
        {
            return i;
        }
    }
    return -1;
}

template <typename T, unsigned int space>
void Print(List<T, space>& list)
{
    std::cout << "<<List info>>" << std::endl;
    if (list.size > 0)
    {
        for (unsigned int i = 0; i < list.size; i++)
        {
            std::cout << std::right << std::setw(log10(list.size) + 1);
            std::cout << i << ". " << *list.data_point[i] << std::endl;
        }
    }
    else
    {
        std::cout << "The list is empty" << std::endl;
    }
    std::cout << "<<End>>" << std::endl;
}

int main()
{
    srand(time(NULL));
    unsigned int N = 0;
    List<int, 20> A;
    Constructor(A);
    std::cout << "Quantity of elements(up to 20): ";
    std::cin >> N;
    for (unsigned int i = 0; i < N; i++)
    {
        PushBack(A, rand() % 21);
    }
    Print(A);
    PushBack(A, 999999);
    Print(A);
    Push(A, 101010, 3);
    Print(A);
    std::cout << "Index of 3: " << GetIndex(A, 3) << std::endl;
    std::cout << "First element of list A: " << PopFront(A) << std::endl;
    std::cout << "Last element of list A: " << PopBack(A) << std::endl;
    std::cout << "Fifth element of list A: " << GetData(A, 5) << std::endl;
    std::cout << "Fifth element of list A: " << Pop(A, 5) << std::endl;
    Print(A);
    Destructor(A);

    Region First, Second, Third;
    First.name = "Osaka";
    First.population = 1000;
    Second.name = "Kioto";
    Second.population = 2000;
    Third.name = "Fukuoka";
    Third.population = 3000;

    List<Region, 4> LOL;
    Constructor(LOL);
    PushBack(LOL, Third);
    Push(LOL, Second, 1);
    PushBack(LOL, First);
    Print(LOL);
    std::cout << "Index of Osaka: " << GetIndex(LOL, Second) << std::endl;
    PopFront(LOL);
    PopBack(LOL);
    Print(LOL);
    Destructor(LOL);
    Print(LOL);
} // Проверит гент индекс для структуры