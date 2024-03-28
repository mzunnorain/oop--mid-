#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Reservation {
private:
    string name;
    int partySize;
    string dateTime;

public:
    Reservation(string n, int size, string dt) : name(n), partySize(size), dateTime(dt) {}

    string getDateTime() const {
        return dateTime;
    }

    void display() const {
        cout << "Name: " << name << ", Party Size: " << partySize << ", Date & Time: " << dateTime << endl;
    }
};

class Restaurant {
private:
    string name;
    vector<string> availableTimeSlots;
    vector<Reservation> reservations;

public:
    Restaurant(string n) : name(n) {}

    bool isTimeSlotAvailable(const string& dateTime) const {
        for (const auto& reservation : reservations) {
            if (reservation.getDateTime() == dateTime) {
                return false;
            }
        }
        return true;
    }

    bool bookReservation(const Reservation& reservation) {
        if (isTimeSlotAvailable(reservation.getDateTime())) {
            reservations.push_back(reservation);
            updateAvailableTimeSlots(reservation.getDateTime());
            return true;
        }
        return false;
    }

    void updateAvailableTimeSlots(const string& bookedDateTime) {
        auto it = find(availableTimeSlots.begin(), availableTimeSlots.end(), bookedDateTime);
        if (it != availableTimeSlots.end()) {
            availableTimeSlots.erase(it);
        }
    }

    void displayAvailableTimeSlots() const {
        cout << "Available time slots for " << name << ":\n";
        for (const auto& dateTime : availableTimeSlots) {
            cout << dateTime << endl;
        }
    }

    void displayReservations() const {
        cout << "Reservations for " << name << ":\n";
        for (const auto& reservation : reservations) {
            reservation.display();
        }
    }

    void addAvailableTimeSlot(const string& dateTime) {
        availableTimeSlots.push_back(dateTime);
    }
};

int main() {
    Restaurant restaurant("The Great Diner");

    // Add available time slots
    restaurant.addAvailableTimeSlot("2024-04-01 18:00");
    restaurant.addAvailableTimeSlot("2024-04-02 19:30");
    restaurant.addAvailableTimeSlot("2024-04-02 22:30");
    restaurant.addAvailableTimeSlot("2024-04-02 23:30");
    restaurant.addAvailableTimeSlot("2024-04-02 16:30");

    int choice;
    do {
        cout << "\nWelcome to  Baratie !" << endl;
        cout << "1. Show available time slots" << endl;
        cout << "2. Make a reservation" << endl;
        cout << "3. Display all reservations" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            restaurant.displayAvailableTimeSlots();
            break;
        case 2: {
            string selectedTime;
            cin.ignore(); // Clear the input buffer
            cout << "Enter your preferred time slot: ";
            getline(cin, selectedTime);

            if (!restaurant.isTimeSlotAvailable(selectedTime)) {
                cout << "Selected time slot is not available. Please select from the available time slots." << endl;
                break;
            }

            string customerName;
            int partySize;
            cout << "Enter your name: ";
            getline(cin, customerName);
            cout << "Enter party size: ";
            cin >> partySize;

            cin.ignore(); // Clear the input buffer
            Reservation reservation(customerName, partySize, selectedTime);

            if (restaurant.bookReservation(reservation)) {
                cout << "Reservation successful." << endl;
            }
            else {
                cout << "Reservation failed. Time slot not available." << endl;
            }
            break;
        }
        case 3:
            restaurant.displayReservations();
            break;
        case 4:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
