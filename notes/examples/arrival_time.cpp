#include <iostream>
#include <iomanip>

int main()
{
    int dep_h, dep_m;
    scanf("%d:%d", &dep_h, &dep_m);

    int arr_h, arr_m;
    scanf("%d:%d", &arr_h, &arr_m);

    int dep_t = dep_h * 60 + dep_m;
    int arr_t = arr_h * 60 + arr_m;

    int sum = arr_t + dep_t;
    int diff_h = (sum / 60 % 24);
    int diff_m = sum % 60;

    std::cout << std::setfill('0') << std::setw(2) << diff_h << ":" 
    << std::setfill('0') << std::setw(2) << diff_m << std::endl;

}
