# ATM Management System 🏦

A comprehensive **C++** console application that simulates a real-world Automated Teller Machine (ATM) system. The project focuses on object-oriented logic, efficient file handling, and structured data manipulation using vectors and structs.

---

## 🚀 Features

- **Secure Login System:** Validates user access using Account Numbers and Pin Codes directly from a secure database file.
- **Quick Withdraw:** Fast cash withdrawal options (20, 50, 100, 200, 400, 600, 800, 1000).
- **Normal Withdraw:** Allows customized withdrawal amounts (multiples of 5).
- **Instant Deposit:** Seamlessly deposit funds and update account balances in real-time.
- **Check Balance:** Displays current user balance securely.
- **Data Persistence:** Automatically reads and writes all client transactions back to a local flat-file database (`Clients.txt`).

---

## 🛠️ Built With

- **Language:** C++
- **IDE:** Visual Studio
- **Concepts Used:** System Architecture, File Handling (`fstream`), Dynamic Arrays (`std::vector`), Data Structures (`struct`), Strings Tokenization/Splitting.

---

## 💻 How to Run and Test

1. **Download the Files:** Download `ConsoleApplication3.cpp` and `Clients.txt` from this repository.
2. **Setup the Project:** Open **Visual Studio**, create a new C++ Console Application, and paste the code from `ConsoleApplication3.cpp` into your main file.
3. **Database File Placement:** Make sure the `Clients.txt` file is placed in the **same directory** where the project executable runs (Relative Path).
4. **Compile & Run:** Press `Ctrl + F5` or click **Run** to launch the ATM simulator!

---

## 📄 Sample Database Format (`Clients.txt`)
The system reads client accounts formatted with a unique delimiter `/##/`. Example:
```text
A101/##/1234/##/Fadi El Isa/##/0555xxxxxx/##/5000
A102/##/4321/##/John Doe/##/0544xxxxxx/##/1200
