/* --------------------------------------------------------------------------
Here implement notification service include describe and get current state 
-----------------------------------------------------------------------------
 serverNotificationProducer.cpp
 
 bw-2.wsdl server
----------------------------------------------------------------------------- */

#include <sstream>

#include "soapNotificationProducerBindingService.h"
#include "soapNotificationConsumerBindingProxy.h"
#include "onvif_impl.h"

int NotificationProducerBindingService::Subscribe(_wsnt__Subscribe *wsnt__Subscribe, _wsnt__SubscribeResponse &wsnt__SubscribeResponse)
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	NotificationConsumerBindingProxy* subcriberProxy = new NotificationConsumerBindingProxy(wsnt__Subscribe->ConsumerReference.Address);
	
	_wsnt__Notify notification;
	notification.NotificationMessage.push_back(soap_new_wsnt__NotificationMessageHolderType(subcriberProxy->soap));
	notification.NotificationMessage.back()->Message.__any = soap_dom_element(subcriberProxy->soap, (char*)NULL, (char*)NULL, (char*)"subscribed");	
	if (subcriberProxy->Notify(&notification) != SOAP_OK)
	{
		subcriberProxy->soap_stream_fault(std::cerr);
	}
	
	ctx->m_subscriber.push_back(subcriberProxy);
	std::cout << __FUNCTION__ << " nb subscriber:" << ctx->m_subscriber.size() << std::endl;	
	
	std::ostringstream os;
	os << "http://" << ctx->getServerIpFromClientIp(htonl(this->soap->ip)) << ":" << ctx->m_port;
	std::string url(os.str());
	
	timeval tv;
	tv.tv_sec = time(NULL);
	tv.tv_usec = 0;
	wsnt__SubscribeResponse.SubscriptionReference.Address = strcpy((char*)soap_malloc(this->soap, url.size()+1), url.c_str());
	wsnt__SubscribeResponse.CurrentTime = soap_new_ptr(this->soap,tv);
	tv.tv_sec += 3600;
	wsnt__SubscribeResponse.TerminationTime = soap_new_ptr(this->soap,tv);
	
	return SOAP_OK;
}

int NotificationProducerBindingService::GetCurrentMessage(_wsnt__GetCurrentMessage *wsnt__GetCurrentMessage, _wsnt__GetCurrentMessageResponse &wsnt__GetCurrentMessageResponse)
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}
