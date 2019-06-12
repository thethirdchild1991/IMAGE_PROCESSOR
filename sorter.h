#ifndef SORTER_H
#define SORTER_H

#include <functional>
#include <vector>

template<typename T>
class Sorter{
public:

    static size_t bubleSort( std::vector<T>& srcArray,
                             std::function<bool(T& l, T& r)> predicate ){
        auto swapped = false;
        do{
            swapped = false;
            for( auto it = srcArray.begin()+1; it != srcArray.end(); it++){
                if( predicate(*it, *(it-1)) ){
                    swapped = true;
                    std::iter_swap(it, (it-1));
                }
            }
        }while(swapped != false);
        return srcArray.size();
    }


    void quickSort(){}
    void joinSort(){}

};

#endif // SORTER_H
