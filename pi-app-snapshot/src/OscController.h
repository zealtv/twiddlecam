#pragma once

#include "ofMain.h"
#include "Parameter.h"

class OscController {
public:
    void setup(int port);
    void update(ParameterList& parameters);
    int getPort() const;

private:
    int port = 1111;
};
