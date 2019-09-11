/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Signal.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:20
 */

#include "Signal.h"
#include "Entity.h"
#include "Hold.h"
#include "Model.h"
#include "Util.h"

Signal::Signal(Model *model): ModelComponent(model, Util::TypeOf<Signal>()) {

}

Signal::Signal(const Signal& orig): ModelComponent(orig) {

}


Signal::~Signal() {
}
template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

void Signal::_execute(Entity* entity) {
	std::list<ModelComponent*>::iterator it = _model->getComponentManager()->begin();
	for (; it != _model->getComponentManager()->end(); it++) {
		auto component = *it;
		if (instanceof<Hold>(*it)) {
			Hold* h = ((Hold*)(*it));
			if (h->getWaitForValueExpr() == signalName) {
				h->release_signal(limit);
			}
		}
	}
	_model->sendEntityToComponent(entity, this->getNextComponents()->front(), 0.0);
}
std::string Signal::show() {
	return ModelComponent::show() + "";
}
PluginInformation* Signal::GetPluginInformation() {
	return new PluginInformation(Util::TypeOf<Signal>(), &Hold::LoadInstance);
}

void Signal::_initBetweenReplications() {
	
}

ModelComponent* Signal::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Signal* newComponent = new Signal(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {
    }
    return newComponent;
}