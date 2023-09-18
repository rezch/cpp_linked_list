#include "list_source.h"
#include <algorithm>
#include <cassert>


template <typename T>
T &list<T>::operator[](int index)  {
    assert(index >= 0);
    assert(index < this->size_);

    if (index == 0 || this->next == nullptr) {
        return this->value;
    }

    return (*this->next)[index - 1];
}

template <typename T>
void list<T>::append(T val) {
    ++this->size_;

    if (this->next == nullptr) {
        this->next = new list(val);
    }
    else {
        (*this->next).append(val);
    }
}

template <typename T>
void list<T>::extend(T * array, int size) {
    this->size_ += size;

    if (this->next == nullptr) {
        this->next = new list(array, size);
    }
    else {
        (*this->next).extend(array, size);
    }
}

template <typename T>
void list<T>::insert(int index, T val) {
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

template <typename T>
void list<T>::remove(T val) {
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

template <typename T>
void list<T>::pop_back() {
    if ((*this->next).next == nullptr) {
        delete this->next;
        this->next = nullptr;
        --this->size_;
    }
    else {
        (*this->next).pop_back();
    }
}

template <typename T>
void list<T>::pop(int index) {
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

template <typename T>
void list<T>::clear() {
    if (this->next != nullptr) {
        this->next->clear_();
    }

    this->next = nullptr;
    this->size_ = 0;
}

template <typename T>
void list<T>::clear_() const {
    if (this->next != nullptr) {
        this->next->clear_();
    }
    delete this;
}

template <typename T>
int list<T>::index(T val) {
    return this->index_(val, 0);
}

template <typename T>
int list<T>::count_(T val, int count) const {
    if (this->value == val) {
        ++count;
    }

    if (this->next == nullptr) {
        return count;
    }

    return (*this->next).count_(val, count);
}

template <typename T>
int list<T>::count(T val) {
    return this->count_(val, 0);
}

template <typename T>
void list<T>::sort(bool (comparator)(T a, T b)) {
    T * array = this->to_array();
    T array_size = this->size_;


    std::sort(array, array + array_size, comparator);
    this->clear();

    this->size_ = array_size;
    this->value = array[0];
    this->next = new list(array + 1, array_size - 1);
}

template <typename T>
list<T> list<T>::reverse_(list * new_next, int new_size) {
    list * temp = this->next;
    this->size_ = new_size;
    this->next = new_next;

    if (temp == nullptr) {
        return *this;
    }

    return temp->reverse_(this, new_size + 1);
}

template <typename T>
list<T> list<T>::reverse() {
    list new_list = this->copy()->reverse_(nullptr, 1);

    this->clear();

    return new_list;
}

template <typename T>
list<T> * list<T>::copy() {
    return new list(this);
}

template <typename T>
int list<T>::index_(T val, int index) const {
    if (this->next == nullptr) {
        return -1;
    }

    if (this->value == val) {
        return index;
    }

    return (*this->next).index_(val, index + 1);
}

template <typename T>
int list<T>::size() const {
    return this->size_;
}

template <typename T>
T *list<T>::to_array() {
    T * array = new T[this->size_];
    list * ptr = this;

    for (int i = 0; i < this->size_ && ptr != nullptr; ++i, ptr = ptr->next) {
        array[i] = ptr->value;
    }

    return array;
}

