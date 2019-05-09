#pragma once
#include <vector>

using namespace std;

const int DEFAULT_CAPACITY = 10;

template <class T>
class KnapsackProblem
{
public:
	KnapsackProblem();
	~KnapsackProblem();

	bool setCapacity(double capacity);
	bool setItemsSizes(vector <double> *itemsSizes);
	bool setItemsValues(vector <double> *itemsValues);
	double getFitness(vector<T> &genotype);
	int getItemsSizes();
	double getSize();

private:
	double capacity;
	vector <double> *itemsSizes;
	vector <double> *itemsValues;
	double sizeOfAllItems;
};



//================================================================ .cpp ===============================================================



template <class T>
KnapsackProblem<T>::KnapsackProblem()
{
	capacity = DEFAULT_CAPACITY;
	itemsSizes = nullptr;
	itemsValues = nullptr;
}

template <class T>
KnapsackProblem<T>::~KnapsackProblem()
{
}

template <class T>
bool KnapsackProblem<T>::setCapacity(double capacity)
{
	if (capacity > 0)
	{
		this->capacity = capacity;
		return true;
	}
	else return false;
}

template <class T>
bool KnapsackProblem<T>::setItemsSizes(vector<double> *itemsSizes)
{
	if (itemsSizes != nullptr)
	{
		this->itemsSizes = itemsSizes;
		return true;
	}
	else return false;
}

template <class T>
bool KnapsackProblem<T>::setItemsValues(vector<double> *itemsValues)
{
	if (itemsValues != nullptr)
	{
		this->itemsValues = itemsValues;
		return true;
	}
	else return false;
}

template <class T>
double KnapsackProblem<T>::getFitness(vector<T> &genotype)
{
	double fitness = 0;
	double size = 0;
	for (int i = 0; i < genotype.size() && size <= capacity; i++)
	{

		if (genotype.at(i) != 0)
		{
			fitness += genotype.at(i) * itemsValues->at(i);
			size += genotype.at(i) * itemsSizes->at(i);
		}
	}
	sizeOfAllItems = size;
	return size <= capacity ? fitness : 0;
}

template <class T>
int KnapsackProblem<T>::getItemsSizes()
{
	return itemsSizes != nullptr ? itemsSizes->size() : 0;
}

template <class T>
double KnapsackProblem<T>::getSize()
{
	return sizeOfAllItems;
}

