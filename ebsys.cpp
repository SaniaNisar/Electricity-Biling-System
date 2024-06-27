#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <algorithm>

using namespace std;

// Constants
const string EMPLOYEE_DATA_FILE = "EmployeesData.txt";
const string CUSTOMER_INFO_FILE = "CustomerInfo.txt";
const string BILLING_INFO_FILE = "BillingInfo.txt";
const string TARIFF_TAX_INFO_FILE = "TariffTaxInfo.txt";
const string NADRA_DB_FILE = "NADRADB.txt";
const int MAX_METERS_PER_CNIC = 3;

// Structures
struct Employee {
    string username;
    string password;
};

struct Customer {
    int customerId;
    string cnic;
    string name;
    string address;
    string phone;
    string customerType;
    string meterType;
    string connectionDate;
    int regularUnitsConsumed;
    int peakHourUnitsConsumed;
};

struct Billing {
    int customerId;
    string billingMonth;
    int currentMeterReadingRegular;
    int currentMeterReadingPeak;
    string readingEntryDate;
    double costOfElectricity;
    double salesTaxAmount;
    double fixedCharges;
    double totalBillingAmount;
    string dueDate;
    string billPaidStatus;
    string billPaymentDate;
};

// Utility function to read file lines into a vector of strings
vector<string> readFileLines(const string& filename) {
    vector<string> lines;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

// Utility function to write lines to a file
void writeFileLines(const string& filename, const vector<string>& lines) {
    ofstream file(filename);
    for (const string& line : lines) {
        file << line << endl;
    }
    file.close();
}

// Utility function to split a string by delimiter
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to validate a date in format DD/MM/YYYY
bool isValidDate(const string& date) {
    // Add date validation logic
    return true;
}

// Function to generate a 4-digit customer ID
int generateCustomerId() {
    static int id = 1000; // Starting from 1000
    return id++;
}

// Function to load employees from the file
unordered_map<string, Employee> loadEmployees() {
    unordered_map<string, Employee> employees;
    vector<string> lines = readFileLines(EMPLOYEE_DATA_FILE);
    for (const string& line : lines) {
        vector<string> tokens = splitString(line, ',');
        if (tokens.size() == 2) {
            employees[tokens[0]] = { tokens[0], tokens[1] };
        }
    }
    return employees;
}

// Function to save employees to the file
void saveEmployees(const unordered_map<string, Employee>& employees) {
    vector<string> lines;
    for (const auto& pair : employees) {
        lines.push_back(pair.second.username + "," + pair.second.password);
    }
    writeFileLines(EMPLOYEE_DATA_FILE, lines);
}

// Function to change employee password
void changeEmployeePassword(unordered_map<string, Employee>& employees, const string& username, const string& currentPassword, const string& newPassword) {
    if (employees.count(username) && employees[username].password == currentPassword) {
        employees[username].password = newPassword;
        saveEmployees(employees);
        cout << "Password changed successfully." << endl;
    }
    else {
        cout << "Invalid username or password." << endl;
    }
}

// Function to load customers from the file
vector<Customer> loadCustomers() {
    vector<Customer> customers;
    vector<string> lines = readFileLines(CUSTOMER_INFO_FILE);
    for (const string& line : lines) {
        vector<string> tokens = splitString(line, ',');
        if (tokens.size() == 10) {
            Customer customer = { stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7], stoi(tokens[8]), stoi(tokens[9]) };
            customers.push_back(customer);
        }
    }
    return customers;
}

// Function to save customers to the file
void saveCustomers(const vector<Customer>& customers) {
    vector<string> lines;
    for (const Customer& customer : customers) {
        lines.push_back(to_string(customer.customerId) + "," + customer.cnic + "," + customer.name + "," + customer.address + "," + customer.phone + "," + customer.customerType + "," + customer.meterType + "," + customer.connectionDate + "," + to_string(customer.regularUnitsConsumed) + "," + to_string(customer.peakHourUnitsConsumed));
    }
    writeFileLines(CUSTOMER_INFO_FILE, lines);
}

// Function to add a new customer
void addCustomer(vector<Customer>& customers, const Customer& newCustomer) {
    int meterCount = 0;
    for (const Customer& customer : customers) {
        if (customer.cnic == newCustomer.cnic) {
            meterCount++;
        }
    }
    if (meterCount < MAX_METERS_PER_CNIC) {
        customers.push_back(newCustomer);
        saveCustomers(customers);
        cout << "Customer added successfully." << endl;
    }
    else {
        cout << "Not Allowed! Maximum 3 meters allowed per CNIC." << endl;
    }
}

// Function to load billing information from the file
vector<Billing> loadBilling() {
    vector<Billing> billingInfo;
    vector<string> lines = readFileLines(BILLING_INFO_FILE);
    for (const string& line : lines) {
        vector<string> tokens = splitString(line, ',');
        if (tokens.size() == 11) {
            Billing billing = { stoi(tokens[0]), tokens[1], stoi(tokens[2]), stoi(tokens[3]), tokens[4], stod(tokens[5]), stod(tokens[6]), stod(tokens[7]), stod(tokens[8]), tokens[9], tokens[10] };
            billingInfo.push_back(billing);
        }
    }
    return billingInfo;
}

// Function to save billing information to the file
void saveBilling(const vector<Billing>& billingInfo) {
    vector<string> lines;
    for (const Billing& billing : billingInfo) {
        lines.push_back(to_string(billing.customerId) + "," + billing.billingMonth + "," + to_string(billing.currentMeterReadingRegular) + "," + to_string(billing.currentMeterReadingPeak) + "," + billing.readingEntryDate + "," + to_string(billing.costOfElectricity) + "," + to_string(billing.salesTaxAmount) + "," + to_string(billing.fixedCharges) + "," + to_string(billing.totalBillingAmount) + "," + billing.dueDate + "," + billing.billPaidStatus + "," + billing.billPaymentDate);
    }
    writeFileLines(BILLING_INFO_FILE, lines);
}

// Function to add a new billing record
void addBillingRecord(vector<Billing>& billingInfo, const Billing& newBilling) {
    billingInfo.push_back(newBilling);
    saveBilling(billingInfo);
    cout << "Billing record added successfully." << endl;
}

// Function to update bill paid status
void updateBillPaidStatus(vector<Billing>& billingInfo, int customerId, const string& billPaidStatus, const string& billPaymentDate) {
    for (Billing& billing : billingInfo) {
        if (billing.customerId == customerId && billing.billPaidStatus == "Unpaid") {
            billing.billPaidStatus = billPaidStatus;
            billing.billPaymentDate = billPaymentDate;
            saveBilling(billingInfo);
            cout << "Bill paid status updated successfully." << endl;
            return;
        }
    }
    cout << "No unpaid bill found for customer ID " << customerId << "." << endl;
}

// Function to load tariff and tax information
vector<vector<string>> loadTariffTaxInfo() {
    vector<vector<string>> tariffTaxInfo;
    vector<string> lines = readFileLines(TARIFF_TAX_INFO_FILE);
    for (const string& line : lines) {
        tariffTaxInfo.push_back(splitString(line, ','));
    }
    return tariffTaxInfo;
}

// Function to save tariff and tax information
void saveTariffTaxInfo(const vector<vector<string>>& tariffTaxInfo) {
    vector<string> lines;
    for (const vector<string>& row : tariffTaxInfo) {
        lines.push_back(row[0] + "," + row[1] + "," + row[2] + "," + row[3] + "," + row[4]);
    }
    writeFileLines(TARIFF_TAX_INFO_FILE, lines);
}

// Function to update tariff and tax information
void updateTariffTaxInfo(vector<vector<string>>& tariffTaxInfo, int index, const vector<string>& newInfo) {
    if (index >= 0 && index < tariffTaxInfo.size()) {
        tariffTaxInfo[index] = newInfo;
        saveTariffTaxInfo(tariffTaxInfo);
        cout << "Tariff and tax information updated successfully." << endl;
    }
    else {
        cout << "Invalid index." << endl;
    }
}

// Function to login
bool login(const unordered_map<string, Employee>& employees, const string& username, const string& password) {
    return employees.count(username) && employees.at(username).password == password;
}

// Function to view a bill
void viewBill(const vector<Billing>& billingInfo, int customerId) {
    for (const Billing& billing : billingInfo) {
        if (billing.customerId == customerId) {
            cout << "Customer ID: " << billing.customerId << endl;
            cout << "Billing Month: " << billing.billingMonth << endl;
            cout << "Current Meter Reading Regular: " << billing.currentMeterReadingRegular << endl;
            cout << "Current Meter Reading Peak: " << billing.currentMeterReadingPeak << endl;
            cout << "Reading Entry Date: " << billing.readingEntryDate << endl;
            cout << "Cost of Electricity: " << billing.costOfElectricity << endl;
            cout << "Sales Tax Amount: " << billing.salesTaxAmount << endl;
            cout << "Fixed Charges: " << billing.fixedCharges << endl;
            cout << "Total Billing Amount: " << billing.totalBillingAmount << endl;
            cout << "Due Date: " << billing.dueDate << endl;
            cout << "Bill Paid Status: " << billing.billPaidStatus << endl;
            cout << "Bill Payment Date: " << billing.billPaymentDate << endl;
            return;
        }
    }
    cout << "No bill found for customer ID " << customerId << "." << endl;
}

// Function to calculate bill details
void calculateBillDetails(Billing& billing, const vector<Customer>& customers, const vector<vector<string>>& tariffTaxInfo) {
    for (const Customer& customer : customers) {
        if (customer.customerId == billing.customerId) {
            // Get tariff and tax information based on customer's meter type and type (commercial/domestic)
            string meterType = customer.meterType;
            string customerType = customer.customerType;
            double regularUnitPrice = 0.0, peakHourUnitPrice = 0.0, salesTaxPercentage = 0.0, fixedCharges = 0.0;

            // Find the corresponding row in tariffTaxInfo based on meter type and customer type
            for (const auto& row : tariffTaxInfo) {
                if (row[0] == meterType && row[1] == customerType) {
                    regularUnitPrice = stod(row[2]);
                    peakHourUnitPrice = (meterType == "Three Phase") ? stod(row[3]) : 0.0;
                    salesTaxPercentage = stod(row[4]);
                    fixedCharges = stod(row[5]);
                    break;
                }
            }

            // Calculate cost of electricity
            double regularCost = regularUnitPrice * billing.currentMeterReadingRegular;
            double peakHourCost = (meterType == "Three Phase") ? peakHourUnitPrice * billing.currentMeterReadingPeak : 0.0;
            billing.costOfElectricity = regularCost + peakHourCost;

            // Calculate sales tax amount
            billing.salesTaxAmount = (salesTaxPercentage / 100) * billing.costOfElectricity;

            // Calculate fixed charges
            billing.fixedCharges = fixedCharges;

            // Calculate total billing amount
            billing.totalBillingAmount = billing.costOfElectricity + billing.salesTaxAmount + billing.fixedCharges;

            // Calculate due date (7 days after the reading entry date)
            // Assuming reading entry date is in format "DD/MM/YYYY"
            string readingEntryDate = billing.readingEntryDate;
            int day, month, year;
            sscanf_s(readingEntryDate.c_str(), "%d/%d/%d", &day, &month, &year);
            struct tm entryDate = { 0 };
            entryDate.tm_mday = day;
            entryDate.tm_mon = month - 1; // Month is zero-based in struct tm
            entryDate.tm_year = year - 1900; // Year is years since 1900 in struct tm
            time_t entryTime = mktime(&entryDate);
            entryTime += 7 * 24 * 3600; // Add 7 days
            struct tm dueDate;
            localtime_s(&dueDate, &entryTime);
            char dueDateStr[11];
            strftime(dueDateStr, sizeof(dueDateStr), "%d/%m/%Y", &dueDate);
            billing.dueDate = string(dueDateStr);

            // Set bill status to unpaid
            billing.billPaidStatus = "Unpaid";
            break;
        }
    }
}

// Main function for the LESCO billing system
int main() {
    unordered_map<string, Employee> employees = loadEmployees();
    vector<Customer> customers = loadCustomers();
    vector<Billing> billingInfo = loadBilling();
    vector<vector<string>> tariffTaxInfo = loadTariffTaxInfo();

    // Example usage
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (login(employees, username, password)) {
        cout << "Login successful!" << endl;

        // Perform actions based on user input
        int choice;
        do {
            cout << "1. Change Employee Password" << endl;
            cout << "2. Add Customer" << endl;
            cout << "3. Add Billing Record" << endl;
            cout << "4. Update Bill Paid Status" << endl;
            cout << "5. Update Tariff and Tax Information" << endl;
            cout << "6. View Bill" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string currentPassword, newPassword;
                cout << "Enter current password: ";
                cin >> currentPassword;
                cout << "Enter new password: ";
                cin >> newPassword;
                changeEmployeePassword(employees, username, currentPassword, newPassword);
                break;
            }
            case 2: {
                Customer newCustomer;
                newCustomer.customerId = generateCustomerId();
                cout << "Enter CNIC: ";
                cin >> newCustomer.cnic;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, newCustomer.name);
                cout << "Enter Address: ";
                getline(cin, newCustomer.address);
                cout << "Enter Phone: ";
                cin >> newCustomer.phone;
                cout << "Enter Customer Type (commercial/domestic): ";
                cin >> newCustomer.customerType;
                cout << "Enter Meter Type (Single Phase/Three Phase): ";
                cin >> newCustomer.meterType;
                cout << "Enter Connection Date (DD/MM/YYYY): ";
                cin >> newCustomer.connectionDate;
                newCustomer.regularUnitsConsumed = 0;
                newCustomer.peakHourUnitsConsumed = (newCustomer.meterType == "Three Phase") ? 0 : -1;
                addCustomer(customers, newCustomer);
                break;
            }
            case 3: {
                Billing newBilling;
                cout << "Enter Customer ID: ";
                cin >> newBilling.customerId;

                // Ensure customer ID exists
                auto customerIt = find_if(customers.begin(), customers.end(),
                    [&](const Customer& customer) { return customer.customerId == newBilling.customerId; });
                if (customerIt == customers.end()) {
                    cout << "Customer ID not found!" << endl;
                    break;
                }

                cout << "Enter Billing Month: ";
                cin >> newBilling.billingMonth;
                cout << "Enter Current Meter Reading Regular: ";
                cin >> newBilling.currentMeterReadingRegular;

                // Check if the meter type is Three Phase for peak reading
                if (customerIt->meterType == "Three Phase") {
                    cout << "Enter Current Meter Reading Peak: ";
                    cin >> newBilling.currentMeterReadingPeak;
                }
                else {
                    newBilling.currentMeterReadingPeak = -1;
                }

                cout << "Enter Reading Entry Date (DD/MM/YYYY): ";
                cin >> newBilling.readingEntryDate;

                // Calculate bill details
                calculateBillDetails(newBilling, customers, tariffTaxInfo);

                addBillingRecord(billingInfo, newBilling);
                break;
            }

            case 4: {
                int customerId;
                string billPaidStatus, billPaymentDate;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                cout << "Enter Bill Paid Status (Paid/Unpaid): ";
                cin >> billPaidStatus;
                if (billPaidStatus == "Paid") {
                    cout << "Enter Bill Payment Date (DD/MM/YYYY): ";
                    cin >> billPaymentDate;
                }
                else {
                    billPaymentDate = "";
                }
                updateBillPaidStatus(billingInfo, customerId, billPaidStatus, billPaymentDate);
                break;
            }
            case 5: {
                int index;
                vector<string> newInfo(6);
                cout << "Enter Index to Update (0 to " << tariffTaxInfo.size() - 1 << "): ";
                cin >> index;
                cout << "Enter Meter Type (Single Phase/Three Phase): ";
                cin >> newInfo[0];
                cout << "Enter Customer Type (commercial/domestic): ";
                cin >> newInfo[1];
                cout << "Enter Regular Unit Price: ";
                cin >> newInfo[2];
                cout << "Enter Peak Hour Unit Price: ";
                cin >> newInfo[3];
                cout << "Enter Sales Tax Percentage: ";
                cin >> newInfo[4];
                cout << "Enter Fixed Charges: ";
                cin >> newInfo[5];
                updateTariffTaxInfo(tariffTaxInfo, index, newInfo);
                break;
            }
            case 6: {
                int customerId;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                viewBill(billingInfo, customerId);
                break;
            }
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 7);
    }
    else {
        cout << "Invalid username or password." << endl;
    }

    return 0;
}
