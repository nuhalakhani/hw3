#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

  void heapify(int index);

private:
  /// Add whatever helper functions and data members you need below
  vector<T> heap;
  int m1;
  PComparator c1;



};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m1(m), c1(c) {}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {
  while(!empty()) {
    heap.pop_back();
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  heap.push_back(item);
  int index = heap.size()-1;
  while (c1(heap[index], heap[(index-1)/m1])) {
    swap(heap[index],heap[(index-1)/m1]);
    index = (index-1)/m1;
  }
  return; 
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
  throw underflow_error("Empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap.front();


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
  throw underflow_error("Empty");
  }
  T temp = heap[heap.size()-1];
  heap[0] = temp;
  heap.pop_back();
  heapify(0); 
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int index) {

  int first_child_idx = m1*index+1;
  if((unsigned)first_child_idx >= heap.size()) {
    return;
  }

  int min_child_idx = first_child_idx;

  for(int i = 1; i < m1; i++) {
    int current_child_idx = first_child_idx + i;
    if((unsigned)current_child_idx < heap.size()) {
      if(c1(heap[current_child_idx], heap[min_child_idx])) {
        min_child_idx = current_child_idx;
      }
    }
  }
  if(c1(heap[min_child_idx], heap[index])) {
    swap(heap[min_child_idx], heap[index]);
    heapify(min_child_idx);
  }
} 

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return heap.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return heap.size();
}

#endif

