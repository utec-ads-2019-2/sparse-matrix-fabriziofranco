#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <vector>
#include "node.h"
#include <iomanip>
#include <list>
#include <map>

using namespace std;

template <typename T>
class Matrix {
private:
    vector<IndexNode<T>* > MyRows, MyColumns;
    unsigned Rows, Columns;

    Node<T>* Find(unsigned row, unsigned column) const {
        if (row >= Rows or column >= Columns or column<0 or row<0)
            throw out_of_range("Please check your input");

        Node<T>* currentNode = MyRows[row]->link;
        while (currentNode) {
            if (currentNode->column == column)
                return currentNode;
            currentNode = currentNode->next;
        }
        return nullptr;
    }

    Node<T>* FindPrevColumn(int row, int column){
        if (row >= Rows or column >= Columns or column<0 or row<0)
            throw invalid_argument("Index out of range");
        Node<T>* begin = MyColumns[column]->link;
        while(begin){
            if (begin->down)
                if(begin->down->row>=row)
                    return begin;
            begin = begin->down;
        }
        return nullptr;
    }

    Node<T>* FindPrevRow(int row, int column){
        if (row >= Rows or column >= Columns or column<0 or row<0)
            throw invalid_argument("Index out of range");
        Node<T>* begin = MyColumns[column]->link;
        while(begin){
            if (begin->next)
                if(begin->next->column>=column)
                    return begin;
            begin = begin->next;
        }
        return nullptr;
    }



public:
    Matrix(unsigned rows, unsigned columns) : Rows(rows), Columns(columns) {
        for (unsigned i = 0; i < rows; ++i)
            MyRows.push_back(new IndexNode<T>(i));

        for (unsigned i = 0; i < columns; ++i)
            MyColumns.push_back(new IndexNode<T>(i));
    }

    void set(int row, int column, T data){
        if (row >= Rows or column >= Columns or column<0 or row<0)
            throw  out_of_range("Index out of range, please check your input");
        else{
            IndexNode<T>* ColumnPosition=MyColumns[column], *RowPosition=MyRows[row];
            auto flag=Find(row,column),PrevUp=FindPrevColumn(row,column), PrevLeft=FindPrevRow(row,column);
            if(flag){
                if(data==0){
                    if(ColumnPosition->link==flag)
                        ColumnPosition->link=flag->down;
                    else
                        PrevUp->down=flag->down;

                    if(RowPosition->link==flag)
                        RowPosition->link=flag->next;
                    else
                        PrevLeft->next=flag->next;
                    delete flag;
                }
                else{
                    flag->setData(data);
                }
            }
            else{
                if(data==0)
                    return;
                else{
                    auto temp= new Node<T>(row,column,data);
                    if(PrevLeft){
                        auto TempNext=PrevLeft->next;
                        PrevLeft->next=temp;
                        temp->next=TempNext;
                    }
                    else{
                        auto First=RowPosition->link;
                        RowPosition->link=temp;
                        temp->next=First;
                    }
                    if(PrevUp){
                        auto TempDown=PrevUp->down;
                        PrevUp->next=temp;
                        temp->next=TempDown;
                    }
                    else{
                        auto First=ColumnPosition->link;
                        ColumnPosition->link=temp;
                        temp->down=First;
                    }
                }
            }
        }
    }

    T operator()(unsigned row, unsigned column) const {
        auto element=Find(row,column);
        if(element)
            return Find(row,column)->data;
        else
            return 0;
    }

    Matrix<T> operator*(T scalar) const {
        Matrix ImTheFutureOfThisFunction(Rows,Columns);
        for(auto i=0;i<Rows;i++){
            for(auto y=0;y<Columns;y++){
                ImTheFutureOfThisFunction.set(i,y,this->operator()(i,y)*scalar);
            }
        }
        return ImTheFutureOfThisFunction;
    }

    Matrix<T> operator*(Matrix<T> &other) const {
        Matrix ImTheFutureOfThisFunction(Rows,other.Columns);



        return ImTheFutureOfThisFunction;
    }

    Matrix<T>& operator=(const Matrix<T> &other) {
        ImDone();

        Rows = other.Rows;
        Columns = other.Columns;

        for (auto i = 0; i <Rows; ++i)
            MyRows.push_back(new IndexNode<T>(i));

        for (auto i = 0; i <Columns; ++i)
            MyColumns.push_back(new IndexNode<T>(i));

        for(auto i=0;i<Rows;i++){
            for(auto y=0;y<Columns;y++){
                set(i,y,other.operator()(i,y));
            }
        }
        return *this;
    }
    bool operator==(const Matrix<T> &other) {
        for(auto i=0;i<Rows;i++){
            for(auto y=0;y<Columns;y++){
                if(this->operator()(i,y)!=other.operator()(i,y))
                    return false;
            }
        }
        return true;
    }
    Matrix<T> operator+(Matrix<T> &other) const {
        if (Rows != other.Rows or Columns != other.Columns)
            throw out_of_range("Check your input");
        Matrix<T> ImTheFutureOfThisFunction(Rows,Columns);

        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Columns; ++j){
                T sum =  this->operator()(i,j)+other.operator()(i,j);
                ImTheFutureOfThisFunction.set(i,j,sum);
            }
        }
        return ImTheFutureOfThisFunction;
    }
    Matrix<T> operator-(Matrix<T> &other) const {
        if (Rows != other.Rows or Columns != other.Columns)
            throw out_of_range("Check your input");
        Matrix<T> ImTheFutureOfThisFunction(Rows,Columns);
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Columns; ++j){
                T sum =  this->operator()(i,j)-other.operator()(i,j);
                ImTheFutureOfThisFunction.set(i,j,sum);
            }
        }
        return ImTheFutureOfThisFunction;
    }
    Matrix<T> transpose() const {
        Matrix ImTheFutureOfThisFunction(Columns,Rows);
        for(auto i=0;i<Rows;i++){
            for(auto y=0;y<Columns;y++){
                ImTheFutureOfThisFunction.set(y,i,this->operator()(i,y));
            }
        }
        return ImTheFutureOfThisFunction;
    }
    void print() const {
        for(auto i=0;i<Rows;i++){
            for(auto y=0;y<Columns;y++)
                cout<<this->operator()(i,y)<<" ";
            cout<<endl;
        }
    }
    void ImDone(){
        while (!MyColumns.empty()) {
            auto currentNode = MyColumns.back()->link;
            while (currentNode) {
                auto temp = currentNode;
                currentNode = currentNode->down;
                delete temp;
            }
            MyColumns.pop_back();
        }
        while (!MyRows.empty())
            MyRows.pop_back();
        Rows = Columns = 0;
    }
    ~Matrix() {
        ImDone();
    }
};

template<class T>
void Node<T>::setData(T t) {
    Node::data = t;
}

#endif //SPARSE_MATRIX_MATRIX_H