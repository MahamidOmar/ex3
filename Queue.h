

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template<class T>
class Node
{
public:
    T m_data;
    Node* m_next;

    explicit Node(const T data): m_data(data), m_next(nullptr){};
    Node(const Node& node): m_data(node.m_data), m_next(node.m_next){};
    ~Node() = default;
};

template<class T>
class Queue
{
public:
    Queue(): m_size(0), m_head(nullptr), m_tail(nullptr){};
    ~Queue();

    Queue(const Queue& queue);

    Queue& operator=(const Queue& copy);

    void pushBack(const T& data);

    T& front();

    const T& front() const;

    void popFront();

    int size()const;

    class EmptyQueue: public std::exception{};

    class Iterator;
    class ConstIterator;

    Iterator begin() ;
    Iterator end() ;

    ConstIterator begin() const;
    ConstIterator end() const;

private:
    int m_size;
    Node<T>* m_head;
    Node<T>* m_tail;
};

template<typename T, typename Condition>
Queue<T> filter(Queue<T>& queue, const Condition& condition)
{
    Queue<T> filtered;
    if(queue.size() == 0)
    {
        return filtered;
    }
    for (typename Queue<T>::Iterator it = queue.begin(); it != queue.end() ; ++it)
    {
        if(condition(*it))
        {
            filtered.pushBack(*it);
        }
    }
    return filtered;
}

template<typename T, typename Operation>
void transform(Queue<T>& queue , const Operation& operate)
{
    if(queue.size() == 0)
    {
        return;
    }
    for (typename Queue<T>::Iterator it = queue.begin(); it != queue.end() ; ++it)
    {
        operate(*it);
    }
}

template<class T>
class Queue<T>::Iterator
{
    int m_index;
    const Queue<T>* m_queue;
    friend class Queue<T>;
    Iterator(int index , const Queue<T>* queue):m_index(index) , m_queue(queue){};

public:
    bool operator!=(const Queue<T>::Iterator& it)const;

    Iterator& operator++();

    Iterator operator++(int i);

    T& operator*()const;

    class InvalidOperation: public std::exception{};
};

template<class T>
class Queue<T>::ConstIterator
{
    int m_index;
    const Queue<T>* m_queue;
    friend class Queue<T>;
    ConstIterator(int index , const Queue<T>* queue):m_index(index) , m_queue(queue){};

public:
    bool operator!=(const Queue<T>::ConstIterator& it)const
    {
        return (m_index != it.m_index) || (m_queue != it.m_queue);

    }
    const ConstIterator& operator++()
    {
        if(m_index > m_queue->m_size)
        {
            throw InvalidOperation();
        }
        ++m_index;
        return *this;
    }
    const ConstIterator operator++(int i)
    {
        if(m_index > m_queue->m_size)
        {
            throw InvalidOperation();
        }
        const ConstIterator result = *this;
        ++(*this);
        return result;
    }
    const T& operator*()const
    {
        if(m_index > m_queue->m_size)
        {
            throw InvalidOperation();
        }
        Node<T>* tmp = m_queue->m_head;
        int i = 1;
        while (i < m_index)
        {
            tmp = tmp->m_next;
            ++i;
        }
        return tmp->m_data;
    }

    class InvalidOperation: public std::exception{};
};

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(1 , this);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(m_size + 1 , this);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(1 , this);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(m_size + 1 , this);
}

template<class T>
Queue<T>::~Queue()
{
    Node<T>* toDelete = m_head;
    Node<T>* tmp = m_head;
    while(tmp)
    {
        toDelete = tmp;
        tmp = tmp->m_next;
        delete toDelete;
    }
}

template<class T>
Queue<T>::Queue(const Queue& queue): m_size(queue.m_size), m_head(nullptr), m_tail(nullptr)
{
    const Node<T>* queueNode = queue.m_head;
    m_head = new Node<T>(queueNode->m_data);
    queueNode = queueNode->m_next;
    m_tail = m_head;
    while (queueNode)
    {
        try {
            m_tail->m_next = new Node<T>(queueNode->m_data);
            m_tail = m_tail->m_next;
            queueNode = queueNode->m_next;
        }catch (const std::bad_alloc& e)
        {
            Node<T>* toDelete = m_head;
            Node<T>* tmp = m_head;
            while(tmp)
            {
                toDelete = tmp;
                tmp = tmp->m_next;
                delete toDelete;
            }
            m_size = 0;
            throw e;
        }
    }
}
template<class T>
Queue<T>& Queue<T>::operator=(const Queue& copy)
{
    Node<T>* copyNodes = copy.m_head;
    Node<T>* newHead = new Node<T>(copyNodes->m_data);
    Node<T>* newTail = newHead;
    copyNodes = copyNodes->m_next;
    while (copyNodes)
    {
        try {
            newTail->m_next = new Node<T>(copyNodes->m_data);
            newTail = newTail->m_next;
            copyNodes = copyNodes->m_next;
        }
        catch (const std::bad_alloc& e)
        {
            while(newHead)
            {
                Node<T>* toDelete = newHead;
                newHead = newHead->m_next;
                delete toDelete;
            }
            throw e;
        }
    }
    while (m_head)
    {
        Node<T>* toDelete = m_head;
        m_head = m_head->m_next;
        delete toDelete;
    }
    m_size = copy.m_size;
    m_head = newHead;
    m_tail = newTail;
    return *this;
}

template<class T>
void Queue<T>::pushBack(const T& data)
{
    if(m_size == 0)
    {
        m_head = new Node<T>(data);
        m_tail = m_head;
    }
    else
    {
        m_tail->m_next = new Node<T>(data);
        m_tail = m_tail->m_next;
    }
    m_size++;
}

template<class T>
T& Queue<T>::front()
{
    if(m_size == 0)
    {
        throw EmptyQueue();
    }
    return  m_head->m_data;
}

template<class T>
const T& Queue<T>::front() const
{
    if(m_size == 0)
    {
        throw EmptyQueue();
    }
    return  m_head->m_data;
}

template<class T>
void Queue<T>::popFront() {
    if (m_size == 0) {
        throw EmptyQueue();
    }
    Node<T> *toDelete = m_head;
    m_head = m_head->m_next;
    delete toDelete;
    m_size--;
}

template<class T>
int Queue<T>::size()const
{
    return m_size;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Queue<T>::Iterator& it)const
{
    return (m_index != it.m_index) || (m_queue != it.m_queue);
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(m_index > m_queue->m_size)
    {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int i)
{
    if(m_index > m_queue->m_size)
    {
        throw InvalidOperation();
    }
    Iterator result = *this;
    ++(*this);
    return result;
}

template<class T>
T& Queue<T>::Iterator::operator*()const
{
    if(m_index > m_queue->m_size)
    {
        throw InvalidOperation();
    }
    Node<T>* tmp = m_queue->m_head;
    int i = 1;
    while (i < m_index)
    {
        tmp = tmp->m_next;
        ++i;
    }
    return tmp->m_data;
}

#endif //QUEUE_H

