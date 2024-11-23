#pragma once

#include <cstddef>
#include <utility>

/**
 * @brief A smart pointer that owns an object and deletes it when it goes out of scope.
 * @tparam T The type of the object to manage.
 * @note This class is a simpler version of `std::unique_ptr`.
 */
template <typename T>
class unique_ptr
{
private:
  /* STUDENT TODO: What data must a unique_ptr keep track of? */
  T *u_ptr;

public:
  /**
   * @brief Constructs a new `unique_ptr` from the given pointer.
   * @param ptr The pointer to manage.
   * @note You should avoid using this constructor directly and instead use `make_unique()`.
   */
  unique_ptr(T *ptr) : u_ptr(ptr) {}

  /**
   * @brief Constructs a new `unique_ptr` from `nullptr`.
   */
  unique_ptr(std::nullptr_t) : u_ptr(nullptr) {};

  /**
   * @brief Constructs an empty `unique_ptr`.
   * @note By default, a `unique_ptr` points to `nullptr`.
   */
  unique_ptr() : unique_ptr(nullptr) {}

  /** STUDENT TODO: In the space below, do the following:
   * - Implement a destructor
   * -实现析构函数
   * - Delete the copy constructor
   * -删除拷贝构造函数
   * - Delete the copy assignment operator
   * -删除拷贝赋值运算符
   * - Implement the move constructor
   * -实现移动构造函数
   * - Implement the move assignment operator
   * -实现移动赋值运算符
   */
  ~unique_ptr()
  {
    delete u_ptr; // 释放空间
  }
  // 显式的删除复制构造函数和复制赋值运算符，保证unique_ptr的独占所有权

  unique_ptr(const unique_ptr &) = delete;// 删除了复制构造函数，防止多个 unique_ptr 实例管理同一个资源，避免二次释放
  unique_ptr &operator=(const unique_ptr &) = delete; // 这个同样是为了防止二次释放，避免因为浅拷贝的内存泄漏

  // 实现显式的移动操作
  // 目的：避免了编译器默认实现可能带来的资源泄漏或行为不一致的问题
  unique_ptr(unique_ptr &&other) noexcept : u_ptr(other.u_ptr)
  {
    other.u_ptr = nullptr;
  }

  unique_ptr &operator=(unique_ptr &&other) noexcept
  {
    if (this != &other)
    {
      delete u_ptr;
      u_ptr = other.u_ptr;
      other.u_ptr = nullptr;
    }
    return *this;
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a reference to the object.
   * @return A reference to the object.
   */
  T &operator*()
  {
    /* STUDENT TODO: Implement the dereference operator */
    //    throw std::runtime_error("Not implemented: operator*()");
    if (!u_ptr)
      throw std::runtime_error("Dereferencing a nullptr");
    else
      return *u_ptr;
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a const reference to the object.
   * @return A const reference to the object.
   */
  const T &operator*() const
  {
    /* STUDENT TODO: Implement the dereference operator (const) */
    // throw std::runtime_error("Not implemented: operator*() const");
    // 和上一个一样，但是这个是const的
    if (!u_ptr)
      throw std::runtime_error("Dereferencing a nullptr");
    else
      return *u_ptr;
  }

  /**
   * @brief Returns a pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A pointer to the object.
   */
  T *operator->()
  {
    /* STUDENT TODO: Implement the arrow operator */
    // throw std::runtime_error("Not implemented: operator->()");
    // 提供箭头操作符
    return u_ptr;
  }

  /**
   * @brief Returns a const pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A const pointer to the object.
   */
  const T *operator->() const
  {
    /* STUDENT TODO: Implement the arrow operator */
    // throw std::runtime_error("Not implemented: operator->() const");
    return u_ptr;
  }

  /**
   * @brief Returns whether or not the `unique_ptr` is non-null.
   * @note This allows us to use a `unique_ptr` inside an if-statement.
   * @return `true` if the `unique_ptr` is non-null, `false` otherwise.
   */
  operator bool() const
  {
    /* STUDENT TODO: Implement the boolean conversion operator */
    // throw std::runtime_error("Not implemented: operator bool() const");
    return u_ptr != nullptr;
  }
  
};
/**
 * @brief Creates a new unique_ptr for a type with the given arguments.
 * @example auto ptr = make_unique<int>(5);
 * @tparam T The type to create a unique_ptr for.
 * @tparam Args The types of the arguments to pass to the constructor of T.
 * @param args The arguments to pass to the constructor of T.
 */
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args &&...args)
{
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}