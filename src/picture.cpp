#include "picture.hpp"
#include <iostream>
#include <utility>


Picture::Picture() : head(nullptr), tail(nullptr){}

Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr){
    for (ListNode* p = other.head; p != nullptr; p = p->next){
        add(*p->shape);
    }
}

Picture::Picture(Picture&& other) : head(other.head), tail(other.tail){
    other.head = nullptr;
    other.tail = nullptr;
}

void Picture::swap(Picture& other){
    ListNode* tmp_head = head;
    ListNode* tmp_tail = tail;

    head = other.head;
    tail = other.tail;

    other.head = tmp_head;
    other.tail = tmp_tail;
}

Picture& Picture::operator=(const Picture& other){
    Picture tmp(other);
    swap(tmp);
    return *this;
}

Picture& Picture::operator=(Picture&& other){
    swap(other);
    return *this;
}

void Picture::add(const Shape& shape){
    ListNode* newNode = new ListNode{ shape.clone(), nullptr};

    if (tail == nullptr){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// calls method print() on each shape in the order they were added
void Picture::print_all(std::ostream& out) const{
    for (ListNode* p = head; p != nullptr; p = p->next){
        p->shape->print(out);
        p->shape->draw(out);
    }
}

// draws the Shapes in this Picture in the order they were added
void Picture::draw_all(std::ostream& out) const{
    for (ListNode* p = head; p != nullptr; p = p->next){
        p->shape->draw(out);
    }
}

// returns the sum of the aeas of all the Shapes in this Picture
double Picture::total_area() const{
    double area = 0.0;
    for (ListNode* p = head; p != nullptr; p = p->next){
        area += p->shape->area();
    }
    return area;
}

// frees all storage owed by this Picture when it dies
Picture::~Picture(){
    for (ListNode* p = head; p != nullptr;){
        ListNode* tmp = p;
        p = p->next;
        delete tmp->shape;
        delete tmp;
    }
}
