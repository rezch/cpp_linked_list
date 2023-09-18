#pragma once


template <typename T> class list {

public:
    list() : next(nullptr) {}
    explicit list<T>(T value) : value(value), next(nullptr), size_(1) {}
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

    T &operator[](int index);

    void append(T val);

    void extend(T * array, int size) ;

    void insert(int index, T val) ;

    void remove(T val);

    void pop_back();

    void pop(int index);

    void clear();

    int index(T val);

    int count(T val);

    void sort(bool (comparator)(T a, T b) = [](T a, T b){ return a < b; });

    list reverse();

    list * copy();

    [[nodiscard]] int size() const;

    T * to_array();

protected:
    T value{};
    int size_{};
    list* next;

    void clear_() const;

    int index_(T val, int index) const;

    int count_(T val, int count) const;

    list reverse_(list * new_next, int new_size);

};

