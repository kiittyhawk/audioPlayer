#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QWidget>

struct item
{
  QString   path;
//  int       duration;
};

class Node
{
public:
    item item;
    Node *prev;
    Node *next;

public:
    Node(QString path)
    {
//        this->item.duration = duration;
        this->item.path = path;
        this->next = NULL;
        this->prev = NULL;
    }
};

class LinkedList
{
public:
    Node *head;
    Node *tail;

public:
    LinkedList()
    {
        head = tail = NULL;
    }

    ~LinkedList()
    {
        while (head != NULL)
            pop_front();
    }

    Node *push_front(QString path)
    {
        Node *ptr = new Node(path);
        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        head = ptr;
        return ptr;
    }

    Node *push_back(QString path)
    {
        Node *ptr = new Node(path);
        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;
        return ptr;
    }

    void pop_front()
    {
        if (head == NULL) return;

        Node *ptr = head->next;
        if (ptr != NULL)
            ptr->prev = NULL;
        else
            tail = NULL;

        delete head;
        head = ptr;
    }

    void pop_back()
    {
        if (tail == NULL) return;

        Node *ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;

        delete tail;
        tail = ptr;
    }

    Node *getAt(int index)
    {
        Node    *ptr = head;
        int     n = 0;

        while(n != index)
        {
            if (ptr == NULL)
                return NULL;
            ptr = ptr->next;
            n++;
        }
        return ptr;
    }

    Node *operator[] (int index)
    {
        return getAt(index);
    }

    Node *insert(int index, QString path)
    {
        Node *right = getAt(index);
        if (right == NULL) return push_back(path);

        Node *left = right->prev;
        if (left == NULL) return push_front(path);

        Node *ptr = new Node(path);
        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    void erase(int index)
    {
        Node *ptr = getAt(index);
        if (ptr == NULL) return;

        if (ptr->prev == NULL)
        {
            pop_front();
            return;
        }

        if (ptr->next == NULL)
        {
            pop_back();
            return;
        }

        Node *left = ptr->prev;
        Node *right = ptr->next;
        left->next = right;
        right->prev = left;
        delete ptr;
    }
};

#endif // LINKEDLIST_H
