#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include "ai_instance_handler.hpp"

void AI_InstanceHandler::serializeAll(const std::vector<AI_InstanceHandler> &instances, int &generationNumber, const std::string logPrefix) {
    std::string fname = logPrefix + ".aihandlelist";
    std::ofstream file(fname, std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&generationNumber), sizeof(int));
        for (const auto& instance : instances) {
            file.write(reinterpret_cast<const char*>(&instance), sizeof(AI_InstanceHandler));
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for serialization\n";
    }
}

bool AI_InstanceHandler::deserializeAll(std::vector<AI_InstanceHandler> &instances, int &generationNumber, const std::string logPrefix) {
    std::string fname = logPrefix + ".aihandlelist";
    std::ifstream file(fname, std::ios::in | std::ios::binary);
    if (file.is_open()) {
		instances.clear();
        file.read(reinterpret_cast<char*>(&generationNumber), sizeof(int));
        AI_InstanceHandler instance;
        while (file.read(reinterpret_cast<char*>(&instance), sizeof(AI_InstanceHandler))) {
            instances.push_back(instance);
        }
        file.close();
		return true;
    } else {
		return false;
    }
}

void AI_InstanceHandler::crossover(const AI_InstanceHandler &parent1, const AI_InstanceHandler &parent2) {

	this->mBottomConfig.crossover(parent1.mBottomConfig, parent2.mBottomConfig);
	this->mMiddleConfig.crossover(parent1.mMiddleConfig, parent2.mMiddleConfig);
	this->mTopConfig.crossover(parent1.mTopConfig, parent2.mTopConfig);
	
}

void AI_InstanceHandler::initialize(const double weightSize, const std::mt19937 &generator) {

	this->mBottomConfig.initialize(weightSize, generator);
	this->mMiddleConfig.initialize(weightSize, generator);
	this->mTopConfig.initialize(weightSize, generator);

}

std::string AI_InstanceHandler::displayHandler() const {

	std::string ret = "{\n";
	auto appendMe = "\"bottom\": {\n" +
	this->mBottomConfig.displayConfig() +
	"},\n";
	ret.append(appendMe);

	appendMe = "\"middle\": {\n" +
	this->mMiddleConfig.displayConfig() +
	"},\n";
	ret.append(appendMe);

	appendMe = "\"top\": {\n" +
	this->mTopConfig.displayConfig() +
	"},\n";
	ret.append(appendMe);

	ret.append(
		"\"trainedAs3tier\": true,\n"
		"\"levelControlsSectionsBeneath\": true,\n"
		"\"catersToIndividualPieces\": true,\n"
		"\"includesEveryLevel\": false,\n"
		"\"usesPerfectScores\": false,\n"
		"\"tetrisOverridesScore\": true\n"
		"}\n"
	);

	return ret;
}

int AI_InstanceHandler::applyMutation(const int mutationRate, const double weightSize, const std::mt19937 &generator) {

	int totalMutations = 0;

	totalMutations += this->mBottomConfig.applyMutation(mutationRate, weightSize, generator);
	totalMutations += this->mMiddleConfig.applyMutation(mutationRate, weightSize, generator);
	totalMutations += this->mTopConfig.applyMutation(mutationRate, weightSize, generator);

	// Try for a chance to copy one config on top of another
	if (rand() % 100 <= mutationRate / 2) {

		totalMutations += 2;

		// 6 ways of doing this
		int notMe = rand() % 6;

		switch (notMe) {
			case 0:
				this->mMiddleConfig = mTopConfig;
				break;
			case 1:
				this->mTopConfig = mMiddleConfig;
				break;
			case 2:
				this->mBottomConfig = mTopConfig;
				break;
			case 3:
				this->mTopConfig = mBottomConfig;
				break;
			case 4:
				this->mBottomConfig = mMiddleConfig;
				break;
			case 5:
				this->mMiddleConfig = mBottomConfig;
				break;
		}
		
	}

}