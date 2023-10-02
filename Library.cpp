// ============================================================================
// File: Library.cpp
// ============================================================================
// Programmger: Owen Lee
// Project: Library Simulator
// 
// Description: This program is a library simulator that involves multiple
//              classes and it is aimed to implement patron interactions
//              and transactional operations using encapsulation, inheritance,
//              and polymorphism.
// 
// ============================================================================
#include "Library.hpp"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void Patron::remove_library_item(LibraryItem* return_item)
{
    for (vector<LibraryItem*>::iterator it = checked_out_items.begin(); it !
         = checked_out_items.end(); ++it)
    {
        if (*it == return_item)
        {
            checked_out_items.erase(it);
            break;
        }
    };
}; // end of remove_library_item

LibraryItem* Library::lookup_library_item_from_id(int item_id)
{
        for (LibraryItem*& item : holdings)
        {
            if (item -> get_library_id() == item_id)
            {
                return item;
            }
        }
        return nullptr;
}; // end of lookup_library_item_from_id

Patron* Library::lookup_patron_from_id(int patron_id)
{
    for (Patron*& item : members)
    
        if (patron -> get_patron_id() == patron_id)
            return patron;

    return nullptr;
}; // end of lookup_patron_from_id

string Library::check_out_library_item(int patron_id, int item_id)
{
    Patron* patron = lookup_patron_from_id(patron_id);

    if (!patron)
        return "Patron not found";

    LibraryItem* item = lookup_library_item_from_id(item_id);

    if (!item)
        return "Item not found";

    if (item->get_location() == OUT)
        return "Item already checked out";

    else if (item->get_location() == IN)
    {
        if (item->get_requested_by() == patron -> get_patron_name() 
            || item -> get_requested_by() == NONE)
        {
            item -> set_requested_by(NONE);
            item -> set_checked_out_by(patron_id);
            item -> set_location(OUT);
            item -> set_date_checked_out(m_current_date);
            patron -> add_library_item(item);
        }
        else
            return "Item on hold by other patron";
        
        return "Check out successful";
    }
} // end of check_out_library_item

string Library::return_library_item(int item_id)
{
    LibraryItem* item = lookup_library_item_from_id(item_id);

    if (!item)
        return "Item not found";

    if (item -> get_location() == OUT)
    {
        if (item -> get_requested_by() != NONE)
        {
            item -> set_location(HOLD);
        }
        else
        {
            item -> set_location(IN);
        }
        Patron* patron = lookup_patron_from_id(item -> get_checked_out_by());
        patron -> remove_library_item(item);
        
        return "Return successful";
    }
    else
        return "Item already in library";
} // end of return_library_item

string Library::request_library_item(int patron_id, int item_id)
{
    LibraryItem* item = lookup_library_item_from_id(item_id);
    Patron* patron = lookup_patron_from_id(patron_id);

    if (!item)
        return "Item not found";
    else if (!patron)
        return "Patron not found";

    if (item->get_requested_by() != NONE)
    {
        return "Item already on hold";
    }
    else
    {
        item -> set_location(HOLD);
        item -> set_requested_by(patron -> get_patron_name());
    }
    return "Request Successful";
} // end of request_library_item

string Library::pay_fine(int patron_id, double amount)
{
    Patron* patron = lookup_patron_from_id(patron_id);

    if(!patron)
        return "Patron not found";
    else
        patron -> amend_fine(-amount);

    return "Payment Successful";
} // end of pay_fine

void Library::increment_current_date()
{
    double fine = .10;
    ++m_current_date;

    for (Patron* patron : members)
    {
        vector<LibraryItem*> checked_out = patron -> get_checked_out_items();

        for (LibraryItem* items : checked_out)
        {
            int days_checked_out = m_current_date - 
                                   (items -> get_date_checked_out());
            int overdue = days_checked_out - (items -> get_check_out_length());

            if (overdue > 0)
                patron -> amend_fine(fine);
        }
    }
} // end of increment_current_date
        
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