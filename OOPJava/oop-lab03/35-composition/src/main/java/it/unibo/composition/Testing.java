package it.unibo.composition;

public class Testing {

    public static void main(final String[] args) {

        // 1)Creare 3 studenti a piacere
        Student a = new Student(0, "ciao", "pizza", "abcd", 1);
        Student b = new Student(1, "aiai", "pasta", "efgh", 2);
        Student c = new Student(2, "bibi", "abcde", "ijkl", 3);

        // 2)Creare 2 docenti a piacere
        Professor ap = new Professor(0, "pippo", "tanto", "abcd",
            new String[]{"corso1", "corso2"});
        Professor bp = new Professor(1, "culo", "culo", "culo",
            new String[]{"Corso3", "Corso4"});

        // 3) Creare due aulee di esame, una con 100 posti una con 80 posti
        ExamRoom ex1 = new ExamRoom(100, "ciaociao", false, false);
        ExamRoom ex2 = new ExamRoom(80, "ciaociao", false, false);
        
        // 4) Creare due esami, uno con nMaxStudents=10, l'altro con
        // nMaxStudents=2
        Exam exam1 = new Exam(100, 10, "corso1", ap, ex2);
        Exam exam2 = new Exam(109, 2, "corso3", bp, ex1);

        // 5) Iscrivere tutti e 3 gli studenti agli esami
        exam1.registerStudent(a);
        exam1.registerStudent(b);
        exam1.registerStudent(c);
        exam2.registerStudent(a);
        exam2.registerStudent(b);
        exam2.registerStudent(c);

        // 6) Stampare in stdout la rapresentazione in stringa dei due esami
        System.out.println(exam1);
        System.out.println(exam2);
    }
}
