/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dummy.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 22 de Maio de 2019, 18:41
 */

#include "Dummy.h"
#include "Model.h"

// TODO: FOR TESTING ONLY
#include "ODE.h"
#include "Variable.h"

Dummy::Dummy(Model* model) : ModelComponent(model, Util::TypeOf<Dummy>()) {
    _ode = new ODE(model->getElementManager());
}

Dummy::Dummy(const Dummy& orig) : ModelComponent(orig) {
}

Dummy::~Dummy() {
}

std::string Dummy::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Dummy::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Dummy* newComponent = new Dummy(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Dummy::setOde(ODE* _ode) {
    this->_ode = _ode;
}

ODE* Dummy::getOde() const {
    return _ode;
}

void Dummy::_execute(Entity* entity) {
    /*
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
    */
    _ode->solve();
    Event* newEvent = new Event(_ode->getStepH(), entity, this->getNextComponents()->frontConnection());
    _model->getEvents()->insert(newEvent);
}

bool Dummy::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
    }
    return res;
}

void Dummy::_initBetweenReplications() {
}

std::map<std::string, std::string>* Dummy::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance(); 
    return fields;
}

bool Dummy::_check(std::string* errorMessage) {   
    return true;
}

PluginInformation* Dummy::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Dummy>(), &Dummy::LoadInstance); return info;
}
