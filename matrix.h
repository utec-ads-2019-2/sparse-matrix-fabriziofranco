#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <vector>
#include "node.h"
using namespace std;

template <typename T>
class Matrix {
private:
    unsigned rows, columns;
    vector<IndexNode<T>*> MyRows;
    vector<IndexNode<T>*> MyColumns;

    Node<T>* Find(int row, int column){
        if (row >= rows or column >= columns or column<0 or row<0)
            return nullptr;
        Node<T>* begin = MyColumns[column]->link;
        while (begin){
            if (begin->row == row)
                return begin;
            begin = begin->down;
        }
        return nullptr;
    }

    Node<T>* FindPrevColumn(int row, int column){
        if (row >= rows or column >= columns or column<0 or row<0)
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
        if (row >= rows or column >= columns or column<0 or row<0)
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
    Matrix(unsigned rows, unsigned columns):rows(rows),columns(columns){
        for(unsigned i=0;i<rows;i++)
            MyRows.push_back(new IndexNode<T>(i));

        for(unsigned i=0;i<columns;i++)
            MyColumns.push_back(new IndexNode<T>(i));
    }

    void set(int row, int column, T data){
        if(row>rows or column>=columns or row<0 or column<0)
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


    T operator()(unsigned row, unsigned column){
        if(Find(row,column))
            return Find(row,column)->getData();
        else
            return 0;
    }

    Matrix<T> operator*(T scalar) {
        Matrix<T> result(rows,columns);
        
    }

    Matrix<T> operator*(Matrix<T> other){}
    Matrix<T> operator+(Matrix<T> other) { }
    Matrix<T> operator-(Matrix<T> other) { }
    Matrix<T> transpose() { }
    void print(){
        for(auto i=0;i<rows;i++){
            for(auto y=0;y<columns;y++)
                cout<<this->operator()(i,y)<<" ";
            cout<<endl;
        }
    }

    ~Matrix(){

    }
};


#endif //SPARSE_MATRIX_MATRIX_H