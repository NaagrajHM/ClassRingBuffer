#include "InterfaceRingBuffer.hpp"

#include <mutex>

template <typename T, size_t Capacity>
class ClassRingBuffer : public InterfaceRingBuffer<T, Capacity>{
   private:
      T       buffer[Capacity];
      size_t  head = 0;
      size_t  tail = 0;
      bool    full = false;
      mutable mutex mtx;

   public:
      ClassRingBuffer(void) = default;

      bool isEmpty(void) const override{
         lock_guard<mutex> lock(mtx);
         return !full && (head == tail);
      }

      bool isFull(void) const override{
         lock_guard<mutex> lock(mtx);
         return full;
      }

      bool push(const T& item) override{
         lock_guard<mutex> lock(mtx);
         if(full){
            return false;
         }
         else{
            buffer[head] = item;
            head = (head + 1) % Capacity;
            full = (head == tail);
            return true;
         }
      }

      optional<T> pop(void) override{
         lock_guard<mutex> lock(mtx);
         if(
               !full
            && (head == tail)
         ){
            return nullopt;
         }
         else{
            T item = buffer[tail];
            full = false;
            tail = (tail + 1) % Capacity;
            return item;
         }
      }
};

template<typename T, size_t Capacity>
unique_ptr<InterfaceRingBuffer<T, Capacity>> InterfaceRingBuffer<T, Capacity>::Instantiate(void){
   return make_unique<ClassRingBuffer<T, Capacity>>();
}

template class ClassRingBuffer<Message, SIZE_RING_BUFFER>;
template unique_ptr<InterfaceRingBuffer<Message, SIZE_RING_BUFFER>> InterfaceRingBuffer<Message, SIZE_RING_BUFFER>::Instantiate();
