public class Book {
    // class: a collection of state and behavior that completely describes something
    // state: fields (AKA attributes)
    // behavior: methods

    // object: instance of a class
    // class like a blueprint, and an object is a realization of that blueprint
    // members of a class include constructors, fields, methods, nested classes, etc.

    // fields
    private String title;
    private String author;
    private int numPages;

    // constructors
    // we get a free default value constructor (DVC)

    // explicit value constructor (EVC)
    public Book(String title, String paramAuthor, int paramNumPages) {
        // this is a reference to the invoking object
        // in a constructor this refers to the object being created
        this.title = title; // shadowing... title the param has the same name as title the field
        author = paramAuthor;
        numPages = paramNumPages;
    }

    // when we define a constructor we lose our free DVC
    // define our own DVC
    public Book() {
        title = "BLANK TITLE";
        author = "BLANK AUTHOR";
        numPages = -1;
    }

    // recall Object is the direct or indirect super class of all classes in Java
    // Object has some useful methods that we inherit
    // toString()
    // we can override toString()

    // ANNOTATIONS
    // @Deprecated @Override @SuppressWarnings
    // metadata metainformation used by the compiler and the IDE
    // doesn't affect source

    @Override
    public String toString() {
        // return a string representation of the invoking object
        // this !!
        // called whenever a string representation of an object is needed (implicility)
        // println()

        return this.title + " by " + this.author;
    }

    // getters and setters
    // recall access modifiers
    // 1. public (accessible anywhere)
    // 2. package-private (accessible anywhere in this package)
    // 3. protected (package-private plus accessible from any subclass, even in a diff package)
    // 4. private (accessible only from this class)

    // only expose state and behavior as the application requires
    // getter (AKA accessor)
    public String getTitle() {
        return this.title;
    }

    // setter (AKA mutator)
    public void setTitle(String title) {
        this.title = title;
    }

    // task 1: getter and setter for our other two fields
    // generate code alt + ins OR cmd + N


    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public int getNumPages() {
        return numPages;
    }

    public void setNumPages(int numPages) {
        this.numPages = numPages;
    }

    // task 2: still in this project...
    // create a Point class and a PointTester
    // Point represents a point in 2D space
    // x, y
    // toString() example: (0, 0)
    // PointTester, just exercise some of your Point class members
}
