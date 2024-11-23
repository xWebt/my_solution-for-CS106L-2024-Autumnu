/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <string>

class User
{
public:
  User(const std::string &name);

  void add_friend(const std::string &name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string &name);

  /**
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   * 你的自定义操作符和特殊成员函数将在这里实现！
   */
  friend std::ostream &operator<<(std::ostream &os, const User &user);
  // 构析函数
  ~User();

  // 拷贝函数
  User(const User &user);
  User(User &&user) = delete;
  // 重载
  User &operator=(const User &user);
  User &operator=(User &&user) = delete;
  User &operator+=(const User &user);
  bool operator<(const User &user) const;

private:
  std::string _name;
  std::string *_friends;
  size_t _size;
  size_t _capacity;
};