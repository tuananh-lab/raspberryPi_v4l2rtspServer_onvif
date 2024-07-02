/*Here implements an ONVIF-compliant web service specifically for managing display-related functionalities.
 It includes capabilities to retrieve service capabilities, configure layouts, obtain display options, and manage pane configurations. */
#include "soapDisplayBindingService.h"
#include "onvif_impl.h"


int DisplayBindingService::GetServiceCapabilities(_tls__GetServiceCapabilities *tls__GetServiceCapabilities, _tls__GetServiceCapabilitiesResponse &tls__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tls__GetServiceCapabilitiesResponse.Capabilities = ctx->getDisplayServiceCapabilities(this->soap);		
	return SOAP_OK;
}

int DisplayBindingService::GetLayout(_tls__GetLayout *tls__GetLayout, _tls__GetLayoutResponse &tls__GetLayoutResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tls__GetLayoutResponse.Layout = soap_new_tt__Layout(this->soap);
	tls__GetLayoutResponse.Layout->PaneLayout.push_back(soap_new_tt__PaneLayout(this->soap));
	tls__GetLayoutResponse.Layout->PaneLayout.back()->Pane = ctx->m_outdevice;
	tls__GetLayoutResponse.Layout->PaneLayout.back()->Area = soap_new_tt__Rectangle(this->soap);
	return SOAP_OK;
}

int DisplayBindingService::SetLayout(_tls__SetLayout *tls__SetLayout, _tls__SetLayoutResponse &tls__SetLayoutResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DisplayBindingService::GetDisplayOptions(_tls__GetDisplayOptions *tls__GetDisplayOptions, _tls__GetDisplayOptionsResponse &tls__GetDisplayOptionsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	tls__GetDisplayOptionsResponse.CodingCapabilities = soap_new_tt__CodingCapabilities(this->soap);
	tls__GetDisplayOptionsResponse.CodingCapabilities->VideoDecodingCapabilities = soap_new_tt__VideoDecoderConfigurationOptions(this->soap);
	tls__GetDisplayOptionsResponse.CodingCapabilities->VideoDecodingCapabilities->H264DecOptions = soap_new_tt__H264DecOptions(this->soap);
	tls__GetDisplayOptionsResponse.CodingCapabilities->VideoDecodingCapabilities->H264DecOptions->ResolutionsAvailable.push_back(soap_new_req_tt__VideoResolution(this->soap, 640, 480));
	return SOAP_OK;
}

int DisplayBindingService::GetPaneConfigurations(_tls__GetPaneConfigurations *tls__GetPaneConfigurations, _tls__GetPaneConfigurationsResponse &tls__GetPaneConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DisplayBindingService::GetPaneConfiguration(_tls__GetPaneConfiguration *tls__GetPaneConfiguration, _tls__GetPaneConfigurationResponse &tls__GetPaneConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	tls__GetPaneConfigurationResponse.PaneConfiguration = soap_new_tt__PaneConfiguration(this->soap);
	tls__GetPaneConfigurationResponse.PaneConfiguration->PaneName = soap_new_std__string(this->soap);
	tls__GetPaneConfigurationResponse.PaneConfiguration->PaneName->assign("Display");
	tls__GetPaneConfigurationResponse.PaneConfiguration->ReceiverToken = soap_new_std__string(this->soap);
	tls__GetPaneConfigurationResponse.PaneConfiguration->ReceiverToken->assign("receivertoken");
	return SOAP_OK;
}

int DisplayBindingService::SetPaneConfigurations(_tls__SetPaneConfigurations *tls__SetPaneConfigurations, _tls__SetPaneConfigurationsResponse &tls__SetPaneConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DisplayBindingService::SetPaneConfiguration(_tls__SetPaneConfiguration *tls__SetPaneConfiguration, _tls__SetPaneConfigurationResponse &tls__SetPaneConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DisplayBindingService::CreatePaneConfiguration(_tls__CreatePaneConfiguration *tls__CreatePaneConfiguration, _tls__CreatePaneConfigurationResponse &tls__CreatePaneConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DisplayBindingService::DeletePaneConfiguration(_tls__DeletePaneConfiguration *tls__DeletePaneConfiguration, _tls__DeletePaneConfigurationResponse &tls__DeletePaneConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

