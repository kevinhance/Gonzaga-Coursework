import java.time.LocalDate;
import java.util.Arrays;

public class Employee implements Comparable {
    private String name;
    private double salary;
    private LocalDate hireDay;

    public Employee(String n, double s, int year, int month, int day)
    {
        name = n;
        salary = s;
        hireDay = LocalDate.of(year, month, day);
    }

    public String getName()
    {
        return name;
    }

    public double getSalary()
    {
        return salary;
    }

    public LocalDate getHireDay()
    {
        return hireDay;
    }

    public void raiseSalary(double byPercent)
    {
        double raise = salary * byPercent / 100;
        salary += raise;
    }
	
	public boolean equals(Object otherObject) {
		if (this == otherObject) return true;
		if (otherObject == null) return false;
		if (this.getClass() != otherObject.getClass()) return false;
		else {
			Employee otherEmp = (Employee) otherObject;
			if (this.name == otherEmp.getName() &&
				this.salary == otherEmp.getSalary() &&
				this.hireDay == otherEmp.getHireDay())
				return true;
		}
		return false;
	}
	
	public int compareTo(Object otherObj) {
		Employee otherEmp = (Employee) otherObj;
		
		if(this.salary > otherEmp.getSalary())
			return 1;
		else if (this.salary == otherEmp.getSalary())
			return 0;
		else
			return -1;
	}		
		
}