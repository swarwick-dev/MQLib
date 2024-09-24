/*
 * MQMessage.cpp
 *
 *  Created on: 25 Jun 2013
 *      Author: GBY18020
 */

#include <sstream>

#include "MQMessage.h"

MQMessage::MQMessage() {
	this->vElements.clear();
}

MQMessage::~MQMessage() {
	this->vElements.clear();
}

string MQMessage::toStringFull() {
	ostringstream oss;
	vector<string>::iterator it;

	oss << XML_DECLARATION << this->sTitle
			<< "<" << this->sType << " " << XML_START_ELEMENT_TOP;

	for ( it = this->vElements.begin(); it != this->vElements.end(); it++)
	{
		oss << (*it);
	}

	oss << "</" << this->sType << ">";

	return oss.str();
}

string MQMessage::toStringContent() {
	ostringstream oss;
	vector<string>::iterator it;

	for ( it = this->vElements.begin(); it != this->vElements.end(); it++)
	{
		oss << (*it);
	}

	return oss.str();
}

void MQMessage::addElement(string sElement) {
	this->vElements.push_back(sElement);
}

void MQMessage::setType(string sType) {
	this->sType = sType;

}

void MQMessage::setTitle(string sTitle) {
	this->sTitle = sTitle;

}


void MQMessage::addNameValuePair(string sField, string sType, string sName, string sValue) {
	ostringstream oss;

	oss << "<wmqi:" << sField << ">"
			<< "<" << sType << ":name>"
			<< sName
			<< "</" << sType << ":name>"
			<< "<" << sType << ":value>"
			<< sValue
			<< "</" << sType << ":value>"
			<< "</wmqi:" << sField <<">";

	this->vElements.push_back(oss.str());
}

void MQMessage::addNameValuePair(string sField, string sName, string sValue) {
	ostringstream oss;

	oss << "<" << sField << ">"
			<< "<name>"
			<< sName
			<< "</name>"
			<< "<value>"
			<< sValue
			<< "</value>"
			<< "</" << sField <<">";

	this->vElements.push_back(oss.str());
}

void MQMessage::addValuePair(string sName, string sValue) {
	ostringstream oss;

	oss << "<" << sName << ">"
			<< sValue
			<< "</" << sName <<">";

	this->vElements.push_back(oss.str());
}
