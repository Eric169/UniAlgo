package compilation.lab.math;

public class Student {
    String name;
    String surname;
    int ID;

    Student(String name, String surname, int ID){
        this.name = name;
        this.surname = surname;
        this.ID = ID;
    }

    void PrintStudent(){
        System.out.println("Name: " + name +
            "\nSurname: " + surname + "\nID: " + ID);
    }
}
