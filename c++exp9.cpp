#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Observer Interface
class Observer
{
public:
    virtual void notify(const string& message) = 0;

    virtual ~Observer() {}
};

// Email Notification
class EmailNotification : public Observer
{
private:
    string email;

public:
    EmailNotification(string e)
    {
        email = e;
    }

    void notify(const string& message) override
    {
        cout << "Email sent to " << email
             << ": " << message << endl;
    }
};

// SMS Notification
class SMSNotification : public Observer
{
private:
    string phoneNumber;

public:
    SMSNotification(string number)
    {
        phoneNumber = number;
    }

    void notify(const string& message) override
    {
        cout << "SMS sent to " << phoneNumber
             << ": " << message << endl;
    }
};

// Factory Pattern
class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
        {
            return make_shared<EmailNotification>(receiver);
        }
        else if (type == "SMS")
        {
            return make_shared<SMSNotification>(receiver);
        }

        return nullptr;
    }
};

// Singleton Pattern
class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    EventManager()
    {
    }

public:
    EventManager(const EventManager&) = delete;

    EventManager& operator=(const EventManager&) = delete;

    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    void subscribe(shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void triggerEvent(const string& message)
    {
        cout << "\nEvent Triggered: " << message << endl;

        cout << "\nSending Notifications...\n";

        for (auto observer : observers)
        {
            observer->notify(message);
        }
    }
};

int main()
{
    EventManager& manager = EventManager::getInstance();

    int choice;
    string receiver, message;

    cout << "1. Email Notification" << endl;
    cout << "2. SMS Notification" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore();

    cout << "Enter Receiver Details: ";
    getline(cin, receiver);

    cout << "Enter Event Message: ";
    getline(cin, message);

    shared_ptr<Observer> notification;

    if (choice == 1)
    {
        notification =
            NotificationFactory::createNotification(
                "EMAIL", receiver);
    }
    else if (choice == 2)
    {
        notification =
            NotificationFactory::createNotification(
                "SMS", receiver);
    }
    else
    {
        cout << "Invalid Choice!" << endl;
        return 0;
    }

    manager.subscribe(notification);

    manager.triggerEvent(message);

    return 0;
}
