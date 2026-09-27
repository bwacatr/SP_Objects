// ClassesPract.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>
#include <string>
#define DEBUG



using namespace std;
class ServiceOrder
{
public:

    ServiceOrder(string client, string device, double diagnosticCost) : client(client), device(device), diagnosticCost(diagnosticCost) {}

    string GetClient() {
        return client;
    }

    void SetClient(string input) {
        try
        {
            if (input.empty())
            {
                throw invalid_argument("Ошибка: введена пустая строка");
            }

            client = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    string GetDevice() {
        return device;
    }

    void SetDevice(string input) {
        try
        {
            if (input.empty())
            {
                throw invalid_argument("Ошибка: введена пустая строка");
            }

            device = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    double GetDiagnosticCost() {

        return diagnosticCost;
    }

    void SetDiagnosticCost(double input) {
        try
        {
            if (input < 0)
            {
                throw invalid_argument("Ошибка: цена диагностики не может быть отрицательной");
            }

            diagnosticCost = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    void printInfo()
    {
        cout << "Клиент: " << client << "\n" << "Устройство: " << device << "\n" << "Цена диагностики: " << diagnosticCost << endl;
    }

    void RandomizeDiagnosticCost()
    {

        int num = rand() % 3001;

        SetDiagnosticCost(num);
    }

protected:
    std::string client{ "" };
    std::string device{ "" };
    double diagnosticCost{ 0.0 };
};

class RepairOrder : public ServiceOrder
{
public:
    using ServiceOrder::ServiceOrder;

    RepairOrder(string client, string device, double diagnosticCost, double partsCost, int workHours, double hourRate) : ServiceOrder(client,device,diagnosticCost), partsCost(partsCost), workHours(workHours), hourRate(hourRate) {}
    double GetPartsCost() {
        return partsCost;
    }

    void printInfoRepairOrder()
    {
        printInfo();

        cout << "Цена запчастей: " << partsCost << "\n" << "Часы работы: " << workHours << "\n" << "Оплата по часам: " << hourRate << "\n" << "Общая цена: " << calculateCost() << "\n" << "Цена работы сотрудников: " << laborCost() << "\n" << "Средняя цена часа: " << averageCostPerHour() << endl;
    }

    static RepairOrder CreateRepairOrder()
    {
        cout << "Введите имя клиента:" << endl;
        try
        {
           
            string client;
            getline(cin, client);
            if (client.empty())
            {
                throw invalid_argument("Ошибка: имя клиента не может быть пустым");
            }
                
            
        
            cout << "Введите название устройства:" << endl;
        
            string device;
            getline(cin, device);
            if (device.empty())
            {
                throw invalid_argument("Ошибка: название устройства не может быть пустым");
            }
        
            cout << "Введите цену диагностики" << endl;
        
            double diagnosticCost;
            cin.ignore();
            cin >> diagnosticCost;

            if (diagnosticCost < 0)
            {
                throw invalid_argument("Ошибка: цена диагностики не может быть отрицательной");
            }
        
            cout << "Введите цену запчастей" << endl;
        
            double partsCost;
            cin.ignore();
            cin >> partsCost;

            if (partsCost < 0)
            {
                throw invalid_argument("Ошибка: цена запчастей не может быть отрицательной");
            }
        
        
            cout << "Введите часы работы" << endl;
        
            int workHours;
            cin.ignore();
            cin >> workHours;

            if (workHours <= 0)
            {
                throw invalid_argument("Ошибка: кол-во рабочих часов должно быть больше 0");
            }
        
            cout << "Введите оплату по часу" << endl;
        
            int hourRate;
            cin.ignore();
            cin >> hourRate;

            if (hourRate <= 0)
            {
                throw invalid_argument("Ошибка: оплата по часу должна быть больше 0");
            }
            RepairOrder repairOrder(client, device, diagnosticCost, partsCost, workHours, hourRate);
            return repairOrder;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    void SetPartsCost(double input) {
        try
        {
            if (input < 0)
            {
                throw invalid_argument("Ошибка: цена запчастей не может быть отрицательной");
            }
            partsCost = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    int GetWorkHours() {
        return workHours;
    }

    void SetWorkHours(int input) {
        try
        {
            if (input <= 0)
            {
                throw invalid_argument("Ошибка: кол-во рабочих часов должно быть больше 0");
            }
            workHours = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    double GetHourRate() {
        return hourRate;
    }

    void SetHourRate(double input) {
        try
        {
            if (input <= 0)
            {
                throw invalid_argument("Ошибка: оплата по часу должна быть больше 0");
            }

            hourRate = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    double calculateCost()
    {
        return GetDiagnosticCost() + GetPartsCost() + laborCost();
    }

    double laborCost()
    {
        return hourRate * workHours;
    }

    double averageCostPerHour()
    {
        return calculateCost() / static_cast<double>(workHours);
    }

private:
    double partsCost{ 0.0 };
    int workHours{ 0 };
    double hourRate{ 0 };
};

class MaintenanceOrder : public ServiceOrder // maintenanceOrder
{
public:
    using ServiceOrder::ServiceOrder;

    MaintenanceOrder(string client, string device, double diagnosticCost, int operations, double operationPrice, int discountPercent) : ServiceOrder(client, device, diagnosticCost), operations(operations), operationPrice(operationPrice), discountPercent(discountPercent) {}
    double GetDiscountPercent() {
        return discountPercent;
    }

    void printInfoMaintenanceOrder()
    {
        printInfo();
        

        cout << "Кол-во операций: " << operations << "\n" << "Цена одной операции: " << operationPrice << "\n" << "Скидка в процентах: " << discountPercent << "\n" << "Общая цена: " << calculateCost() << "\n" << "Цена операций: " << operationsCost() << "\n" << "Скидка в деньгах: " << discountAmount() << endl;
        
    }

    static MaintenanceOrder CreateMaintenanceOrder()
    {
        cout << "Введите имя клиента:" << endl;
        try
        {

            string client;
            getline(cin, client);
            if (client.empty())
            {
                throw invalid_argument("Ошибка: имя клиента не может быть пустым");
            }



            cout << "Введите название устройства:" << endl;

            string device;
            getline(cin, device);
            if (device.empty())
            {
                throw invalid_argument("Ошибка: название устройства не может быть пустым");
            }

            cout << "Введите цену диагностики" << endl;

            double diagnosticCost;
            cin.ignore();
            cin >> diagnosticCost;

            if (diagnosticCost < 0)
            {
                throw invalid_argument("Ошибка: цена диагностики не может быть отрицательной");
            }

            cout << "Введите кол-во операций" << endl;

            int operations;
            cin.ignore();
            cin >> operations;

            if (operations <= 0)
            {
                throw invalid_argument("Ошибка: кол-во операций должно быть больше 0");
            }


            cout << "Введите цену одной операции" << endl;

            double operationPrice;
            cin.ignore();
            cin >> operationPrice;

            if (operationPrice <= 0)
            {
                throw invalid_argument("Ошибка: цена одной операции должна быть больше 0");
            }

            cout << "Введите процент скидки" << endl;

            int discountPercent;
            cin.ignore();
            cin >> discountPercent;

            if (discountPercent < 0 || discountPercent > 100)
            {
                throw invalid_argument("Ошибка: процент скидки не может быть меньше 0 или больше 100");
            }
            MaintenanceOrder maintenanceOrder(client, device, diagnosticCost, operations, operationPrice, discountPercent);
            return maintenanceOrder;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }

    }

    void SetDiscountPercent(int input) {
        try
        {
            if (input < 0 || input > 100)
            {
                throw invalid_argument("Ошибка: процент скидки не может быть меньше 0 или больше 100");
            }
            discountPercent = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    int GetOperationPrice() {
        return operationPrice;
    }

    void SetOperationPrice(double input) {
        try
        {
            if (input <= 0)
            {
                throw invalid_argument("Ошибка: цена одной операции должна быть больше 0");
            }

            operationPrice = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    double GetOperations() {
        return operations;
    }

    void SetOperations(int input) {
        try
        {
            if (input <= 0)
            {
                throw invalid_argument("Ошибка: кол-во операций должно быть больше 0");
            }
            operations = input;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << endl;
        }
        
    }

    double calculateCost()
    {
        return GetDiagnosticCost() + operationsCost() - discountAmount();
    }

    double discountAmount()
    {
        return calculateCost() * static_cast<double>(discountPercent) / 100;
    }

    double operationsCost()
    {
        return operations * operationPrice;
    }

    

private:
    int operations{ 0 };
    double operationPrice{ 0 };
    int discountPercent{ 0 };
};

int main()
{
    setlocale(LC_ALL, "Russian");

    srand(time(NULL));

#if defined DEBUG
    cout << "------------ Отладка ------------" << endl;
    RepairOrder repairOrder("client", "device", 100, 500, 12, 440);
    MaintenanceOrder maintenanceOrder("client2", "device2", 150, 3, 200, 10);
#else

    cout << "Введите данные о заказе на починку" << endl;

    RepairOrder repairOrder = RepairOrder::CreateRepairOrder();

    cout << "\n" << "Введите данные о заказе на обслуживание" << endl;

    MaintenanceOrder maintenanceOrder = MaintenanceOrder::CreateMaintenanceOrder();

    cout << "\n" << "Исходное состояние заказа на починку" << endl;

    repairOrder.printInfoRepairOrder();

    cout << "\n" << "Исходное состояние заказа на обслуживание" << endl;

    maintenanceOrder.printInfoMaintenanceOrder();

    if (repairOrder.calculateCost() > maintenanceOrder.calculateCost())
    {
        cout << "\n" << "Заказ на починку дороже заказа на обслуживание" << endl;
    }
    else if (repairOrder.calculateCost() < maintenanceOrder.calculateCost())
    {
        cout << "\n" << "Заказ на починку дешевле заказа на обслуживание" << endl;
    }
    else
    {
        cout << "\n" << "Заказ на починку имеет ту же стоимость, что и заказ на обслуживание" << endl;
    }
#endif





    bool skip = false;

    

    
    do
    {
        
        cout << "\n" << "Изменение данных" << "\n" << "1 - Заказ на починку" << "\n" << "2 - Заказ на обслуживание" << "\n" << "любая другая цифра - выход" << endl;
        
        int input;
        
        cin >> input;

        if (input == 1) //доделать изменение данных
        {
            int inputSwitch;
            cout << "\n" << "Изменение данных заказа на починку" << "\n" << "1 - имя клиента" << "\n" << "2 - название устройства" << "\n" << "3 - цена диагностики" << "\n" << "4 - цена запчастей" << "\n" << "5 - рабочие часы" << "\n" << "6 - оплата по часам" << "\n" << "7 - изменить цену диагностики на случайное число между 0 и 3000" << "\n" << "остальные цифры - пропуск" << endl;
            cin >> inputSwitch;

            string client;
            string device;
            double diagnosticCost;
            double partsCost;
            int workHours;
            double hourRate;

            
            switch (inputSwitch)
            {
            case 1:
                cout << "Введите имя клиента" << endl;
                cin >> client;

                repairOrder.SetClient(client);
                repairOrder.printInfoRepairOrder();
                break;
            case 2:
                cout << "Введите название устройства" << endl;
                cin >> device;

                repairOrder.SetDevice(client);
                repairOrder.printInfoRepairOrder();
                break;
            case 3:
                cout << "Введите цену диагностики" << endl;
                
                cin >> diagnosticCost;

                repairOrder.SetDiagnosticCost(diagnosticCost);
                repairOrder.printInfoRepairOrder();
                break;
            case 4:
                cout << "Введите цену запчастей" << endl;
               
                cin >> partsCost;

                repairOrder.SetPartsCost(partsCost);
                repairOrder.printInfoRepairOrder();
                break;
            case 5:
                cout << "Введите кол-во рабочих часов" << endl;
                
                cin >> workHours;

                repairOrder.SetWorkHours(workHours);
                repairOrder.printInfoRepairOrder();
                break;
            case 6:
                cout << "Введите оплату по часам" << endl;
               
                cin >> hourRate;

                repairOrder.SetHourRate(workHours);
                repairOrder.printInfoRepairOrder();
                break;

            case 7:
                repairOrder.RandomizeDiagnosticCost();
                repairOrder.printInfoRepairOrder();
                break;
            default:
                cout << "Изменение данных пропущено. Возврат к выбору заказов." << endl;
                break;
            }
        }
        else if (input == 2) // обслуживание
        {
            int inputSwitch;
            cout << "\n" << "Изменение данных заказа на починку" << "\n" << "1 - имя клиента" << "\n" << "2 - название устройства" << "\n" << "3 - цена диагностики" << "\n" << "4 - кол-во операций" << "\n" << "5 - цена одной операции" << "\n" << "6 - процент скидки в целых числах" << "7 - изменить цену диагностики на случайное число между 0 и 3000" << "\n" << "остальные кнопки - пропуск" << endl;

            cin >> inputSwitch;

            string client;
            string device;
            double diagnosticCost;
            int operations;
            int discountPercent;
            double operationPrice;

            switch (inputSwitch)
            {
            case 1:
                cout << "Введите имя клиента" << endl;
                cin >> client;

                maintenanceOrder.SetClient(client);
                maintenanceOrder.printInfoMaintenanceOrder();
                break;
            case 2:
                cout << "Введите название устройства" << endl;
                cin >> device;

                maintenanceOrder.SetDevice(client);
                maintenanceOrder.printInfoMaintenanceOrder();
                break;
            case 3:
                cout << "Введите цену диагностики" << endl;
                
                cin >> diagnosticCost;

                maintenanceOrder.SetDiagnosticCost(diagnosticCost);
                maintenanceOrder.printInfoMaintenanceOrder();
                break;
            case 4:
                cout << "Введите кол-во операций" << endl;
                
                cin >> operations;

                maintenanceOrder.SetOperations(operations);
                maintenanceOrder.printInfoMaintenanceOrder();
                break;
            case 5:
                cout << "Введите цену одной операции" << endl;
                
                cin >> operationPrice;

                maintenanceOrder.SetOperationPrice(operationPrice);
                maintenanceOrder.printInfoMaintenanceOrder();
                break;
            case 6:
                cout << "Введите скидку целым числом" << endl;
               
                cin >> discountPercent;

                maintenanceOrder.SetDiscountPercent(discountPercent);
                maintenanceOrder.printInfoMaintenanceOrder();
                break;
            case 7:
                maintenanceOrder.RandomizeDiagnosticCost();
                maintenanceOrder.printInfoMaintenanceOrder();
                break;
            default:
                cout << "Изменение данных пропущено. Возврат к выбору заказов." << endl;
                break;
            }
        }
        else
        {
            skip = true;
        }
    } 
    while (skip == false);


    if (repairOrder.calculateCost() > maintenanceOrder.calculateCost())
    {
        cout << "\n" << "Заказ на починку дороже заказа на обслуживание" << endl;
    }
    else if (repairOrder.calculateCost() < maintenanceOrder.calculateCost())
    {
        cout << "\n" << "Заказ на починку дешевле заказа на обслуживание" << endl;
    }
    else
    {
        cout << "\n" << "Заказ на починку имеет ту же стоимость, что и заказ на обслуживание" << endl;
    }


    repairOrder.printInfoRepairOrder();
    maintenanceOrder.printInfoMaintenanceOrder();
    

    
}