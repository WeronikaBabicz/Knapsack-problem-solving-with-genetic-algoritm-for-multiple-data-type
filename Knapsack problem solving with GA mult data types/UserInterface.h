#pragma once
#include "GeneticAlgorithm.h"
#include <string>
#include <iostream>

using namespace std;

const string ALL_OPERATIONS = "Enter operation:\n[1] Binary knapsack problem\n[2] Integer knapsack problem\n[3] Double knapsack problem\n[0] Exit\n";
const string DATA_OPERATIONS = "Enter items' data (sizes and values) you'd like to use:\n[1] Default data\n[2] Custom data\n";
const string OPERATION_NOT_FOUND_ERROR = "Operation not found!!! ";
const string ENTER_INTEGER = "Enter integer! ";
const string ENTER_DOUBLE = "Enter double! ";
const string ENTER_NUMBER_OF_ITEMS = "Enter number of items: ";
const string ENTER_STOPPING_CRIT = "Enter number of generations: ";
const string ENTER_TIME_TO_STOP = "Enter time (in seconds) after when simulation has to be stopped: ";
const string ENTER_MUTATION_PROB = "Set mutation probabilty: ";
const string ENTER_CROSSOVER_PROB = "Set crossover probability: ";
const string ENTER_POP_SIZE = "Enter population size: ";
const string ENTER_CAPACITY = "Enter capacity: ";
const string ENTER_PROB_VALUE = "Enter probability value [0;1]";
const string ENTER = "Enter ";
const string ITEMS_VAL = " item's value";
const string ITEMS_SIZE = " item's size";
const string SPACE = " ";

class UserInterface
{
public:
	UserInterface();

	void run();
	void getOperation();
	void getDataOperation();
	void setData();
	int getInt();
	double getDouble();
	double getProbability();
	void binaryProblem();
	void integerProblem();
	void doubleProblem();
	void deleteData();

	void enterCapacity();
	void enterPopulationSize();
	void enterCrossoverProb();
	void enterMutationProb();
	void enterGenerations();
	void enterTimestopCriteria();

	void setCapacity(int capacity);
	void setPopulationSize(int populationSize);
	void setCrossoverProb(double crossoverProbability);
	void setMutationProb(double mutationProbability);
	void setGenerations(int numberOfGenerations);
	void setTimestopCriteria(double timeToStop);

	void defaultData();
	void setNonDefaultData();




private:
	int operation;
	int capacity;
	int populationSize;
	double crossoverProbability;
	double mutationProbability;
	int numberOfGenerations;
	double timeToStop;
	vector <double>  itemsSizes;
	vector <double>  itemsValues;
};




//=============================================================== .cpp =============================================================================




UserInterface::UserInterface()
{

}

void UserInterface::run()
{
	getOperation();
	while (operation != 0)
	{
		switch (operation)
		{
		case 1:
			binaryProblem();
			break;
		case 2:
			integerProblem();
			break;
		case 3:
			doubleProblem();
			break;
		}
		deleteData();
		getOperation();
	}
}

void UserInterface::getOperation()
{
	cout << ALL_OPERATIONS << endl;
	operation = getInt();
	while ((operation > 3) || (operation < 0))
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << OPERATION_NOT_FOUND_ERROR << endl;
		cout << ALL_OPERATIONS << endl;
		operation = getInt();
	}
	cin.clear();
	cin.ignore();
}

void UserInterface::getDataOperation()
{
	cout << DATA_OPERATIONS << endl;
	operation = getInt();
	while ((operation > 2) || (operation < 1))
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << OPERATION_NOT_FOUND_ERROR << endl;
		cout << DATA_OPERATIONS << endl;
		operation = getInt();
	}
	cin.clear();
	cin.ignore();
}

void UserInterface::setData()
{
	getDataOperation();

	if (operation == 1)
	{
		defaultData();
	}
	if (operation == 2)
	{
		setNonDefaultData();
	}

	enterCapacity();
	enterPopulationSize();
	enterCrossoverProb();
	enterMutationProb();
	//enterGenerations();
	enterTimestopCriteria();
}

int UserInterface::getInt()
{
	int integer;
	cin >> integer;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << ENTER_INTEGER << endl;
		cin >> integer;
	}
	return integer;
}

double UserInterface::getDouble()
{
	double dDouble;
	cin >> dDouble;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << ENTER_DOUBLE << endl;
		cin >> dDouble;
	}
	return dDouble;
}

double UserInterface::getProbability()
{
	double probability = getDouble();
	while (probability < 0 || probability > 1)
	{
		cout << ENTER_PROB_VALUE << endl;
		probability = getDouble();
	}
	return probability;
}

void UserInterface::binaryProblem()
{
	KnapsackProblem<bool> knapsackProblem;
	GeneticAlgorithm<bool> geneticAlgorithm;
	vector<bool> bestGenotype;
	vector<bool> secondBestGenotype;

	setData();

	knapsackProblem.setCapacity(capacity);
	knapsackProblem.setItemsSizes(&itemsSizes);
	knapsackProblem.setItemsValues(&itemsValues);

	geneticAlgorithm.setCrossoverProb(crossoverProbability);
	geneticAlgorithm.setMutationProb(mutationProbability);
	geneticAlgorithm.setPopulationSize(populationSize);
	geneticAlgorithm.setKnapsackProblem(&knapsackProblem);
	geneticAlgorithm.setGenerations(numberOfGenerations);
	geneticAlgorithm.setTimeToStop(timeToStop);

	geneticAlgorithm.run();

	bestGenotype = geneticAlgorithm.getBestIndividualGenotype();
	secondBestGenotype = geneticAlgorithm.getSecondBestIndividualGenotype();

	cout << endl << BEST_GENOTYPE;
	for (int i = 0; i < bestGenotype.size(); i++)
	{
		cout << bestGenotype.at(i) << SPACE;
	}
	cout << endl << SECOND_BEST;
	for (int i = 0; i < secondBestGenotype.size(); i++)
	{
		cout << secondBestGenotype.at(i) << SPACE;
	}
	cout << endl << endl;
}

void UserInterface::integerProblem()
{
	KnapsackProblem<int> knapsackProblem;
	GeneticAlgorithm<int> geneticAlgorithm;
	vector<int> bestGenotype;
	vector<int> secondBestGenotype;

	setData();

	knapsackProblem.setCapacity(capacity);
	knapsackProblem.setItemsSizes(&itemsSizes);
	knapsackProblem.setItemsValues(&itemsValues);

	geneticAlgorithm.setCrossoverProb(crossoverProbability);
	geneticAlgorithm.setMutationProb(mutationProbability);
	geneticAlgorithm.setPopulationSize(populationSize);
	geneticAlgorithm.setKnapsackProblem(&knapsackProblem);
	geneticAlgorithm.setGenerations(numberOfGenerations);
	geneticAlgorithm.setTimeToStop(timeToStop);

	geneticAlgorithm.run();

	bestGenotype = geneticAlgorithm.getBestIndividualGenotype();
	secondBestGenotype = geneticAlgorithm.getSecondBestIndividualGenotype();

	cout << endl << BEST_GENOTYPE;
	for (int i = 0; i < bestGenotype.size(); i++)
	{
		cout << bestGenotype.at(i) << SPACE;
	}
	cout << endl << endl << SECOND_BEST;
	for (int i = 0; i < secondBestGenotype.size(); i++)
	{
		cout << secondBestGenotype.at(i) << SPACE;
	}
	cout << endl;
}

void UserInterface::doubleProblem()
{
	KnapsackProblem<double> knapsackProblem;
	GeneticAlgorithm<double> geneticAlgorithm;
	vector<double> bestGenotype;
	vector<double> secondBestGenotype;

	setData();

	knapsackProblem.setCapacity(capacity);
	knapsackProblem.setItemsSizes(&itemsSizes);
	knapsackProblem.setItemsValues(&itemsValues);

	geneticAlgorithm.setCrossoverProb(crossoverProbability);
	geneticAlgorithm.setMutationProb(mutationProbability);
	geneticAlgorithm.setPopulationSize(populationSize);
	geneticAlgorithm.setKnapsackProblem(&knapsackProblem);
	geneticAlgorithm.setGenerations(numberOfGenerations);
	geneticAlgorithm.setTimeToStop(timeToStop);

	geneticAlgorithm.run();

	bestGenotype = geneticAlgorithm.getBestIndividualGenotype();
	secondBestGenotype = geneticAlgorithm.getSecondBestIndividualGenotype();

	cout << endl << BEST_GENOTYPE;
	for (int i = 0; i < bestGenotype.size(); i++)
	{
		cout << bestGenotype.at(i) << SPACE;
	}
	cout << endl << endl << SECOND_BEST;
	for (int i = 0; i < secondBestGenotype.size(); i++)
	{
		cout << secondBestGenotype.at(i) << SPACE;
	}
	cout << endl;
}

inline void UserInterface::deleteData()
{

	itemsSizes.clear();
	itemsValues.clear();

}

void UserInterface::enterCapacity()
{
	cout << ENTER_CAPACITY << endl;
	int capacity = getInt();
	this->capacity = capacity;
	cout << endl;
}

inline void UserInterface::enterPopulationSize()
{
	cout << ENTER_POP_SIZE << endl;
	int populationSize = getInt();
	this->populationSize = populationSize;
	cout << endl;
}

void UserInterface::enterCrossoverProb()
{
	cout << ENTER_CROSSOVER_PROB << endl;
	double crossoverProbability = getProbability();
	this->crossoverProbability = crossoverProbability;
	cout << endl;
}

void UserInterface::enterMutationProb()
{
	cout << ENTER_MUTATION_PROB << endl;
	double mutationProbability = getProbability();
	this->mutationProbability = mutationProbability;
	cout << endl;
}

void UserInterface::enterGenerations()
{
	cout << ENTER_STOPPING_CRIT << endl;
	int numberOfGenerations = getInt();
	this->numberOfGenerations = numberOfGenerations;
	cout << endl;
}

inline void UserInterface::enterTimestopCriteria()
{
	cout << ENTER_TIME_TO_STOP << endl;
	double timeToStop = getDouble();
	this->timeToStop = timeToStop;
	cout << endl;
}

void UserInterface::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void UserInterface::setPopulationSize(int populationSize)
{
	this->populationSize = populationSize;
}

void UserInterface::setCrossoverProb(double crossoverProbability)
{
	this->crossoverProbability = crossoverProbability;
}

void UserInterface::setMutationProb(double mutationProbability)
{
	this->mutationProbability = mutationProbability;
}

void UserInterface::setGenerations(int numberOfGenerations)
{
	this->numberOfGenerations = numberOfGenerations;
}

void UserInterface::setTimestopCriteria(double timeToStop)
{
	this->timeToStop = timeToStop;
}

void UserInterface::defaultData()
{
	itemsValues.push_back(2);
	itemsValues.push_back(1);
	itemsValues.push_back(3);
	itemsValues.push_back(5);
	itemsValues.push_back(4);
	itemsValues.push_back(6);
	itemsValues.push_back(1);
	itemsValues.push_back(3);
	itemsValues.push_back(8);
	itemsValues.push_back(7);
	itemsValues.push_back(2);
	itemsValues.push_back(9);
	itemsValues.push_back(3);
	itemsValues.push_back(6);
	itemsValues.push_back(7);
	itemsValues.push_back(1);


	itemsSizes.push_back(2);
	itemsSizes.push_back(4);
	itemsSizes.push_back(1);
	itemsSizes.push_back(4);
	itemsSizes.push_back(8);
	itemsSizes.push_back(6);
	itemsSizes.push_back(2);
	itemsSizes.push_back(1);
	itemsSizes.push_back(5);
	itemsSizes.push_back(3);
	itemsSizes.push_back(4);
	itemsSizes.push_back(1);
	itemsSizes.push_back(7);
	itemsSizes.push_back(5);
	itemsSizes.push_back(2);


}

void UserInterface::setNonDefaultData()
{
	cout << ENTER_NUMBER_OF_ITEMS << endl;
	int numberOfItems = getInt();
	cout << endl;

	for (int i = 0; i < numberOfItems; i++)
	{
		cout << ENTER << i + 1 << ITEMS_VAL << endl;
		double itemValue = getDouble();
		itemsValues.push_back(itemValue);
		cout << ENTER << i + 1 << ITEMS_SIZE << endl;
		double itemSize = getDouble();
		itemsSizes.push_back(itemSize);
		cout << endl;
	}


}

