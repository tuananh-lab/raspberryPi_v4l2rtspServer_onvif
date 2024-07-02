/* --------------------------------------------------------------------------
Here implement an ONVIF-compliant event handling web service. 
It includes functionalities such as retrieving service capabilities, creating pull point subscriptions for event notifications, and obtaining event properties.
Manage event-based interactions between devices and clients, supporting real-time event notifications and configurations.*/
-----------------------------------------------------------------------------
 serverEvent.cpp
 
 events.wsdl server
----------------------------------------------------------------------------- */
#include <sstream>
#include "soapEventBindingService.h"
#include "onvif_impl.h"

int EventBindingService::GetServiceCapabilities(_tev__GetServiceCapabilities *tev__GetServiceCapabilities, _tev__GetServiceCapabilitiesResponse &tev__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tev__GetServiceCapabilitiesResponse.Capabilities = ctx->getEventServiceCapabilities(this->soap);		
	return SOAP_OK;
}

int EventBindingService::CreatePullPointSubscription(_tev__CreatePullPointSubscription *tev__CreatePullPointSubscription, _tev__CreatePullPointSubscriptionResponse &tev__CreatePullPointSubscriptionResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	std::ostringstream os;
	os << "http://" << ctx->getServerIpFromClientIp(htonl(this->soap->ip)) << ":" << ctx->m_port;
	std::string url(os.str());
	
	timeval tv;
	tv.tv_sec = time(NULL);
	tv.tv_usec = 0;
	tev__CreatePullPointSubscriptionResponse.SubscriptionReference.Address = strcpy((char*)soap_malloc(this->soap, url.size()+1), url.c_str());
	tev__CreatePullPointSubscriptionResponse.wsnt__CurrentTime = tv;
	tv.tv_sec += 3600;
	tev__CreatePullPointSubscriptionResponse.wsnt__TerminationTime = tv;
		
	return SOAP_OK;
}

int EventBindingService::GetEventProperties(_tev__GetEventProperties *tev__GetEventProperties, _tev__GetEventPropertiesResponse &tev__GetEventPropertiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

