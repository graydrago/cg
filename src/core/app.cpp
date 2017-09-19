#pragma once

#include <map>
#include <memory>

#include "experiment.cpp"

class App {
    private:
      App();

    public:
        App(App const&) = delete;
        static App& instance() {
          static App instance;
          return instance;
        }

        virtual ~App();
};

