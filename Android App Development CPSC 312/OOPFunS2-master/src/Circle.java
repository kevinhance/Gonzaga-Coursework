public class Circle {
    private double radius;
    private Point center;

    // DVC
    public Circle() {
        radius = 1.0;
        center = new Point();
    }

    // EVC
    public Circle(double radius, Point center) {
        this.radius = radius;
        this.center = center;
    }

    public Circle(double radius, int x, int y) {
        this.radius = radius;
        this.center = new Point(x, y);
    }


    @Override
    public String toString() {
        return "Circle{" +
                "radius=" + radius +
                ", center=" + center +
                '}';
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public Point getCenter() {
        return center;
    }

    public void setCenter(Point center) {
        this.center = center;
    }

    // NESTED CLASSES
    // a class defined inside another class
    // outer class: a class that is not nested
    // outer class is just like our "normal" classes we have been working with
    // outer classes can be public or package-private

    // 4 types of nested classes
    // 1. static nested class (we will make Point a static nested class of Circle)
    // 2. non-static nested class (AKA inner class)
    // 3. local inner class (inner class defined inside a method)
    // 4. anonymous inner class (local class with no name)

    // example of 1. static nested class
    public static class Point {
        private int x;
        private int y;

        // DVC
        public Point() {
            x = 0;
            y = 0;
        }

        // EVC
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public String toString() {
            return "(" + x + ", " + y + ")";
        }

        public int getX() {
            return x;
        }

        public void setX(int x) {
            this.x = x;
        }

        public int getY() {
            return y;
        }

        public void setY(int y) {
            this.y = y;
        }
    }
}
