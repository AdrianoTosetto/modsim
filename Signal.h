/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Signal.h
 * Author: rlcancian
 *
 * Created on 03 de Junho de 2019, 15:20
 */

#ifndef SIGNAL_H
#define SIGNAL_H
#include "ModelComponent.h"

class Signal: public ModelComponent {
public:
    Signal(Model *model);
    Signal(const Signal& orig);
    virtual ~Signal();
    virtual std::string show();
    static PluginInformation* GetPluginInformation();
    static ModelComponent* LoadInstance(Model* model, std::map<std::string, std::string>* fields);
    void setSignalName(std::string name) {
        signalName = name;
    }
    std::string getSignalName() {
        return signalName;
    }
private:
    int limit = 10;
    std::string signalName;

protected:
    virtual void _execute(Entity* entity);
    virtual void _initBetweenReplications();

};

#endif /* SIGNAL_H */

