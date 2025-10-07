/**LowerScoreBoard.java
 * 
 * This program implements the lower score board in
 * Yahtzee as an object for easy of use
 * 
 * CPSC 224_01, Spring 2018
 * Assignment 5
 * @author Zach McKee
 * @version 1.5 3/22/2018
 */
public class LowerScoreBoard {
	private int[] scoreLines; /* scoreLines[0] = 3 of a Kind score
							   * scoreLines[1] = 4 of a Kind score
							   * scoreLines[2] = Full House score
							   * scoreLines[3] = Small Straight score
							   * scoreLines[4] = Large Straight score
							   * scoreLines[5] = Yahtzee score
							   * scoreLines[6] = Chance score
							   */
	
	private final int LOWER_LINES = 7;
	private int MAX_DIE_VALUE;
	private boolean[] linesTaken;
	
	public LowerScoreBoard(Hand h) {
		scoreLines = new int[LOWER_LINES];
		calculateLowerScore(h);
		MAX_DIE_VALUE = h.getMaxDieValue();
		linesTaken = new boolean[7];
		for(int i = 0; i < 7; i++)
			linesTaken[i] = h.checkLineTaken(i + MAX_DIE_VALUE);
	}
	
	/**
	 * calculateLowerScore()
	 * This method goes through Hand h and calculates the whole lower score card.
	 * Stores all the scores in scoreLines according to the key above.
	 * @param h
	 */
	public void calculateLowerScore(Hand h) {
		if(maxOfAKindFound(h) >= 3)
			scoreLines[0] = totalAllDice(h);
		else
			scoreLines[0] = 0;
		
		if(maxOfAKindFound(h) >= 4)
			scoreLines[1] = totalAllDice(h);
		else
			scoreLines[1] = 0;
		
		if(fullHouseFound(h))
			scoreLines[2] = 25;
		else
			scoreLines[2] = 0;
		
		if(maxStraightFound(h) >= (h.getHandSize() - 1))
			scoreLines[3] = 30;
		else
			scoreLines[3] = 0;
		
		if(maxStraightFound(h) >= (h.getHandSize()))
			scoreLines[4] = 40;
		else
			scoreLines[4] = 0;
		
		if(maxOfAKindFound(h) >= (h.getHandSize()))
			scoreLines[5] = 50;
		else
			scoreLines[5] = 0;

		scoreLines[6] = totalAllDice(h);
	}
	
	/**
	 * maxStraightFound()
	 * This method looks through Hand h and returns the largest
	 * straight found in int maxLength
	 * @param h
	 * @return maxLength
	 */
	private static int maxStraightFound(Hand h) {
		int maxLength = 1;
		int currentLength = 1;
		for(int i = 0; i < h.getHandSize() - 1; i++) {
			if(h.getDieValueAt(i) + 1 == h.getDieValueAt(i + 1)) 
				currentLength++;
			else if (h.getDieValueAt(i) + 1 < h.getDieValueAt(i + 1)) 
				currentLength = 1;
			if(currentLength > maxLength)
				maxLength = currentLength;
		}
		return maxLength;
	}
	
	/**
	 * maxOfAKindFound()
	 * This method looks through Hand h and finds returns the largest
	 * of a Kind found in int maxStreak
	 * @param h
	 * @return maxStreak
	 */
	private int maxOfAKindFound(Hand h) {
		int maxStreak = 0; 
		int currentStreak;
		for(int currentDieValue = 0; currentDieValue <= 6; currentDieValue++) {
			currentStreak = 0;
			for(int i = 0; i < h.getHandSize(); i++) {
				if(h.getDieValueAt(i) == currentDieValue)
					currentStreak++;
			}
			if(currentStreak > maxStreak) {
				maxStreak = currentStreak;
			}
		}
		return maxStreak;
	}
	
	/**
	 * totalAllDice()
	 * This method looks through Hand h and returns the total
	 * of all the dice in int total
	 * @param h
	 * @return total
	 */
	private int totalAllDice(Hand h) {
		int total = 0;
		for(int i = 0; i < h.getHandSize(); i++) {
			total += h.getDieValueAt(i);
		}
		return total;
	}
	
	/**
	 * fullHouseFound()
	 * This method looks through Hand h and returns true
	 * if there is a full house, else returns false
	 * @param h
	 * @return foundFH
	 */
	private boolean fullHouseFound(Hand h) {
		int maxDieValue = h.getMaxDieValue();
		boolean found3k = false;
		boolean foundFH = false;
		int currentStreak;
		int currentNumbers = 0; //Checks how many different numbers there are.
		int lastNumber = 0;		//For a full house, there should only be two different numbers, plus a three of a kind
		for(int currentDieValue = 1; currentDieValue <= maxDieValue; currentDieValue++) {
			currentStreak = 0;
			if((currentDieValue < h.getHandSize()) && (h.getDieValueAt(currentDieValue - 1) != lastNumber)) {
				currentNumbers++; //Increments how many diffrent numbers there are in the hand
				lastNumber = h.getDieValueAt(currentDieValue - 1);
			}
			for(int i = 0; i < h.getHandSize(); i++) {
				if(h.getDieValueAt(i) == currentDieValue)
					currentStreak++;
			}
			if(currentStreak == 3)
				found3k = true;
		}
		if((currentNumbers == 2) && found3k) {
			foundFH = true;
		}
		return foundFH;
	}
	
	/**
	 * toString()
	 * This method converts a LowerScoreBoard object into a String format
	 * @return String form of LowerScoreBoard
	 */
	public String toString() {
		StringBuilder build = new StringBuilder();
		build.append("Your lower scorecard:\n");
		if(linesTaken[0] == false)
			build.append((MAX_DIE_VALUE + 1) + ": Score " + scoreLines[0] + " on the 3 of a Kind line\n");
		if(linesTaken[1] == false)
			build.append((MAX_DIE_VALUE + 2) + ": Score " + scoreLines[1] + " on the 4 of a Kind line\n");
		if(linesTaken[2] == false)
			build.append((MAX_DIE_VALUE + 3) + ": Score " + scoreLines[2] + " on the Full House line\n");
		if(linesTaken[3] == false)
			build.append((MAX_DIE_VALUE + 4) + ": Score " + scoreLines[3] + " on the Small Straight line\n");
		if(linesTaken[4] == false)
			build.append((MAX_DIE_VALUE + 5) + ": Score " + scoreLines[4] + " on the Large Straight line\n");
		if(linesTaken[5] == false)
			build.append((MAX_DIE_VALUE + 6) + ": Score " + scoreLines[5] + " on the Yahtzee line\n");
		if(linesTaken[6] == false)
			build.append((MAX_DIE_VALUE + 7) + ": Score " + scoreLines[6] + " on the Chance line\n");
		return build.toString();
	}
	
	/**
	 * getScoreAt()
	 * This method returns the score at a specific line
	 * @param index
	 * @return scoreLines at line index
	 */
	public int getScoreAt(int index) {
		return scoreLines[index];
	}
}
