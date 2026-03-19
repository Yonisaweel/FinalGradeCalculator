# FinalGradeCalculator

Weighted Grade Calculations for a Course

In this assignment, you will calculate weighted grades for students based on course components
such as assignments, quizzes, and exams. Each course component is defined by its name, weight
(percentage), maximum score for that component, and the student’s earned score. The final numeric
grade is calculated as a percentage (0–100%). Note that dynamic memory allocations (e.g.,
malloc, calloc, realloc) and uses of Structures (e.g. struct, union) are strictly NOT allowed in
this assignment.

Key Requirements:
  ◼ Display a menu at the beginning (options for calculating grades for a single student,
multiple students, or exit).
  ◼ Students must store data related to students and course components in arrays whose sizes
are determined at runtime based on user input (e.g., the number of components and/or
the number of students).
  ◼ The program’s logic should be divided into distinct functions (e.g., for reading component
data (if applicable), computing final grades, calculating statistics, etc), ensuring that core
functionalities are not duplicated throughout the code.
  ◼ At least one function must use recursion to perform a calculation, such as summing up
weighted grades or performing another relevant operation. Put the comment before the
function that uses recursion.
  ◼ Numerical final grades must be mapped to letter grades according to a specified grading
scale (e.g., A, A+, A-, etc.)
  ◼ The program must compute maximum, average, and median grades for a set of students
and display these results appropriately.
