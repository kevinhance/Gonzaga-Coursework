//	Kevin Andrew Hance
//	March 8th, 2018
//	CPSC 224: Object Oriented Programming (Zhang)
//	HW Assignment #5: Yahtzee
//
//  This subclass models the upper and lower parts of the Yahtzee scoreboard. Allows
//	for scores to be saved and bonuses to be applied to the scoreboard.

public class Scoreboard {
	
	private int[] upperSb;
	private int[] lowerSb;
	
	public Scoreboard(int maxDieVal) {
		// aces-sixes (or more), plus one element for 35 pt bonus
		upperSb = new int[maxDieVal + 1];
		// 3kind, 4kind, FH, SmStr, LgStr, Yhtz, Chance
		lowerSb = new int[7];
	}
	
	
	//apply score to ones row
	public void acesScore(int score) {
		upperSb[0] = score;
	}
	
	//apply score to twos row
	public void twosScore(int score) {
		upperSb[1] = score;
	}
	
	//apply score to threes row
	public void threesScore(int score) {
		upperSb[2] = score;
	}
	
	//apply score to fours row
	public void foursScore(int score) {
		upperSb[3] = score;
	}
	
	//apply score to fives row
	public void fivesScore(int score) {
		upperSb[4] = score;
	}
	
	//apply score to sixes row
	public void sixesScore(int score) {
		upperSb[5] = score;
	}
	
	//apply 35pt bonus for having over 63 points in upper scoreboard
	public void applyUpperBonus() {
		int sum = 0;
		for (int i : upperSb)
			sum += i;
		if(sum >= 63)
			upperSb[6] = 35;
	}
	
	//apply score to ones row
	public void threeOfaKindScore(int score) {
		lowerSb[0] = score;
	}
	
	//apply score to ones row
	public void fourOfaKindScore(int score) {
		lowerSb[1] = score;
	}
	
	//apply score to ones row
	public void fullHouseScore(int score) {
		lowerSb[2] = score;
	}
	
	//apply score to ones row
	public void smStraightScore(int score) {
		lowerSb[3] = score;
	}
	
	//apply score to large straight row
	public void lgStrightScore(int score) {
		lowerSb[4] = score;
	}
	
	//apply score to yahtzee row
	public void yahtzeeScore(int score) {
		lowerSb[5] = score;
	}
	
	//apply score to chance row
	public void chanceScore(int score) {
		lowerSb[6] = score;
	}
	
	//apply 50pt bonus for each second, third, fourth, etc. yahtzees
	public void applyYahtzeeBonus() {
		int bonus = (((lowerSb[5] / 50) - 1) * 50);
		lowerSb[7] = bonus;
	}
	
}
