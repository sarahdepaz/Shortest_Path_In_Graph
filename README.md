# Shortest Path in a Graph Searcher - Milestone 2 - BIU.

Finding the shortest path between two entries in a matrix using different search algorithms able to move left/right and up/down.

**Prerequisites**
Linux environemnt to run the code
Running the code
Download the code and open a telnet connection in the terminal in your desired port. This will connect to the program

# Supplying your own graphs
The graphs are entered in a specific format:
```
a,b,c,d,e
f,g,h,j,p
...
...
entry_row, entry_col
exit_row, exit_col
end
```
Where each letter represents a number. This number indicates the weight of the cell in the matrix - how much it costs to move to that position in the graph. The length of a path is the sum of the weights in the path and not necessarily the amount of steps it took.
Note: negative weights are ignored as they are treated as 'walls' the algorithm cannot pass, meaning it will search for a path around it.

The matrices don't have to be squares, but all the rows need to be the same size!

You can also change the starting position using the 'entry_row/col' numbers, and finish position using the 'exit_row/col' numbers. You can set these values to your liking or needs. Make sure your entry/exit position is within the matrix and isn't exceeding its size. The first row and column are numbered '0'.
The final line of your input needs to be 'end' in order to tell the algorithm to start looking for the path.

**Solution**

Once the algorithm has finished searching for the path, it will display it in a sequence of instructions - go left, go right, etc.

**Example**

Suppose we give the program the following problem:
```
8,2,8,6,8,2,12,2,4,1,9,9,5,12,1,1,1,2,7,3,1,6,9,3,9,7,7,9,5,6,4,5,1,6,-1,1,7
4,12,2,3,2,5,2,1,12,2,4,5,4,3,3,4,12,2,3,9,6,9,1,6,7,7,5,8,7,2,-1,3,2,5,-1,9,2
1, 5, 8, 9, 2, 1, 2, 4, 7, 8, 2, 9, 8, 4, 2, 2,12, 8, 8, 2, 3, 3, 1, 5,12,-1, 2, 7, 1, 4,-1,-1,-1, 2,-1, 5, 6
8, 6, 2, 4,12, 8, 9, 9, 7, 1, 2, 8, 8, 2, 4, 2, 1, 7, 6, 8, 3,-1, 8, 1, 8, 6, 1, 3, 3, 2, 7, 3, 4, 2, 9,12, 2
7, 6, 2,12, 7, 8, 1,-1, 5, 8, 8, 1, 1, 5, 8, 9, 9, 1, 8, 5, 1, 8, 4, 5, 4, 5, 8, 7, 6, 6, 8, 2, 2, 8, 8, 8, 8
9, 3, 2, 3, 5,12,-1, 9, 2, 8, 3, 8, 2,12,12, 7, 1, 8, 4, 2,12, 5, 4, 7, 4, 4, 6,12, 9, 2, 3, 5,12, 2, 2, 3, 5
12, 5, 1, 7, 5,12, 6, 6, 6, 5, 8, 9, 4, 3, 9, 2,12, 4, 9, 5, 3,12, 3, 9, 3, 4,-1, 8, 5, 2,12, 5, 2, 3, 7, 6,-1
 1,12, 2, 9, 9, 1, 2, 2,-1, 2, 6,12, 1,12,12, 2, 7, 5, 2, 7, 7, 6, 9, 2, 3, 2, 4, 9,-1, 5, 7,-1, 9, 8, 6, 3, 4
12, 2, 1, 2, 6,12, 2, 6,-1,-1, 3, 9, 9, 8, 3, 7, 4, 3, 4, 5,-1, 9, 3, 5,12, 2, 3,-1,12, 2, 2, 2, 7, 8,-1,12, 2
 7, 4, 8, 2, 8, 7,-1, 3,-1, 2,-1, 7, 9, 6, 7, 6, 1,12, 6, 2, 5, 8, 1, 2, 8, 3, 2,12, 7,12, 1, 2, 6, 9, 7, 3, 8
 6, 2, 4, 7, 7,12, 8, 2, 1, 6, 2, 6, 4, 6, 6, 7, 5, 5, 8, 2,12, 2, 6, 8,12, 8,12, 9, 9, 2, 2, 2, 9, 6, 5, 4, 2
 7, 2, 9, 4, 7, 4, 5, 8, 2, 2, 4, 3, 6, 1, 4, 7, 4, 9,-1, 5,12, 3, 4, 9, 7,12, 3, 5, 2, 9, 7, 2,-1, 5,12, 7, 1
 6, 6, 8, 2,12, 4,-1, 4,-1, 2, 9, 6, 5, 7, 2, 4, 9,12, 4, 9, 2, 9, 2, 6, 7, 1,12, 5, 6, 6, 5,12, 4, 5, 7, 6, 8
 3, 9, 1, 4, 8, 2,-1, 2,-1, 7, 8, 3, 6, 6, 9, 4, 6,-1, 4,-1, 1, 4, 5, 9, 2, 2, 1, 9, 3, 7, 2, 1,12, 5, 6,-1, 9
12, 8, 9, 1,12, 7, 2,12, 9,12,12, 1, 9, 3, 7, 5, 9, 3, 8, 6, 6, 7, 1, 1, 5, 6, 2, 7, 2, 3, 4, 9, 9, 9,12, 2, 8
12, 2, 8, 5,-1, 2, 5, 8, 7, 2, 5, 1, 3, 2, 4, 3, 9, 5, 9, 7, 7, 2,-1, 2, 8, 4, 1, 5, 9, 6, 2, 4, 2, 9, 1,-1, 2
 4, 4, 5,12, 2, 5, 2, 3, 2, 2, 2, 4, 5, 3,12, 9, 3, 6, 2, 9, 9, 1, 4, 3, 2,12, 3, 1, 8, 6, 7, 4, 6, 7, 5, 1, 8
 4,-1, 9, 7, 5, 5, 3,12, 8, 3, 3, 9, 5, 6, 1,12, 7, 4, 9, 9, 5, 9, 8, 9, 9, 1, 6, 9, 7, 5, 3, 5, 4, 6, 3, 2, 1
 9, 2, 1, 5, 1, 3, 8, 2, 1, 2, 5, 2, 9, 9, 3, 4, 2, 2, 2,12, 7, 2,12, 3, 7, 2, 8, 9, 2, 1, 2, 2, 2, 3, 4,12, 3
 6, 6, 1,-1,12, 7, 1, 5, 2, 3, 5, 8,12, 7, 3, 2, 6, 8, 5, 1,12, 2, 6, 6, 8, 2, 7,-1, 2, 7, 9, 5, 5, 7, 1, 5, 4
 3, 6, 4,12, 7, 8, 2, 9, 8, 3, 4, 3, 8, 7, 6, 6, 2, 7, 9, 6, 6, 2, 2, 6, 5, 9, 2, 3, 3, 3,12, 7,12, 6, 7, 2, 9
12, 1, 2,-1, 7, 2, 5,12, 2, 8, 4, 7, 8, 7, 7, 5, 2, 5, 7, 4, 2, 4, 3,12, 6, 8, 5, 2, 1, 4, 9, 2, 1, 4, 2, 2, 2
12, 4, 9,12, 9,12, 9,12, 7, 9, 2, 1, 6, 5, 3, 2, 6, 4, 7, 9,12, 4, 4, 9, 8, 1, 7, 8, 2, 2, 9, 3, 8, 5, 3, 7, 6
 7, 4, 6, 2, 7, 7, 8, 6, 8, 9, 1, 2, 9, 3, 4, 9, 2, 8,12, 1, 2, 5, 9, 8, 7, 9, 3, 3,12, 7, 9, 8, 3, 2,12, 3, 6
 9, 2, 1, 8, 4, 8, 1, 8, 6, 2, 3, 9, 1, 7, 3, 8, 5, 8, 5, 4, 4,12, 5, 2, 9, 2, 1, 9, 2, 6, 8, 4, 4,-1,-1,-1,12
 7, 7, 2, 8, 4, 4, 1, 9, 8, 2, 9, 8,12, 5, 5, 2, 8, 1, 5, 9, 9,12, 6, 5, 9, 8, 1, 4, 4, 7, 6,12, 4, 9, 1, 8, 2
 1, 6, 7, 2, 8, 7, 6,12, 1, 2, 9, 5,12, 7, 6, 4, 9, 2, 2, 5, 1, 9, 2, 1, 6, 8, 3, 2, 8, 1, 2, 6, 9, 8, 3,-1, 2
 5, 5, 7,12, 1, 8, 4, 4, 2,12,12, 1, 1, 2, 8, 4, 8, 2, 6, 8, 3, 8, 5, 5, 3, 8,12, 8, 5,12, 1,12, 2, 5, 2,-1, 6
 9, 2, 8, 1, 3, 5, 6, 2, 7, 9, 2, 1, 6, 8, 1, 2, 1, 5, 2, 2,12, 2, 4, 9, 2, 2, 4, 7, 4, 3, 6, 9, 6, 5,12, 2, 3
 1, 7, 2, 2, 5, 6,12, 6, 6,12,12, 2, 1, 2, 2, 7, 1, 1, 8, 3, 5, 2,12, 1, 8, 2, 6, 3, 2, 9, 3, 2, 4, 9, 8, 5, 3
 1, 3, 2, 1, 1, 6, 3,-1, 2, 4, 8, 7, 3, 4, 7, 6, 1, 9, 7, 2,12, 4, 6, 5, 7, 8, 2,12, 1, 2, 6, 7, 8, 2, 3,12, 9
3, 6, 4, 9, 2,12, 9, 8, 2, 7, 6, 6, 8, 3, 7, 9, 3, 7, 2, 2, 3, 2, 4, 5, 8, 7, 2,12,12, 4,12, 2,12,-1, 6,-1, 2
6, 4, 4,12, 8, 3, 2, 7, 3, 8, 4, 7, 3, 1, 5, 6, 2, 2, 2, 6, 2, 1, 4, 3, 1, 4, 2, 5, 7, 1, 6, 5,12, 7, 5,-1, 3
4, 8, 2, 2,12, 9, 3, 3, 8, 7, 7, 8,12, 6,12, 2, 4,12, 2,12, 7, 8, 7, 1, 9, 5,12, 4, 2, 2, 9, 7, 1, 8, 3, 8, 9
2, 2, 5, 1, 7, 1, 8, 2,12, 3,12, 5, 7, 9,12,12,12, 2, 4, 4, 2,12, 2, 2, 1, 6, 9,12, 7, 4, 6,12, 8, 4, 8, 2,12
3, 1, 2, 8, 1, 4, 7, 9, 3, 7, 3, 6, 6, 6, 3, 9, 9, 3, 9, 3, 3, 7, 5,12, 2, 8, 2, 2, 5, 4, 9, 8, 5, 3, 2, 6, 4
12, 1, 9, 5, 9, 2, 6,12, 3, 4,12,-1,12, 7, 9, 2, 1, 2, 2, 4, 6,12, 2, 2, 2, 3, 4, 1, 4, 4, 2, 4,12, 6, 2, 5, 6
0,0
36,36
end
```
The starting position is the top left corner and the finish position if the bottom right corner. The shortest path is going straight down all the way and then right all the way, so the solution will be displayed as:
```
Down (12) ,Down (13) ,Right (18) ,Down (24) ,Right (26) ,Down (28) ,Down (30) ,Down (31) ,Down (33) ,Down (34) ,Right (36) ,Down (38) ,Down (45) ,Down (49) ,Down (51) ,Down (55) ,Right (63) ,Right (65) ,Down (72) ,Right (74) ,Down (79) ,Down (81) ,Right (84) ,Right (86) ,Right (88) ,Down (91) ,Down (93) ,Down (96) ,Down (99) ,Right (103) ,Down (107) ,Down (109) ,Down (110) ,Down (113) ,Left (115) ,Down (117) ,Down (119) ,Right (128) ,Right (133) ,Down (134) ,Down (135) ,Down (137) ,Right (138) ,Right (140) ,Right (142) ,Up (143) ,Right (145) ,Right (146) ,Down (147) ,Down (148) ,Down (151) ,Down (153) ,Right (155) ,Right (157) ,Right (163) ,Right (165) ,Right (166) ,Right (170) ,Right (173) ,Down (174) ,Down (176) ,Right (177) ,Down (179) ,Down (181) ,Right (184) ,Right (188) ,Right (189) ,Right (193) ,Right (197) ,Right (199) ,Right (203) ,Right (215) ,Right (221) ,Right (223) ,Right (228) ,Right (234)
```
