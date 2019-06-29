#include "TrainingSet.h"

TrainingSet::TrainingSet(unsigned int learningRepetitions, unsigned int epochs, unsigned int numbEpisodes, unsigned int batchSize, unsigned int learningRate) {
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
        
void TrainingSet::setLearningRate(unsigned int learningRate) {
    this->learningRate = learningRate;
}

void TrainingSet::train(Agent* agent, LearnedPolicy lpol) {
    agent->setPolicy(&lpol);
    vector<Episode> episodes;
    for (unsigned int i = 0; i < learningRepetitions; i++) {
        for (unsigned int j = 0; j < numbEpisodes; j++) {
            episodes.push_back(agent->getEpisode());
        }
    RLDataset dataSet(episodes);
    episodes.clear();
    lpol.vModel->learn(dataSet, epochs, batchSize, learningRate);
    }
}
