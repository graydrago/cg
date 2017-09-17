#pragma once

#include <map>
#include <memory>

#include "experiment.cpp"

class App {
    private:
      //std::map<std::string, std::unique_ptr<Experiment>> m_experiment_list;
      App();

    public:
        App(App const&) = delete;
        static App& instance() {
          static App instance;
          return instance;
        }

        virtual ~App();
};

