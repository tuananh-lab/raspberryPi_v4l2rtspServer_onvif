/* --------------------------------------------------------------------------
Here implement explain notify message service
-----------------------------------------------------------------------------
 serverNotificationConsumer.cpp
 
 bw-2.wsdl server
----------------------------------------------------------------------------- */

#include "soapNotificationConsumerBindingService.h"
#include "onvif_impl.h"


int NotificationConsumerBindingService::Notify(_wsnt__Notify *wsnt__Notify) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	for (auto msg : wsnt__Notify->NotificationMessage)
	{
		std::cout << "\tMessage:" << msg->Message.__any << std::endl;
	}
	
	return SOAP_OK;
}
