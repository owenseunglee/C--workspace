// ============================================================================
// File: Library.hpp
// ============================================================================
// Programmger: Owen Lee
// Project: Library Simulator
// 
// Description: This is a header file for Library.cpp
// 
// ============================================================================
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// global variables for the location of the items
string const NONE = "None";
string const HOLD = "ON_HOLD";
string const OUT = "CHEKCED_OUT";
string const IN = "ON_SHELF";

// LibraryItem class declaration 
class LibraryItem
{
public:
    LibraryItem(int id, string title){
        m_library_item_id = id;
        m_title = title;
        m_requested_by = NONE;
        m_checked_out_by = NONE;
        m_location = IN;
    };
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

// Book class declaration
class Book : public LibraryItem{
public:
    static const int check_out_length = 21;
    Book(int id, string title, string author) : 
            LibraryItem(id, title), m_author(author){};
    string get_author(){return m_author;};
    int get_check_out_length() override {return check_out_length;};
    
private:
    string m_author;
};

// Album class declaration
class Album : public LibraryItem{
public:
    static const int check_out_length = 14;
    Album(int id, string title, string artist) : 
            LibraryItem(id, title), m_artist(artist){};
    string get_artist(){return m_artist;};
    int get_check_out_length() override {return check_out_length};
    
private:
    string m_artist;
};

// Movie class declaration
class Movie : public LibraryItem{
public:
    static const int check_out_length = 7;
    Movie(int id, string title, string director) : 
            LibraryItem(id, title), m_director(director){};
    string get_director(){return m_director;};
    int get_check_out_length() override {return check_out_length};

private:
    string m_director;
};

// Patron class declaration
class Patron{
public:
    Patron(int id, string name){
        m_patron_id = id;
        m_name = name;
        m_fine_amount = 0.0;};
    double get_fine_amount(){return m_fine_amount;};
    void add_library_item(LibraryItem* add_item){
        checked_out_items.push_back(add_item);};
    void remove_library_item(LibraryItem* return_item)
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

// Library class declaration
class Library
{
public:
    Library(){
        m_current_date = 0;};
    void add_library_item(LibraryItem* item){holdings.push_back(item);};
    void add_patron(Patron* patron){members.push_back(patron);};
    LibraryItem* lookup_library_item_from_id(int item_id)
    Patron* lookup_patron_from_id(int patron_id)
    string return_library_item(int item_id)
    string request_library_item(int patron_id, int item_id)
    string pay_fine(int patron_id, double amount)
    void increment_current_date()
    
private:
    vector<LibraryItem*> holdings;
    vector<Patron*> members;
    int m_current_date;
};
