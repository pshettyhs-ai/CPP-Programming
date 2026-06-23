/*
 * Project  : Parking Lot Management System
 * Author   : Pavan Shetty H S
 * Date     : Week 16
 *
 * Concepts: OOP, Queue (for waiting list), 2D array for slots, time calculation
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <map>
#include <ctime>
#include <cmath>
using namespace std;

enum class VehicleType { TWO_WHEELER, CAR, SUV, TRUCK };

string vehicleTypeStr(VehicleType vt) {
    switch(vt) {
        case VehicleType::TWO_WHEELER: return "2-Wheeler";
        case VehicleType::CAR:         return "Car";
        case VehicleType::SUV:         return "SUV";
        case VehicleType::TRUCK:       return "Truck";
    }
    return "Unknown";
}

double ratePerHour(VehicleType vt) {
    switch(vt) {
        case VehicleType::TWO_WHEELER: return 10.0;
        case VehicleType::CAR:         return 30.0;
        case VehicleType::SUV:         return 50.0;
        case VehicleType::TRUCK:       return 80.0;
    }
    return 30.0;
}

struct Vehicle {
    string      plateNumber;
    string      ownerName;
    VehicleType type;
    time_t      entryTime;
    int         slotNumber;

    Vehicle(string plate, string owner, VehicleType vt)
        : plateNumber(plate), ownerName(owner), type(vt),
          entryTime(time(nullptr)), slotNumber(-1) {}
};

struct ParkingSlot {
    int     slotNo;
    string  vehicleType;  // zone: "2W", "CAR", "SUV", "TRUCK"
    bool    occupied;
    Vehicle* vehicle;

    ParkingSlot(int no, string zone)
        : slotNo(no), vehicleType(zone), occupied(false), vehicle(nullptr) {}
};

class ParkingLot {
    vector<ParkingSlot>    slots;
    queue<Vehicle*>        waitingQueue;
    map<string, Vehicle*>  activeVehicles;  // plate → vehicle
    vector<string>         receiptHistory;
    int totalSlots;
    double totalRevenue;

    string getZone(VehicleType vt) {
        switch(vt) {
            case VehicleType::TWO_WHEELER: return "2W";
            case VehicleType::CAR:         return "CAR";
            case VehicleType::SUV:         return "SUV";
            case VehicleType::TRUCK:       return "TRUCK";
        }
        return "CAR";
    }

    int findAvailableSlot(VehicleType vt) {
        string zone = getZone(vt);
        for (auto& slot : slots) {
            if (!slot.occupied && slot.vehicleType == zone)
                return slot.slotNo;
        }
        return -1;
    }

    double calculateFee(Vehicle* v) {
        time_t now = time(nullptr);
        double hours = difftime(now, v->entryTime) / 3600.0;
        if (hours < 0.5) hours = 0.5;  // minimum 30 min charge
        return ceil(hours * ratePerHour(v->type));
    }

    string formatTime(time_t t) {
        char buf[20];
        strftime(buf, sizeof(buf), "%H:%M %d/%m/%y", localtime(&t));
        return string(buf);
    }

public:
    ParkingLot() : totalRevenue(0) {
        // Create zones: 20 two-wheelers, 30 cars, 10 SUVs, 5 trucks
        for (int i = 1;  i <= 20; i++) slots.emplace_back(i,    "2W");
        for (int i = 21; i <= 50; i++) slots.emplace_back(i,    "CAR");
        for (int i = 51; i <= 60; i++) slots.emplace_back(i,    "SUV");
        for (int i = 61; i <= 65; i++) slots.emplace_back(i,    "TRUCK");
        totalSlots = slots.size();
    }

    void vehicleEntry() {
        string plate, owner;
        int typeChoice;
        cout << "  Plate Number  : "; cin >> plate;
        if (activeVehicles.count(plate)) {
            cout << "  ❌ Vehicle already parked!\n"; return;
        }
        cout << "  Owner Name    : "; cin.ignore(); getline(cin, owner);
        cout << "  Vehicle Type  :" << endl;
        cout << "    1. Two Wheeler (₹10/hr)" << endl;
        cout << "    2. Car         (₹30/hr)" << endl;
        cout << "    3. SUV         (₹50/hr)" << endl;
        cout << "    4. Truck       (₹80/hr)" << endl;
        cout << "  Choice: "; cin >> typeChoice;

        VehicleType vt;
        switch(typeChoice) {
            case 1: vt = VehicleType::TWO_WHEELER; break;
            case 3: vt = VehicleType::SUV;         break;
            case 4: vt = VehicleType::TRUCK;       break;
            default: vt = VehicleType::CAR;
        }

        int slot = findAvailableSlot(vt);
        if (slot == -1) {
            cout << "  ⚠ No slots available for " << vehicleTypeStr(vt) << ". Adding to waiting list.\n";
            waitingQueue.push(new Vehicle(plate, owner, vt));
            cout << "  Queue position: " << waitingQueue.size() << endl;
            return;
        }

        Vehicle* v = new Vehicle(plate, owner, vt);
        v->slotNumber = slot;
        slots[slot - 1].occupied = true;
        slots[slot - 1].vehicle  = v;
        activeVehicles[plate]    = v;

        cout << "  ✅ Vehicle parked!" << endl;
        cout << "  Slot   : " << slot << " (" << getZone(vt) << " Zone)" << endl;
        cout << "  Entry  : " << formatTime(v->entryTime) << endl;
        cout << "  Rate   : ₹" << ratePerHour(vt) << "/hr" << endl;
    }

    void vehicleExit() {
        string plate;
        cout << "  Plate Number: "; cin >> plate;

        if (!activeVehicles.count(plate)) {
            cout << "  ❌ Vehicle not found in parking lot.\n"; return;
        }

        Vehicle* v    = activeVehicles[plate];
        int      slot = v->slotNumber;
        double   fee  = calculateFee(v);
        time_t   now  = time(nullptr);
        double   hrs  = difftime(now, v->entryTime) / 3600.0;

        cout << "\n  ╔═══════════════════════════════════════╗" << endl;
        cout << "  ║         PARKING RECEIPT               ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ Plate   : " << left << setw(28) << plate                 << " ║" << endl;
        cout << "  ║ Owner   : " << left << setw(28) << v->ownerName          << " ║" << endl;
        cout << "  ║ Type    : " << left << setw(28) << vehicleTypeStr(v->type) << " ║" << endl;
        cout << "  ║ Slot    : " << left << setw(28) << slot                  << " ║" << endl;
        cout << "  ║ Entry   : " << left << setw(28) << formatTime(v->entryTime) << " ║" << endl;
        cout << "  ║ Exit    : " << left << setw(28) << formatTime(now)       << " ║" << endl;
        cout << "  ║ Duration: " << left << setw(28) << (to_string((int)ceil(hrs)) + " hr(s)") << " ║" << endl;
        cout << "  ║ Rate    : ₹" << left << setw(27) << (to_string((int)ratePerHour(v->type)) + "/hr") << " ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ TOTAL   : ₹" << left << setw(27) << fixed << setprecision(2) << fee << " ║" << endl;
        cout << "  ╚═══════════════════════════════════════╝" << endl;

        // Free slot
        slots[slot - 1].occupied = false;
        slots[slot - 1].vehicle  = nullptr;
        activeVehicles.erase(plate);
        totalRevenue += fee;

        delete v;

        // Check waiting queue
        if (!waitingQueue.empty()) {
            Vehicle* waiting = waitingQueue.front();
            int availSlot = findAvailableSlot(waiting->type);
            if (availSlot != -1) {
                waitingQueue.pop();
                waiting->slotNumber = availSlot;
                slots[availSlot - 1].occupied = true;
                slots[availSlot - 1].vehicle  = waiting;
                activeVehicles[waiting->plateNumber] = waiting;
                cout << "  ✅ Waiting vehicle " << waiting->plateNumber
                     << " assigned to slot " << availSlot << endl;
            }
        }
    }

    void viewStatus() {
        int occupied = 0;
        for (auto& s : slots) if (s.occupied) occupied++;
        int available = totalSlots - occupied;

        cout << "\n╔══════════════════════════════════════════╗" << endl;
        cout << "║          PARKING LOT STATUS              ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
        cout << "║  Total Slots  : " << left << setw(25) << totalSlots  << " ║" << endl;
        cout << "║  Occupied     : " << left << setw(25) << occupied    << " ║" << endl;
        cout << "║  Available    : " << left << setw(25) << available   << " ║" << endl;
        cout << "║  Waiting Queue: " << left << setw(25) << waitingQueue.size() << " ║" << endl;
        cout << "║  Revenue Today: ₹" << left << setw(24) << fixed << setprecision(2) << totalRevenue << " ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
        cout << "║  Zone     | Total | Occupied | Available ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;

        map<string, pair<int,int>> zoneStats;
        for (auto& s : slots) {
            zoneStats[s.vehicleType].first++;
            if (s.occupied) zoneStats[s.vehicleType].second++;
        }
        for (auto& [zone, stats] : zoneStats) {
            cout << "  " << left << setw(10) << zone
                 << setw(8) << stats.first
                 << setw(10) << stats.second
                 << setw(9) << (stats.first - stats.second) << endl;
        }
        cout << "╚══════════════════════════════════════════╝" << endl;
    }

    void searchVehicle() {
        string plate;
        cout << "  Plate: "; cin >> plate;
        if (!activeVehicles.count(plate)) {
            cout << "  Vehicle not in parking lot.\n"; return;
        }
        Vehicle* v = activeVehicles[plate];
        cout << "  Found! Slot: " << v->slotNumber
             << " | Type: " << vehicleTypeStr(v->type)
             << " | Entry: " << formatTime(v->entryTime)
             << " | Est. Fee: ₹" << calculateFee(v) << endl;
    }

    void run() {
        int choice;
        do {
            cout << "\n╔══════════════════════════════════╗" << endl;
            cout << "║   PARKING MANAGEMENT SYSTEM      ║" << endl;
            cout << "╠══════════════════════════════════╣" << endl;
            cout << "║  1. Vehicle Entry                ║" << endl;
            cout << "║  2. Vehicle Exit & Bill          ║" << endl;
            cout << "║  3. View Lot Status              ║" << endl;
            cout << "║  4. Search Vehicle               ║" << endl;
            cout << "║  5. Exit                         ║" << endl;
            cout << "╚══════════════════════════════════╝" << endl;
            cout << "  Choice: "; cin >> choice;
            switch(choice) {
                case 1: vehicleEntry();  break;
                case 2: vehicleExit();   break;
                case 3: viewStatus();    break;
                case 4: searchVehicle(); break;
                case 5: cout << "  Goodbye!\n"; break;
                default: cout << "  Invalid.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    ParkingLot lot;
    lot.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread ParkingManagement.cpp -o prog
 ================================================================


 ╔══════════════════════════════════╗
 ║   PARKING MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Vehicle Entry                ║
 ║  2. Vehicle Exit & Bill          ║
 ║  3. View Lot Status              ║
 ║  4. Search Vehicle               ║
 ║  5. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Plate Number  :   Owner Name    :   Vehicle Type  :
     1. Two Wheeler (₹10/hr)
     2. Car         (₹30/hr)
     3. SUV         (₹50/hr)
     4. Truck       (₹80/hr)
   Choice:   ✅ Vehicle parked!
   Slot   : 21 (CAR Zone)
   Entry  : 07:01 21/06/26
   Rate   : ₹30/hr

 ╔══════════════════════════════════╗
 ║   PARKING MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Vehicle Entry                ║
 ║  2. Vehicle Exit & Bill          ║
 ║  3. View Lot Status              ║
 ║  4. Search Vehicle               ║
 ║  5. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Plate Number  :   Owner Name    :   Vehicle Type  :
     1. Two Wheeler (₹10/hr)
     2. Car         (₹30/hr)
     3. SUV         (₹50/hr)
     4. Truck       (₹80/hr)
   Choice:   ✅ Vehicle parked!
   Slot   : 1 (2W Zone)
   Entry  : 07:01 21/06/26
   Rate   : ₹10/hr

 ╔══════════════════════════════════╗
 ║   PARKING MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Vehicle Entry                ║
 ║  2. Vehicle Exit & Bill          ║
 ║  3. View Lot Status              ║
 ║  4. Search Vehicle               ║
 ║  5. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ╔══════════════════════════════════════════╗
 ║          PARKING LOT STATUS              ║
 ╠══════════════════════════════════════════╣
 ║  Total Slots  : 65                        ║
 ║  Occupied     : 2                         ║
 ║  Available    : 63                        ║
 ║  Waiting Queue: 0                         ║
 ║  Revenue Today: ₹0.00                     ║
 ╠══════════════════════════════════════════╣
 ║  Zone     | Total | Occupied | Available ║
 ╠══════════════════════════════════════════╣
   2W        20      1         19       
   CAR       30      1         29       
   SUV       10      0         10       
   TRUCK     5       0         5        
 ╚══════════════════════════════════════════╝

 ╔══════════════════════════════════╗
 ║   PARKING MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Vehicle Entry                ║
 ║  2. Vehicle Exit & Bill          ║
 ║  3. View Lot Status              ║
 ║  4. Search Vehicle               ║
 ║  5. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Plate:   Found! Slot: 21 | Type: Car | Entry: 07:01 21/06/26 | Est. Fee: ₹15.00

 ╔══════════════════════════════════╗
 ║   PARKING MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Vehicle Entry                ║
 ║  2. Vehicle Exit & Bill          ║
 ║  3. View Lot Status              ║
 ║  4. Search Vehicle               ║
 ║  5. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Plate Number: 
   ╔═══════════════════════════════════════╗
   ║         PARKING RECEIPT               ║
   ╠═══════════════════════════════════════╣
   ║ Plate   : KA01AB1234                   ║
   ║ Owner   : Demo Owner                   ║
   ║ Type    : Car                          ║
   ║ Slot    : 21                           ║
   ║ Entry   : 07:01 21/06/26               ║
   ║ Exit    : 07:01 21/06/26               ║
   ║ Duration: 0 hr(s)                      ║
   ║ Rate    : ₹30/hr                       ║
   ╠═══════════════════════════════════════╣
   ║ TOTAL   : ₹15.00                       ║
   ╚═══════════════════════════════════════╝

 ╔══════════════════════════════════╗
 ║   PARKING MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Vehicle Entry                ║
 ║  2. Vehicle Exit & Bill          ║
 ║  3. View Lot Status              ║
 ║  4. Search Vehicle               ║
 ║  5. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ╔══════════════════════════════════════════╗
 ║          PARKING LOT STATUS              ║
 ╠══════════════════════════════════════════╣
 ║  Total Slots  : 65                        ║
 ║  Occupied     : 1                         ║
 ║  Available    : 64                        ║
 ║  Waiting Queue: 0                         ║
 ║  Revenue Today: ₹15.00                    ║
 ╠══════════════════════════════════════════╣
 ║  Zone     | Total | Occupied | Available ║
 ╠══════════════════════════════════════════╣
   2W        20      1         19       
   CAR       30      0         30       
   SUV       10      0         10       
   TRUCK     5       0         5        
 ╚══════════════════════════════════════════╝

 ╔══════════════════════════════════╗
 ║   PARKING MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Vehicle Entry                ║
 ║  2. Vehicle Exit & Bill          ║
 ║  3. View Lot Status              ║
 ║  4. Search Vehicle               ║
 ║  5. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Goodbye!

 ================================================================
*/

