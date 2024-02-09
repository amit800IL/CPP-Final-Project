#pragma once

#include <iostream>
#include <iterator>
#include <memory>
#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"


#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H


struct Node
{
	Customer& customer;
	std::unique_ptr<Node> next;

	explicit Node(Customer& customer) : customer(customer), next(nullptr) {}
};

struct Iterator
{
private:
    Node* current;
public:
    explicit Iterator(Node* node) : current(node) {}

    Customer& operator*() const { return current->customer; }

    Iterator& operator++() 
    {
        current = current->next.get();
        return *this;
    }

    bool operator !=(const Iterator& other) const { return current != other.current; }
};

class CustomerQueue
{
private:
	std::unique_ptr<Node> head;
	std::unique_ptr<Customer> lastServedCustomer;
	Node* tail;
	bool lastCustomerRegular;

public:
    CustomerQueue() : head(nullptr), tail(nullptr), lastCustomerRegular(false) {}

    bool IsEmpty() const;
    void Enqueue(Customer&& customer);
    void Dequeue();
    const Node& GetHead() const;

    bool LastCustomerRegular() const { return lastCustomerRegular; }
    Iterator begin() { return Iterator(head.get()); }
    Iterator end() { return Iterator(nullptr); }
};

#endif // CUSTOMER_QUEUE_H
