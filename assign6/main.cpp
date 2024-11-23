/*
 * CS106L Assignment 6: Explore Courses
 * Created by Haven Whitney with modifications by Jacob Roberts-Baca and Fabio
 * Ibanez.
 */

#include <algorithm>
#include <type_traits>
#include <vector>

/** STUDENT_TODO: You will need to include a relevant header file here! */
/** 学生任务：你需要在这里包含一个相关的头文件！ */
#include <optional>
#include "autograder/utils.hpp"

/**
 * A course. This should be familiar from Assignment 1!
 * 一门课程。这应该和任务 1 中的内容很熟悉！
 */
struct Course
{
  std::string title;
  std::string number_of_units;
  std::string quarter;

  /**
   * You don't have to ignore this anymore! We're defining the `==` operator for
   * the Course struct.
   * 你不必再忽略这一点了！我们正在为 `Course` 结构体定义 `==` 运算符。
   */
  bool operator==(const Course &other) const
  {
    return title == other.title && number_of_units == other.number_of_units &&
           quarter == other.quarter;
  }
};

class CourseDatabase
{
public:
  CourseDatabase(std::string filename)
  {
    auto lines = read_lines(filename);
    std::transform(lines.begin(),
                   lines.end(),
                   std::back_inserter(courses),
                   [](std::string line)
                   {
                     auto parts = split(line, ',');
                     return Course{parts[0], parts[1], parts[2]};
                   });
  }

  /**
   * Finds a course in the database with the given title, if it exists.
   * 在数据库中查找具有指定标题的课程（如果存在）。
   * @param course_title The title of the course to find.
   *                     要查找的课程标题。
   * @return You will need to figure this out!
   *         你需要自己确定返回类型！
   */
  std::optional<Course> find_course(std::string course_title)
  {
    /* STUDENT_TODO: Implement this method! You will need to change the return
     * type. */
    auto it = find_if(courses.begin(), courses.end(), [&](Course &other)
                      { return other.title == course_title; });
    if (it != courses.end())
      return *it;
    else
      return std::nullopt;
    // throw std::runtime_error("find_course not implemented");
  }
private:
  std::vector<Course> courses;
};

int main(int argc, char *argv[])
{
  static_assert(
      !std::is_same_v<std::invoke_result_t<decltype(&CourseDatabase::find_course),CourseDatabase, std::string>,FillMeIn>,
      "You must change the return type of CourseDatabase::find_course to "
      "something other than FillMeIn.");

  if (argc == 2)
  {
    CourseDatabase db("autograder/courses.csv");
    auto course = db.find_course(argv[1]);

    /* STUDENT_TODO: Change this condition. How can you check if the database
     * has the desired course? */
    if (course)
    {
      std::cout << "Found course: " << course->title << ","
                << course->number_of_units << "," << course->quarter << "\n";
    }
    else
    {
      std::cout << "Course not found.\n";
    }

    return 0;
  }

  return run_autograder();
}