#include <stdexcept>
#include <iostream>

namespace kkoppolu {
  
  template <class T>
  class SharedPtr
  {
  public:

    ~SharedPtr();
    
    // construct from any raw pointer of type Y
    // where implicit conversion between Y and T is available
    // example Y inherits from T
    template<class Y>
    explicit SharedPtr(Y* p)
      :d_p(p), d_refCount(new size_t(1))
      {}

    // explicit copy constructor
    // (to prevent the compiler from providing one)
    explicit SharedPtr(const SharedPtr& p)
      :d_p(p.get()), d_refCount(p.refCount())
      {
	++(*d_refCount); // we have one additional ref now
      }

  
    // construct from any shared pointer of type Y
    // where implicit conversion between Y and T is available
    // example Y inherits from T    
    template<class Y>
    SharedPtr(const SharedPtr<Y>& p)
      :d_p(p.get()), d_refCount(p.refCount())
      {
	++(*d_refCount); // we have one additional ref now
      }

    // explicit assignment operator
    // to prevent the compiler from providing one)
    SharedPtr& operator=(const SharedPtr& other);
    
    // assign from any shared pointer of type Y
    // where implicit conversion between Y and T is available
    // example Y inherits from T    
    template<class Y>
    SharedPtr& operator=(const SharedPtr<Y>& other);
    
    T& operator*() const;
    T* get() const;
    
  protected:
    // derived types of T should be able to get refCount from base class shared pointers
    size_t* refCount() const;
    
  private:
    void remove();
    
    T* d_p;
    size_t* d_refCount;
    
  }; // SharedPtr

  template<class T>
  SharedPtr<T>&
  SharedPtr<T>::operator=(const SharedPtr<T>& other)
  {
    if (d_p != NULL) {
      remove();
    } // if
    d_p = other.get();
    d_refCount = other.refCount();
    ++(*d_refCount);
  } // operator=

  
  template<class T> template <class Y>
  SharedPtr<T>&
  SharedPtr<T>::operator=(const SharedPtr<Y>& other)
  {
    if (d_p != NULL) {
      remove();
    } // if
    d_p = other.get();
    d_refCount = other.refCount();
    ++(*d_refCount);
  } // operator=

  
  template<class T>
  SharedPtr<T>::~SharedPtr<T>()
  {
    std::cout << "d_p is " << d_p << std::endl;
    std::cout << "d_refCount is " << d_refCount << std::endl;
    remove();
  } // ~SharedPtr

  
  template<class T>
  T*
  SharedPtr<T>::get() const
  {
    return d_p;
  } // get

  template<class T>
  T&
  SharedPtr<T>::operator*() const
  {
    if (d_p == NULL) {
      throw std::runtime_error("Null Pointer");
    } // if
    return *d_p;
  } // operator*()

  
  template<class T>
  size_t*
  SharedPtr<T>::refCount() const
  {
    return d_refCount;
  } // refCount

  
  template<class T>
  void
  SharedPtr<T>::remove()
  {
    if (d_refCount == NULL || d_p == NULL) {
      throw std::runtime_error("Obj/Ref Counter is NULL");
    } // if
    
    --(*d_refCount);
    if (d_refCount == 0) {      
      delete d_p;
      d_p = NULL;
      delete d_refCount;
      d_refCount = NULL;
    } // if
  } // remove
  
} // namespace kkoppolu
