#include "ai_configuration.hpp"
#include <stdexcept>

void AI_Configuration::initialize(const double weightSize, const std::mt19937 &generator) {

	std::uniform_real_distribution<> distrLarge(-weightSize, weightSize);
    std::uniform_real_distribution<> distrSmall(-0.5, 5);
    std::uniform_real_distribution<> distrDiffs(0.0, 20.0);

	// Go through and assign random values

	crackiness = distrLarge(generator);
	coveredHoles = distrLarge(generator);
	wellDepth = distrLarge(generator);
	aggregateHeight = distrLarge(generator);
	linesCleared = distrLarge(generator);
	bumpiness = distrLarge(generator);
	highestBlock = distrLarge(generator);
	scoreValue = distrLarge(generator);
	averageColumnLoad = distrLarge(generator);
	rightColumn = distrLarge(generator);
	movedDown = distrLarge(generator);
	iPenalty = distrLarge(generator);

	wellExponent = distrSmall(generator);
	crackinessExponent = distrSmall(generator);
	coveredExponent = distrSmall(generator);
	scoreExponent = distrSmall(generator);

	for (int i = 0; i < pieceDifferenceMultipliers.size(); i++) {
		pieceDifferenceMultipliers[i] = distrLarge(generator);
	}

	for (int i = 0; i < pieceLevels.size(); i++) {
		pieceLevels[i] = distrLarge(generator);
	}

	for (int i = 0; i < clearScores.size(); i++) {
		clearScores[i] = distrLarge(generator);
	}

}

void AI_Configuration::crossover(const AI_Configuration &parent1, const AI_Configuration &parent2) {

	crackiness = (parent1.crackiness / 2.0 + parent2.crackiness / 2.0);
	coveredHoles = (parent1.coveredHoles / 2.0 + parent2.coveredHoles / 2.0);
	wellDepth = (parent1.wellDepth / 2.0 + parent2.wellDepth / 2.0);
	aggregateHeight = (parent1.aggregateHeight / 2.0 + parent2.aggregateHeight / 2.0);
	linesCleared = (parent1.linesCleared / 2.0 + parent2.linesCleared / 2.0);
	bumpiness = (parent1.bumpiness / 2.0 + parent2.bumpiness / 2.0);
	highestBlock = (parent1.highestBlock / 2.0 + parent2.highestBlock / 2.0);
	scoreValue = (parent1.scoreValue / 2.0 + parent2.scoreValue / 2.0);
	averageColumnLoad = (parent1.averageColumnLoad / 2.0 + parent2.averageColumnLoad / 2.0);
	wellExponent = (parent1.wellExponent / 2.0 + parent2.wellExponent / 2.0);
	rightColumn = (parent1.rightColumn / 2.0 + parent2.rightColumn / 2.0);
	crackinessExponent = (parent1.crackinessExponent / 2.0 + parent2.crackinessExponent / 2.0);
	coveredExponent = (parent1.coveredExponent / 2.0 + parent2.coveredExponent / 2.0);
	movedDown = (parent1.movedDown / 2.0 + parent2.movedDown / 2.0);
	scoreExponent = (parent1.scoreExponent / 2.0 + parent2.scoreExponent / 2.0);
	iPenalty = (parent1.iPenalty / 2.0 + parent2.iPenalty / 2.0);
	
	for (int i = 0; i < pieceDifferenceMultipliers.size(); i++) {
		pieceDifferenceMultipliers[i] = (parent1.pieceDifferenceMultipliers[i] + parent2.pieceDifferenceMultipliers[i]) / 2;
	}

	for (int i = 0; i < pieceLevels.size(); i++) {
		pieceLevels[i] = (parent1.pieceLevels[i] + parent2.pieceLevels[i]) / 2;
	}

	for (int i = 0; i < clearScores.size(); i++) {
		clearScores[i] = (parent1.clearScores[i] + parent2.clearScores[i]) / 2;
	}
	
}

int AI_Configuration::applyMutation(const int mutationRate, const double weightSize, const std::mt19937 &generator) {

	if (rand() % 100 > mutationRate) return 0;

	int mutationCount = 0;
	int mutationsLeft = (rand() % 4) + 2;

	while (mutationsLeft > 0) {
		if (rand() % 100 < 20) {
			// We do a swap between two random mutations here
			mutationCount += 2;
			mutationsLeft -= 2;

			// Pick 2 genes to swap
			int ind1 = rand() % AI_Configuration::sGenomeSize;
			int ind2 = rand() % AI_Configuration::sGenomeSize;

			// Swap
			double temp = getGeneValueByIndex(ind1);
			alterGeneByIndex(ind1, getGeneValueByIndex(ind2));
			alterGeneByIndex(ind2, temp);
		} else {
			mutationCount++;
			mutationsLeft--;

			randomizeRandomGene(generator, weightSize);
		}
	}

	return mutationCount;

}

AI_Configuration::AI_Configuration() {}

void AI_Configuration::alterGeneByIndex(const int index, const double newValue) {
	
	switch (index) {
		case 0:
			crackiness = newValue;
			break;
		case 1:
			coveredHoles = newValue;
			break;
		case 2:
			wellDepth = newValue;
			break;
		case 3:
			aggregateHeight = newValue;
			break;
		case 4:
			linesCleared = newValue;
			break;
		case 5:
			bumpiness = newValue;
			break;
		case 6:
			highestBlock = newValue;
			break;
		case 7:
			scoreValue = newValue;
			break;
		case 8:
			averageColumnLoad = newValue;
			break;
		case 9:
			wellExponent = newValue;
			break;
		case 10:
			rightColumn = newValue;
			break;
		case 11:
			crackinessExponent = newValue;
			break;
		case 12:
			coveredExponent = newValue;
			break;
		case 13:
			movedDown = newValue;
			break;
		case 14:
			scoreExponent = newValue;
			break;
		case 15:
			iPenalty = newValue;
			break;
		case 16:
			pieceLevels[0] = newValue;
			break;
		case 17:
			pieceLevels[1] = newValue;
			break;
		case 18:
			pieceLevels[2] = newValue;
			break;
		case 19:
			pieceLevels[3] = newValue;
			break;
		case 20:
			pieceLevels[4] = newValue;
			break;
		case 21:
			pieceLevels[5] = newValue;
			break;
		case 22:
			pieceLevels[6] = newValue;
			break;
		case 23:
			pieceDifferenceMultipliers[0] = newValue;
			break;
		case 24:
			pieceDifferenceMultipliers[1] = newValue;
			break;
		case 25:
			pieceDifferenceMultipliers[2] = newValue;
			break;
		case 26:
			pieceDifferenceMultipliers[3] = newValue;
			break;
		case 27:
			pieceDifferenceMultipliers[4] = newValue;
			break;
		case 28:
			pieceDifferenceMultipliers[5] = newValue;
			break;
		case 29:
			pieceDifferenceMultipliers[6] = newValue;
			break;
		case 30:
			clearScores[0] = newValue;
			break;
		case 31:
			clearScores[1] = newValue;
			break;
		case 32:
			clearScores[2] = newValue;
			break;
		case 33:
			clearScores[3] = newValue;
			break;
		default:
			throw std::invalid_argument("Index received for altering gene is invalid value");
	}
	
}

void AI_Configuration::randomizeRandomGene(const std::mt19937 &generator, const double weightSize) {

	// Pick a random weight to mutate
	int index = rand() % AI_Configuration::sGenomeSize;

	std::uniform_real_distribution<> distrLarge(-weightSize, weightSize);
	std::uniform_real_distribution<> distrSmall(-5.5, 5.5);
	std::uniform_real_distribution<> distrDiffs(0, 20.0);
	
	switch (index) {
		case 0:
			crackiness = distrLarge(generator);
			break;
		case 1:
			coveredHoles = distrLarge(generator);
			break;
		case 2:
			wellDepth = distrLarge(generator);
			break;
		case 3:
			aggregateHeight = distrLarge(generator);
			break;
		case 4:
			linesCleared = distrLarge(generator);
			break;
		case 5:
			bumpiness = distrLarge(generator);
			break;
		case 6:
			highestBlock = distrLarge(generator);
			break;
		case 7:
			scoreValue = distrLarge(generator);
			break;
		case 8:
			averageColumnLoad = distrLarge(generator);
			break;
		case 9:
			wellExponent = distrSmall(generator);
			break;
		case 10:
			rightColumn = distrLarge(generator);
			break;
		case 11:
			crackinessExponent = distrSmall(generator);
			break;
		case 12:
			coveredExponent = distrSmall(generator);
			break;
		case 13:
			movedDown = distrLarge(generator);
			break;
		case 14:
			scoreExponent = distrSmall(generator);
			break;
		case 15:
			iPenalty = distrLarge(generator);
			break;
		case 16:
			pieceLevels[0] = distrDiffs(generator);
			break;
		case 17:
			pieceLevels[1] = distrDiffs(generator);
			break;
		case 18:
			pieceLevels[2] = distrDiffs(generator);
			break;
		case 19:
			pieceLevels[3] = distrDiffs(generator);
			break;
		case 20:
			pieceLevels[4] = distrDiffs(generator);
			break;
		case 21:
			pieceLevels[5] = distrDiffs(generator);
			break;
		case 22:
			pieceLevels[6] = distrDiffs(generator);
			break;
		case 23:
			pieceDifferenceMultipliers[0] = distrLarge(generator);
			break;
		case 24:
			pieceDifferenceMultipliers[1] = distrLarge(generator);
			break;
		case 25:
			pieceDifferenceMultipliers[2] = distrLarge(generator);
			break;
		case 26:
			pieceDifferenceMultipliers[3] = distrLarge(generator);
			break;
		case 27:
			pieceDifferenceMultipliers[4] = distrLarge(generator);
			break;
		case 28:
			pieceDifferenceMultipliers[5] = distrLarge(generator);
			break;
		case 29:
			pieceDifferenceMultipliers[6] = distrLarge(generator);
			break;
		case 30:
			clearScores[0] = distrDiffs(generator);
			break;
		case 31:
			clearScores[1] = distrDiffs(generator);
			break;
		case 32:
			clearScores[2] = distrDiffs(generator);
			break;
		case 33:
			clearScores[3] = distrDiffs(generator);
			break;
		default:
			throw std::invalid_argument("Index received for altering gene is invalid value");
	}
	
}

double AI_Configuration::getGeneValueByIndex(const int index) const {

	switch (index) {
		case 0:
			return crackiness;			
		case 1:
			return coveredHoles;			
		case 2:
			return wellDepth;			
		case 3:
			return aggregateHeight;			
		case 4:
			return linesCleared;			
		case 5:
			return bumpiness;			
		case 6:
			return highestBlock;			
		case 7:
			return scoreValue;			
		case 8:
			return averageColumnLoad;			
		case 9:
			return wellExponent;			
		case 10:
			return rightColumn;			
		case 11:
			return crackinessExponent;			
		case 12:
			return coveredExponent;			
		case 13:
			return movedDown;			
		case 14:
			return scoreExponent;			
		case 15:
			return iPenalty;			
		case 16:
			return pieceLevels[0];			
		case 17:
			return pieceLevels[1];			
		case 18:
			return pieceLevels[2];			
		case 19:
			return pieceLevels[3];			
		case 20:
			return pieceLevels[4];			
		case 21:
			return pieceLevels[5];			
		case 22:
			return pieceLevels[6];			
		case 23:
			return pieceDifferenceMultipliers[0];			
		case 24:
			return pieceDifferenceMultipliers[1];			
		case 25:
			return pieceDifferenceMultipliers[2];			
		case 26:
			return pieceDifferenceMultipliers[3];			
		case 27:
			return pieceDifferenceMultipliers[4];			
		case 28:
			return pieceDifferenceMultipliers[5];			
		case 29:
			return pieceDifferenceMultipliers[6];			
		case 30:
			return clearScores[0];			
		case 31:
			return clearScores[1];			
		case 32:
			return clearScores[2];			
		case 33:
			return clearScores[3];			
		default:
			throw std::invalid_argument("Index received for altering gene is invalid value");
	}
	
}

std::string AI_Configuration::displayConfig() const {
	std::string ret = ""
	"  \"crackiness\":                 " + std::to_string(crackiness) + ",\n" +
	"  \"coveredHoles\":               " + std::to_string(coveredHoles) + ",\n" +
	"  \"wellDepth\":                  " + std::to_string(wellDepth) + ",\n" +
	"  \"aggregateHeight\":            " + std::to_string(aggregateHeight) + ",\n" +
	"  \"linesCleared\":               " + std::to_string(linesCleared) + ",\n" +
	"  \"bumpiness\":                  " + std::to_string(bumpiness) + ",\n" +
	"  \"highestBlock\":               " + std::to_string(highestBlock) + ",\n" +
	"  \"scoreValue\":                 " + std::to_string(scoreValue) + ",\n" +
	"  \"averageColumnLoad\":          " + std::to_string(averageColumnLoad) + ",\n" +
	"  \"wellExponent\":               " + std::to_string(wellExponent) + ",\n" +
	"  \"rightColumn\":                " + std::to_string(rightColumn) + ",\n" +
	"  \"crackinessExponent\":         " + std::to_string(crackinessExponent) + ",\n" +
	"  \"coveredExponent\":            " + std::to_string(coveredExponent) + ",\n" +
	"  \"movedDown\":                  " + std::to_string(movedDown) + ",\n" +
	"  \"scoreExponent\":              " + std::to_string(scoreExponent) + ",\n" +
	"  \"iPenalty\":                   " + std::to_string(iPenalty) + ",\n" +
	"  \"piece0Level\":                " + std::to_string(pieceLevels[0]) + ",\n" +
	"  \"piece1Level\":                " + std::to_string(pieceLevels[1]) + ",\n" +
	"  \"piece2Level\":                " + std::to_string(pieceLevels[2]) + ",\n" +
	"  \"piece3Level\":                " + std::to_string(pieceLevels[3]) + ",\n" +
	"  \"piece4Level\":                " + std::to_string(pieceLevels[4]) + ",\n" +
	"  \"piece5Level\":                " + std::to_string(pieceLevels[5]) + ",\n" +
	"  \"piece6Level\":                " + std::to_string(pieceLevels[6]) + ",\n" +
	"  \"piece0DifferenceMultiplier\": " + std::to_string(pieceDifferenceMultipliers[0]) + ",\n" +
	"  \"piece1DifferenceMultiplier\": " + std::to_string(pieceDifferenceMultipliers[1]) + ",\n" +
	"  \"piece2DifferenceMultiplier\": " + std::to_string(pieceDifferenceMultipliers[2]) + ",\n" +
	"  \"piece3DifferenceMultiplier\": " + std::to_string(pieceDifferenceMultipliers[3]) + ",\n" +
	"  \"piece4DifferenceMultiplier\": " + std::to_string(pieceDifferenceMultipliers[4]) + ",\n" +
	"  \"piece5DifferenceMultiplier\": " + std::to_string(pieceDifferenceMultipliers[5]) + ",\n" +
	"  \"piece6DifferenceMultiplier\": " + std::to_string(pieceDifferenceMultipliers[6]) + ",\n" +
	"  \"clear1Score\":                " + std::to_string(clearScores[0]) + ",\n" +
	"  \"clear2Score\":                " + std::to_string(clearScores[1]) + ",\n" +
	"  \"clear3Score\":                " + std::to_string(clearScores[2]) + ",\n" +
	"  \"clear4Score\":                " + std::to_string(clearScores[3]) + ",\n";

	return ret;
}