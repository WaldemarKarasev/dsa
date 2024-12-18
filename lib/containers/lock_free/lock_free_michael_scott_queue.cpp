// #include <atomic>
// #include <iostream>
// #include <optional>

// namespace lockfree {
    
// // Michael-Scott unbound lock-free queue
// // https://www.cs.rochester.edu/~scott/papers/1996_PODC_queues.pdf

// // Queue: dummy-> node1 -> node2 -> node3
// // head_ -> dummy
// // tail_ -> node3

// template <typename T>
// class MSQueue
// {
//     struct Node 
//     {
//         std::optional<T> value;
//         std::atomic<Node*> next{nullptr};
//     };

// public:
//     MSQueue()
//     {
//         Node* dummy = new Node();
//         head_.store(dummy);
//         tail_.store(dummy);
//     }

//     ~MSQueue()
//     {
//         DeleteList(head_load());
//     }

//     void Push(T value)
//     {
//         Node* new_node = new Node(std::move(value));


//         Node* curr_tail;

//         // Step 1
//         while (true)
//         {
//             curr_tail = tail_.load();

//             if (curr_tail->next != nullptr)
//             {
//                 // Concurrent Push in process

//                 // Helping
//                 if (tail_.compare_exchange_weak(curr_tail, curr_tail->next))
//                 {
//                     continue;
//                 }
//             }

//             Node* null_ptr = nullptr;
//             if (curr_tail->next.compare_exchange_weak(null_ptr, new_node))
//             {
//                 break;
//             }
//         }

//         // Step 2

//         // tail_.store(new_node);
//         tail_.compare_exchange_strong(curr_tail, new_node);
//     }

//     std::optional TryPop()
//     {
//         // Similar to TryPop in Treiber Stack
//         while (true)
//         {
//             Node* curr_head = head_.load();

//             if (curr_head->next == nullptr)
//             {
//                 return std::nullopt; // Empty queue
//             }

//             if (head_.compare_exchange_weak(curr_head, curr_head->next))
//             {
//                 Node* next_head = curr_head->next;
//                 T value = std::move(*(next_head->value));
//                 // delete curr_head
//                 return value;
//             }
//         }
        
//         return std::nullopt;
//     }

// private:
//     std::atomic<Node*> head_;
//     std::atomic<Node*> tail_;
// };

// }




// #include <vector>
// #include <string>
// int main()
// {

//     std::atomic<int> a = 2;

//     std::cout << a << std::endl;

//     int new_v = 5;
//     int prev_v = a.load();

//     std::cout << "res = " << a.compare_exchange_weak(prev_v, new_v) << std::endl;

//     std::cout << a << std::endl;
// }