/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include <iostream>
#include "class.h"

/* #### Please don't change this line! #### */
int run_autograder();

int main()
{
  // STUDENT TODO: Construct an instance of your class!
  person someone("Jeff", 20);
  std::cout << someone << std::endl;
  /* #### Please don't change this line! #### */
  return run_autograder();
}

/* #### Please don't change this line! #### */
#include "utils.hpp"