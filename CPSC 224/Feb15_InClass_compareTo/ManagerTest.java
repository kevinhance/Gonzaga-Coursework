import java.util.*;
import java.util.Arrays;


public class ManagerTest {
	public static void main(String[] args) {
		Employee[] staff = new Employee[3];
		staff[0] = new Manager("Zach", 2, 1942, 4, 20);
		staff[1] = new Employee("Kevin", 100000.0, 1994, 3, 25);
		staff[2] = new Employee("Bassel", 1738.0, 2001, 1, 1);
		
		Arrays.sort(staff);
		
		Manager boss = (Manager) staff[0];
		
		for (Employee e: staff)
			System.out.println("name = " + e.getName() + ", salary = "+ e.getSalary() );
		
		System.out.println(boss.equals(staff[0]));
	}
}

