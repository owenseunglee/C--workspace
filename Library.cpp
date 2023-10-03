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



// ==== Patron::remove_library_item ===========================================
//
// This function removes the specified LibraryItem from checked_out_item.
//
// Input:
//      return_item [IN]  -- a pointer to an object that needs to be removed 
//                           from checked_out_item
//
// Output:
//      N/A
//
// ============================================================================

void Patron::remove_library_item(LibraryItem* return_item)
{
    // traverse through the list of checked out items, LibraryItem objects
    for (vector<LibraryItem*>::iterator it = checked_out_items.begin(); it !
         = checked_out_items.end(); ++it)
    {
        if (*it == return_item)
        {
            // remove LibraryItem object from the list
            checked_out_items.erase(it);
            break;
        }
    };
}; // end of remove_library_item



// ==== Library::lookup_library_item_from_id ==================================
//
// This function returns the LibraryItem object corresponding to the ID 
// parameter, or nullptr if no such LibraryItem is in the holdings.
//
// Input:
//      item_id [IN]  -- a specified item id, an integer variable to lookup in 
//                       the library
//
// Output:
//      item    [OUT] -- a LibrarayItem object corresponding to the ID
//                       parameter
//
//      nullptr [OUT] -- a nullptr when no corresponding object is found
//
// ============================================================================

LibraryItem* Library::lookup_library_item_from_id(int item_id)
{
    // traverse through the list of LibraryItem objects
    for (LibraryItem*& item : holdings)
    {
        // check for matching object using item_id
        if (item -> get_library_id() == item_id)
        {
            return item;
        }
    }
    return nullptr;
}; // end of lookup_library_item_from_id



// ==== Library::lookup_patron_from_id ========================================
//
// This function returns the Patron object corresponding to the ID parameter, 
// or nullptr if no such Patron is a member
//
// Input:
//      patron_id [IN]  -- a specified patron id, an integer variable, to 
//                         lookup in the library
//
// Output:
//      item    [OUT] -- a Patron object corresponding to the ID parameter
//
//      nullptr [OUT] -- a nullptr when no corresponding object is found
//
// ============================================================================
Patron* Library::lookup_patron_from_id(int patron_id)
{
    // traver through the list of Patron objects
    for (Patron*& item : members)
        // check for matching object using patron_id
        if (patron -> get_patron_id() == patron_id)
            return patron;

    return nullptr;
}; // end of lookup_patron_from_id



// ==== Library::check_out_library_item =======================================
//
// This function allows a library member to borrow an item. It checks if the 
// member and item exist, if the item is available for borrowing, and updates 
// the status of the item and member accordingly. If successful, it returns 
// "check out successful".
//
// Input:
//      patron_id   [IN] -- a specified patron id, an integer variable to 
//                          lookup in the library
//
//      item_id     [IN] -- a specified patron id, an integer variable to 
//                          lookup in the library.
//
// Output:
//      strings     [OUT]-- differnt corresponding messages are returned as the
//                        result of the operation
//
// ============================================================================
string Library::check_out_library_item(int patron_id, int item_id)
{
    Patron* patron = lookup_patron_from_id(patron_id);

    if (!patron)
        return "Patron not found";

    LibraryItem* item = lookup_library_item_from_id(item_id);
    
    if (!item)
        return "Item not found";
    // checked out
    if (item->get_location() == OUT)
        return "Item already checked out";
    // in library
    else if (item->get_location() == IN)
    {
        // check if the requested patron is the same patron checking out the 
        // item or no one requested the item
        if (item->get_requested_by() == patron -> get_patron_name() 
            || item -> get_requested_by() == NONE)
        {
            // update the status of the item and member
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



// ==== Library::return_library_item ==========================================
//
// This function returns the LibraryItem object corresponding to the ID 
// parameter, or nullptr if no such LibraryItem is in the holdings.
//
// Input:
//      item_id [IN]  -- a specified item id, an integer variable to lookup in 
//                       the library
//
// Output:
//      strings [OUT] -- differnt corresponding messages are returned as the
//                       result of the operation
//
// ============================================================================
string Library::return_library_item(int item_id)
{
    LibraryItem* item = lookup_library_item_from_id(item_id);

    if (!item)
        return "Item not found";
    // check if the item is checked out
    if (item -> get_location() == OUT)
    {
        // check if anyone requested the returning item
        if (item -> get_requested_by() != NONE)
        {
            // update the status
            item -> set_location(HOLD);
        }
        else
        {
            // update the status
            item -> set_location(IN);
        }
        Patron* patron = lookup_patron_from_id(item -> get_checked_out_by());
        // remove the item from checked out list
        patron -> remove_library_item(item);
        
        return "Return successful";
    }
    else
        return "Item already in library";
} // end of return_library_item



// ==== Library::request_library_item ==========================================
//
// This function allows a library member to place a hold on an item. It takes a 
// patron ID and an item ID as parameters, verifies the existence of both the 
// patron and the item in the library, and checks if the item is already on 
// hold.
//
// Input:
//      patron_id [IN]  -- a speficied patron id, an integer variable to lookup
//                         in the library
//
//      item_id   [IN]  -- a specified item id, an integer variable to lookup in 
//                         the library
//
// Output:
//      strings   [OUT] -- differnt corresponding messages are returned as the
//                         result of the operation
//
// ============================================================================
string Library::request_library_item(int patron_id, int item_id)
{
    LibraryItem* item = lookup_library_item_from_id(item_id);
    Patron* patron = lookup_patron_from_id(patron_id);

    if (!item)
        return "Item not found";
    else if (!patron)
        return "Patron not found";
    // check if someone else requested
    if (item->get_requested_by() != NONE)
    {
        return "Item already on hold";
    }
    else
    {
        // otherwise update the status of the item
        item -> set_location(HOLD);
        item -> set_requested_by(patron -> get_patron_name());
    }
    return "Request Successful";
} // end of request_library_item



// ==== Library::pay_fine =====================================================
//
// This function processes fine payments for library patrons.
//
// Input:
//      patron_id [IN]  -- a specified item id, an integer variable to lookup in 
//                         the library
//
//      amount    [IN]  -- a fixed amount of .10 cents after each due date
//
// Output:
//      strings   [OUT] -- differnt corresponding messages are returned as the
//                         result of the operation
//
// ============================================================================
string Library::pay_fine(int patron_id, double amount)
{
    Patron* patron = lookup_patron_from_id(patron_id);

    if(!patron)
        return "Patron not found";
    else
        // add the payment amount
        patron -> amend_fine(-amount);

    return "Payment Successful";
} // end of pay_fine



// ==== Library::increment_current_date =======================================
//
// This function progresses the library's current date by one day and increases 
// fines for any patrons who have overdue items.
//
// Input:
//      N/A
//
// Output:
//      N/A
//
// ============================================================================
void Library::increment_current_date()
{
    double fine = .10;
    ++m_current_date;

    for (Patron* patron : members)
    {
        // retrieve every checked out items from a patron
        vector<LibraryItem*> checked_out = patron -> get_checked_out_items();
        // traverse through each checked out items
        for (LibraryItem* items : checked_out)
        {
            // calculate the overdue date
            int days_checked_out = m_current_date - 
                                   (items -> get_date_checked_out());
            int overdue = days_checked_out - (items -> get_check_out_length());
            // charge the correct amount of late fee
            if (overdue > 0)
                patron -> amend_fine(fine);
        }
    }
} // end of increment_current_date