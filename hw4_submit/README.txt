HOMEWORK 4: GROCERY LISTS


NAME:  < Hao Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Xu Chai, Steven, Aritra B, Taoran li ,Stanley Cheung, Andrea Wong/ Cplusplus, Google >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 hours >



ORDER NOTATION:
For each request/command,

i = # of different ingredients in the kitchen
u = maximum units of a single ingredient in the kitchen
r = # of different recipes
k = maximum # of different ingredients in a single recipe
v = maximum units of single ingredient in a single recipe
a = maximum # of different ingredients added with a single ’a’ command 
w = maximum units of a single ingredient added with a single ’a’ command

—————————————————————————————————————————————————————————————————————————————————————————
command 'r' / add a recipe: O(k + r)
Answer:
In this function, I have two parts: Part I: is a for () loop that is used to verify whether the recipe is already in the lists. It’s order notation is O(r). The Part II, the code continue to read the units and name of each Ingredient in a single recipe, and thus the order notation is O(k). SINCE, we don’t know which one is bigger. 
The order notation of this total function is O(k + r).
—————————————————————————————————————————————————————————————————————————————————————————
command 'a' / add ingredients to the kitchen: O(i*a)
Answer:
In this function, I have a loop inside to read through units and name of each Ingredients that are being added into the kitchen. The order notation of this loop is O(a). And inside this loop, there is a member function of kitchen class, this member function has order notation O(i). 
The order notation of this total function O(i*a) 
—————————————————————————————————————————————————————————————————————————————————————————
command 'p' / print a recipe: O(r + klogk)
Answer:
In this function, I have a loop that is used to verify whether the recipe is already in the lists. The order notation of this loop is O(r). And inside this loop, there is a member function of recipe class, this member function has order notation O(klogk + 2k), in which klogk is the order notation of “sort” and k is the order notation of the print loop. Since O(nlogn) is bigger than O(n).
The order notation of this total function is O(r + klogk)

—————————————————————————————————————————————————————————————————————————————————————————
command 'm' / make a recipe:O(r+ k*i + klogk)
Answer:
In this function: I have a loop that is used to verify whether the recipe is already in the lists. The order notation of this loop is O(r). Inside this loop, I divided it into four Parts(you can see them in my makeRecipe function, which had been divided into four parts). Part I, there is nested loop and the order notation of it is O(k*i). Part II, O(k*i). Part III, O(k* Name_exist.size()) (where Name_exist has size smaller than i).
Worst case is O(k*i).
Part IV, let Ingredient_Needed = n, it is O(nlogn), worst case is O(klogk);
Thus, the total order notation is O(r+(k*i+k*i+k*i+klogk)), which can also be simplified as O(r+k*i+klogk)

—————————————————————————————————————————————————————————————————————————————————————————
command 'k' / print the contents of the kitchen: O(ilogi)
Answer:
In this function: O(2i+ilogi), which can be simplified as O(ilogi);

—————————————————————————————————————————————————————————————————————————————————————————
command 's' / suggest recipes: O(r*k*i + rlogr)
In this function: I have a loop that is used to verify whether the recipe is already in the lists. The order notation of this loop is O(r). Inside the loop, the order notation is O(k*i). Part II, the order notation is O(rlogr) (worst case: every recipe can be prepared). Thus, the total order notation is O(r*k*i+rlogr); 
—————————————————————————————————————————————————————————————————————————————————————————
(extra credit) command 'd' / suggest dinner menu:



EXTRA CREDIT:
Describe your implementation of the "suggest dinner menu" option.



MISC. COMMENTS TO GRADER:  
Thank you for your grading!!!！！！！*&*


