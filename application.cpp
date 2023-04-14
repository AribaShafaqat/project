#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;
void readDataFromFile();
void viewUsers();
const int userArrSize = 10;
string users[userArrSize];
string passwords[userArrSize];
string roles[userArrSize];
int usersCount = 0;
string plants[100];
int prices[100];
int size = 0; // for plant and price array
void header();
void subMenu(string submenu);
void clearScreen();
int OwnerMenu();
int ManagerMenu();
int CustomerMenu();
void OwnerInterface();
void ManagerInterface();
void CustomerInterface();
int loginMenu();
string names[100];
string passwards[100];
bool signUp(string name, string password, string role);
string signIn(string name, string password);
void storeInFile(string name, string password, string role);
void stock();
void addPlant();
void deletePlant();
void salesadd();
string plantReturn(int index);
int priceReturn(int index);
string npasswords;
string pusername;
string username[30];
string password[30];
int csize = -1;
void storeCustomInfo();
int totalPrice;
void sales();
int TotalSales;
void plprAdding();
void loadData();
void loadCustomInfo();
void viewCustomerInfo();
void updatePlantPrice();

main()
{
    
    // plprAdding();//add data of plants and price in file
    loadData(); // loads the data in plant and price array
    readDataFromFile();
    int loginOption = 0;
    while (loginOption != 4)
    {
        header();
        subMenu("Login");
        loginOption = loginMenu();
        if (loginOption == 1)
        {
            system("cls");

            string name;
            string password;
            string role;
            header();
            subMenu("SignIn");
            cout << "Enter your Name: " << endl;
            cin >> name;
            cout << "Enter your Password: " << endl;
            cin >> password;
            role = signIn(name, password);

            if (role == "Owner")
            {
                clearScreen();
                OwnerInterface();
            }
            else if (role == "Manager")
            {
                clearScreen();
                ManagerInterface();
            }
            else if (role == "Customer")
            {
                clearScreen();
                CustomerInterface();
            }
            else if (role == "undefined")
            {
                cout << "You Entered wrong Credentials" << endl;
            }
        }
        else if (loginOption == 2)
        {
            system("cls");
            string name;
            string password;
            string role;
            header();
            subMenu("SignUp");
            cout << "Enter your Name: " << endl;
            cin >> name;
            cout << "Enter your Password:(Your Passward shouldn't exceed 8 charecters) " << endl;
            cin >> password;
            if (password.length() > 8)
            {
                cout << "Your Passward is more than 8 charecters.. Please enter correct Password" << endl;
                cin >> password;
            }

            cout << "Enter your Role (Owner,Manager or Customer): " << endl;
            cin >> role;
            bool isValid = signUp(name, password, role);
            if (isValid)
            {
                cout << "SignedUp Successfully" << endl;
            }
            if (!isValid)
            {
                cout << "Users in the System have exceeded the Capacity" << endl;
            }
            storeInFile(name, password, role);
        }
       else if (loginOption == 3)
        {
            viewUsers();
        }
        clearScreen();
    }
}

int loginMenu()
{
    int option;
    cout << "1. Sign in" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. View Users"<<endl;
    cout << "4. Exit the Application" << endl;
    cout << "Enter the Option Number > ";
    cin >> option;
    return option;
}
string signIn(string name, string password)
{
    for (int index = 0; index < usersCount; index++)
    {
        if (users[index] == name && passwords[index] == password)
        {
            return roles[index];
        }
    }
    return "undefined";
}

bool signUp(string name, string password, string role)
{
    if (usersCount < userArrSize)
    {
        users[usersCount] = name;
        passwords[usersCount] = password;
        roles[usersCount] = role;
        usersCount++;

        if (role == "Customer")
        {
            npasswords = password;
            pusername = name;
        }
        return true;
    }
    else
    {
        return false;
    }
}
void storeInFile(string userName, string password, string role)
{
    fstream file;
    file.open("users.txt", ios::out);
    file << userName << ",";
    file << password << ",";
    file << role << endl;
    file.close();
}
void viewUsers()
{
    cout << "Usernames"
         << "\t"
         << "Passwords"
         << "\t"
         << "Role" << endl;
    for (int idx = 0; idx < usersCount; idx++)
    {
        cout << users[idx] << "\t\t" << passwords[idx] << "\t\t" << roles[idx] << endl;
    }
}
void readDataFromFile()
{
    string username;
    string password;
    string role;
    fstream file;
    string value;
    int commaCount = 0;
    file.open("users.txt", ios::in);
    while (getline(file, value))
    {
        for (int i = 0; i < value.length(); i++)
        {
            if (commaCount == 0)
            {
                if (value[i] != ',')
                {
                    username += value[i];
                }
                else
                {
                    commaCount++;
                }
            }
            else if (commaCount == 1)
            {
                if (value[i] != ',')
                {
                    password += value[i];
                }
                else
                {
                    commaCount++;
                }
            }
            else
            {
                role += value[i];
            }
        }
    }
    file.close();
}
void header()
{
    cout << " ---------------------------------------------------------------            " << endl;
    cout << " **                                                           **              " << endl;
    cout << " **                 NURSERY FARM MANAGEMENT                   **              " << endl;
    cout << " **                        SYSTEM                             **                   " << endl;
    cout << " **                                                           **                " << endl;
    cout << " ---------------------------------------------------------------              " << endl;
}
void subMenu(string submenu)
{
    string message = submenu + " Menu";
    cout << message << endl;
    cout << "---------------------" << endl;
}
void clearScreen()
{
    cout << "Press Any Key to Continue.." << endl;
    getch();
    system("cls");
}

int OwnerMenu()
{
    int option;
    cout << "Select one of the following options number..." << endl;
    cout << "1. View the stock" << endl;
    cout << "2. Adding a new stock " << endl;
    cout << "3. Deleting a stock" << endl;
    cout << "4. View  Record Monthly Sales" << endl;
    cout << "5. Update Price of Plant" << endl;
    cout << "6. Exit" << endl;
    cout << "Your Option..";
    cin >> option;
    return option;
}
int ManagerMenu()
{
    int option;
    cout << "Select one of the following options number..." << endl;
    cout << "1.Add Customer Information" << endl;
    cout << "2.Calculating Monthly Sales" << endl;
    cout << "3.View Customer Information" << endl;
    cout << "4.Exit" << endl;
    cout << "Your Option..";
    cin >> option;
    return option;
}
int CustomerMenu()
{
    int option;
    cout << "Select one of the following options number..." << endl;
    cout << "1.View stock                         " << endl;
    cout << "2.Select plants and show price                " << endl;
    cout << "3.Submit your Feedback                       " << endl;
    cout << "4.Exit" << endl;
    cout << "Your Option..";
    cin >> option;
    return option;
}
void OwnerInterface()
{
    int Owneroption = 0;
    while (Owneroption != 6)
    {
        header();
        subMenu("");
        Owneroption = OwnerMenu();
        if (Owneroption == 1)
        {
            system("cls");
            header();
            stock();

            clearScreen();
        }
        if (Owneroption == 2)
        {
            system("cls");
            addPlant();
        }
        if (Owneroption == 3)
        {
            system("cls");
            stock();
            deletePlant();
        }
        if (Owneroption == 4)
        {
            system("cls");
            sales();
        }
        if (Owneroption == 5)
        {
            system("cls");
            stock();
            updatePlantPrice();
        }
    }
}

void ManagerInterface()
{
    int Manageroption = 0;
    while (Manageroption != 4)
    {
        header();
        subMenu("");
        Manageroption = ManagerMenu();
        if (Manageroption == 1)
        {
            system("cls");
            storeCustomInfo();
        }
        else if (Manageroption == 2)
        {
            system("cls");
            header();
            sales();
        }
        else if (Manageroption == 3)
        {
            system("cls");
            loadCustomInfo();
            viewCustomerInfo();
        }
    }
}
void CustomerInterface()
{
    int Customeroption = 0;
    while (Customeroption != 4)
    {
        header();
        subMenu("");
        Customeroption = CustomerMenu();
        if (Customeroption == 1)
        {
            system("cls");
            header();
            stock();
        }
        else if (Customeroption == 2)
        {
            system("cls");
            stock();
            char ch;
            string n[100];
            int quantity;
            int priceplant[100];
            int sizee = -1;
            int index;
            totalPrice = 0;
            cout << "Please enter plant number:";
            cin >> index;
            cout << "Please enter plant quantity:";
            cin >> quantity;
            index = index - 1;
            int counter = 0;
            if (index < size)
            {
                do
                {
                    if (counter > 0)
                    {
                        cout << "Enter plant number:";
                        cin >> index;
                        cout << "Enter quantity:";
                        cin >> quantity;
                    }
                    sizee++;
                    string plant = plantReturn(index);
                    n[sizee] = plant;
                    int price = priceReturn(index);
                    priceplant[sizee] = price;
                    totalPrice += priceplant[sizee] * quantity;
                    cout << "Do you want to select more plants:";
                    cin >> ch;
                    counter++;
                } while (ch == 'y');
                TotalSales = totalPrice;
                cout << "Your Total Bill is :" << totalPrice << endl;
                salesadd();
            }
        }
        else if (Customeroption == 3)
        {
            system("cls");
            string Feedback;
            cout << "Enter your Feedback" << endl;
            cin >> Feedback;
            system("cls");
            header();
            cout << "Thank You For Your Response!!Shop Again" << endl;
            cout << "---------------------------------"<<endl;
        }
    }
}
void stock()
{
    int idx = 0;
    while (idx <= size)
    {
        cout << idx + 1 << "-" << plants[idx] << " " << prices[idx] << endl;
        idx++;
    }
}
void addPlant()
{
    if (size < 100)
    {
        size = size + 1;
        string newPlant;
        string newPrice;
        cout << "Please enter plant to add:";
        cin >> newPlant;
        for(int idx=0;idx<30;idx++)
        {
        if(newPlant==plants[idx])
        {
        
            cout<<"Plant exist already. Enter Again"<<endl;
            cin>>newPlant;
        }
        }
       

        cout << "Please enter price of plant:";
        cin >> newPrice;
        fstream out;
        out.open("plant.txt", ios::app);
        out << newPlant << "," << newPrice << "\n";
        out.close();
        loadData();
    }
}

void deletePlant()
{
    int index;
    cout << "enter idx" << endl;
    cin >> index;
    index--; // because size starts from 0
    fstream in, out;
    in.open("plant.txt", ios::in);
    out.open("plantsDuplicate.txt", ios::out);
    string plantName;
    plantName = plants[index];
    string value;
    int i;
    string compare;
    int j = 0;
    while (getline(in, value))
    {
        compare = "";
        for (i = 0; i < value.length(); i++)
        {

            if (value[i] != ',')
            {
                compare += value[i];
            }
            else
            {
                if (compare != plantName)
                {
                    out << value << "\n";
                    break;
                }
                else
                {
                    break;
                }
            }
        }
        j++;
    }
    out.close();
    in.close();
    remove("plant.txt");
    rename("plantsDuplicate.txt", "plant.txt");
    size--;
    loadData();
}
void updatePlantPrice()
{
    int index;
    string newPlantPrice = "", plantName = "";
    cout << "enter idx" << endl;
    cin >> index;
    index--; // because size starts from 0
    cout << "enter new price:";
    cin >> newPlantPrice;
    fstream in, out;
    in.open("plant.txt", ios::in);
    out.open("plantsDuplicate.txt", ios::out);
    plantName = plants[index];
    string value;
    int i;
    string compare;
    int j = 0;
    while (getline(in, value))
    {
        compare = "";
        for (i = 0; i < value.length(); i++)
        {
            if (value[i] != ',')
            {
                compare += value[i];
            }
            else
            {
                if (compare != plantName)
                {
                    out << value << "\n";
                    break;
                }
                else
                {

                    out << plantName << "," << newPlantPrice << "\n";
                    break;
                }
            }
        }
        j++;
    }
    out.close();
    in.close();
    remove("plant.txt");
    rename("plantsDuplicate.txt", "plant.txt");
    loadData();
}
string plantReturn(int index)
{
    return plants[index];
}
int priceReturn(int index)
{
    return prices[index];
}
void storeCustomInfo()
{
    fstream out;
    out.open("customerInfo.txt", ios::app);
    out << pusername << "," << npasswords << "\n";
    out.close();
}
void loadCustomInfo()
{
    fstream in;
    in.open("customerInfo.txt", ios::in);
    string value;
    int i;
    int j = 0;
    while (getline(in, value))
    {
        string customerUserName = "";
        for (i = 0; i < value.length(); i++)
        {

            if (value[i] != ',')
            {
                customerUserName += value[i];
            }
            else
            {
                string customerPassword = "";
                for (; i < value.length(); i++)
                {
                    if (value[i] != ',')
                    {
                        customerPassword += value[i];
                    }
                }
                username[j] = customerUserName;
                password[j] = customerPassword;
            }
        }
        j++;
    }
    csize = j - 1; // for setting the range of arrays for customerInfoFile
    in.close();
}
void viewCustomerInfo()
{
    int idx = 0;
    while (idx <= csize)
    {
        cout << "Customer Info: " << username[idx] << "," << password[idx] << endl;
        idx++;
    }
}
void salesadd()
{

    fstream out;
    out.open("Sales.txt", ios::app);
    out << "Sale"
        << "," << TotalSales << "\n";
    out.close();
}
void sales()
{
    string value;
    fstream in;
    in.open("Sales.txt", ios::in);
    while (getline(in, value))
    {
        cout << value << endl;
    }
    in.close();
}
void plprAdding()
{
    string arr1[15] = {"Lilly", "Rose", "Tulip", "Stawberry", "Guava", "Cactus", "Marigold", "Lotus", "Shrub", "Gingko", "Fir", "Daffodil", "Aloe", "Spider Plant", "Golden Palm"};
    string arr2[15] = {"120", "130", "140", "40", "70", "320", "200", "155", "270", "340", "420", "160", "180", "290", "350"};
    fstream out;
    out.open("plant.txt", ios::out);
    for (int i = 0; i < 15; i++)
    {
        out << arr1[i] << "," << arr2[i] << "\n";
    }
    out.close();
}
void loadData()
{
    fstream in;
    in.open("plant.txt", ios::in);
    string value;
    int i;
    int j = 0;
    while (getline(in, value))
    {
        string plantt = ""; // setting it to empty string so that it can used for new data everytime
        for (i = 0; i < value.length(); i++)
        {

            if (value[i] != ',')
            {
                plantt += value[i];
            }
            else
            {
                string pricee = ""; // setting it to empty string so that it can used for new data everytime
                for (; i < value.length(); i++)
                {
                    if (value[i] != ',')
                    {
                        pricee += value[i];
                    }
                }
                plants[j] = plantt;
                prices[j] = stoi(pricee);
            }
        }
        j++;
    }
    size = j - 1; // sets the size untill where array is filled
    in.close();
}