Implemented a Graph ADT to explore path finding in mazes. 

I use an adjacency list to store edges between nodes. The maze consists of a grid, where each vertex is adjacent to the vertices directly, above, below, 
to the left and to the right. The search algorithm implemented is breadth first search (BFS). Given a start point and a target end point, the program 
finds the distance of the shortest path between them and reports the number of left, right, up and down steps taken in a specific format.

An input and output example for the following maze is given in test.in and test.out:
                                                              
           ################################                   
           #e.................e...........#                   
           ##############################.#                   
      #####       #.......#     ######  #.##        #####     
      #s..#########.......#######....# ##..#        #...#     
      #...#......##..................###...#####    #...#     
      #...#....................................######...#     
      #...#......######.................................#     
      #.......................s.......e.............#...#     
      #...................s..................#......#...#     
      #################...###########...................#     
                      #...#         ######...#......#####     
                      #####              #...########         
                                         #####                

The output follows the following format:
`number_explored path_length left_steps right_steps up_steps down_steps`

Where number_explored is the total number of nodes that were explored using the pathfinding algorithm,
path_length is the total length of the path,
left_steps is the number of left neighours followed,
right_steps is the number of right neighbors followed,
up_steps is the number of up neighbors followed,
down_steps is the number of down neighbors followed.
