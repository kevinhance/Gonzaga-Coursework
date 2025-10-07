//	Kevin Andrew Hance
//	February 7th, 2018
//	Object Oriented Programming
//	HW Assignment #3: Container
//
//  This program creates an array full of integers in "data.txt". Integers i and j are indexes
//	of 2 different elements in the array. Then, using the integers in the array at elements i and
//	j, the program finds the maximum container size (height * width). Height is defined as the
//	minimum of the two values being compared. Width is defined as j minus i. After trying every
//	possible combination of i, j, ai, and aj where i < j, the program will output the maximum
//	container area using the algorithm described above.

import java.util.*;
import java.io.*;

public class Container {

	public static void main (String[] args) throws FileNotFoundException {
		
		String 	filename = "data.txt";
		int 	filesize = 0;
		int[]	pointsFromFile;
		int 	area = -1;
		
		System.out.print("Reading file \"" + filename + "\"");
		Scanner filescanner = new Scanner(new File(filename));
		
		while(filescanner.hasNextInt()) {
			filesize++;
			filescanner.nextInt();
			System.out.print(".");
		}
		
		System.out.print("\nNumber of Elements: " + filesize + "\nPopulating array");
		
		// filesize now contains the size of the array we want
		pointsFromFile = new int[filesize];
		
		// close filescanner and re-open it to get to the beginning
		filescanner.close();
		filescanner = new Scanner(new File(filename));
		
		// populate the int array with values from our data.txt file
		for(int i = 0; filescanner.hasNextInt(); i++) {
			pointsFromFile[i] = filescanner.nextInt();
			System.out.print(".");
		}
		
		
		// now, the array can be passed into MaxContainer to find the max area
		// close the scanner to avoid memory issues
		filescanner.close();
		
		// before we call MaxContainer(), we ensure that the array has at least 2 elements in it
		if (filesize <= 0) {
			System.out.println("\nOperation can not be performed on an empty array.");
		} else if (filesize == 1) {
			System.out.println("\nOperation can not be performed with only one element in array.");
		} else {
			area = MaxContainer(pointsFromFile);
		}
		
		// if the original area variable wasn't changed by the else statement above,
		// this statement will not be entered.
		if(area >= 0) {
			System.out.println("\nMaximum area of container: " + area);
		}
		
	}
	
	public static int MaxContainer(int[] points) {
		
		// initializing variables
		int currentArea = 0;
		int maxArea = 0;
		int height;
		int width;
		
		for(int i = 0; i < points.length-1; i++) {
			for(int j = i+1; j < points.length; j++) {
				// set height of container to the minimum of ai and aj
				height = Math.min(points[i], points[j]);
				
				// set width of container to the difference between j and i
				// because j starts at i + 1 and reaches the end of points[]
				// before i increments by 1, j will always be greater than i.
				width = j - i;
				currentArea = (height * width);
				
				// update maxArea if necessary
				if(currentArea > maxArea) {
					maxArea = currentArea;
				}
			}
		}
		return maxArea;
	}
}