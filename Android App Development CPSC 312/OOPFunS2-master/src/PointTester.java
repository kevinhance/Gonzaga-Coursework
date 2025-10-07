import java.util.Arrays;

public class PointTester {
    public static void main(String[] args) {
        Circle.Point origin = new Circle.Point();
        System.out.println(origin);

        // array of references
        Circle.Point[] points = new Circle.Point[5];
        // NO Point objects were just made!!
        // 5 Point references were just made (null)
        for (int i = 0; i < points.length; i++) {
            points[i] = new Circle.Point(i, i); // here actually making a Point object
        }
        System.out.println(Arrays.toString(points));

//        for (Point p : points) { // "enhanced" for loop
//            System.out.println(p);
//        }

        // task 3: in this project...
        // create a Circle class and a CircleTester class
        // Circle has a radius (double) center (Point)
        // "has-a" relationship -> composition
        // "is-a" relationship -> inheritance

    }
}
