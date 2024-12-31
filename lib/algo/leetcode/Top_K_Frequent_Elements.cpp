#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> map;

        std::for_each(nums.begin(), nums.end(), [&map](int i) {
            map[i]++;
        });

        std::priority_queue<std::pair<int, int>> pq;
        for_each(map.begin(), map.end(), [&pq](auto elem) {
            pq.push({elem.second, elem.first});
        });

        std::vector<int> result;

        while(k > 0) {
            result.push_back(pq.top().second);
            pq.pop();
            --k;
        }

        return result;
    }
};


#include <queue>
int main() 
{
   
    //vec result = Top_K_Frequent_Elements(input, k);

    std::priority_queue<std::pair<int, int>> q;
    q.push({3,32});
    q.push({30,-1});
    q.push({-2,-1});
    q.push({2,12123});
    q.push({2,-12323});

    while (!q.empty())
    {
        std::cout << q.top().first << " " << q.top().second << std::endl;
        q.pop();
    }
    

}