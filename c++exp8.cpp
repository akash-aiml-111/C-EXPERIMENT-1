#include <iostream>
#include <cstring>
#include <utility>
using namespace std;

class String
{
private:
    char* data;
    size_t length;

public:
    String(const char* str = "")
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    // Copy Constructor
    String(const String& other)
    {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    // Move Constructor
    String(String&& other) noexcept
    {
        data = other.data;
        length = other.length;

        other.data = nullptr;
        other.length = 0;
    }

    // Copy Assignment
    String& operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] data;

            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }

        return *this;
    }

    // Move Assignment
    String& operator=(String&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data;

            data = other.data;
            length = other.length;

            other.data = nullptr;
            other.length = 0;
        }

        return *this;
    }

    // Destructor
    ~String()
    {
        delete[] data;
    }

    void display() const
    {
        if (data != nullptr)
            cout << data << endl;
    }
};

// Perfect Forwarding
template <typename T>
String createString(T&& value)
{
    return String(forward<T>(value));
}

int main()
{
    string input;

    cout << "Enter a string: ";
    getline(cin, input);

    String original(input.c_str());

    cout << "\nOriginal String: ";
    original.display();

    // Copy Operation
    String copy = original;

    cout << "Copied String: ";
    copy.display();

    // Move Operation
    String moved = move(original);

    cout << "Moved String: ";
    moved.display();

    // Perfect Forwarding
    String forwarded = createString(input.c_str());

    cout << "Perfect Forwarding Result: ";
    forwarded.display();

    return 0;
}
