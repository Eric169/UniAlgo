package it.unibo.shapes.impl;

import it.unibo.shapes.api.Polygon;

public class Rectangle implements Polygon{
    private final int EDGE_COUNT = 4;

    private double width;
    private double height;
    
    public Rectangle(double width, double height){
        this.width = width;
        this.height = height;
    }

    public double getArea(){
        return this.width * this.height;
    }

    public double getPerimeter(){
        return (this.width + this.height) * 2;
    }

    public int getEdgeCount(){
        return EDGE_COUNT;
    }
}
