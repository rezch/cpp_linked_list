
class list {

public:
    list();
    explicit list(int value);
    list(int * array, int size);
    explicit list(list * lst);

    int &operator[](int index);

    void append(int val);

    void extend(int * array, int size) ;

    void insert(int index, int val) ;

    void remove(int val);

    void pop_back();

    void pop(int index);

    void clear();

    int index(int val);

    int count(int val);

    void sort(bool (comparator)(int a, int b) = [](int a, int b){ return a < b; });

    list reverse();

    list * copy();

    int size() const;

    int * to_array();

protected:
    int value = (int)NULL, size_{};
    list* next;

    void clear_() const;

    int index_(int val, int index) const;

    int count_(int val, int count) const;

    list reverse_(list * new_next, int new_size);

};