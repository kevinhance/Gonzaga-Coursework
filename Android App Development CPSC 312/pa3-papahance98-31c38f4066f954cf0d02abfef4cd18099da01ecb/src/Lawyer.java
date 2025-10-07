// Kevin Hance
// CPSC 312
// PA3

public class Lawyer extends Employee{
    protected int stockOptions;


    // evc
    public Lawyer(String name, int stockOptions) {
        super(name);
        this.salary += 30000;
        this.stockOptions = stockOptions;
    }

    // dvc
    public Lawyer(){
        super("<Your name here>");
        this.salary += 30000;
        this.stockOptions = 0;

    }

    // getter for stock options
    public int getStockOptions() {
        return stockOptions;
    }

    // setter for stock options
    public void setStockOptions(int stockOptions) {
        this.stockOptions = stockOptions;
    }

    // override for reportSalary function
    @Override
    public String reportSalary() {
        String returnStr;
        returnStr = "I'm a Lawyer. I make $" + this.salary + " and I have " + this.stockOptions + " stock options.";
        return returnStr;
    }

    // override for compareTo function
    @Override
    public int compareTo(Employee o) {
        if(this == o)
            return 0;
        else{
            return this.name.compareTo(o.name);
        }
    }

    // override for toString function
    @Override
    public String toString() {
        String returnStr = super.toString();
        returnStr += "Stock options: " + stockOptions + "\n";
        return returnStr;
    }

}
