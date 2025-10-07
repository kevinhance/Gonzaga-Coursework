//	Kevin Andrew Hance
//	March 8th, 2018
//	CPSC 224: Object Oriented Programming (Zhang)
//	HW Assignment #5: Yahtzee
//
//  This program emulates the popular dice game, Yahtzee. The program rolls dice for the user,
//	displays the output, then allows more chances to re-roll undesired dice before showing the
//	user what their options are for scoring in Yahtzee with that specific hand of dice. Then,
//	the user can choose which category they wish to score in. At the end of the game, the
//	scoreboard is printed out for the user to see, bonuses included.


import java.io.*;
import java.util.*;
import java.time.*;

public class LizardSpockYahtzee {

	public static void main(String args[]) throws FileNotFoundException {
		
		//initialize default game settings incase file isn't read correctly
		int handSize = 5;
		int maxDieValue = 6;
		int maxRolls = 3;
		
		
		Scanner s = new Scanner(System.in);	
		
		char playAgain = 'y';
		
		int[] cfgArr = runInitialization();
		maxDieValue = cfgArr[0];
		handSize = cfgArr[1];
		maxRolls = cfgArr[2];
		
		Hand h = new Hand(handSize, maxDieValue);
		Scoreboard scr = new Scoreboard(maxDieValue, h);
		
		for(int i = 0; i < 13 + (maxDieValue - 6); i++)
		{
			String keep = "";
			for(int j = 0; j < handSize; j++) {
				keep += "n";
			}
			//setup to roll all dice in the first roll
			int turn = 1;
			while (turn < maxRolls && keep.contains("n"))
			{
				//roll dice not kept
				h.rollDice(keep);
				//output roll
				System.out.print("Your roll was: ");
				h.printHand();
				//if not the last roll of the hand prompt the user for dice to keep
				if(turn < maxRolls)
				{
					do
					{
						System.out.print("enter dice to keep (y or n) ");
						keep = s.nextLine();
					} while (keep.length() !=handSize);
				}
				System.out.println();
				turn++;
			}
			
			// start scoring:
			// hand needs to be sorted to check for straights
			h.sortHand();
		 	
			// output sorted hand
			System.out.print("Here is your sorted hand : ");
			h.printHand();
			
			//scr.print out and then ask the user what they want to put the score in, then repeat
			
			boolean repeatScoreChoice = false;
			do {
				// print out all of the options the user has for scoring
				scr.printScoreboard(maxDieValue, h);
				// take in user input for what category they want to score in
				char scoreOption = s.nextLine().toCharArray()[0];
				// score option int converts a 1-digit numeric character into the integr equivalent
				int scoreOptionInt = ((int) scoreOption) - 48;
				if((int) scoreOption < 58) {
					// if the user entered an integer (Upper Scoreboard, Aces - Max Die Value)
					if(scr.isScoreEmptyUpper(scoreOptionInt-1)) {
						scr.bigDieScore(scoreOptionInt);
						repeatScoreChoice = false;
					} else {
						System.out.println("Score has already been used");
						repeatScoreChoice = true;
					}
				} else { // if the user entered a character (Lower Scoreboard)
					if(scoreOption == 'A') {
						if(scr.isScoreEmptyLower(0)) {
							scr.threeOfaKindScore();
							repeatScoreChoice = false;
						} else {
							System.out.println("Score has already been used");
							repeatScoreChoice = true;
						}
					}
					else if(scoreOption == 'B') {
						if(scr.isScoreEmptyLower(1)) {
							scr.fourOfaKindScore();
							repeatScoreChoice = false;
						} else {
							System.out.println("Score has already been used");
							repeatScoreChoice = true;
						}
					}
					else if(scoreOption == 'C') {
						if(scr.isScoreEmptyLower(2)) {
							scr.fullHouseScore();
							repeatScoreChoice = false;
						} else {
							System.out.println("Score has already been used");
							repeatScoreChoice = true;
						}
					}
					else if(scoreOption == 'D') {
						if(scr.isScoreEmptyLower(3)) {
							scr.smStraightScore();
							repeatScoreChoice = false;
						} else {
							System.out.println("Score has already been used");
							repeatScoreChoice = true;
						}
					}
					else if(scoreOption == 'E') {
						if(scr.isScoreEmptyLower(4)) {
							scr.lgStrightScore();
							repeatScoreChoice = false;
						} else {
							System.out.println("Score has already been used");
							repeatScoreChoice = true;
						}
					}
					else if(scoreOption == 'F') {
						if(scr.isScoreEmptyLower(5)) {
							scr.yahtzeeScore();
							repeatScoreChoice = false;
						} else {
							System.out.println("Score has already been used");
							repeatScoreChoice = true;
						}
					}
					else if(scoreOption == 'G') {
						if(scr.isScoreEmptyLower(6)) {
							scr.chanceScore();
							repeatScoreChoice = false;
						} else {
							System.out.println("Score has already been used");
							repeatScoreChoice = true;
						}
					}
				} 
			} while (repeatScoreChoice);
			
		}
		
		// apply bonuses for upper scoreboard and extra yahtzees, then print out final scoreboard
		scr.applyUpperBonus();
		scr.applyYahtzeeBonus();
		scr.printFinalScore();
	}

	public static int[] runInitialization() throws FileNotFoundException {
		// I know this is a bad way to access the file because it only works on my computer, but for some reason
		// referencing "LizardSpockYahtzee\\src\\yahtzeeConfig.txt" or just "yahtzeeConfig.txt" caused a
		// FileNotFoundException.
		File f = new File("C:\\Users\\kevin\\eclipse-workspace\\LizardSpockYahtzee\\src\\yahtzeeConfig.txt");
		//config game settings from file, give user option to change settings via console after file reading
		int[] cfgArr = configureFromFile(f);
		return cfgArr;
	}
	
	public static int[] configureFromFile(File f) throws FileNotFoundException {
		Scanner cfg = new Scanner(f);
		// return an int array to main to configure settings
		int[] cfgArr = {5,6,3}; 
		// fill int array with values from file
		if(cfg.hasNextInt())
		{
			cfgArr[0] = cfg.nextInt();
			if(cfg.hasNextInt()) {
				cfgArr[1] = cfg.nextInt();
				if(cfg.hasNextInt()) {
					cfgArr[2] = cfg.nextInt();
				}
			}
		}
		// let the user know what settings were specified in the file,
		// then allow them to change it if they wish
		Scanner console = new Scanner(System.in);
		System.out.println("You will be playing with " + cfgArr[1] + " " + cfgArr[0] + "-sided dice.");
		System.out.println("You will get " + cfgArr[2] + " rolls per hand.\n");
		System.out.print("Enter 'y' if you would like to change the configuration: ");
		// set changeConfigChar to first character entered by user (they could enter "yes" or "YEAH and it'd still work)
		char changeConfigChar = console.nextLine().toLowerCase().toCharArray()[0];
		if(changeConfigChar == 'y')
		{
			return configureFromUserInput();
		}
		return cfgArr;
	}
	

	// simple function to return int array based on user input representing game settings
	public static int[] configureFromUserInput() {
		Scanner c = new Scanner(System.in);
		String str1 = "";
		String str2 = "";
		String str3 = "";
		int[] cfgArr = {5,6,3};
		System.out.print("Enter the number of sides on each die: ");
		str1 = c.nextLine();
		cfgArr[0] = Integer.parseInt(str1);
		System.out.print("Enter the number of dice in play: ");
		str2 = c.nextLine();
		cfgArr[1] = Integer.parseInt(str2);
		System.out.print("Enter the number of rolls per hand: ");
		str3 = c.nextLine();
		cfgArr[2] = Integer.parseInt(str3);
		System.out.println();
		return cfgArr;
	}
	
}