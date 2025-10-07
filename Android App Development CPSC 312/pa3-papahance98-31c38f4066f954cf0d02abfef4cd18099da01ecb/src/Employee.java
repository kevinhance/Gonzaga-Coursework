// Kevin Hance
// CPSC 312
// PA3

import java.text.DecimalFormat;

public abstract class Employee implements Comparable<Employee>{
    protected String name;
    protected double salary;
    protected DecimalFormat decForm;

    // evc
    public Employee(String name) {
        this.name = name;
        this.salary = 40000;
        decForm = new DecimalFormat("#####.00");
    }

    // getter for name
    public String getName() {
        return name;
    }

    // setter for name
    public void setName(String name) {
        this.name = name;
    }

    // getter for salary
    public double getSalary() {
        return salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    // return string stating salary and benefits
    public abstract String reportSalary();

    // toString override
    @Override
    public String toString() {
        String returnStr = "";
        returnStr += "Name: " + this.name + "\t" + "Salary: $" + decForm.format(this.salary) + "\t";
        return returnStr;
    }
}
