import java.util.Arrays;
import java.util.Random;
public class Hand {
	public enum Resources {Fuel, Hull_Parts, Crew_Member, Electronics, Glass, Chance;
						   private static Random ran = new Random();
						   public static Resources randomResource() { //This method is used to get random resources
							   return Resources.values()[ran.nextInt(6)];};
						   }
	Resources[] playerResources;
	boolean[] partsBuilt = new boolean[10]; //The first 9 elements are reserved for the rocket's parts.
											//The tenth element is reserved for if the rocket is complete
	int[] commodities = new int[2]; //This is to keep track of the crew members and fuel
	private final int HAND_SIZE = 5;
	
	public Hand() {
		playerResources = new Resources[HAND_SIZE];
		for(int i = 0; i < HAND_SIZE; i++) {
			playerResources[i] = Resources.randomResource();
		}
		for(int i = 0; i < partsBuilt.length; i++)
			partsBuilt[i] = false;
	}
	
	/**
	 * reroll()
	 * This method rerolls a die at the specified index
	 * @param index
	 */
	public void reroll(int index) {
		playerResources[index] = Resources.randomResource();
	}
	
	/**
	 * getDieAt()
	 * This method returns the resource at index
	 * @param index
	 * @return die at index
	 */
	public Resources getResourceAt(int index) {
		return playerResources[index];
	}
	
	/**
	 * toString()
	 * This method returns the hand in a printable format
	 * @return Hand in a string form
	 */
	public String toString() {
		StringBuilder a = new StringBuilder();
		for(int i = 0; i < HAND_SIZE; i++) {
			a.append(playerResources[i] + " ");
		}
		return a.toString();
	}
	
	/**
	 * sort()
	 * This method sorts the hand
	 */
	public void sort() {
		Arrays.sort(playerResources);
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
	 * checkPartBuilt()
	 * This method returns whether a part has already been built on line index
	 * Returns true if the line is occupied
	 * @param index
	 * @return Whether the line is taken
	 */
	public boolean checkPartBuilt(int index) {
		return partsBuilt[index];
	}
	
	/**
	 * buildPart()
	 * This method builds a part by setting partsBuilt at index to true
	 * @param index
	 */
	public void buildPart(int index) {
		partsBuilt[index] = true;
	}
	
	public int numberOfHullParts(){
		int num = 0;
		for(int i = 0; i < 5; i++){
			if(playerResources[i] == Hull_Parts)
				num++;
		}
		return num;
	}
	
	public int numberOfElectronics(){
		int num = 0;
		for(int i = 0; i < 5; i++){
			if(playerResources[i] == Electronics)
				num++;
		}
		return num;
	}
	
	public int numberOfGlass(){
		int num = 0;
		for(int i = 0; i < 5; i++){
			if(playerResources[i] == Glass)
				num++;
		}
		return num;
	}
	
	public int numberOfCrewMembers(){
		int num = 0;
		for(int i = 0; i < 5; i++){
			if(playerResources[i] == Crew_Member)
				num++;
		}
		return num;
	}
	
	public int numberOfFuel(){
		int num = 0;
		for(int i = 0; i < 5; i++){
			if(playerResources[i] == Fuel)
				num++;
		}
		return num;
	}
	
}

