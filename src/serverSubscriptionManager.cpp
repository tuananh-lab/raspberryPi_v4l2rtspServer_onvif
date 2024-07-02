/* --------------------------------------------------------------------------
Here implements subscription management operations for ONVIF services. 
It includes functions for renewing subscriptions (Renew) and unsubscribing (Unsubscribe) from notifications.
-----------------------------------------------------------------------------
 serverSubscriptionManager.cpp
 
 bw-2.wsdl server
----------------------------------------------------------------------------- */


#include "soapSubscriptionManagerBindingService.h"
#include "onvif_impl.h"


int SubscriptionManagerBindingService::Renew(_wsnt__Renew *wsnt__Renew, _wsnt__RenewResponse &wsnt__RenewResponse)
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}

int SubscriptionManagerBindingService::Unsubscribe(_wsnt__Unsubscribe *wsnt__Unsubscribe, _wsnt__UnsubscribeResponse &wsnt__UnsubscribeResponse)
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	return SOAP_OK;
}
