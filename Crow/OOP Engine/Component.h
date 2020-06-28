//
// Created by Igli milaqi on 25/02/2020.
//

#ifndef CROW_COMPONENT_H
#define CROW_COMPONENT_H


class OOPEngine;

class Gameobject;

class Component {

public:
    Gameobject* parent;
    OOPEngine* engine;
    virtual void Update(){};
    virtual void Start(){};

};


#endif //CROW_COMPONENT_H
