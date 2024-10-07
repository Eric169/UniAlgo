package it.unibo.encapsulation.interfaces;

public class StrictBankAccount implements BankAccount {
    
    /*
     * Aggiungere i seguenti campi:
     * - double balance: ammontare del conto
     * - int transactions: numero delle operazioni effettuate
     * - static double ATM_TRANSACTION_FEE = 1: costo delle operazioni via ATM
     */
    private AccountHolder accountHolder;
    private double balance;
    private int transactions;
    private static double ATM_TRANSACTION_FEE = 1;
    private final int id;

    /*
     * Creare un costruttore pubblico che prenda in ingresso un intero (ossia
     * l'id dell'utente) ed un double (ossia, l'ammontare iniziale del conto
     * corrente).
     */
    public StrictBankAccount(final int id, AccountHolder accountHolder){
        this(id, accountHolder, 0);
    }

    public StrictBankAccount(final int id, AccountHolder accountHolder,
                final double balance) {
        this.id = id;
        this.accountHolder = accountHolder;
        this.balance = balance;
        this.transactions = 0;
    }

    /*
     * Si aggiungano selettori per:
     * - ottenere l'id utente del possessore del conto
     * - ottenere il numero di transazioni effettuate
     * - ottenere l'ammontare corrente del conto.
     */
    public int getid() {
        return this.id;
    }

    public double getBalance() {
        return this.balance;
    }

    public int getTransactionsCount() {
        return this.transactions;
    }

    public AccountHolder getAccountHolder(){
        return this.accountHolder;
    }

    public void deposit(final int id, final double amount) {
        if(this.id == id){
            this.transactions++;
            this.balance += amount;
        }
        /*
         * Incrementa il numero di transazioni e aggiunge amount al totale del
         * conto Nota: il deposito va a buon fine solo se l'id utente
         * corrisponde
         */
    }

    public void withdraw(final int id, final double amount) {
        if(this.id == id && amount <= this.balance){
            this.transactions++;
            this.balance -= amount;
        }
        /*
         * Incrementa il numero di transazioni e rimuove amount al totale del
         * conto. Note: - Il conto puo' andare in rosso (ammontare negativo) -
         * Il prelievo va a buon fine solo se l'id utente corrisponde
         */
    }

    public void depositFromATM(final int id, final double amount) {
        if(this.id == id){
            this.transactions++;
            this.balance += amount - ATM_TRANSACTION_FEE;
        }
        /*
         * Incrementa il numero di transazioni e aggiunge amount al totale del
         * conto detraendo le spese (costante ATM_TRANSACTION_FEE) relative
         * all'uso dell'ATM (bancomat) Nota: il deposito va a buon fine solo se
         * l'id utente corrisponde
         */
    }

    public void withdrawFromATM(final int id, final double amount) {
        if(this.id == id && amount + ATM_TRANSACTION_FEE <= this.balance){
            this.transactions++;
            this.balance -= amount + ATM_TRANSACTION_FEE;
        }
        /*
         * Incrementa il numero di transazioni e rimuove amount + le spese
         * (costante ATM_TRANSACTION_FEE) relative all'uso dell'ATM (bancomat)
         * al totale del conto. Note: - Il conto puo' andare in rosso (ammontare
         * negativo) - Il prelievo va a buon fine solo se l'id utente
         * corrisponde
         */
    }

    public void chargeManagementFees(final int id) {
        /*
         * Riduce il bilancio del conto di un ammontare pari alle spese di
         * gestione
         */
        balance -= 5 + 0.1 * (double)this.transactions;
    }
}
