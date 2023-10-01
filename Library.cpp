#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string const none = "None";
string const hold = "ON_HOLD";
string const out = "CHEKCED_OUT";
string const in = "ON_SHELF";

class LibraryItem
{
    public:
    LibraryItem(int id, string title){
        m_library_item_id = id;
        m_title = title;
        m_requested_by = none;
        m_checked_out_by = none;
        m_location = in;};
    string get_location(){return m_location;};
    int get_library_id(){return m_library_item_id;};
    string get_title(){return m_title;};
    string get_requested_by(){return m_requested_by;};
    void set_checked_out_by(int patron){m_checked_out_by = patron;};
    int get_checked_out_by(){return m_checked_out_by;};
    void set_requested_by(string patron){m_requested_by = patron;};
    void set_date_checked_out(int date){m_date_checked_out = date;};
    int get_date_checked_out(){return m_date_checked_out;};
    void set_location(string new_location){m_location = new_location;};
    virtual int get_check_out_length(){return 0;};

    private:
    int m_library_item_id;
    string m_title;
    string m_location;
    int m_checked_out_by;
    string m_requested_by;
    int m_date_checked_out;
};

class Book : public LibraryItem{
    public:
    static const int check_out_length = 21;
    Book(int id, string title, string author) : LibraryItem(id, title), m_author(author){};
    string get_author(){return m_author;};
    int get_check_out_length() override {return check_out_length;};
    private:
    string m_author;
};

class Album : public LibraryItem{
    public:
    static const int check_out_length = 14;
    Album(int id, string title, string artist) : LibraryItem(id, title), m_artist(artist){};
    string get_artist(){return m_artists;};
    int get_check_out_length() override {return check_out_length};
    private:
    string m_artists;
};

class Movie : public LibraryItem{
    public:
    static const int check_out_length = 7;
    Movie(int id, string title, string director) : LibraryItem(id, title), m_director(director){};
    string get_director(){return m_director;};
    int get_check_out_length() override {return check_out_length};
};

class Patron{
    public:
    Patron(int id, string name){
        m_patron_id = id;
        m_name = name;
        m_fine_amount = 0.0;};
    double get_fine_amount(){return m_fine_amount;};
    void add_library_item(LibraryItem* add_item){
        checked_out_items.push_back(add_item);
    };
    void remove_library_item(LibraryItem* return_item){
        for (vector<LibraryItem*>::iterator it = checked_out_items.begin(); it != checked_out_items.end(); ++it)
        {
            if(*it == return_item)
            {
                checked_out_items.erase(it);
                break;
            }
        };};
    string get_patron_name(){return m_name;};
    int get_patron_id(){return m_patron_id;};
    vector<LibraryItem*> get_checked_out_items(){return checked_out_items;};
    void amend_fine(double amount){m_fine_amount += amount;};
    
    private:
    int m_patron_id;
    string m_name;
    double m_fine_amount;
    vector<LibraryItem*> checked_out_items;
};

class Library
{
    public:
    Library(){
        m_current_date = 0;};
    void add_library_item(LibraryItem* item){holdings.push_back(item);};
    void add_patron(Patron* patron){members.push_back(patron);};
    LibraryItem* lookup_library_item_from_id(int item_id){
        for (LibraryItem*& item : holdings)
        {
            if (item -> get_library_id() == item_id)
            {
                return item;
            }
        }
        return nullptr;
    };
    Patron* lookup_patron_from_id(int patron_id)
    {
        for (Patron*& item : members)
        {
            if (patron -> get_patron_id() == patron_id)
            {
                return patron;
            }
        }
        return nullptr;
    };
    string check_out_library_item(int patron_id, int item_id)
    {
        Patron* patron = lookup_patron_from_id(patron_id);

        if (!patron)
        {
            return "Patron not found";
        }

        LibraryItem* item = lookup_library_item_from_id(item_id);

        if (!item)
        {
            return "Item not found";
        }

        if(item->get_location() == out)
        {
            return "Item already checked out";
        }
        else if(item->get_location() == in)
        {
            if(item->get_requested_by() == patron -> get_patron_name() || item -> get_requested_by() == none)
            {
                item -> set_requested_by(none);
                item -> set_checked_out_by(patron_id);
                item -> set_location(out);
                item -> set_date_checked_out(m_current_date);
                patron -> add_library_item(item);
            }
            else
            {
                return "Item on hold by other patron";
            }
            return "Check out successful";
        }
    }

    string return_library_item(int item_id)
    {
        LibraryItem* item = lookup_library_item_from_id(item_id);

        if(!item)
            return "Item not found";

        if (item -> get_location() == out)
        {
            if (item -> get_requested_by() != none)
            {
                item -> set_location(hold);
            }
            else
            {
                item -> set_location(in);
            }
            Patron* patron = lookup_patron_from_id(item -> get_checked_out_by());
            patron -> remove_library_item(item);
            return "Return successful";
        }
        else
            return "Item already in library";
    }

    string request_library_item(int patron_id, int item_id)
    {
        LibraryItem* item = lookup_library_item_from_id(item_id);
        Patron* patron = lookup_patron_from_id(patron_id);

        if(!item)
            return "Item not found";
        else if(!patron)
            return "Patron not found";

        if(item->get_requested_by() != none)
        {
            return "Item already on hold";
        }
        else
        {
            item -> set_location(hold);
            item -> set_requested_by(patron -> get_patron_name());
        }
        return "Request Successful";
    }

    string pay_fine(int patron_id, double amount)
    {
        Patron* patron = lookup_patron_from_id(patron_id);

        if(!patron)
            return "Patron not found";
        else
            patron -> amend_fine(-amount);

        return "Payment Successful";
    }

    void increment_current_date()
    {
        double fine = .10;
        ++m_current_date;
        for (Patron* patron : members)
        {
            vector<LibraryItem*> checked_out = patron -> get_checked_out_items();

            for (LibraryItem* items : checked_out)
            {
                int days_checked_out = m_current_date - (items -> get_date_checked_out());
                int overdue = days_checked_out - (items -> get_check_out_length());

                if(overdue > 0)
                {
                    patron -> amend_fine(fine);
                }
            }
        }
    }

    private:
    vector<LibraryItem*> holdings;
    vector<Patron*> members;
    int m_current_date;
};

int main()
{
    Book b(123, "Phantom", "Juster");
    Album a(456, "...And", "Fast");
    Movie m(567, "laput", "miyaza");

    Patron p1(000, "Joe");
    Patron p2(111, "YAAA");
    
    Library Lib;

    lib.add_library_item(&b);
    lib.add_library_item(&a);
    lib.add_patron(&p1);
    lib.add_patron(&p2);

    lib.check_out_library_item (111, 456);

    for (int i = 0; i < 7; ++i)
    {
        lib.increment_current_date();
    }

    lib.check_out_library_item(000, 567);

    cout << a.get_location() << " " << b.get_library_id() << " " << b.get_title() << endl;

    for (int i = 0; i < 15; ++i)
    {
        lib.increment_current_date();
    }

    cout << "Fine for Joe: " << p1.get_fine_amount() << endl;
    cout << "Fine for YAAA: " << p2.get_fine_amount() << endl;
}