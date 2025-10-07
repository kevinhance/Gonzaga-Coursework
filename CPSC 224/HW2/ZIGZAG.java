// CPSC 224-01, Spring 2018
// Programming Assignment #2 (Zig-Zag Conversion)
// @author Kevin Hance
// @version v1.0 1/31/18

import java.util.*;

public class ZIGZAG {
	public static void main (String[] args) {
		
		Scanner console = new Scanner(System.in);
		
		while(true) {
			
			// Ask for string and save response
			System.out.print("Please enter a string (alphanumeric characters only): ");
			String inputStr = console.nextLine();
			
			// Ask for # of rows and save response
			System.out.println("To quit program, enter zero or any negative integer");
			System.out.print("Please enter desired number of rows(integer values only): ");
			int rowCount = console.nextInt();
			
			// this is a rudimentary exit procedure that also solves the issue of invalid negative row input
			if(rowCount < 1) {
				System.out.println("Goodbye, thanks for using my program!");
				console.close();
				return;
			}
			
			// call ZIGZAG_CONVERSION
			String output = ZIGZAG_CONVERSION(inputStr, rowCount);
			System.out.println("\nYour converted string: " + output);
		}
		
		
		
	}
	
	public static String ZIGZAG_CONVERSION (String inputStr, int rowCount) {
		
		// convert input string into upper-case character array
		inputStr = inputStr.replace(" ", "");
		char[] inputArr = (inputStr.toUpperCase()).toCharArray();
		char[] outputArr = new char[inputStr.length()];
		
		
		// 2D array of arrays, with each inner-array representing 1 row
		char[][] masterArr = new char[rowCount][inputStr.length()];
		
		// fill 2D array with hyphens, so we know when to ignore an element in the final step
		for(int i = 0; i < rowCount; i++) {
			for(int j = 0; j < inputStr.length(); j++) {
				masterArr[i][j] = '-';
			}
		}
		
		// put the characters into their correct place within the 2D array
		
		// if rowCount is even, this code is called
		if(rowCount % 2 == 0) { // if rowCount is even, 
			for(int i = 0; i < inputArr.length; i++) {
				masterArr[i % rowCount][i] = inputArr[i];
			}
		}
		
		// if rowCount is odd, this code is called
		else if(rowCount % 2 == 1) {
			// mid index is the index at which we place the characters after filling one column of the zig-zag
			int midIndex = rowCount / 2;
			
			// midValCount allows us to use i as an indicator of which row we need to put the character into
			// without modifying the natural increments of the for-loop
			int midValCount = 0;
			
			for(int i = 0; i < inputArr.length; i++) {
				if(i % (rowCount + 1) != rowCount) {
					masterArr[(i - midValCount) % rowCount][i] = inputArr[i];
				} else {
					// this is where we place the character in the row specified by the "midIndex"
					// we also increment midValCount by one to keep the modulo expression above working correctly
					masterArr[midIndex][i] = inputArr[i];
					midValCount++;
				}
			}
		}
		
		// create a variable to keep track of where we are in the final output array
		int outputIndex = 0;
		
		// iterate through the 2D array and place characters into the output array
		for(int i = 0; i < rowCount; i++) {
			for(int j = 0; j < inputStr.length(); j++) {
				if(masterArr[i][j] != '-') {
					outputArr[outputIndex] = masterArr[i][j];
					outputIndex++;
				}
			}
		}
		
		// convert outputArr into a String and return that string
		String outputStr = arrayToString(outputArr);
		return outputStr;
	}
	
	// this is a helper function used to convert a 1-dimensional character Array into a String without any
	// extra characters such as '[' or ','
	public static String arrayToString(char[] charArr) {
		String outputStr = "";
		for(char c: charArr) {
			if(c != '-') {
				outputStr = outputStr + c;
			}
		}
		return outputStr;
	}
}
