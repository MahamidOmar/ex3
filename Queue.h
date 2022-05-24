

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template<class T>
class Node
{
public:
    T m_data;
    Node* m_next;
    Node* m_previous;

    Node(const T& data): m_data(data), m_next(nullptr), m_previous(nullptr){};
    ~Node() = default;
};

template<class T>
class Queue
{
public:
    Queue(): m_size(0), m_head(nullptr), m_tail(nullptr){};
    ~Queue()
    {
        while (m_head != nullptr)
        {
            Node<T>* toDelete = m_head;
            m_head = m_head->m_next;
            delete toDelete;
        }
    }

    void pushBack(const T& data)
    {
        if(!m_head)
        {
            m_head = new Node<T>(data);
            m_tail = m_head;
        }
        else
        {
            Node<T>* tmp = m_tail;
            m_tail->m_next = new Node<T>(data);
            m_tail = m_tail->m_next;
            m_tail->m_previous = tmp;
        }
        m_size++;
    }

    T& front()const
    {
        if(m_size == 0)
        {
            throw EmptyQueue();
        }
        return  m_head->m_data;
    }

    void popFront() {
        if (!m_head) {
            throw EmptyQueue();
        }
        Node<T> *toDelete = m_head;
        m_head = m_head->m_next;
        delete toDelete;
        m_size--;
    }

    int size()const
    {
        return m_size;
    }

    class EmptyQueue {};


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
    bool operator!=(const Queue<T>::Iterator& it)const
    {
        return (m_index != it.m_index) || (m_queue != it.m_queue);
    }
    Iterator& operator++()
    {
        if(m_index > m_queue->m_size)
        {
            throw InvalidOperation();
        }
        ++m_index;
        return *this;
    }
    Iterator operator++(int i)
    {
        if(m_index > m_queue->m_size)
        {
            throw InvalidOperation();
        }
        Iterator result = *this;
        ++(*this);
        return result;
    }
    T& operator*()const
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

    class InvalidOperation{};
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

    class InvalidOperation{};
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

#endif //QUEUE_H

