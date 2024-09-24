/*
 * MQConnection.h
 *
 *  Created on: 24 Jun 2013
 *      Author: GBY18020
 */

#ifndef MQCONNECTION_H_
#define MQCONNECTION_H_

#include <cmqc.h>
#include "Params.h"

class MQConnection {
private:
	MQHCONN l_connection_handle;
public:
    char cp_request_queue_manager[50 + 1];
    char cp_email_care_request_q[50 + 1];
    char cp_email_customer_request_q[50 + 1];
    char cp_single_sms_q[50 + 1];
    char cp_service_q[50 + 1];
    char cp_reply_to_qmgr[50 + 1];
    char cp_reply_to_q[50 + 1];
    char cp_email_care_address[80 + 1];
    char cp_email_internal_request_q[50 + 1];
    char cp_email_creditnrisk_address[80 + 1];
    MQLONG l_completion_code;
	MQLONG l_reason_code;
	MQConnection();
	virtual ~MQConnection();
	int setup(Params *pParams);
	int connect();
	int disconnect();
	int commit();
	int rollback();
	char *getEnvVar(const char *pcString);
	int putMessage(char *cp_request_q, char *cp_reply_to_qmgr, char *cp_reply_to_q, const char *cp_mq_message);
};

#endif /* MQCONNECTION_H_ */
