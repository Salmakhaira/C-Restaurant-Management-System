# C-Restaurant-Management-System
# The 50 Snack on Tray Management System

Overview
The 50 Snack on Tray Management System is a comprehensive software solution designed to streamline the daily operations of "The 50 Snack on Tray," a unique hangout spot that limits itself to 50 orders a day. This system manages critical aspects of the business, including employee management, menu management, order processing, and performance summaries. The application is designed with simplicity in mind, ensuring easy navigation and a user-friendly interface.

Features
1. Employee Management
View Employees: Displays a list of all registered employees with details such as ID, name, status, working period (in months), initial salary, and projected salary.
Register Employee: Adds a new employee, automatically generating a unique ID and calculating projected salary based on the working period. The system supports up to 10 active employees and replaces inactive employees when adding new ones.
Change Employee Status: Allows updating an employee's status (active, annual leave, inactive) by inputting their unique ID.
2. Menu Management
View Menu: Lists all registered menu items, showing their ID, name, type (food or beverage), and price.
Register Menu: Adds new menu items with a unique ID generated from the name and random digits. The system can hold up to 50 menu items and allows updating or replacing existing items.
Update Menu: Modifies existing menu items by updating the name, type, and price, and generates a new ID.
3. Order Management
View Order History: Displays the last 5 orders with details such as Order ID, Table No, Employee Name, list of ordered items, quantities, subtotal, service charge, tax, discount, and total payment.
Create New Order: Processes new orders, limiting the system to 50 orders per day. It verifies the availability of menu items, calculates the order total, and includes service charges, tax, and applicable discounts.
4. Daily Report
Summary Report: Generates a daily report that includes the total number of orders, total items ordered (foods and beverages), total transactions, and the "Most Valuable Employee" (MVE) based on the number of orders processed.

Usage
The program runs in a continuous loop, allowing the user to manage employees, menus, and orders, as well as generate daily reports. The system will only terminate when explicitly commanded by the user or when the day's operations are complete.
