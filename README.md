# LibrarySimulator

This project is a simulation of a library system involving multiple classes: Library, Patron(users), and LibraryItems(books, albums, and movies).

The system supports common library operations such as checkign out items, returning items, requesting items, paying/calculating fines for overdue
items, and incrementing dates. Each operation takes into account various factors such as item availability, patron status, item status, and etc.

Classes:

LibraryItem:
Represents a generic library item that can be checked out by patrons. It has subclasses for specific types of library items.

Patron:
Represents a patron of the library. Patrons have their own unique IDs(integers) and can cehck out or request LibraryItems.

Library:
Represents the entire libraray system. It maintains colections of all available LibraryItems and resgistered Patrons in the system.

Usage Example:
int main()
{
    // initialize library items
    Book b(123, "Phantom", "Juster");
    Album a(456, "...And", "Fast");
    Movie m(567, "laput", "miyaza");

    // initialize Patrons(users)
    Patron p1(000, "Joe");
    Patron p2(111, "YAAA");

    // initialize the library
    Library Lib;

    // add items to library
    lib.add_library_item(&b);
    lib.add_library_item(&a);
    lib.add_patron(&p1);
    lib.add_patron(&p2);

    // check out an item
    lib.check_out_library_item (111, 456);

    // increment the date
    for (int i = 0; i < 7; ++i)
    {
        lib.increment_current_date();
    }

    lib.check_out_library_item(000, 567);

    // check the location, id, title, and etc.
    cout << a.get_location() << " " << b.get_library_id() << " " << b.get_title() << endl;

    for (int i = 0; i < 15; ++i)
    {
        lib.increment_current_date();
    }

    // check how much patrons owe
    cout << "Fine for Joe: " << p1.get_fine_amount() << endl;
    cout << "Fine for David: " << p2.get_fine_amount() << endl;

    // pay overdue fine
    lib.pay_fine(111, p1_fine);

    // return an item
    lib.return_library(456);
}
