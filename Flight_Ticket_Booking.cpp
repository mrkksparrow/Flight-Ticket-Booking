#include <bits/stdc++.h>
using namespace std;

struct Plane
{
    string plane_name;
    vector<bool> economy_seat;
    int economy_price = 1000;
    vector<bool> bussiness_seat;
    int bussiness_price = 2000;
    int revenue = 0;
    vector<int> meals_booked;
};

struct Booking
{
    int booking_id;
    int plane_id;
    string clas;
    vector<int> seat_booked;
    bool meals;
    bool cancel;
    int cancellation_fee = 0;
    int total = 0;
};

map<int, Plane *> planedb;
map<int, Plane *>::iterator itr_planedb;

map<int, Booking *> bookingdb;
map<int, Booking *>::iterator itr_bookingdb;

static int serialid = 1;

void addPlane()
{
    int id;
    cout << "Enter plane id" << endl;
    cin >> id;
    cin.ignore();
    Plane *temp = new Plane();
    cout << "Enter plane name" << endl;
    cin >> temp->plane_name;
    temp->economy_seat.resize(12, false);
    temp->bussiness_seat.resize(6, false);
    planedb[id] = temp;
}

void bookSeat()
{
    cout << "Enter the id of the plane you want to book seat" << endl;
    for (itr_planedb = planedb.begin(); itr_planedb != planedb.end(); itr_planedb++)
    {
        cout << "Plane name : " << itr_planedb->second->plane_name << "Id : " << itr_planedb->first << endl;
        cout << "----------------------------------------------------------------------" << endl;
    }
    int id;
    cin >> id;
    itr_planedb = planedb.find(id);
    int choice;
    cout << "Select ut choice" << endl
         << "1. Economy Class" << endl
         << "2. Business Class" << endl;
    cin >> choice;
    if (choice == 1)
    {
        Booking *temp = new Booking();
        temp->clas = "Economy Class";
        int no;
        cout << "Enter number of seats to be booked" << endl;
        cin >> no;
        cout << "Select from the Availabe Seats" << endl;
        for (int i = 0; i < itr_planedb->second->economy_seat.size(); i++)
        {
            if (itr_planedb->second->economy_seat[i] == false)
            {
                cout << i + 1 << " | ";
            }
        }
        cout << endl;
        int no_meal = no;
        while (no--)
        {
            int x;
            cin >> x;
            itr_planedb->second->economy_seat[x - 1] = true;
            temp->booking_id = serialid;
            temp->plane_id = id;
            temp->seat_booked.push_back(x);
            temp->total += itr_planedb->second->economy_price;
            itr_planedb->second->revenue += itr_planedb->second->economy_price;
            itr_planedb->second->economy_price += 100;
        }
        cout << "Do u require meals, if yes enter 1 otherwise enter 0" << endl;
        int m;
        cin >> m;
        if (m)
        {
            temp->total += (no_meal * 200);
            itr_planedb->second->revenue += (no_meal * 200);
            for (int i = 0; i < temp->seat_booked.size(); i++)
            {
                itr_planedb->second->meals_booked.push_back(temp->seat_booked[i]);
            }
        }
        temp->meals = m;
        bookingdb[serialid++] = temp;
    }
    else
    {
        Booking *temp = new Booking();
        temp->clas = "Bussiness Class";
        int no;
        cout << "Enter number of seats to be booked" << endl;
        cin >> no;
        cout << "Select from the Availabe Seats" << endl;
        for (int i = 0; i < itr_planedb->second->bussiness_seat.size(); i++)
        {
            if (itr_planedb->second->bussiness_seat[i] == false)
            {
                cout << i + 1 << " | ";
            }
        }
        cout << endl;
        int no_meal = no;
        while (no--)
        {
            int x;
            cin >> x;
            itr_planedb->second->bussiness_seat[x - 1] = true;
            temp->booking_id = serialid;
            temp->plane_id = id;
            temp->seat_booked.push_back(x - 1);
            temp->total += itr_planedb->second->bussiness_price;
            itr_planedb->second->revenue += itr_planedb->second->bussiness_price;
            itr_planedb->second->bussiness_price += 200;
        }
        cout << "Do u require meals, if yes enter 1 otherwise enter 0" << endl;
        int m;
        cin >> m;
        temp->meals = m;
        if (m)
        {
            temp->total += (no_meal * 200);
            itr_planedb->second->revenue += (no_meal * 200);
            for (int i = 0; i < temp->seat_booked.size(); i++)
            {
                itr_planedb->second->meals_booked.push_back(temp->seat_booked[i]);
            }
        }
        bookingdb[serialid++] = temp;
    }
}

void summary()
{
    for (itr_bookingdb = bookingdb.begin(); itr_bookingdb != bookingdb.end(); itr_bookingdb++)
    {
        cout << "Booking id : " << itr_bookingdb->first << endl;
        cout << "Plane id : " << itr_bookingdb->second->plane_id << endl;
        if (itr_bookingdb->second->cancel == false)
        {
            cout << itr_bookingdb->second->clas << " : ";
            for (auto &it : itr_bookingdb->second->seat_booked)
            {
                cout << it << " | ";
            }
            cout << endl;
            cout << "Meals Required : ";
            if (itr_bookingdb->second->meals == true)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            cout << "Total Cost : " << itr_bookingdb->second->total << endl;
        }
        else
        {
            cout << "Cancelled" << endl;
            cout << "Total Cancellation fee : " << itr_bookingdb->second->cancellation_fee << endl;
        }

        cout << "--------------------------------------------------" << endl;
    }
}

void display()
{
    for (itr_planedb = planedb.begin(); itr_planedb != planedb.end(); itr_planedb++)
    {
        cout << "Plane id : " << itr_planedb->first << endl;
        cout << "Plane name : " << itr_planedb->second->plane_name << endl;
        cout << "Bussines class : " << endl;
        cout << "Availabe : ";
        for (int i = 0; i < itr_planedb->second->bussiness_seat.size(); i++)
        {
            if (itr_planedb->second->bussiness_seat[i] == false)
            {
                cout << i + 1 << " | ";
            }
        }
        cout << "Booked : ";
        for (int i = 0; i < itr_planedb->second->bussiness_seat.size(); i++)
        {
            if (itr_planedb->second->bussiness_seat[i] == true)
            {
                cout << i + 1 << " | ";
            }
        }
        cout << endl;
        cout << "Economy class : " << endl;
        cout << "Availabe : ";
        for (int i = 0; i < itr_planedb->second->economy_seat.size(); i++)
        {
            if (itr_planedb->second->economy_seat[i] == false)
            {
                cout << i + 1 << " | ";
            }
        }
        cout << "Booked : ";
        for (int i = 0; i < itr_planedb->second->economy_seat.size(); i++)
        {
            if (itr_planedb->second->economy_seat[i] == true)
            {
                cout << i + 1 << " | ";
            }
        }
        cout << endl;

        cout << "Meals Booked : ";
        for (auto &it : itr_planedb->second->meals_booked)
        {
            cout << it << " | ";
        }

        cout << endl;
        cout << "Total Revenue : " << itr_planedb->second->revenue << endl;
        cout << endl
             << "--------------------------------------------------" << endl;
    }
}

void cancelTicket()
{
    cout << "Choose the booking id to be cancelled" << endl;
    for (itr_bookingdb = bookingdb.begin(); itr_bookingdb != bookingdb.end(); itr_bookingdb++)
    {
        cout << "Booking id : " << itr_bookingdb->first << "  [---  ";
        cout << "Plane id : " << itr_bookingdb->second->plane_id << " ";
        cout << itr_bookingdb->second->clas << " : ";
        for (auto &it : itr_bookingdb->second->seat_booked)
        {
            cout << it << " | ";
        }
        cout << "Total Cost : " << itr_bookingdb->second->total << "  ---]" << endl;
    }
    int cancel_id;
    cin >> cancel_id;
    itr_bookingdb = bookingdb.find(cancel_id);
    itr_bookingdb->second->cancel = true;
    int num = itr_bookingdb->second->seat_booked.size();
    itr_bookingdb->second->cancellation_fee = num * 200;
    itr_planedb = planedb.find(itr_bookingdb->second->plane_id);
    if (itr_bookingdb->second->clas == "Bussiness Class")
    {
        for (auto &it : itr_bookingdb->second->seat_booked)
        {
            itr_planedb->second->bussiness_seat[it - 1] = false;
        }
    }
    else
    {
        for (auto &it : itr_bookingdb->second->seat_booked)
        {
            itr_planedb->second->economy_seat[it - 1] = false;
        }
    }
}

int main()
{

    int choice;
    do
    {
        cout << "Welcome to Zoho Airways" << endl
             << "Select ur choice" << endl
             << "1. Add Plane" << endl
             << "2. Book Seat" << endl
             << "3. Plane Database" << endl
             << "4. Booking Database" << endl
             << "5. Cancel Ticket" << endl
             << "----------------------------------------------------" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            addPlane();
            break;

        case 2:
            bookSeat();
            break;

        case 3:
            display();
            break;

        case 4:
            summary();
            break;

        case 5:
            cancelTicket();
            break;

        case 0:
            cout << "Thank you, Have a nice journey" << endl;
            break;
        }
    } while (choice != 0);
}
