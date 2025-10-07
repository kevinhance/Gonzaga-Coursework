// Kevin Hance
// CPSC 312
// PA3

import java.util.*;

public class Main {
    public static void main(String[] args) {

        // init arraylist of employees
        ArrayList<Employee> empList = new ArrayList<Employee>();
        empList.add(new Programmer());
        empList.add(new Programmer("Ima Nerd", true));
        empList.add(new Lawyer("Kenny Dewitt", 10));
        empList.add(new Lawyer("Dan D. Lyon", 0));
        empList.add(new Lawyer("Willie Makit", 100));
        empList.add(new Accountant("Hal E. Luya", 17.00));
        empList.add(new Accountant("Midas Well", 45.50));
        empList.add(new Accountant("Doll R. Bill", 2.50));
        System.out.println(empList);

        System.out.println("\n\n");

        // report salaries for all employees
        for(int i = 0; i < empList.size(); i++){
            System.out.println(empList.get(i).reportSalary());
        }

        System.out.println("\n\n");

        // init array of cars
        Car[] cars = new Car[10];
        cars[0] = new Car("Honda", "Civic", 1998, 120000);
        cars[1] = new Car("Honda", "Civic", 1998, 110000);
        cars[2] = new Car("Honda", "Civic", 2001, 100000);
        cars[3] = new Car("Honda", "Civic", 1998, 135000);
        cars[4] = new Car("PT Cruiser", "Chrysler", 2005, 90000);
        cars[5] = new Car("Ford", "Focus", 2008, 35000);
        cars[6] = new Car("Toyota", "Sequoia", 2007, 120000);
        cars[7] = new Car("Ferrari", "488", 2017, 13050);
        cars[8] = new Car("Honda", "Accord", 2012, 25100);
        cars[9] = new Car("Mitsubishi", "Evo", 2010, 45200);

        System.out.println(Arrays.toString(cars));

        // sort cars
        Arrays.sort(cars);

        System.out.println(Arrays.toString(cars));

        // go for a few drives
        cars[0].drive(25000);
        cars[2].drive(1000);
        cars[7].drive(12500);

        // sort cars again
        Arrays.sort(cars);

        System.out.println(Arrays.toString(cars));



    }
}
