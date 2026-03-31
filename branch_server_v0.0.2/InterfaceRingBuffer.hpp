#pragma once

#include <optional>
#include <memory>

using namespace std;

static constexpr size_t SIZE_RING_BUFFER =  5;

template<typename T, size_t Capacity>
class InterfaceRingBuffer{
   public:
      virtual                                             ~InterfaceRingBuffer () = default;
      virtual bool                                         isEmpty             (void) const    = 0;
      virtual bool                                         isFull              (void) const    = 0;
      virtual bool                                         push                (const T& item) = 0;
      virtual optional<T>                                  pop                 (void)          = 0;
      static  unique_ptr<InterfaceRingBuffer<T, Capacity>> Instantiate         (void);
};
