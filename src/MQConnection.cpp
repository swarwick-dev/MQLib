/*
 * MQConnection.cpp
 *
 *  Created on: 24 Jun 2013
 *      Author: GBY18020
 */

#include "MQConnection.h"
#include "Logger.h"
#include "common_constants.h"

MQConnection::MQConnection() {
    this->cp_request_queue_manager[0] = '\0';
    this->cp_email_care_request_q[0] = '\0';
    this->cp_email_customer_request_q[0] = '\0';
    this->cp_single_sms_q[0] = '\0';
    this->cp_service_q[0] = '\0';
    this->cp_reply_to_qmgr[0] = '\0';
    this->cp_reply_to_q[0] = '\0';
    this->cp_email_care_address[0] = '\0';
    this->cp_email_internal_request_q[0] = '\0';
    this->cp_email_creditnrisk_address[0] = '\0';

    this->l_completion_code=0;
	this->l_reason_code=0;
	this->l_connection_handle = 0;
}

MQConnection::~MQConnection() {
	// TODO Auto-generated destructor stub
}

int MQConnection::setup(Params *pParams) {
	int iExitCode = SUCCESS;
	char *cp_temp;

	sprintf(this->cp_request_queue_manager,"%s", pParams->getValueForParameter("REQUEST_QMGR").c_str());
	if (strcmp(this->cp_request_queue_manager, "ERROR") != 0) {
		gl_inform("REQUEST_QMGR environment variable is: %s", cp_request_queue_manager);
	}
	else
	{
		gl_error("name of request queue manager could not be obtained from environment variable REQUEST_QMGR.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_email_care_request_q,"%s", pParams->getValueForParameter("REQUEST_Q_EMAIL_CARE").c_str());
	if (strcmp(this->cp_email_care_request_q, "ERROR") != 0) {
		gl_inform(
				"REQUEST_Q_EMAIL_CARE environment variable is: %s", cp_email_care_request_q);
	}
	else
	{
		gl_error("Name of referral queue could not be obtained from environment variable REQUEST_Q_EMAIL_CARE.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_email_customer_request_q,"%s", pParams->getValueForParameter("REQUEST_Q_EMAIL_CUSTOMER").c_str());
	if (strcmp(this->cp_email_customer_request_q, "ERROR") != 0) {
		gl_inform(
				"REQUEST_Q_EMAIL_CUSTOMER environment variable is: %s", cp_email_customer_request_q);
	}
	else
	{
		gl_error("Name of customer email queue could not be obtained from environment variable REQUEST_Q_EMAIL_CUSTOMER.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_single_sms_q,"%s", pParams->getValueForParameter("REQUEST_Q_SINGLE_SMS").c_str());
	if (strcmp(this->cp_single_sms_q, "ERROR") != 0) {
		gl_inform(
				"REQUEST_Q_SINGLE_SMS environment variable is: %s", cp_single_sms_q);
	}
	else
	{
		gl_error("Name of SMS queue could not be obtained from environment variable REQUEST_Q_SINGLE_SMS.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_service_q,"%s", pParams->getValueForParameter("REQUEST_Q_SERVICE").c_str());
	if (strcmp(this->cp_service_q, "ERROR") != 0) {
		gl_inform("REQUEST_Q_SERVICE environment variable is: %s", cp_service_q);
	}
	else
	{
		gl_error("Name of Service Request queue could not be obtained from environment variable REQUEST_Q_SERVICE.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_reply_to_qmgr,"%s", pParams->getValueForParameter("REPLY_TO_QMGR").c_str());
	if (strcmp(this->cp_reply_to_qmgr, "ERROR") != 0) {
		gl_inform("REPLY_TO_QMGR environment variable is: %s", cp_reply_to_qmgr);
	}
	else
	{
		gl_error("Reply to queue manager could not be obtained from environment variable REPLY_TO_QMGR.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_reply_to_q,"%s", pParams->getValueForParameter("REPLY_TO_Q").c_str());
	if (strcmp(this->cp_reply_to_q, "ERROR") != 0) {
		gl_inform("REPLY_TO_Q environment variable is: %s", cp_reply_to_q);
	}
	else
	{
		gl_error("Reply queue name could not be obtained from environment variable REPLY_TO_Q.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_email_care_address,"%s", pParams->getValueForParameter("CARE_EMAIL_ADDRESS").c_str());
	if (strcmp(this->cp_email_care_address, "ERROR") != 0) {

		gl_inform(
				"CARE_EMAIL_ADDRESS environment variable is: %s", cp_email_care_address);
	}
	else
	{
		gl_error("email address for care could not be obtained from environment variable CARE_EMAIL_ADDRESS.");
		iExitCode = FAILURE;
	}

	sprintf(this->cp_email_internal_request_q,"%s", pParams->getValueForParameter("REQUEST_Q_INTERNAL_EMAIL").c_str());
	if (strcmp(this->cp_email_internal_request_q, "ERROR") != 0) {
		gl_inform(
				"REQUEST_Q_INTERNAL_EMAIL environment variable is: %s", cp_email_internal_request_q);
	}
	else
	{
		gl_error("Name of Internal Email request queue could not be obtained from environment variable REQUEST_Q_INTERNAL_EMAIL.");
		iExitCode = FAILURE;
	}

	return iExitCode;
}

int MQConnection::connect() {
	int iExitCode = SUCCESS;

	MQCONN (this->cp_request_queue_manager, &this->l_connection_handle,
			&this->l_completion_code, &this->l_reason_code);

    if (this->l_completion_code == MQCC_FAILED)
    {
       gl_error("Could not connect to Queue Manager %s", this->cp_request_queue_manager);
       gl_error("The MQSeries MQCONN call ended with reason code %ld", this->l_reason_code);
       iExitCode = FAILURE;
    }
    else
    {
       if (this->l_reason_code != MQRC_NONE)
       {
          gl_error("Could not connect to Queue Manager %s", this->cp_request_queue_manager);
          gl_error("The MQSeries MQCONN call ended with reason code %ld", this->l_reason_code);
          iExitCode = FAILURE;
       }
    }

    if ( iExitCode == SUCCESS )
    	gl_inform(" Connected to Queue Manager %s", this->cp_request_queue_manager);

	return iExitCode;
}

int MQConnection::disconnect() {
	int iExitCode = SUCCESS;

	MQDISC(&this->l_connection_handle,
	            &this->l_completion_code,
	            &this->l_reason_code);

    if (this->l_completion_code == MQCC_FAILED)
    {
       gl_error("Could not disconnect from Queue Manager %s");
       gl_error("The MQSeries MQDISC call ended with reason code %ld", this->l_reason_code);
       iExitCode = FAILURE;
    }
    else
    {
       if (this->l_reason_code != MQRC_NONE)
       {
          gl_error("Could not disconnect from Queue Manager %s");
          gl_error("The MQSeries MQDISC call ended with reason code %ld", this->l_reason_code);
          iExitCode = FAILURE;
       }
    }

    if ( iExitCode == SUCCESS )
    	gl_inform(" Disconnected from Queue Manager %s", this->cp_request_queue_manager);

	return iExitCode;
}

int MQConnection::commit() {
	int iExitCode = SUCCESS;

	MQCMIT( this->l_connection_handle, &this->l_completion_code, &this->l_reason_code );
     if ( this->l_completion_code == MQCC_FAILED )
     {
       gl_error ( "Could not commit transaction to Queue Manager" );
       gl_error ( "The MQCMIT call ended with reason code %ld", this->l_reason_code );
       iExitCode = FAILURE;
     }

	return iExitCode;
}

int MQConnection::rollback() {
	int iExitCode = SUCCESS;

	MQBACK ( this->l_connection_handle,
	           &this->l_completion_code,
	           &this->l_reason_code );

	if ( this->l_completion_code == MQCC_FAILED )
	{
	  gl_error ( "Could not backout transaction from Queue Manager" );
	  gl_error ( "The MQBACK call ended with reason code %ld", this->l_reason_code );
	  iExitCode = FAILURE;
	}

	return iExitCode;
}

int MQConnection::putMessage(char *cp_request_q, char *cp_reply_to_qmgr, char *cp_reply_to_q,
		const char *cp_mq_message) {
	int iExitCode = SUCCESS;
	MQOD     object_descriptor = {MQOD_DEFAULT};
	MQMD     struct_message_descriptor = {MQMD_DEFAULT};
	MQPMO    l_put_message_options = {MQPMO_DEFAULT};
	MQLONG   l_msg_length = 0;

	strncpy(object_descriptor.ObjectName, cp_request_q, (size_t)MQ_Q_NAME_LENGTH);

	/* length without null        */
	l_msg_length = strlen(cp_mq_message);

	/*set put options*/
	l_put_message_options.Options |= MQPMO_NEW_MSG_ID;
	l_put_message_options.Options |= MQPMO_NEW_CORREL_ID;
	l_put_message_options.Options |= MQPMO_SYNCPOINT;
	memcpy(struct_message_descriptor.Format,MQFMT_STRING, (size_t)MQ_FORMAT_LENGTH);
	struct_message_descriptor.MsgType  = MQMT_REQUEST;
	struct_message_descriptor.Persistence = MQPER_PERSISTENT;
	if ( strlen(cp_reply_to_q) > 0 )
		strncpy(struct_message_descriptor.ReplyToQ,cp_reply_to_q, MQ_Q_NAME_LENGTH);
	if ( strlen(cp_reply_to_qmgr) > 0 )
		strncpy(struct_message_descriptor.ReplyToQMgr,cp_reply_to_qmgr, MQ_Q_MGR_NAME_LENGTH);

	MQPUT1(this->l_connection_handle,
			&object_descriptor,
			&struct_message_descriptor,
			&l_put_message_options,
			l_msg_length,
			(void *)cp_mq_message,
			&this->l_completion_code,
			&this->l_reason_code);

	if (this->l_completion_code == MQCC_FAILED)
	{
		gl_error("The MQSeries call MQPUT1 Failed with reason code %ld", this->l_reason_code);
		iExitCode = FAILURE;
	}
	else
	{
		if (this->l_reason_code != MQRC_NONE)
		{
			gl_warn("The MQSeries MQPUT1 call ended with reason code %ld", this->l_reason_code);
		}
		else
		{
			gl_trace(_DETAILED, "Message put to queue %s", cp_request_q);
			iExitCode = SUCCESS;
		}
	}

	return iExitCode;
}
