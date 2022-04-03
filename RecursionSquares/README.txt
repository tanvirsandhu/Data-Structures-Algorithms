This program generates graphics patterns procedurally, specifically one for squares. 

I read from stdin and input should consist of:
  -dimension of image - 2 integers, representing width (number of columns) and height (number of rows). Coordinates of points on the image are 0..W-1, 
  0..H-1. The origin is at the top left corner.
  -recursive depth - an integer,
  -fraction - a double (between 0 and 1),
  -starting point - 2 doubles (x and y coordinates),
  -ending point - 2 doubles (x and y coordinates).
  
Therefore, input should look like: 
512 512 20 0.1 50.0 460.0 460.0 460.0

There is an example of input and output within the file.
