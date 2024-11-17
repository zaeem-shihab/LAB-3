
#include <stdio.h>
#include <time.h>

// --- CORE PARAMETERS --- //
#define BASE_BALANCE 1000            // Default starting balance
#define TRANSACTION_LIMIT 100        // Maximum allowable bank account transactions

// --- FUNCTION DECLARATIONS --- //
void execute_transactions(const int txn_list[], int txn_count);
void log_transaction(int txn_id, int txn_value, int current_balance);
void display_pending(const int pending_txn[], int count);
void show_summary(int deposits, int withdrawals, int failed_txns);
const char* get_time_stamp(); // For adding timestamps to the logs

// --- ENTRY POINT --- //
int main() {
    // Array of transaction values: positive for deposits, negative for withdrawals
    int txn_data[] = {200, -150, -500, -400, -50, -200, 300};
    int txn_count = sizeof(txn_data) / sizeof(txn_data[0]);

    // System boot: Initialize transaction processing
    printf(">>[INIT] Activating Banking Terminal...\n");
    printf("[SECURE] System Timestamp: %s\n", get_time_stamp());
    execute_transactions(txn_data, txn_count);
    printf("\n[SHUTDOWN] Banking Terminal Offline.\n");

    return 0;
}

// --- TRANSACTION PROCESSING --- //
void execute_transactions(const int txn_list[], int txn_count) {
    int balance = BASE_BALANCE;          // Initializes the user balance
    int pending_txn[TRANSACTION_LIMIT]; // Stores the unprocessed transactions
    int pending_count = 0;              // Counter for the pending transactions

    int total_deposits = 0;             // Total amount deposited 
    int total_withdrawals = 0;          // Total amount withdrawn
    int failed_txns = 0;                // Total number of failed transactions

    printf("\n========== TRANSACTION LOG ==========\n");
    printf("[INFO] Account Balance Initialized: %d AED\n", balance);

    // Iterates through all the transactions
    for (int i = 0; i < txn_count; i++) {
        int txn = txn_list[i];

        // Stops processing if the account balance hits zero
        if (balance == 0) {
            printf("[CRITICAL] Balance exhausted. Cannot process further transactions.\n");
            pending_txn[pending_count++] = txn;
            failed_txns++;
            continue;
        }

        // Processing withdrawals (negative values)
        if (txn < 0) {
            if (balance + txn < 0) {
                // Insufficient balance for withdrawal
                printf("[FAILED] Txn %d: Withdrawal of %d AED declined (Insufficient Funds).\n", i + 1, -txn);
                pending_txn[pending_count++] = txn;
                failed_txns++;
            } else {
                // Execute withdrawal transaction
                balance += txn;
                total_withdrawals += -txn; // Track withdrawal amount
                log_transaction(i + 1, txn, balance);
            }
        } else {
            // Processing deposits (positive values)
            balance += txn;
            total_deposits += txn; // Tracks the deposit amount
            log_transaction(i + 1, txn, balance);
        }
    }

    // Final summary
    printf("\n========== PROCESSING COMPLETE ==========\n");
    printf("[INFO] Final Account Balance: %d AED.\n", balance);

    if (pending_count > 0) {
        printf("[NOTICE] Some transactions remain unprocessed.\n");
        display_pending(pending_txn, pending_count);
    } else {
        printf("[SUCCESS] All transactions completed successfully.\n");
    }

    // Displays the transaction summary to the user
    show_summary(total_deposits, total_withdrawals, failed_txns);
}

// --- TRANSACTION LOGGER --- //
void log_transaction(int txn_id, int txn_value, int current_balance) {
    // Logs each transaction with type (deposit/withdrawal) and updated balance
    printf("[TXN] Transaction %d: %s of %d AED\n", 
           txn_id, 
           (txn_value < 0) ? "Withdrawal" : "Deposit", 
           (txn_value < 0) ? -txn_value : txn_value);
    printf("      Updated Balance: %d AED\n", current_balance);
}

// --- DISPLAY PENDING TRANSACTIONS --- //
void display_pending(const int pending_txn[], int count) {
    // Output of all the unprocessed transactions
    for (int i = 0; i < count; i++) {
        printf("[PENDING] Unprocessed Transactions >> %d AED.\n", pending_txn[i]);
    }
}

// --- TRANSACTION SUMMARY --- //
void show_summary(int deposits, int withdrawals, int failed_txns) {
    printf("\n========== TRANSACTION SUMMARY ==========\n");
    printf("[DATA] Total Deposits      : %d AED\n", deposits);
    printf("[DATA] Total Withdrawals   : %d AED\n", withdrawals);
    printf("[DATA] Failed Transactions : %d\n", failed_txns);
}

// --- GET CURRENT TIMESTAMP --- //
const char* get_time_stamp() {
    static char buffer[20];
    time_t t = time(NULL);
    struct tm* time_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
    return buffer;
}
