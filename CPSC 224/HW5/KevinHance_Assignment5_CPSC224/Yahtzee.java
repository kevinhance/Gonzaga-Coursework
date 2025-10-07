//	Kevin Andrew Hance
//	March 8th, 2018
//	CPSC 224: Object Oriented Programming (Zhang)
//	HW Assignment #5: Yahtzee
//
//  This program emulates the popular dice game, Yahtzee. The program rolls 5 dice for the user,
//	displays the output, then allows 2 more chances to re-roll undesired dice before showing the
//	user what their options are for scoring in Yahtzee with that specific hand of dice.


import java.io.*;
import java.util.*;
import java.time.*;

public class Yahtzee {
	
	static int handSize = 5;
	static int maxDieValue = 6;
	static Random rand = new Random();
	static Hand h = new Hand(handSize);
	Scoreboard scr = new Scoreboard(maxDieValue);
	Scanner s = new Scanner(System.in);
	
	
	public static void main(String args[]) {
		
		char playAgain = 'y';
		Scanner s = new Scanner(System.in);
		
		while (playAgain == 'y')
		{
			String keep = "nnnnn"; //setup to roll all dice in the first roll
			int turn = 1;
			while (turn < 4 && !keep.equals("yyyyy"))
			{
				//roll dice not kept
				h.rollDice(keep);
				//output roll
				System.out.print("Your roll was: ");
				h.printHand();
				//if not the last roll of the hand prompt the user for dice to keep
				if (turn < 3)
				{
					System.out.print("enter dice to keep (y or n) ");
					keep = s.nextLine();
				}
				System.out.println();
				turn++;
			}
			
			//start scoring
			//hand needs to be sorted to check for straights
			h.sortHand();
			
			//output sorted hand
			System.out.print("Here is your sorted hand : ");
			h.printHand();
			
			//upper scorecard
			
			//all die
			for (int dieValue = 1; dieValue <=maxDieValue; dieValue++)
			{
				int currentCount = 0;
				for (int diePosition = 0; diePosition < 5; diePosition++)
				{
					if (h.getDieVal(diePosition) == dieValue)
						currentCount++;
				}
				System.out.print("Score " + dieValue * currentCount + " on the ");
				System.out.println(dieValue + " line");
			}
			
			
			//lower scorecard
			
			//3 of a kind
			if (maxOfAKindFound(h) >= 3)
			{
				System.out.print("Score " + totalAllDice(h) + " on the ");
				System.out.print("3 of a Kind line\n");
			}
			else System.out.print("Score 0 on the 3 of a Kind line\n");
			
			//4 of a kind
			if (maxOfAKindFound(h) >= 4)//where i left off TODO
			{
				System.out.print("Score " + totalAllDice(h) + " on the ");
				System.out.print("4 of a Kind line\n");
			}
			else System.out.print("Score 0 on the 4 of a Kind line\n");

			//full house
			if (fullHouseFound(h))
				System.out.print("Score 25 on the Full House line\n");
			else
				System.out.print("Score 0 on the Full House line\n");
			
			//small straight
			if (maxStraightFound(h) >= 4)
				System.out.print("Score 30 on the Small Straight line\n");
			else
				System.out.print("Score 0 on the Small Straight line\n");
			
			//small straight
			if (maxStraightFound(h) >= 5)
				System.out.print("Score 40 on the Large Straight line\n");
			else
				System.out.print("Score 0 on the Large Straight line\n");

			//large straight
			if (maxOfAKindFound(h) >= 5)
				System.out.print("Score 50 on the Yahtzee line\n");
			else
				System.out.print("Score 0 on the Yahtzee line\n");

			//chance
			System.out.print("Score " + totalAllDice(h) + " on the ");
			System.out.print("Chance line\n");
			
			//prompt for another turn
			System.out.print("\nEnter 'y' to play again ");
			playAgain = (char) s.nextLine().charAt(0);
		}
		s.close();
	}
	
	public static int rollDie()
	//this function simulates the rolling of a single die
	{
	    int roll = rand.nextInt(5) + 1 ;
	    return roll;
	}
	public static int maxOfAKindFound(Hand hand)
	//this function returns the count of the die value occurring most in the hand
	//but not the value itself
	{
	    int maxCount = 0;
	    int currentCount ;
	    for (int dieValue = 1; dieValue <=6; dieValue++)
	    {
	        currentCount = 0;
	        for (int diePosition = 0; diePosition < 5; diePosition++)
	        {
	            if (hand.getDieVal(diePosition) == dieValue)
	                currentCount++;
	        }
	        if (currentCount > maxCount)
	            maxCount = currentCount;
	    }
	    return maxCount;
	}
	public static int totalAllDice(Hand hand)
	//this function returns the total value of all dice in a hand
	{
	    int total = 0;
	    for (int diePosition = 0; diePosition < 5; diePosition++)
	    {
	        total += hand.getDieVal(diePosition);
	    }
	    return total;
	}
	/*public static void sortArray(int array[], int size)
	//bubble sort from  Gaddis chapter 8
	{
	   boolean swap;
	   int temp;

	   do
	   {
	      swap = false;
	      for (int count = 0; count < (size - 1); count++)
	      {
	         if (array[count] > array[count + 1])
	         {
	            temp = array[count];
	            array[count] = array[count + 1];
	            array[count + 1] = temp;
	            swap = true;
	         }
	      }
	   } while (swap);
	}*/
	public static int maxStraightFound(Hand hand)
	//this function returns the length of the longest
	//straight found in a hand
	{
	    int maxLength = 1;
	    int curLength = 1;
	    for(int counter = 0; counter < 4; counter++)
	    {
	        if (hand.getDieVal(counter) + 1 == hand.getDieVal(counter + 1) ) //jump of 1
	            curLength++;
	        else if (hand.getDieVal(counter) + 1 < hand.getDieVal(counter + 1)) //jump of >= 2
	            curLength = 1;
	        if (curLength > maxLength)
	            maxLength = curLength;
	    }
	    return maxLength;
	}
	public static boolean fullHouseFound(Hand hand)
	//this function returns true if the hand is a full house
	//or false if it does not
	{
	    boolean foundFH = false;
	    boolean found3K = false;
	    boolean found2K = false;
	    int currentCount ;
	    for (int dieValue = 1; dieValue <=6; dieValue++)
	    {
	        currentCount = 0;
	        for (int diePosition = 0; diePosition < 5; diePosition++)
	        {
	            if (hand.getDieVal(diePosition) == dieValue)
	                currentCount++;
	        }
	        if (currentCount == 2)
	            found2K = true;
	        if (currentCount == 3)
	            found3K = true;
	    }
	    if (found2K && found3K)
	        foundFH = true;
	    return foundFH;
	}
}