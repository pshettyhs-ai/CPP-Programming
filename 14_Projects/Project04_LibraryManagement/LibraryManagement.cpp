/*
 * Project  : Library Management System
 * Author   : Pavan Shetty H S
 * Date     : Week 15
 *
 * Concepts: OOP, Linked List (for book catalog), STL, File I/O, dates
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
using namespace std;

struct Book {
    int    id;
    string title;
    string author;
    string isbn;
    string category;
    int    totalCopies;
    int    availableCopies;
    double price;

    Book() : id(0), totalCopies(0), availableCopies(0), price(0) {}
    Book(int i, string t, string a, string isb, string cat, int copies, double pr)
        : id(i), title(t), author(a), isbn(isb), category(cat),
          totalCopies(copies), availableCopies(copies), price(pr) {}

    bool isAvailable() const { return availableCopies > 0; }

    void display() const {
        cout << "  ID: " << left << setw(5) << id
             << "Title: " << setw(32) << title.substr(0, 30)
             << "Author: " << setw(20) << author.substr(0, 18)
             << "Avail: " << availableCopies << "/" << totalCopies << endl;
    }
};

struct IssueRecord {
    int    memberId;
    int    bookId;
    string bookTitle;
    string issueDate;
    string returnDate;
    bool   returned;
    double fine;

    IssueRecord(int mId, int bId, string title, string iDate, string rDate)
        : memberId(mId), bookId(bId), bookTitle(title),
          issueDate(iDate), returnDate(rDate), returned(false), fine(0.0) {}
};

struct Member {
    int    id;
    string name;
    string email;
    string phone;
    string memberType;  // STUDENT, FACULTY, STAFF
    int    booksIssued;
    int    maxBooks;

    Member() : id(0), booksIssued(0), maxBooks(3) {}
    Member(int i, string n, string e, string p, string type)
        : id(i), name(n), email(e), phone(p), memberType(type),
          booksIssued(0) {
        maxBooks = (type == "FACULTY") ? 5 : 3;
    }

    bool canIssueMore() const { return booksIssued < maxBooks; }

    void display() const {
        cout << "  ID: " << left << setw(6) << id
             << "Name: " << setw(22) << name
             << "Type: " << setw(10) << memberType
             << "Books: " << booksIssued << "/" << maxBooks << endl;
    }
};

class Library {
private:
    vector<Book>        books;
    vector<Member>      members;
    vector<IssueRecord> issueRecords;
    int nextBookId   = 1001;
    int nextMemberId = 5001;

    string getCurrentDate() {
        time_t now = time(nullptr);
        char buf[20];
        strftime(buf, sizeof(buf), "%d/%m/%Y", localtime(&now));
        return string(buf);
    }

    string getDueDate(int days = 14) {
        time_t now  = time(nullptr) + days * 86400;
        char buf[20];
        strftime(buf, sizeof(buf), "%d/%m/%Y", localtime(&now));
        return string(buf);
    }

    Book*   findBook(int id) {
        for (auto& b : books)   if (b.id == id) return &b;
        return nullptr;
    }
    Member* findMember(int id) {
        for (auto& m : members) if (m.id == id) return &m;
        return nullptr;
    }

public:
    Library() {
        // Seed with books
        books.emplace_back(nextBookId++, "The C++ Programming Language", "Bjarne Stroustrup", "978-0321563842", "Programming", 3, 1200.0);
        books.emplace_back(nextBookId++, "Effective C++",                "Scott Meyers",      "978-0321334879", "Programming", 2, 850.0);
        books.emplace_back(nextBookId++, "Clean Code",                   "Robert C. Martin",  "978-0132350884", "Software Engg", 4, 650.0);
        books.emplace_back(nextBookId++, "Introduction to Algorithms",   "CLRS",              "978-0262033848", "Algorithms",  2, 1500.0);
        books.emplace_back(nextBookId++, "Computer Networks",            "Tanenbaum",         "978-0132126953", "Networks",    3, 900.0);
        books.emplace_back(nextBookId++, "Operating System Concepts",    "Galvin",            "978-1119320913", "OS",          3, 950.0);
        books.emplace_back(nextBookId++, "Database System Concepts",     "Silberschatz",      "978-0073523323", "DBMS",        2, 800.0);

        // Seed with members
        members.emplace_back(nextMemberId++, "Pavan Shetty H S", "pavan@uni.edu",  "9876543210", "STUDENT");
        members.emplace_back(nextMemberId++, "Dr. Ramesh Kumar", "ramesh@uni.edu", "9876543211", "FACULTY");
        members.emplace_back(nextMemberId++, "Priya Singh",      "priya@uni.edu",  "9876543212", "STUDENT");
    }

    void addBook() {
        string title, author, isbn, category;
        int copies; double price;
        cout << "  Title    : "; cin.ignore(); getline(cin, title);
        cout << "  Author   : "; getline(cin, author);
        cout << "  ISBN     : "; cin >> isbn;
        cout << "  Category : "; cin >> category;
        cout << "  Copies   : "; cin >> copies;
        cout << "  Price ₹  : "; cin >> price;
        books.emplace_back(nextBookId++, title, author, isbn, category, copies, price);
        cout << "  ✅ Book added. ID: " << (nextBookId - 1) << endl;
    }

    void addMember() {
        string name, email, phone, type;
        cout << "  Name  : "; cin.ignore(); getline(cin, name);
        cout << "  Email : "; cin >> email;
        cout << "  Phone : "; cin >> phone;
        cout << "  Type (STUDENT/FACULTY/STAFF): "; cin >> type;
        members.emplace_back(nextMemberId++, name, email, phone, type);
        cout << "  ✅ Member added. ID: " << (nextMemberId - 1) << endl;
    }

    void issueBook() {
        int memberId, bookId;
        cout << "  Member ID: "; cin >> memberId;
        cout << "  Book ID  : "; cin >> bookId;

        Member* mem = findMember(memberId);
        Book*   bk  = findBook(bookId);

        if (!mem) { cout << "  ❌ Member not found.\n"; return; }
        if (!bk)  { cout << "  ❌ Book not found.\n"; return; }
        if (!mem->canIssueMore()) { cout << "  ❌ Member reached max book limit.\n"; return; }
        if (!bk->isAvailable())   { cout << "  ❌ No copies available.\n"; return; }

        string issued = getCurrentDate();
        string due    = getDueDate(14);
        issueRecords.emplace_back(memberId, bookId, bk->title, issued, due);
        bk->availableCopies--;
        mem->booksIssued++;

        cout << "  ✅ Book issued successfully!" << endl;
        cout << "  Book  : " << bk->title << endl;
        cout << "  Member: " << mem->name << endl;
        cout << "  Issued: " << issued    << endl;
        cout << "  Due   : " << due       << endl;
    }

    void returnBook() {
        int memberId, bookId;
        cout << "  Member ID: "; cin >> memberId;
        cout << "  Book ID  : "; cin >> bookId;

        for (auto& rec : issueRecords) {
            if (rec.memberId == memberId && rec.bookId == bookId && !rec.returned) {
                rec.returned = true;
                Book*   bk  = findBook(bookId);
                Member* mem = findMember(memberId);
                if (bk)  bk->availableCopies++;
                if (mem) mem->booksIssued--;

                cout << "  ✅ Book returned successfully!" << endl;
                cout << "  Book: " << rec.bookTitle << endl;
                if (rec.fine > 0)
                    cout << "  Fine: ₹" << fixed << setprecision(2) << rec.fine << endl;
                else
                    cout << "  No fine." << endl;
                return;
            }
        }
        cout << "  ❌ Issue record not found.\n";
    }

    void searchBooks() {
        cout << "  Search by: 1.Title  2.Author  3.Category\n  Choice: ";
        int ch; cin >> ch;
        string query; cin.ignore(); getline(cin, query);
        transform(query.begin(), query.end(), query.begin(), ::tolower);

        bool found = false;
        cout << "\n  Search results for '" << query << "':\n";
        for (auto& b : books) {
            string field = (ch == 1) ? b.title : (ch == 2) ? b.author : b.category;
            string fl = field;
            transform(fl.begin(), fl.end(), fl.begin(), ::tolower);
            if (fl.find(query) != string::npos) {
                b.display();
                found = true;
            }
        }
        if (!found) cout << "  No results found.\n";
    }

    void viewAllBooks() {
        cout << "\n╔═══════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    BOOK CATALOG                                   ║" << endl;
        cout << "╠═══════════════════════════════════════════════════════════════════╣" << endl;
        for (auto& b : books) b.display();
        cout << "╚═══════════════════════════════════════════════════════════════════╝" << endl;
        cout << "  Total books: " << books.size() << endl;
    }

    void viewAllMembers() {
        cout << "\n--- All Members ---" << endl;
        for (auto& m : members) m.display();
    }

    void viewIssueHistory() {
        cout << "\n--- Issue History ---" << endl;
        if (issueRecords.empty()) { cout << "  No records.\n"; return; }
        for (auto& r : issueRecords) {
            cout << "  Member:" << r.memberId << " Book:" << r.bookId
                 << " '" << r.bookTitle.substr(0,25) << "'"
                 << " Issued:" << r.issueDate
                 << " Due:" << r.returnDate
                 << " [" << (r.returned ? "RETURNED" : "ACTIVE") << "]" << endl;
        }
    }

    void run() {
        int choice;
        do {
            cout << "\n╔══════════════════════════════════╗" << endl;
            cout << "║   LIBRARY MANAGEMENT SYSTEM      ║" << endl;
            cout << "╠══════════════════════════════════╣" << endl;
            cout << "║  1. Add Book                     ║" << endl;
            cout << "║  2. Add Member                   ║" << endl;
            cout << "║  3. Issue Book                   ║" << endl;
            cout << "║  4. Return Book                  ║" << endl;
            cout << "║  5. Search Books                 ║" << endl;
            cout << "║  6. View All Books               ║" << endl;
            cout << "║  7. View All Members             ║" << endl;
            cout << "║  8. Issue History                ║" << endl;
            cout << "║  9. Exit                         ║" << endl;
            cout << "╚══════════════════════════════════╝" << endl;
            cout << "  Choice: ";
            cin >> choice;
            switch(choice) {
                case 1: addBook();         break;
                case 2: addMember();       break;
                case 3: issueBook();       break;
                case 4: returnBook();      break;
                case 5: searchBooks();     break;
                case 6: viewAllBooks();    break;
                case 7: viewAllMembers();  break;
                case 8: viewIssueHistory(); break;
                case 9: cout << "  Goodbye!\n"; break;
                default: cout << "  Invalid.\n";
            }
        } while (choice != 9);
    }
};

int main() {
    Library lib;
    lib.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread LibraryManagement.cpp -o prog
 ================================================================


 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ╔═══════════════════════════════════════════════════════════════════╗
 ║                    BOOK CATALOG                                   ║
 ╠═══════════════════════════════════════════════════════════════════╣
   ID: 1001 Title: The C++ Programming Language    Author: Bjarne Stroustrup   Avail: 3/3
   ID: 1002 Title: Effective C++                   Author: Scott Meyers        Avail: 2/2
   ID: 1003 Title: Clean Code                      Author: Robert C. Martin    Avail: 4/4
   ID: 1004 Title: Introduction to Algorithms      Author: CLRS                Avail: 2/2
   ID: 1005 Title: Computer Networks               Author: Tanenbaum           Avail: 3/3
   ID: 1006 Title: Operating System Concepts       Author: Galvin              Avail: 3/3
   ID: 1007 Title: Database System Concepts        Author: Silberschatz        Avail: 2/2
 ╚═══════════════════════════════════════════════════════════════════╝
   Total books: 7

 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 --- All Members ---
   ID: 5001  Name: Pavan Shetty H S      Type: STUDENT   Books: 0/3
   ID: 5002  Name: Dr. Ramesh Kumar      Type: FACULTY   Books: 0/5
   ID: 5003  Name: Priya Singh           Type: STUDENT   Books: 0/3

 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Member ID:   Book ID  :   ✅ Book issued successfully!
   Book  : The C++ Programming Language
   Member: Pavan Shetty H S
   Issued: 21/06/2026
   Due   : 05/07/2026

 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Member ID:   Book ID  :   ✅ Book issued successfully!
   Book  : Clean Code
   Member: Dr. Ramesh Kumar
   Issued: 21/06/2026
   Due   : 05/07/2026

 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Search by: 1.Title  2.Author  3.Category
   Choice: 
   Search results for 'stroustrup':
   ID: 1001 Title: The C++ Programming Language    Author: Bjarne Stroustrup   Avail: 2/3

 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Member ID:   Book ID  :   ✅ Book returned successfully!
   Book: The C++ Programming Language
   No fine.

 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 --- Issue History ---
   Member:5001 Book:1001 'The C++ Programming Langu' Issued:21/06/2026 Due:05/07/2026 [RETURNED]
   Member:5002 Book:1003 'Clean Code' Issued:21/06/2026 Due:05/07/2026 [ACTIVE]

 ╔══════════════════════════════════╗
 ║   LIBRARY MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Book                     ║
 ║  2. Add Member                   ║
 ║  3. Issue Book                   ║
 ║  4. Return Book                  ║
 ║  5. Search Books                 ║
 ║  6. View All Books               ║
 ║  7. View All Members             ║
 ║  8. Issue History                ║
 ║  9. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Goodbye!

 ================================================================
*/

