#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <class T>
class Node {
protected:
    T data;
    unsigned row, column;
    Node<T> *next, *down;
public:
    Node(unsigned row, unsigned column, T data) : row(row), column(column), data(data), next(nullptr),
                                                                down(nullptr) {}

    void setData(T t);

    ~Node() {
        next = down = nullptr;
        data = row = column = 0;
    }

    friend class Matrix<T>;
};

template <class T>
class IndexNode {
protected:
    unsigned index;
    Node<T>* link;
public:
    explicit IndexNode(unsigned index) : index(index), link(nullptr) {}

    ~IndexNode() {
        link = nullptr;
        index = 0;
    }

    friend class Matrix<T>;
};
#endif //SPARSE_MATRIX_NODE_H