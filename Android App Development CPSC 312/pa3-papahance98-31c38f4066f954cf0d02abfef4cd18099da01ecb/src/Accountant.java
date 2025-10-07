// Kevin Hance
// CPSC 312
// PA3

import java.text.DecimalFormat;

public class Accountant extends Employee{
    protected double parkingAllowance;
    DecimalFormat decForm = new DecimalFormat("###.00");

    // evc
    public Accountant(String name, double parkingAllowance) {
        super(name);
        this.parkingAllowance = parkingAllowance;
    }

    // dvc
    public Accountant(){
        super("<Your name here>");
        this.parkingAllowance = 0.00;

    }

    // getter for parkingAllowance
    public double getParkingAllowance() {
        return parkingAllowance;
    }

    // setter for parkingAllowance
    public void setParkingAllowance(double parkingAllowance) {
        this.parkingAllowance = parkingAllowance;
    }

    // decrementer for parkingAllowance
    public void decrementParkingAllowance(double decAmount){
        this.parkingAllowance -= decAmount;
    }

    // override for reportSalary
    @Override
    public String reportSalary() {
        String returnStr;
        returnStr = "I'm an Accoutant. I make $" + this.salary + " and I have a parking allowance of " + decForm.format(this.parkingAllowance) + ".";
        return returnStr;
    }
    // override for compareTo
    @Override
    public int compareTo(Employee o) {
        if(this == o)
            return 0;
        else{
            return this.name.compareTo(o.name);
        }
    }

    // override for toString
    @Override
    public String toString() {
        String returnStr = super.toString();
        returnStr += "Parking allowance: " + decForm.format(this.parkingAllowance) + "\n";
        return returnStr;
    }

}
