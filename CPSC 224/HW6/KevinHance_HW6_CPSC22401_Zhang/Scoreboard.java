//	Kevin Andrew Hance
//	March 8th, 2018
//	CPSC 224: Object Oriented Programming (Zhang)
//	HW Assignment #5: Yahtzee
//
//  This subclass models the upper and lower parts of the Yahtzee scoreboard. Allows
//	for scores to be saved and bonuses to be applied to the scoreboard. Also has implementation
//	to print out possible categories to score in, and the final scoreboard with bonuses applied.

public class Scoreboard {
	
	private int[] upperSb;
	private int[] lowerSb;
	Hand h;
	
	
	public Scoreboard(int maxDieVal, Hand newHand) {
		// aces-sixes (or more), plus one element for 35 pt bonus
		upperSb = new int[maxDieVal + 1];
		// 3kind, 4kind, FH, SmStr, LgStr, Yhtz, Chance
		lowerSb = new int[7];
		// ensure all score values are initially set to zero
		for (int j = 0; j < upperSb.length; j++) {
			upperSb[j] = 0;
		}
		for (int i = 0; i < lowerSb.length; i++) {
			lowerSb[i] = 0;
		}
		h = newHand;
	}
	
	// add together and return all scores on upper scoreboard
	public int sumUpperScore() {
		int sum = 0;
		for(int i  : upperSb) {
			sum += i;
		}
		return sum;
	}

	// add together and return all scores on lower scoreboard
	public int sumLowerScore() {
		int sum = 0;
		for(int i  : lowerSb) {
			sum += i;
		}
		return sum;
	}
	
	// returns boolean representing whether or not the user has already scored in a specific category
	// in upper scoreboard
	public boolean isScoreEmptyUpper(int index) {
		return upperSb[index] == 0;
	}
	
	// returns boolean representing whether or not the user has already scored in a specific category
	// in lower scoreboard
	public boolean isScoreEmptyLower(int index) {
		return lowerSb[index] == 0;
	}
	
	//apply score to ones row
	public void acesScore() {
		int currentCount = 0;
		for (int diePosition = 0; diePosition < 5; diePosition++)
		{
			if (h.getDieVal(diePosition) == 1)
				currentCount++;
		}
		upperSb[0] = currentCount;
	}
	
	//apply score to twos row
	public void twosScore() {
		int currentCount = 0;
		for (int diePosition = 0; diePosition < 5; diePosition++)
		{
			if (h.getDieVal(diePosition) == 2)
				currentCount++;
		}
		upperSb[1] = currentCount;
	}
	
	//apply score to threes row
	public void threesScore() {
		int currentCount = 0;
		for (int diePosition = 0; diePosition < 5; diePosition++)
		{
			if (h.getDieVal(diePosition) == 3)
				currentCount++;
		}
		upperSb[2] = currentCount;
	}
	
	//apply score to fours row
	public void foursScore() {
		int currentCount = 0;
		for (int diePosition = 0; diePosition < 5; diePosition++)
		{
			if (h.getDieVal(diePosition) == 4)
				currentCount++;
		}
		upperSb[3] = currentCount;
	}
	
	//apply score to fives row
	public void fivesScore() {
		int currentCount = 0;
		for (int diePosition = 0; diePosition < 5; diePosition++)
		{
			if (h.getDieVal(diePosition) == 5)
				currentCount++;
		}
		upperSb[4] = currentCount;
	}
	
	//apply score to sixes row
	public void sixesScore() {
		int currentCount = 0;
		for (int diePosition = 0; diePosition < 5; diePosition++)
		{
			if (h.getDieVal(diePosition) == 6)
				currentCount++;
		}
		upperSb[5] = currentCount;
	}
	public void bigDieScore(int dieVal) {
		int currentCount = 0;
		for (int diePosition = 0; diePosition < 5; diePosition++)
		{
			if (h.getDieVal(diePosition) == dieVal)
				currentCount++;
		}
		upperSb[dieVal-1] = currentCount;
	}
	
	//apply 35pt bonus for having over 63 points in upper scoreboard
	public void applyUpperBonus() {
		int sum = 0;
		for (int i : upperSb)
			sum += i;
		if(sum >= 63)
			upperSb[upperSb.length-1] = 35;
	}
	
	//apply score to ones row
	public void threeOfaKindScore() {
		if (maxOfAKindFound(h) >= 3)
			lowerSb[0] = totalAllDice(h);
	}
	
	//apply score to ones row
	public void fourOfaKindScore() {
		if (maxOfAKindFound(h) >= 3)
			lowerSb[1] = totalAllDice(h);
	}
	
	//apply score to ones row
	public void fullHouseScore() {
		if (fullHouseFound(h))
			lowerSb[2] = 25;
	}
	
	//apply score to ones row
	public void smStraightScore() {
		if (maxStraightFound(h) >= 4)
			lowerSb[3] = 30;
	}
	
	//apply score to large straight row
	public void lgStrightScore() {
		if (maxStraightFound(h) >= 5)
			lowerSb[4] = 40;
	}
	
	//apply score to yahtzee row
	public void yahtzeeScore() {
		if (maxOfAKindFound(h) >= 5)
			lowerSb[5] += 50;
	}
	
	//apply score to chance row
	public void chanceScore() {
		lowerSb[6] = totalAllDice(h);
	}
	
	//apply 50pt bonus for each second, third, fourth, etc. yahtzees
	public void applyYahtzeeBonus() {
		int bonus = (((lowerSb[5] / 50) - 1) * 50);
		lowerSb[7] = bonus;
	}
	
	public void printScoreboard(int maxDieValue, Hand h)
	{
		//upper scorecard
		//all die
		for (int dieValue = 1; dieValue <= maxDieValue; dieValue++)
		{
			int currentCount = 0;
			for (int diePosition = 0; diePosition < 5; diePosition++)
			{
				if (h.getDieVal(diePosition) == dieValue)
					currentCount++;
			}
			System.out.print("Enter " + dieValue + " to score " + dieValue * currentCount + " on the ");
			System.out.println(dieValue + " line");
		}
		
		
		//lower scorecard
		//3 of a kind
		if (maxOfAKindFound(h) >= 3)
		{
			System.out.print("Enter A to score " + totalAllDice(h) + " on the ");
			System.out.print("3 of a Kind line\n");
		}
		else System.out.print("Enter A to score 0 on the 3 of a Kind line\n");
		
		//4 of a kind
		if (maxOfAKindFound(h) >= 4)
		{
			System.out.print("Enter B to score " + totalAllDice(h) + " on the ");
			System.out.print("4 of a Kind line\n");
		}
		else System.out.print("Enter B to score 0 on the 4 of a Kind line\n");

		//full house
		if (fullHouseFound(h))
			System.out.print("Enter C to score 25 on the Full House line\n");
		else
			System.out.print("Enter C to score 0 on the Full House line\n");
		
		//small straight
		if (maxStraightFound(h) >= 4)
			System.out.print("Enter D to score 30 on the Small Straight line\n");
		else
			System.out.print("Enter D to score 0 on the Small Straight line\n");
		
		//large straight
		if (maxStraightFound(h) >= 5)
			System.out.print("Enter E to score 40 on the Large Straight line\n");
		else
			System.out.print("Enter E to score 0 on the Large Straight line\n");

		//yahtze
		if (maxOfAKindFound(h) >= 5)
			System.out.print("Enter F to score 50 on the Yahtzee line\n");
		else
			System.out.print("Enter F to score 0 on the Yahtzee line\n");

		//chance
		System.out.print("Enter G to score " + totalAllDice(h) + " on the ");
		System.out.print("Chance line\n");
	}
	
	// prints out all scores, bonuses, subtotals and grand total
	public void printFinalScore() {
		System.out.println("Aces:\t\t" + upperSb[0]);
		System.out.println("Twos:\t\t" + upperSb[1]);
		System.out.println("Threes:\t\t" + upperSb[2]);
		System.out.println("Fours:\t\t" + upperSb[3]);
		System.out.println("Fives:\t\t" + upperSb[4]);
		System.out.println("Sixes:\t\t" + upperSb[5]);
		System.out.println("Upper Bonus:\t\t" + upperSb[h.getMaxDieValue()]);
		System.out.println("\nUpper Total:\t\t" + sumUpperScore());
		
		System.out.println("3 of a kind:\t" + lowerSb[0]);
		System.out.println("4 of a kind:\t" + lowerSb[1]);
		System.out.println("Full House:\t" + lowerSb[2]);
		System.out.println("Small Straight:\t" + lowerSb[3]);
		System.out.println("Large Straight:\t" + lowerSb[4]);
		System.out.println("Yahtzee:\t\t" + lowerSb[5]);
		System.out.println("Chance:\t\t" + lowerSb[6]);
		System.out.println("Yahtzee Bonus:\t" + lowerSb[7]);
		System.out.println("\nLower Total:\t" + sumLowerScore());
		System.out.println("\nGrand Total:\t" + (sumUpperScore() + sumLowerScore()));
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
