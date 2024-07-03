# Electricity-Biling-System

## Overview
The Electricity Billing System is a C++ console application designed to manage electricity billing for customers. The system allows employees to log in, add new customers, add billing records, update bill statuses, and view tariff and tax information. It ensures that each customer has a maximum of three meters associated with their CNIC and calculates billing amounts based on the customer's meter type and consumption.

## Features
* Employee Login
* Change Employee Password
* Add New Customer
* Add Billing Record
* Update Bill Paid Status
* Update Tariff and Tax Information
* View Bill

## File Structure
* main.cpp: The main program file containing the implementation of the Electricity billing system.
* EmployeesData.txt: Stores employee usernames and passwords.
* CustomerInfo.txt: Stores customer information including customer ID, CNIC, name, address, phone, customer type, meter type, connection date, and units consumed.
* BillingInfo.txt: Stores billing records including customer ID, billing month, meter readings, entry date, cost of electricity, sales tax amount, fixed charges, total billing amount, due date, bill paid status, and bill payment date.
* TariffTaxInfo.txt: Stores tariff and tax information based on meter type and customer type.
* NADRADB.txt: This file is not used in the current implementation but can be used for future enhancements.

## Notes
- Ensure the data files are in the same directory as the executable.
- Modify the EMPLOYEE_DATA_FILE, CUSTOMER_INFO_FILE, BILLING_INFO_FILE, and TARIFF_TAX_INFO_FILE constants in the code if the file paths are different.
