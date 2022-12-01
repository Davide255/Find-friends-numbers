#include <iostream>
#include <signal.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <ctime>

#ifdef _WIN32
bool Windows = true;
#include <Windows.h>
#else 
bool Windows = false;
#endif

bool RUNNING = true;
std::vector<int> PrimeNumbers = { 2, };
std::vector<std::vector<int>> solutions = {};
std::chrono::time_point<std::chrono::system_clock> start, end;

int _divs_sum(int n) {
    int _sum = 0;
    int _sqrt = (int)std::round(sqrt(n));

    if (_sqrt > 2) {
        bool prime = true;

        for (int _i = 0; _i < PrimeNumbers.size(); _i++) {
            if (PrimeNumbers[_i] > _sqrt) { prime = true; break; }
            if (n % PrimeNumbers[_i] == 0) { prime = false; break; }
        }

        if (prime) {

            bool found = false;
            for (int _i = 0; _i < PrimeNumbers.size(); _i++) {
                if (PrimeNumbers[_i] == n) found = true;
            }

            if (!found) PrimeNumbers.push_back(n);

            return 1;
        }
    }

    for (int _i = 0; _i <= n/2; _i++) {
        if (_i != 0 && n % _i == 0) _sum += _i;
    }

    return _sum;
}

bool friends(int n1, int n2){
    if (_divs_sum(n1) == n2) return true;
    else return false;
}

void t_end() {
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Elapsed time : " << elapsed_seconds.count() << "s\n";
}

void pprint(std::vector<int> vector, int max_cols = 7) {
    std::cout << "[ ";

    int col = 0;

    for (int i = 0; i < vector.size(); i++) {
        if (col == 0) std::cout << "  ";
        std::cout << vector[i];
        col++;
        if (col == max_cols) { std::cout << "\n"; col = 0; }
    }

    std::cout << "]\n";
}

void pprint(std::vector<std::vector<int>> vector, int max_cols = 3) {

    std::cout << "\nSolutions are:\n{\n";

    int col = 0;

    for (int i = 0; i < vector.size(); i++) {

        std::vector<int> list = vector.at(i);

        if (col == 0) std::cout << "   ";

        if (list.size() == 1) std::cout << "[" << list[0] << "], ";
        else std::cout << "[" << list[0] << ", " << list[1] << "], ";
        col ++;

        if (col == max_cols) { std::cout << "\n"; col = 0; }
    }

    std::cout << "\n}" << std::endl;
}

int main()
{
    start = std::chrono::system_clock::now();

    if (Windows) SetConsoleTitle(L"Friends Numbers");
    std::cout << "This program should find all perfect numbers and all friends number!\n\n";

    signal(SIGINT, [](int s) { RUNNING = false;});
    
    int i = 0;

    while (RUNNING) {
        i += 1;
        int s = _divs_sum(i);
        if (_divs_sum(s) == i) {
            if (s != i && i < s) {
                std::cout << s << " " << i << " amici\n";
                std::vector<int> data = { s, i };
                solutions.push_back(data);
            }
            else if (s == i)
            {
                std::cout << s << " Perfetto\n";
                std::vector<int> data = { s };
                solutions.push_back(data);
            }
        }
    }

    pprint(solutions);

    t_end();
    system("pause");
    return 0;
}
