#include "list.h"
#include <algorithm>


list::list() : next(nullptr) {}

list::list(int value) : value(value), next(nullptr), size_(1) {}

list::list(int * array, int size) {
    this->value = *array;
    this->size_ = size;

    if (size == 1) {
        this->next = nullptr;
    }
    else {
        this->next = new list(array + 1, size - 1);
    }
}

list::list(list *lst) {
    this->value = lst->value;
    this->size_ = lst->size_;

    if (lst->next == nullptr) {
        this->next = nullptr;
    }
    else {
        this->next = new list(lst->next);
    }
}

int &list::operator[](int index) {
    if (index == 0 || this->next == nullptr) {
        return this->value;
    }

    return (*this->next)[index - 1];
}

void list::append(int val) {
    ++this->size_;

    if (this->next == nullptr) {
        this->next = new list(val);
    }
    else {
        (*this->next).append(val);
    }
}

void list::extend(int * array, int size) {
    this->size_ += size;

    if (this->next == nullptr) {
        this->next = new list(array, size);
    }
    else {
        (*this->next).extend(array, size);
    }
}

void list::insert(int index, int val) {
    if (index == 0) {
        this->value = val;
        ++this->size_;
        return;
    }

    if (this->next == nullptr) {
        this->next = new list(val);
    }
    else {
        (*this->next).insert(index - 1, val);
    }
}

void list::remove(int val) {
    if (this->next == nullptr) {
        return;
    }

    if ((*this->next).value == val) {
        list * tmp = this->next;
        this->next = (*this->next).next;
        delete tmp;
        --this->size_;
    }
    else {
        (*this->next).remove(val);
    }
}

void list::pop_back() {
    if ((*this->next).next == nullptr) {
        delete this->next;
        this->next = nullptr;
        --this->size_;
    }
    else {
        (*this->next).pop_back();
    }
}

void list::pop(int index) {
    if (this->next == nullptr) {
        return;
    }

    if (index == 1) {
        list * tmp = this->next;
        this->next = (*this->next).next;
        delete tmp;
        --this->size_;
    }
    else {
        (*this->next).pop(index - 1);
    }
}

void list::clear() {
    this->next->clear_();

    this->next = nullptr;
    this->size_ = 0;
    this->value = (int)NULL;
}

void list::clear_() const {
    if (this->next != nullptr) {
        this->next->clear_();
    }
    delete this;
}

int list::index(int val) {
    return this->index_(val, 0);
}

int list::count_(int val, int count) const {
    if (this->value == val) {
        ++count;
    }

    if (this->next == nullptr) {
        return count;
    }

    return (*this->next).count_(val, count);
}

int list::count(int val) {
    return this->count_(val, 0);
}

void list::sort(bool (comparator)(int a, int b)) {
    int * array = this->to_array();
    int array_size = this->size_;


    std::sort(array, array + array_size, comparator);
    this->clear();

    this->size_ = array_size;
    this->value = array[0];
    this->next = new list(array + 1, array_size - 1);
}

list list::reverse_(list * new_next, int new_size) {
    list * temp = this->next;
    this->size_ = new_size;
    this->next = new_next;

    if (temp == nullptr) {
        return *this;
    }

    return temp->reverse_(this, new_size + 1);
}

list list::reverse() {
    list new_list = this->copy()->reverse_(nullptr, 1);

    this->clear();

    return new_list;
}

list * list::copy() {
    return new list(this);
}

int list::index_(int val, int index) const {
    if (this->next == nullptr) {
        return -1;
    }

    if (this->value == val) {
        return index;
    }

    return (*this->next).index_(val, index + 1);
}

int list::size() const {
    return this->size_;
}

int *list::to_array() {
    int * array = new int[this->size_];
    list * ptr = this;

    for (int i = 0; i < this->size_ && ptr != nullptr; ++i, ptr = ptr->next) {
        array[i] = ptr->value;
    }

    return array;
}

