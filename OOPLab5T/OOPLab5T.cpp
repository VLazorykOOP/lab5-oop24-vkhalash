#include <iostream>
#include <cmath>

using namespace std;

void MenuTask()
{
    cout << "    Menu Task\n";
    cout << "    1.  Task 1\n";
    cout << "    2.  Task 2\n";
    cout << "    3.  Task 3\n";
    cout << "    4.  Exit\n";
}

class Triad
{
protected:
    double a, b, c;

public:
    Triad(double a, double b, double c) : a(a), b(b), c(c) {}

    void setA(double newA) { a = newA; }
    void setB(double newB) { b = newB; }
    void setC(double newC) { c = newC; }

    double sum() const { return a + b + c; }
};

class Triangle : public Triad
{
public:
    Triangle(double a, double b, double c) : Triad(a, b, c) {}

    double angleA() const { return acos((b * b + c * c - a * a) / (2 * b * c)) * 180.0 / M_PI; }
    double angleB() const { return acos((a * a + c * c - b * b) / (2 * a * c)) * 180.0 / M_PI; }
    double angleC() const { return acos((a * a + b * b - c * c) / (2 * a * b)) * 180.0 / M_PI; }

    double area() const
    {
        double s = sum() / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

class Window;

class Button
{
public:
    // Constructor that accepts button text
    Button(const string &text) : text(text) {}

    // Method for setting a callback function
    void setOnClick(void (Window::*onClick)())
    {
        this->onClick = onClick;
    }

    // Method that calls a callback function
    void click(Window *window)
    {
        if (onClick != nullptr)
        {
            (window->*onClick)();
        }
    }

    string getText() const
    {
        return text;
    }

private:
    string text;
    // Pointer to a callback function
    void (Window::*onClick)() = nullptr;
};

class Title
{
public:
    // Constructor that accepts the header text
    Title(const string &text) : text(text) {}

    string getText() const
    {
        return text;
    }

private:
    string text;
};

class Window
{
public:
    // Constructor that accepts the title text and button text
    Window(const string &titleText, const string &buttonText) : title(titleText), button(buttonText)
    {
        // Callback function for the button
        button.setOnClick(&Window::onButtonClick);
    }

    void display() const
    {
        cout << "Window: " << title.getText() << endl;
        cout << "Button: " << button.getText() << endl;
    }

    void onButtonClick()
    {
        cout << "Button clicked" << endl;
    }

    void handleInput()
    {
        cout << "Press any key" << endl;
        cin.get();
        button.click(this);
    }

private:
    Title title;
    Button button;
};

int main()
{
    MenuTask();

    int choice;

    do
    {
        cout << "Choice ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Task 1
        {
            double sideA, sideB, sideC;

            cout << "Input sides" << endl;
            cout << "Side A ";
            cin >> sideA;
            cout << "Side B ";
            cin >> sideB;
            cout << "Side C ";
            cin >> sideC;

            // The sum of any two sides must be greater than the third side, and sides cannot be zero or negative
            if (sideA <= 0 || sideB <= 0 || sideC <= 0 || sideA + sideB <= sideC || sideA + sideC <= sideB || sideB + sideC <= sideA)
            {
                cout << "Invalid side lengths" << endl;
                return 1;
            }

            Triangle t(sideA, sideB, sideC);

            cout << "Perimeter = " << t.sum() << endl;
            cout << "Angles" << endl;
            cout << "A = " << t.angleA() << endl;
            cout << "B = " << t.angleB() << endl;
            cout << "C = " << t.angleC() << endl;
            cout << "Area = " << t.area() << endl;

            choice = 4;
            break;
        }
        case 2: // Task 2
        {
            Window window("Window", "Click");
            window.display();
            window.handleInput();

            choice = 4;
            break;
        }
        case 3: // Task 3
        {
            choice = 4;
            break;
        }
        case 4: // Exit
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    } while (choice != 4);

    return 0;
}
