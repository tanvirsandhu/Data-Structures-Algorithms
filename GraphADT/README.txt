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
