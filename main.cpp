#include <iostream>
using namespace std;

struct Data // Data format
{
    int happy_id;
    int bored_id;
    int cost;
};

class Playground // Main Class
{
private:
    int num_toys;
    int max_coins;

public:
    Data *detail_arr; // Pointer where the data will be located
    int **R; // R table from Knapsnack algorithm

    Playground(int toys); // Constructor

    void knapsnack01(); // Main algorithm

    int calculate_happiness(int num_times, int happiness_id, int bored_id); // Special case

    void setValues(int happy, int bored, int cost, int line);

    void setR(int my_max_coins);
};

Playground ::Playground(int toys)
{
    detail_arr = new Data[toys]; // Details
    num_toys = toys;
}

void Playground ::setValues(int happy, int bored, int cost, int line)
{
    detail_arr[line].happy_id = happy; // Set values in the Data table
    detail_arr[line].bored_id = bored;
    detail_arr[line].cost = cost;
}

void Playground ::setR(int my_max_coins)
{ // creates the table R
    max_coins = my_max_coins;
    R = new int *[num_toys + 1]; // Creates the R table
    for (int i = 0; i < num_toys + 1; i++)
    {
        R[i] = new int[max_coins + 1];
        R[i][0] = 0;
    }
    for (int i = 0; i < max_coins + 1; i++)
    {
        R[0][i] = 0;
    }

    knapsnack01(); // Starts the Knapsnack 
}

int Playground ::calculate_happiness(int num_times, int happiness_id, int bored_id)
{
    int aux = ((num_times -1)*(num_times-1));
    int answer = happiness_id - aux*bored_id; // In case the kid chooses the same toy

    if (answer < 0)
    {
        answer = -1;
    }
    return answer;
}

void Playground ::knapsnack01()
{
    int weight, happy, num_times, bored, temp_value;

    for (int i = 1; i <= num_toys; i++)
    {
        for (int j = 1; j <= max_coins; j++)
        {
            R[i][j] = R[i - 1][j]; // Gets the past value
            weight = detail_arr[i - 1].cost; // Gets the details from the Data table
            happy = detail_arr[i - 1].happy_id;
            bored = detail_arr[i - 1].bored_id;

            num_times = j / weight; // The number of times it is possible to repeat the same toy
            int total_value = 0;
            for (int m = 1; m <= num_times; m++)
            {
                temp_value = calculate_happiness(m, happy, bored);  // Gets each value from each time 
                // The kid uses the toy
                total_value += temp_value; // Sums up the past value
                
                if (temp_value == -1) // In case the total value does not increase
                {
                    break;
                }
                
                if (total_value + R[i - 1][j - m*weight] > R[i][j] && weight <= j)
                {
                    R[i][j] = total_value + R[i - 1][j - m*weight]; // Knapsnack logic
                }
            }
        }
    }
}

int main()
{
    int num_toys, cost, happy, bored, values, credits;

    cin >> num_toys;
    Playground playground(num_toys); // Creates the class
    for (int i = 0; i < num_toys; i++)
    {
        cin >> happy;
        cin >> bored;
        cin >> cost;
        playground.setValues(happy, bored, cost, i); // Put the values inside the Data table
    }
    cin >> values;
    int credit_arr[values]; // Storages the credits inside the credit_array
    int max_credit = 0;
    for (int i = 0; i < values; i++)
    {
        cin >> credits;
        credit_arr[i] = credits;
        if (credits > max_credit) // Gets the maximum value
        {
            max_credit = credits;
        }
    }
    playground.setR(max_credit); // Creates the table based on the largest credit
    
    for (int i = 0; i < values; i++){
        cout << i << ": "<<playground.R[num_toys][credit_arr[i]] << endl; // Accsses the R table
        // In order to get the input credits
    }
    
    return 0;
}
