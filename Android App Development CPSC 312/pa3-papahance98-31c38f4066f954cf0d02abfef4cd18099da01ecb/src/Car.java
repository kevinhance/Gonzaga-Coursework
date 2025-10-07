// Kevin Hance
// CPSC 312
// PA3

public class Car implements Driveable, Comparable<Car>{
    protected String make;
    protected String model;
    protected int year;
    protected int odometerReading;

    public Car(String make, String model, int year, int odometerReading) {
        this.make = make;
        this.model = model;
        this.year = year;
        this.odometerReading = odometerReading;
    }

    // vvv GETTERS AND SETTERS FOR PROTECTED FIELDS vvv

    public String getMake() {
        return make;
    }

    public void setMake(String make) {
        this.make = make;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public int getOdometerReading() {
        return odometerReading;
    }

    public void setOdometerReading(int odometerReading) {
        this.odometerReading = odometerReading;
    }

    // override for drive function (implementing Drivable interface)
    @Override
    public void drive(int milesDriven) {
        this.odometerReading += milesDriven;
    }

    // override for compareTo function
    @Override
    public int compareTo(Car o) {
        if(this.year != o.year) {
            // compare by year
            return this.year - o.year;
        } else if(this.make.compareTo(o.make) != 0){
            // compare by make
            return this.make.compareTo(o.make);
        } else if(this.model.compareTo(o.model) != 0){
            // compare by model
            return this.model.compareTo(o.model);
        } else {
            // compare by odometer
            return this.odometerReading - o.odometerReading;
        }
    }

    // override for toString function
    @Override
    public String toString() {
        return "Make: " + this.make + ", Model: " + this.model + ", Year: " + this.year + ", Odometer: " + odometerReading + "\n";
    }
}
