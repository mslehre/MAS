#ifndef TRAININGSET_H
#define TRAININGSET_H
#include <iostream>
#include "../../alignment/State.h"
#include "../../alignment/Graph.h"
#include "../../alignment/Node.h"
#include "../../alignment/Edge.h"
#include "../SimpleAgent/Agent.h"
#include "../SimpleAgent/Policy.h"
#include "../SimpleAgent/RandomPolicy.h"
#include "../SimpleAgent/Episode.h"
#include "valueMLmodel.h"
#include "LearnedPolicy.h"
#include "LinearNet.h"
#include "RLDataset.h"
#include <torch/torch.h>
#include <vector>

using std::vector;
using namespace std;


class TrainingSet {

    public:
        TrainingSet(unsigned int learningRepetitions, unsigned int epochs, unsigned int numbEpisodes, unsigned int batchSize, unsigned int learningRate); 
	
        unsigned int learningRepetitions;   ///< Number of times the agent gets trained
        unsigned int epochs;    ///< Number of epochs
        unsigned int batchSize;    ///< The size of a batch
        unsigned int learningRate;   ///< The rate of learning (alpha)
        unsigned int numbEpisodes;   ///< The number of episodes
        
        void setLearningRepetitions(unsigned int learningRepetitions);

        void setEpochs(unsigned int epochs);

        void setNumbEpisodes(unsigned int numbEpisodes);

        void setBatchSize(unsigned int batchSize);

        void setLearningRate(unsigned int learningRate);

        /** \brief This function trains an agent a designated number of times.
         *  \param agent requires an agent that has learnedPolicy that has learned at least once.
         */ 
        void train(Agent* agent);
};
#endif
