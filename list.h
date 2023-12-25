#pragma once
#include <algorithm>
#include <cassert>

template <typename T> class list {
public:
    list() : next(nullptr) {}

    explicit list(T value) : value(value), next(nullptr), size_(1) {}

    list(T * array, int size) {
        this->value = *array;
        this->size_ = size;

        if (size == 1) {
            this->next = nullptr;
        }
        else {
            this->next = new list(array + 1, size - 1);
        }
    }

    explicit list(list * lst) {
        this->value = lst->value;
        this->size_ = lst->size_;

        if (lst->next == nullptr) {
            this->next = nullptr;
        }
        else {
            this->next = new list(lst->next);
        }
    }

    T &operator[](int index) {
        assert(index >= 0);
        assert(index < this->size_);
        if (index == 0 || this->next == nullptr) {
            return this->value;
        }
        return (*this->next)[index - 1];
    }

    void append(T val) {
        ++this->size_;
        if (this->next == nullptr) {
            this->next = new list(val);
            return;
        }
        this->next->append(val);
    }

    void extend(T * array, int size) {
        this->size_ += size;

        if (this->next == nullptr) {
            this->next = new list(array, size);
        }
        else {
            this->next->extend(array, size);
        }
    }

    void insert(int index, T val) {
        if (index == 0) {
            this->value = val;
            ++this->size_;
            return;
        }

        if (this->next == nullptr) {
            this->next = new list(val);
        }
        else {
            this->next->insert(index - 1, val);
        }
    }

    void remove(T val) {
        if (this->next == nullptr) {
            return;
        }
        if (this->next->value == val) {
            list * tmp = this->next;
            this->next = this->next->next;
            delete tmp;
            --this->size_;
            return;
        }
        this->next->remove(val);
    }

    void pop(int index = 0) {
        if (this->next == nullptr) {
            return;
        }
        if (index == 1) {
            list * tmp = this->next;
            this->next = this->next->next;
            delete tmp;
            --this->size_;
            return;
        }
        this->next->pop(index - 1);
    }

    void pop_back() {
        this->pop(this->size_);
    }

    void clear() {
        if (this->next != nullptr) {
            this->next->clear_();
        }

        this->next = nullptr;
        this->size_ = 0;
    }

    int index(T val) {
        return this->index_(val, 0);
    }

    int count(T val) {
        return this->count_(val, 0);
    }

    void sort(bool (comparator)(T a, T b) = [](T a, T b){ return a < b; }) {
        T * array = this->to_array();
        T array_size = this->size_;
        std::sort(array, array + array_size, comparator);
        this->clear();
        this->size_ = array_size;
        this->value = array[0];
        this->next = new list(array + 1, array_size - 1);
    }

    list reverse() {
        list new_list = this->copy()->reverse_(nullptr, 1);
        this->clear();
        return new_list;
    }

    list * copy() {
        return new list(this);
    }

    [[nodiscard]] int size() const {
        return this->size_;
    }

    T * to_array() {
        T * array = new T[this->size_];
        list * ptr = this;
        for (int i = 0; i < this->size_ && ptr != nullptr; ++i, ptr = ptr->next) {
            array[i] = ptr->value;
        }
        return array;
    }

protected:
    T value{};
    int size_{};
    list* next;

    void clear_() const {
        if (this->next != nullptr) {
            this->next->clear_();
        }
        delete this;
    }

    int index_(T val, int index) const {
        if (this->next == nullptr) {
            return -1;
        }
        if (this->value == val) {
            return index;
        }
        return this->next->index_(val, index + 1);
    }

    int count_(T val, int count) const {
        if (this->next == nullptr) {
            return count;
        }
        if (this->value == val) {
            ++count;
        }
        return this->next->count_(val, count);
    }

    list reverse_(list * new_next, int new_size) {
        list * temp = this->next;
        this->size_ = new_size;
        this->next = new_next;
        if (temp == nullptr) {
            return *this;
        }
        return temp->reverse_(this, new_size + 1);
    }

};

