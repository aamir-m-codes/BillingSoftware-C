# BillingSoftware-C
A simple but powerful **Console-based billing software** in C
This project is designed for small shops to manage item billing quickly.

---

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)
![License](https://img.shields.io/badge/License-MIT-green)

---

## 🚀 Features
- Add items with name, price and quantity
- Calculate total bill with discount
- Display formatted bill summary
- Store records of each invoice (bill) in file (unreadable without this software)
- User-friendly menu-driven interface
- Search invoice with customer name
- Delete invoice with customer name

---

## 📂 Project Structure
```
BillingSoftware-C/
│── main.c # Source code
│── Billing.txt # File where store records in binary formate not readable without software
│── README.md # Project documentation
│── LICENSE # Open-source license (MIT recommended)
```
## 🛠️ How to Run

1. Clone the repository:
  ```bash
  git clone https://github.com/aamir-m-codes/BillingSoftware-C.git
  ```
2. Compile the code:
  ```bash
  gcc main.c -o billing
  ```
3. Run the program:
  ```bash
  ./billing
  ```
   
## 📊 Sample Output
  ```bash

                *****"Your" super market*****

                        _-_-_-_-_-_-_-_
Customer        John
Date            Sep 16 2025
Time            18:50:56
-------------------------------------------------------------------------------
Items                   Qty                     price                   Total
-------------------------------------------------------------------------------
Soda                    2                       20.00                   40.00
Snacks                  5                       10.00                   50.00
-------------------------------------------------------------------------------

Net total                                                               90.00
@10 discount                                                            9.00
Final total                                                             81.00
-------------------------------------------------------------------------------
  ```