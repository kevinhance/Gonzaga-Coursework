/**UpperScoreBoard.java
 * 
 * This program implements the upper score board in
 * Yahtzee as an object for easy of use
 * 
 * CPSC 224_01, Spring 2018
 * Assignment 5
 * @author Zach McKee
 * @version 1.1 3/22/2018
 */
public class UpperScoreBoard {
	private int[] scoreLines;
	private int numberOfLines;
	private boolean[] linesTaken;
	
	public UpperScoreBoard(Hand h) {
		numberOfLines = h.getMaxDieValue();
		scoreLines = new int[numberOfLines];
		calculateUpperScore(h);
		linesTaken = new boolean[numberOfLines];
		for(int i = 0; i < numberOfLines; i++) {
			linesTaken[i] = h.checkLineTaken(i);
		}
	}
	
	/**
	 * calculateUpperScore()
	 * This method goes through Hand h and calculates the whole upper score card.
	 * Stores the scores in scoreLines
	 * @param h
	 */
	public void calculateUpperScore(Hand h) {
		for(int currentDieValue = 1; currentDieValue <= numberOfLines; currentDieValue++) {
			int totalDie = 0;
			for(int i = 0; i < h.getHandSize(); i++) {
				if(h.getDieValueAt(i) == currentDieValue) {
					totalDie++;
				}
			}
			scoreLines[currentDieValue-1] = (currentDieValue * totalDie);
		}
	}
	
	/**
	 * toString()
	 * This method converts the UpperScoreBoard object into a printable format
	 * @return UpperScoreBoard in a string
	 */
	public String toString() {
		StringBuilder build = new StringBuilder();
		build.append("Your upper scorecard: \n");
		for(int i = 0; i < numberOfLines; i++) {
			if(linesTaken[i] == false)
			build.append((i + 1) + ": Score of " + scoreLines[i] + " on the " + (i+1) + " line\n");
		}
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
