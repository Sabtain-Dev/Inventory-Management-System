# 🛒 Inventory Management System (C++ Console App)

A simple Inventory Management System built using **C++** and **linked lists**, featuring admin and user roles, persistent data storage, and product management capabilities.

---

## 🚀 Features

### 👨‍💼 Admin Functionality:
- 🔐 Secure login
- ➕ Add new products
- ✏️ Edit existing product details
- ❌ Delete products
- 🔍 Search products by name or ID
- 📊 Display product list
  - Sort by Name, ID, Price (Low→High, High→Low)
- 💾 Persistent data storage via `products.txt`

### 🙋 User Functionality:
- 🔐 Secure login
- 📊 View all products
  - Sort options included
- 🔍 Search by product name or ID

---

## 🗃️ Data Storage

- Product data is stored in a local file: `products.txt`
- Each product includes:
  - `ID`, `Name`, `Price`, `Quantity`
- Users are stored in code (hardcoded in `main()`)

---

## 🔑 Default Login Credentials

### 👨‍💼 Admin:
- **Username:** `admin`
- **Password:** `admin123`

### 🙋 User:
- **Username:** `user`
- **Password:** `user123`

---

## 🧰 Technologies Used

- 💻 **Language:** C++
- 📁 **File I/O:** `fstream`
- 🧠 **Data Structure:** Linked List
- ⏳ **Delay/Wait:** `windows.h` for Sleep (Windows-only)

---

## 📦 Sample Use Case
- Admin logs in → Adds 3 products → Views them sorted by price
- User logs in → Searches for a product → Views sorted list
- Admin logs in again → Edits one product → Deletes another
  
---

## 📄 License
This project is open-source and free to use for educational or personal purposes.

---

## 🙋‍♂️ Author
- M. Sabtain Khan
- GitHub: [(https://github.com/Sabtain-Dev)]
