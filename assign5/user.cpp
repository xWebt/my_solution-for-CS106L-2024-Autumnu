#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string &name) : _name(name), _friends(nullptr), _size(0), _capacity(0) {}
/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void User::add_friend(const std::string &name)
{
  if (_size == _capacity)
  {
    _capacity = 2 * _capacity + 1;
    std::string *newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string &name)
{
  _friends[index] = name;
}

/**
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */
std::ostream &operator<<(std::ostream &os, const User& user)
{
  os << "User(name=" << user.get_name() << ", friends=[";
  for (size_t i = 0; i < user._size; ++i)
    {
      os << user._friends[i];
      if(i != user._size - 1)
        os << ", ";
    }
    os << "])";
  return os;
}
User::~User(){
  delete[] _friends;
}

User::User(const User &user) : _name(user._name), _size(user._size), _capacity(user._capacity), _friends(new std::string[user._capacity])
{
  std::copy(user._friends, user._friends + user._size, _friends);
}

User &User::operator=(const User &other)
{
  if (this == &other) // 防止自己拷贝自己
    return *this;
  delete[] _friends;

  _name = other._name;
  _size = other._size;
  _capacity = other._capacity;
  _friends = new std::string[_capacity];
  std::copy(other._friends, other._friends + _size, _friends);
  return *this;
}

User &User::operator+=(const User &user)
{
  add_friend(user.get_name());

  const_cast<User &>(user).add_friend(get_name());
  return *this;
}

bool User::operator<(const User &user) const
{
  return _name < user._name;
}
