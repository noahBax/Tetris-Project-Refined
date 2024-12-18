#ifndef AI_CONFIGURATION
#define AI_CONFIGURATION

#include <random>
#include <array>

class AI_Configuration {

private:
	void alterGeneByIndex(const int index, const double newValue);
	void randomizeRandomGene(std::mt19937 &generator, const double weightSize);
	double getGeneValueByIndex(const int index) const;

public:
	double crackiness;
	double coveredHoles;
	double wellDepth;
	double aggregateHeight;
	double linesCleared;
	double bumpiness;
	double highestBlock;
	double scoreValue;
	double averageColumnLoad;
	double wellExponent;
	double rightColumn;
	double crackinessExponent;
	double coveredExponent;
	double movedDown;
	double scoreExponent;
	double iPenalty;

	std::array<double, 7> pieceLevels;

	std::array<double, 7> pieceDifferenceMultipliers;

	// Treat clear scores are 1-indexed
	std::array<double, 4> clearScores;

	static const int sGenomeSize = 34;

	AI_Configuration();
		
	void crossover(AI_Configuration &parent1, AI_Configuration &parent2);
	void initialize(const double weightSize, std::mt19937 &generator);
	std::string displayConfig() const;
	int applyMutation(const int mutationRate, const double weightSize, std::mt19937 &generator);

};

#endif // AI_CONFIGURATION