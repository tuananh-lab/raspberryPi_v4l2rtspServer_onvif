/* --------------------------------------------------------------------------
Here implements ONVIF replay service operations including capabilities retrieval and URI generation for replaying recorded content.
-----------------------------------------------------------------------------
 serverReplay.cpp
 
 replay.wsdl server
----------------------------------------------------------------------------- */

#include "soapReplayBindingService.h"
#include "onvif_impl.h"

int ReplayBindingService::GetServiceCapabilities(_trp__GetServiceCapabilities *trp__GetServiceCapabilities, _trp__GetServiceCapabilitiesResponse &trp__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	trp__GetServiceCapabilitiesResponse.Capabilities = ctx->getReplayServiceCapabilities(this->soap);	
	return SOAP_OK;
}

int ReplayBindingService::GetReplayUri(_trp__GetReplayUri *trp__GetReplayUri, _trp__GetReplayUriResponse &trp__GetReplayUriResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;	
	trp__GetReplayUriResponse.Uri = "rtsp://";
	trp__GetReplayUriResponse.Uri.append(ctx->getServerIpFromClientIp(htonl(this->soap->ip)));
	trp__GetReplayUriResponse.Uri.append("/");
	if (trp__GetReplayUri != NULL)
	{
		trp__GetReplayUriResponse.Uri.append(trp__GetReplayUri->RecordingToken);
	}
	return SOAP_OK;
}

int ReplayBindingService::GetReplayConfiguration(_trp__GetReplayConfiguration *trp__GetReplayConfiguration, _trp__GetReplayConfigurationResponse &trp__GetReplayConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int ReplayBindingService::SetReplayConfiguration(_trp__SetReplayConfiguration *trp__SetReplayConfiguration, _trp__SetReplayConfigurationResponse &trp__SetReplayConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}
