#ifndef SORTER_H
#define SORTER_H

#include <functional>
#include <math.h>
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

    static size_t getMainIndex( size_t len ){
        return static_cast<size_t>(floor(static_cast<float>(len)* 0.62));
    }

    static size_t partition( std::vector<T>& srcArray, size_t left, size_t main, size_t right,
                    std::function<bool(T& l, T& r)> predicate ){
        auto value = srcArray[main];
        std::iter_swap( srcArray.begin() + main, srcArray.begin() + right );

        auto storeIndex = srcArray.begin() + left;

        for( auto it = srcArray.begin() + left; it != srcArray.begin() + right; it++ ){
            if( predicate(*it, value) ){
                std::iter_swap(it, storeIndex);
                storeIndex += 1;;
            }
        }

        std::iter_swap(srcArray.begin() + right, storeIndex);
        return ( storeIndex - srcArray.begin() );
    }


    static size_t quickSort( std::vector<T>& srcArray, size_t l, size_t r,
                    std::function<bool(T& l, T& r)> predicate ){
        if( l < r ){
            auto index = l + getMainIndex(r - l);
            auto newIndex = partition(srcArray, l, index, r, predicate);

            quickSort(srcArray, l, newIndex - 1, predicate);
            quickSort(srcArray, newIndex + 1, r, predicate);
        }

        return srcArray.size();

    }
    void joinSort(){}

};

#endif // SORTER_H
