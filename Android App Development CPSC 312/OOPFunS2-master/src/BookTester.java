public class BookTester {
    // a tester (AKA driver) exercises methods, constructors, etc.
    // in a program or class or etc.

    public static void main(String[] args) {
        Book bookOne = new Book();
        System.out.println(bookOne);

        Book bookTwo = new Book("Catch22", "Joseph Heller", 100);
        System.out.println(bookTwo.toString());
        System.out.println(bookTwo.getTitle());
    }

}
