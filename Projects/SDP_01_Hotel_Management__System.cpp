#include <iostream>
#include <istream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <conio.h>
#include <set>
#include <windows.h>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;

int singleACCost = 100;
int singleNonACCost = 50;
int dualACCost = 200;
int dualNonACCost = 100;
double restaurantBill = 0.0;
string name;
string address;
string contactNumber;
string email;

int main();
void screenClear();
void color();
void Title();
void retrieveAndDisplayBill();
void displayBill(double totalCost);
void displayAllBills();
double calculateTotalBill();
void getCustomerInformation();
void chooseSingleRoomType();
void chooseDualRoomType();
void chooseRoomType();
void bookaroom();
void displayRoomAvailability();
void checkOut();
bool login_user();
void register_user();
void forgot_password();

bool is_valid_username(const string &username)
{
    for (char ch : username)
    {
        if (!isalnum(ch) && ch != '_')
        {
            return false;
        }
    }
    return true;
}

bool is_valid_password(const string &password)
{
    if (password.length() < 8 || password.length() > 16)
    {
        return false;
    }

    bool has_upper = false;
    bool has_digit = false;
    bool has_special = false;

    for (char ch : password)
    {
        if (isupper(ch))
        {
            has_upper = true;
        }
        else if (isdigit(ch))
        {
            has_digit = true;
        }
        else if (ispunct(ch))
        {
            has_special = true;
        }
    }

    return has_upper && has_digit && has_special;
}

void DisplayDualNonACAvailability();
void DisplayDualACAvailability();
void DisplaySingleNonACAvailability();
void DisplaySingleACAvailability();
void listAvailableRoomNumbers(int totalRooms);
bool welcomeAnimationShown = false;
void login();
void registr();
void forgot();
int totalSingleACRooms = 20;
int totalSingleNonACRooms = 20;
int totalDualACRooms = 40;
int totalDualNonACRooms = 20;
set<int> bookedRooms;

double placeOrder(int choice, double totalBill, string &itemName, int &itemPrice, int &quantity, string &orderDetails);
double placeRestaurantOrder(double totalBill);
struct CostRecord
{
    string customerName;
    string roomType;
    int roomNumber;
    int nights;
    double roomCost;
    double payment;
};

vector<CostRecord> costHistory;
double totalCost = 0.0;

void SaveTotalCost(double total)
{
    ofstream totalCostFile("total_cost.txt");
    totalCostFile << "Total Cost: BDT" << total << endl;
    totalCostFile.close();
}

double LoadTotalCost()
{
    double total = 0.0;
    ifstream totalCostFile("total_cost.txt");
    string line;

    try
    {
        while (getline(totalCostFile, line))
        {
            size_t pos = line.find('BDT');
            if (pos != string::npos)
            {
                string costStr = line.substr(pos + 1);
                total = stod(costStr);
            }
        }
    }
    catch (const std::invalid_argument &e)
    {
        cerr << "Error converting string to double: " << e.what() << endl;
        total = 0.0;
    }

    totalCostFile.close();
    return total;
}

void AddToCostHistory(const string &customerName, const string &roomType, int roomNumber, int nights, double roomCost, double payment)
{
    CostRecord record;
    record.customerName = customerName;
    record.roomType = roomType;
    record.roomNumber = roomNumber;
    record.nights = nights;
    record.roomCost = roomCost;
    record.payment = payment;

    costHistory.push_back(record);

    totalCost += roomCost;

    ofstream historyFile("cost_history.txt", ios::app);
    if (historyFile.is_open())
    {
        historyFile << "Customer: " << record.customerName << endl;
        historyFile << "Room Type: " << record.roomType << endl;
        historyFile << "Room Number: " << record.roomNumber << endl;
        historyFile << "Nights: " << record.nights << endl;
        historyFile << "Room Cost: BDT" << record.roomCost << endl;
        historyFile << "Payment Amount: BDT" << record.payment << endl;
        historyFile << "---------------------------" << endl;
        historyFile.close();
    }
    else
    {
        cout << "Failed to save cost history to the file." << endl;
    }

    SaveTotalCost(totalCost);
}

void ShowTotalCost()
{
    double totalRoomCost = LoadTotalCost();
    double total = totalRoomCost + restaurantBill;

    system("cls");
    cout << "Total Cost of All Customers" << endl;

    if (costHistory.empty())
    {
        cout << "No room cost history available." << endl;
    }
    else
    {
        cout << "Total Room Cost: BDT" << totalRoomCost << endl;
    }

    cout << "Total Restaurant Bill: BDT" << restaurantBill << endl;

    cout << "Total Cost (Room + Restaurant): BDT " << total << endl;

    cout << "Press any key to continue...";
    getch();
    bookaroom();
}

void ShowCostHistory()
{
    system("cls");
    cout << "Cost History" << endl;

    ifstream historyFile("cost_history.txt");
    if (historyFile.is_open())
    {
        string line;
        while (getline(historyFile, line))
        {
            cout << line << endl;
        }
        historyFile.close();
    }
    else
    {
        cout << "No cost history available." << endl;
    }

    cout << "Press any key to continue...";
    getch();
    bookaroom();
}

void setRoomCosts()
{
    singleACCost = 5000.0;
    singleNonACCost = 2500.0;
    dualACCost = 10000.0;
    dualNonACCost = 5000.0;

    int placeOrder(int choice, int &totalBill, string &itemName, int &itemPrice, int &quantity, string &orderDetails);
    void displayMenu();
}

int getStayDuration()
{
    int duration;
    cout << "Enter the number of nights you will be staying: ";
    cin >> duration;
    return duration;
}

void bill_single_ac()
{
    int stayDuration = getStayDuration();
    string roomTypeName = "Single AC";

    double cost = singleACCost;
    totalCost = cost * stayDuration;

    ofstream totalCostFile("total_cost.txt");
    totalCostFile << totalCost << endl;
    totalCostFile.close();

    cout << fixed << setprecision(2);
    cout << "Room Type: " << roomTypeName << endl;
    cout << "Cost per night: BDT" << cost << endl;
    cout << "Stay Duration: " << stayDuration << " nights" << endl;
    cout << "Total Cost: BDT" << totalCost << endl;

    displayBill(totalCost);
}

void bill_single_non_ac()
{
    int stayDuration = getStayDuration();
    string roomTypeName = "Single Non-AC";

    double cost = singleNonACCost;
    totalCost = cost * stayDuration;

    ofstream totalCostFile("total_cost.txt");
    totalCostFile << totalCost << endl;
    totalCostFile.close();

    cout << fixed << setprecision(2);
    cout << "Room Type: " << roomTypeName << endl;
    cout << "Cost per night: BDT" << cost << endl;
    cout << "Stay Duration: " << stayDuration << " nights" << endl;
    cout << "Total Cost: BDT" << totalCost << endl;

    displayBill(totalCost);
}

void bill_dual_ac()
{
    int stayDuration = getStayDuration();
    string roomTypeName = "Dual AC";

    double cost = dualACCost;
    totalCost = cost * stayDuration;

    ofstream totalCostFile("total_cost.txt");
    totalCostFile << totalCost << endl;
    totalCostFile.close();

    cout << fixed << setprecision(2);
    cout << "Room Type: " << roomTypeName << endl;
    cout << "Cost per night: BDT" << cost << endl;
    cout << "Stay Duration: " << stayDuration << " nights" << endl;
    cout << "Total Cost: BDT" << totalCost << endl;

    displayBill(totalCost);
}

void bill_dual_non_ac()
{
    int stayDuration = getStayDuration();
    string roomTypeName = "Dual Non-AC";

    double cost = dualNonACCost;
    totalCost = cost * stayDuration;

    ofstream totalCostFile("total_cost.txt");
    totalCostFile << totalCost << endl;
    totalCostFile.close();

    cout << fixed << setprecision(2);
    cout << "Room Type: " << roomTypeName << endl;
    cout << "Cost per night: BDT" << cost << endl;
    cout << "Stay Duration: " << stayDuration << " nights" << endl;
    cout << "Total Cost: BDT" << totalCost << endl;

    displayBill(totalCost);
}

void welcome_ani()
{
    if (!welcomeAnimationShown)
    {
        string welcome = "\t\t  Hotel  Management  System \n\n\t\t   Welcome To Hotel Relax \n\n\n\t Developed By: \t\t\t TEAM INFINITY \n\n\n";
        for (char c : welcome)
        {
            cout << c;
            Sleep(100);
        }
        cout << std::endl;
        welcomeAnimationShown = true;

        cout << "\t\t Press any key to continue...!! \n";
        _getch();
    }
}

void screenClear()
{
    system("CLS");
}
void color()
{
    system("color A");
}

void Title()
{
    cout << "\t\t ................................\n\n";
    cout << "\t\t\tWelcome to login page\n\n";
    cout << "\t\t ................................\n";
    cout << "\t\t[Customer Login and Access Control]\n";
    cout << "\t\t ===============================\n\n";
}

void log_reg()
{

    int choice;

    do
    {
        cout << "1. Register\n2. Login\n3. Forgot Password\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            register_user();
            break;
        case 2:
            if (login_user())
            {
                cout << "\t\tLogin successful!" << endl;
                getch();
                bookaroom();
            }
            else
            {
                cout << "Login failed. Invalid username or password." << endl;
            }
            break;
        case 3:
            forgot_password();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

    } while (choice != 4);
}

int main()
{
    ofstream createFile("bills.txt", ios::app);
    if (createFile)
    {
        createFile.close();
    }

    ifstream totalCostFile("total_cost.txt");
    if (totalCostFile)
    {
        totalCostFile >> totalCost;
        totalCostFile.close();
    }

    screenClear();
    color();
    welcome_ani();
    screenClear();
    Title();
    log_reg();
    setRoomCosts();
    LoadTotalCost();
    totalCost = LoadTotalCost();

    ifstream historyFile("cost_history.txt");
    if (historyFile.is_open())
    {
        string line;
        CostRecord record;
        while (getline(historyFile, line))
        {
            if (line.find("Room Cost: $") != string::npos)
            {

                size_t pos = line.find('$');
                if (pos != string::npos)
                {
                    string costStr = line.substr(pos + 1);
                    record.roomCost = stod(costStr);
                }

                costHistory.push_back(record);
            }
        }
        historyFile.close();
    }

    ifstream restaurantBillFile("restaurant_bill.txt");
    if (restaurantBillFile)
    {
        restaurantBillFile >> restaurantBill;
        restaurantBillFile.close();
    }

    return 0;
}

void retrieveAndDisplayBill()
{
    ifstream billFile("bills.txt");
    if (!billFile)
    {
        cout << "No bill information found. Please make a booking first." << endl;
        return;
    }

    string line;
    cout << "Billing Information:\n";
    while (getline(billFile, line))
    {
        cout << line << endl;
    }
    billFile.close();

    cout << "Press any key to continue...";
    cin.get();
}

void bookaroom()
{
    int book;
    system("cls");
    cout << "1. Book a room \n 2.Order food \n 3.Show Cost History \n 4.Total Cost \n 5.Check-Out \n 6. Logout" << endl;
    cout << "Enter your choice: ";
    cin >> book;

    if (book == 1)
    {
        system("cls");
        getCustomerInformation();
        cout << "\n\n\t\tThanks for submitting your information";
        getch();
        chooseRoomType();
    }

    else if (book == 2)
    {
        system("cls");
        restaurantBill = placeRestaurantOrder(restaurantBill);
    }

    else if (book == 3)
    {
        system("cls");
        ShowCostHistory();
    }

    else if (book == 4)
    {
        system("cls");
        ShowTotalCost();
    }

    else if (book == 5)
    {
        system("cls");
        checkOut();
    }

    else if (book == 6)
    {
        system("cls");
        main();
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
        bookaroom();
    }
}

void chooseRoomType()
{
    int roomChoice;
    system("cls");
    cout << "1. Single Bed Room\n2. Dual Bed Room\n3. Logout" << endl;
    cout << "Enter your choice: ";
    cin >> roomChoice;

    if (roomChoice == 1)
    {
        chooseSingleRoomType();
    }
    else if (roomChoice == 2)
    {
        chooseDualRoomType();
    }
    else if (roomChoice == 3)
    {
        system("cls");
        main();
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
        chooseRoomType();
    }
}

void chooseSingleRoomType()
{
    int roomType;
    system("cls");
    cout << "1. Single Room (AC)\n2. Single Room (Non-AC)\n3. Back to the main menu" << endl;
    cout << "Enter your choice: ";
    cin >> roomType;

    if (roomType == 1)
    {

        cout << "You chose a Single Room (AC)." << endl;
        getch();
        DisplaySingleACAvailability();
    }
    else if (roomType == 2)
    {

        cout << "You chose a Single Room (Non-AC)." << endl;
        getch();
        DisplaySingleNonACAvailability();
    }
    else if (roomType == 3)
    {
        system("cls");
        bookaroom();
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
        getch();
        chooseSingleRoomType();
    }
}

void chooseDualRoomType()
{
    int roomType;
    system("cls");
    cout << "1. Dual Room (AC)\n2. Dual Room (Non-AC)\n3. Back to the main menu" << endl;
    cout << "Enter your choice: ";
    cin >> roomType;

    if (roomType == 1)
    {

        cout << "You chose a Dual Room (AC)." << endl;
        getch();
        DisplayDualACAvailability();
    }
    else if (roomType == 2)
    {
        cout << "You chose a Dual Room (Non-AC)." << endl;
        getch();
        DisplayDualNonACAvailability();
    }
    else if (roomType == 3)
    {
        system("cls");
        bookaroom();
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
        chooseDualRoomType();
    }
}

void listAvailableRoomNumbers(int totalRooms)
{
    cout << "Available Room Numbers:\n";
    for (int roomNumber = 1; roomNumber <= totalRooms; roomNumber++)
    {
        cout << roomNumber << " ";
    }
    cout << "\nEnter the room number you want to book: ";
}

void CalculateRoomCost(int nights, const string &roomType, double &totalCost)
{

    if (roomType == "Single AC")
    {
        totalCost = singleACCost * nights;
    }
    else if (roomType == "Single Non AC")
    {
        totalCost = singleNonACCost * nights;
    }
    else if (roomType == "Dual AC")
    {
        totalCost = dualACCost * nights;
    }
    else if (roomType == "Dual Non AC")
    {
        totalCost = dualNonACCost * nights;
    }
    else
    {

        cout << "Invalid room type. Using default cost." << endl;
        totalCost = 0;
    }
}

void DisplaySingleACAvailability()
{
    system("cls");
    cout << "Single AC Rooms Availability:" << endl;
    set<int> bookedRooms;

    ifstream bookedFile("single_ac_booked_rooms.txt");
    int bookedRoom;
    while (bookedFile >> bookedRoom)
    {
        bookedRooms.insert(bookedRoom);
    }
    bookedFile.close();

    int totalSingleACRooms = 20;
    int availableRooms = totalSingleACRooms - bookedRooms.size();

    cout << "Total Single AC Rooms: " << availableRooms << endl;

    cout << "Available Room Numbers: ";
    bool available = false;

    for (int roomNumber = 1; roomNumber <= totalSingleACRooms; ++roomNumber)
    {
        if (!bookedRooms.count(roomNumber))
        {
            cout << roomNumber << " ";
            available = true;
        }
    }

    if (!available)
    {
        cout << "No rooms available." << endl;
    }
    else
    {
        cout << endl;

        int roomNumber;
        cout << "Enter the room number you want to book: ";
        cin >> roomNumber;

        if (roomNumber >= 1 && roomNumber <= totalSingleACRooms)
        {
            if (!bookedRooms.count(roomNumber))
            {
                int nights;
                cout << "Enter the number of nights you want to stay: ";
                cin >> nights;

                double roomCost;
                CalculateRoomCost(nights, "Single AC", roomCost);

                cout << "Room " << roomNumber << " costs BDT" << roomCost << " for " << nights << " night(s)." << endl;

                double payment;
                cout << "Please enter the payment amount: BDT";
                cin >> payment;

                if (payment == roomCost)
                {
                    cout << "Room " << roomNumber << " booked successfully!" << endl;
                    bookedRooms.insert(roomNumber);
                    AddToCostHistory(name, "Single AC", roomNumber, nights, roomCost, payment);

                    ofstream bookedFile("single_ac_booked_rooms.txt");
                    for (int bookedRoom : bookedRooms)
                    {
                        bookedFile << bookedRoom << endl;
                    }
                    bookedFile.close();

                    availableRooms = totalSingleACRooms - bookedRooms.size();
                    cout << "Total Single AC Rooms: " << availableRooms << endl;
                }
                else
                {
                    cout << "Payment does not match the room cost. Booking unsuccessful." << endl;
                }
            }
            else
            {
                cout << "Room " << roomNumber << " is already booked. Please choose a different room." << endl;
            }
        }
        else
        {
            cout << "Invalid room number. Please choose a valid room number." << endl;
        }
    }

    cout << "Press any key to continue...";
    getch();
    bookaroom();
}

void DisplaySingleNonACAvailability()
{
    system("cls");
    cout << "Single Non-AC Rooms Availability:" << endl;
    set<int> bookedRooms;

    ifstream bookedFile("single_non_ac_booked_rooms.txt");
    int bookedRoom;
    while (bookedFile >> bookedRoom)
    {
        bookedRooms.insert(bookedRoom);
    }
    bookedFile.close();

    int totalSingleNonACRooms = 20;
    int availableRooms = totalSingleNonACRooms - bookedRooms.size();

    cout << "Total Single Non-AC Rooms: " << availableRooms << endl;

    cout << "Available Room Numbers: ";
    bool available = false;

    for (int roomNumber = 21; roomNumber <= 20 + totalSingleNonACRooms; ++roomNumber)
    {
        if (!bookedRooms.count(roomNumber))
        {
            cout << roomNumber << " ";
            available = true;
        }
    }

    if (!available)
    {
        cout << "No rooms available." << endl;
    }
    else
    {
        cout << endl;

        int roomNumber;
        cout << "Enter the room number you want to book: ";
        cin >> roomNumber;

        if (roomNumber >= 21 && roomNumber <= 20 + totalSingleNonACRooms)
        {
            if (!bookedRooms.count(roomNumber))
            {
                int nights;
                cout << "Enter the number of nights you want to stay: ";
                cin >> nights;

                double roomCost;
                CalculateRoomCost(nights, "Single Non AC", roomCost);

                cout << "Room " << roomNumber << " costs BDT" << roomCost << " for " << nights << " night(s)." << endl;

                double payment;
                cout << "Please enter the payment amount: BDT";
                cin >> payment;

                if (payment == roomCost)
                {
                    cout << "Room " << roomNumber << " booked successfully!" << endl;
                    bookedRooms.insert(roomNumber);
                    AddToCostHistory(name, "Single Non AC", roomNumber, nights, roomCost, payment);

                    ofstream bookedFile("single_non_ac_booked_rooms.txt");
                    for (int bookedRoom : bookedRooms)
                    {
                        bookedFile << bookedRoom << endl;
                    }
                    bookedFile.close();

                    availableRooms = totalSingleNonACRooms - bookedRooms.size();
                    cout << "Total Single Non-AC Rooms: " << availableRooms << endl;
                }
                else
                {
                    cout << "Payment does not match the room cost. Booking unsuccessful." << endl;
                }
            }
            else
            {
                cout << "Room " << roomNumber << " is already booked. Please choose a different room." << endl;
            }
        }
        else
        {
            cout << "Invalid room number. Please choose a valid room number." << endl;
        }
    }

    cout << "Press any key to continue...";
    getch();
    bookaroom();
}

void DisplayDualACAvailability()
{
    system("cls");
    cout << "Dual AC Rooms Availability:" << endl;
    set<int> bookedRooms;

    ifstream bookedFile("dual_ac_booked_rooms.txt");
    int bookedRoom;
    while (bookedFile >> bookedRoom)
    {
        bookedRooms.insert(bookedRoom);
    }
    bookedFile.close();

    int totalDualACRooms = 40;
    int availableRooms = totalDualACRooms - bookedRooms.size();

    cout << "Total Dual AC Rooms: " << availableRooms << endl;

    cout << "Available Room Numbers: ";
    bool available = false;

    for (int roomNumber = 40; roomNumber <= 80; ++roomNumber)
    {
        if (!bookedRooms.count(roomNumber))
        {
            cout << roomNumber << " ";
            available = true;
        }
    }

    if (!available)
    {
        cout << "No rooms available." << endl;
    }
    else
    {
        cout << endl;

        int roomNumber;
        cout << "Enter the room number you want to book: ";
        cin >> roomNumber;

        if (roomNumber >= 40 && roomNumber <= 80)
        {
            if (!bookedRooms.count(roomNumber))
            {
                int nights;
                cout << "Enter the number of nights you want to stay: ";
                cin >> nights;

                double roomCost;
                CalculateRoomCost(nights, "Dual AC", roomCost);

                cout << "Room " << roomNumber << " costs BDT" << roomCost << " for " << nights << " night(s)." << endl;

                double payment;
                cout << "Please enter the payment amount: BDT";
                cin >> payment;

                if (payment == roomCost)
                {
                    cout << "Room " << roomNumber << " booked successfully!" << endl;
                    bookedRooms.insert(roomNumber);
                    AddToCostHistory(name, "Dual AC", roomNumber, nights, roomCost, payment);

                    ofstream bookedFile("dual_ac_booked_rooms.txt");
                    for (int bookedRoom : bookedRooms)
                    {
                        bookedFile << bookedRoom << endl;
                    }
                    bookedFile.close();

                    availableRooms = totalDualACRooms - bookedRooms.size();
                    cout << "Total Dual AC Rooms: " << availableRooms << endl;
                }
                else
                {
                    cout << "Payment does not match the room cost. Booking unsuccessful." << endl;
                }
            }
            else
            {
                cout << "Room " << roomNumber << " is already booked. Please choose a different room." << endl;
            }
        }
        else
        {
            cout << "Invalid room number. Please choose a valid room number." << endl;
        }
    }

    cout << "Press any key to continue...";
    getch();
    bookaroom();
}

void DisplayDualNonACAvailability()
{
    system("cls");
    cout << "Dual Non-AC Rooms Availability:" << endl;
    set<int> bookedRooms;

    ifstream bookedFile("dual_non_ac_booked_rooms.txt");
    int bookedRoom;
    while (bookedFile >> bookedRoom)
    {
        bookedRooms.insert(bookedRoom);
    }
    bookedFile.close();

    int totalDualNonACRooms = 20;
    int availableRooms = totalDualNonACRooms - bookedRooms.size();

    cout << "Total Dual Non-AC Rooms: " << availableRooms << endl;

    cout << "Available Room Numbers: ";
    bool available = false;

    for (int roomNumber = 81; roomNumber <= 100; ++roomNumber)
    {
        if (!bookedRooms.count(roomNumber))
        {
            cout << roomNumber << " ";
            available = true;
        }
    }

    if (!available)
    {
        cout << "No rooms available." << endl;
    }
    else
    {
        cout << endl;

        int roomNumber;
        cout << "Enter the room number you want to book: ";
        cin >> roomNumber;

        if (roomNumber >= 81 && roomNumber <= 100)
        {
            if (!bookedRooms.count(roomNumber))
            {
                int nights;
                cout << "Enter the number of nights you want to stay: ";
                cin >> nights;

                double roomCost;
                CalculateRoomCost(nights, "Dual Non AC", roomCost);

                if (roomCost > 0)
                {
                    cout << "Room " << roomNumber << " costs BDT" << roomCost << " for " << nights << " night(s)." << endl;

                    double payment;
                    cout << "Please enter the payment amount: BDT";
                    cin >> payment;

                    if (payment == roomCost)
                    {
                        cout << "Room " << roomNumber << " booked successfully!" << endl;
                        bookedRooms.insert(roomNumber);
                        AddToCostHistory(name, "Dual Non AC", roomNumber, nights, roomCost, payment);

                        ofstream bookedFile("dual_non_ac_booked_rooms.txt");
                        for (int bookedRoom : bookedRooms)
                        {
                            bookedFile << bookedRoom << endl;
                        }
                        bookedFile.close();

                        availableRooms = totalDualNonACRooms - bookedRooms.size();
                        cout << "Total Dual Non-AC Rooms: " << availableRooms << endl;
                    }
                    else
                    {
                        cout << "Payment does not match the room cost. Booking unsuccessful." << endl;
                    }
                }
                else
                {
                    cout << "Invalid room type. Using default cost." << endl;
                }
            }
            else
            {
                cout << "Room " << roomNumber << " is already booked. Please choose a different room." << endl;
            }
        }
        else
        {
            cout << "Invalid room number. Please choose a valid room number." << endl;
        }
    }

    cout << "Press any key to continue...";
    getch();
    bookaroom();
}

void getCustomerInformation()
{

    cout << "Please enter your information for room booking:\n";

    cout << "Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Address: ";
    getline(cin, address);

    cout << "Contact Number: ";
    getline(cin, contactNumber);

    cout << "Email: ";
    getline(cin, email);

    ofstream customerFile("customer_info.txt", ios::app);
    customerFile << "Name: " << name << endl;
    customerFile << "Address: " << address << endl;
    customerFile << "Contact Number: " << contactNumber << endl;
    customerFile << "Email: " << email << endl;
    customerFile << "---------------------" << endl;
    customerFile.close();

    cout << "Customer information saved.\n";
}

void displayBill(double totalCost)
{
    string name, address, contactNumber, email;

    ifstream customerFile("customer_info.txt");
    string line;
    while (getline(customerFile, line))
    {
        if (line.find("Name: ") != string::npos)
        {
            name = line.substr(6);
        }
        else if (line.find("Address: ") != string::npos)
        {
            address = line.substr(9);
        }
        else if (line.find("Contact Number: ") != string::npos)
        {
            contactNumber = line.substr(16);
        }
        else if (line.find("Email: ") != string::npos)
        {
            email = line.substr(7);
        }
    }
    customerFile.close();

    system("cls");
    cout << "Customer Information:\n";
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Contact Number: " << contactNumber << endl;
    cout << "Email: " << email << endl;

    ofstream billFile("bills.txt", ios::app);
    if (billFile.is_open())
    {
        billFile << "Customer Information:\n";
        billFile << "Name: " << name << "\n";
        billFile << "Address: " << address << "\n";
        billFile << "Contact Number: " << contactNumber << "\n";
        billFile << "Email: " << email << "\n";
        billFile << "Total Cost: BDT" << totalCost << "\n";
        billFile << "---------------------\n";
        billFile.close();
    }

    cout << "Total Cost: BDT" << totalCost << endl;
    cout << "Press any key to continue...";
    getch();
}

void displayAllBills()
{
    ifstream billFile("bills.txt");
    ifstream restaurantOrderFile("order2.txt");

    if (!billFile)
    {
        cout << "No bill information found. Please make a booking first." << endl;
        return;
    }

    string line;
    bool customerInfoFound = false;
    string customerInfo;
    while (getline(billFile, line))
    {
        if (line.find("Customer Information:") != string::npos)
        {
            customerInfoFound = true;
            customerInfo = line + "\n";
        }
        else if (customerInfoFound)
        {
            if (line.find("Total Cost: BDT") != string::npos)
            {
                string restaurantBillLine;
                while (getline(restaurantOrderFile, restaurantBillLine))
                {
                    if (restaurantBillLine.find("Total Cost: BDT") != string::npos)
                    {
                        customerInfo += "Restaurant Bill: " + restaurantBillLine + "\n";
                        break;
                    }
                }

                cout << customerInfo;
                cout << line << endl;
                cout << "---------------------" << endl;

                customerInfo.clear();
                customerInfoFound = false;
            }
            else
            {
                customerInfo += line + "\n";
            }
        }
    }

    billFile.close();
    restaurantOrderFile.close();

    cout << "Press any key to continue...";
    getch();
}

double calculateTotalBill()
{
    ifstream billFile("bills.txt");
    if (!billFile)
    {
        cout << "No bill information found. Please make a booking first." << endl;
        return 0.0;
    }

    double totalBill = 0.0;
    string line;

    while (getline(billFile, line))
    {
        if (line.find("Total Cost: BDT") != string::npos)
        {

            size_t startPos = line.find("BDT");
            if (startPos != string::npos)
            {
                double cost = stod(line.substr(startPos + 1));
                totalBill += cost;
            }
        }
    }

    billFile.close();
    return totalBill;
}

/**.....................................CODE OF REASTURANT...................................**/

void displayMenu()
{
    int tabCount = 5;

    cout << "\n";
    cout << string(tabCount, '\t') << "------- WELCOME TO FOOD ORDERING SYSTEM OF  -------" << endl;

    cout << string(tabCount, '\t') << "****************************************************" << endl;
    cout << string(tabCount, '\t') << "*          HOTEL RELAX's RESTAURANT                *" << endl;
    cout << string(tabCount, '\t') << "****************************************************" << endl;
    cout << string(tabCount, '\t') << "            ----- START YOUR ORDER -----" << endl;

    cout << string(tabCount, '\t') << "  MENU                                         PRICE" << endl;
    cout << string(tabCount, '\t') << "----------------------------------------------------" << endl;
    cout << string(tabCount, '\t') << "1. Biriyani                                 BDT 250 " << endl;
    cout << string(tabCount, '\t') << "2. Chicken Curry                            BDT 200" << endl;
    cout << string(tabCount, '\t') << "3. Luchi                                    BDT 150" << endl;
    cout << string(tabCount, '\t') << "4. Cheeseburger                             BDT 180" << endl;
    cout << string(tabCount, '\t') << "5. French Fries                             BDT 120" << endl;
    cout << string(tabCount, '\t') << "6. Pizza                                    BDT 300" << endl;
    cout << string(tabCount, '\t') << "7. Spring Rolls                             BDT 220" << endl;
    cout << string(tabCount, '\t') << "8. Fried Rice                               BDT 240" << endl;
    cout << string(tabCount, '\t') << "9. Chow Mein                                BDT 260" << endl;
    cout << string(tabCount, '\t') << "10. Spaghetti                               BDT 220" << endl;
    cout << string(tabCount, '\t') << "11. Tiramisu                                BDT 180" << endl;
    cout << string(tabCount, '\t') << "12. Ice Cream                               BDT 150" << endl;
    cout << string(tabCount, '\t') << "13. Cheesecake                              BDT 200" << endl;
    cout << string(tabCount, '\t') << "14. Gulab Jamun                             BDT 120" << endl;
    cout << string(tabCount, '\t') << "15. Rasgulla                                BDT 150" << endl;
    cout << string(tabCount, '\t') << "----------------------------------------------------" << endl;

    cout << string(tabCount, '\t') << "16. Back to main menu                               " << endl;

    cout << "\n";
}

double placeOrder(int choice, double totalBill, string &itemName, int &itemPrice, int &quantity, string &orderDetails)
{
    ofstream orderFile("order2.txt", ios::app);

    switch (choice)
    {
    case 1:
        itemPrice = 250;
        itemName = "Biriyani";
        break;
    case 2:
        itemPrice = 200;
        itemName = "Chicken Curry";
        break;
    case 3:
        itemPrice = 150;
        itemName = "Luchi";
        break;
    case 4:
        itemPrice = 180;
        itemName = "Cheeseburger";
        break;
    case 5:
        itemPrice = 120;
        itemName = "French Fries";
        break;
    case 6:
        itemPrice = 300;
        itemName = "Pizza";
        break;
    case 7:
        itemPrice = 220;
        itemName = "Spring Rolls";
        break;
    case 8:
        itemPrice = 240;
        itemName = "Fried Rice";
        break;
    case 9:
        itemPrice = 260;
        itemName = "Chow Mein";
        break;
    case 10:
        itemPrice = 220;
        itemName = "Spaghetti";
        break;
    case 11:
        itemPrice = 180;
        itemName = "Tiramisu";
        break;
    case 12:
        itemPrice = 150;
        itemName = "Ice Cream";
        break;
    case 13:
        itemPrice = 200;
        itemName = "Cheesecake";
        break;
    case 14:
        itemPrice = 120;
        itemName = "Gulab Jamun";
        break;
    case 15:
        itemPrice = 150;
        itemName = "Rasgulla";
        break;
    case 16:
        break;

    default:
        cout << "\n\t\t\t\t\t\t\tYOU ENTERED AN INVALID ITEM NUMBER" << endl;
        return totalBill;
    }

    if (choice != 16)
    {
        cout << "\n\n\t\t\t\t\tHOW MANY DO YOU WANT: ";
        cin >> quantity;

        totalBill += itemPrice * quantity;
        restaurantBill += itemPrice * quantity;

        if (orderFile.is_open())
        {
            cout << "\n\n\n\t\t\t\t\tYOU ORDER " << itemName << " (" << itemPrice << " BDT)" << endl;
            orderFile << "\t\t\t\t\t\tNUMBER OF ITEMS IS: " << quantity << "\n";
            orderFile.close();
        }

        orderDetails += "\t\t\t\t\t\t\tYOU ORDER " + itemName + ": " + to_string(itemPrice) + " BDT\tQUANTITY: " + to_string(quantity) + "\n\n";
    }

    cout << "\t\t\t\t\tYOUR ORDER RECEIVED " << endl;
    return totalBill;
}

double placeRestaurantOrder(double totalBill)
{
    int choice;
    int payment;
    char anotherOrder;
    string orderDetails = "";

    do
    {
        displayMenu();
        cout << "\n\n\t\t\t\t\tENTER ITEM NUMBER TO ORDER (or enter 16 to exit): ";
        cin >> choice;

        int itemPrice = 0;
        string itemName;
        int quantity;

        if (choice >= 1 && choice <= 15)
        {
            totalBill = placeOrder(choice, totalBill, itemName, itemPrice, quantity, orderDetails);

            orderDetails += "\t\t\t\t\t\t\tYOU ORDER " + itemName + ": " + to_string(itemPrice) + " BDT\tQUANTITY: " + to_string(quantity) + "\n\n";
        }
        else if (choice != 16)
        {
            cout << "\n\t\t\t\t\tINVALID ITEM NUMBER. Please enter a valid item number.\n";
        }

        else if (choice == 16)
        {
            bookaroom();
        }

        cout << "\n\t\t\t\t\tDO YOU WANT TO ORDER ANOTHER ITEM (Y/N): ";
        cin >> anotherOrder;

    } while (anotherOrder == 'y' || anotherOrder == 'Y');

    system("CLS");

    srand(time(0));
    int randomNum = rand() % 1000 + 1;

    cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tTHANK YOU FOR YOUR ORDER \n\t\t\t\t\t\t\t \n\t\t\t\t\t\t\tBilling In Process  ";
    for (int i = 0; i < 8; i++)
    {
        Sleep(500);
        cout << "..";
    }

    system("cls");

    cout << "\n\n";

    cout << "\t\t\t\t\t\t\t ================================================" << endl;
    cout << "\t\t\t\t\t\t\t|               HOTEL RELAX'S RESTAURANT         |" << endl;
    cout << "\t\t\t\t\t\t\t ================================================" << endl;
    cout << "\t\t\t\t\t\t\t   \t\t  Bill No : " << randomNum << endl;

    cout << "\n\n\t\t\t\t\t\t\t\t         ORDER DETAILS:" << endl;
    cout << orderDetails << endl;

    cout << "\n\t\t\t\t\t\t\t\t    YOUR TOTAL BILL IS " << totalBill << " BDT" << endl;
    cout << "\t\t\t\t\t\t\t Please make your payment \n\t\t\t\t\t\t\t Enter amount : ";
    cin >> payment;
    if (totalBill == payment)
    {
        cout << "\t\t\t\t\t\t\t Payment Successfull. \n\t\t\t\t\t\t\tYou will recive your order in 20 Minutes. " << endl;
        totalBill = 0;
    }

    cout << "\t\t\t\t\t\t\t ================================================" << endl;

    ofstream restaurantBillFile("restaurant_bill.txt");
    restaurantBillFile << restaurantBill << endl;
    restaurantBillFile.close();

    cout << "Back to the main menu";
    getch();
    bookaroom();

    return totalBill;
}

void checkOut()
{
    screenClear();
    int roomNumber;
    system("cls");
    cout << "Enter the room number to check out: ";
    cin >> roomNumber;

    if (roomNumber < 1 || roomNumber > 100)
    {
        cout << "Invalid room number. Please enter a valid room number." << endl;
        cout << "Press any key to continue...";
        getch();
        return;
    }

    set<int> bookedRooms;
    string roomType;
    ifstream bookedFile;

    if (roomNumber >= 1 && roomNumber <= 20)
    {
        roomType = "Single AC";
        bookedFile.open("single_ac_booked_rooms.txt");
    }
    else if (roomNumber >= 21 && roomNumber <= 40)
    {
        roomType = "Single Non-AC";
        bookedFile.open("single_non_ac_booked_rooms.txt");
    }
    else if (roomNumber >= 41 && roomNumber <= 80)
    {
        roomType = "Dual AC";
        bookedFile.open("dual_ac_booked_rooms.txt");
    }
    else if (roomNumber >= 81 && roomNumber <= 100)
    {
        roomType = "Dual Non-AC";
        bookedFile.open("dual_non_ac_booked_rooms.txt");
    }
    else
    {
        cout << "Invalid room number. Please enter a valid room number." << endl;
        cout << "Press any key to continue...";
        getch();
        return;
    }

    int bookedRoom;
    while (bookedFile >> bookedRoom)
    {
        bookedRooms.insert(bookedRoom);
    }
    bookedFile.close();

    if (bookedRooms.count(roomNumber))
    {

        bookedRooms.erase(roomNumber);

        ofstream updatedFile;
        if (roomType == "Single AC")
        {
            updatedFile.open("single_ac_booked_rooms.txt");
        }
        else if (roomType == "Single Non-AC")
        {
            updatedFile.open("single_non_ac_booked_rooms.txt");
        }
        else if (roomType == "Dual AC")
        {
            updatedFile.open("dual_ac_booked_rooms.txt");
        }
        else if (roomType == "Dual Non-AC")
        {
            updatedFile.open("dual_non_ac_booked_rooms.txt");
        }

        if (updatedFile.is_open())
        {
            for (int bookedRoom : bookedRooms)
            {
                updatedFile << bookedRoom << endl;
            }
            updatedFile.close();

            cout << "Room " << roomNumber << " has been successfully checked out. \n Thank you so much for vising here...\n"
                 << endl;
        }
        else
        {
            cout << "Unable to update room status. Please try again later." << endl;
        }
    }
    else
    {
        cout << "Room " << roomNumber << " is not currently booked or does not exist." << endl;
    }

    cout << "Press any key to continue...";
    getch();
    bookaroom();
}

void register_user()
{
    screenClear();
    string username, password, confirm_password;

    cout << "Enter username: ";
    getline(cin, username);

    while (!is_valid_username(username))
    {
        cout << "Invalid username! Use only letters, digits, and underscore." << endl;
        cout << "Enter username: ";
        getline(cin, username);
    }

    do
    {
        cout << "Enter password: ";
        getline(cin, password);

        while (!is_valid_password(password))
        {
            cout << "Invalid password! Password must be 8-16 characters with at least one uppercase letter, one digit, and one special character." << endl;
            cout << "Enter password: ";
            getline(cin, password);
        }

        cout << "Confirm password: ";
        getline(cin, confirm_password);

        if (password != confirm_password)
        {
            cout << "Passwords do not match. Please try again." << endl;
        }

    } while (password != confirm_password);

    ofstream outfile("user_data.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();

    cout << "Registration successful!" << endl;
    getch();
    main();
}

bool login_user()
{
    screenClear();
    string username, password, stored_username, stored_password;

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    ifstream infile("user_data.txt");

    while (infile >> stored_username >> stored_password)
    {
        if (username == stored_username && password == stored_password)
        {
            infile.close();
            return true;
        }
    }

    infile.close();
    return false;
}

void forgot_password()
{
    screenClear();
    string username, new_password, confirm_password;
    bool found = false;

    cout << "Enter your username to reset password: ";
    getline(cin, username);

    ifstream infile("user_data.txt");
    ofstream tempfile("temp_user_data.txt");

    string stored_username, stored_password;
    while (infile >> stored_username >> stored_password)
    {
        if (username == stored_username)
        {
            found = true;
            cout << "Enter new password: ";
            getline(cin, new_password);

            while (!is_valid_password(new_password))
            {
                cout << "Invalid password! Password must be 8-16 characters with at least one uppercase letter, one digit, and one special character." << endl;
                cout << "Enter new password: ";
                getline(cin, new_password);
            }

            cout << "Confirm new password: ";
            getline(cin, confirm_password);

            if (new_password != confirm_password)
            {
                cout << "Passwords do not match. Please try again." << endl;
            }
            else
            {
                tempfile << username << " " << new_password << endl;
            }
        }
        else
        {
            tempfile << stored_username << " " << stored_password << endl;
        }
    }

    infile.close();
    tempfile.close();

    if (found)
    {
        remove("user_data.txt");
        rename("temp_user_data.txt", "user_data.txt");
        cout << "Password reset successful!" << endl;
        getch();
        screenClear();
    }
    else
    {
        cout << "Username not found. Please check your username and try again." << endl;
    }
}
