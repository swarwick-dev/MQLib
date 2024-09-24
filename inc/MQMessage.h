/*
 * MQMessage.h
 *
 *  Created on: 25 Jun 2013
 *      Author: GBY18020
 */

#ifndef MQMESSAGE_H_
#define MQMESSAGE_H_

#include <vector>

using namespace std;

#define XML_DECLARATION "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
#define XML_START_ELEMENT_TOP "xmlns:wmqi=\"http://WMQIServices.eai.o2c.ibm.com\" xmlns:common=\"http://CommonCompanionElements.eai.o2c.ibm.com\" xmlns:cs=\"http://companion.eai.o2c.ibm.com\" xmlns:gentypes=\"http://gentypes.eai.o2c.ibm.com\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://WMQIServices.eai.o2c.ibm.com C:\\Mine\\Projects\\Real\\COMPAN~1\\R2.0\\R2.0Schemas\\WMQIServices.xsd\">"

class MQMessage {
private:
	string sMessage;
	string sType;
	string sTitle;
public:
	vector<string> vElements;

	MQMessage();
	virtual ~MQMessage();
	string toStringFull();
	string toStringContent();
	void addElement(string sElement);
	void setType(string sType);
	void setTitle(string sTitle);
	void addNameValuePair(string sField, string sType, string sName, string sValue);
	void addNameValuePair(string sField, string sName, string sValue);
	void addValuePair(string sName, string sValue);
};

#endif /* MQMESSAGE_H_ */
