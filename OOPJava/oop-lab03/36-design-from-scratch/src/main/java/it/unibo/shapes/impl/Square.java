package it.unibo.shapes.impl;

import it.unibo.shapes.api.Polygon;

public class Square implements Polygon{
    private static final int EDGE_COUNT = 4;

    private double edgeLen;
    
    public Square(double edgeLen){
        this.edgeLen = edgeLen;
    }

    public double getArea(){
        return this.edgeLen * this.edgeLen;
    }

    public double getPerimeter(){
        return this.edgeLen * EDGE_COUNT;
    }

    public int getEdgeCount(){
        return EDGE_COUNT;
    }
}
