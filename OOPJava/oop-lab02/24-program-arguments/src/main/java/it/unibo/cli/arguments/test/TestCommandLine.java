package it.unibo.cli.arguments.test;

class TestCommandLine {

    public static void main(final String[] args) {
        System.out.println("The provided arguments are:");
        for(String s : args){
            System.out.println(" * " + s + ", " + s.length() +
                " character" + (s.length()>1 ? "s" : "") + " long");
        }
        /*
         * Write the main method in such a way that it iterates through the
         * array of arguments, printing each one along with the length of the
         * string - the String class provides an
         *
         * int length()
         *
         * method that returns the length of the String.
         *
         * Example output:
         *
         * $ java it.unibo.cli.arguments.test.TestCommandLine Welcome to the lab
         *
         * The provided arguments are:
         *  * Welcome, 7 characters long
         *  * to, 2 characters long
         *  * the, 3 characters long
         *  * lab, 3 characters long
         */
    }
}
