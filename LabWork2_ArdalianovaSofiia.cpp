#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

double a, b, h;
int n;
bool dataReady = false;

void clearScreen()
{
    system("cls");
}

void line()
{
    cout << "--------------------------------------------------\n";
}

void waitEnter()
{
    cout << "\nPress Enter to return to main menu...";
    cin.get();
}

double inputNumber(string text)
{
    string s;
    double value;
    char extra;
    cout << text;
    while (true)
    {
        if (!getline(cin, s)) exit(0);        // read the whole line (exit if input is closed)

        for (int i = 0; i < (int)s.length(); i++)  // 1,5 -> 1.5
        {
            if (s[i] == ',') s[i] = '.';
        }

        stringstream ss(s);
        if (ss >> value && !(ss >> extra))    // a number and nothing else after it
        {
            return value;
        }
        cout << "  [!] Error: enter a number (for example 2 or 1.5): ";
    }
}

double calculate(double x)
{
    double y = 0;

    if (x < 0)
    {
        for (int i = 2; i <= n; i++)
        {
            y = y + pow(i - 3 + x, 2);
        }
        y = y - 5 * x;
    }
    else
    {
        for (int i = 0; i <= n; i++)
        {
            double p = 1;
            for (int j = 1; j <= n - 1; j++)
            {
                p = p * (i + j) / (2 * pow(1 + x, 2));
            }
            y = y + p;
        }
    }
    return y;
}

void showEntryScreen()
{
    clearScreen();
    line();
    cout << "        Function Calculator (Task 1)\n";
    line();
    cout << "Welcome to the calculator.\n";
    cout << "Press Enter to see the Main Menu...";
    cin.get();
}

void showMenu()
{
    clearScreen();
    line();
    cout << "        Function Calculator\n";
    line();
    cout << "1. Enter data (a, b, h, n)\n";
    cout << "2. Calculate and show results\n";
    cout << "3. Show formula and help\n";
    cout << "4. Exit\n";
    line();
}

void enterData()
{
    clearScreen();
    line();
    cout << "        Enter data\n";
    line();

    do
    {
        a = inputNumber("Enter a (start of range): ");
        b = inputNumber("Enter b (end of range):   ");
        if (a >= b)
        {
            cout << "  [!] Error: a must be less than b. Enter again.\n";
        }
    } while (a >= b);

    do
    {
        h = inputNumber("Enter h (step, h > 0):    ");
        if (h <= 0)
        {
            cout << "  [!] Error: h must be greater than 0. Enter again.\n";
        }
    } while (h <= 0);

    double temp;
    do
    {
        temp = inputNumber("Enter n (integer, n >= 2): ");
        if (temp < 2 || temp != (int)temp)
        {
            cout << "  [!] Error: n must be an integer, n >= 2. Enter again.\n";
        }
    } while (temp < 2 || temp != (int)temp);
    n = (int)temp;

    dataReady = true;
    cout << "\nData saved successfully!\n";
    waitEnter();
}

void showResults()
{
    clearScreen();
    line();
    cout << "        Results\n";
    line();

    if (dataReady == false)
    {
        cout << "  [!] No data yet. Choose option 1 first.\n";
        waitEnter();
        return;
    }

    ofstream file("results.txt");   // create (or rewrite) the file

    cout << "a = " << a << ", b = " << b << ", h = " << h << ", n = " << n << "\n";
    file << "a = " << a << ", b = " << b << ", h = " << h << ", n = " << n << "\n";
    line();
    cout << setw(5) << "#" << setw(14) << "x" << setw(22) << "y" << "\n";
    file << setw(5) << "#" << setw(14) << "x" << setw(22) << "y" << "\n";
    line();

    int k = 1;
    for (double x = a; x <= b + 0.000001; x = x + h)
    {
        double y = calculate(x);
        cout << setw(5) << k << setw(14) << fixed << setprecision(3) << x
            << setw(22) << setprecision(4) << y << "\n";
        file << setw(5) << k << setw(14) << fixed << setprecision(3) << x
            << setw(22) << setprecision(4) << y << "\n";
        k++;
    }
    file.close();

    line();
    cout << "Results are saved to the file results.txt\n";
    waitEnter();
}

void showFormula()
{
    clearScreen();
    line();
    cout << "        Formula and help\n";
    line();
    cout << "y = sum(i=2..n) (i-3+x)^2 - 5x,                      x < 0\n";
    cout << "y = sum(i=0..n) prod(j=1..n-1) (i+j)/(2(1+x)^2),      x >= 0\n\n";
    cout << "Constraints: a < b, step h > 0, n is an integer, n >= 2.\n";
    cout << "The program calculates y for x = a, a+h, a+2h, ... while x <= b.\n";
    cout << "Decimal numbers can be typed with a dot or a comma (1.5 or 1,5).\n";
    cout << "The results are also saved to the file results.txt.\n";
    waitEnter();
}

int main()
{
    int choice = 0;

    showEntryScreen();

    while (choice != 4)
    {
        showMenu();
        if (choice < 0 || choice > 4)
        {
            cout << "  [!] Unknown option. Please type 1, 2, 3 or 4.\n";
        }
        cout << "Select option: ";

        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            choice = -1;
        }
        cin.ignore(1000, '\n');

        if (choice == 1) enterData();
        if (choice == 2) showResults();
        if (choice == 3) showFormula();
    }

    clearScreen();
    cout << "Exiting program...\nGoodbye!\n";
    return 0;
}