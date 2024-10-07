package it.unibo.shapes.test;

import it.unibo.shapes.impl.Circle;
import it.unibo.shapes.impl.Rectangle;
import it.unibo.shapes.impl.Square;
import it.unibo.shapes.impl.Triangle;

public class WorkWithShapes {

    public static void main(final String[] args){
        Circle circle = new Circle(3);
        Triangle triangle = new Triangle(3, 4, 5);
        Rectangle rectangle = new Rectangle(3, 2);
        Square square = new Square(2);

        System.out.println("Circle:\nPerimeter: " + circle.getPerimeter()
            + "\nArea: " + circle.getArea() + "\nTriangle:\nPerimeter: "
            + triangle.getPerimeter() + "\nArea: " + triangle.getArea()
            + "\nRectangle:\nPerimeter: " + rectangle.getPerimeter()
            + "\nArea: " + rectangle.getArea() + "\nSquare:\nPerimeter: "
            + square.getPerimeter() + "\nArea: " + square.getArea());
    }

}
