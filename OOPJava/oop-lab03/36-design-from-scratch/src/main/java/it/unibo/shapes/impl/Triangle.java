package it.unibo.shapes.impl;

import it.unibo.shapes.api.Polygon;

public class Triangle implements Polygon{
    private final int EDGE_COUNT = 3;

    private double edge1;
    private double edge2;
    private double edge3;

    public Triangle(double edge3, double edge1, double edge2){
        this.edge3 = edge3;
        this.edge1 = edge1;
        this.edge2 = edge2;
    }

    public double getArea(){
        double p = this.getPerimeter()/2;
        return Math.sqrt(p * (p-this.edge1) * (p-this.edge2) * (p-this.edge3));
    }

    public double getPerimeter(){
        return this.edge3 + this.edge1 + this.edge2;
    }

    public int getEdgeCount(){
        return EDGE_COUNT;
    }
}
