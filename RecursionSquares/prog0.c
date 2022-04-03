//Tanvir Sandhu (taksandh@ucsc.edu)
//Program 0, CSE 101
//October 3, 2021
//ID #1721309

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <string.h>

//square function created to carry out the mathematics and recursion//
void squares(cairo_t *cr, int p1_x, int p1_y, int p2_x, int p2_y, int height, int width, int depth, double fraction) 
{
	//As long as the amount of squares requested has not been reached, this if statement will carry out the math of finding the slope and points
	//of the next line
	if (depth >= 0) 
	{
		//each time the next square is being drawn, height and width are adjusted to be the size that will fit by subtracting the first point
		//of each coordinate from the second 
		int height = (p2_y - p1_y);
		int width = (p2_x - p1_x);
		//the new line will then have the end point of the new height and width added to the original point
		int p3_x = p2_x + height;
		int p3_y = p2_y - width;
		int p4_x = p3_x - width;
		int p4_y = p3_y - height;
		//moved to new point and drawing the new line using the points discovered above.
		cairo_move_to(cr, p1_x, p1_y);
		cairo_line_to(cr, p2_x, p2_y);
		cairo_line_to(cr, p3_x, p3_y);
		cairo_line_to(cr, p4_x, p4_y);
		cairo_line_to(cr, p1_x, p1_y);
		//calculating the slope of the next line using the fraction given and the formula 
		p1_x = p1_x + (fraction * width);
		p1_y = p1_y + (fraction * height);
		p2_x = p2_x + (fraction * height);
		p2_y = p2_y - (fraction * width);
		//each time a square is created, we will subtract one from the depth counter to make sure that the amount of squares is correct
		depth = depth - 1;
		//call the squares function over and over untill all requested squares have printed.
		squares(cr, p1_x, p1_y, p2_x, p2_y, height, width, depth, fraction);
	}
	//changing brush color to pink :)//
	cairo_set_source_rgb(cr, 0.95, 0.715, 0.925); 
        cairo_set_line_width(cr, 1.0);
        cairo_stroke(cr);
}

//the main function to read the input and create the square png that will be the output 
int main(void) 
{
	//creating variables to store file contents
	char file_name[20];
        char png[20] = ".png";
        int canvas_width = 0;
        int canvas_height = 0;
        int depth = 0;
        double fraction = 0.0;
        double p1_x = 0.0;
        double p1_y = 0.0;
        double p2_x = 0.0;
        double p2_y = 0.0;
	
	//reads input and places the given values into the appropriate variables to use in the squares function
	scanf("%s %d %d %d %lf %lf %lf %lf %lf", file_name, &canvas_width, &canvas_height, &depth, &fraction, &p1_x, &p1_y, &p2_x, &p2_y);
	//combining file output name and ".png" into one string to create appropriate file name
	strcat(file_name, png);
	
	//adjusting the height and width as above
	int height = p2_y - p1_y;
        int width = p2_x - p1_x;

	//professor provided startup code 
	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, canvas_width, canvas_height);
	cairo_t *cr = cairo_create(surface);
	//setting background to white
	cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_rectangle(cr, 0, 0, canvas_width, canvas_height);
        cairo_fill(cr);
	
	//calls recursive function
	squares(cr, p1_x, p1_y, p2_x, p2_y, height, width, depth, fraction);
	
	//professor provided png output code
	cairo_destroy(cr);
        cairo_surface_write_to_png(surface, file_name);
        cairo_stroke(cr);
}

