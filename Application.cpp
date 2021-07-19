#include <bits/stdc++.h>
using namespace std;

class Railways;
class Station;

class Station
{
    string name_;

public:
    Station(string stationName) : name_(stationName) {}

    bool operator==(Station other)
    {
        if (name_ == other.name_)
            return true;
        else
            return false;
    }
    Station operator=(const Station other)
    {
        this->name_ = other.name_;
        return (*this);
    }
    //Station (Station& s): name_(s.name_){}
    string GetName() const
    {
        return name_;
    }

    int GetDistance(Station other, vector<tuple<Station, Station, int>> &sDistStations)
    {
        for (auto eachStation : sDistStations)
        {
            Station curr(""), des("");
            int dist = 0;
            tie(curr, des, dist) = eachStation;
            if ((*this) == curr && other == des)
            {
                return dist;
            }
            if ((*this) == des && other == curr)
            {
                return dist;
            }
        }
        return -1;
    }
};

class Railways
{

public:
    static vector<tuple<Station, Station, int>> sDistStations;
    static vector<Station> sStations;
    int GetDistance(Station src, Station dst)
    {
        for (auto eachStation : sDistStations)
        {
            Station curr(""), next("");
            int dist;
            tie(curr, next, dist) = eachStation;
            if (curr == src && next == dst)
            {
                return dist;
            }
        }
        return -1;
    }
};
vector<Station> Railways::sStations{Station("Mumbai"), Station("Delhi"),
                                    Station("Bangalore"), Station("Kolkata"), Station("Chennai")};

vector<tuple<Station, Station, int>> Railways::sDistStations{
    {Station("Mumbai"), Station("Delhi"), 1447},
    {Station("Mumbai"), Station("Bangalore"), 981},
    {Station("Mumbai"), Station("Kolkata"), 2014},
    {Station("Mumbai"), Station("Chennai"), 1338},
    {Station("Bangalore"), Station("Delhi"), 2150},
    {Station("Kolkata"), Station("Delhi"), 1472},
    {Station("Chennai"), Station("Delhi"), 2180},
    {Station("Bangalore"), Station("Kolkata"), 1871},
    {Station("Bangalore"), Station("Chennai"), 350},
    {Station("Kolkata"), Station("Chennai"), 1659}};

class Date
{
    static vector<string> sDayNames;
    static vector<string> sMonthNames;
    const uint32_t day_;
    const uint32_t month_;
    const uint32_t year_;

public:
    Date(uint32_t d, uint32_t m, uint32_t y) : day_(d), month_(m), year_(y) {}
    friend ostream &operator<<(ostream &out, const Date &t);
};
ostream &operator<<(ostream &out, const Date &t)
{
    out << t.day_ << '/' << t.sMonthNames[t.month_ - 1] << '/' << t.year_;
    return out;
}
vector<string> Date::sMonthNames{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
vector<string> Date::sDayNames{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

/*
Functions to implement`
GetLoadFactor(),  // very end 
GetName(),  //very end
IsSitting(),  // at first level
IsAC(),  //at second level
GetNumberOfTiers() //at end level(for berth) and at first level for (seat)
IsLuxury() //at end level
*/

/********************************************************/
class BookingClass
{
public:
    static double sBaseFarePerKM;
    static double sLuxuryTaxPercent;
    virtual double GetLoadFactor() = 0;
    virtual string GetName() = 0;
    virtual bool IsSitting() = 0;
    virtual bool IsAC() = 0;
    virtual int GetNumberOfTiers() = 0;
    virtual bool IsLuxury() = 0;
    friend ostream &operator<<(ostream &out, BookingClass &b);
};
ostream &operator<<(ostream &out, BookingClass &b)
{
    if (b.IsSitting() == true)
        out << "\tMode: Sitting" << endl;
    else
        out << "\tMode: Sleeping" << endl;

    if (b.IsAC() == true)
        out << "\tComfort: AC" << endl;
    else
        out << "\tComfort: Non-AC" << endl;

    out << "\tBunks: " << b.GetNumberOfTiers() << endl;

    if (b.IsLuxury() == true)
        out << "\tLuxury: Yes" << endl;
    else
        out << "\tLuxury: No" << endl;
    return out;
}
double BookingClass::sBaseFarePerKM = 0.5;
double BookingClass::sLuxuryTaxPercent = 25;

/********************************************************/

class Seat : public BookingClass
{
    static int sNumOfTiers;
    bool sitting = true;

public:
    int GetNumberOfTiers()
    {
        return sNumOfTiers;
    }
    bool IsSitting()
    {
        return sitting;
    }
};
int Seat::sNumOfTiers = 0;

/********************************************************/

class ACChairCar : public Seat
{
    bool ac_ = true;
    double loadFactor_ = 1.25;
    string name_ = "AC Chair Car";
    bool isLuxury_ = false;

public:
    static BookingClass *Type();
    bool IsAC() { return ac_; }
    double GetLoadFactor() { return loadFactor_; }
    string GetName() { return name_; }
    bool IsLuxury() { return isLuxury_; }
};
BookingClass *ACChairCar::Type()
{
    BookingClass *temp;
    temp = new ACChairCar;
    return temp;
}

/********************************************************/

class SecondSitting : public Seat
{
    bool ac_ = false;
    double loadFactor_ = 0.5;
    string name_ = "Second Sitting";
    bool isLuxury_ = false;

public:
    static BookingClass *Type();
    bool IsAC() { return ac_; }
    double GetLoadFactor() { return loadFactor_; }
    string GetName() { return name_; }
    bool IsLuxury() { return isLuxury_; }
};
BookingClass *SecondSitting::Type()
{
    BookingClass *temp;
    temp = new SecondSitting;
    return temp;
}

/********************************************************/

class Berth : public BookingClass
{
    bool sit_ = false;

public:
    bool IsSitting()
    {
        return sit_;
    }
};

/********************************************************/

class ACBerth : public Berth
{
public:
    bool ac_ = true;
    bool IsAC() { return ac_; }
};

/********************************************************/

class ACFirstClass : public ACBerth
{
    int tiers_ = 2;
    double loadFactor_ = 3;
    string name_ = "AC First Class";
    bool isLuxury_ = true;

public:
    static BookingClass *Type();
    int GetNumberOfTiers() { return tiers_; }
    double GetLoadFactor() { return loadFactor_; }
    string GetName() { return name_; }
    bool IsLuxury() { return isLuxury_; }
};
BookingClass *ACFirstClass::Type()
{
    BookingClass *temp;
    temp = new ACFirstClass;
    return temp;
}

/********************************************************/

class AC2Tier : public ACBerth
{
    int tiers_ = 2;
    double loadFactor_ = 2.00;
    string name_ = "AC 2 Tier";
    bool isLuxury_ = false;

public:
    static BookingClass *Type();
    int GetNumberOfTiers() { return tiers_; }
    double GetLoadFactor() { return loadFactor_; }
    string GetName() { return name_; }
    bool IsLuxury() { return isLuxury_; }
};
BookingClass *AC2Tier::Type()
{
    BookingClass *temp;
    temp = new AC2Tier;
    return temp;
}

/********************************************************/

class AC3Tier : public ACBerth
{
    int tiers_ = 3;
    double loadFactor_ = 1.75;
    string name_ = "AC 3 Tier";
    bool isLuxury_ = false;

public:
    static BookingClass *Type();
    int GetNumberOfTiers() { return tiers_; }
    double GetLoadFactor() { return loadFactor_; }
    string GetName() { return name_; }
    bool IsLuxury() { return isLuxury_; }
};
BookingClass *AC3Tier::Type()
{
    BookingClass *temp;
    temp = new AC3Tier;
    return temp;
}

/********************************************************/

class NonACBerth : public Berth
{
    bool ac = false;
    bool IsAC() { return ac; }
};

/********************************************************/

class FirstClass : public NonACBerth
{
    int tiers_ = 2;
    double loadFactor_ = 2.00;
    string name_ = "First Class";
    bool isLuxury_ = true;

public:
    static BookingClass *Type();
    int GetNumberOfTiers() { return tiers_; }
    double GetLoadFactor() { return loadFactor_; }
    string GetName() { return name_; }
    bool IsLuxury() { return isLuxury_; }
};
BookingClass *FirstClass::Type()
{
    BookingClass *temp;
    temp = new FirstClass;
    return temp;
}

/********************************************************/

class Sleeper : public NonACBerth
{
    int tiers_ = 3;
    double loadFactor_ = 1.00;
    string name_ = "Sleeper";
    bool isLuxury_ = true;

public:
    static BookingClass *Type();
    int GetNumberOfTiers() { return tiers_; }
    double GetLoadFactor() { return loadFactor_; }
    string GetName() { return name_; }
    bool IsLuxury() { return isLuxury_; }
};
BookingClass *Sleeper::Type()
{
    BookingClass *temp;
    temp = new Sleeper;
    return temp;
}

/********************************************************/

class Passenger
{
};

class Booking
{
    static int sNextPNR;
    const Station fromStation_;
    const Station toStation_;
    const int pnr_ = ++sNextPNR;
    const bool bookingStatus_ = true;
    const string bookingMessage_ = "BOOKING SUCCEDED";
    const Passenger *human;
    const Date bookingDate;
    const BookingClass *bookingClass;

public:
    static vector<Booking *> sBookings;
    int ComputeFare() const
    {
        Railways t_rail;
        double t_dist = t_rail.GetDistance(fromStation_, toStation_);
        double t_base = BookingClass::sBaseFarePerKM;
        BookingClass *t = const_cast<BookingClass *>(bookingClass);
        bool isAC = t->IsAC();
        bool isLux = t->IsLuxury();
        double f = t->GetLoadFactor();

        int price = ((t_dist*t_base*f + isAC * 50) * (1 + ((double)isLux * (double)(25)) / 100) + 0.5);
        return price;
    }
    Booking(Station src, Station des, Date now, BookingClass *b, Passenger *human = NULL) : fromStation_(src), toStation_(des),
                                                                                            bookingDate(now), human(NULL)

    {
        bookingClass = b;
        sBookings.push_back((this));
    }
    ~Booking() {}
    friend ostream &operator<<(ostream &out, const Booking &b);
};
ostream &operator<<(ostream &out, const Booking &b)
{
    // out<<this->day_<<'/'<<this->sMonthNames[this->month_-1]<<'/'<<this->year_;
    // return out;
    out << b.bookingMessage_ << ":" << endl;
    out << "PNR Number: " << b.pnr_ << endl;
    out << "From Station " << b.fromStation_.GetName() << endl;
    out << "To Station " << b.toStation_.GetName() << endl;
    out << "Travel Date " << b.bookingDate << endl;
    out << *(const_cast<BookingClass *>(b.bookingClass));

    out << b.ComputeFare() << endl
        << endl;
    return out;
}

int Booking::sNextPNR = 0;
vector<Booking *> Booking::sBookings;

void BookingApplication()
{
    // Bookings by different booking classes
    // <BookingClasses>::Type() returns the constant object of the respective type
    Booking b1(Station("Mumbai"), Station("Delhi"), Date(15, 2, 2021), ACFirstClass::Type());
    Booking b2(Station("Kolkata"), Station("Delhi"), Date(5, 3, 2021), AC2Tier::Type());
    Booking b3(Station("Mumbai"), Station("Kolkata"), Date(17, 3, 2021), FirstClass::Type());
    Booking b4(Station("Mumbai"), Station("Delhi"), Date(23, 3, 2021), AC3Tier::Type());
    Booking b5(Station("Chennai"), Station("Delhi"), Date(25, 4, 2021), ACChairCar::Type());
    Booking b6(Station("Chennai"), Station("Kolkata"), Date(7, 5, 2021), Sleeper::Type());
    Booking b7(Station("Mumbai"), Station("Delhi"), Date(19, 5, 2021), SecondSitting::Type());
    Booking b8(Station("Delhi"), Station("Mumbai"), Date(22, 5, 2021), SecondSitting::Type());
    // Output the bookings done where sBookings is the collection of bookings done
    vector<Booking *>::iterator it;
    for (it = Booking::sBookings.begin(); it < Booking::sBookings.end(); ++it)
    {
        cout << *(*it);
    }
    return;
}
int main()
{
    BookingApplication();
    return 0;
}
