/*
 * CS106L Assignment 1: SimpleEnroll
 * CS106L 作业 1：简单注册
 *
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 * 由 Fabio Ibanez 创建，Jacob Roberts-Baca 修改。
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * 欢迎来到 CS106L 的作业 1！请完成文件中每个标有 STUDENT TODO 的任务。
 *
 * in this file. You do not need to modify any other files.
 * 只需修改本文件，您无需更改任何其他文件。
 *
 * Students must implement: parse_csv, write_courses_offered,
 * 学生需要实现以下函数：parse_csv、write_courses_offered、
 *
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * 表示学生可以在 ExploreCourses 中选修的课程。
 *
 * You must fill in the types of the fields in this struct.
 * 您需要填写该结构体中字段的类型。
 *
 * Hint: Remember what types C++ streams work with?!
 * 提示：记住 C++ 流操作的常用类型！
 */
struct Course
{
  /* STUDENT TODO */ std::string title;
  /* STUDENT TODO */ std::string number_of_units;
  /* STUDENT TODO */ std::string quarter;
};

/**
 * (STUDENT TODO) Look at how the main function (at the bottom of this file)
 * calls `parse_csv`, `write_courses_offered`, and `write_courses_not_offered`.
 * Modify the signatures of these functions so that they work as intended, and then delete this
 * comment!
 *
 * （学生 TODO）查看本文件底部主函数如何调用 `parse_csv`、`write_courses_offered` 和
 * `write_courses_not_offered`。 修改这些函数的签名，使它们按预期工作，然后删除此注释！
 */

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 *
 * 注意：
 * 我们需要在声明 Course 结构体之后再 #include utils.cpp，
 * 这样 utils.cpp 中的代码才能知道 Course 是什么。
 * 请记住，#include 实际上是将文件内容复制并粘贴到当前位置。
 */

#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * 此函数应该用 `Course` 类型的结构体填充 `courses` 向量。
 * 我们希望通过 courses.csv 文件中的记录来创建这些结构体，其中每一行是一个记录！
 *
 * Hints:
 * 提示：
 * 1) Take a look at the split function we provide in utils.cpp
 * 1) 查看我们在 utils.cpp 中提供的 `split` 函数。
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 2) 每一行都是一条记录！ *这很重要，我们再次强调 :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 * 3) CSV 文件中的第一行定义了列名，所以你可以忽略它！
 *
 * @param filename The name of the file to parse.要解析的文件名。
 * @param courses  A vector of courses to populate.要填充的课程向量。
 */

void parse_csv(std::string filename, std::vector<Course>& courses)
{
  /* (STUDENT TODO) Your code goes here... */
  std::ifstream input_file(filename); // 文件输入流，处理输入
  if (input_file.is_open())
  { // 确认文件是否打开
    std::string deal;
    getline(input_file, deal); // 去除第一行的无效信息
    while (getline(input_file, deal))
    {
      auto return_vec = split(deal, ',');
      Course parse_course;
      parse_course.title = return_vec[0];
      parse_course.number_of_units = return_vec[1];
      parse_course.quarter = return_vec[2];
      // std::cout << parse_course.title << " " << parse_course.number_of_units << std::endl;
      courses.emplace_back(parse_course);
    }
    input_file.close();
  }
  return;
}

/**
 * This function has TWO requirements.
 * 这个函数有两个要求。
 *
 * 1) Write the courses that are offered to the file
 *    "student_output/courses_offered.csv"
 * 1) 将已提供的课程写入文件 "student_output/courses_offered.csv"
 *
 * 2) Delete the courses that are offered from the `all_courses` vector.
 *    IMPORTANT: do this after you write out to the file!
 * 2) 从 `all_courses` 向量中删除已提供的课程。
 *    重要：在写入文件后再进行删除！
 *
 * HINTS:
 * 提示：
 * 1) Keep track of the classes that you need to delete!
 * 1) 跟踪你需要删除的课程！
 * 2) Use the delete_elem_from_vector function we give you!
 * 2) 使用我们提供的 `delete_elem_from_vector` 函数！
 * 3) Remember to write the CSV column headers at the beginning of the output!
 *    See courses.csv for reference.
 * 3) 记得在输出文件的开头写入 CSV 列标题！
 *    可以参考 courses.csv 文件。
 *
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *  通过调用 `parse_csv` 获取的所有课程的向量
 * This vector will be modified by removing all offered courses.
 *这个向量会被修改，删除所有已提供的课程。
 */

void write_courses_offered(std::vector<Course>& all_courses)
{
  /* (STUDENT TODO) Your code goes here... */
  std::ofstream output_file(COURSES_OFFERED_PATH);
  output_file << "Title,Number of Units,Quarter" << std::endl;
  // 存一下要删除的
  std::vector<Course> vector_need_delete;
  if (output_file.is_open())
  {
    for (const auto &[title, number_of_units, quarter] : all_courses)
      if (quarter != "null")
      {
        output_file << title << "," << number_of_units << "," << quarter << std::endl;
        vector_need_delete.push_back({title, number_of_units, quarter});
      }
    output_file.close(); // 用完就关好习惯
  }
  // 注意提示，写入dot_csv文件后再进行删除
  for (const auto &course : vector_need_delete)
    delete_elem_from_vector(all_courses, course);
  return;
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * 这个函数将未提供的课程写入文件 "student_output/courses_not_offered.csv"。
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * 此函数总是在调用 `write_courses_offered` 函数之后调用。
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 * 由于在 `write_courses_offered` 函数中删除了已提供的课程，`unlisted_courses` 将包含未提供的课程。
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 * 提示：这应该与 `write_courses_offered` 非常相似。
 *
 * @param unlisted_courses A vector of courses that are not offered.
 * 一个未提供的课程的向量。
 */

void write_courses_not_offered(std::vector<Course>& unlisted_courses)
{
  /* (STUDENT TODO) Your code goes here... */
  std::ofstream output_file(COURSES_NOT_OFFERED_PATH);
  output_file << "Title,Number of Units,Quarter" << std::endl;
  if (output_file.is_open())
  {
    for (const auto &[title, number_of_units, quarter] : unlisted_courses)
      output_file << title << "," << number_of_units << "," << quarter << std::endl;
     output_file.close(); // 用完就关好习惯
  }
  return;
}

int main()
{
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}