package it.unibo.encapsulation.interfaces;

public class TestSimpleBankAccount {

    private TestSimpleBankAccount() {
        /*
         * Prevents object creation from the outside.
         */
    }

    public static void main(final String[] args) {
        // 1) Creare l' AccountHolder relativo a Andrea Rossi con id 1
        AccountHolder aRossi = new AccountHolder("andrea", "Rossi", 1);

        // 2) Creare l' AccountHolder relativo a Alex Bianchi con id 2
        AccountHolder aBianchi = new AccountHolder("Alec", "Bianchi", 2);

        // 3) Creare i due SimpleBankAccount corrispondenti
        SimpleBankAccount aRossiSimpleBankAccount =
                new SimpleBankAccount(aRossi.getUserID(), aRossi);
        SimpleBankAccount aBianchiSimpleBankAccount =
                new SimpleBankAccount(aBianchi.getUserID(), aBianchi);

        // 4) Effettuare una serie di depositi e prelievi
        aRossiSimpleBankAccount.depositFromATM(aRossi.getUserID(), 100);
        aBianchiSimpleBankAccount.depositFromATM(aBianchi.getUserID(), 200);

        /*
         * 5) Stampare a video l'ammontare dei due conti e verificare la
         * correttezza del risultato
         */
        System.out.println("Rossi balance: "
                + aRossiSimpleBankAccount.getBalance() + "\nBianchi balance: "
                + aBianchiSimpleBankAccount.getBalance());

        // 6) Provare a prelevare fornendo un id utente sbagliato
        aRossiSimpleBankAccount.withdraw(10, 100);

        // 7) Controllare nuovamente l'ammontare
        System.out.println("Rossi balance: "
                + aRossiSimpleBankAccount.getBalance() + "\nBianchi balance: "
                + aBianchiSimpleBankAccount.getBalance());
    }
}
