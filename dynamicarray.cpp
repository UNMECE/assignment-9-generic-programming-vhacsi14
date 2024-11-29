#include <iostream>
#include <stdexcept> 

template <typename T>
class DynamicArray {
private:
    T* arr;          
    int currentSize; 
    int capacity;    

public:
   
    DynamicArray() : arr(nullptr), currentSize(0), capacity(0) {}

    
    ~DynamicArray() {
        delete[] arr;
    }

    
    void addElement(T value) {
        if (currentSize == capacity) {
           
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newArr = new T[capacity];
            
            
            for (int i = 0; i < currentSize; ++i) {
                newArr[i] = arr[i];
            }

            
            delete[] arr;

            
            arr = newArr;
        }

        
        arr[currentSize++] = value;
    }

    
    T at(int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    
    int size() const {
        return currentSize;
    }

    
    T sum() const {
        T total = 0;
        for (int i = 0; i < currentSize; ++i) {
            total += arr[i];
        }
        return total;
    }

    
    T max() const {
        if (currentSize == 0) {
            throw std::runtime_error("Array is empty");
        }
        
        T maxValue = arr[0];
        for (int i = 1; i < currentSize; ++i) {
            if (arr[i] > maxValue) {
                maxValue = arr[i];
            }
        }
        return maxValue;
    }

    
    T min() const {
        if (currentSize == 0) {
            throw std::runtime_error("Array is empty");
        }

        T minValue = arr[0];
        for (int i = 1; i < currentSize; ++i) {
            if (arr[i] < minValue) {
                minValue = arr[i];
            }
        }
        return minValue;
    }

   
    DynamicArray<T>* slice(int begin, int end) const {
        if (begin < 0 || end >= currentSize || begin > end) {
            throw std::out_of_range("Invalid slice range");
        }

        DynamicArray<T>* slicedArray = new DynamicArray<T>();
        for (int i = begin; i <= end; ++i) {
            slicedArray->addElement(arr[i]);
        }
        return slicedArray;
    }
};


int main() {
    try {
        DynamicArray<int> int_array;
        int_array.addElement(10);
        int_array.addElement(20);
        int_array.addElement(30);
        int_array.addElement(40);
        int_array.addElement(50);

        std::cout << "Size of array: " << int_array.size() << std::endl;
        std::cout << "Sum of the array: " << int_array.sum() << std::endl;
        std::cout << "Maximum value: " << int_array.max() << std::endl;
        std::cout << "Minimum value: " << int_array.min() << std::endl;

        
        DynamicArray<int>* sliced_array = int_array.slice(1, 3);
        std::cout << "Sliced array: ";
        for (int i = 0; i < sliced_array->size(); ++i) {
            std::cout << sliced_array->at(i) << " ";
        }
        std::cout << std::endl;

        
        delete sliced_array;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

