Programming Project 1.

You are to implement an event counter using red-black tree. Each event has two fields: ID and count, where count is the number of active events with the given ID. The event counter stores only those ID’s whose count is > 0. Once a count drops below 1, that ID is removed. Initially, your program must build red-black tree from a sorted list of n events (i.e., n pairs (ID, count) in ascending order of ID) in O(n) time. Your counter should support the following operations in the specified time complexity. You are not allowed to use TreeMap in Java and std::map in C++.
