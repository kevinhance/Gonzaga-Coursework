// Kevin Hance
// CPSC 312
// PA3

public class Programmer extends Employee{

    protected boolean hasBusPass;

    // evc
    public Programmer(String name, boolean hasBusPass) {
        super(name);
        this.salary += 20000;
        this.hasBusPass = hasBusPass;
    }

    // dvc
    public Programmer(){
        super("<Your name here>");
        this.salary += 20000;
        this.hasBusPass = false;
    }

    // getter for bus pass
    public boolean getHasBusPass() {
        return hasBusPass;
    }

    // setter for has bus pass
    public void setHasBusPass(boolean hasBusPass) {
        this.hasBusPass = hasBusPass;
    }

    // toString override
    @Override
    public String reportSalary() {
        String returnStr;
        returnStr = "I'm a Programmer. I make $" + this.salary + " and I do ";
        if(!this.hasBusPass)
            returnStr += "not ";
        returnStr += "have a bus pass.";
        return returnStr;
    }

    // compareTo override
    @Override
    public int compareTo(Employee o) {
        if(this == o)
            return 0;
        else{
            return this.name.compareTo(o.name);
        }
    }

    // toString override
    @Override
    public String toString() {
        String returnStr = super.toString();
        returnStr += "Has bus pass: " + hasBusPass + "\n";
        return returnStr;
    }
}
