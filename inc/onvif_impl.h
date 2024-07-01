
#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

#include <list>
#include <map>

#include "soapH.h"

class NotificationConsumerBindingProxy;

class User 
{
	public:
		User () {}
		User (const std::string & password, enum tt__UserLevel profile) : m_password(password), m_profile(profile) {}
		std::string        m_password;
		enum tt__UserLevel m_profile;
};

class ServiceContext
{
public:
	std::string                   getLocalIp();
	std::string                   getServerIpFromClientIp(int ip);
	std::list<std::string>        getScopes();
	std::string                   getScopesString();
	std::map<in_addr_t,in_addr_t> getGateways();
	int                           isAuthorized(soap* soap);
	
	// V4L2 access
	int                getFormat        (const std::string &device, int& width, int& height, int& format);
	float              getFrameRate     (const std::string &device);
	int                getCtrlValue     (const std::string &device, int idctrl);
	void               setCtrlValue     (const std::string &device, int idctrl, int value);
	std::pair<int,int> getCtrlRange     (const std::string &device, int idctrl);
	void               getIdentification(const std::string &device, std::string & card, std::string & driver, std::string & bus);
	std::string        getName          (const std::string &device);

	// service capabilities
	tds__DeviceServiceCapabilities* getDeviceServiceCapabilities(struct soap* soap);
	trt__Capabilities*  getMediaServiceCapabilities    (struct soap* soap);
	timg__Capabilities* getImagingServiceCapabilities  (struct soap* soap);
	trc__Capabilities*  getRecordingServiceCapabilities(struct soap* soap);
	tse__Capabilities*  getSearchServiceCapabilities   (struct soap* soap);
	trv__Capabilities*  getReceiverServiceCapabilities (struct soap* soap);
	trp__Capabilities*  getReplayServiceCapabilities   (struct soap* soap);
	tev__Capabilities*  getEventServiceCapabilities    (struct soap* soap);
	tls__Capabilities*  getDisplayServiceCapabilities  (struct soap* soap);
	tmd__Capabilities*  getDeviceIOServiceCapabilities (struct soap* soap);
	tptz__Capabilities* getPTZServiceCapabilities      (struct soap* soap);

	// device
	tds__StorageConfiguration* getStorageCfg(struct soap* soap, const std::string & path);

	// media 
	tt__Profile*                          getProfile               (struct soap* soap, const std::string & token);
	tt__VideoSourceConfiguration*         getVideoSourceCfg        (struct soap* soap, const std::string & token);
	tt__VideoSourceConfigurationOptions*  getVideoSourceCfgOptions (struct soap* soap, const std::string & token);
	tt__VideoEncoderConfiguration*        getVideoEncoderCfg       (struct soap* soap, const std::string & token);
	tt__VideoEncoderConfigurationOptions* getVideoEncoderCfgOptions(struct soap* soap, const std::string & token);
	tt__MetadataConfigurationOptions*     getMetadataCfgOptions    (struct soap* soap, const std::string & token);

	// recording
	tt__RecordingJobConfiguration* getRecordingJobConfiguration(struct soap* soap, const std::string & token);
	tt__RecordingConfiguration*    getRecordingCfg(struct soap* soap);
	tt__TrackConfiguration*        getTracksCfg(struct soap* soap);
	
public:
	std::map<std::string,std::string> m_devices;
	std::string m_outdevice;
	int         m_port;
	int         m_rtspport;
	std::map<std::string, User> m_userList;
	std::list<NotificationConsumerBindingProxy*> m_subscriber;
	std::string m_timezone;
	int         m_isdst;
};

template<typename T>
T * soap_new_ptr(struct soap* soap, T value)
{
	T* ptr = (T*)soap_malloc(soap, sizeof(T));
	*ptr = value;
	return ptr;
}


#endif
