#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void paging(const int& quantity, const int& cur, int* arr)
{
    if ((cur >= 5) && (cur <= (quantity-4)))
    {
        arr[0] = 1;
        arr[1] = -1;
        int num = cur - 2;
        for (int i = 2; i < 7; ++i)
        {
            arr[i] = num;
            ++num;
        }
        arr[7] = -1;
        arr[8] = quantity;
    }
    if ((cur < 5) && (cur <= (quantity - 4)))
    {
        int i = 1;
        while(i <= cur+2)
        {
            arr[i-1] = i;
            ++i;
        }
        arr[i-1] = -1;
        arr[i] = quantity;
    }
    if ((cur >= 5) && (cur > (quantity - 4)))
    {
        arr[0] = 1;
        arr[1] = -1;
        int num = cur - 2;
        for (int i = 2; i < (quantity - cur + 5); ++i)
        {
            arr[i] = num;
            ++num;
        }
    }
    if ((cur < 5) && (cur > (quantity - 4)))
    {
        for (int i = 1; i <= quantity; ++i)
        {
            arr[i-1] = i;
        }
    }
}

void input(int& quantity, int& cur)
{
    cout << endl << "Enter the quantity of pages: ";
    cin >> quantity;
    while (quantity < 1)
    {
        cin.clear();
        cin.sync();
        cout << "Incorrect input!" << endl << "Enter the quantity of pages: ";
        cin >> quantity;
    }
    cout << "Enter the current page: ";
    cin >> cur;
    while ((cur < 1) || (cur > quantity))
    {
        cin.clear();
        cin.sync();
        cout << "Incorrect input!" << endl << "Enter the current page: ";
        cin >> cur;
    }
}

void output(const int& cur, const int* arr)
{
    cout << "Output: " << endl;
    for (int i = 0; i < 9; ++i)
    {
       	if (arr[i] == 0)
       		continue;
		if (arr[i] == -1)
        {	
			cout << ".. ";
		}
        else
		{
			if (arr[i] == cur)
			{	
				cout << "[" << arr[i] << "] ";
			}
			else
			{
				cout << arr[i] << " ";
			}
		}
    }
    cout << endl;
}

int main()
{
    cout << "Hello! ";
    char again;
    do
    {
        int quantity = 0;
        int cur = 0;
        int* arr = new int[9];
        for (int i = 0; i < 9; ++i)
        {
        	arr[i] = 0;
        }
        input(quantity, cur);
        paging(quantity, cur, arr);
        output(cur, arr);
        again = 'n';
        cout << "Do you want to try again? (y/n): ";
        cin >> again;
    } while ((again == 'y') || (again == 'Y'));
}
