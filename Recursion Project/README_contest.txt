HOMEWORK 6: CARCASSONNE CONTEST


NAME:  < Hao Chen >



COLLABORATORS AND OTHER RESOURCES:
< Xu Chai, Taoran Li, Aritra B / google, cplusplus >



DESCRIPTION OF ANY PERFORMANCE IMPROVEMENTS/OPTIMIZATIONS:
(please be concise!)

(I). If the board is very big (rows + colums > tiles.size() ), we don't need to consider all the board places. We can just use part of it. For example,
     if (rows + columns > tiles.size()) {
        rows = int(tiles.size()/2);
        columns = int(tiles.size()/2);
     }
(II). Consider some special cases and of the checking function and make it faster when certain 
situation happens.For example:
       // Corner case: If the every locations can be found,
       // We can initially conclude that this solution have been appeared in the past
       //---------------------------------------------
           for (int i = 0; i < tiles.size(); ++i) {
                for (int j = 0; j < tiles.size(); ++j) {
                        if (Results[m][i] == locations[j]) {
                             count ++;
                         }
                 }
           }



DESCRIBE INTERESTING NEW PUZZLES YOU CREATED:
When it allow rotations, my code just run very slow. Does there anyway to make it faster? 
I have just heard that it run all puzzles within one minutes in Professor’s code.

SUMMARY OF YOUR PERFORMANCE ON ALL PUZZLES:
Correctness & approximate wall clock running time for various command
line arguments.

All puzzles apart from those allowing rotations run correctly and fast.
If not allow_rotations:
PUZZLEs          num_solutions
puzzile6.txt        4
puzzle9.txt         9
All the puzzles can be run within 1 minutes even thought the board is very big. Expect that:
In my code, I can run out all the correct solutions of puzzle8 and puzzle9 with rotations. but there is two problems:
(1) There are duplicate solutions, I’m not able to check the duplicate solutions perfectly after rotations.

