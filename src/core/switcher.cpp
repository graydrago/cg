#pragma once

#include <memory>
#include <string>

#include "experiment.cpp"
#include "../chapter_2/experiment_2_1.cpp"
#include "../chapter_2/experiment_2_5.cpp"

void selectExperiment(std::string name, std::unique_ptr<Experiment> &current) {
    if (name == "2.1") { current.reset(new Experiment_2_1()); }
    else if (name == "2.5") { current.reset(new Experiment_2_5()); }
    else { SDL_Log("Experiment %s was not found", name.c_str()); }
}
