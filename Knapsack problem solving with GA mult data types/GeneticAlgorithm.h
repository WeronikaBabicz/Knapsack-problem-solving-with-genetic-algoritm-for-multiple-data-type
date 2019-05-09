#pragma once
#include "KnapsackProblem.h"
#include "Individual.h"
#include <vector>
#include <random>
#include <string>
#include <time.h>

using namespace std;

const string BEST_GENOTYPE = "Best genotype: ";
const string FITNESS = "  Fitness: ";
const string SIZE = "  Size: ";
const string SECOND_BEST = "Second best genotype: ";

const int DEFAULT_POPULATION_SIZE = 10;
const int DEFAULT_GENERATIONS = 10;
const double DEFAULT_TIME_TO_STOP = 30;
const double DEFAULT_CROSSOVER_PROB = 0.3;
const double DEFAULT_MUTATION_PROB = 0.2;


template <class T>
class GeneticAlgorithm
{

public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	void run();

	bool setPopulationSize(int populationSize);
	bool setCrossoverProb(double dCrossoverProb);
	bool setMutationProb(double dMutationProb);
	bool setGenerations(int iGenerations);
	bool setTimeToStop(double dTimeToStop);
	bool setKnapsackProblem(KnapsackProblem<T> *cKnapsackProblem);

	vector<T> getBestIndividualGenotype();
	vector<T> getSecondBestIndividualGenotype();

	void deletePopulation();
	void setTwoDefaultBests();

private:
	mt19937 gen; //Standard mersenne_twister_engine seeded with rd()

	int getBetterIndividualIndex(int indexOfFirstIndividual, int indexOfSecondIndividual);
	void findAndSetBestIndividual();
	void generatePopulation();

	time_t timer;
	double startTime;
	double timeToStop;

	int populationSize;
	double crossoverProbability;
	double mutationProbability;
	int numberOfGenerations;
	vector <Individual<T>*> population;
	KnapsackProblem<T> *knapsackProblem;
	Individual<T> bestIndividual;
	Individual<T> secondBestIndividual;
};



//================================================================ .cpp ===============================================================



template <class T>
GeneticAlgorithm<T>::GeneticAlgorithm()
{
	random_device rd;
	mt19937 generator(rd());
	gen = generator;
	populationSize = DEFAULT_POPULATION_SIZE;
	numberOfGenerations = DEFAULT_GENERATIONS;
	timeToStop = DEFAULT_TIME_TO_STOP;
	crossoverProbability = DEFAULT_CROSSOVER_PROB;
	mutationProbability = DEFAULT_MUTATION_PROB;
	knapsackProblem = nullptr;
}

template <class T>
GeneticAlgorithm<T>::~GeneticAlgorithm()
{
}

template <class T>
void GeneticAlgorithm<T>::run()
{
	startTime = time(0);
	generatePopulation();
	findAndSetBestIndividual();
	while (difftime(time(0), startTime) < timeToStop)
	{
		vector <Individual<T>*> newPopulation;

		uniform_int_distribution <> dis(0, population.size() - 1);

		while (newPopulation.size() < populationSize - 2)
		{
			int parentIndex1 = getBetterIndividualIndex(dis(gen), dis(gen));
			int parentIndex2 = getBetterIndividualIndex(dis(gen), dis(gen));
			int parentIndex3 = getBetterIndividualIndex(dis(gen), dis(gen));
			int parentIndex4 = getBetterIndividualIndex(dis(gen), dis(gen));

			newPopulation.push_back(*population.at(parentIndex1) + population.at(parentIndex2));
			newPopulation.push_back(*population.at(parentIndex3) + population.at(parentIndex4));

		}

		Individual<T> *bestInCurrentGeneration = new Individual<T>();
		Individual<T> *secondBestInCurrentGeneration = new Individual<T>();

		bestInCurrentGeneration->setGenotype(bestIndividual.getGenotype());
		secondBestInCurrentGeneration->setGenotype(secondBestIndividual.getGenotype());

		bestInCurrentGeneration->setKnapsachProblem(knapsackProblem);
		secondBestInCurrentGeneration->setKnapsachProblem(knapsackProblem);

		newPopulation.push_back(bestInCurrentGeneration);
		newPopulation.push_back(secondBestInCurrentGeneration);

		for (int j = 0; j < populationSize; j++)
		{
			(*newPopulation.at(j))++; 
		}

		deletePopulation();

		population = newPopulation;
		findAndSetBestIndividual();
	}
	deletePopulation();
}

template <class T>
bool GeneticAlgorithm<T>::setPopulationSize(int populationSize)
{
	if (populationSize > 1)
	{
		this->populationSize = populationSize;
		return true;
	}
	else return false;

}

template <class T>
bool GeneticAlgorithm<T>::setCrossoverProb(double crossoverProbability)
{
	if (crossoverProbability >= 0 && crossoverProbability <= 1)
	{
		this->crossoverProbability = crossoverProbability;
		return true;
	}
	else return false;
}

template <class T>
bool GeneticAlgorithm<T>::setMutationProb(double mutationProbability)
{
	if (mutationProbability >= 0 && mutationProbability <= 1)
	{
		this->mutationProbability = mutationProbability;
		return true;
	}
	else return false;
}

template <class T>
bool GeneticAlgorithm<T>::setGenerations(int numberOfGenerations)
{
	if (numberOfGenerations > 0)
	{
		this->numberOfGenerations = numberOfGenerations;
		return true;
	}
	else return false;

}

template<class T>
inline bool GeneticAlgorithm<T>::setTimeToStop(double timeToStop)
{
	if (timeToStop > 0)
	{
		this->timeToStop = timeToStop;
		return true;
	}
	else return false;
}

template <class T>
bool GeneticAlgorithm<T>::setKnapsackProblem(KnapsackProblem<T> * knapsackProblem)
{
	if (knapsackProblem != nullptr)
	{
		this->knapsackProblem = knapsackProblem;
		return true;
	}
	else return false;
}

template <class T>
vector<T> GeneticAlgorithm<T>::getBestIndividualGenotype()
{
	return bestIndividual.getGenotype();
}

template <class T>
vector<T> GeneticAlgorithm<T>::getSecondBestIndividualGenotype()
{
	return secondBestIndividual.getGenotype();
}

template <class T>
void GeneticAlgorithm<T>::deletePopulation()
{
	for (int i = 0; i < population.size(); i++)
	{
		delete population.at(i);
	}
}

template <class T>
void GeneticAlgorithm<T>::setTwoDefaultBests()
{
	if (population.at(0)->getFitness() > population.at(1)->getFitness())
	{
		bestIndividual = *population.at(0);
		secondBestIndividual = *population.at(1);
	}
	else
	{
		bestIndividual = *population.at(1);
		secondBestIndividual = *population.at(0);
	}
}

template <class T>
int GeneticAlgorithm<T>::getBetterIndividualIndex(int indexOfFirst, int indexOfSecond)
{
	if (population.at(indexOfFirst)->getFitness() < population.at(indexOfSecond)->getFitness())
	{
		return indexOfSecond;
	}
	else return indexOfFirst;
}

template <class T>
void GeneticAlgorithm<T>::findAndSetBestIndividual()
{
	int bestDefaultIndividualIndex = 0;
	double bestDefaultIndividualFitness = population.at(bestDefaultIndividualIndex)->getFitness();
	for (int i = 0; i < populationSize; i++)
	{
		if (population.at(i)->getFitness() > bestDefaultIndividualFitness)
		{
			bestDefaultIndividualIndex = i;
			bestDefaultIndividualFitness = population.at(i)->getFitness();
		}
	}
	if (bestDefaultIndividualFitness > bestIndividual.getFitness())
	{
		secondBestIndividual = bestIndividual;
		bestIndividual = *population.at(bestDefaultIndividualIndex);
	}


	for (int i = 0; i < getBestIndividualGenotype().size(); i++)
	{
		cout << " [" << getBestIndividualGenotype().at(i) << "] ";
	}
	cout << FITNESS << bestIndividual.getFitness();
	cout << SIZE << bestIndividual.getSize() << endl;
}

template <class T>
void GeneticAlgorithm<T>::generatePopulation()
{
	uniform_int_distribution <> dis(0, 1);
	for (int i = 0; i < populationSize; i++)
	{
		Individual<T> *newIndividual = new Individual<T>();
		vector <T> genotype;
		for (int j = 0; j < knapsackProblem->getItemsSizes(); j++)
		{
			genotype.push_back(dis(gen));
		}
		newIndividual->setGenotype(genotype);
		newIndividual->setKnapsachProblem(knapsackProblem);
		newIndividual->setCrossoverProb(crossoverProbability);
		newIndividual->setMutationProb(mutationProbability);
		population.push_back(newIndividual);
	}
	setTwoDefaultBests();
}

template<>
void GeneticAlgorithm<int>::generatePopulation()
{
	uniform_int_distribution <> dis(0, MAX_I_ITEMS);
	for (int i = 0; i < populationSize; i++)
	{
		Individual<int> *newIndividual = new Individual<int>();
		vector <int> vGenotype;
		for (int j = 0; j < knapsackProblem->getItemsSizes(); j++)
		{
			vGenotype.push_back(dis(gen));
		}
		newIndividual->setGenotype(vGenotype);
		newIndividual->setKnapsachProblem(knapsackProblem);
		population.push_back(newIndividual);
	}
	setTwoDefaultBests();
}
template<>
void GeneticAlgorithm<double>::generatePopulation()
{
	uniform_real_distribution <> dis(0, MAX_D_ITEMS);
	for (int i = 0; i < populationSize; i++)
	{
		Individual<double> *cNewIndividual = new Individual<double>();
		vector <double> vGenotype;
		for (int j = 0; j < knapsackProblem->getItemsSizes(); j++)
		{
			vGenotype.push_back(dis(gen));
		}
		cNewIndividual->setGenotype(vGenotype);
		cNewIndividual->setKnapsachProblem(knapsackProblem);
		population.push_back(cNewIndividual);
	}
	setTwoDefaultBests();
}



