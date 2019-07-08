#include "TrainingSet.h"

TrainingSet::TrainingSet(unsigned int learningRepetitions, unsigned int epochs, unsigned int numbEpisodes, unsigned int batchSize, float learningRate) {
    this->learningRepetitions = learningRepetitions;
    this->epochs = epochs;
    this->numbEpisodes = numbEpisodes;
    this->batchSize = batchSize;
    this->learningRate = learningRate;
}

void TrainingSet::setLearningRepetitions(unsigned int learningRepetitions) {
    this->learningRepetitions = learningRepetitions;
}

void TrainingSet::setEpochs(unsigned int epochs) {
    this->epochs = epochs;
}
        
void TrainingSet::setNumbEpisodes(unsigned int numbEpisodes) {
    this->numbEpisodes = numbEpisodes;
}

void TrainingSet::setBatchSize(unsigned int batchSize) {
    this->batchSize = batchSize;
}
        
void TrainingSet::setLearningRate(float learningRate) {
    this->learningRate = learningRate;
}

void TrainingSet::train(Agent* agent) {
    vector<Episode> episodes;
    RLDataset dataSet;
    for (unsigned int i = 0; i < learningRepetitions; i++) {
        for (unsigned int j = 0; j < numbEpisodes; j++) {
            episodes.push_back(agent->getEpisode());
        }
        dataSet.set(episodes);
        episodes.clear();
        agent->lpolicy.vModel.learn(dataSet, epochs, batchSize, learningRate);
    }
}
