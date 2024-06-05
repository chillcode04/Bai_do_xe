#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class Vehicle {
private:
	string plate;
	string time_in;
	string time_out;
	Vehicle* next;
public: 
    Vehicle(string plate, string time_in) {
        this->plate = plate;
        this->time_in = time_in;
        this->time_out = "";
        this->next = nullptr;
    }

    string getPlate() {
        return plate;
    }

    string getTimeIn() {
        return time_in;
    }

    string getTimeOut() {
        return time_out;
    }

    void setTimeOut(string time_out) {
        this->time_out = time_out;
    }

    Vehicle* getNext() {
        return next;
    }

    void setNext(Vehicle* next) {
        this->next = next;
    }
};
class ParkingLot {
private:
    Vehicle* head;

public:
    ParkingLot() {
        head = nullptr;
    }

    Vehicle* getHead() {
        return head;
    }
    void addVehicle(string time_in, string plate) {
        Vehicle* vehicle = new Vehicle(plate, time_in);
        if (head == nullptr) {
            head = vehicle;
        }
        else {
            Vehicle* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(vehicle);
        }
    }
    void deleteVehicle(string time_out, string plate) {
        Vehicle* current = head;
        Vehicle* prev = current;
        while (current != nullptr) {
            if (current->getPlate() == plate) {
                prev->setNext(current->getNext());
                delete(current);
                break;
            }
            prev = current;
            current = current->getNext();
        }
    }
    int findVehicle(string plate) {
        int index = 0;
        Vehicle* current = head;
        while (current != nullptr) {
            if (current->getPlate() == plate) {
                return index;
            }
            current = current->getNext();
            index++;
        }
        return -1;
    }

    int cnt_moto() {
        int cnt = 0;
        Vehicle* current = head;
        while (current != nullptr) {
            if (current->getPlate() < "xxxx") cnt++;
            current = current->getNext();
        }
        return cnt;
    }
    int billBike(string time_out, string plate) {
        int bill = 0;
        if (findVehicle(plate) == -1) return -1; // khong tim thay xe
        Vehicle* current = head;
        for (int i = 0; i < findVehicle(plate); i++) current = current->getNext(); // curren chay den chi so cua plate
        if (current->getTimeIn() < "06:00:00") {
            if (time_out < "06:00:00") bill = 2;
            else if (time_out > "06:00:00" && time_out < "18:00:00") bill = 3;
            else bill = 5;
        }
        else {
            if (time_out < "18:00:00") bill = 1;
            else bill = 3;
        }
        return bill;
    }

    int billMoto(string time_out, string plate) {
        int bill = 0;
        if (findVehicle(plate) == -1) return -1; // khong tim thay xe
        Vehicle* current = head;
        for (int i = 0; i < findVehicle(plate); i++) current = current->getNext(); // curren chay den chi so cua plate
        if (current->getTimeIn() < "06:00:00") {
            if (time_out < "06:00:00") bill = 5;
            else if (time_out > "06:00:00" && time_out < "18:00:00") bill = 8;
            else bill = 13;
        }
        else {
            if (time_out < "18:00:00") bill = 3;
            else bill = 8;
        }
        return bill;
    }

    void list(Vehicle* head) {
        while (head != nullptr) {
            cout << head->getTimeIn() << ' ' << head->getPlate() << endl;
            head = head->getNext();
        }
    }

};
int main() {
    int billall = 0;
    ParkingLot parkingLot;
    string input1;
    string input2;
    // Đọc dữ liệu đầu vào
    while (getline(cin, input1)) {
        if (input1 == "*") {
            break; // Kết thúc đọc khi gặp dấu *
        }
        // Phân tích dòng đầu vào để lấy thông tin về thời gian và biển số xe
        string time_in, plate;
        stringstream iss(input1);
        iss >> time_in >> plate;
        parkingLot.addVehicle(time_in, plate);
    }
    while (getline(cin, input2)) {
        if (input2 == "***") {
            break;
        }
        stringstream ss(input2);
        string command;
        ss >> command;

        if (command == "list") {
            parkingLot.list(parkingLot.getHead());
        }

        else if (command == "in") {
            string time_in, plate;
            ss >> time_in >> plate;
            if (parkingLot.findVehicle(plate) == -1) {
                //TH khong co xe trong bai
                parkingLot.addVehicle(time_in, plate);
                cout << 1 << endl;
            }
            else {
                //TH da co xe trong bai
                cout << 0 << endl; 
            }
        }

        else if (command == "find") {
            string plate;
            ss >> plate;
            cout << parkingLot.findVehicle(plate) << endl;
        }

        else if (command == "out") {
            string time_out, plate;
            ss >> time_out >> plate;
            if (parkingLot.findVehicle(plate) == -1) {
                // TH khong co xe trong bai
                cout << 0 << endl;
            }
            else {
                if (plate < "xxxx") billall += parkingLot.billMoto(time_out, plate);
                else billall += parkingLot.billBike(time_out, plate);
                parkingLot.deleteVehicle(time_out, plate);
                cout << 1;
            }
        }

        else if (command == "cnt-moto") {
            cout << parkingLot.cnt_moto() << endl;
        }

        else if (command == "bill") {
            string time_out, plate;
            ss >> time_out >> plate;
            if (plate < "xxxx") {
                cout << parkingLot.billMoto(time_out, plate) << endl;
            }
            else {
                cout << parkingLot.billBike(time_out, plate) << endl;
            }
        }

        else if (command == "billall") {
            cout << billall << endl;
        }
    }
}