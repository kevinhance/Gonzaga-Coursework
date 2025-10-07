/**LizardSpockYahtzee.java
 * 
 * This program runs a game of LizardSpockYahtzee
 * 
 * CPSC 224_01, Spring 2018
 * Assignment 5
 * @author Zach McKee
 * @version 2.0 3/22/2018
 */
import java.io.*;
import java.util.Scanner;

public class LizardSpockYahtzee {
	/**
	 * The main method, runs through a game of Yahtzee
	 * but does not keep track of score between turns.
	 * The user can play as many turns as they like.
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner userIn = new Scanner(System.in);
		int MAX_DIE_VALUE = 0;
		int DIE_IN_HAND = 0;
		int ROLLS_PER_HAND = 0;
		try { //Initialization of the files, asks user if they want to change
			File userFile = new File("yahtzeeConfig.txt");
			if(!userFile.createNewFile()) {
				System.out.println("Reading from yahtzeeConfig.txt");
				Scanner userFileRead = new Scanner(userFile);
				MAX_DIE_VALUE = userFileRead.nextInt();
				DIE_IN_HAND	= userFileRead.nextInt();
				ROLLS_PER_HAND = userFileRead.nextInt();
				System.out.println("You are playing with " + DIE_IN_HAND + " " + MAX_DIE_VALUE + "-sided dice");
				System.out.println("You get " + ROLLS_PER_HAND + " rolls per turn\n");
				System.out.print("Would you like to make changes? (y): ");
				String changes = userIn.nextLine();
				userFileRead.close();
				if(changes.equalsIgnoreCase("y")) {
					System.out.print("Sides of each die?: ");
					MAX_DIE_VALUE = userIn.nextInt();
					System.out.print("Dice in a hand?: ");
					DIE_IN_HAND = userIn.nextInt();
					System.out.print("Rolls per turn?: ");
					ROLLS_PER_HAND = userIn.nextInt();
					System.out.println("Saving config to yahtzeeConfig.txt");
					BufferedWriter userWrite = new BufferedWriter(new FileWriter(userFile));
					userWrite.write(MAX_DIE_VALUE + "");
					userWrite.newLine();
					userWrite.write(DIE_IN_HAND + "");
					userWrite.newLine();
					userWrite.write(ROLLS_PER_HAND + "");
					userWrite.newLine();
					userWrite.close();
				}
			} else {
				System.out.println("yahtzeeConfig.txt was not found, please enter a new configuration");
				System.out.print("Sides of each die?: ");
				MAX_DIE_VALUE = userIn.nextInt();
				System.out.print("Dice in a hand?: ");
				DIE_IN_HAND = userIn.nextInt();
				System.out.print("Rolls per turn?: ");
				ROLLS_PER_HAND = userIn.nextInt();
				System.out.println("Saving config to yahtzeeConfig.txt");
				BufferedWriter userWrite = new BufferedWriter(new FileWriter(userFile));
				userWrite.write(MAX_DIE_VALUE + "");
				userWrite.newLine();
				userWrite.write(DIE_IN_HAND + "");
				userWrite.newLine();
				userWrite.write(ROLLS_PER_HAND + "");
				userWrite.newLine();
				userWrite.close();
			}
		} catch (IOException e) {
		}
		
		Hand player = new Hand(MAX_DIE_VALUE, DIE_IN_HAND);
		StringBuilder fullKeepB = new StringBuilder();
		StringBuilder initialKeep = new StringBuilder();
		for(int i = 0; i < DIE_IN_HAND; i++) {
			fullKeepB.append("y");
			initialKeep.append("n");
		}
		String fullKeep = fullKeepB.toString();
		int roundTurn = 0;
		while (roundTurn < (MAX_DIE_VALUE + 7)) { //If there are still rounds left, keep playing
			userIn = new Scanner(System.in);
			System.out.println("\n~~~Round " + (roundTurn + 1) + "~~~");
			int currentTurn = 0;
			String keep = initialKeep.toString();
			while(currentTurn < ROLLS_PER_HAND && !(keep.equals(fullKeep))) { //While the user still has turns and hasn't opted to score,
				for(int i = 0; i < player.getHandSize(); i++) {	//Reroll the dice they decided to change
					if(keep.charAt(i) == 'n')
						player.reroll(i);
				}
				System.out.println("Your roll " + (currentTurn + 1) + " was: " + player);	//Display their roll
				System.out.print("Enter dice to keep (y or n) :");//Prompt the user to change their dice
				keep = userIn.nextLine(); //Get the user input
				while(keep.length() != initialKeep.length()) {
					System.out.println("\nPlease enter values for all " + DIE_IN_HAND + " dice");
					System.out.print("Enter dice to keep (y or n) :");
					keep = userIn.nextLine();
				}
				System.out.println();
				currentTurn++;
			}
			if(!(keep.equals(fullKeep)))
				for(int i = 0; i < player.getHandSize(); i++)	//Reroll the dice they decided to change
					if(keep.charAt(i) == 'n')
						player.reroll(i);
			
			System.out.println("~~~~~~~~Scoring~~~~~~~~\n");
			player.sort();
			System.out.println("Your sorted hand: " + player);
			
			UpperScoreBoard turnUp = new UpperScoreBoard(player); //Calculate their upper board and put
			System.out.print(turnUp);							  //the scores in UpperScoreBoard object turnUp
			System.out.println();
			LowerScoreBoard turnDown = new LowerScoreBoard(player);//Calculate their lower board and put
			System.out.print(turnDown);							   //the score in LowerScoreBoard object turnDown
			
			boolean repeat = true;
			while(repeat) {
				System.out.print("Choose a line to save: ");
				int lineNumber = userIn.nextInt();
				if(lineNumber > 0 && lineNumber <= (MAX_DIE_VALUE + 7) && (player.checkLineTaken(lineNumber - 1) == false)) {
					if(lineNumber - 1 < MAX_DIE_VALUE) {
						player.setScoreAtLine(lineNumber - 1, turnUp.getScoreAt(lineNumber - 1));
					} else {
						player.setScoreAtLine(lineNumber - 1, turnDown.getScoreAt(lineNumber - MAX_DIE_VALUE - 1));
					}
					repeat = false;
					player.takeLine(lineNumber - 1);
				} else {
					System.out.println("Invalid line (Either taken or out of bounds)");
				}
			}
			roundTurn++;
		}
		System.out.println("\n~~Final Scores~~");
		System.out.println(player.printFinalScores());
		
		System.out.println("\nGoodbye");
		userIn.close();
	}
}
