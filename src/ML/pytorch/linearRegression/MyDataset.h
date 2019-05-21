#pragma once

class MyDataset : public torch::data::Dataset<MyDataset>
{
    private:
        torch::Tensor states, scores;

    public:
        explicit MyDataset(unsigned n, unsigned ds) {
            float state_mut_prob = 0.1;

            states = torch::zeros({n,ds}); //dataset of states
            scores = torch::zeros({n,1}); //corresponding scores

            std::default_random_engine gen;
            std::uniform_int_distribution<int> score_dist(0,250);
            std::uniform_real_distribution<double> prob_dist(0.0,1.0);

            //(state, score) dataset
            for (unsigned i = 0; i < n; i++){
                scores[i] = score_dist(gen);
                for (unsigned j = 0; j < ds; j++){
                    if (prob_dist(gen) < state_mut_prob)
                        states[i][j] = 1.0f;
                }
            }
        }

        torch::data::Example<> get(size_t index) override {
            return {states[index], scores[index]};
        }

        torch::optional<size_t> size() const override {
            return states.size(0);
        }
};
