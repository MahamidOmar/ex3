

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template<class T>
class Node
{
public:
    T m_data;
    Node* m_next;

    /*
     * constructor for class Node
     */
    explicit Node(const T data): m_data(data), m_next(nullptr){};

    /*
     * copy constructor for class Node
     */
    Node(const Node& node): m_data(node.m_data), m_next(node.m_next){};

    /*
     * default destructor for class Node
     */
    ~Node() = default;
};

template<class T>
class Queue
{
public:
    /*
     * constructor for class Queue(template), starts a new empty queue
     */
    Queue(): m_size(0), m_head(nullptr), m_tail(nullptr){};

    /*
     * destructor for class Queue(template), clears all the dynamic allocated memory for the nodes
     */
    ~Queue();

    /*
     * copy constructor for class Queue(template), makes a new copy of parameter queue, and allocates to this
     */
    Queue(const Queue& queue);

    /*
     * operator= for class Queue(template), makes a new copy of parameter queue, and allocates to this
     */
    Queue& operator=(const Queue& copy);

    /*
     * method to add new data to the end of the current(this) queue
     */
    void pushBack(const T& data);

    /*
     * returns a reference to the data that was first admitted to the queue
     */
    T& front();

    /*
     * returns a const reference to the data that was first admitted to the queue
     * for the cases of when using const queue
     */
    const T& front() const;

    /*
     * deletes the first data that was first admitted to the queue
     */
    void popFront();

    /*
     * return the size of the current queue
     */
    int size()const;

    /*
     * class for throwing when trying to imply a function on an empty queue
     */
    class EmptyQueue: public std::exception{};

    class Iterator;
    class ConstIterator;

    /*
     * return an iterator which points to the first data in the queue
     */
    Iterator begin() ;

    /*
     * return an iterator which points to the end of the queue
     * doesn't have any data in this location
     */
    Iterator end() ;

    /*
     * return an iterator which points to the first data in the queue
     * in the case of using const queue
     */
    ConstIterator begin() const;

    /*
     * return an iterator which points to the end of the queue
     * in the case of using const queue
     * doesn't have any data in this location
     */
    ConstIterator end() const;

private:
    int m_size;
    Node<T>* m_head;
    Node<T>* m_tail;
};

/*
 * filters data in queue that only work in condition
 * and inserts them to a new Queue
 */
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

/*
 * transforms the data in the queue by performing the operation that it takes
 */
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
    bool operator!=(const Queue<T>::ConstIterator& it)const;

    const ConstIterator& operator++();

    const ConstIterator operator++(int i);

    const T& operator*()const;

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

template<class T>
bool Queue<T>::ConstIterator::operator!=(const Queue<T>::ConstIterator& it)const
{
    return (m_index != it.m_index) || (m_queue != it.m_queue);

}

template<class T>
const typename Queue<T>::ConstIterator::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(m_index > m_queue->m_size)
    {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template<class T>
const typename Queue<T>::ConstIterator::ConstIterator Queue<T>::ConstIterator::operator++(int i)
{
    if(m_index > m_queue->m_size)
    {
        throw InvalidOperation();
    }
    const ConstIterator result = *this;
    ++(*this);
    return result;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*()const
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

