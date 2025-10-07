//	Kevin Andrew Hance
//	January 25th, 2018
//	Object Oriented Programming
//	HW Assignment #1: Anagram Check
//
//  This program compares any two strings (consisting only of alphanumeric characters and spaces), then
//  outputs whether or not the two strings are anagrams of each other. The program begins by prompting
//  user for two strings, then converts them into character arrays, which allows us to compare the size
//  and contents of the two strings in a simple and organized manner. If one of the two strings contains
//  the character '!', the program quits and says "Goodbye".

import java.util.*;
import java.util.Arrays;


public class AnagramCheck {
	
	public static void main (String[] args) {
		
		//initialization
		
		Scanner console = new Scanner(System.in);
		String str1;
		String str2;
		boolean sentinel = true;
		boolean isAnagramBool;
		
		//loop w/ sentinel value
		
		while(sentinel) {
			System.out.println("Enter \"!\" into either prompt to quit.");
			System.out.println("Please type in any phrase (alphanumerics and spaces only) and press Enter:");
			str1 = console.nextLine();
			System.out.println("Please type in another phrase and press Enter:");
			str2 = console.nextLine();
			
			//quit if requested
			
			if(str2.contains("!") || str1.contains("!"))
			{
				//user has requested to quit, say goodbye
				System.out.println("Goodbye, thanks for using my program!");
				return;
			}
			
			//check strings & output result
			
			isAnagramBool = isAnagram(str1, str2);
			if(isAnagramBool)
			{
				System.out.println(str1 + " is anagram of " + str2 + ".");
				
			} 
			
			else
			{
				System.out.println(str1 + " is not anagram of " + str2 + ".");
			}
		}
	}
	
	public static boolean isAnagram(String str1, String str2)
	{
		//Step 1: remove white spaces
		String modStr1 = str1.replace(" ", "");
		String modStr2 = str2.replace(" ", "");
		
		//Step 2: all lowercase
		modStr1 = modStr1.toLowerCase();
		modStr2 = modStr2.toLowerCase();
		
		//Step 3: convert String to charArray
		char[] str1Arr = modStr1.toCharArray();
		char[] str2Arr = modStr2.toCharArray();
		
		//Step 4: sort both charArrays
		Arrays.sort(str1Arr);
		Arrays.sort(str2Arr);
		
		//Step 5: compare size of both arrays
			
			//if size str1 equals size str2
			if(str1Arr.length == str2Arr.length)
			{
				
				//iterate through both arrays, return false if any
				for(int i = 0; i < str1Arr.length; i++)
				{
					
					//if two elements at a given index dont match, return false
					if(str1Arr[i] != str2Arr[i]) 
					{
						return false;
					}
					
				}
				
				//if we reach the end of this loop, return true, they're equal
				return true;
			}
			
			else
			{
				// if arrays are different lengths, they aren't anagrams
				return false;
			}
		
				
	}
	
}