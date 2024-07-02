/* --------------------------------------------------------------------------
Services list in ONVIF camera:
Device Service
Media Service
Imaging Service
Event Service
Recording Service
Replay Service
Search Service
Display Service
DeviceIO Service
Receiver Service
PTZ Service
-----------------------------------------------------------------------------
 serverDevice.cpp
 
 devicemgmt.wsdl server
----------------------------------------------------------------------------- */
#include <ifaddrs.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <resolv.h>
#include <sys/utsname.h>

#include <map>
#include <sstream>
#include <iomanip>

#include "soapDeviceBindingService.h"
#include "onvif_impl.h"
/*Function retrieves list services provied by device*/
int DeviceBindingService::GetServices(_tds__GetServices *tds__GetServices, _tds__GetServicesResponse &tds__GetServicesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;	
	std::ostringstream os;
	os << "http://" << ctx->getServerIpFromClientIp(htonl(this->soap->ip)) << ":" << ctx->m_port;
	std::string url(os.str());
	
	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/device/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,5);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		tds__DeviceServiceCapabilities *capabilities = ctx->getDeviceServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "tds:Capabilities", capabilities, capabilities->soap_type());
	}

	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/media/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,6);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		trt__Capabilities *capabilities = ctx->getMediaServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "trt:Capabilities", capabilities, capabilities->soap_type());
	}


	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver20/imaging/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,5);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		timg__Capabilities *capabilities = ctx->getImagingServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "timg:Capabilities", capabilities, capabilities->soap_type());
	}

	
	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/events/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,6);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		tev__Capabilities *capabilities = ctx->getEventServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "tev:Capabilities", capabilities, capabilities->soap_type());
	}

	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/recording/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,5);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		trc__Capabilities *capabilities = ctx->getRecordingServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "trc:Capabilities", capabilities, capabilities->soap_type());
	}

	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/replay/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,2);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		trp__Capabilities *capabilities = ctx->getReplayServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "trp:Capabilities", capabilities, capabilities->soap_type());
	}

	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/search/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,4);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		tse__Capabilities *capabilities = ctx->getSearchServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "trs:Capabilities", capabilities, capabilities->soap_type());
	}

	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/display/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,1);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		tls__Capabilities *capabilities = ctx->getDisplayServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "tls:Capabilities", capabilities, capabilities->soap_type());
	}

	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/deviceIO/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,6);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		tmd__Capabilities *capabilities = ctx->getDeviceIOServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "tmd:Capabilities", capabilities, capabilities->soap_type());
	}
	
	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver10/receiver/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,1);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		trv__Capabilities *capabilities = ctx->getReceiverServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "trv:Capabilities", capabilities, capabilities->soap_type());
	}

	tds__GetServicesResponse.Service.push_back(soap_new_tds__Service(this->soap));
	tds__GetServicesResponse.Service.back()->Namespace  = "http://www.onvif.org/ver20/ptz/wsdl";
	tds__GetServicesResponse.Service.back()->XAddr = url;
	tds__GetServicesResponse.Service.back()->Version = soap_new_req_tt__OnvifVersion(this->soap,2,1);
	if (tds__GetServices->IncludeCapability)
	{
		tds__GetServicesResponse.Service.back()->Capabilities = soap_new__tds__Service_Capabilities(this->soap);
		tptz__Capabilities *capabilities = ctx->getPTZServiceCapabilities(this->soap);
		tds__GetServicesResponse.Service.back()->Capabilities->__any = soap_dom_element(this->soap, NULL, "tptz:Capabilities", capabilities, capabilities->soap_type());
	}
	
	return SOAP_OK;
}
/*Function fetches the capabilities of the device service*/
int DeviceBindingService::GetServiceCapabilities(_tds__GetServiceCapabilities *tds__GetServiceCapabilities, _tds__GetServiceCapabilitiesResponse &tds__GetServiceCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;	
	tds__GetServiceCapabilitiesResponse.Capabilities = ctx->getDeviceServiceCapabilities(this->soap);
	return SOAP_OK;
}
/*Function retrieves system information*/
int DeviceBindingService::GetDeviceInformation(_tds__GetDeviceInformation *tds__GetDeviceInformation, _tds__GetDeviceInformationResponse &tds__GetDeviceInformationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	struct utsname info;	
	if (uname(&info) == 0) {
		tds__GetDeviceInformationResponse.Manufacturer    = info.release;
		tds__GetDeviceInformationResponse.Model           = info.sysname;
		tds__GetDeviceInformationResponse.HardwareId      = info.machine;
		tds__GetDeviceInformationResponse.FirmwareVersion = VERSION;
		tds__GetDeviceInformationResponse.SerialNumber    = info.version;
	}	
	return SOAP_OK;
}
/*Function sets the system date and time based on provided input values*/
int DeviceBindingService::SetSystemDateAndTime(_tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, _tds__SetSystemDateAndTimeResponse &tds__SetSystemDateAndTimeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	if (tds__SetSystemDateAndTime->TimeZone) {
		ctx->m_timezone = tds__SetSystemDateAndTime->TimeZone->TZ;
	}
	if (tds__SetSystemDateAndTime->TimeZone) {
		ctx->m_isdst = tds__SetSystemDateAndTime->DaylightSavings;
	}
	return SOAP_OK;
}
/*Function retrieves the current system date and time*/
int DeviceBindingService::GetSystemDateAndTime(_tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, _tds__GetSystemDateAndTimeResponse &tds__GetSystemDateAndTimeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	const time_t timestamp = time(NULL);
	struct tm * tm = gmtime(&timestamp);
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime = soap_new_tt__SystemDateTime(this->soap);
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime->DateTimeType = tt__SetDateTimeType__Manual;
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime->DaylightSavings = ctx->m_isdst;
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime->TimeZone = soap_new_tt__TimeZone(this->soap);
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime->TimeZone->TZ = ctx->m_timezone;
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime->UTCDateTime = soap_new_tt__DateTime(this->soap);
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime->UTCDateTime->Time = soap_new_req_tt__Time(this->soap, tm->tm_hour, tm->tm_min  , tm->tm_sec );
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime->UTCDateTime->Date = soap_new_req_tt__Date(this->soap, tm->tm_year, tm->tm_mon+1, tm->tm_mday);
	
	return SOAP_OK;
}

int DeviceBindingService::SetSystemFactoryDefault(_tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault, _tds__SetSystemFactoryDefaultResponse &tds__SetSystemFactoryDefaultResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::UpgradeSystemFirmware(_tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, _tds__UpgradeSystemFirmwareResponse &tds__UpgradeSystemFirmwareResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SystemReboot(_tds__SystemReboot *tds__SystemReboot, _tds__SystemRebootResponse &tds__SystemRebootResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::RestoreSystem(_tds__RestoreSystem *tds__RestoreSystem, _tds__RestoreSystemResponse &tds__RestoreSystemResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemBackup(_tds__GetSystemBackup *tds__GetSystemBackup, _tds__GetSystemBackupResponse &tds__GetSystemBackupResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemLog(_tds__GetSystemLog *tds__GetSystemLog, _tds__GetSystemLogResponse &tds__GetSystemLogResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemSupportInformation(_tds__GetSystemSupportInformation *tds__GetSystemSupportInformation, _tds__GetSystemSupportInformationResponse &tds__GetSystemSupportInformationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetScopes(_tds__GetScopes *tds__GetScopes, _tds__GetScopesResponse &tds__GetScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	for (auto scope : ctx->getScopes())
	{
		tds__GetScopesResponse.Scopes.push_back(soap_new_req_tt__Scope(soap,tt__ScopeDefinition__Fixed,scope));
	}
	return SOAP_OK;
}

int DeviceBindingService::SetScopes(_tds__SetScopes *tds__SetScopes, _tds__SetScopesResponse &tds__SetScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::AddScopes(_tds__AddScopes *tds__AddScopes, _tds__AddScopesResponse &tds__AddScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::RemoveScopes(_tds__RemoveScopes *tds__RemoveScopes, _tds__RemoveScopesResponse &tds__RemoveScopesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDiscoveryMode(_tds__GetDiscoveryMode *tds__GetDiscoveryMode, _tds__GetDiscoveryModeResponse &tds__GetDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetDiscoveryMode(_tds__SetDiscoveryMode *tds__SetDiscoveryMode, _tds__SetDiscoveryModeResponse &tds__SetDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetRemoteDiscoveryMode(_tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode, _tds__GetRemoteDiscoveryModeResponse &tds__GetRemoteDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRemoteDiscoveryMode(_tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode, _tds__SetRemoteDiscoveryModeResponse &tds__SetRemoteDiscoveryModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDPAddresses(_tds__GetDPAddresses *tds__GetDPAddresses, _tds__GetDPAddressesResponse &tds__GetDPAddressesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetEndpointReference(_tds__GetEndpointReference *tds__GetEndpointReference, _tds__GetEndpointReferenceResponse &tds__GetEndpointReferenceResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetRemoteUser(_tds__GetRemoteUser *tds__GetRemoteUser, _tds__GetRemoteUserResponse &tds__GetRemoteUserResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRemoteUser(_tds__SetRemoteUser *tds__SetRemoteUser, _tds__SetRemoteUserResponse &tds__SetRemoteUserResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetUsers(_tds__GetUsers *tds__GetUsers, _tds__GetUsersResponse &tds__GetUsersResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;	
	if (!ctx->m_userList.empty())
	{
		for (auto it : ctx->m_userList) {
			tds__GetUsersResponse.User.push_back(soap_new_tt__User(this->soap));
			tds__GetUsersResponse.User.back()->Username = it.first;
			tds__GetUsersResponse.User.back()->UserLevel = it.second.m_profile;
		}
	}
	return SOAP_OK;
}

int DeviceBindingService::CreateUsers(_tds__CreateUsers *tds__CreateUsers, _tds__CreateUsersResponse &tds__CreateUsersResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	for (auto it : tds__CreateUsers->User) {
		if (it->Password) {
			ctx->m_userList[it->Username] = User(it->Password->c_str(), it->UserLevel);
		}
	}	
	return SOAP_OK;
}

int DeviceBindingService::DeleteUsers(_tds__DeleteUsers *tds__DeleteUsers, _tds__DeleteUsersResponse &tds__DeleteUsersResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	for (auto it : tds__DeleteUsers->Username) {
		ctx->m_userList.erase(it);
	}		
	return SOAP_OK;
}

int DeviceBindingService::SetUser(_tds__SetUser *tds__SetUser, _tds__SetUserResponse &tds__SetUserResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetWsdlUrl(_tds__GetWsdlUrl *tds__GetWsdlUrl, _tds__GetWsdlUrlResponse &tds__GetWsdlUrlResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;	
	std::ostringstream os;
	os << "http://" << ctx->getServerIpFromClientIp(htonl(this->soap->ip)) << ":" << ctx->m_port;	
	tds__GetWsdlUrlResponse.WsdlUrl = os.str();
	return SOAP_OK;
}

int DeviceBindingService::GetCapabilities(_tds__GetCapabilities *tds__GetCapabilities, _tds__GetCapabilitiesResponse &tds__GetCapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	
	std::ostringstream os;
	os << "http://" << ctx->getServerIpFromClientIp(htonl(this->soap->ip)) << ":" << ctx->m_port;
	std::string url(os.str());
	
	tds__GetCapabilitiesResponse.Capabilities = soap_new_tt__Capabilities(this->soap);
	std::vector<tt__CapabilityCategory>& categories(tds__GetCapabilities->Category);
	if (categories.empty())
	{
		categories.push_back(tt__CapabilityCategory__All);
	}
	for (tt__CapabilityCategory category : categories)
	{
		if (!tds__GetCapabilitiesResponse.Capabilities->Device && ( (category == tt__CapabilityCategory__All) || (category == tt__CapabilityCategory__Device) ) )
		{
			tds__GetCapabilitiesResponse.Capabilities->Device = soap_new_tt__DeviceCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Device->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Device->System = soap_new_tt__SystemCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Device->System->SupportedVersions.push_back(soap_new_req_tt__OnvifVersion(this->soap,2,0));
			tds__GetCapabilitiesResponse.Capabilities->Device->Network = soap_new_tt__NetworkCapabilities(this->soap);	
			tds__GetCapabilitiesResponse.Capabilities->Device->Security = soap_new_tt__SecurityCapabilities(this->soap);	
			tds__GetCapabilitiesResponse.Capabilities->Device->IO = soap_new_tt__IOCapabilities(this->soap);
		}

		if (!tds__GetCapabilitiesResponse.Capabilities->Media && ( (category == tt__CapabilityCategory__All) || (category == tt__CapabilityCategory__Media) ) )
		{
			tds__GetCapabilitiesResponse.Capabilities->Media  = soap_new_tt__MediaCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Media->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Media->StreamingCapabilities = soap_new_tt__RealTimeStreamingCapabilities(this->soap);
		}

		if (!tds__GetCapabilitiesResponse.Capabilities->Imaging && ( (category == tt__CapabilityCategory__All) || (category == tt__CapabilityCategory__Imaging) ) )
		{
			tds__GetCapabilitiesResponse.Capabilities->Imaging = soap_new_tt__ImagingCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Imaging->XAddr = url;
		}

		if (!tds__GetCapabilitiesResponse.Capabilities->Events && ( (category == tt__CapabilityCategory__All) || (category == tt__CapabilityCategory__Events) ) )
		{
			tds__GetCapabilitiesResponse.Capabilities->Events = soap_new_tt__EventCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Events->XAddr = url;
		}

		if (!tds__GetCapabilitiesResponse.Capabilities->Extension && (category == tt__CapabilityCategory__All) )
		{
			tds__GetCapabilitiesResponse.Capabilities->Extension  = soap_new_tt__CapabilitiesExtension(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Extension->Recording  = soap_new_tt__RecordingCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Extension->Recording->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Extension->Recording->MediaProfileSource = true;
			tds__GetCapabilitiesResponse.Capabilities->Extension->Recording->ReceiverSource = true;
			tds__GetCapabilitiesResponse.Capabilities->Extension->Replay  = soap_new_tt__ReplayCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Extension->Replay->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver = soap_new_tt__ReceiverCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Extension->Receiver->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Extension->Search = soap_new_tt__SearchCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Extension->Search->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Extension->Display = soap_new_tt__DisplayCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Extension->Display->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Extension->Display->FixedLayout = true;
			tds__GetCapabilitiesResponse.Capabilities->Extension->DeviceIO = soap_new_tt__DeviceIOCapabilities(this->soap);
			tds__GetCapabilitiesResponse.Capabilities->Extension->DeviceIO->XAddr = url;
			tds__GetCapabilitiesResponse.Capabilities->Extension->DeviceIO->VideoSources = ctx->m_devices.size();
			tds__GetCapabilitiesResponse.Capabilities->Extension->DeviceIO->VideoOutputs = 1;
		}
	}

	return SOAP_OK;
}

int DeviceBindingService::SetDPAddresses(_tds__SetDPAddresses *tds__SetDPAddresses, _tds__SetDPAddressesResponse &tds__SetDPAddressesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetHostname(_tds__GetHostname *tds__GetHostname, _tds__GetHostnameResponse &tds__GetHostnameResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	int ret = ctx->isAuthorized(this->soap);
	if (ret == SOAP_OK)
	{
		char buffer[HOST_NAME_MAX];
		tds__GetHostnameResponse.HostnameInformation = soap_new_req_tt__HostnameInformation(this->soap, false);
		tds__GetHostnameResponse.HostnameInformation->Name = soap_new_std__string(this->soap);
		if (gethostname(buffer, sizeof(buffer)) == 0)
		{
			tds__GetHostnameResponse.HostnameInformation->Name->assign(buffer);
		}
	}
      
	return ret;
}

int DeviceBindingService::SetHostname(_tds__SetHostname *tds__SetHostname, _tds__SetHostnameResponse &tds__SetHostnameResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetHostnameFromDHCP(_tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP, _tds__SetHostnameFromDHCPResponse &tds__SetHostnameFromDHCPResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_FAULT;
}

int DeviceBindingService::GetDNS(_tds__GetDNS *tds__GetDNS, _tds__GetDNSResponse &tds__GetDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	tds__GetDNSResponse.DNSInformation = soap_new_tt__DNSInformation(soap);
	struct __res_state state;
	res_ninit(&state);
	for (int i=0; i < state.nscount; i++)
	{
		tt__IPAddress* address = soap_new_tt__IPAddress(soap);
		address->Type = tt__IPType__IPv4;
		address->IPv4Address = soap_new_std__string(soap);
		address->IPv4Address->assign(inet_ntoa(state.nsaddr_list[i].sin_addr));
		tds__GetDNSResponse.DNSInformation->DNSManual.push_back(address);
	}
	
	return SOAP_OK;
}

int DeviceBindingService::SetDNS(_tds__SetDNS *tds__SetDNS, _tds__SetDNSResponse &tds__SetDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_FAULT;
}

int DeviceBindingService::GetNTP(_tds__GetNTP *tds__GetNTP, _tds__GetNTPResponse &tds__GetNTPResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	tds__GetNTPResponse.NTPInformation = soap_new_tt__NTPInformation(soap);
	return SOAP_OK;
}

int DeviceBindingService::SetNTP(_tds__SetNTP *tds__SetNTP, _tds__SetNTPResponse &tds__SetNTPResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_FAULT;
}

int DeviceBindingService::GetDynamicDNS(_tds__GetDynamicDNS *tds__GetDynamicDNS, _tds__GetDynamicDNSResponse &tds__GetDynamicDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetDynamicDNS(_tds__SetDynamicDNS *tds__SetDynamicDNS, _tds__SetDynamicDNSResponse &tds__SetDynamicDNSResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_FAULT;
}

int DeviceBindingService::GetNetworkInterfaces(_tds__GetNetworkInterfaces *tds__GetNetworkInterfaces, _tds__GetNetworkInterfacesResponse &tds__GetNetworkInterfacesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;	
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	std::map<in_addr_t,in_addr_t> routeTable = ctx->getGateways();
	
	char host[NI_MAXHOST];
	struct ifaddrs *ifaddr = NULL;
	if (getifaddrs(&ifaddr) == 0) 
	{
		// get MAC addresses
		std::map<std::string,std::string> eterMap;
		for (struct ifaddrs* ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
		{
			if ( (ifa->ifa_addr != NULL) && (ifa->ifa_addr->sa_family == AF_PACKET) )			
			{
				struct sockaddr_ll *s = (struct sockaddr_ll*)ifa->ifa_addr;
				std::ostringstream os;
				os << std::hex << std::setw(2) << std::setfill('0');
				for (int i=0; i <s->sll_halen; i++)
				{
					if (i!=0) os <<":";
					os << (int)s->sll_addr[i];
				}
				eterMap[ifa->ifa_name] = os.str();
			}
		}
		
		// get corresponding IP address		
		for (struct ifaddrs* ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
		{
			int prefix = 0;
			if ( (ifa->ifa_netmask != NULL) && (ifa->ifa_netmask->sa_family == AF_INET) )
			{
				unsigned int mask = htonl(((struct sockaddr_in *)(ifa->ifa_netmask))->sin_addr.s_addr);
				while (mask  != 0)
				{
					mask <<= 1;
					prefix++;
				}
			}
			if ( (ifa->ifa_addr != NULL) && (ifa->ifa_addr->sa_family == AF_INET) )			
			{
				if ( ( (ifa->ifa_flags & IFF_LOOPBACK) == 0 ) && (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, sizeof(host), NULL, 0, NI_NUMERICHOST) == 0) )
				{
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.push_back(soap_new_tt__NetworkInterface(this->soap));
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->Enabled = true;
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->Info = soap_new_tt__NetworkInterfaceInfo(this->soap);
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->Info->Name = soap_new_std__string(this->soap);
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->Info->Name->assign(ifa->ifa_name);
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->Info->HwAddress = eterMap[ifa->ifa_name];
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->IPv4 = soap_new_tt__IPv4NetworkInterface(this->soap);
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->IPv4->Config = soap_new_tt__IPv4Configuration(this->soap);
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->IPv4->Config->Manual.push_back(soap_new_tt__PrefixedIPv4Address(this->soap));
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->IPv4->Config->Manual.back()->Address = host;		
					tds__GetNetworkInterfacesResponse.NetworkInterfaces.back()->IPv4->Config->Manual.back()->PrefixLength = prefix;
				}
			}
		}
	}
	freeifaddrs(ifaddr);

	return SOAP_OK;
}

int DeviceBindingService::SetNetworkInterfaces(_tds__SetNetworkInterfaces *tds__SetNetworkInterfaces, _tds__SetNetworkInterfacesResponse &tds__SetNetworkInterfacesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetNetworkProtocols(_tds__GetNetworkProtocols *tds__GetNetworkProtocols, _tds__GetNetworkProtocolsResponse &tds__GetNetworkProtocolsResponse) 
{
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	std::cout << __FUNCTION__ << std::endl;
	tds__GetNetworkProtocolsResponse.NetworkProtocols.push_back(soap_new_tt__NetworkProtocol(soap));
	tds__GetNetworkProtocolsResponse.NetworkProtocols.back()->Name = tt__NetworkProtocolType__HTTP;
	tds__GetNetworkProtocolsResponse.NetworkProtocols.back()->Enabled = true;
	tds__GetNetworkProtocolsResponse.NetworkProtocols.back()->Port.push_back(ctx->m_port);

	tds__GetNetworkProtocolsResponse.NetworkProtocols.push_back(soap_new_tt__NetworkProtocol(soap));
	tds__GetNetworkProtocolsResponse.NetworkProtocols.back()->Name = tt__NetworkProtocolType__RTSP;
	tds__GetNetworkProtocolsResponse.NetworkProtocols.back()->Enabled = true;
	tds__GetNetworkProtocolsResponse.NetworkProtocols.back()->Port.push_back(ctx->m_rtspport);
	return SOAP_OK;
}

int DeviceBindingService::SetNetworkProtocols(_tds__SetNetworkProtocols *tds__SetNetworkProtocols, _tds__SetNetworkProtocolsResponse &tds__SetNetworkProtocolsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetNetworkDefaultGateway(_tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway, _tds__GetNetworkDefaultGatewayResponse &tds__GetNetworkDefaultGatewayResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;
	std::map<in_addr_t,in_addr_t> routeTable = ctx->getGateways();
	struct in_addr defaultGw;
	defaultGw.s_addr = routeTable[INADDR_ANY];

	tds__GetNetworkDefaultGatewayResponse.NetworkGateway = soap_new_tt__NetworkGateway(soap);
	tds__GetNetworkDefaultGatewayResponse.NetworkGateway->IPv4Address.push_back(inet_ntoa(defaultGw));

	return SOAP_OK;
}

int DeviceBindingService::SetNetworkDefaultGateway(_tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway, _tds__SetNetworkDefaultGatewayResponse &tds__SetNetworkDefaultGatewayResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetZeroConfiguration(_tds__GetZeroConfiguration *tds__GetZeroConfiguration, _tds__GetZeroConfigurationResponse &tds__GetZeroConfigurationResponse) 
{
	tds__GetZeroConfigurationResponse.ZeroConfiguration =  soap_new_tt__NetworkZeroConfiguration(soap);
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetZeroConfiguration(_tds__SetZeroConfiguration *tds__SetZeroConfiguration, _tds__SetZeroConfigurationResponse &tds__SetZeroConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_FAULT;
}

int DeviceBindingService::GetIPAddressFilter(_tds__GetIPAddressFilter *tds__GetIPAddressFilter, _tds__GetIPAddressFilterResponse &tds__GetIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetIPAddressFilter(_tds__SetIPAddressFilter *tds__SetIPAddressFilter, _tds__SetIPAddressFilterResponse &tds__SetIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_FAULT;
}

int DeviceBindingService::AddIPAddressFilter(_tds__AddIPAddressFilter *tds__AddIPAddressFilter, _tds__AddIPAddressFilterResponse &tds__AddIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::RemoveIPAddressFilter(_tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter, _tds__RemoveIPAddressFilterResponse &tds__RemoveIPAddressFilterResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetAccessPolicy(_tds__GetAccessPolicy *tds__GetAccessPolicy, _tds__GetAccessPolicyResponse &tds__GetAccessPolicyResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetAccessPolicy(_tds__SetAccessPolicy *tds__SetAccessPolicy, _tds__SetAccessPolicyResponse &tds__SetAccessPolicyResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::CreateCertificate(_tds__CreateCertificate *tds__CreateCertificate, _tds__CreateCertificateResponse &tds__CreateCertificateResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCertificates(_tds__GetCertificates *tds__GetCertificates, _tds__GetCertificatesResponse &tds__GetCertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCertificatesStatus(_tds__GetCertificatesStatus *tds__GetCertificatesStatus, _tds__GetCertificatesStatusResponse &tds__GetCertificatesStatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetCertificatesStatus(_tds__SetCertificatesStatus *tds__SetCertificatesStatus, _tds__SetCertificatesStatusResponse &tds__SetCertificatesStatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteCertificates(_tds__DeleteCertificates *tds__DeleteCertificates, _tds__DeleteCertificatesResponse &tds__DeleteCertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetPkcs10Request(_tds__GetPkcs10Request *tds__GetPkcs10Request, _tds__GetPkcs10RequestResponse &tds__GetPkcs10RequestResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::LoadCertificates(_tds__LoadCertificates *tds__LoadCertificates, _tds__LoadCertificatesResponse &tds__LoadCertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetClientCertificateMode(_tds__GetClientCertificateMode *tds__GetClientCertificateMode, _tds__GetClientCertificateModeResponse &tds__GetClientCertificateModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetClientCertificateMode(_tds__SetClientCertificateMode *tds__SetClientCertificateMode, _tds__SetClientCertificateModeResponse &tds__SetClientCertificateModeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetRelayOutputs(_tds__GetRelayOutputs *tds__GetRelayOutputs, _tds__GetRelayOutputsResponse &tds__GetRelayOutputsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRelayOutputSettings(_tds__SetRelayOutputSettings *tds__SetRelayOutputSettings, _tds__SetRelayOutputSettingsResponse &tds__SetRelayOutputSettingsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetRelayOutputState(_tds__SetRelayOutputState *tds__SetRelayOutputState, _tds__SetRelayOutputStateResponse &tds__SetRelayOutputStateResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SendAuxiliaryCommand(_tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand, _tds__SendAuxiliaryCommandResponse &tds__SendAuxiliaryCommandResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCACertificates(_tds__GetCACertificates *tds__GetCACertificates, _tds__GetCACertificatesResponse &tds__GetCACertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::LoadCertificateWithPrivateKey(_tds__LoadCertificateWithPrivateKey *tds__LoadCertificateWithPrivateKey, _tds__LoadCertificateWithPrivateKeyResponse &tds__LoadCertificateWithPrivateKeyResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetCertificateInformation(_tds__GetCertificateInformation *tds__GetCertificateInformation, _tds__GetCertificateInformationResponse &tds__GetCertificateInformationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::LoadCACertificates(_tds__LoadCACertificates *tds__LoadCACertificates, _tds__LoadCACertificatesResponse &tds__LoadCACertificatesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::CreateDot1XConfiguration(_tds__CreateDot1XConfiguration *tds__CreateDot1XConfiguration, _tds__CreateDot1XConfigurationResponse &tds__CreateDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetDot1XConfiguration(_tds__SetDot1XConfiguration *tds__SetDot1XConfiguration, _tds__SetDot1XConfigurationResponse &tds__SetDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot1XConfiguration(_tds__GetDot1XConfiguration *tds__GetDot1XConfiguration, _tds__GetDot1XConfigurationResponse &tds__GetDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot1XConfigurations(_tds__GetDot1XConfigurations *tds__GetDot1XConfigurations, _tds__GetDot1XConfigurationsResponse &tds__GetDot1XConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteDot1XConfiguration(_tds__DeleteDot1XConfiguration *tds__DeleteDot1XConfiguration, _tds__DeleteDot1XConfigurationResponse &tds__DeleteDot1XConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot11Capabilities(_tds__GetDot11Capabilities *tds__GetDot11Capabilities, _tds__GetDot11CapabilitiesResponse &tds__GetDot11CapabilitiesResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetDot11Status(_tds__GetDot11Status *tds__GetDot11Status, _tds__GetDot11StatusResponse &tds__GetDot11StatusResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::ScanAvailableDot11Networks(_tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks, _tds__ScanAvailableDot11NetworksResponse &tds__ScanAvailableDot11NetworksResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetSystemUris(_tds__GetSystemUris *tds__GetSystemUris, _tds__GetSystemUrisResponse &tds__GetSystemUrisResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::StartFirmwareUpgrade(_tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade, _tds__StartFirmwareUpgradeResponse &tds__StartFirmwareUpgradeResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::StartSystemRestore(_tds__StartSystemRestore *tds__StartSystemRestore, _tds__StartSystemRestoreResponse &tds__StartSystemRestoreResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetStorageConfigurations(_tds__GetStorageConfigurations *tds__GetStorageConfigurations, _tds__GetStorageConfigurationsResponse &tds__GetStorageConfigurationsResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;	
	tds__GetStorageConfigurationsResponse.StorageConfigurations.push_back(ctx->getStorageCfg(this->soap, "/tmp"));
	return SOAP_OK;
}

int DeviceBindingService::CreateStorageConfiguration(_tds__CreateStorageConfiguration *tds__CreateStorageConfiguration, _tds__CreateStorageConfigurationResponse &tds__CreateStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetStorageConfiguration(_tds__GetStorageConfiguration *tds__GetStorageConfiguration, _tds__GetStorageConfigurationResponse &tds__GetStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	ServiceContext* ctx = (ServiceContext*)this->soap->user;	
	tds__GetStorageConfigurationResponse.StorageConfiguration = ctx->getStorageCfg(this->soap, "/tmp");
	return SOAP_OK;
}

int DeviceBindingService::SetStorageConfiguration(_tds__SetStorageConfiguration *tds__SetStorageConfiguration, _tds__SetStorageConfigurationResponse &tds__SetStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteStorageConfiguration(_tds__DeleteStorageConfiguration *tds__DeleteStorageConfiguration, _tds__DeleteStorageConfigurationResponse &tds__DeleteStorageConfigurationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::GetGeoLocation(_tds__GetGeoLocation *tds__GetGeoLocation, _tds__GetGeoLocationResponse &tds__GetGeoLocationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::SetGeoLocation(_tds__SetGeoLocation *tds__SetGeoLocation, _tds__SetGeoLocationResponse &tds__SetGeoLocationResponse) 
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}

int DeviceBindingService::DeleteGeoLocation(_tds__DeleteGeoLocation *tds__DeleteGeoLocation, _tds__DeleteGeoLocationResponse &tds__DeleteGeoLocationResponse)
{
	std::cout << __FUNCTION__ << std::endl;
	return SOAP_OK;
}
