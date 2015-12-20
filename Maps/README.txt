HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Hao Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.


http://www.cs.rpi.edu/academics/courses/spring15/csci1200/calendar.php
http://stackoverflow.com/questions/tagged/c%2B%2B
http://www.cplusplus.com

LMS discussion board:
Timothy Ho 
about generate

Taylor Dahlin
about loading

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?

********************* answer ***********************
The size of the first word map is m. And for each element in the first map
we have p following words, and so on for all sub maps. With window=w;
the total memory used for storing data is O(m*p^(w-1))
********************* answer ***********************

What is the order notation for performance (running time) of each of
the commands?

********************* answer ***********************
load     O(n)
print    O(p)
generate O(k), 
where k= the length of the sentence that we are asked to generate
********************* answer ***********************

EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).

********************* answer ***********************
My program can handle window size greater than 3 because it 
uses heap allocated memory to store the data structure 
, which allows the expansion of windows depth
I did test cases for window=4, window=5 and window=6,
all of which performed fairly well, no error, no memory leaks
and all command processed
********************* answer ***********************

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


