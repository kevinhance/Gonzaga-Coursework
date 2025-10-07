/**Die.java
 * 
 * This program implements a Die to
 * be used in a hand and in scoring for Yahtzee
 * 
 * CPSC 224_01, Spring 2018
 * Assignment 5
 * @author Zach McKee
 * @version 1.3 3/22/2018
 */
import java.util.Random;

public class Die implements Comparable<Object>{
	private int Value;
	private Random rand;
	
	//Default constructor is not used,
	//except for initialization of an array
	public Die() {	
	}
	
	public Die(int MAX_DIE_VALUE) {
		rand = new Random();
		Value = rand.nextInt(MAX_DIE_VALUE) + 1;
	}
	
	/**
	 * getDieValue()
	 * This method returns the value of the Die
	 * @return Value
	 */
	public int getDieValue() {
		return Value;
	}
	
	/**
	 * compareTo()
	 * This method implements the compareTo method from the comparable interface
	 * @return 1, This Die Value > other Die Value
	 * @return 0, This Die Value == other Die Value
	 * @return -1, This Die Value < other Die Value
	 */
	public int compareTo(Object obj) {
		Die other = (Die) obj;
		if(Value > other.Value) {
			return 1;
		} else if (Value == other.Value) {
			return 0;
		}
		return -1;
	}
}
