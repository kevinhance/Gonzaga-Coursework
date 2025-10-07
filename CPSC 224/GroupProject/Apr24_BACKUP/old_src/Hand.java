/**Hand.java
 * 
 * This program holds an array of Die and acts
 * as a players hand in the game of Yahtzee
 * 
 * CPSC 224_01, Spring 2018
 * Assignment 5
 * @author Zach McKee
 * @version 1.0 3/6/2018
 */
import java.util.Arrays;

public class Hand {
	private Die[] dice;
	private int MAX_DIE_VALUE;
	private boolean[] linesTaken;
	private int[] scores;

	private int HAND_SIZE;
	
	public Hand(int MAX_DIE_VALUE, int DIE_IN_HAND) {
		dice = new Die[DIE_IN_HAND];
		for(int i = 0; i < HAND_SIZE; i++) {
			dice[i] = new Die(MAX_DIE_VALUE);
		}
		HAND_SIZE = DIE_IN_HAND;
		this.MAX_DIE_VALUE = MAX_DIE_VALUE;
		linesTaken = new boolean[MAX_DIE_VALUE + 7];
		for(int i = 0; i < linesTaken.length; i++)
			linesTaken[i] = false;
		scores = new int[MAX_DIE_VALUE + 7];
	}
	
	/**
	 * reroll()
	 * This method rerolls a die at the specified index
	 * @param index
	 */
	public void reroll(int index) {
		dice[index] = new Die(MAX_DIE_VALUE);
	}
	
	/**
	 * getDieAt()
	 * This method returns the Die object at index
	 * @param index
	 * @return die at index
	 */
	public Die getDieAt(int index) {
		return dice[index];
	}
	
	/**
	 * getDieValueAt()
	 * This method returns the value of the die at index
	 * @param index
	 * @return value of die at index
	 */
	public int getDieValueAt(int index) {
		return dice[index].getDieValue();
	}
	
	/**
	 * toString()
	 * This method returns the hand in a printable format
	 * @return Hand in a string form
	 */
	public String toString() {
		StringBuilder a = new StringBuilder();
		for(int i = 0; i < HAND_SIZE; i++) {
			a.append(dice[i].getDieValue() + " ");
		}
		return a.toString();
	}
	
	/**
	 * sort()
	 * This method sorts the hand
	 */
	public void sort() {
		Arrays.sort(dice);
	}
	
	/**
	 * getHandSize()
	 * This method returns the size of the hand
	 * @return HAND_SIZE
	 */
	public int getHandSize() {
		return HAND_SIZE;
	}
	
	/**
	 * getMaxDieValue()
	 * This method returns the max die value from the hand
	 * @return MAX_DIE_VALUE
	 */
	public int getMaxDieValue() {
		return MAX_DIE_VALUE;
	}
	
	/**
	 * checkLineTaken()
	 * This method returns whether a given line already has a score
	 * Returns true if the line is occupied
	 * @param index
	 * @return Whether the line is taken
	 */
	public boolean checkLineTaken(int index) {
		return linesTaken[index];
	}
	
	/**
	 * takeLine()
	 * This method takes the line at index i
	 * @param index
	 */
	public void takeLine(int index) {
		linesTaken[index] = true;
	}
	
	/**
	 * setScoreAt()
	 * This method saves a score at line index
	 * @param index
	 * @param newScore
	 */
	public void setScoreAtLine(int index, int newScore) {
		scores[index] = newScore;
	}
	
	/**
	 * printFinalScores()
	 * This method prints out the final scores of the game
	 * @return completeScores
	 */
	public String printFinalScores() {
		StringBuilder build = new StringBuilder();
		int index = 0;
		for(; index < MAX_DIE_VALUE; index++) {
			build.append("Score of " + scores[index] + " on the " + (index + 1) + " line\n");
		}
		build.append("Score " + scores[index] + " on the 3 of a Kind line\n");
		build.append("Score " + scores[index + 1] + " on the 4 of a Kind line\n");
		build.append("Score " + scores[index + 2] + " on the Full House line\n");
		build.append("Score " + scores[index + 3] + " on the Small Straight line\n");
		build.append("Score " + scores[index + 4] + " on the Large Straight line\n");
		build.append("Score " + scores[index + 5] + " on the Yahtzee line\n");
		build.append("Score " + scores[index + 6] + " on the Chance line\n");
		int grandTotal = 0;
		for(int i = 0; i < scores.length; i++) {
			grandTotal += scores[i];
		}
		build.append("For a grand total of " + grandTotal + " points!");
		
		String completeScores = build.toString();
		return completeScores;
	}
}
