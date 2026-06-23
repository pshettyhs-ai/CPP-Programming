/*
 * Project  : Hospital Management System
 * Author   : Pavan Shetty H S
 * Date     : Week 15
 *
 * Concepts: Inheritance (Person→Patient/Doctor), Polymorphism, STL, Exception Handling
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// ── Base class
class Person {
protected:
    int    id;
    string name;
    int    age;
    string gender;
    string phone;

public:
    Person(int i, string n, int a, string g, string p)
        : id(i), name(n), age(a), gender(g), phone(p) {}
    virtual ~Person() {}

    int    getId()    const { return id; }
    string getName()  const { return name; }
    int    getAge()   const { return age; }
    string getPhone() const { return phone; }

    virtual void display() const {
        cout << "  ID: " << id << " | Name: " << name
             << " | Age: " << age << " | Phone: " << phone << endl;
    }
    virtual string getType() const = 0;
};

// ── Doctor class (inherits Person)
class Doctor : public Person {
    string specialisation;
    double consultFee;
    string availability;  // MON-FRI, MON-SAT etc.

public:
    Doctor(int i, string n, int a, string g, string p, string spec, double fee, string avail)
        : Person(i, n, a, g, p), specialisation(spec), consultFee(fee), availability(avail) {}

    string getSpecialisation() const { return specialisation; }
    double getConsultFee()     const { return consultFee; }

    string getType() const override { return "Doctor"; }

    void display() const override {
        cout << "  Dr. " << left << setw(22) << name
             << "Spec: " << setw(18) << specialisation
             << "Fee: ₹" << setw(7) << consultFee
             << "Avail: " << availability << endl;
    }
};

// ── Patient class (inherits Person)
class Patient : public Person {
    string   bloodGroup;
    string   address;
    string   disease;
    int      doctorId;
    string   admitDate;
    bool     isAdmitted;
    double   totalBill;

public:
    Patient(int i, string n, int a, string g, string p, string bg, string addr)
        : Person(i, n, a, g, p), bloodGroup(bg), address(addr),
          doctorId(-1), isAdmitted(false), totalBill(0) {}

    void admit(int dId, string date, string dis) {
        doctorId = dId; admitDate = date; disease = dis; isAdmitted = true;
    }
    void discharge()           { isAdmitted = false; }
    void addBill(double amt)   { totalBill += amt; }

    int    getDoctorId()   const { return doctorId; }
    double getTotalBill()  const { return totalBill; }
    bool   getIsAdmitted() const { return isAdmitted; }
    string getDisease()    const { return disease; }
    string getBloodGroup() const { return bloodGroup; }

    string getType() const override { return "Patient"; }

    void display() const override {
        cout << "  [" << id << "] " << left << setw(22) << name
             << "Age:" << setw(4) << age
             << "Blood:" << setw(5) << bloodGroup
             << "Disease:" << setw(20) << disease
             << "[" << (isAdmitted ? "ADMITTED" : "OPD") << "]" << endl;
    }

    void showBill() const {
        cout << "\n  ╔══════════════════════════════╗" << endl;
        cout << "  ║       HOSPITAL BILL          ║" << endl;
        cout << "  ╠══════════════════════════════╣" << endl;
        cout << "  ║ Patient: " << left << setw(19) << name << " ║" << endl;
        cout << "  ║ Disease: " << left << setw(19) << disease << " ║" << endl;
        cout << "  ║ Total  : ₹" << left << setw(18) << fixed << setprecision(2) << totalBill << " ║" << endl;
        cout << "  ║ Status : " << left << setw(19) << (isAdmitted ? "In-patient" : "Discharged") << " ║" << endl;
        cout << "  ╚══════════════════════════════╝" << endl;
    }
};

// ── Appointment
struct Appointment {
    int    patientId, doctorId;
    string date, time_, reason;
    bool   confirmed;
    Appointment(int p, int d, string dt, string t, string r)
        : patientId(p), doctorId(d), date(dt), time_(t), reason(r), confirmed(true) {}
};

// ── Hospital
class Hospital {
    vector<Doctor*>      doctors;
    vector<Patient*>     patients;
    vector<Appointment>  appointments;
    int nextPId = 1001, nextDId = 2001;

    Doctor*  findDoctor(int id) { for (auto d : doctors)  if (d->getId()==id) return d; return nullptr; }
    Patient* findPatient(int id){ for (auto p : patients) if (p->getId()==id) return p; return nullptr; }

public:
    Hospital() {
        doctors.push_back(new Doctor(nextDId++, "Arun Sharma",   45, "M", "9800000001", "Cardiology",      800, "MON-SAT"));
        doctors.push_back(new Doctor(nextDId++, "Sunita Rao",    38, "F", "9800000002", "Neurology",       1000,"MON-FRI"));
        doctors.push_back(new Doctor(nextDId++, "Vikram Patel",  52, "M", "9800000003", "Orthopaedics",    600, "MON-SAT"));
        doctors.push_back(new Doctor(nextDId++, "Meena Nair",    41, "F", "9800000004", "Gynaecology",     700, "MON-FRI"));
        doctors.push_back(new Doctor(nextDId++, "Ravi Kumar",    35, "M", "9800000005", "General Medicine", 400,"MON-SAT"));

        Patient* p1 = new Patient(nextPId++, "Pavan Shetty", 22, "M", "9876500001", "O+", "Mangalore");
        p1->admit(2001, "15/06/2025", "Hypertension");
        p1->addBill(5000);
        patients.push_back(p1);

        Patient* p2 = new Patient(nextPId++, "Ananya R", 30, "F", "9876500002", "B+", "Bangalore");
        p2->admit(2002, "16/06/2025", "Migraine");
        p2->addBill(8500);
        patients.push_back(p2);
    }

    ~Hospital() {
        for (auto d : doctors)  delete d;
        for (auto p : patients) delete p;
    }

    void registerPatient() {
        string name, gender, phone, bg, addr;
        int age;
        cout << "  Name       : "; cin.ignore(); getline(cin, name);
        cout << "  Age        : "; cin >> age;
        cout << "  Gender     : "; cin >> gender;
        cout << "  Phone      : "; cin >> phone;
        cout << "  Blood Group: "; cin >> bg;
        cout << "  Address    : "; cin.ignore(); getline(cin, addr);
        patients.push_back(new Patient(nextPId++, name, age, gender, phone, bg, addr));
        cout << "  ✅ Registered. Patient ID: " << (nextPId - 1) << endl;
    }

    void admitPatient() {
        int pid, did;
        string date, dis;
        cout << "  Patient ID : "; cin >> pid;
        cout << "  Doctor ID  : "; cin >> did;
        cout << "  Disease    : "; cin.ignore(); getline(cin, dis);
        cout << "  Date       : "; getline(cin, date);

        Patient* p = findPatient(pid);
        Doctor*  d = findDoctor(did);
        if (!p) { cout << "  ❌ Patient not found.\n"; return; }
        if (!d) { cout << "  ❌ Doctor not found.\n"; return; }

        p->admit(did, date, dis);
        p->addBill(d->getConsultFee());
        cout << "  ✅ Admitted under Dr. " << d->getName() << endl;
    }

    void generateBill() {
        int pid;
        cout << "  Patient ID: "; cin >> pid;
        Patient* p = findPatient(pid);
        if (!p) { cout << "  ❌ Not found.\n"; return; }
        p->showBill();
    }

    void viewDoctors() {
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    DOCTORS LIST                              ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        for (auto d : doctors) d->display();
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    }

    void viewPatients() {
        cout << "\n--- All Patients ---" << endl;
        for (auto p : patients) p->display();
    }

    void searchPatient() {
        int id; cout << "  Patient ID: "; cin >> id;
        Patient* p = findPatient(id);
        if (p) p->display();
        else   cout << "  ❌ Not found.\n";
    }

    void run() {
        int choice;
        do {
            cout << "\n╔══════════════════════════════╗" << endl;
            cout << "║  HOSPITAL MANAGEMENT SYSTEM  ║" << endl;
            cout << "╠══════════════════════════════╣" << endl;
            cout << "║  1. Register Patient         ║" << endl;
            cout << "║  2. Admit Patient            ║" << endl;
            cout << "║  3. Generate Bill            ║" << endl;
            cout << "║  4. View All Doctors         ║" << endl;
            cout << "║  5. View All Patients        ║" << endl;
            cout << "║  6. Search Patient           ║" << endl;
            cout << "║  7. Exit                     ║" << endl;
            cout << "╚══════════════════════════════╝" << endl;
            cout << "  Choice: "; cin >> choice;
            switch(choice) {
                case 1: registerPatient(); break;
                case 2: admitPatient();    break;
                case 3: generateBill();    break;
                case 4: viewDoctors();     break;
                case 5: viewPatients();    break;
                case 6: searchPatient();   break;
                case 7: cout << "  Goodbye!\n"; break;
                default: cout << "  Invalid.\n";
            }
        } while (choice != 7);
    }
};

int main() {
    Hospital h;
    h.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread HospitalManagement.cpp -o prog
 ================================================================


 ╔══════════════════════════════╗
 ║  HOSPITAL MANAGEMENT SYSTEM  ║
 ╠══════════════════════════════╣
 ║  1. Register Patient         ║
 ║  2. Admit Patient            ║
 ║  3. Generate Bill            ║
 ║  4. View All Doctors         ║
 ║  5. View All Patients        ║
 ║  6. Search Patient           ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Choice: 
 ╔══════════════════════════════════════════════════════════════╗
 ║                    DOCTORS LIST                              ║
 ╠══════════════════════════════════════════════════════════════╣
   Dr. Arun Sharma           Spec: Cardiology        Fee: ₹800    Avail: MON-SAT
   Dr. Sunita Rao            Spec: Neurology         Fee: ₹1000   Avail: MON-FRI
   Dr. Vikram Patel          Spec: Orthopaedics      Fee: ₹600    Avail: MON-SAT
   Dr. Meena Nair            Spec: Gynaecology       Fee: ₹700    Avail: MON-FRI
   Dr. Ravi Kumar            Spec: General Medicine  Fee: ₹400    Avail: MON-SAT
 ╚══════════════════════════════════════════════════════════════╝

 ╔══════════════════════════════╗
 ║  HOSPITAL MANAGEMENT SYSTEM  ║
 ╠══════════════════════════════╣
 ║  1. Register Patient         ║
 ║  2. Admit Patient            ║
 ║  3. Generate Bill            ║
 ║  4. View All Doctors         ║
 ║  5. View All Patients        ║
 ║  6. Search Patient           ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Choice: 
 --- All Patients ---
   [1001] Pavan Shetty          Age:22  Blood:O+   Disease:Hypertension        [ADMITTED]
   [1002] Ananya R              Age:30  Blood:B+   Disease:Migraine            [ADMITTED]

 ╔══════════════════════════════╗
 ║  HOSPITAL MANAGEMENT SYSTEM  ║
 ╠══════════════════════════════╣
 ║  1. Register Patient         ║
 ║  2. Admit Patient            ║
 ║  3. Generate Bill            ║
 ║  4. View All Doctors         ║
 ║  5. View All Patients        ║
 ║  6. Search Patient           ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Choice:   Name       :   Age        :   Gender     :   Phone      :   Blood Group:   Address    :   ✅ Registered. Patient ID: 1003

 ╔══════════════════════════════╗
 ║  HOSPITAL MANAGEMENT SYSTEM  ║
 ╠══════════════════════════════╣
 ║  1. Register Patient         ║
 ║  2. Admit Patient            ║
 ║  3. Generate Bill            ║
 ║  4. View All Doctors         ║
 ║  5. View All Patients        ║
 ║  6. Search Patient           ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Choice:   Patient ID :   Doctor ID  :   Disease    :   Date       :   ✅ Admitted under Dr. Arun Sharma

 ╔══════════════════════════════╗
 ║  HOSPITAL MANAGEMENT SYSTEM  ║
 ╠══════════════════════════════╣
 ║  1. Register Patient         ║
 ║  2. Admit Patient            ║
 ║  3. Generate Bill            ║
 ║  4. View All Doctors         ║
 ║  5. View All Patients        ║
 ║  6. Search Patient           ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Choice:   Patient ID: 
   ╔══════════════════════════════╗
   ║       HOSPITAL BILL          ║
   ╠══════════════════════════════╣
   ║ Patient: Demo Patient        ║
   ║ Disease: Fever               ║
   ║ Total  : ₹800.00             ║
   ║ Status : In-patient          ║
   ╚══════════════════════════════╝

 ╔══════════════════════════════╗
 ║  HOSPITAL MANAGEMENT SYSTEM  ║
 ╠══════════════════════════════╣
 ║  1. Register Patient         ║
 ║  2. Admit Patient            ║
 ║  3. Generate Bill            ║
 ║  4. View All Doctors         ║
 ║  5. View All Patients        ║
 ║  6. Search Patient           ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Choice:   Patient ID:   [1001] Pavan Shetty          Age:22  Blood:O+   Disease:Hypertension        [ADMITTED]

 ╔══════════════════════════════╗
 ║  HOSPITAL MANAGEMENT SYSTEM  ║
 ╠══════════════════════════════╣
 ║  1. Register Patient         ║
 ║  2. Admit Patient            ║
 ║  3. Generate Bill            ║
 ║  4. View All Doctors         ║
 ║  5. View All Patients        ║
 ║  6. Search Patient           ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Choice:   Goodbye!

 ================================================================
*/

