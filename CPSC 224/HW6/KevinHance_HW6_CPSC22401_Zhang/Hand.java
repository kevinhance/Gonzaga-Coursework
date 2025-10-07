//	Kevin Andrew Hance
//	March 8th, 2018
//	CPSC 224: Object Oriented Programming (Zhang)
//	HW Assignment #5: Yahtzee
//
//  This subclass models the data fields and behavior for one hand of dice. Multiple constructors
//	are used to allow the user to specify the number of dice in a hand or use the default 5-die
//	hand. Subclass can also re-roll dice, sort, and print hand to console. Getters are included,
//	but due to the nature of the game, setters are not included. Value of dice can only be changed
//	through re-rolling hand.

import java.util.*;

public class Hand {
	
	private int maxDieValue;
	private int handSize;
	private ArrayList<Die> handList = new ArrayList<Die>();
	
	//default constructor assumes 5 dice in a hand
	public Hand()
	{
		handSize = 5;
		maxDieValue = 6;
		for(int i = 0; i < handSize; i++)
			handList.add(new Die(maxDieValue));
		
	}
	
	//this constructor takes in an int parameter as the # of dice
	public Hand(int size, int maxDieValue)
	{
		handSize = size;
		for(int i = 0; i < handSize; i++)
			handList.add(new Die(maxDieValue));
	}
	
	//takes in a string as a parameter and re-rolls dice in hand based on contents of string
	public  void rollDice(String keep)
	{
		for(int i = 0; i < handSize; i++)
		{
			if(keep.charAt(i) == 'n')
			{
				handList.set(i, new Die());
			}
		}
	}
	
	//prints hand in the following format:	5 2 4 1 5
	public void printHand()
	{
		for(int i = 0; i < handSize; i++)
		{
			System.out.print(handList.get(i).getDieVal() + " ");
		}
		System.out.println();
	}
	
	//returns reference to the specified Die
	public  Die getDie(int dieNumber)
	{
		return handList.get(dieNumber);
	}
	
	//returns int value of the specified Die
	public int getDieVal(int dieNumber)
	{
		return handList.get(dieNumber).getDieVal();
	}
	
	//sorts hand from least to greatest value
	public void sortHand()
	{
		Collections.sort(handList);
	}
	
	// getter
	public int getHandSize() {
		return handSize;
	}
	// setter
	public int getMaxDieValue() {
		return maxDieValue;
	}
}
