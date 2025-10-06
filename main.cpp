#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Ticket.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class User_Login
{
protected:
    string user_name;
    string password;

public:
    User_Login() {}
    vector<Ticket *> tickets;
    void SetUserNameAndPass(string user, string pass)
    {
        user_name = user;
        password = pass;
    }
    bool login(string user_name, string pass)
    {
        if (this->user_name == user_name && this->password == pass)
            return true;
        return false;
    }
    string getuser() { return user_name; }
    void printBookedTickets()
    {
        for (auto &x : tickets)
        {
            if (x->type == 0)
            {
                cout << "BUS DETAILS " << endl;
            }
            if (x->type == 1)
            {
                cout << "TRAIN DETAILS " << endl;
            }
            if (x->type == 2)
            {
                cout << "FLIGHT DETAILS " << endl;
            }
            x->printTicketDetail();
            cout << endl;
        }
    }
};

class Registration : protected User_Login
{
private:
    string full_name;
    unsigned long int adhaar_Number;
    int age;
    long long phone_number;

    bool isPassSame(const string &x, const string &y)
    {
        if (x == y)
            return true;
        return false;
    }

    string VerifyPass()
    {
        string x, y;
        cout << "Enter Password : ";
        cin >> x;
        cout << "Re-enter Password : ";
        cin >> y;
        bool isSame = isPassSame(x, y);
        if (isSame)
            return x;
        cout << "Passwords do not match please re-enter " << endl;
        return VerifyPass();
    }

public:
    Registration() : User_Login()
    {
        cout << "Enter User Name : ";
        cin >> user_name;
        cout << "Enter your full name : ";
        cin >> full_name;
        cout << "Adhaar Number : ";
        cin >> adhaar_Number;

        cout << "Enter Age : ";
        cin >> age;
        cout << "Enter your phone Number " << endl;
        cin >> phone_number;
        ofstream outdata;

        outdata.open("otp.txt");
        int otp = rand();
        if (!outdata)
        {
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }
        else
        {
            outdata << otp;
            outdata.close();
        }
        int x;
        cout << "Enter OTP send to " << phone_number << " : ";
        cin >> x;
        if (x == otp)
        {
            cout << "Registration Successfull" << endl;
        }
        else
        {
            cout << "One - Time Password do not match " << endl;
            cout << endl;
            Registration();
            return;
        }
        password = VerifyPass();
        ofstream ofs;
        ofs.open("otp.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }

    User_Login *Create_User()
    {
        User_Login *newuser = new User_Login;
        newuser->SetUserNameAndPass(this->user_name, this->password);
        return newuser;
    }
};

class Transportation
{
public:
    string from;
    string to;
    float price;
    int duration;
    int id;
    string date;
    Transportation(string f, string t, float price, string start_time, int d)
    {
        from = f;
        to = t;
        this->price = price;
        this->date = start_time;
        duration = d;
    }
    int type;

    virtual Ticket *bookticket() = 0;
    virtual void getDetails()
    {
        cout << "FROM : " << from << endl;
        cout << "TO : " << to << endl;
        cout << "PRICE (RS) : " << price << endl;
        cout << "Start Time : " << date << endl;
    };
};

class Bus : public Transportation
{
public:
    int busNo;
    Bus(int busno, string f, string t, float price, string start_time, int d) : Transportation(f, t, price, start_time, d)
    {
        from = f;
        to = t;
        this->price = price;
        this->date = start_time;
        this->id = busno;
        duration = d;
        type = 0;
        busNo = busno;
    }

    Ticket *bookticket()
    {
        return new Ticket(from, to, price, date, 1);
    }
    void getDetails()
    {
        cout << "BUS DETAILS :  " << endl;
        cout << "Bus Number : " << busNo << endl;
        Transportation ::getDetails();

        cout << endl;
    }
};

class Train : public Transportation
{
public:
    int train;
    Train(int trainNo, string f, string t, float price, string start_time, int d) : Transportation(f, t, price, start_time, d)
    {
        from = f;
        to = t;
        this->price = price;
        this->date = start_time;
        this->id = trainNo;
        duration = d;
        type = 1;
        train = trainNo;
    }

    Ticket *bookticket()
    {
        return new Ticket(from, to, price, date, 1);
    }
    void getDetails()
    {
        cout << "TRAIN DETAILS :  " << endl;
        cout << "Train Number : " << train << endl;
        Transportation ::getDetails();

        cout << endl;
    }
};

class Flight : public Transportation
{
public:
    int FlNo;
    Flight(int flno, string f, string t, float price, string start_time, int d) : Transportation(f, t, price, start_time, d)
    {
        from = f;
        to = t;
        this->price = price;
        this->date = date;
        this->id = flno;
        duration = d;
        type = 2;
        FlNo = id;
    }

    Ticket *bookticket()
    {
        return new Ticket(from, to, price, date, 2);
    }
    void getDetails()
    {
        cout << "FLIGHT DETAILS :  " << endl;
        cout << "Flight Number : " << FlNo << endl;
        Transportation ::getDetails();

        cout << endl;
    }
};

class City
{
public:
    string City_name;
    string state;
    int pincode;
    City(string x, string y, int p)
    {
        City_name = x;
        state = y;
        pincode = p;
    }
    void getCityDetails()
    {
        cout << "City Name : " << this->City_name << endl;
        cout << "State : " << this->state << endl;
        cout << "Pincode : " << this->pincode << endl;
        cout << endl;
    }
    vector<Transportation *> travellingWays;

    void displayDetails(string y)
    {
        for (int i = 0; i < travellingWays.size(); i++)
        {
            if (travellingWays[i]->to == y)
            {
                travellingWays[i]->getDetails();
                cout << endl;
            }
        }
    }

    void allways()
    {
        for (int i = 0; i < travellingWays.size(); i++)
        {
            travellingWays[i]->getDetails();
            cout << endl;
        }
    }
    void displayDetails()
    {
        for (int i = 0; i < travellingWays.size(); i++)
        {
            travellingWays[i]->getDetails();
            cout << endl;
        }
    }
    void getSpecificWays(int x)
    {
        for (int i = 0; i < travellingWays.size(); i++)
        {
            if (travellingWays[i]->type == x)
            {
                travellingWays[i]->getDetails();
            }
        }
    }
};

class BookMyTrip
{
    vector<Registration *> registers;
    User_Login *curruser;
    BookMyTrip()
    {
        cout << "*********APPLICATIION INSTALLED SUCCESSFULLY**********" << endl;
    }

public:
    string app_name;
    static BookMyTrip *ApplicationInstance;
    vector<User_Login *> users;
    vector<City *> cities;

    void addCity(City *c)
    {
        cities.push_back(c);
    }

    BookMyTrip *Download_BookMyTrip()
    {
        if (ApplicationInstance == 0)
        {

            ApplicationInstance = new BookMyTrip();
            return ApplicationInstance;
        }
        else
        {
            cout << "----->>>> Application has already been installed <<<<----- " << endl;
        }
        return ApplicationInstance;
    }

    void getCities()
    {
        for (int i = 0; i < cities.size(); i++)
        {
            cities[i]->getCityDetails();
        }
    }

    bool Login()
    {
        string x, y;
        cout << "Enter the User_name : ";
        cin >> x;
        cout << "Password : ";
        cin >> y;
        for (int i = 0; i < users.size(); i++)
        {
            bool isLogin = users[i]->login(x, y);
            if (isLogin)
            {
                cout << "LOGIN SUCCESS" << endl;
                cout << endl;
                curruser = users[i];
                travel();
                return true;
            }
        }
        cout << "Credentials Do not match " << endl;
        cout << endl;

        return false;
    }

    void Register()
    {
        Registration *r = new Registration;
        registers.push_back(r);
        users.push_back(r->Create_User());
    }

    void displayFROMtoTO(string s, string d)
    {
        for (int i = 0; i < cities.size(); i++)
        {
            if (cities[i]->City_name == s)
            {

                cities[i]->displayDetails(d);
            }
        }
    }

    void booktickets(int id)
    {
        for (int i = 0; i < cities.size(); i++)
        {
            auto &x = cities[i]->travellingWays;
            for (int k = 0; k < x.size(); k++)
            {
                if (x[k]->id == id)
                {
                    Ticket *t = x[k]->bookticket();
                    cout << "********TICKET BOOKED******* " << endl;
                    curruser->tickets.push_back(t);
                    return;
                }
            }
        }
    }

    void open()
    {
        while (1)
        {
            int x;
            cout << "1.SIGN IN" << endl;
            cout << "2.LOG IN" << endl;
            cout << "3.EXIT OFF THE APPLICATION" << endl;
            cin >> x;
            if (x == 1)
            {
                Register();
            }
            else if (x == 2)
            {
                Login();
                cout << endl;
            }
            else if (x == 3)
            {
                cout << "*****************EXITED****************" << endl;
                exit(0);
            }
        }
    }
    void ListTransportion()
    {
        cout << "Enter your start from city  : ";
        string s;
        cin >> s;
        for (int i = 0; i < cities.size(); i++)
        {
            if (cities[i]->City_name == s)
            {
                cities[i]->displayDetails();
            }
        }
    }

    void getVehicles(int x)
    {
        for (int i = 0; i < cities.size(); i++)
        {
            cities[i]->getSpecificWays(x);
        }
    }
    void book(int w)
    {

        cout << "1. TO BOOK TICKET " << endl;
        cout << "2. BACK" << endl;
        int c;
        cin >> c;

        if (c == 1)
        {
            int x;
            cout << "ENTER ID : ";
            cin >> x;
            booktickets(x);
        }
        else
        {
            return;
        }
    }
    void travel()
    {

        while (1)
        {
            cout << "1. TRAVEL FROM SPECIFIC CITY TO CITY " << endl;
            cout << "2. CHECK ALL POSSIBLE TRAVELLING WAYS AVAILABLE " << endl;
            cout << "3. TRAVEL FROM A SPECIFIC CITY" << endl;
            cout << "4. CHECK ALL FLIGHTS " << endl;
            cout << "5. CHECK ALL BUSES " << endl;
            cout << "6. CHECK ALL TRAINS " << endl;
            cout << "7. MY BOOKED TICKETS " << endl;
            cout << "8. LOGOUT" << endl;

            int x;
            cin >> x;
            cout << endl;
            if (x == 1)
            {
                string s;
                string d;
                cout << "1.Enter from : ";
                cin >> s;
                cout << "2.Enter To : ";
                cin >> d;
                displayFROMtoTO(s, d);
                book(1);
            }
            if (x == 2)
            {
                for (int i = 0; i < cities.size(); i++)
                {
                    cities[i]->allways();
                }
                book(2);
            }
            if (x == 3)
            {
                string s;
                cout << "Enter City : ";
                cin >> s;
                for (int i = 0; i < cities.size(); i++)
                {
                    if (cities[i]->City_name == s)
                    {
                        cities[i]->allways();
                    }
                }
                book(3);
            }
            if (x == 4)
            {
                getVehicles(2);
                book(4);
            }
            if (x == 5)
            {
                getVehicles(0);
                book(5);
            }
            if (x == 6)
            {
                getVehicles(1);
                book(6);
            }
            if (x == 7)
            {
                curruser->printBookedTickets();
            }

            if (x == 8)
            {
                curruser = NULL;
                break;
            }
        }
    }

    template <typename T>
    void addVehi(T *vehi)
    {
        for (int i = 0; i < cities.size(); i++)
        {
            if (cities[i]->City_name == vehi->from)
            {
                cities[i]->travellingWays.push_back(vehi);
            }
        }
    }
};

BookMyTrip *BookMyTrip ::ApplicationInstance = 0;

int main()
{

    BookMyTrip *App = App->Download_BookMyTrip();
    City city1("Bengaluru", "Karnataka", 500001);
    City city2("Mumbai", "Karnataka", 521251);
    City city3("Delhi", "Karnataka", 600215);
    City city4("Kolkota", "Karnataka", 528001);
    City city5("Hyderabad", "Karnataka", 400001);
    App->addCity(&city1);
    App->addCity(&city2);
    App->addCity(&city3);
    App->addCity(&city4);
    App->addCity(&city5);
    Bus b[10]{

        Bus(0, "Bengaluru", "Delhi", 2200, "25/11/2022", 8),
        Bus(1, "Bengaluru", "Mumbai", 1600, "26/11/2022", 6),
        Bus(2, "Mumbai", "Delhi", 1260, "28/11/2022", 12),
        Bus(3, "Mumbai", "Kolkota", 2465, "1/12/2022", 32),
        Bus(4, "Kolkota", "Hyderabad", 2631, "2/12/2022", 14),
        Bus(5, "Delhi", "Mumbai", 1134, "3/12/2022", 10),
        Bus(6, "Bengaluru", "Delhi", 1752, "5/12/2022", 11),
        Bus(7, "Bengaluru", "Kolkota", 1300, "6/12/2022", 28),
        Bus(8, "Bengaluru", "Hyderabad", 800, "30/11/2022", 9),
        Bus(9, "Kolkota", "Delhi", 1200, "1/11/2022", 8)};

    Train t[10]{
        Train(10, "Bengaluru", "Delhi", 620, "25/11/2022", 8),
        Train(11, "Bengaluru", "Mumbai", 350, "26/11/2022", 5),
        Train(12, "Mumbai", "Delhi", 680, "28/11/2022", 9),
        Train(13, "Mumbai", "Kolkota", 880, "1/12/2022", 14),
        Train(14, "Kolkota", "Hyderabad", 950, "2/12/2022", 17),
        Train(15, "Delhi", "Mumbai", 450, "3/12/2022", 16),
        Train(16, "Bengaluru", "Delhi", 632, "5/12/2022", 15),
        Train(17, "Bengaluru", "Kolkota", 415, "6/12/2022", 24),
        Train(18, "Bengaluru", "Hyderabad", 310, "30/11/2022", 8),
        Train(19, "Kolkota", "Delhi", 550, "1/11/2022", 10)};

    Flight f[10] = {

        Flight(20, "Bengaluru", "Delhi", 4525, "25/11/2022", 96),
        Flight(21, "Bengaluru", "Mumbai", 6525, "26/11/2022", 41),
        Flight(22, "Mumbai", "Delhi", 6500, "28/11/2022", 63),
        Flight(23, "Mumbai", "Kolkota", 4500, "1/12/2022", 74),
        Flight(24, "Kolkota", "Hyderabad", 6300, "2/12/2022", 75),
        Flight(25, "Delhi", "Mumbai", 8500, "3/12/2022", 25),
        Flight(26, "Bengaluru", "Delhi", 7500, "5/12/2022", 63),
        Flight(27, "Bengaluru", "Kolkota", 8600, "6/12/2022", 42),
        Flight(28, "Bengaluru", "Hyderabad", 3020, "30/11/2022", 63),
        Flight(29, "Kolkota", "Delhi", 4102, "1/11/2022", 74)};

    for (int i = 0; i < 10; i++)
    {
        App->addVehi(&t[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        App->addVehi(&f[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        App->addVehi(&b[i]);
    }

    App->open();
}
