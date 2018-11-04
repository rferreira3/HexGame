//creating a disjoint
#ifndef DISJOINT_SET_DEFINED
#define DISJOINT_SET_DEFINED
#include <iostream>
#include <array>
#include <unordered_set>

// Maintains a disjoint set of equivalence classes
// The N parameter is a compile-time constant that
// that specifies the number of sets.
//auto foo = DisjointSet<5>()
template <int N>
class DisjointSet {
	// 1. Add private data (including an array of size N) to
	//    maintain the state of the disjoint set
private:
	int Set[N]; //array of size N 
	//vector<int> Set(N, -1);
	//int numSets;
	// 2. Need a constructor
public:
	DisjointSet() { 
		for (int i = 0; i < N; i++)
		{
			Set[i] = i;
		}
	};

	//DisjointSet() { /*Make_Set();*/ }; //constrsuctor

	// 3. Add a method to make a set
	void Make_Set(int i) {

			Set[i] = i;
	}
	// 4. Add a find method
	int Find(int i) //using path compression ... shortens the size 
	{
		if (Set[i] == -1)
		{
			return i;
		}
		if (Set[i] != i)
		{
			Set[i] = Find(Set[i]);
			
		}

	}
	// 5. Add a union (I called mine merge) method
	void Union(int s1, int s2)
	{
		int p1 = Find(s1);
		int	p2 = Find(s2);
		Set[p1] = p2;
	}

	// 6. Add a method that returns the number of equivalence classes
	int euqiv()
	{
		int count = 0;
		std::unordered_set<int> temp;
		for (int i = 0; i <= N; i++)
		{
			temp.insert(Set[i]);
		}
		return temp.size();
		//code how many seperate sets there is 
	}
	// 7. Add a method that splits all the equivalence classes into
	  //  sets containing just one element
	void split()
	{
		for (int i = 0; i <= N; i++)
			if (Find(i) != i)
			{
				Set[i] = i;
			}
	}

};

#endif

