LOOP- THE - LOOP

Solution:

--. Enter -1 value for empty cells.

--. The edge number should be equal to total number of edges needed to form a single loop.

--. Enter space-separated edge-pairs.

Input problem matrix

2

2

2

2


Insert total number of edges that is needed to solve the problem:
//Solve the problem in paper and count the number of egdes.

8

Enter space separated source node and destiation node value  
Vertex value starts from 0  
//Edge pair should be inputed in sequential manner, i.e. as we solve the problem in game.

//For the below example we start from vertex 0 and go step by step to its adjecent vertices.

0  1 -> edge from vertex 0 to vertex 1

1  2 -> edge from vertex 1 to vertex 2

2  5 -> edge from vertex 2 to vertex 5

5  8 -> edge from vertex 5 to vertex 8

8  7 -> edge from vertex 8 to vertex 7

7  6 -> edge from vertex 7 to vertex 6

6  3 -> edge from vertex 6 to vertex 3  

3  0 -> edge from vertex 3 to vertex 0


//Print the adjecent list


Adjacency list of vertex: 0 head-> 3-> 1

Adjacency list of vertex: 1 head-> 2-> 0

Adjacency list of vertex: 2 head-> 5-> 1

Adjacency list of vertex: 3 head-> 0-> 6

Adjacency list of vertex: 4 head

Adjacency list of vertex: 5 head-> 8-> 2

Adjacency list of vertex: 6 head-> 3-> 7

Adjacency list of vertex: 7 head-> 6-> 8

Adjacency list of vertex: 8 head-> 7-> 5

//Final solution

Your solution is correct.
