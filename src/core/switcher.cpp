#pragma once

#include <memory>
#include <string>

#include "experiment.cpp"
#include "../chapter_2/experiment_2_1.cpp"
#include "../chapter_2/experiment_2_5.cpp"
#include "../chapter_2/experiment_2_7.cpp"
#include "../chapter_2/experiment_2_9.cpp"
#include "../chapter_2/experiment_2_14.cpp"
#include "../chapter_2/experiment_2_17.cpp"
#include "../chapter_2/experiment_2_18.cpp"
#include "../chapter_2/experiment_2_19.cpp"
#include "../chapter_2/exercise_2_12.cpp"
#include "../chapter_2/exercise_2_13.cpp"
#include "../chapter_2/exercise_2_14.cpp"
#include "../chapter_2/exercise_2_17.cpp"
#include "../chapter_2/exercise_2_20.cpp"

void selectExperiment(std::string name, std::unique_ptr<Experiment> &current) {
    if (name == "2.1") { current.reset(new Experiment_2_1()); }
    else if (name == "2.5") { current.reset(new Experiment_2_5()); }
    else if (name == "2.7") { current.reset(new Experiment_2_7()); }
    else if (name == "2.9") { current.reset(new Experiment_2_9()); }
    else if (name == "2.14") { current.reset(new Experiment_2_14()); }
    else if (name == "2.17") { current.reset(new Experiment_2_17()); }
    else if (name == "2.18") { current.reset(new Experiment_2_18()); }
    else if (name == "2.19") { current.reset(new Experiment_2_19()); }
    else if (name == "e2.12") { current.reset(new Exercise_2_12()); }
    else if (name == "e2.13") { current.reset(new Exercise_2_13()); }
    else if (name == "e2.14") { current.reset(new Exercise_2_14()); }
    else if (name == "e2.17") { current.reset(new Exercise_2_17()); }
    else if (name == "e2.20") { current.reset(new Exercise_2_20()); }
    else { SDL_Log("Experiment %s was not found", name.c_str()); }
}
