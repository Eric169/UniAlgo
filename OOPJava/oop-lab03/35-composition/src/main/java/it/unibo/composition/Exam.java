package it.unibo.composition;

import java.util.Arrays;

public class Exam{
    private int id;
    private int maxStudents;
    private int registeredStudents;
    private String courseName;
    private Professor professor;
    private ExamRoom examRoom;
    private Student[] students;

    public Exam(int id, int maxStudents, String courseName, Professor professor,
                ExamRoom examRoom){
        this.id = id;
        this.maxStudents = maxStudents;
        this.courseName = courseName;
        this.professor = professor;
        this.examRoom = examRoom;
        this.registeredStudents = 0;
        this.students = new Student[this.maxStudents];
    }

    public int getId(){
        return this.id;
    }
    public int getMaxStudents(){
        return this.maxStudents;
    }
    public int getRegisteredStudents(){
        return this.registeredStudents;
    }
    public String getCourseName(){
        return this.courseName;
    }
    public Professor getProfessor(){
        return this.professor;
    }
    public ExamRoom getExamRoom(){
        return this.examRoom;
    }
    public Student[] getStudents(){
        return this.students;
    }

    public void registerStudent(Student student){
        if(this.registeredStudents == this.maxStudents) return;
        this.students[this.registeredStudents] = student;
        this.registeredStudents++;
    }

    public String toString(){
        return "Id: " + this.id + "\nMax students: " + this.maxStudents +
            "\nRegistered students: " + this.registeredStudents +
            "\nCourse Name: " + this.courseName + "\nProfessor:\n" +
            this.professor + "\nExam room: " + this.examRoom + "\nStudents:\n"
            + Arrays.toString(students);
    }
}