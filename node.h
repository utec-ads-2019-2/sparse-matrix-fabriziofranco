#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;



template <class T>
class Node {
protected:
    T data;
    int row, column;
    Node<T> *next, *down;
public:
    Node(int row, int column, T data) : row(row), column(column), data(data), next(nullptr),down(nullptr) {}

    void setData(T NewData){
        data=NewData;
    }

    T getData(){
        return data;
    }

    ~Node(){
        ///FALTA
        }


    friend class Matrix<T>;
};

template <class T>


class IndexNode {
protected:
    int position;
    Node<T>* link;
public:
    explicit IndexNode(int position) : position(position), link(nullptr) {}

    ~IndexNode(){
        ///Falta
    }
    friend class Matrix<T>;
};
#endif //SPARSE_MATRIX_NODE_H