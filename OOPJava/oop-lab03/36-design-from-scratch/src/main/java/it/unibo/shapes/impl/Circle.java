package it.unibo.shapes.impl;

import java.lang.Math;
import it.unibo.shapes.api.Shape;

public class Circle implements Shape{
    private double radious;

    public Circle(double radious){
        this.radious = radious;
    }

    public double getArea(){
        return Math.PI * this.radious * this.radious;
    }

    public double getPerimeter(){
        return Math.PI * 2 * this.radious;
    }
}
