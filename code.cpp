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
        return find(availableTimeSlots.begin(), availableTimeSlots.end(), dateTime) != availableTimeSlots.end();
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

    void addWrongCommandWarning(const string& selectedTime) const {
        cout << "Warning: '" << selectedTime << "' is not a valid time slot. Please select from the available time slots." << endl;
    }
};

int main() {

    cout << "Welcome to Baratie \n" << endl;
    Restaurant restaurant("The Great Diner");


    restaurant.addAvailableTimeSlot("2024-04-01 18:00");
    restaurant.addAvailableTimeSlot("2024-04-02 19:30");
    restaurant.addAvailableTimeSlot("2024-04-02 22:30");
    restaurant.addAvailableTimeSlot("2024-04-02 23:30");
    restaurant.addAvailableTimeSlot("2024-04-02 16:30");

    restaurant.displayAvailableTimeSlots();

    
    string selectedTime;
    cout << "\nEnter your preferred time slot: ";
    getline(cin, selectedTime);


    if (!restaurant.isTimeSlotAvailable(selectedTime)) {
        restaurant.addWrongCommandWarning(selectedTime);
        return 1; 
    }

    string customerName;
    int partySize;
    cout << "Enter your name: ";
    getline(cin, customerName);
    cout << "Enter party size: ";
    cin >> partySize;

 
    Reservation reservation(customerName, partySize, selectedTime);

    if (restaurant.bookReservation(reservation)) {
        cout << "Reservation successful.\n";
    }
    else {
        cout << "Reservation failed. Time slot not available.\n";
    }


    restaurant.displayReservations();

    return 0;
}
