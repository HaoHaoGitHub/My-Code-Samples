HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Hao Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< XuChai, Aritra B, Taoran Li / google, cplusplus >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >



NAIVE ALGORITHM:

Order Notation:  O(w^2 * h^2)

Timing Experiment Data:
Test Case	                 Real	          User	          Systiny_5x5.ppm	               0m0.011s  	0m0.002s	0m0.004ssmall_10x10.ppm 	       0m0.010s	        0m0.002s	0m0.003ssquiggle_30x30.ppm	       0m0.037s	        0m0.028s	0m0.004slines_100x100.ppm	       0m2.587s	        0m1.451s	0m0.008sdata_structures_300x300.ppm    3m41.237s        3m39.320s       0m0.331sdots_1000x1000.ppm	       three hours had past, but the result still didn’t run out

Discussion:
This naive algorithm is based on a four-level nested loop which tries to compute the distance between
every pixels. Very inefficient and cost a lot of running time.


IMPROVED ALGORITHM:

Order Notation: O(w*h*p)

Timing Experiment Data:
Test Case                      	Real	          User         	  Sys
tiny_5x5.ppm            	0m0.015s	0m0.001s	0m0.003ssmall_10x10.ppm        		0m0.017s	0m0.003s	0m0.004ssquiggle_30x30.ppm              0m0.032s	0m0.012s	0m0.006slines_100x100.ppm	       	0m0.122s	0m0.102s	0m0.004sdata_structures_300x300.ppm	0m14.787s	0m20.007s	0m0.008s
dots_1000x1000.ppm              half an hour had past, but the result still didn’t run out

Discussion:
In this method, we first find all of the black pixels(O(w*h)), then use another loop to compute closest
distances to the black pixels (O(w*h*p)). Total: O(w*h)+O(w*h*p)= O(w*h*p). Still very slow when the input
is very big.

FAST MARCHING METHOD (with a map):

Order Notation: O(p^2 + w*h)

Timing Experiment Data:
Test Case                      	Real	          User         	  Sys
tiny_5x5.ppm	                0m0.018s	0m0.002s	0m0.005ssmall_10x10.ppm 	        0m0.011s	0m0.002s	0m0.004ssquiggle_30x30.ppm	        0m0.018s	0m0.010s	0m0.004slines_100x100.ppm	        0m0.120s	0m0.110s	0m0.005sdata_structures_300x300.ppm	0m1.530s	0m15.927s       0m0.012sdots_1000x1000.ppm	        0m16.361s	0m8.581s	0m0.101s
Discussion:
This method is quite efficient and runs pretty fast even for very large input.
1) // Initialize the coordinates in distance_image: O(w*h)
2) // Initialize the distance field value of black pixels to 0: O(w*h)
3) // Calculate the 8 neighboring pixels' distances of each black pixels and set them:
   O(p*8*8*p) = O(64*p^2)
4) // Place the newly_updated pixels into a priority queue: O(1)* 8*p
 1) removing the top element(O(log8*p):the approximate size of the priority queue is 8*p and the perculate_down is O(logn))
 2) compute 8 adjacent pixels of the removed root (O(1)*8)
 3) if a certain adjacent pixel is already in queue, adjust its place.(perculate_up O(1) + perculate_down O(log8*p))
    if a certain adjacent pixel is not in queue, push it in the queue (perculate_up O(1));
the while loop is about 8*p times iteration. So the total running time for this loop is 8*p*(log8*p + 8 + 1 + log8*p + 1)
which can be concluded as O(p*logp)

Total Order notation: O(p*logp) + O(p^2) + O(w*h) = O(p^2 + w*h)

DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:


FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Thank you for your grading!






