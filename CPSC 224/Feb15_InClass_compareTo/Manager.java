import java.util.Arrays;

public class Manager extends Employee {	
	private double bonus;
	public Manager(String n, double s, int y, int m, int d) {
		//call constructor from super
		super(n, s, y, m, d);
		//initialize bonus
		bonus = 0.0;
	}
	public double getSalary() {
		//this method will return salary.bonus
		return super.getSalary() + bonus;
	}
	public void setBonus(double b) {
		//setter: modify value of bonus
		bonus = b;
	}
	
	public double getBonus() {
		//getter: return value of bonus
		return bonus;
	}
	
	public boolean equals(Object otherObject) {
		if (super.equals(otherObject)) {
			Manager otherBoss = (Manager) otherObject;
			return (this.bonus == otherBoss.getBonus());
		}
		return false;
	}
}