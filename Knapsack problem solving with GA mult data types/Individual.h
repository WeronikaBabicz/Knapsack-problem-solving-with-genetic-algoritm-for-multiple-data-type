#pragma once

#include <vector>
#include <random>
#include "KnapsackProblem.h"
#include <iostream>


using namespace std;

const int MAX_I_ITEMS = 3;
const double MAX_D_ITEMS = 5;


template <class T>
class Individual
{
public:
	Individual();
	~Individual();

	double getFitness();
	double getSize();
	void mutate();
	Individual<T>* crossover(Individual<T> *individualOther);
	bool setMutationProb(double mutationProbability);
	bool setCrossoverProb(double crossoverProbability);
	vector<T> getGenotype() { return genotype; };
	void setGenotype(vector <T> genotype);
	void setKnapsachProblem(KnapsackProblem<T> *knapsackProblem);

	void operator++(int);
	Individual<T>* operator+(Individual<T> *individualOther);


private:
	double crossoverProbability;
	double mutationProbability;
	mt19937 gen;
	vector<T> genotype;
	KnapsackProblem<T> *knapsackProblem;
};



//================================================================ .cpp ===============================================================



template <class T>
Individual<T>::Individual()
{
	random_device rd;
	mt19937 generator(rd());
	gen = generator;
	knapsackProblem = nullptr;
}

template <class T>
Individual<T>::~Individual()
{
}

template <class T>
double Individual<T>::getFitness()
{
	return knapsackProblem->getFitness(genotype);
}

template <class T>
double Individual<T>::getSize()
{
	return knapsackProblem->getSize();
}



template <class T>
void Individual<T>::mutate()
{
	uniform_real_distribution<> dis(0, 1);
	for (int i = 0; i < genotype.size(); i++)
	{
		if (dis(gen) <= mutationProbability)
		{
			if (genotype.at(i) == 0) genotype.at(i) = 1;
			else genotype.at(i) = 0;
		}
	}
}

template <>
void Individual<int>::mutate()
{
	uniform_int_distribution<> disi(0, MAX_I_ITEMS);
	uniform_real_distribution<> dis(0, 1);
	for (int i = 0; i < genotype.size(); i++)
	{
		if (dis(gen) <= mutationProbability)
		{
			genotype.at(i) = disi(gen);
		}
	}
}

template <>
void Individual<double>::mutate()
{
	uniform_real_distribution<> disd(0, MAX_D_ITEMS);
	uniform_real_distribution<> dis(0, 1);
	for (int i = 0; i < genotype.size(); i++)
	{
		if (dis(gen) <= mutationProbability)
		{
			genotype.at(i) = disd(gen);
		}
	}
}



template <class T>
Individual<T>* Individual<T>::crossover(Individual<T> *individualOther)
{
	uniform_int_distribution<> dis(1, genotype.size() - 1);
	uniform_real_distribution<> disreal(0, 1);
	Individual<T> *newIndividual = new Individual<T>();
	if (disreal(gen) <= crossoverProbability)
	{
		int crossoverPoint = dis(gen);
		vector <T> firstGenotype;
		//vector <T> secondGenotype;

		for (int i = 0; i < crossoverPoint; i++)
		{
			firstGenotype.push_back(genotype.at(i));
			//secondGenotype.push_back(individualOther.genotype.at(i));
		}
		for (int i = crossoverPoint; i < genotype.size(); i++)
		{
			firstGenotype.push_back(individualOther->genotype.at(i));
			//secondGenotype.push_back(genotype.at(i));
		}

		newIndividual->setGenotype(firstGenotype);
		newIndividual->setKnapsachProblem(knapsackProblem);
		newIndividual->setCrossoverProb(crossoverProbability);
		newIndividual->setMutationProb(mutationProbability);



	}
	else
	{
		newIndividual->setGenotype(getGenotype());
		newIndividual->setKnapsachProblem(knapsackProblem);
		newIndividual->setCrossoverProb(crossoverProbability);
		newIndividual->setMutationProb(mutationProbability);

	}
	return newIndividual;
}

template<class T>
bool Individual<T>::setMutationProb(double mutationProbability)
{
	if (mutationProbability <= 0 && mutationProbability >= 1)
	{
		this->mutationProbability = mutationProbability;
		return true;
	}
	else return false;
}

template<class T>
bool Individual<T>::setCrossoverProb(double crossoverProbability)
{
	if (crossoverProbability >= 0 && crossoverProbability <= 1)
	{
		this->crossoverProbability = crossoverProbability;
		return true;
	}
	return false;
}

template <class T>
void Individual<T>::setGenotype(vector<T> genotype)
{
	this->genotype = genotype;
}

template <class T>
void Individual<T>::setKnapsachProblem(KnapsackProblem<T> * knapsackProblem)
{
	this->knapsackProblem = knapsackProblem;
}

template<class T>
void Individual<T>::operator++(int)
{
	mutate();
}

template<class T>
Individual<T>* Individual<T>::operator+(Individual<T> *individualOther)
{
	return crossover(individualOther);
}



