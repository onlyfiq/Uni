#include "Date.h"
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    cout << "Test 1: Default constructor\n";
    Date d1;
    cout << d1 << "\n\n";

    cout << "Test 2: Parameterized constructor\n";
    Date d2(25, 12, 2020);
    cout << d2 << "\n\n";

    cout << "Test 3: Parameterized constructor\n";
    try
    {
        Date d3(0, 5, 2020);
    }
    catch (exception &e)
    {
        cout << "Caught expected: " << e.what() << "\n";
    }
    try
    {
        Date d4(15, 13, 2020);
    }
    catch (exception &e)
    {
        cout << "Caught expected: " << e.what() << "\n";
    }
    try
    {
        Date d5(10, 10, 0);
    }
    catch (exception &e)
    {
        cout << "Caught expected: " << e.what() << "\n";
    }
    cout << "\n";

    cout << "Test 4: SetDate valid + invalid\n";
    Date s;
    s.SetDate(7, 11, 2022);
    cout << s << "\n";

    try
    {
        s.SetDate(32, 1, 2022);
    }
    catch (exception &e)
    {
        cout << "Caught expected: " << e.what() << "\n";
    }
    cout << "\n";

    cout << "Test 5: Get methods\n";
    Date g(28, 3, 2023);
    cout << "Day: " << g.GetDay() << "\n";
    cout << "Month: " << g.GetMonth() << "\n";
    cout << "Year: " << g.GetYear() << "\n";
    cout << "Month name: " << g.GetMonthNames() << "\n\n";

    cout << "Test 6: Comparison operators\n";
    Date a(10, 10, 2020);
    Date b(11, 10, 2020);
    Date c(10, 10, 2020);
    cout << "(a < b): " << (a < b) << "\n";
    cout << "(b < a): " << (b < a) << "\n";
    cout << "(a == c): " << (a == c) << "\n\n";

    cout << "Test 7: Stream input valid\n";
    stringstream ss1("12 8 2021");
    Date si1;
    ss1 >> si1;
    cout << si1 << "\n\n";

    cout << "Test 8: Stream input invalid\n";
    stringstream ss2("0 5 2021");
    try
    {
        Date si2;
        ss2 >> si2;
        cout << "ERROR: no exception\n";
    }
    catch (exception &e)
    {
        cout << "Caught expected: " << e.what() << "\n";
    }
    cout << "\n";

    cout << "Test 9: Output stream\n";
    Date out(3, 4, 2020);
    cout << out << "\n";

    return 0;
}
