#ifndef AI_INSTANCE_HANDLER
#define AI_INSTANCE_HANDLER

#include <random>
#include <vector>
#include "tetris_rules.hpp"
#include "ai_configuration.hpp"

class AI_InstanceHandler {

private:
	AI_Configuration mBottomConfig;
	AI_Configuration mMiddleConfig;
	AI_Configuration mTopConfig;

public:
	static void serializeAll(const std::vector<AI_InstanceHandler> &instances, int &generationNumber, const std::string logPrefix);
	static bool deserializeAll(std::vector<AI_InstanceHandler> &instances, int &generationNumber, const std::string logPrefix);

	void crossover(const AI_InstanceHandler &parent1, const AI_InstanceHandler &parent2);
	void initialize(const double weightSize, const std::mt19937 &generator);
	std::string displayHandler() const;

	int applyMutation(const int mutationRate, const double weightSize, const std::mt19937 &generator);

	double fitness = 0;
	double linesResult = 0;
	double scoreResult = 0;
};

#endif // AI_INSTANCE_HANDLER