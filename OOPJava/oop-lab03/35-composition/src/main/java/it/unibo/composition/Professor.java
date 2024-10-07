package it.unibo.composition;

public class Professor implements User {
    private int id;
    private String name;
    private String surname;
    private String password;
    private String[] courses;

    public Professor(int id, String name, String surname, String password,
            String[] courses){
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.password = password;
        this.courses = courses.clone();
    }

    public String getUsername(){
        return this.name;
    }
    public String getPassword(){
        return this.password;   
    }
    public String getDescription(){
        return "Name: " + this.name + "\nSurname: " + this.surname;
    }

    public int getId(){
        return this.id;
    }

    public void replaceCourse(String courseName, int idx){
        if(idx < 0 || idx >= courses.length) return;
        courses[idx] = courseName;
    }

    public void replaceAllCourses(String[] courses){
        if(courses.length != this.courses.length) return;
        this.courses = courses.clone();
    }
}
