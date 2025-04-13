/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * CS106L 第二次作业：婚姻协议
 * 由 Haven Whitney 创建，Fabio Ibanez 和 Jacob Roberts-Baca 修改。
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * 欢迎来到 CS106L 的第二次作业！请完成此文件中的每个 STUDENT TODO。
 *
 * in this file. You do not need to modify any other files.
 * 你不需要修改其他文件。
 *
 */
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <sstream>
#include "utils.h"
// 随便编造的名字
std::string kYourName = "A B"; // Don't forget to change this!
/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * 接收一个文件名，并返回一个包含所有申请者名字的集合。
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 *                  要读取的文件名。
 *                  文件的每一行将是一个申请者的名字。
 *
 * @returns         A set of all applicant names read from the file.
 *                 返回一个包含从文件中读取的所有申请者名字的集合。
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 *         如果需要，可以将此函数（以及下面的函数）的返回类型更改为 `std::unordered_set`。
 *         如果这样做，请确保也更改 `utils.h` 中相应的函数。
 */

std::set<std::string> get_applicants(std::string filename)
{
  // STUDENT TODO: Implement this function.
  std::ifstream input_file(filename);
  std::set<std::string> name;
  if (input_file.is_open())
  {
    std::string s;
    while (getline(input_file, s))
      name.insert(s);
    input_file.close();
  }
  return name;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * 接收一个学生名字的集合（通过引用传递），并返回一个包含匹配给定学生名字的名字队列。
 *
 * @param name      The returned queue of names should have the same initials as this name.
 *                  返回的名字队列应与此名字具有相同的首字母。
 * @param students  The set of student names.
 *                  学生名字的集合。
 * @return          A queue containing pointers to each matching name.
 *                 返回一个包含指向每个匹配名字的指针的队列。
 */

std::queue<const std::string *> find_matches(std::string name, std::set<std::string> &students)
{
  // STUDENT TODO: Implement this function.
  std::stringstream split(name);
  std::string first, second;
  split >> first >> second;

  std::queue<const std::string *> que;
  for (const auto &now_name : students)
  {
    split.clear();
    split << now_name;
    std::string first_name, last_name;
    split >> first_name >> last_name;
    if (first_name[0] == first[0] && last_name[0] == second[0])
      que.push(&now_name); // 从set当中取出的值是const string，需要取地址转换为const string*
  }
  return que;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * 接受一个可能匹配对象的指针队列，并确定那个唯一的真爱！
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * 你可以根据自己的方式来实现这个函数，但尽量做得比简单的 `pop()` 更复杂一些。
 *
 * @param matches The queue of possible matches.
 *                一个可能匹配对象的队列。
 *
 * @return        Your magical one true love.
 *                你那个神奇的唯一真爱。
 *
 * Will return "NO MATCHES FOUND." if `matches` is empty.
 * 如果 `matches` 为空，将返回 "NO MATCHES FOUND."。
 */

std::string get_match(std::queue<const std::string *> &matches)
{
  // STUDENT TODO: Implement this function.
  if (matches.empty())
    return "NO MATCHES FOUND.";

  size_t que_size = matches.size();
  srand(time(0)); // 时间戳随机生成随机数
  int pos = (rand() % que_size) - 1;
  while (pos--)
    matches.pop();
  return *matches.front();

  return "NO MATCHES FOUND.";
}
/* #### Please don't modify this call to the autograder! #### */
int main() { return run_autograder(); }
