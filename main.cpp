/*
    =====================================================
     UTILITY & ENERGY CONSUMPTION MONITORING SYSTEM
     Group 13 - Atencio & Nemenzo
     Topic: Utilities and Energy Consumption
    =====================================================
    Records the monthly electricity, water, and LPG use of
    households, computes their bills, rates their electricity
    usage, and shows a summary of all households.
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {

    // ---------------- CONSTANTS ----------------
    const int MAX = 50;          // maximum number of households
    const int UTIL = 3;          // number of utilities

    // ---------------- 1D ARRAYS ----------------
    int    householdID[MAX];
    string ownerName[MAX];

    string utilityName[UTIL] = {"Electricity", "Water", "LPG"};
    string utilityUnit[UTIL] = {"kWh", "cu.m", "kg"};
    float  utilityRate[UTIL] = {11.50, 35.00, 80.00};   // pesos per unit

    // ---------------- 2D ARRAY -----------------
    // consumption[household][utility]
    float consumption[MAX][UTIL];

    // ---------------- VARIABLES ----------------
    int    choice = 0;
    int    count  = 0;      // number of saved households
    int    id     = 0;
    int    found  = -1;     // index of the household found
    float  bill   = 0;
    float  total  = 0;
    string level  = "";

    cout << fixed << setprecision(2);

    do {

        // ================= MAIN MENU =================
        cout << "\n==============================================\n";
        cout << "   UTILITY & ENERGY CONSUMPTION MONITORING\n";
        cout << "==============================================\n";
        cout << "       1. Add Household Record\n";
        cout << "       2. View All Households\n";
        cout << "       3. Search Household\n";
        cout << "       4. Update Consumption Record\n";
        cout << "       5. Delete Household Record\n";
        cout << "       6. Display Consumption Summary\n";
        cout << "       7. Exit\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {              // letters were typed
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        // ===== Options 3, 4, 5 all need a household ID first =====
        if (choice >= 3 && choice <= 5) {

            if (count == 0) {
                cout << "\nNo household records yet!\n";
                continue;
            }

            cout << "\nEnter Household ID: ";
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(1000, '\n');
                id = -1;
            }

            found = -1;
            for (int i = 0; i < count; i++) {
                if (householdID[i] == id) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                cout << "\nHousehold not found!\n";
                continue;
            }
        }

        switch (choice) {

        // ================= 1. ADD =================
        case 1:

            if (count == MAX) {
                cout << "\nStorage is full!\n";
                break;
            }

            cout << "\nEnter Household ID : ";
            while (!(cin >> id) || id <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid! Enter a positive number: ";
            }

            found = -1;
            for (int i = 0; i < count; i++) {
                if (householdID[i] == id) {
                    found = i;
                }
            }

            if (found != -1) {
                cout << "\nThat Household ID already exists!\n";
                break;
            }

            householdID[count] = id;

            cout << "Enter Owner Name   : ";
            cin.ignore(1000, '\n');
            getline(cin, ownerName[count]);

            cout << "\n--- Monthly Consumption ---\n";
            for (int j = 0; j < UTIL; j++) {
                cout << left << setw(19) << utilityName[j] + " (" + utilityUnit[j] + ")" << ": ";
                while (!(cin >> consumption[count][j]) || consumption[count][j] < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid! Enter 0 or more: ";
                }
            }

            count++;
            cout << "\nHousehold added successfully!\n";
            break;

        // ================= 2. VIEW ALL =================
        case 2:

            if (count == 0) {
                cout << "\nNo household records yet!\n";
                break;
            }

            cout << "\n=============================== HOUSEHOLD RECORDS ===============================\n";
            cout << left  << setw(6)  << "ID"
                          << setw(18) << "Owner"
                 << right << setw(10) << "Elec(kWh)"
                          << setw(11) << "Water(m3)"
                          << setw(9)  << "LPG(kg)"
                          << setw(14) << "Bill(PHP)"
                          << "   Usage\n";
            cout << "---------------------------------------------------------------------------------\n";

            for (int i = 0; i < count; i++) {

                total = 0;
                for (int j = 0; j < UTIL; j++) {
                    total = total + consumption[i][j] * utilityRate[j];
                }

                if (consumption[i][0] <= 100)       level = "LOW";
                else if (consumption[i][0] <= 250)  level = "AVERAGE";
                else                                level = "HIGH";

                cout << left  << setw(6)  << householdID[i]
                              << setw(18) << ownerName[i].substr(0, 17)
                     << right << setw(10) << consumption[i][0]
                              << setw(11) << consumption[i][1]
                              << setw(9)  << consumption[i][2]
                              << setw(14) << total
                              << "   " << level << "\n";
            }

            cout << "=================================================================================\n";
            break;

        // ================= 3. SEARCH =================
        case 3:

            cout << "\n========== HOUSEHOLD DETAILS ==========\n";
            cout << "Household ID : " << householdID[found] << "\n";
            cout << "Owner Name   : " << ownerName[found] << "\n";
            cout << "---------------------------------------\n";

            total = 0;
            for (int j = 0; j < UTIL; j++) {
                bill  = consumption[found][j] * utilityRate[j];
                total = total + bill;

                cout << left  << setw(12) << utilityName[j]
                     << right << setw(8)  << consumption[found][j] << " "
                     << left  << setw(5)  << utilityUnit[j]
                     << "PHP " << right << setw(9) << bill << "\n";
            }

            if (consumption[found][0] <= 100)       level = "LOW";
            else if (consumption[found][0] <= 250)  level = "AVERAGE";
            else                                    level = "HIGH - try to save energy!";

            cout << "---------------------------------------\n";
            cout << "Total Bill   : PHP " << total << "\n";
            cout << "Usage Level  : " << level << "\n";
            cout << "=======================================\n";
            break;

        // ================= 4. UPDATE =================
        case 4:

            cout << "\nUpdating record of " << ownerName[found] << "\n";

            for (int j = 0; j < UTIL; j++) {
                cout << "New " << left << setw(19) << utilityName[j] + " (" + utilityUnit[j] + ")" << ": ";
                while (!(cin >> consumption[found][j]) || consumption[found][j] < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid! Enter 0 or more: ";
                }
            }

            cout << "\nRecord updated successfully!\n";
            break;

        // ================= 5. DELETE =================
        case 5:

            // move every record after the deleted one up by one
            for (int i = found; i < count - 1; i++) {
                householdID[i] = householdID[i + 1];
                ownerName[i]   = ownerName[i + 1];
                for (int j = 0; j < UTIL; j++) {
                    consumption[i][j] = consumption[i + 1][j];
                }
            }

            count--;
            cout << "\nHousehold deleted successfully!\n";
            break;

        // ================= 6. SUMMARY =================
        case 6: {

            if (count == 0) {
                cout << "\nNo household records yet!\n";
                break;
            }

            float utilTotal[UTIL] = {0, 0, 0};
            float grandTotal  = 0;
            float highestBill = 0;
            int   highest     = 0;
            int   highUsers   = 0;

            for (int i = 0; i < count; i++) {

                total = 0;
                for (int j = 0; j < UTIL; j++) {
                    utilTotal[j] = utilTotal[j] + consumption[i][j];
                    total        = total + consumption[i][j] * utilityRate[j];
                }

                grandTotal = grandTotal + total;

                if (total > highestBill) {
                    highestBill = total;
                    highest     = i;
                }

                if (consumption[i][0] > 250) {
                    highUsers++;
                }
            }

            cout << "\n========== CONSUMPTION SUMMARY ==========\n";
            cout << "Total Households : " << count << "\n\n";

            cout << left  << setw(13) << "Utility"
                 << right << setw(11) << "Total"
                          << setw(11) << "Average" << "\n";
            cout << "-----------------------------------------\n";

            for (int j = 0; j < UTIL; j++) {
                cout << left  << setw(13) << utilityName[j]
                     << right << setw(11) << utilTotal[j]
                              << setw(11) << utilTotal[j] / count
                     << " " << utilityUnit[j] << "\n";
            }

            cout << "-----------------------------------------\n";
            cout << "Total of All Bills : PHP " << grandTotal << "\n";
            cout << "Average Bill       : PHP " << grandTotal / count << "\n";
            cout << "Highest Bill       : " << ownerName[highest]
                 << " (PHP " << highestBill << ")\n";
            cout << "HIGH Usage Homes   : " << highUsers << "\n";
            cout << "=========================================\n";
            break;
        }

        // ================= 7. EXIT =================
        case 7:
            cout << "\nThank you for using the system. Goodbye!\n";
            break;

        default:
            cout << "\nInvalid choice! Please enter 1 to 7.\n";
        }

    } while (choice != 7);

    return 0;
}
