package it.unibo.encapsulation.interfaces;

public class TestBankAccount {

    private TestBankAccount() {
    }

    public static void main(final String[] args) {
        // 1) Creare l' AccountHolder relativo a Andrea Rossi con id 1
        AccountHolder aRossi = new AccountHolder("andrea", "Rossi", 1);

        // 2) Creare l' AccountHolder relativo a Alex Bianchi con id 2
        AccountHolder aBianchi = new AccountHolder("Alec", "Bianchi", 2);

        /*
        * 3) Dichiarare due variabili di tipo BankAccount ed inizializzarle,
        * rispettivamente, con oggetti di tipo SimpleBankAccount per il conto di
        * Rossi (ammontare iniziale = 0), e di tipo StrictBankAccount per il
        * conto di Bianchi (ammontare iniziale = 0)
        */
        BankAccount aRossiSimpleBankAccount =
                new SimpleBankAccount(aRossi.getUserID(), aRossi);
        BankAccount aBianchiStrictBankAccount =
                new StrictBankAccount(aBianchi.getUserID(), aBianchi);
        /*
         * 4) Prima riflessione: perché è stato possibile fare la new di due
         * classi diverse in variabili dello stesso tipo?
         */
        /*
         * 5) Depositare €10000 in entrambi i conti
         */
        aRossiSimpleBankAccount.deposit(aRossi.getUserID(), 10000);
        aBianchiStrictBankAccount.deposit(aBianchi.getUserID(), 10000);
        /*
         * 6) Prelevare €15000$ da entrambi i conti
         */
        aRossiSimpleBankAccount.withdraw(aRossi.getUserID(), 15000);
        aBianchiStrictBankAccount.withdraw(aBianchi.getUserID(), 15000);
        /*
         * 7) Stampare in stdout l'ammontare corrente
         */
        System.out.println("Rossi balance: "
                + aRossiSimpleBankAccount.getBalance() + "\nBianchi balance: "
                + aBianchiStrictBankAccount.getBalance());
        /*
         * 8) Qual è il risultato e perché?
         */
        /*
         * 9) Depositare nuovamente €10000 in entrambi i conti
         */
        aRossiSimpleBankAccount.deposit(aRossi.getUserID(), 10000);
        aBianchiStrictBankAccount.deposit(aBianchi.getUserID(), 10000);
        /*
         * 10) Invocare il metodo computeManagementFees su entrambi i conti
         */
        aRossiSimpleBankAccount.chargeManagementFees(aRossi.getUserID());;
        aBianchiStrictBankAccount.chargeManagementFees(aBianchi.getUserID());
        /*
         * 11) Stampare a video l'ammontare corrente
         */
        System.out.println("Rossi balance: "
                + aRossiSimpleBankAccount.getBalance() + "\nBianchi balance: "
                + aBianchiStrictBankAccount.getBalance());
        /*
         * 12) Qual è il risultato e perché?
         */
    }
}
