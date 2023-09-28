HOMEWORK 3: MATRIX CLASS


NAME: Oliver Adams


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Lefteri, google, stack overflow, geeksforgeeks, c++ docs

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 10



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get:
O(1) because the time to access something in memory is constant and for assigning a double

set:
O(1) because the time to access something in memory is constant and for assigning a double

num_rows:
O(1) because its accessing a stored int

get_column:
O(1) because its accessing a stored int

operator<<:
O(m*n) because it must loop over every element in the matrix

quarter:
O(m*n) because it has to loop over more than half of the elements in the matrix

operator==:
O(m*n) because it loops over every element

operator!=:
O(m*n) because it loops over every element

swap_rows:
O(n) because it has to copy every element in the array

rref (provided in matrix_main.cpp):
O()


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I didn't run into many confusing memory problems when implemeneting my version of the Matrix class, I did however only run my code through valgrind until all memory leaks were plugged.
I always use cout on lines to figure out where a program is going wrong, but I am trying to get into the habit of using gdb more often.

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

