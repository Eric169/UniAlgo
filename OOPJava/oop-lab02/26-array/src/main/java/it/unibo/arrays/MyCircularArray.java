package it.unibo.arrays;

class MyCircularArray {

    int[] array;
    int i;

    MyCircularArray() {
        this(10);
    }
    
        MyCircularArray(int size) {
            array = new int[size];
            i = 0;
        }

    void add(final int elem) {
        array[i] = elem;
        i++;
        i %= array.length;
    }

    void reset() {
        for(i = 0; i < array.length; i++) array[i] = 0;
        i = 0;
    }

    void printArray() {
        System.out.print("[");
        for (int i = 0; i < this.array.length - 1; i++) {
            System.out.print(this.array[i] + ",");
        }
        System.out.print(this.array[this.array.length - 1] + "]");
    }

    public static void main(final String[] args) {

        // 1) Creare un array circolare di dieci elementi
        final int size = 10;
        MyCircularArray array = new MyCircularArray(size);

        // 2) Aggiungere gli elementi da 1 a 10 e stampare il contenuto
        // dell'array circolare
        for(int i = 1; i <= size; i++) array.add(i);
        array.printArray();

        // 3) Aggiungere gli elementi da 11 a 15 e stampare il contenuto
        // dell'array circolare
        for(int i = 11; i <= 15; i++) array.add(i);
        array.printArray();

        // 4) Invocare il metodo reset
        array.reset();

        // 5) Stampare il contenuto dell'array circolare
        array.printArray();

        // 6) Aggiungere altri elementi a piacere e stampare il contenuto
        // dell'array circolare
        array.add(1);
        array.printArray();
    }
}
