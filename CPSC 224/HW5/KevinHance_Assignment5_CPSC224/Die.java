//	Kevin Andrew Hance
//	March 8th, 2018
//	CPSC 224: Object Oriented Programming (Zhang)
//	HW Assignment #5: Yahtzee
//
//  This subclass models the data fields and behavior for one die. Multiple constructors
//	are used to allow dice to be initialized to the default 6-sided die, or a specified
//	number of sides (ex. D4, D10, D20). While the class allows dice to be initialized to
//	have any number of sides, Yahtzee.java may not handle straights and full houses
//	correctly with dice that aren't 6-sided.

import java.util.*;

public class Die implements Comparable {

	private int dieVal = 1;
	private Random r = new Random();
	static int maxDieVal;
	
	//default constructor assumes a 6-sided die
	public Die()
	{
		maxDieVal = 6;
		dieVal = r.nextInt(6) + 1;
	}
	
	//this constructor takes in an int parameter as the # of sides on the die
	public Die(int sides)
	{
		maxDieVal = sides;
		dieVal = r.nextInt(maxDieVal) + 1;
	}
	
	//return die value as an int
	public int getDieVal()
	{
		return dieVal;
	}
	
	//implements comparable interface for sorting
	public int compareTo(Object otherObj) {
		Die otherDie = (Die) otherObj;
		
		if(this.dieVal > otherDie.getDieVal())
			return 1;
		else if (this.dieVal == otherDie.getDieVal())
			return 0;
		else
			return -1;
	}		
}
