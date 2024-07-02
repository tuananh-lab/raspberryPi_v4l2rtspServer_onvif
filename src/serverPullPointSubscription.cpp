/* --------------------------------------------------------------------------
Here implements notification service for the PullPointSubscription service based on the ONVIF standard, enabling interaction with devices using the SOAP protocol.
-----------------------------------------------------------------------------
 serverPullPointSubscription.cpp
 
 bw-2.wsdl server
----------------------------------------------------------------------------- */

#include <sstream>

#include "soapPullPointSubscriptionBindingService.h"
#include "onvif_impl.h"


int PullPointSubscriptionBindingService::PullMessages(_tev__PullMessages *tev__PullMessages, _tev__PullMessagesResponse &tev__PullMessagesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	for (int i=0; i<10; i++)
	{
		std::ostringstream os;
		os << "msg:" << i;
		std::string msg(os.str());
		tev__PullMessagesResponse.wsnt__NotificationMessage.push_back(soap_new_wsnt__NotificationMessageHolderType(this->soap));
		tev__PullMessagesResponse.wsnt__NotificationMessage.back()->Message.__any = soap_dom_element(this->soap, (char*)NULL, (char*)NULL, msg.c_str());
	}
	return SOAP_OK;
}

int PullPointSubscriptionBindingService::Seek(_tev__Seek *tev__Seek, _tev__SeekResponse &tev__SeekResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int PullPointSubscriptionBindingService::SetSynchronizationPoint(_tev__SetSynchronizationPoint *tev__SetSynchronizationPoint, _tev__SetSynchronizationPointResponse &tev__SetSynchronizationPointResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}
