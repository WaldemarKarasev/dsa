#include <iostream>
#include <vector>

int main()
{
	std::vector<int> arr = {99, 4, 2, 13, 34, 423, 33, 2, 1};

	int max =  0;

	for(int i = 0; i < arr.size(); i++)
	{
		//res = arr[i];
		if(max < arr[i]) max = arr[i];

		//std::cout << arr[i] << " ";
	}

	std::cout << "\n";	
	std::cout << "res = " << max << std::endl;
}
